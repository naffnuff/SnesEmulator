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
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error);

void Emulator::initialize()
{
    registers.initialize();

    rom.storeToMemory(cpuState);

    CPU::State::MemoryType& memory = cpuState.getMemory();

    if (rom.isLowRom()) {
        // RAM
        for (Long address = 0x7e0000; address < 0x800000; address++) {
            memory.createLocation<ReadWriteMemory>(address, 0x55);
        }

        // RAM mirrors
        for (Byte bank = 0; bank < 0x40; ++bank) {
            for (Word address = 0; address < 0x2000; ++address) {
                memory.createMirror(Long(address, bank), Long(address, 0x7E));
            }
        }

        // I/O between the CPU and SPC700
        for (Word i = 0; i < 4; ++i) {
            memory.createLocation<ReadWriteRegister>(Long(0x2140 + i),
                [this, i](Byte& value) {
                    value = spcToCpuBuffers[i];
                },
                [this, i](Byte, Byte newValue) {
                    cpuToSpcBuffers[i] = newValue;
                });
            MemoryLocation* spcMemoryLocation = spcState.getMemoryLocation(Word(0xf4 + i));
            spcMemoryLocation->setReadWrite();
            spcMemoryLocation->onRead = [this, i](Byte& value) {
                value = cpuToSpcBuffers[i];
            };
            spcMemoryLocation->onWrite = [this, i](Byte, Byte newValue) {
                spcToCpuBuffers[i] = newValue;
            };
        }

        // Register mirrors
        for (Byte bank = 0x01; bank < 0x60; ++bank) {
            for (Word address = 0x2000; address < 0x8000; ++address) {
                memory.createMirror(Long(address, bank), Long(address, 0x00));
            }
        }

        // ROM mirrors
        for (Long address = 0; address < 0x600000; ++address) {
            memory.createMirror(address + 0x800000, address);
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
                        memory.createLocation<ReadWriteRegister>(address,
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
                                    std::lock_guard<std::mutex> lock(saveRamSaver.mutex);
                                    saveRamSaver.saveRamModified = true;
                                }
                                saveRamSaver.condition.notify_one();
                            },
                            byte);
                    } else {
                        memory.createMirror(address, saveRamAddress);
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

    video.initialize(rom.gameTitle);

    audio.initialize(memory);

    memory.finalize();

    cpuState.reset();

    debugger.loadBreakpoints(cpuContext, cpuState);
    debugger.loadBreakpoints(spcContext, spcState);

    cpuContext.nextInstruction = cpuInstructionDecoder.getNextInstruction(cpuState);
    spcContext.nextInstruction = spcInstructionDecoder.getNextInstruction(spcState);
}

