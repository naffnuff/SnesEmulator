#pragma once

#include <stdint.h>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <utility>

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
        InstructionBase<State>::state.incrementProgramCounter();
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
        InstructionBase<State>::state.incrementProgramCounter();
        InstructionBase<State>::state.incrementProgramCounter();
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
        InstructionBase<State>::state.incrementProgramCounter();
        InstructionBase<State>::state.incrementProgramCounter();
        InstructionBase<State>::state.incrementProgramCounter();
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
        InstructionBase<State>::state.incrementProgramCounter();
        InstructionBase<State>::state.incrementProgramCounter();
        InstructionBase<State>::state.incrementProgramCounter();
        InstructionBase<State>::state.incrementProgramCounter();
        return invokeOperator(lowByte, highByte, bankByte);
    }

    uint16_t size() const override
    {
        return 4;
    }
};

template<typename State, typename... Bytes>
class FiniteInstruction : InstructionBase<State>
{
    using InstructionBase<State>::InstructionBase;

protected:
    virtual int invokeOperator(Bytes...) = 0;

    template <typename T> int read(State& state)
    {
        return state.nextProgramByte();
    }

    int applyOperand()
    {
        InstructionBase<State>::state.incrementProgramCounter();
        std::tuple<Bytes...> tuple = std::make_tuple(read<Bytes>(InstructionBase<State>::state)...);
        return std::apply([this](Bytes... bytes) { return this->invokeOperator(bytes...); }, tuple);
    }
};

template<typename State>
class ThreeBytes : FiniteInstruction<State, uint8_t, uint8_t, uint8_t>
{
    using FiniteInstruction<State, uint8_t, uint8_t, uint8_t>::FiniteInstruction;

    int invokeOperator(uint8_t lowByte, uint8_t highByte, uint8_t bankByte) override
    {
        std::cout << +lowByte << ", " << +highByte << ", " << +bankByte << std::endl;
        return 0;
    }

    std::string toString() const
    {
        return "";
    }
    std::string opcodeToString() const
    {
        return "";
    }
public:
    int execute()
    {
        return FiniteInstruction<State, uint8_t, uint8_t, uint8_t>::applyOperand();
    }
    uint16_t size() const
    {
        return 0;
    }
};