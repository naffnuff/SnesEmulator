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

class Instruction2Byte : public Instruction
{
public:
    int execute(State& state) const override;
protected:
    virtual int apply(State& state, uint8_t operand) const = 0;
    std::string operandToString(const State& state) const override;
};

class Instruction3Byte : public Instruction
{
public:
    int execute(State& state) const override;
public:
    virtual int apply(State& state, uint16_t operand) const = 0;
    std::string operandToString(const State& state) const override;
};

class Instruction4Byte : public Instruction
{
public:
    int execute(State& state) const override;
protected:
    virtual int apply(State& state, uint32_t operand) const = 0;
    std::string operandToString(const State& state) const override;
};

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
