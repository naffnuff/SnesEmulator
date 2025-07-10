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

    Instruction<State>* getNextInstruction(const State& state) const
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

}