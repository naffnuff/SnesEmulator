#include "Emulator.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Common/Exception.h"
#include "Common/Memory.h"

#include "VideoDebugger.h"

#include "DmaInstruction.h"
#include "HdmaInstruction.h"

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context<State>& context, OtherState& otherState, Debugger::Context<OtherState>& otherContext, std::ostream& error);

void Emulator::initialize()
{
    videoRegisters.initialize();

    rom.storeToMemory(cpuState);

    CPU::State::MemoryType& cpuMemory = cpuState.getMemory();

    if (rom.isLowRom()) {
        // RAM
        for (Long address = 0x7e0000; address < 0x800000; address++) {
            cpuMemory.createLocation<ReadWriteMemory>(address, 0x55);
        }

        // RAM mirrors
        for (Byte bank = 0; bank < 0x40; ++bank) {
            for (Word address = 0; address < 0x2000; ++address) {
                cpuMemory.createMirror(Long(address, bank), Long(address, 0x7E));
            }
        }

        // I/O between the CPU and SPC700
        for (Word i = 0; i < 4; ++i) {
            cpuMemory.createLocation<ReadWriteRegister>(Long(0x2140 + i),
                [this, i](Byte& value) {
                    value = spcToCpuBuffers[i];
                },
                [this, i](Byte, Byte newValue) {
                    cpuToSpcBuffers[i] = newValue;
                }
            );
        }

        // Register mirrors
        for (Byte bank = 0x01; bank < 0x60; ++bank) {
            for (Word address = 0x2000; address < 0x8000; ++address) {
                cpuMemory.createMirror(Long(address, bank), Long(address, 0x00));
            }
        }

        // ROM mirrors
        for (Long address = 0; address < 0x600000; ++address) {
            cpuMemory.createMirror(address + 0x800000, address);
        }

        // Save RAM
        {
            if (rom.saveRamSize > 0) {
                std::ifstream file(rom.gameTitle + ".save");
                file >> std::hex;
                Long saveRamAddress = 0x700000;
                for (Long address = saveRamAddress; address < 0x7e0000; ++address, ++saveRamAddress) {
                    if (saveRamAddress == 0x700000 + rom.saveRamSize) {
                        saveRamAddress = 0x700000;
                    }
                    if (address == saveRamAddress) {
                        Byte byte;
                        int inputValue;
                        if (file >> inputValue) {
                            byte = inputValue;
                        }
                        Long localAddress = address - 0x700000;
                        saveRamSaver.saveRam[localAddress] = byte;
                        cpuMemory.createLocation<ReadWriteRegister>(address,
                            [this, localAddress](Byte& value) {
                                value = saveRamSaver.saveRam[localAddress];
                            },
                            [this, localAddress](Byte oldValue, Byte newValue) {
                                if (oldValue != saveRamSaver.saveRam[localAddress]) {
                                    std::stringstream ss;
                                    ss << __FUNCTION__ << ": ";
                                    ss << "oldValue=" << oldValue << " != saveRamSaver.saveRam[address]=" << saveRamSaver.saveRam[localAddress];
                                    ss << " @" << localAddress << std::endl;
                                    throw std::logic_error(ss.str());
                                }
                                if (newValue != saveRamSaver.saveRam[localAddress]) {
                                    saveRamSaver.saveRam[localAddress] = newValue;
                                    std::scoped_lock<std::mutex> lock(saveRamSaver.mutex);
                                    saveRamSaver.saveRamModified = true;
                                }
                                saveRamSaver.condition.notify_one();
                            },
                            byte);
                    } else {
                        cpuMemory.createMirror(address, saveRamAddress);
                    }
                }
                output << "Save RAM end address: " << saveRamAddress << std::endl;
            }
        }

        saveRamSaverThread = std::thread(std::ref(saveRamSaver));
    }
    else {
        throw std::runtime_error("Only the low-rom mempory map is supported for now");
    }

    videoProcessor.initialize(rom.gameTitle);

    audioSystem.initialize(cpuToSpcBuffers, spcToCpuBuffers);

    cpuMemory.finalize();

    cpuState.reset();

    debugger.loadBreakpoints(cpuContext, cpuState);

    cpuContext.nextInstruction = cpuInstructionDecoder.getNextInstruction(cpuState);
}

