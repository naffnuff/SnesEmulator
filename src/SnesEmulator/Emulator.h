#pragma once

#include <ctime>
#include <set>

#include "Instruction.h"

class Emulator
{
public:
    Emulator(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
    {
    }

    void run();
    bool executeNext(Instruction* instruction, const IState& state, uint64_t& nextExecution, uint64_t cycleCount);
    bool awaitCommand();
    void printState(const Instruction* instruction, const IState& state);

private:
    uint32_t inspectedAddress = 0;
    bool watchMode = true;
    bool stepMode = true;
    std::set<uint32_t> breakpoints;
    std::time_t startTime;

    std::ostream& output;
    std::istream& input;
    std::ostream& error;
};

