#pragma once

#include <stdint.h>
#include <iostream>
#include <iomanip>

// Wrapper classes Byte (8-bit), Word (16-bit) and Long (24-bit)
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

    Byte& operator++()
    {
        ++value;
        return *this;
    }

    Byte operator++(int)
    {
        Byte copy(value);
        ++value;
        return copy;
    }

    Byte& operator--()
    {
        --value;
        return *this;
    }

    Byte operator--(int)
    {
        Byte copy(value);
        --value;
        return copy;
    }

    template<typename T>
    Byte& operator|=(T operand)
    {
        value |= operand;
        return *this;
    }

    template<typename T>
    Byte& operator&=(T operand)
    {
        value &= operand;
        return *this;
    }

    template<typename T>
    Byte& operator^=(T operand)
    {
        value ^= operand;
        return *this;
    }

    template<typename T>
    Byte& operator<<=(T operand)
    {
        value <<= operand;
        return *this;
    }

    template<typename T>
    Byte& operator>>=(T operand)
    {
        value >>= operand;
        return *this;
    }

    bool getBit(int bitIndex) const
    {
        return value & 1 << bitIndex;
    }

    void setBit(int bitIndex, bool bitValue)
    {
        if (bitValue) {
            value |= 1 << bitIndex;
        } else {
            value &= ~(1 << bitIndex);
        }
    }

    bool isNegative() const
    {
        return getBit(7);
    }

    void binaryAdd(Byte addend, bool& unsignedCarry, bool& signedOverflow)
    {
        uint16_t result = uint16_t(value) + uint16_t(addend.value) + unsignedCarry;
        unsignedCarry = result & 1 << 8;
        value = uint8_t(result);
        signedOverflow = isNegative() != unsignedCarry;
    }

    void binarySubtract(Byte subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow)
    {
        binaryAdd(~subtrahend, invertedUnsignedBorrow, signedOverflow);
    }

private:
    uint8_t value;

    friend std::ostream& operator<<(std::ostream&, Byte);
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

    Word(Byte lowByte, Byte highByte)
        : value(lowByte | highByte << 8)
    {
    }

    operator uint16_t() const
    {
        return value;
    }

    template<typename T>
    Word& operator+=(T operand)
    {
        value += operand;
        return *this;
    }

    template<typename T>
    Word& operator|=(T operand)
    {
        value |= operand;
        return *this;
    }

    template<typename T>
    Word& operator<<=(T operand)
    {
        value <<= operand;
        return *this;
    }

    Word& operator++()
    {
        ++value;
        return *this;
    }

    Word& operator--()
    {
        --value;
        return *this;
    }

    Word operator--(int)
    {
        Word copy(value);
        --value;
        return copy;
    }

    bool isNegative() const
    {
        return value & 1 << 15;
    }

    Byte getLowByte() const
    {
        return Byte(value);
    }

    void setLowByte(Byte lowByte)
    {
        value = lowByte | value & 0xff00;
    }

    Byte getHighByte() const
    {
        return Byte(value >> 8);
    }

    void setHighByte(Byte highByte)
    {
        value = value & 0x00ff | highByte;
    }

private:
    uint16_t value;

    friend std::ostream& operator<<(std::ostream&, Word);
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

    Long(Byte lowByte, Byte highByte, Byte bankByte)
        : value(lowByte | highByte << 8 | bankByte << 16)
    {
    }

    Long(Word address, Byte bank)
        : value(address | bank << 16)
    {
    }

    operator uint32_t() const
    {
        return value;
    }

    template<typename T>
    Long& operator+=(T operand)
    {
        value += operand;
        return *this;
    }

    template<typename T>
    Long& operator-=(T operand)
    {
        value -= operand;
        return *this;
    }

    Long& operator++()
    {
        ++value;
        return *this;
    }

    Long operator++(int)
    {
        Long copy(value);
        ++value;
        return copy;
    }

private:
    uint32_t value;

    friend std::ostream& operator<<(std::ostream&, Long);
};

inline std::ostream& operator<<(std::ostream& output, Byte byte)
{
    return output << std::hex << std::setw(2) << std::setfill('0') << +byte.value << std::dec;
}

inline std::ostream& operator<<(std::ostream& output, Word word)
{
    return output << std::hex << std::setw(4) << std::setfill('0') << word.value << std::dec;
}

inline std::ostream& operator<<(std::ostream& output, Long long_)
{
    return output << std::hex << std::setw(6) << std::setfill('0') << long_.value << std::dec;
}
