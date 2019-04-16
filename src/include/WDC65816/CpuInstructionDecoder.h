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
    SHARED InstructionDecoder(State& state);

    Instruction* readNextInstruction(State& state) const
    {
        Byte opcode = state.applyProgramByte();
        if (state.is16Bit(State::m) && instructions16BitM[opcode]) {
            return instructions16BitM[opcode].get();
        } else if (state.is16Bit(State::x) && instructions16BitX[opcode]) {
            return instructions16BitX[opcode].get();
        } else {
            return instructions[opcode].get();
        }
    }

private:
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions;
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions16BitM;
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions16BitX;
};

}