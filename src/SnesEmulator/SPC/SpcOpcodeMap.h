#pragma once

#include <array>
#include <memory>

#include "../Instruction.h"
#include "SpcState.h"

namespace SPC {

class OpcodeMap
{
public:
    OpcodeMap(State& state);
    Instruction* getNextInstruction(State& state) const;

private:
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions;
};

}
