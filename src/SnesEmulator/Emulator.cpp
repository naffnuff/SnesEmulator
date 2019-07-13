#include "Emulator.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Common/Exception.h"

#include "DmaInstruction.h"

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error);

void Emulator::initialize()
{
    //rom.loadFromFile("../../Super Mario World (USA).sfc", cpuState);
    rom.loadFromFile("../../Legend of Zelda, The - A Link to the Past (U) [!].smc", cpuState);
    //rom.loadFromFile("../../Super Metroid (Japan, USA) (En,Ja).sfc", cpuState);
    //rom.loadFromFile("../../Super Metroid (JU) [!].smc", cpuState);
    //rom.loadFromFile("../../Megaman X (USA).sfc", cpuState);

    if (rom.isLowRom()) {
        // RAM
        for (Long address = 0x7E0000; address < 0x800000; address++) {
            cpuState.getMemoryLocation(address)->setReadWrite();
        }
        // RAM mirrors
        for (Byte bank = 0; bank < 0x40; ++bank) {
            for (Word address = 0; address < 0x2000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setMirrorOf(cpuState.getMemoryLocation(Long(address, 0x7E)));
            }
        }

        // ROM mirrors
        for (Long address = 0; address < 0x800000; ++address) {
            cpuState.getMemoryLocation(address + 0x800000)->setMirrorOf(cpuState.getMemoryLocation(address));
        }

        // Save RAM
        for (Byte bank = 0x70; bank < 0x71/*0x78*/; ++bank) {
            for (Word address = 0; address < 0x8000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setReadWrite();
                cpuState.getMemoryLocation(Long(address, bank))->setValue(0x00);
            }
        }

        registers.initialize();

        // Register mirrors
        for (Byte bank = 0x01; bank < 0x40; ++bank) {
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
    Video::OamViewer oamViewer(video);
    //Video::BackgroundViewer background1Viewer(video, Video::BackgroundLayer1);
    Video::BackgroundViewer background2Viewer(video, Video::BackgroundLayer2);
    //Video::BackgroundViewer background3Viewer(video, Video::BackgroundLayer3);
    //Video::BackgroundViewer background4Viewer(video, Video::BackgroundLayer4);
    /*std::thread vramRendererThread(
        [this]() {
            video.vramRenderer.initialize("VRAM viewer");
            while (running) {
                video.vramRenderer.update();
            }
        });
    std::thread cgramRendererThread(
        [this]() {
            video.cgramRenderer.initialize("CGRAM viewer");
            while (running) {
                video.cgramRenderer.update();
            }
        });*/
    /*std::thread bgRendererThread(
        [this]() {
            video.bgRenderer.initialize("Background viewer");
            while (running) {
                video.bgRenderer.update();
            }
        });*/
    /*std::thread rendererThread(
        [this]() {
            video.renderer.initialize("Background viewer");
            while (running) {
                video.renderer.update();
            }
        });*/

    DmaInstruction dmaInstruction(output, error, cpuState);

    uint64_t nextCpu = masterCycle;
    uint64_t nextSpc = masterCycle;
    uint64_t cycleCountTarget = masterCycle;

    uint64_t audioCycle = 0;

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

                if (dmaInstruction.enabled()) { // DMA enabled
                    //cpuContext.stepMode = true;
                    dmaInstruction.blockedInstruction = instruction;
                    instruction = static_cast<Instruction*>(&dmaInstruction);
                }

                cpuContext.nextInstruction = instruction;

                if (cpuContext.stepMode) {
                    output << "Cycle count: " << masterCycle << ", Next cpu: " << nextCpu << ", Next spc: " << nextSpc << std::endl;
                    output << "Frame: " << registers.frame << ", V counter: " << registers.vCounter << ", H counter: " << registers.hCounter << ", V blank: " << registers.vBlank << ", H blank: " << registers.hBlank << ", nmi: " << cpuState.isNmiActive() << ", irq: " << cpuState.isIrqActive() << std::endl;
                    debugger.printBreakpoints(cpuContext, spcContext);
                    debugger.printMemory(cpuState, cpuContext, spcState, spcContext, video);
                }

                if (int cycles = executeNext(instruction, cpuState, debugger, cpuContext, spcState, spcContext, error)) {
                    nextCpu += cycles * 8;
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
                    nextSpc += cycles * 16;
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
                if (iteration % 100 == 0)
                {
                    double elapsedTime = video.renderer.getTime() - runStartTime;
                    static const double clockSpeedTarget = 1.89e9 / 88.0;
                    cycleCountTarget = uint64_t(elapsedTime * clockSpeedTarget);
                }

                if (cycleCountTarget > cycleCountDelta)
                {
                    increment = true;
                }

                increment = true;

                static int incrementCount = 0;
                static int totalCount = 0;

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
                if (registers.hCounter == 1100) {
                    if (registers.vCounter < 224) {
                        video.drawScanline(registers.vCounter);
                    }
                    registers.hBlank = true;
                }
                else if (registers.hCounter == 1364) {
                    registers.hCounter = 0;
                    registers.hBlank = false;
                    ++registers.vCounter;
                    if (registers.vCounterIrqEnabled() && registers.getVTimer() == registers.vCounter) {
                        irqRequested = true;
                    }
                    if (registers.vCounter == 224) {
                        video.renderer.update();

                        registers.controllerPort1Data1.setBit(4, video.renderer.buttonR);
                        registers.controllerPort1Data1.setBit(5, video.renderer.buttonL);
                        registers.controllerPort1Data1.setBit(6, video.renderer.buttonX);
                        registers.controllerPort1Data1.setBit(7, video.renderer.buttonA);
                        registers.controllerPort1Data1.setBit(8, video.renderer.buttonRight);
                        registers.controllerPort1Data1.setBit(9, video.renderer.buttonLeft);
                        registers.controllerPort1Data1.setBit(10, video.renderer.buttonDown);
                        registers.controllerPort1Data1.setBit(11, video.renderer.buttonUp);
                        registers.controllerPort1Data1.setBit(12, video.renderer.buttonStart);
                        registers.controllerPort1Data1.setBit(13, video.renderer.buttonSelect);
                        registers.controllerPort1Data1.setBit(14, video.renderer.buttonY);
                        registers.controllerPort1Data1.setBit(15, video.renderer.buttonB);

                        if (video.renderer.pause) {
                            video.renderer.pause = false;
                            cpuContext.stepMode = true;
                        }
                        registers.vBlank = true;
                        registers.video.oam.address = registers.oamStartAddress;
                        if (registers.nmiEnabled()) {
                            nmiRequested = true;
                        }
                    }
                    else if (registers.vCounter == 262) {
                        ++registers.frame;
                        registers.vCounter = 0;
                        registers.interlaceField = !registers.interlaceField;
                        registers.vBlank = false;
                        oamViewer.update();
                        //background1Viewer.update();
                        background2Viewer.update();
                        //background3Viewer.update();
                        //background4Viewer.update();
                    }
                }
            }
            ++iteration;
        }
    } catch (const std::exception& e) {
        running = false;
        //oamRendererThread.join();
        //vramRendererThread.join();
        //cgramRendererThread.join();
        //bgRendererThread.join();
        throw e;
    }
    //oamRendererThread.join();
    //vramRendererThread.join();
    //cgramRendererThread.join();
    //bgRendererThread.join();
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
        // TODO: really an else here?
        else {
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
