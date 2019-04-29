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

        // Registers
        debugger.setRegister(cpuState, 0x2100);
        debugger.setRegister(cpuState, 0x212e);
        debugger.setRegister(cpuState, 0x212f);
        debugger.setRegister(cpuState, 0x4200);
        debugger.setRegister(cpuState, 0x420b);
        debugger.setRegister(cpuState, 0x420c);

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

void Emulator::initializeSPPURegisters(std::map<Word, MemoryLocation>& registers)
{
    registers[0x4200].setMirror(cpuState.getMemoryLocation(0x4200), MemoryLocation::ReadOnly);
}

std::string operationToString(MemoryLocation::Operation operation)
{
    switch (operation) {
    case MemoryLocation::Read:
        return "Read ";
    case MemoryLocation::Write:
        return "Write ";
    case MemoryLocation::Access:
        return "Access ";
    case MemoryLocation::Apply:
        return "Apply ";
    default:
        return "";
    }
};

void Emulator::run()
{
    uint64_t nextCpu = 186;
    uint64_t nextSpc = 186;
    debugger.startTime = clock();

    while (running) {
        if (cycleCount == nextCpu) {

            cpuState.serviceInterrupt();

            Instruction* instruction = cpuInstructionDecoder.readNextInstruction(cpuState);

            if (cpuContext.stepMode) {
                output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                for (const Debugger::Context* context : { &cpuContext, &spcContext }) {
                    if (!context->breakpoints.empty()) {
                        output << "Breakpoints:";
                        for (Long breakpoint : context->breakpoints) {
                            output << " " << breakpoint;
                        }
                        output << std::endl;
                    }
                }
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

            if (spcContext.stepMode) {
                output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                for (const Debugger::Context* context : { &cpuContext, &spcContext }) {
                    if (!context->breakpoints.empty()) {
                        output << "Breakpoints:";
                        for (Long breakpoint : context->breakpoints) {
                            output << " " << breakpoint;
                        }
                        output << std::endl;
                    }
                }
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

        ++cycleCount;
    }

    std::time_t endTime = clock();
    double elapsedSeconds = double(endTime - debugger.startTime) / CLOCKS_PER_SEC;
    output << "Time delta=" << elapsedSeconds << std::endl;
    output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
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

        } else {
            for (Long i = state.getProgramAddress(); i < state.getProgramAddress() + instruction->size(); ++i) {
                if (context.breakpoints.find(i) != context.breakpoints.end()) {
                    context.stepMode = true;
                    break;
                }
            }

            if (context.stepMode) {
                debugger.printClockSpeed();
            } else {
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
