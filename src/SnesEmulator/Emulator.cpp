#include "Emulator.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Common/Exception.h"

#include "VideoDebugger.h"

#include "DmaInstruction.h"
#include "HdmaInstruction.h"

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error);

void Emulator::initialize()
{
    rom.storeToMemory(cpuState);

    if (rom.isLowRom()) {
        // RAM
        for (Long address = 0x7e0000; address < 0x800000; address++) {
            cpuState.getMemoryLocation(address)->setReadWrite();
        }
        // RAM mirrors
        for (Byte bank = 0; bank < 0x40; ++bank) {
            for (Word address = 0; address < 0x2000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setMirrorOf(cpuState.getMemoryLocation(Long(address, 0x7E)));
            }
        }

        // ROM mirrors
        for (Long address = 0; address < 0x600000; ++address) {
            cpuState.getMemoryLocation(address + 0x800000)->setMirrorOf(cpuState.getMemoryLocation(address));
        }

        // Save RAM
        {
            std::ifstream file(rom.gameTitle + ".save");
            file >> std::hex;
            Long saveRamAddress = 0x700000;
            for (Long address = saveRamAddress; address < 0x7e0000; ++address, ++saveRamAddress) {
                if (saveRamAddress == 0x700000 + rom.saveRamSize) {
                    saveRamAddress = 0x700000;
                }
                MemoryLocation* saveRamLocation = cpuState.getMemoryLocation(saveRamAddress);
                if (address == saveRamAddress) {
                    Byte byte;
                    int inputValue;
                    if (file >> inputValue) {
                        byte = inputValue;
                    }
                    saveRamLocation->setReadWrite();
                    saveRamLocation->setValue(byte);
                    saveRamLocation->onWrite = [this](Byte oldValue, Byte& newValue) {
                        if (newValue != oldValue) {
                            std::lock_guard<std::mutex> lock(saveRamSaver.mutex);
                            saveRamSaver.saveRamModified = true;
                        }
                        saveRamSaver.condition.notify_one();
                    };
                }
                else {
                    cpuState.getMemoryLocation(address)->setMirrorOf(saveRamLocation);
                }
            }
            output << "Save RAM end address: " << saveRamAddress << std::endl;
        }

        saveRamSaverThread = std::thread(std::ref(saveRamSaver));

        registers.initialize();

        // Register mirrors
        for (Byte bank = 0x01; bank < 0x60; ++bank) {
            for (Word address = 0x2000; address < 0x8000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setMirrorOf(cpuState.getMemoryLocation(Long(address, 0x00)));
            }
        }
    }
    else {
        throw std::runtime_error("Only the low-rom mempory map is supported for now");
    }

    video.initialize(rom.gameTitle);

    std::array<MemoryLocation*, 4> cpuToSpcPorts;
    // I/O between the CPU and SPC700
    for (Word i = 0; i < 4; ++i) {
        MemoryLocation* cpuMemoryLocation = cpuState.getMemoryLocation(Long(0x2140 + i));
        cpuToSpcPorts[i] = cpuMemoryLocation;
        MemoryLocation* spcMemoryLocation = spcState.getMemoryLocation(Word(0xf4 + i));
        cpuMemoryLocation->setMappings(nullptr, spcMemoryLocation, MemoryLocation::ReadWrite);
        spcMemoryLocation->setMappings(nullptr, cpuMemoryLocation, MemoryLocation::ReadWrite);
    }

    audio.initialize(cpuToSpcPorts);

    debugger.loadBreakpoints(cpuContext, cpuState);
    debugger.loadBreakpoints(spcContext, spcState);

    cpuContext.nextInstruction = cpuInstructionDecoder.readNextInstruction(cpuState);
    spcContext.nextInstruction = spcInstructionDecoder.readNextInstruction(spcState);
}

