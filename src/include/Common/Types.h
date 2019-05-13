#pragma once

#include <stdint.h>
#include <iostream>
#include <iomanip>

namespace Types {

template<typename T>
T binaryAdd(T augend, T addend, bool& unsignedCarry, bool& signedOverflow)
{
    uint32_t sum = uint32_t(augend) + uint32_t(addend) + unsignedCarry;
    unsignedCarry = sum & 1 << T::bitCount();
    T result(sum);
    signedOverflow = augend.isNegative() == addend.isNegative() && addend.isNegative() != result.isNegative();
    return result;
}

template<typename T>
T binarySubtract(T minuhend, T subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow)
{
    return binaryAdd(minuhend, T(~subtrahend), invertedUnsignedBorrow, signedOverflow);
}

}

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

    /*Byte operator--(int)
    {
        Byte copy(value);
        --value;
        return copy;
    }*/

    template<typename T>
    Byte& operator+=(T operand)
    {
        value += operand;
        return *this;
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

    static int bitCount()
    {
        return 8;
    }

    bool isNegative() const
    {
        return getBit(7);
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
    Word& operator-=(T operand)
    {
        value -= operand;
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

    template<typename T>
    Word& operator>>=(T operand)
    {
        value >>= operand;
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

    static int bitCount()
    {
        return 16;
    }

    bool isNegative() const
    {
        return value & 1 << 15;
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

    Byte getLowByte() const
    {
        return Byte(value);
    }

    void setLowByte(Byte lowByte)
    {
        value = lowByte | (value & 0xff00);
    }

    Byte getHighByte() const
    {
        return Byte(value >> 8);
    }

    void setHighByte(Byte highByte)
    {
        value = (value & 0x00ff) | highByte << 8;
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
        : Long(Byte(value), Byte(value >> 8), Byte(value >> 16))
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
