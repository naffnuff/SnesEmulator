#include "SpcOpcodeMap.h"

#include <stdint.h>

#include "SpcOpcode.h"
#include "SpcState.h"

namespace SPC {

Instruction* OpcodeMap::getNextInstruction(const State& state) const
{
    uint8_t opcode = state.readProgramByte();
    return instructions[opcode].get();
}

OpcodeMap::OpcodeMap(State& state)
{
    instructions[0xCD] = std::make_unique<Opcode::MOV_CD>(state);
}

}