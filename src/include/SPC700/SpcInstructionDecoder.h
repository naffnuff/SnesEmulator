#pragma once

#include <array>
#include <memory>

#include "Instruction.h"
#include "SpcState.h"

namespace SPC {

class InstructionDecoder
{
public:
    __declspec(dllexport) InstructionDecoder(State& state);

    Instruction* readNextInstruction(State& state) const
    {
        return instructions[state.applyProgramByte()].get();
    }

private:
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions;
};

}
