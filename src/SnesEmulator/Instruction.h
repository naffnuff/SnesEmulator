#pragma once

#include <stdint.h>
#include <sstream>
#include <iomanip>

#include "IState.h"

class Instruction
{
public:
    virtual std::string toString() const = 0;
    virtual std::string opcodeToString() const = 0;
    virtual int execute() = 0;
    virtual uint16_t size() const = 0;
};

template<typename State>
class InstructionBase : public Instruction
{
public:
    InstructionBase(State& state)
        : state(state)
    {
    }

protected:
    std::string operandToString() const
    {
        std::ostringstream ss;
        ss << std::hex;
        for (int i = size() - 1; i > 0; --i) {
            ss << std::setw(2) << std::setfill('0') << +state.readProgramByte(i);
        }
        return ss.str();
    }

    State& state;
};

template<typename State>
class Instruction1Byte : public InstructionBase<State>
{
    using InstructionBase<State>::InstructionBase;

protected:
    virtual int invokeOperator() = 0;

    int applyOperand()
    {
        InstructionBase<State>::state.incrementProgramCounter(size());
        return invokeOperator();
    }

    uint16_t size() const override
    {
        return 1;
    }
};

template<typename State>
class Instruction2Byte : public InstructionBase<State>
{
    using InstructionBase<State>::InstructionBase;

protected:
    virtual int invokeOperator(uint8_t lowByte) = 0;

    int applyOperand()
    {
        uint8_t lowByte = InstructionBase<State>::state.readProgramByte(1);
        InstructionBase<State>::state.incrementProgramCounter(size());
        return invokeOperator(lowByte);
    }

    uint16_t size() const override
    {
        return 2;
    }
};

template<typename State>
class Instruction3Byte : public InstructionBase<State>
{
    using InstructionBase<State>::InstructionBase;

protected:
    virtual int invokeOperator(uint8_t lowByte, uint8_t highByte) = 0;

    int applyOperand()
    {
        uint8_t lowByte = InstructionBase<State>::state.readProgramByte(1);
        uint8_t highByte = InstructionBase<State>::state.readProgramByte(2);
        InstructionBase<State>::state.incrementProgramCounter(size());
        return invokeOperator(lowByte, highByte);
    }

    uint16_t size() const override
    {
        return 3;
    }
};

template<typename State>
class Instruction4Byte : public InstructionBase<State>
{
    using InstructionBase<State>::InstructionBase;

protected:
    virtual int invokeOperator(uint8_t lowByte, uint8_t highByte, uint8_t bankByte) = 0;

    int applyOperand()
    {
        uint8_t lowByte = InstructionBase<State>::state.readProgramByte(1);
        uint8_t highByte = InstructionBase<State>::state.readProgramByte(2);
        uint8_t bankByte = InstructionBase<State>::state.readProgramByte(3);
        InstructionBase<State>::state.incrementProgramCounter(size());
        return invokeOperator(lowByte, highByte, bankByte);
    }

    uint16_t size() const override
    {
        return 4;
    }
};