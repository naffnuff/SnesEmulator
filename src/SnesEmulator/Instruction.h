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
    virtual uint16_t size() const = 0;

protected:
    virtual std::string operandToString(const State& state) const
    {
        std::ostringstream ss;
        ss << std::hex;
        for (int i = size() - 1; i > 0; --i) {
            ss << std::setw(2) << std::setfill('0') << +state.readProgramByte(i);
        }
        return ss.str();
    }
};

class Instruction1Byte : public Instruction
{
protected:
    virtual int invokeOperator(State& state) const = 0;

    int applyOperand(State& state) const
    {
        state.incrementProgramCounter(size());
        return invokeOperator(state);
    }

    uint16_t size() const override
    {
        return 1;
    }
};

class Instruction2Byte : public Instruction
{
protected:
    virtual int invokeOperator(State& state, uint8_t lowByte) const = 0;

    int applyOperand(State& state) const
    {
        uint8_t lowByte = state.readProgramByte(1);
        state.incrementProgramCounter(size());
        return invokeOperator(state, lowByte);
    }

    uint16_t size() const override
    {
        return 2;
    }
};

class Instruction3Byte : public Instruction
{
protected:
    virtual int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const = 0;

    int applyOperand(State& state) const
    {
        uint8_t lowByte = state.readProgramByte(1);
        uint8_t highByte = state.readProgramByte(2);
        state.incrementProgramCounter(size());
        return invokeOperator(state, lowByte, highByte);
    }

    uint16_t size() const override
    {
        return 3;
    }
};

class Instruction4Byte : public Instruction
{
protected:
    virtual int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte, uint8_t bankByte) const = 0;

    int applyOperand(State& state) const
    {
        uint8_t lowByte = state.readProgramByte(1);
        uint8_t highByte = state.readProgramByte(2);
        uint8_t bankByte = state.readProgramByte(3);
        state.incrementProgramCounter(size());
        return invokeOperator(state, lowByte, highByte, bankByte);
    }

    uint16_t size() const override
    {
        return 4;
    }
};
