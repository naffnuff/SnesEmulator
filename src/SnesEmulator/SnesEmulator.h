#pragma once

#include <ctime>
#include <set>

#include "Common/Instruction.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"

#include "WDC65816/CpuInstructionDecoder.h"
#include "SPC700/SpcInstructionDecoder.h"

#include "SnesRom.h"
#include "Debugger.h"

class Emulator
{
public:
    Emulator(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
        , debugger(output, input, error, cycleCount, running)
        , rom(output)
        , cpuInstructionDecoder(cpuState)
        , spcInstructionDecoder(spcState)
        , cpuContext("cpu.txt", Debugger::Green)
        , spcContext("spc.txt", Debugger::Magenta)
    {
    }

    void initialize();
    void initializeSPPURegisters(std::map<Word, MemoryLocation>& registers);
    void run();

    void pause()
    {
        cpuContext.stepMode = true;
    }

    void initiateVBlank()
    {
        cpuState.requestInterrupt();
    }

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;

    Debugger debugger;
    Rom rom;
    CPU::State cpuState;
    SPC::State spcState;
    CPU::InstructionDecoder cpuInstructionDecoder;
    SPC::InstructionDecoder spcInstructionDecoder;
    Debugger::Context cpuContext;
    Debugger::Context spcContext;

    bool running = true;
    uint64_t cycleCount = 186;

};

