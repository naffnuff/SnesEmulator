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
    rom.loadFromFile("../../Super Mario World (USA).sfc", cpuState);
    //rom.loadFromFile("../../Legend of Zelda, The - A Link to the Past (U) [!].smc", cpuState);
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
            for (Word address = 0x2000; address < 0x6000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setMirrorOf(cpuState.getMemoryLocation(Long(address, 0x00)));
            }
        }

        // I/O between the CPU and SPC700
        for (Word i = 0; i < 4; ++i) {
            MemoryLocation* cpuMemoryLocation = cpuState.getMemoryLocation(Long(0x2140 + i));
            MemoryLocation* spcMemoryLocation = spcState.getMemoryLocation(Word(0xf4 + i));
            cpuMemoryLocation->setMappings(nullptr, spcMemoryLocation, MemoryLocation::ReadWrite);
            spcMemoryLocation->setMappings(nullptr, cpuMemoryLocation, MemoryLocation::ReadWrite);
        }
    } else {
        throw std::runtime_error("Only the low-rom mempory map is supported for now");
    }

    video.initialize(rom.gameTitle);

    debugger.loadBreakpoints(cpuContext, cpuState);
    debugger.loadBreakpoints(spcContext, spcState);

    cpuContext.nextInstruction = cpuInstructionDecoder.readNextInstruction(cpuState);
    spcContext.nextInstruction = spcInstructionDecoder.readNextInstruction(spcState);
}

void Emulator::run()
{
    /*std::thread oamRendererThread(
        [this]() {
            video.oamRenderer.initialize("OAM viewer");
            while (running) {
                video.oamRenderer.update();
            }
        });
    std::thread vramRendererThread(
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

    DmaInstruction dmaInstruction(registers.registerBus, cpuState.accessMemory(), output, error);

    uint64_t nextCpu = cycleCount;
    uint64_t nextSpc = cycleCount;
    uint64_t cycleCountTarget = cycleCount;

    int hCounter = int(cycleCount);
    int vCounter = 0;
    int frame = 0;

    std::vector<Renderer::Pixel> scanline(256);

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

            if (cycleCount == nextCpu) {

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
                    output << "Cycle count: " << cycleCount << ", Next cpu: " << nextCpu << ", Next spc: " << nextSpc << std::endl;
                    output << "Frame: " << frame << ", V counter: " << vCounter << ", H counter: " << hCounter << ", V blank: " << registers.vBlank << ", H blank: " << registers.hBlank << ", nmi: " << cpuState.isNmiActive() << ", irq: " << cpuState.isIrqActive() << std::endl;
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

            if (cycleCount == nextSpc) {
                Instruction* instruction = spcInstructionDecoder.readNextInstruction(spcState);
                spcContext.nextInstruction = instruction;

                if (spcContext.stepMode) {
                    output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
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

                //increment = true;

                static int incrementCount = 0;
                static int totalCount = 0;

                if (increment) {
                    ++incrementCount;
                    ++cycleCountDelta;
                }
                ++totalCount;
            }

            if (increment) {
                ++cycleCount;
                ++hCounter;
                if (hCounter == 1100) {
                    if (vCounter < 224) {
                        video.drawScanline(vCounter);
                    }
                    registers.hBlank = true;
                }
                else if (hCounter == 1364) {
                    hCounter = 0;
                    registers.hBlank = false;
                    ++vCounter;
                    if (registers.vCounterIrqEnabled() && registers.getVTimer() == vCounter) {
                        irqRequested = true;
                    }
                    if (vCounter == 224) {
                        video.renderer.update();
                        if (video.renderer.pause) {
                            video.renderer.pause = false;
                            cpuContext.stepMode = true;
                        }
                        registers.vBlank = true;
                        if (registers.nmiEnabled()) {
                            nmiRequested = true;
                        }
                    }
                    else if (vCounter == 262) {
                        ++frame;
                        vCounter = 0;
                        registers.vBlank = false;
                        video.drawDebugInfo();
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
        throw e;
    }
    //oamRendererThread.join();
    //vramRendererThread.join();
    //cgramRendererThread.join();
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
            /*for (Long i = state.getProgramAddress(); i < state.getProgramAddress() + instruction->size(); ++i) {
                if (context.breakpoints.find(i) != context.breakpoints.end()) {
                    context.stepMode = true;
                    break;
                }
            }*/

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
        context.printAddressHistory(error);
        error << e.what() << std::endl;
    } catch (AddressModeNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.stepMode = true;
        context.printAddressHistory(error);
        error << e.what() << std::endl;
    } catch (OperatorNotYetImplementedException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.stepMode = true;
        context.printAddressHistory(error);
        error << e.what() << std::endl;
    } catch (MemoryLocation::AccessException& e) {
        state.setProgramAddress(context.getLastKnownAddress());
        context.stepMode = true;
        context.printAddressHistory(error);
        error << e.what() << std::endl;
    }
    return 0;
}
