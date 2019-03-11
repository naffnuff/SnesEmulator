#pragma once

#include "SpcState.h"

namespace SPC {

namespace Operator {

class MOV
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("MOV is not implemented");
        int cycles = 0;
        return cycles;
    }

    static std::string toString()
    {
        return "MOV";
    }
};

}

}