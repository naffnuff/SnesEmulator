#pragma once

#include "OpcodeMap.h"
#include "State.h"

class Emulator
{
public:
    void run(std::ostream& output, std::istream& input, std::ostream& error);
private:
    OpcodeMap instructions;
    State state;
};

