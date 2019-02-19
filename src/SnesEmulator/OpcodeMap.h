#pragma once

#include <array>
#include <memory>

#include "Instruction.h"

class OpcodeMap
{
public:
    OpcodeMap();
    Instruction* getInstruction(uint8_t code) const;
private:
    std::array<std::unique_ptr<Instruction>, 1 << 8> instructions;
};

