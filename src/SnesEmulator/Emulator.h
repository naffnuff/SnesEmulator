#pragma once

#include "InstructionMap.h"
#include "State.h"

class Emulator
{
public:
    Emulator();
    void run();
private:
    InstructionMap instructions;
    State state;
};

