#pragma once

#include <stdint.h>

namespace Util {

inline bool isNegative(uint8_t value)
{
    return value & 1 << 7;
}

inline bool isNegative(uint16_t value)
{
    return value & 1 << 15;
}

}