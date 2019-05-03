#include "SnesEmulator.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Common/Exception.h"

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error);

void Emulator::initialize()
{
    rom.loadFromFile("../../Legend of Zelda, The - A Link to the Past (U) [!].smc", cpuState);
    //rom.loadFromFile("../../Super Mario World (USA).sfc", cpuState);
    //rom.loadFromFile("../../Super Metroid (Japan, USA) (En,Ja).sfc", cpuState);
    //rom.loadFromFile("../../Super Metroid (JU) [!].smc", cpuState);
    //rom.loadFromFile("../../Megaman X (USA).sfc", cpuState);
    //rom.loadFromFile("../../SnesInitializationROM.smc", cpuState);
    //rom.loadFromFile("../../rom.smc", cpuState);
    //rom.loadFromFile("H:\\naffnuff\\wla\\rom.smc", cpuState);
    //rom.loadFromFile("C:\\cygwin64\\home\\rasmus.knutsson\\wla-dx\\wla\\myrom.smc", cpuState);

    renderer.initialize(rom.gameTitle);

    if (rom.isLowRom()) {
        // RAM
        for (Long address = 0x7E0000; address < 0x800000; address++) {
            cpuState.getMemoryLocation(address)->setReadWrite();
        }
        // RAM mirrors
        for (Byte bank = 0; bank < 0x01/*0x40*/; ++bank) {
            for (Word address = 0; address < 0x2000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setMirror(cpuState.getMemoryLocation(Long(address, 0x7E)), MemoryLocation::ReadWrite);
            }
        }

        // Save RAM
        for (Byte bank = 0x70; bank < 0x71/*0x78*/; ++bank) {
            for (Word address = 0; address < 0x8000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setReadWrite();
                cpuState.getMemoryLocation(Long(address, bank))->setValue(0x00);
            }
        }

        std::function<void(Word address)> setOutputRegister = [this](Word address)
        {
            MemoryLocation* memory = cpuState.getMemoryLocation(Long(address, 0));
            memory->setWriteOnly();
            memory->trap =
                [this, address](MemoryLocation::Operation operation, Byte value) {
                    debugger.printMemoryRegister(operation, value, address);
            };
            registers[address].setMirror(memory, MemoryLocation::ReadOnly);
        };

        // Registers
        setOutputRegister(0x2100);
        setOutputRegister(0x212e);
        setOutputRegister(0x212f);
        setOutputRegister(0x4200);
        setOutputRegister(0x420b);
        setOutputRegister(0x420c);

        // Memory mapping: I/O between the CPU and SPC700
        for (Word i = 0; i < 4; ++i) {
            MemoryLocation* cpuMemoryLocation = cpuState.getMemoryLocation(Long(0x2140 + i));
            MemoryLocation* spcMemoryLocation = spcState.getMemoryLocation(Word(0xf4 + i));
            cpuMemoryLocation->setMapping(spcMemoryLocation);
            spcMemoryLocation->setMapping(cpuMemoryLocation);
        }
    } else {
        throw std::runtime_error("Only the low-rom mempory map is supported for now");
    }

    for (Debugger::Context* context : { &cpuContext, &spcContext }) {
        std::ifstream contextFile(context->fileName);
        if (contextFile) {
            std::string breakpointString;
            while (std::getline(contextFile, breakpointString, ' ')) {
                Long breakpoint = std::stoi(breakpointString, 0, 16);
                output << "Read breakpoint: " << breakpoint << " from " << context->fileName << std::endl;
                context->breakpoints.insert(breakpoint);
            }
        }
    }

    cpuContext.nextInstruction = cpuInstructionDecoder.readNextInstruction(cpuState);
    spcContext.nextInstruction = spcInstructionDecoder.readNextInstruction(spcState);
}

