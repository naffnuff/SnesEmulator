#pragma once

#include <stdint.h>

#include "State.h"

class Instruction
{
public:
    Instruction(const std::string& instructionName, const std::string& instructionDescription, const std::string& addressMode)
        : intructionName(instructionName)
        , instructionDescription(instructionDescription)
        , addressMode(addressMode)
    {
    }

    virtual int execute(State& state) const = 0;
    virtual std::ostream& printNextExecution(std::ostream& output, const State& state) const = 0;

    std::ostream& printInfo(std::ostream& ostream) const;

protected:
    virtual int calculateCycles(const State& state) const = 0;

private:
    const std::string intructionName;
    const std::string instructionDescription;
    const std::string addressMode;
};

class Instruction1Byte : public Instruction
{
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state) const = 0;
};

class Instruction2Byte : public Instruction
{
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint8_t value) const = 0;
};

class Instruction3Byte : public Instruction
{
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint16_t value) const = 0;
};

class Instruction4Byte : public Instruction
{
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint32_t value) const = 0;
};

template<State::Flag Flag>
class InstructionFlagSize : public Instruction
{
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint16_t value) const = 0;
private:
    uint16_t consumeValue(State& state) const;
};

template<State::Flag Flag>
int InstructionFlagSize<Flag>::execute(State& state) const
{
    return calculateCycles(state) + apply(state, consumeValue(state));
}

template<State::Flag Flag>
std::ostream& InstructionFlagSize<Flag>::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << +(state.getFlag(Flag) ? state.readOneByteValue() : state.readTwoByteValue()) << std::dec << std::endl << state << std::endl;
}

template<State::Flag Flag>
uint16_t InstructionFlagSize<Flag>::consumeValue(State& state) const
{
    uint16_t value = 0;
    if (state.getFlag(Flag)) {
        state.readOneByteValue();
        state.incrementProgramCounter(1);
    } else {
        state.readTwoByteValue();
        state.incrementProgramCounter(2);
    }
    return value;
}