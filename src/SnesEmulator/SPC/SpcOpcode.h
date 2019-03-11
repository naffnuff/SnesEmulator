#pragma once

#include <stdint.h>

#include "../Instruction.h"
#include "SpcAddressMode.h"
#include "SpcOperator.h"
#include "SpcState.h"

namespace SPC {

namespace Opcode {

class MOV_CD : public AddressMode::Immediate<Operator::MOV>
{
public:
    MOV_CD(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_CD is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override
    {
        return "CD: MOV X, #i";
    }

    State& state;
};

}

}
