#pragma once

#include <ctime>
#include <set>

#include "Common/Instruction.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"

#include "SnesRom.h"
#include "Debugger.h"

class Emulator
{
public:
    Emulator(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
        , debugger(output, input, error, cycleCount)
    {
    }

    void initializeStates(Rom& rom, CPU::State& cpuState, SPC::State& spcState);
    void run();

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;
    uint64_t cycleCount;
    Debugger debugger;
};

