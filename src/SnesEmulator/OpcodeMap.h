#pragma once

#include <array>
#include <memory>

#include "Instruction.h"
#include "State.h"

namespace CPU {

class OpcodeMap
{
public:
    OpcodeMap(State& state);
    Instruction* getNextInstruction(const State& state) const;

private:
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions;
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions16BitM;
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions16BitX;
};

}