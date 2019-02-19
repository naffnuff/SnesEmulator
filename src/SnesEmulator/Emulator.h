#pragma once

#include "OpcodeMap.h"
#include "State.h"

class Emulator
{
public:
    Emulator();
    void run();
private:
    OpcodeMap instructions;
    State state;
};

