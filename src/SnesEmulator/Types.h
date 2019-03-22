#pragma once

#include <stdint.h>
#include <iostream>
#include <iomanip>

struct Byte
{
    uint8_t value;
};

inline std::ostream& operator<<(std::ostream& output, const Byte& byte)
{
    return output << std::setw(2) << std::setfill('0') << byte;
}