#pragma once

#include <ctime>
#include <set>

#include "OpcodeMap.h"
#include "State.h"

class Emulator
{
public:
    void run(std::ostream& output, std::istream& input, std::ostream& error);
    bool awaitCommand(std::ostream& output, std::istream& input, std::ostream& error);
    void printState(std::ostream& output, std::istream& input, std::ostream& error, const Instruction* instruction);

private:
    CPU::State state;

    uint32_t inspectedAddress = 0;
    bool showMemory = true;
    bool showRegisters = true;
    bool watchMode = true;
    bool stepMode = true;
    std::set<uint32_t> breakpoints;
    std::time_t startTime;
};

