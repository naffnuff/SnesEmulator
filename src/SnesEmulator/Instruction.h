#pragma once

#include <stdint.h>
#include <sstream>

#include "State.h"

class Instruction
{
public:
    virtual std::string toString(const State& state) const = 0;
    virtual std::string opcodeToString() const = 0;
    virtual int execute(State& state) const = 0;
protected:
    virtual std::string operandToString(const State& state) const = 0;
    virtual int calculateCycles(const State& state) const = 0;
};

class Instruction1Byte : public Instruction
{
public:
    int execute(State& state) const override;
protected:
    virtual int apply(State& state) const = 0;
    std::string operandToString(const State& state) const override;
};

inline int Instruction1Byte::execute(State& state) const
{
    state.incrementProgramCounter(1);
    return calculateCycles(state) + apply(state);
}

inline std::string Instruction1Byte::operandToString(const State& state) const
{
    return "";
}

class Instruction2Byte : public Instruction
{
public:
    int execute(State& state) const override;
protected:
    virtual int apply(State& state, uint8_t operand) const = 0;
    std::string operandToString(const State& state) const override;
};

inline int Instruction2Byte::execute(State& state) const
{
    uint8_t operand = state.readOneByteValue();
    state.incrementProgramCounter(2);
    return calculateCycles(state) + apply(state, operand);
}

inline std::string Instruction2Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << "One byte: " << std::setw(2) << std::setfill('0') << +state.readOneByteValue();
    return ss.str();
}

class Instruction3Byte : public Instruction
{
public:
    int execute(State& state) const override;
public:
    virtual int apply(State& state, uint16_t operand) const = 0;
    std::string operandToString(const State& state) const override;
};

inline int Instruction3Byte::execute(State& state) const
{
    uint16_t operand = state.readTwoByteValue();
    state.incrementProgramCounter(3);
    return calculateCycles(state) + apply(state, operand);
}

inline std::string Instruction3Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << "Two bytes: " << std::setw(4) << std::setfill('0') << +state.readTwoByteValue();
    return ss.str();
}

class Instruction4Byte : public Instruction
{
public:
    int execute(State& state) const override;
protected:
    virtual int apply(State& state, uint32_t operand) const = 0;
    std::string operandToString(const State& state) const override;
};

inline int Instruction4Byte::execute(State& state) const
{
    uint32_t operand = state.readThreeByteValue();
    state.incrementProgramCounter(4);
    int cycles = calculateCycles(state) + apply(state, operand);
    return cycles;
}

inline std::string Instruction4Byte::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex << "Three bytes: " << std::setw(6) << std::setfill('0') << +state.readThreeByteValue();
    return ss.str();
}

template<State::Flag Flag>
class InstructionFlagSize : public Instruction
{
public:
    int execute(State& state) const override;
protected:
    virtual int apply(State& state, uint16_t operand) const = 0;
    std::string operandToString(const State& state) const override;
};

template<State::Flag Flag>
int InstructionFlagSize<Flag>::execute(State& state) const
{
    uint16_t operand = 0;
    if (state.isEmulationMode() || state.getFlag(Flag)) {
        operand = state.readOneByteValue();
        state.incrementProgramCounter(2);
    } else {
        operand = state.readTwoByteValue();
        state.incrementProgramCounter(3);
    }
    return calculateCycles(state) + apply(state, operand);
}

template<State::Flag Flag>
std::string InstructionFlagSize<Flag>::operandToString(const State& state) const
{
    std::ostringstream ss;
    ss << std::hex;
    if (state.isEmulationMode() || state.getFlag(Flag)) {
        ss << "One byte (variable) " << std::setw(2) << std::setfill('0') << +state.readOneByteValue();
    } else {
        ss << "Two bytes (variable) " << std::setw(4) << std::setfill('0') << state.readTwoByteValue();
    }
    return ss.str();
}
