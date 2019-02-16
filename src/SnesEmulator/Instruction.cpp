#include "Instruction.h"

#include <string>

std::ostream& Instruction::printInfo(std::ostream& output) const
{
    return output << debugName << std::endl << debugDescription << std::endl;
}


int Instruction1Byte::execute(State& state) const
{
    int cycles = calculateCycles(state) + apply(state);
    state.incrementProgramCounter(1);
    return cycles;
}

std::ostream& Instruction1Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << state << std::endl;
}

int Instruction2Byte::execute(State& state) const
{
    uint8_t value = state.readOneByteValue();
    state.incrementProgramCounter(2);
    int cycles = calculateCycles(state) + apply(state, value);
    return cycles;
}

std::ostream& Instruction2Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << state.readOneByteValue() << std::dec << std::endl << state << std::endl;
}

int Instruction3Byte::execute(State& state) const
{
    uint16_t value = state.readTwoByteValue();
    state.incrementProgramCounter(3);
    int cycles = calculateCycles(state) + apply(state, value);
    return cycles;
}

std::ostream& Instruction3Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << state.readTwoByteValue() << std::dec << std::endl << state << std::endl;
}

int Instruction4Byte::execute(State& state) const
{
    uint32_t value = state.readThreeByteValue();
    state.incrementProgramCounter(4);
    int cycles = calculateCycles(state) + apply(state, value);
    return cycles;
}

std::ostream& Instruction4Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << state.readThreeByteValue() << std::dec << std::endl << state << std::endl;
}