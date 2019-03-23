#pragma once
#include <stdint.h>
#include <iostream>
#include <iomanip>

// Wrapper classes Byte (8-bit), Word (16-bit) and Long (24-bit) exist primarily to facilitate nice hexadecimal printing
class Byte
{
public:
    Byte()
        : value(0)
    {
    }

    Byte(uint8_t value)
        : value(value)
    {
    }

    explicit Byte(char value)
        : value(uint8_t(value))
    {
    }

    explicit Byte(uint16_t value)
        : value(uint8_t(value))
    {
    }

    explicit Byte(uint32_t value)
        : value(uint8_t(value))
    {
    }

    explicit Byte(int32_t value)
        : value(uint8_t(value))
    {
    }

    operator uint8_t() const
    {
        return value;
    }

    Byte& operator--()
    {
        --value;
        return *this;
    }

    Byte& operator++()
    {
        ++value;
        return *this;
    }

    Byte& operator|=(Byte operand)
    {
        value |= operand.value;
        return *this;
    }

    Byte& operator&=(Byte operand)
    {
        value &= operand.value;
        return *this;
    }

    bool isNegative() const
    {
        return value & 1 << 7;
    }

private:
    uint8_t value;

    friend std::ostream& operator<<(std::ostream& output, Byte byte);
};

class Word
{
public:
    Word()
        : value(0)
    {
    }

    Word(uint16_t value)
        : value(value)
    {
    }

    operator uint16_t() const
    {
        return value;
    }

private:
    uint16_t value;

    friend std::ostream& operator<<(std::ostream& output, Word word);
};

class Long
{
public:
    Long()
        : value(0)
    {
    }

    Long(uint32_t value)
        : value(value)
    {
    }

    operator uint32_t() const
    {
        return value;
    }

private:
    uint32_t value;

    friend std::ostream& operator<<(std::ostream&, Long long_);
};

inline std::ostream& operator<<(std::ostream& output, Byte byte)
{
    return output << std::hex << std::setw(2) << std::setfill('0') << +byte.value << std::dec;
}

inline std::ostream& operator<<(std::ostream& output, Word word)
{
    return output << std::hex << std::setw(4) << std::setfill('0') << +word.value << std::dec;
}

inline std::ostream& operator<<(std::ostream& output, Long long_)
{
    return output << std::hex << std::setw(6) << std::setfill('0') << +long_.value << std::dec;
}
