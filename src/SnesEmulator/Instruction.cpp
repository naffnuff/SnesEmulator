#include "Instruction.h"

#include <string>

std::ostream& Instruction::printInfo(std::ostream& output) const
{
    return output << debugName << std::endl << debugDescription << std::endl;
}


int Instruction1Byte::execute(State& state) const
{
    int cycles = apply(state);
    state.incrementProgramCounter(1);
    return cycles;
}

std::ostream& Instruction1Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output);
}

int Instruction2Byte::execute(State& state) const
{
    int cycles = apply(state, state.readOneByteValue());
    state.incrementProgramCounter(2);
    return cycles;
}

std::ostream& Instruction2Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << state.readOneByteValue() << std::dec << std::endl;
}

int Instruction3Byte::execute(State& state) const
{
    int cycles = apply(state, state.readTwoByteValue());
    state.incrementProgramCounter(3);
    return cycles;
}

std::ostream& Instruction3Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << state.readTwoByteValue() << std::dec << std::endl;
}

int Instruction4Byte::execute(State& state) const
{
    int cycles = apply(state, state.readThreeByteValue());
    state.incrementProgramCounter(4);
    return cycles;
}

std::ostream& Instruction4Byte::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << state.readThreeByteValue() << std::dec << std::endl;
}