void Emulator::run()
{
    OamViewer oamViewer(video, 1080, 760);
    BackgroundViewer background1Viewer(video, BackgroundLayer1, 0, 10);
    BackgroundViewer background2Viewer(video, BackgroundLayer2, Video::rendererWidth * 2 + 20, 10);
    BackgroundViewer background3Viewer(video, BackgroundLayer3, 0, Video::rendererWidth * 2 + 20);
    BackgroundViewer background4Viewer(video, BackgroundLayer4, Video::rendererWidth * 2, Video::rendererWidth * 2 + 20);
    SpriteLayerViewer spriteLayer1Viewer(video, 0, Video::rendererWidth * 2 + 20, Video::rendererWidth * 2 + 40);
    SpriteLayerViewer spriteLayer2Viewer(video, 1, Video::rendererWidth * 2 + 20 + Video::rendererWidth + 20, Video::rendererWidth * 2 + 40);
    SpriteLayerViewer spriteLayer3Viewer(video, 2, Video::rendererWidth * 2 + 20, Video::rendererWidth * 2 + 40 + Video::rendererWidth);
    SpriteLayerViewer spriteLayer4Viewer(video, 3, Video::rendererWidth * 2 + 20 + Video::rendererWidth + 20, Video::rendererWidth * 2 + 40 + Video::rendererWidth);
    Mode7Viewer mode7Viewer(video, 0, 40);

    DmaInstruction dmaInstruction(output, error, cpuState, registers);
    HdmaInstruction hdmaInstruction(output, error, cpuState, registers);

    uint64_t nextCpu = masterCycle;
    uint64_t nextSpc = masterCycle;
    uint64_t cycleCountTarget = masterCycle;

    uint64_t audioCycle = 0;

    registers.hCounter = int(masterCycle);

    bool nmiRequested = false;
    bool irqRequested = false;

    //cpuContext.setPaused(true);

    double runStartTime = 0.0;
    uint64_t cycleCountDelta = 0;
    bool stepMode = cpuContext.isPaused() || spcContext.isPaused();
    if (!stepMode) {
        output << "Snip" << std::endl;
        debugger.startTime = clock();
        runStartTime = video.renderer.getTime();
    }
    stepMode = true;

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
                        if (!registers.vBlank) {
                            //output << "DMA not during V blank" << std::endl;
                            //cpuContext.stepMode = true;
                        }
                    }

                    if (hdmaInstruction.isActive()) {
                        hdmaInstruction.blockedInstruction = instruction;
                        instruction = static_cast<Instruction*>(&hdmaInstruction);
                        if (dmaPicked) {
                            output << "HDMA interrupts DMA" << std::endl;
                            cpuContext.setPaused(true);
                        }
                    }

                    cpuContext.nextInstruction = instruction;

                    instruction->applyBreakpoints();

                    if (cpuContext.isPaused()) {
                        output << "Cycle count: " << masterCycle << ", Next cpu: " << nextCpu << ", Next spc: " << nextSpc << std::endl;
                        output << "Frame: " << registers.frame << ", V counter: " << registers.vCounter << ", H counter: " << registers.hCounter << ", V blank: " << registers.vBlank << ", H blank: " << registers.hBlank << ", nmi: " << cpuState.isNmiActive() << ", irq: " << cpuState.isIrqActive() << std::endl;
                        debugger.printBreakpoints(cpuContext, spcContext);
                        debugger.printMemory(cpuState, cpuContext, spcState, spcContext, video);
                    }

                    if (int cycles = executeNext(instruction, cpuState, debugger, cpuContext, spcState, spcContext, error)) {
                        nextCpu += uint64_t(cycles) * 6;
                        cpuContext.nextInstruction = cpuInstructionDecoder.getNextInstruction(cpuState);
                    }
                    else {
                        continue;
                    }
                }

                if (registers.pauseRequested) {
                    cpuContext.setPaused(true);
                    registers.pauseRequested = false;
                }

                if (masterCycle == nextSpc) {
                    Instruction* instruction = spcInstructionDecoder.getNextInstruction(spcState);
                    spcContext.nextInstruction = instruction;

                    if (spcContext.isPaused()) {
                        output << "cycleCount=" << masterCycle << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                        debugger.printBreakpoints(cpuContext, spcContext);
                        debugger.printMemory(cpuState, cpuContext, spcState, spcContext, video);
                    }

                    if (int cycles = executeNext(instruction, spcState, debugger, spcContext, cpuState, cpuContext, error)) {
                        nextSpc += uint64_t(cycles) * 16;
                        spcContext.nextInstruction = spcInstructionDecoder.getNextInstruction(spcState);
                    }
                    else {
                        continue;
                    }
                }

                bool increment = false;
                if (cpuContext.isPaused() || spcContext.isPaused()) { // step mode
                    increment = true;
                    stepMode = true;
                }
                else if (stepMode) { // run mode initiated
                    stepMode = false;
                    runStartTime = video.renderer.getTime();
                    cycleCountDelta = 0;
                }
                else { // run mode continued
                    if (iteration % 100 == 0) {
                        double elapsedTime = video.renderer.getTime() - runStartTime;
                        static const double clockSpeedTarget = 1.89e9 / 88.0;
                        cycleCountTarget = uint64_t(elapsedTime * clockSpeedTarget);
                    }

                    if (cycleCountTarget > cycleCountDelta) {
                        increment = true;
                    }

                    increment = true;

                    if (increment) {
                        ++cycleCountDelta;
                    }
                }

                if (increment) {
                    ++masterCycle;
                    if (masterCycle % 21 == 0) {
                        audio.tick();
                    }
                    ++registers.hCounter;
                    if (registers.hCounter == 274) {
                        if (registers.vCounter <= 224) {
                            if (registers.vCounter > 0) {
                                video.drawScanline(registers.vCounter);
                            }
                            if (hdmaInstruction.enabled() && !hdmaInstruction.isActive()) {
                                hdmaInstruction.setActive(true);
                            }
                        }
                        if (registers.vCounter == 224) {
                            static double previousTime = video.renderer.getTime();
                            static uint32_t frameCount = 0;
                            static uint32_t totalFrameCount = 0;

                            double currentTime = video.renderer.getTime();
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
                                    double elapsedTime = video.renderer.getTime() - runStartTime;
                                    output << "Avg. FPS: " << (totalFrameCount / elapsedTime) << std::endl;
                                    output << "Min. FPS: " << minFrameCount << std::endl;
                                    output << "Max. FPS: " << maxFrameCount << std::endl;
                                }
                            }

                            //video.renderer.update();
                            video.rendererLock.unlock();

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
                        registers.hBlank = true;
                    }
                    else if (registers.hCounter == 1374) {
                        registers.hCounter = 0;
                        registers.hBlank = false;
                        ++registers.vCounter;
                        if (registers.irqMode == Registers::VCounterIrq && registers.vTimer == registers.vCounter) {
                            irqRequested = true;
                        }
                        if (registers.vCounter == 225) {
                            hdmaInstruction.setActive(false);
                            registers.vBlank = true;
                            registers.video.oam.address = registers.oamStartAddress;
                            //registers.video.vram.address = registers.vramStartAddress;
                            if (registers.nmiEnabled) {
                                nmiRequested = true;
                            }
                        }
                        else if (registers.vCounter == 227) {
                            registers.readControllers();
                        }
                        else if (registers.vCounter == 262) {
                            video.rendererLock.lock();

                            if (video.renderer.pauseRequested) {
                                video.renderer.pauseRequested = false;
                                cpuContext.setPaused(true);
                            }

                            ++registers.frame;
                            registers.vCounter = 0;
                            registers.interlaceField = !registers.interlaceField;
                            registers.vBlank = false;

                            if (hdmaInstruction.enabled()) {
                                hdmaInstruction.setActive(true, true);
                            }
                        }
                    }
                    if (registers.hTimer == registers.hCounter) {
                        if (registers.irqMode == Registers::HCounterIrq || registers.irqMode == Registers::HAndVCounterIrq && registers.vTimer == registers.vCounter) {
                            irqRequested = true;
                        }
                    }
                }
                ++iteration;
            } catch (Video::MemoryAccessException& e) {
                //cpuState.setProgramAddress(cpuState.getLastKnownAddress());
                cpuContext.setPaused(true);
                error << e.what() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        running = false;
        throw e;
    }
}

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error)
{
    context.addKnownAddress(Long(state.getProgramAddress()));
    try {
        if (context.isPaused()) {
            debugger.printState(state, context);

            if (debugger.awaitCommand(context, state, otherContext, otherState)) {
                int cycles = instruction->execute();
                if (context.isPaused()) {
                    debugger.printRegisters(state, context);
                }
                return cycles;
            }
        }
        else {
            return instruction->execute();
        }
    } catch (OpcodeNotYetImplementedException& e) {
        context.setPaused(true);
        error << e.what() << std::endl;
    } catch (AddressModeNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.setPaused(true);
        error << e.what() << std::endl;
    } catch (OperatorNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.setPaused(true);
        error << e.what() << std::endl;
    } catch (MemoryLocation::AccessException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.setPaused(true);
        error << e.what() << std::endl;
    } catch (MemoryAccessException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.setPaused(true);
        error << e.what() << std::endl;
    } catch (Video::NotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.setPaused(true);
        error << e.what() << std::endl;
    }
    return 0;
}
