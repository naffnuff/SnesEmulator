#pragma once

#include <stdint.h>
#include <iostream>

class IState
{
public:
    virtual std::ostream& printMemoryPage(std::ostream& output, uint32_t startAddress) const = 0;
    virtual std::ostream& printRegisters(std::ostream& output) const = 0;
    virtual uint32_t getProgramAddress(int offset = 0) const = 0;
    virtual uint16_t getProgramCounter(int offset = 0) const = 0;
    virtual uint8_t readProgramByte(int offset = 0) const = 0;
};