#pragma once

#include <stdint.h>

#include "../Instruction.h"
#include "SpcOperator.h"
#include "SpcState.h"

namespace SPC {

namespace AddressMode {

// Absolute
template <typename Operator>
class Immediate : public Instruction2Byte<State>
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Immediate is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const IState& state) const override
    {
        return Operator::toString() + " X, #$" + Instruction2Byte<State>::operandToString(state);
    }
};

}

}