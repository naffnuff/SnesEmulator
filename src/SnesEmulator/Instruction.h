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
    virtual int getCycleCount(const State& state) const = 0;
};

class Instruction1Byte : public Instruction
{
public:
    int execute(State& state) const override
    {
        state.incrementProgramCounter(1);
        return getCycleCount(state) + invokeOperator(state);
    }

protected:
    virtual int invokeOperator(State& state) const = 0;

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
        uint8_t lowByte = state.readProgramByte(1);
        state.incrementProgramCounter(2);
        return getCycleCount(state) + invokeOperator(state, lowByte);
    }

protected:
    virtual int invokeOperator(State& state, uint8_t lowByte) const = 0;

    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << +state.readProgramByte(1);
        return ss.str();
    }
};

class Instruction3Byte : public Instruction
{
public:
    int execute(State& state) const override
    {
        uint8_t lowByte = state.readProgramByte(1);
        uint8_t highByte = state.readProgramByte(2);
        state.incrementProgramCounter(3);
        return getCycleCount(state) + invokeOperator(state, lowByte, highByte);
    }

protected:
    virtual int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const = 0;

    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << +state.readProgramByte(2)
            << std::setw(2) << std::setfill('0') << +state.readProgramByte(1);
        return ss.str();
    }
};

class Instruction4Byte : public Instruction
{
public:
    int execute(State& state) const override
    {
        uint8_t lowByte = state.readProgramByte(1);
        uint8_t highByte = state.readProgramByte(2);
        uint8_t bankByte = state.readProgramByte(3);
        state.incrementProgramCounter(4);
        int cycles = getCycleCount(state) + invokeOperator(state, lowByte, highByte, bankByte);
        return cycles;
    }

protected:
    virtual int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte, uint8_t bankByte) const = 0;

    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << +state.readProgramByte(3)
            << std::setw(2) << std::setfill('0') << +state.readProgramByte(2)
            << std::setw(2) << std::setfill('0') << +state.readProgramByte(1);
        return ss.str();
    }
};

template<State::Flag Flag>
class InstructionVariableSize : public Instruction
{
public:
    int execute(State& state) const override
    {
        if (state.is16Bit(Flag)) {
            uint8_t lowByte = state.readProgramByte(1);
            uint8_t highByte = state.readProgramByte(2);
            state.incrementProgramCounter(3);
            return getCycleCount(state) + invokeOperator(state, lowByte, highByte);
        } else {
            uint8_t lowByte = state.readProgramByte(1);
            state.incrementProgramCounter(2);
            return getCycleCount(state) + invokeOperator(state, lowByte);
        }
    }

protected:
    virtual int invokeOperator(State& state, uint8_t lowByte) const = 0;
    virtual int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const = 0;

    std::string operandToString(const State& state) const override
    {
        std::ostringstream ss;
        ss << std::hex;
        if (state.is16Bit(Flag)) {
            ss << std::setw(2) << std::setfill('0') << +state.readProgramByte(2)
                << std::setw(2) << std::setfill('0') << +state.readProgramByte(1);
        } else {
            ss << std::setw(2) << std::setfill('0') << +state.readProgramByte(1);
        }
        return ss.str();
    }
};
