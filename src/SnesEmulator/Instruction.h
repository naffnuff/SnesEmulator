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
    int execute(State& state) const override
    {
        state.incrementProgramCounter(1);
        return calculateCycles(state) + apply(state);
    }

protected:
    virtual int apply(State& state) const = 0;

    std::string operandToString(const State& state) const override
    {
        return "";
    }
};

class Instruction2Byte : public Instruction
{
public:
    int execute(State& state) const override
    {
        uint8_t operand = state.readOneByteValue();
        state.incrementProgramCounter(2);
        return calculateCycles(state) + apply(state, operand);
    }

protected:
    virtual int apply(State& state, uint8_t operand) const = 0;

    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::hex << "One byte: " << std::setw(2) << std::setfill('0') << +state.readOneByteValue();
        return ss.str();
    }
};

class Instruction3Byte : public Instruction
{
public:
    int execute(State& state) const override
    {
        uint16_t operand = state.readTwoByteValue();
        state.incrementProgramCounter(3);
        return calculateCycles(state) + apply(state, operand);
    }

public:
    virtual int apply(State& state, uint16_t operand) const = 0;
    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::hex << "Two bytes: " << std::setw(4) << std::setfill('0') << +state.readTwoByteValue();
        return ss.str();
    }
};

class Instruction4Byte : public Instruction
{
public:
    int execute(State& state) const override
    {
        uint32_t operand = state.readThreeByteValue();
        state.incrementProgramCounter(4);
        int cycles = calculateCycles(state) + apply(state, operand);
        return cycles;
    }

protected:
    virtual int apply(State& state, uint32_t operand) const = 0;

    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::hex << "Three bytes: " << std::setw(6) << std::setfill('0') << +state.readThreeByteValue();
        return ss.str();
    }
};

template<State::Flag Flag>
class InstructionVariableSize : public Instruction
{
public:
    int execute(State& state) const override
    {
        uint16_t operand = 0;
        if (state.is16Bit(Flag)) {
            operand = state.readTwoByteValue();
            state.incrementProgramCounter(3);
        } else {
            operand = state.readOneByteValue();
            state.incrementProgramCounter(2);
        }
        return calculateCycles(state) + apply(state, operand);
    }

protected:
    virtual int apply(State& state, uint16_t operand) const = 0;

    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::hex;
        if (state.is16Bit(Flag)) {
            ss << "Two bytes (variable) " << std::setw(4) << std::setfill('0') << state.readTwoByteValue();
        } else {
            ss << "One byte (variable) " << std::setw(2) << std::setfill('0') << +state.readOneByteValue();
        }
        return ss.str();
    }
};
