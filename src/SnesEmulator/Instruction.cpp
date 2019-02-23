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
    uint8_t operand = state.readOneByteValue();
    state.incrementProgramCounter(2);
    int cycles = calculateCycles(state) + apply(state, operand);
    return cycles;
}

std::string Instruction2Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << "One byte: " << std::setw(2) << std::setfill('0') << +state.readOneByteValue();
    return ss.str();
}

int Instruction3Byte::execute(State& state) const
{
    uint16_t operand = state.readTwoByteValue();
    state.incrementProgramCounter(3);
    int cycles = calculateCycles(state) + apply(state, operand);
    return cycles;
}

std::string Instruction3Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << "Two bytes: " << std::setw(4) << std::setfill('0') << +state.readTwoByteValue();
    return ss.str();
}

int Instruction4Byte::execute(State& state) const
{
    uint32_t operand = state.readThreeByteValue();
    state.incrementProgramCounter(4);
    int cycles = calculateCycles(state) + apply(state, operand);
    return cycles;
}

std::string Instruction4Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << "Three bytes: " << std::setw(6) << std::setfill('0') << +state.readThreeByteValue();
    return ss.str();
}