void Emulator::run()
{
    OamViewer oamViewer(video, 1080, 760);
    BackgroundViewer background1Viewer(video, BackgroundLayer1, 0, 10);
    BackgroundViewer background2Viewer(video, BackgroundLayer2, Video::rendererWidth * 2 + 20, 10);
    BackgroundViewer background3Viewer(video, BackgroundLayer3, 0, Video::rendererWidth * 2 + 20);
    //BackgroundViewer background4Viewer(video, BackgroundLayer4, Video::rendererWidth * 2, Video::rendererWidth * 2 + 20);
    SpriteLayerViewer spriteLayer1Viewer(video, 0, Video::rendererWidth * 2 + 20, Video::rendererWidth * 2 + 40);
    SpriteLayerViewer spriteLayer2Viewer(video, 1, Video::rendererWidth * 2 + 20 + Video::rendererWidth + 20, Video::rendererWidth * 2 + 40);
    SpriteLayerViewer spriteLayer3Viewer(video, 2, Video::rendererWidth * 2 + 20, Video::rendererWidth * 2 + 40 + Video::rendererWidth);
    SpriteLayerViewer spriteLayer4Viewer(video, 3, Video::rendererWidth * 2 + 20 + Video::rendererWidth + 20, Video::rendererWidth * 2 + 40 + Video::rendererWidth);
    Mode7Viewer mode7Viewer(video, 0, 40);

    DmaInstruction dmaInstruction(output, error, cpuState);
    HdmaInstruction hdmaInstruction(output, error, cpuState);

    uint64_t nextCpu = masterCycle;
    uint64_t nextSpc = masterCycle;
    uint64_t cycleCountTarget = masterCycle;

    uint64_t audioCycle = 0;

    int incrementCount = 0;
    int totalCount = 0;

    registers.hCounter = int(masterCycle);

    bool nmiRequested = false;
    bool irqRequested = false;

    double runStartTime = 0.0;
    uint64_t cycleCountDelta = 0;
    bool stepMode = cpuContext.stepMode || spcContext.stepMode;
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

                Instruction* instruction = cpuInstructionDecoder.readNextInstruction(cpuState);

                bool dmaPicked = false;
                if (dmaInstruction.enabled()) {
                    //cpuContext.stepMode = true;
                    dmaInstruction.blockedInstruction = instruction;
                    instruction = static_cast<Instruction*>(&dmaInstruction);
                    dmaPicked = true;
                    if (!registers.vBlank) {
                        //output << "DMA not during V blank" << std::endl;
                        //cpuContext.stepMode = true;
                    }
                }

                if (hdmaInstruction.active) {
                    //cpuContext.stepMode = true;
                    hdmaInstruction.blockedInstruction = instruction;
                    instruction = static_cast<Instruction*>(&hdmaInstruction);
                    if (dmaPicked) {
                        output << "HDMA interrupts DMA" << std::endl;
                        cpuContext.stepMode = true;
                    }
                }

                cpuContext.nextInstruction = instruction;

                if (cpuContext.stepMode) {
                    output << "Cycle count: " << masterCycle << ", Next cpu: " << nextCpu << ", Next spc: " << nextSpc << std::endl;
                    output << "Frame: " << registers.frame << ", V counter: " << registers.vCounter << ", H counter: " << registers.hCounter << ", V blank: " << registers.vBlank << ", H blank: " << registers.hBlank << ", nmi: " << cpuState.isNmiActive() << ", irq: " << cpuState.isIrqActive() << std::endl;
                    debugger.printBreakpoints(cpuContext, spcContext);
                    debugger.printMemory(cpuState, cpuContext, spcState, spcContext, video);
                }

                if (int cycles = executeNext(instruction, cpuState, debugger, cpuContext, spcState, spcContext, error)) {
                    nextCpu += uint64_t(cycles) * 8;
                    cpuContext.nextInstruction = cpuInstructionDecoder.readNextInstruction(cpuState);
                }
                else {
                    continue;
                }
            }

            if (masterCycle == nextSpc) {
                Instruction* instruction = spcInstructionDecoder.readNextInstruction(spcState);
                spcContext.nextInstruction = instruction;

                if (spcContext.stepMode) {
                    output << "cycleCount=" << masterCycle << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                    debugger.printBreakpoints(cpuContext, spcContext);
                    debugger.printMemory(cpuState, cpuContext, spcState, spcContext, video);
                }

                if (int cycles = executeNext(instruction, spcState, debugger, spcContext, cpuState, cpuContext, error)) {
                    nextSpc += uint64_t(cycles) * 16;
                    spcContext.nextInstruction = spcInstructionDecoder.readNextInstruction(spcState);
                }
                else {
                    continue;
                }
            }

            bool increment = false;
            if (cpuContext.stepMode || spcContext.stepMode) { // step mode
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

                //increment = true;

                if (increment) {
                    ++incrementCount;
                    ++cycleCountDelta;
                }
                ++totalCount;
            }

            if (increment) {
                ++masterCycle;
                if (masterCycle % 21 == 0) {
                    audio.tick();
                }
                ++registers.hCounter;
                if (registers.hCounter == 274) {
                    if (registers.vCounter <= 224 && registers.vCounter > 0) {
                        video.drawScanline(registers.vCounter);
                        if (hdmaInstruction.enabled()) {
                            hdmaInstruction.active = true;
                        }
                    }
                    if (registers.vCounter == 224) {
                        static double previousTime = glfwGetTime();
                        static int frameCount = 0;

                        double currentTime = glfwGetTime();
                        frameCount++;
                        if (currentTime - previousTime >= 1.0) {
                            output << "E: " << frameCount << std::endl;

                            frameCount = 0;
                            previousTime = currentTime;
                        }

                        //video.renderer.update();
                        rendererLock.unlock();

                        oamViewer.update();
                        background1Viewer.update();
                        background2Viewer.update();
                        background3Viewer.update();
                        //background4Viewer.update();
                        spriteLayer1Viewer.update();
                        spriteLayer2Viewer.update();
                        spriteLayer3Viewer.update();
                        spriteLayer4Viewer.update();
                        mode7Viewer.update();

                        if (video.renderer.pause) {
                            video.renderer.pause = false;
                            cpuContext.stepMode = true;
                        }
                    }
                    registers.hBlank = true;
                }
                else if (registers.hCounter == 1374) {
                    registers.hCounter = 0;
                    registers.hBlank = false;
                    ++registers.vCounter;
                    if (registers.vCounterIrqEnabled() && registers.getVTimer() == registers.vCounter) {
                        irqRequested = true;
                    }
                    if (registers.vCounter == 225) {
                        hdmaInstruction.active = false;
                        registers.vBlank = true;
                        registers.video.oam.address = registers.oamStartAddress;
                        //registers.video.vram.address = registers.vramStartAddress;
                        if (registers.nmiEnabled()) {
                            nmiRequested = true;
                        }
                    }
                    else if (registers.vCounter == 227) {
                        registers.readControllers();
                    }
                    else if (registers.vCounter == 262) {
                        rendererLock.lock();

                        ++registers.frame;
                        registers.vCounter = 0;
                        registers.interlaceField = !registers.interlaceField;
                        registers.vBlank = false;

                        if (hdmaInstruction.enabled()) {
                            hdmaInstruction.initialize = true;
                            hdmaInstruction.active = true;
                        }
                    }
                }
            }
            ++iteration;
        }
    } catch (const std::exception& e) {
        running = false;
        throw e;
    }
}

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error)
{
    context.addKnownAddress(state.getProgramAddress());
    try {
        if (context.stepMode) {
            debugger.printState(state, context);

            if (debugger.awaitCommand(context, state, otherContext, otherState)) {
                int cycles = instruction->execute();
                if (context.stepMode) {
                    debugger.printRegisters(state, context);
                }
                return cycles;
            }
        }
        else {
            // TODO: this seems not reachable
            if (context.stepMode) {
                debugger.printClockSpeed();
                context.printAddressHistory(error);
            }
            else {
                return instruction->execute();
            }
        }
    } catch (OpcodeNotYetImplementedException& e) {
        context.stepMode = true;
        error << e.what() << std::endl;
    } catch (AddressModeNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.stepMode = true;
        error << e.what() << std::endl;
    } catch (OperatorNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.stepMode = true;
        error << e.what() << std::endl;
    } catch (MemoryLocation::AccessException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.stepMode = true;
        error << e.what() << std::endl;
    } catch (Video::NotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.stepMode = true;
        error << e.what() << std::endl;
    }
    return 0;
}
