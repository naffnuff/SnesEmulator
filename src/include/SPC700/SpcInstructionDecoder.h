#pragma once

#include <array>
#include <memory>

#include "System.h"
#include "Instruction.h"
#include "SpcState.h"

namespace SPC {

class InstructionDecoder
{
public:
    SHARED InstructionDecoder(State& state);

    InstructionDecoder(const InstructionDecoder&) = delete;
    InstructionDecoder& operator=(const InstructionDecoder&) = delete;

    Instruction* getNextInstruction(State& state) const
    {
        return instructions[state.inspectProgramByte()].get();
    }

private:
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions;
};

}
