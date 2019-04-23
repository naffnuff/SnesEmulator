#include "SnesEmulator.h"

#include <fstream>
#include <iostream>

#include "Common/Exception.h"
#include "SnesRom.h"
#include "Debugger.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"

#include "WDC65816/CpuInstructionDecoder.h"
#include "SPC700/SpcInstructionDecoder.h"

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error);

void Emulator::run()
{
    CPU::State cpuState;

    Rom rom(output);
    rom.loadFromFile("../../Legend of Zelda, The - A Link to the Past (U) [!].smc");
    //rom.loadFromFile("../../Super Mario World (USA).sfc");
    //rom.loadFromFile("../../Super Metroid (Japan, USA) (En,Ja).sfc");
    //rom.loadFromFile("../../Super Metroid (JU) [!].smc");
    //rom.loadFromFile("../../Megaman X (USA).sfc");
    //rom.loadFromFile("../../SnesInitializationROM.smc");
    //rom.loadFromFile("../../rom.smc");
    //rom.loadFromFile("H:\\naffnuff\\wla\\rom.smc");
    //rom.loadFromFile("C:\\cygwin64\\home\\rasmus.knutsson\\wla-dx\\wla\\myrom.smc");
    rom.loadToState(cpuState);
    
    SPC::State spcState;

    // Memory mapping: this is how I/O between the CPU and SPC700 is handled on the SNES
    for (Word i = 0; i < 4; ++i) {
        MemoryLocation* cpuMemoryLocation = cpuState.getMemoryLocation(Long(0x2140 + i));
        MemoryLocation* spcMemoryLocation = spcState.getMemoryLocation(Word(0xf4 + i));
        cpuMemoryLocation->setMapping(spcMemoryLocation);
        spcMemoryLocation->setMapping(cpuMemoryLocation);
    }

    CPU::InstructionDecoder cpuInstructionDecoder(cpuState);
    SPC::InstructionDecoder spcInstructionDecoder(spcState);

    uint64_t cycleCount = 186;
    Debugger debugger(output, input, error, cycleCount);

    Debugger::Context cpuContext("cpu.txt", Debugger::Green, cpuInstructionDecoder.readNextInstruction(cpuState));
    Debugger::Context spcContext("spc.txt", Debugger::Magenta, spcInstructionDecoder.readNextInstruction(spcState));

    const bool resumeLast = true;

    if (resumeLast) {
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
    }

    uint64_t nextCpu = 186;
    uint64_t nextSpc = 186;
    bool running = true;
    debugger.startTime = clock();

    while (running) {
        if (cycleCount == nextCpu) {
            Instruction* instruction = cpuInstructionDecoder.readNextInstruction(cpuState);

            if (cpuContext.stepMode) {
                output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                for (const Debugger::Context& context : { cpuContext, spcContext }) {
                    if (!context.breakpoints.empty()) {
                        output << "Breakpoints:";
                        for (Long breakpoint : context.breakpoints) {
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
                for (const Debugger::Context& context : { cpuContext, spcContext }) {
                    if (!context.breakpoints.empty()) {
                        output << "Breakpoints:";
                        for (Long breakpoint : context.breakpoints) {
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
