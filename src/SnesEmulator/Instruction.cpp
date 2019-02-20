#include "Instruction.h"

#include <sstream>

int Instruction1Byte::execute(State& state) const
{
    int cycles = calculateCycles(state) + apply(state);
    state.incrementProgramCounter(1);
    return cycles;
}

std::string Instruction1Byte::operandToString(const State& state) const
{
    return "";
}

int Instruction2Byte::execute(State& state) const
{
    uint8_t value = state.readOneByteValue();
    state.incrementProgramCounter(2);
    int cycles = calculateCycles(state) + apply(state, value);
    return cycles;
}

std::string Instruction2Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << +state.readOneByteValue();
    return ss.str();
}

int Instruction3Byte::execute(State& state) const
{
    uint16_t value = state.readTwoByteValue();
    state.incrementProgramCounter(3);
    int cycles = calculateCycles(state) + apply(state, value);
    return cycles;
}

std::string Instruction3Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << +state.readTwoByteValue();
    return ss.str();
}

int Instruction4Byte::execute(State& state) const
{
    uint32_t value = state.readThreeByteValue();
    state.incrementProgramCounter(4);
    int cycles = calculateCycles(state) + apply(state, value);
    return cycles;
}

std::string Instruction4Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << +state.readThreeByteValue();
    return ss.str();
}