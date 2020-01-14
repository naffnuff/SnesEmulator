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

    InstructionDecoder(const InstructionDecoder&) = delete;
    InstructionDecoder& operator=(const InstructionDecoder&) = delete;

    Instruction* getNextInstruction(State& state) const
    {
        return getInstruction(state, state.inspectProgramByte());
    }

    Instruction* getInstruction(const State& state, Byte opcode) const
    {
        if (state.is16Bit(State::m) && instructions16BitM[opcode]) {
            return instructions16BitM[opcode].get();
        }
        else if (state.is16Bit(State::x) && instructions16BitX[opcode]) {
            return instructions16BitX[opcode].get();
        }
        else {
            return instructions[opcode].get();
        }
    }

private:
    std::array<std::unique_ptr<Instruction>, Byte::spaceSize> instructions;
    std::array<std::unique_ptr<Instruction>, Byte::spaceSize> instructions16BitM;
    std::array<std::unique_ptr<Instruction>, Byte::spaceSize> instructions16BitX;
};

}