void Emulator::run()
{
    uint64_t nextCpu = 186;
    uint64_t nextSpc = 186;

    int hCounter = 186;
    int vCounter = 0;
    bool vBlank = false;

    std::array<Renderer::Pixel, Renderer::width> scanline;

    bool irq = false;
    bool nmi = false;

    double runStartTime;
    bool stepMode = cpuContext.stepMode || spcContext.stepMode;
    if (!stepMode) {
        debugger.startTime = clock();
        runStartTime = renderer.getTime();
    }

    while (running) {
        if (cycleCount == nextCpu) {

            if (nmi) {
                nmi = false;
                if (registers[0x4200].getValue().getBit(7)) {
                    //cpuState.startNmi();
                }
                nextCpu += 9 * 8; // TODO: check the correct cycles for interrupt
            }

            Instruction* instruction = cpuInstructionDecoder.readNextInstruction(cpuState);
            cpuContext.nextInstruction = instruction;

            if (cpuContext.stepMode) {
                output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                debugger.printBreakpoints(cpuContext, spcContext);
                debugger.printMemory(cpuState, cpuContext, spcState, spcContext);
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
                debugger.printMemory(cpuState, cpuContext, spcState, spcContext);
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
            runStartTime = renderer.getTime();
        }
        else { // run mode continued
            double elapsedTime = renderer.getTime() - runStartTime;
            static const double clockSpeed = 1.89e9 / 88.0;
            uint64_t elapsedCycles = uint64_t(elapsedTime * clockSpeed);
            
            if (elapsedCycles > cycleCount) {
                increment = true;
            }

            static int incrementCount = 0;
            static int totalCount = 0;

            if (increment) {
                ++incrementCount;
            }
            ++totalCount;

            static int nextPrintout = 5;
            double actualSpeed = double(cycleCount) / elapsedTime;
            if (nextPrintout == int(elapsedTime)) {
                nextPrintout += 5;
                output << "Renderer time: " << elapsedTime << std::endl;
                output << "Elapsed cycles: " << elapsedCycles << std::endl;
                output << "Actual cycles: " << cycleCount << std::endl;
                output << "Clock speed: " << clockSpeed << std::endl;
                output << "Actual speed: " << actualSpeed << std::endl;
                output << "ratio: " << actualSpeed / clockSpeed << std::endl;
                output << std::endl;
                output << "increments: " << incrementCount << std::endl;
                output << "total: " << totalCount << std::endl;
                output << "ratio: " << double(incrementCount) / double(totalCount) << std::endl;
                output << std::endl;
                output << "V counter: " << vCounter << std::endl;
                output << "H counter: " << hCounter << std::endl;
                output << std::endl;
            }
        }

        static uint8_t color = 0;
        static bool ascending = true;
        if (increment) {
            ++cycleCount;
            ++hCounter;
            if (hCounter == 1360) {
                hCounter = 0;
                if (vCounter < 224) {
                    for (int i = 0; i < scanline.size(); ++i) {
                        scanline[i] = { color, uint8_t(vCounter), uint8_t(i) };
                    }
                    renderer.setScanline(vCounter, scanline);
                }
                ++vCounter;
                if (vCounter == 224) {
                    vBlank = true;
                    nmi = true;
                    if (ascending) {
                        ++color;
                        if (color == 255) {
                            ascending = false;
                        }
                    } else {
                        --color;
                        if (color == 0) {
                            ascending = true;
                        }
                    }
                }
                else if (vCounter == 262) {
                    vCounter = 0;
                    vBlank = false;
                    renderer.update();
                    if (renderer.pause) {
                        renderer.pause = false;
                        cpuContext.stepMode = true;
                    }
                }
            }
        }
    }
}

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error)
{
    Long lastKnownProgramAddress = state.getProgramAddress();
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
            for (Long i = state.getProgramAddress(); i < state.getProgramAddress() + instruction->size(); ++i) {
                if (context.breakpoints.find(i) != context.breakpoints.end()) {
                    context.stepMode = true;
                    break;
                }
            }

            if (context.stepMode) {
                debugger.printClockSpeed();
            }
            else {
                return instruction->execute();
            }
        }
    } catch (OpcodeNotYetImplementedException& e) {
        error << e.what() << std::endl;
        context.stepMode = true;
    } catch (AddressModeNotYetImplementedException& e) {
        error << e.what() << std::endl;
        state.setProgramAddress(lastKnownProgramAddress);
        context.stepMode = true;
    } catch (OperatorNotYetImplementedException& e) {
        error << e.what() << std::endl;
        state.setProgramAddress(lastKnownProgramAddress);
        context.stepMode = true;
    } catch (MemoryLocation::AccessException& e) {
        error << e.what() << std::endl;
        state.setProgramAddress(lastKnownProgramAddress);
        context.stepMode = true;
    }
    return 0;
}
