#pragma once

#include <stdint.h>

#include "State.h"

class Instruction {
public:
    Instruction(const std::string& debugName, const std::string& debugDescription)
        : debugName(debugName)
        , debugDescription(debugDescription)
    {
    }

    virtual int execute(State& state) const = 0;
    virtual std::ostream& printNextExecution(std::ostream& output, const State& state) const = 0;

    std::ostream& printInfo(std::ostream& ostream) const;

private:
    const std::string debugName;
    const std::string debugDescription;
};

class Instruction1Byte : public Instruction {
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state) const = 0;
};

class Instruction2Byte : public Instruction {
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint8_t value) const = 0;
};

class Instruction3Byte : public Instruction {
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint16_t value) const = 0;
};

class Instruction4Byte : public Instruction {
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint32_t value) const = 0;
};

template<State::Flag FLAG>
class InstructionFlagSize : public Instruction
{
    using Instruction::Instruction;

public:
    int execute(State& state) const override;
    std::ostream& printNextExecution(std::ostream& output, const State& state) const override;

protected:
    virtual int apply(State& state, uint16_t value) const = 0;
private:
    uint16_t readValue(State& state) const;
};

template<State::Flag FLAG>
int InstructionFlagSize<FLAG>::execute(State& state) const
{
    int cycles = apply(state, state.readOneByteValue());
    state.incrementProgramCounter(state.getFlag(FLAG) ? 1 : 2);
    return cycles;
}

template<State::Flag FLAG>
std::ostream& InstructionFlagSize<FLAG>::printNextExecution(std::ostream& output, const State& state) const
{
    return printInfo(output) << std::hex << (state.getFlag(FLAG) ? state.readOneByteValue() : state.readTwoByteValue()) << std::dec << std::endl;
}

template<State::Flag FLAG>
uint16_t InstructionFlagSize<FLAG>::readValue(State& state) const
{
    return state.getFlag(FLAG) ? state.readOneByteValue() : state.readTwoByteValue();
}