void Emulator::run()
{
    Video::OamViewer oamViewer(videoProcessor, 1080, 760);
    Video::BackgroundViewer background1Viewer(videoProcessor, Video::BackgroundLayer1, 0, 10);
    Video::BackgroundViewer background2Viewer(videoProcessor, Video::BackgroundLayer2, Video::rendererWidth * 2 + 20, 10);
    Video::BackgroundViewer background3Viewer(videoProcessor, Video::BackgroundLayer3, 0, Video::rendererWidth * 2 + 20);
    Video::BackgroundViewer background4Viewer(videoProcessor, Video::BackgroundLayer4, Video::rendererWidth * 2, Video::rendererWidth * 2 + 20);
    Video::SpriteLayerViewer spriteLayer1Viewer(videoProcessor, 0, Video::rendererWidth * 2 + 20, Video::rendererWidth * 2 + 40);
    Video::SpriteLayerViewer spriteLayer2Viewer(videoProcessor, 1, Video::rendererWidth * 2 + 20 + Video::rendererWidth + 20, Video::rendererWidth * 2 + 40);
    Video::SpriteLayerViewer spriteLayer3Viewer(videoProcessor, 2, Video::rendererWidth * 2 + 20, Video::rendererWidth * 2 + 40 + Video::rendererWidth);
    Video::SpriteLayerViewer spriteLayer4Viewer(videoProcessor, 3, Video::rendererWidth * 2 + 20 + Video::rendererWidth + 20, Video::rendererWidth * 2 + 40 + Video::rendererWidth);
    Video::Mode7Viewer mode7Viewer(videoProcessor, 0, 40);

    DmaInstruction dmaInstruction(output, error, cpuState, videoRegisters);
    HdmaInstruction hdmaInstruction(output, error, cpuState, videoRegisters);

    uint64_t nextCpu = masterCycle;
    uint64_t nextSpc = masterCycle;
    uint64_t cycleCountTarget = masterCycle;

    uint64_t audioCycle = 0;

    videoRegisters.hCounter = int(masterCycle);

    bool nmiRequested = false;
    bool irqRequested = false;

    //cpuContext.setPaused(true);

    double runStartTime = 0.0;
    uint64_t cycleCountDelta = 0;
    bool stepMode = debugger.isPaused();
    if (!stepMode) {
        debugger.startTime = clock();
        runStartTime = videoProcessor.renderer.getTime();
    }
    stepMode = true;

    audioSystem.start();

    try {
        uint64_t iteration = 0;
        bool dmaActive = false;
        while (running) {
            try {
                if (masterCycle == nextCpu) {
                    if (nmiRequested) {
                        nmiRequested = false;
                        cpuState.startInterrupt(true);
                        nextCpu += 9 * 8; // TODO: check the correct cycles for interrupt
                    }
                    else if (irqRequested && !cpuState.getFlag(CPU::State::i) && !cpuState.isNmiActive()) {
                        irqRequested = false;
                        cpuState.startInterrupt(false);
                        nextCpu += 9 * 8; // TODO: check the correct cycles for interrupt
                    }

                    Instruction* instruction = cpuInstructionDecoder.getNextInstruction(cpuState);

                    bool dmaPicked = false;
                    if (dmaInstruction.enabled()) {
                        //cpuContext.setPaused(true);
                        dmaInstruction.blockedInstruction = instruction;
                        instruction = static_cast<Instruction*>(&dmaInstruction);
                        dmaPicked = true;
                        if (!videoRegisters.vBlank) {
                            //output << "DMA not during V blank" << std::endl;
                            //cpuContext.stepMode = true;
                        }
                    }

                    if (hdmaInstruction.isActive()) {
                        hdmaInstruction.blockedInstruction = instruction;
                        instruction = static_cast<Instruction*>(&hdmaInstruction);
                        if (dmaPicked) {
                            output << "HDMA interrupts DMA" << std::endl;
                        }
                    }

                    cpuContext.nextInstruction = instruction;

                    instruction->applyBreakpoints();

                    if (cpuContext.isStepMode()) {
                        output << "Cycle count: " << masterCycle << ", Next cpu: " << nextCpu << ", Next spc: " << nextSpc << std::endl;
                        output << "Frame: " << videoRegisters.frame << ", V counter: " << videoRegisters.vCounter << ", H counter: " << videoRegisters.hCounter << ", V blank: " << videoRegisters.vBlank << ", H blank: " << videoRegisters.hBlank << ", nmi: " << cpuState.isNmiActive() << ", irq: " << cpuState.isIrqActive() << std::endl;
                        debugger.printBreakpoints(cpuContext, audioSystem.context);
                        debugger.printMemory(cpuState, cpuContext, audioSystem.state, audioSystem.context, videoProcessor);
                    }

                    if (int cycles = executeNext(instruction, cpuState, debugger, cpuContext, audioSystem.state, audioSystem.context, error)) {
                        nextCpu += uint64_t(cycles) * 6;
                        cpuContext.nextInstruction = cpuInstructionDecoder.getNextInstruction(cpuState);
                    }
                    else {
                        continue;
                    }
                }

                if (videoRegisters.pauseRequested) {
                    videoRegisters.pauseRequested = false;
                    debugger.pause(cpuContext);
                }

                if (audioSystem.pauseRequested) {
                    audioSystem.pauseRequested = false;
                    debugger.pause(audioSystem.context);
                }

                if (debugger.isPaused()) {
                    if (masterCycle == nextSpc) {
                        Instruction* instruction = audioSystem.instructionDecoder.getNextInstruction(audioSystem.state);
                        audioSystem.context.nextInstruction = instruction;

                        instruction->applyBreakpoints();

                        if (audioSystem.context.isStepMode()) {
                            output << "cycleCount=" << masterCycle << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                            debugger.printBreakpoints(cpuContext, audioSystem.context);
                            debugger.printMemory(cpuState, cpuContext, audioSystem.state, audioSystem.context, videoProcessor);
                        }

                        if (int cycles = executeNext(instruction, audioSystem.state, debugger, audioSystem.context, cpuState, cpuContext, error)) {
                            nextSpc += uint64_t(cycles) * 16;
                            audioSystem.context.nextInstruction = audioSystem.instructionDecoder.getNextInstruction(audioSystem.state);
                        } else {
                            continue;
                        }
                    }
                }

                bool increment = false;
                if (debugger.isPaused()) { // step mode
                    increment = true;
                    stepMode = true;
                }
                else if (stepMode) { // run mode initiated
                    stepMode = false;
                    runStartTime = videoProcessor.renderer.getTime();
                    cycleCountDelta = 0;
                }
                else { // run mode continued
                    if (iteration % 100 == 0) {
                        double elapsedTime = videoProcessor.renderer.getTime() - runStartTime;
                        static const double clockSpeedTarget = 1.89e9 / 88.0;
                        cycleCountTarget = uint64_t(elapsedTime * clockSpeedTarget);
                    }

                    if (cycleCountTarget > cycleCountDelta) {
                        increment = true;
                    }

                    //increment = true;

                    if (increment) {
                        ++cycleCountDelta;
                    }
                }

                if (increment) {
                    ++masterCycle;
                    if (masterCycle % 21 == 0) {
                        audioSystem.tick();
                    }
                    ++videoRegisters.hCounter;
                    if (videoRegisters.hCounter == 274) {
                        if (videoRegisters.vCounter <= 224) {
                            if (videoRegisters.vCounter > 0) {
                                videoProcessor.drawScanline(videoRegisters.vCounter);
                            }
                            if (hdmaInstruction.enabled() && !hdmaInstruction.isActive()) {
                                hdmaInstruction.setActive(true);
                            }
                        }
                        if (videoRegisters.vCounter == 224) {
                            static double previousTime = videoProcessor.renderer.getTime();
                            static uint32_t frameCount = 0;
                            static uint32_t totalFrameCount = 0;

                            double currentTime = videoProcessor.renderer.getTime();
                            ++frameCount;
                            ++totalFrameCount;
                            static uint32_t minFrameCount = -1;
                            static uint32_t maxFrameCount = 0;
                            static int printOuts = 0;
                            if (currentTime - previousTime >= 1.0) {
                                minFrameCount = min(minFrameCount, frameCount);
                                maxFrameCount = max(maxFrameCount, frameCount);

                                output << "FPS: " << frameCount << std::endl;

                                frameCount = 0;
                                previousTime = currentTime;

                                if (++printOuts % 10 == 0) {
                                    double elapsedTime = videoProcessor.renderer.getTime() - runStartTime;
                                    output << "Avg. FPS: " << (totalFrameCount / elapsedTime) << std::endl;
                                    output << "Min. FPS: " << minFrameCount << std::endl;
                                    output << "Max. FPS: " << maxFrameCount << std::endl;
                                }
                            }

                            //videoProcessor.renderer.update();
                            videoProcessor.rendererLock.unlock();

                            oamViewer.update();
                            background1Viewer.update();
                            background2Viewer.update();
                            background3Viewer.update();
                            background4Viewer.update();
                            spriteLayer1Viewer.update();
                            spriteLayer2Viewer.update();
                            spriteLayer3Viewer.update();
                            spriteLayer4Viewer.update();
                            mode7Viewer.update();

                        }
                        videoRegisters.hBlank = true;
                    }
                    else if (videoRegisters.hCounter == 1374) {
                        videoRegisters.hCounter = 0;
                        videoRegisters.hBlank = false;
                        ++videoRegisters.vCounter;
                        if (videoRegisters.irqMode == Video::Registers::VCounterIrq && videoRegisters.vTimer == videoRegisters.vCounter) {
                            irqRequested = true;
                        }
                        if (videoRegisters.vCounter == 225) {
                            hdmaInstruction.setActive(false);
                            videoRegisters.vBlank = true;
                            videoProcessor.oam.address = videoRegisters.oamStartAddress;
                            //videoRegisters.videoProcessor.vram.address = videoRegisters.vramStartAddress;
                            if (videoRegisters.nmiEnabled) {
                                nmiRequested = true;
                            }
                        }
                        else if (videoRegisters.vCounter == 227) {
                            videoRegisters.readControllers();
                        }
                        else if (videoRegisters.vCounter == 262) {
                            videoProcessor.rendererLock.lock();

                            if (videoProcessor.renderer.pauseRequested) {
                                videoProcessor.renderer.pauseRequested = false;
                                debugger.pause(cpuContext);
                            }

                            ++videoRegisters.frame;
                            videoRegisters.vCounter = 0;
                            videoRegisters.interlaceField = !videoRegisters.interlaceField;
                            videoRegisters.vBlank = false;

                            if (hdmaInstruction.enabled()) {
                                hdmaInstruction.setActive(true, true);
                            }
                        }
                    }
                    if (videoRegisters.hTimer == videoRegisters.hCounter) {
                        if (videoRegisters.irqMode == Video::Registers::HCounterIrq || videoRegisters.irqMode == Video::Registers::HAndVCounterIrq && videoRegisters.vTimer == videoRegisters.vCounter) {
                            irqRequested = true;
                        }
                    }
                }
                ++iteration;
            } catch (Video::MemoryAccessException& e) {
                //cpuState.setProgramAddress(cpuState.getLastKnownAddress());
                debugger.pause(cpuContext);
                error << e.what() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        running = false;
        throw e;
    }
}

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context<State>& context, OtherState& otherState, Debugger::Context<OtherState>& otherContext, std::ostream& error)
{
    context.addKnownAddress(state.getProgramAddress());
    try {
        if (debugger.isPaused()) {
            debugger.printState(state, context);

            if (debugger.awaitCommand(context, state, otherContext, otherState)) {
                int cycles = instruction->execute();
                if (debugger.isPaused()) {
                    debugger.printRegisters(state, context);
                }
                return cycles;
            }
        }
        else {
            return instruction->execute();
        }
    } catch (OpcodeNotYetImplementedException& e) {
        debugger.pause(context);
        error << e.what() << std::endl;
    } catch (AddressModeNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        debugger.pause(context);
        error << e.what() << std::endl;
    } catch (OperatorNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        debugger.pause(context);
        error << e.what() << std::endl;
    } catch (MemoryAccessException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        debugger.pause(context);
        error << e.what() << std::endl;
    } catch (Video::NotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        debugger.pause(context);
        error << e.what() << std::endl;
    }
    return 0;
}
