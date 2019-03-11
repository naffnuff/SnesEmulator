#pragma once

#include <stdint.h>

class IState
{
public:
    virtual uint16_t getProgramCounter(int offset = 0) const = 0;
    virtual uint8_t readProgramByte(int offset = 0) const = 0;
};