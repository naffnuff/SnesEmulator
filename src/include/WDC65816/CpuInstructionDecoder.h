#pragma once

#include <array>
#include <memory>

#include "System.h"
#include "Instruction.h"
#include "CpuState.h"

namespace CPU {

class InstructionDecoder
{
public:
    SHARED InstructionDecoder() {}

    InstructionDecoder(const InstructionDecoder&) = delete;
    InstructionDecoder& operator=(const InstructionDecoder&) = delete;

    Instruction<State>* getNextInstruction(State& state) const
    {
        return getInstruction(state.inspectProgramByte());
    }

    Instruction<State>* getInstruction(Byte opcode) const
    {
        return instructions[opcode];
    }

private:
    static std::array<Instruction<State>*, Byte::spaceSize> instructions;
};

// Alternative 1: lookup struct

struct InstructionInfo
{
    int (*execute)(State& state) = nullptr;
    const char* (*opcodeToString)() = nullptr;
    std::string(*toString)(const State& state) = nullptr;
    void (*applyBreakpoints)(const State& state) = nullptr;
};

}