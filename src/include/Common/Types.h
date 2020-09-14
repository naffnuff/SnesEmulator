#pragma once

#include <stdint.h>
#include <iostream>
#include <iomanip>

#include "Exception.h"

namespace Types {

template<int bitCount, typename T>
T signedClamp(T value)
{
    constexpr int32_t max = (1 << (bitCount - 1)) - 1;
    if (value > max) {
        value = max;
    } else if (value < ~max) {
        value = ~max;
    }
    return value;
}

template<int bitCount, typename T>
T unsignedClamp(T value)
{
    constexpr int32_t max = (1 << bitCount) - 1;
    if (value > max) {
        value = max;
    } else if (value < 0) {
        value = 0;
    }
    return value;
}

template<int bitCount, typename T>
T clip(T value)
{
    constexpr int32_t max = (1 << bitCount) - 1;
    return value & max;
}

template<typename T>
struct SpaceSize
{
    static constexpr uint32_t value = 1 << T::bitCount;
};

template<typename T>
struct BitMask
{
    static constexpr uint32_t value = T::spaceSize - 1;
};

template<typename T>
T binaryAdd(T augend, T addend, bool& unsignedCarry, bool& signedOverflow, bool& halfCarry)
{
    uint32_t sum = uint32_t(augend) + uint32_t(addend) + unsignedCarry;
    T result(sum);
    T halfCarryHighBitMask = 1 << (T::bitCount - 4);
    T halfCarryLowBitsMask = halfCarryHighBitMask - 1;
    halfCarry = ((augend & halfCarryLowBitsMask) + (addend & halfCarryLowBitsMask) + unsignedCarry) & halfCarryHighBitMask;
    bool halfCarryAlt = (augend ^ addend ^ result) & halfCarryHighBitMask;
    if (halfCarry != halfCarryAlt) {
        throw std::logic_error(__FUNCTION__ + std::string(" bad half-carry calculation"));
    }
    unsignedCarry = sum & 1 << T::bitCount;
    signedOverflow = augend.isNegative() == addend.isNegative() && addend.isNegative() != result.isNegative();
    return result;
}

template<typename T>
T binarySubtract(T minuhend, T subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow, bool& halfCarry)
{
    return binaryAdd(minuhend, T(~subtrahend), invertedUnsignedBorrow, signedOverflow, halfCarry);
}

template<typename T>
T decimalAdd(T augend, T addend, bool& unsignedCarry, bool& signedOverflow)
{
    return T::decimalAdd(augend, addend, unsignedCarry, signedOverflow);
}

template<typename T>
T decimalSubtract(T minuhend, T subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow)
{
    return T::decimalSubtract(minuhend, subtrahend, invertedUnsignedBorrow, signedOverflow);
}

}

// Wrapper classes Byte (8-bit), Word (16-bit) and Long (24-bit)
class Byte
{
public:
    static constexpr int bitCount = 8;
    static constexpr uint32_t spaceSize = Types::SpaceSize<Byte>::value;
    static constexpr uint32_t bitMask = Types::BitMask<Byte>::value;

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
    Byte& operator-=(T operand)
    {
        value -= operand;
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

    Byte getBits(int offset, int count) const
    {
        return value >> offset & ((1 << count) - 1);
    }

    bool isNegative() const
    {
        return getBit(7);
    }

    static Byte decimalAdd(Byte augend, Byte addend, bool& unsignedCarry, bool& signedOverflow)
    {
        int sumLow = (augend & 0x0f) + (addend & 0x0f) + unsignedCarry;
        if (sumLow >= 0x0a) {
            sumLow = ((sumLow + 0x06) & 0x0f) + 0x10;
        }
        int sum = (augend & 0xf0) + (addend & 0xf0) + sumLow;
        if (sum >= 0xa0) {
            sum += 0x60;
        }
        unsignedCarry = sum >= 0x100;
        int signedSum = int8_t(augend & 0xf0) + int8_t(addend & 0xf0) + int8_t(sumLow);
        signedOverflow = signedSum < -128 || signedSum > 127;
        return sum;
    }

    static Byte decimalSubtract(Byte minuhend, Byte subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow)
    {
        int differenceLow = (minuhend & 0x0f) - (subtrahend & 0x0f) + invertedUnsignedBorrow - 1;
        if (differenceLow < 0) {
            differenceLow = ((differenceLow - 0x06) & 0x0f) - 0x10;
        }
        int difference = (minuhend & 0xf0) - (subtrahend & 0xf0) + differenceLow;
        if (difference < 0) {
            difference -= 0x60;
        }
        bool dummy = false;
        Types::binarySubtract(minuhend, subtrahend, invertedUnsignedBorrow, signedOverflow, dummy);
        return difference;
    }

private:
    uint8_t value;

    friend std::ostream& operator<<(std::ostream&, Byte);
};

class Word
{
private:
    EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)

public:
    static constexpr int bitCount = 16;
    static constexpr uint32_t spaceSize = Types::SpaceSize<Word>::value;
    static constexpr uint32_t bitMask = Types::BitMask<Word>::value;

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

    Word& operator&=(Word operand)
    {
        value &= operand;
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

    Word operator++(int)
    {
        Word copy(value);
        ++value;
        return copy;
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

    Word getBits(int offset, int count) const
    {
        return value >> offset & ((1 << count) - 1);
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
        value = Word(Byte(value), highByte);
    }

    static Word decimalAdd(Word augend, Word addend, bool& unsignedCarry, bool& signedOverflow)
    {
        throw NotYetImplementedException("Decimal addition for Word");
        return 0;
    }

    static Word decimalSubtract(Word minuhend, Word subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow)
    {
        throw NotYetImplementedException("Decimal subtraction for Word");
        return 0;
    }

private:
    uint16_t value;

    friend std::ostream& operator<<(std::ostream&, Word);
};

class Long
{
public:
    static constexpr int bitCount = 24;
    static constexpr uint32_t spaceSize = Types::SpaceSize<Long>::value;
    static constexpr uint32_t bitMask = Types::BitMask<Long>::value;

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

    void wrapValue()
    {
        constexpr uint32_t bitMask = (1 << bitCount) - 1;
        value = value & bitMask;
    }

    template<typename T>
    Long& operator+=(T operand)
    {
        value += operand;
        wrapValue();
        return *this;
    }

    template<typename T>
    Long& operator-=(T operand)
    {
        value -= operand;
        wrapValue();
        return *this;
    }

    Long& operator++()
    {
        ++value;
        wrapValue();
        return *this;
    }

    Long operator++(int)
    {
        Long copy(value);
        ++value;
        wrapValue();
        return copy;
    }

    bool getBit(int bitIndex) const
    {
        return value & 1 << bitIndex;
    }

    Byte getLowByte() const
    {
        return Byte(value);
    }

    void setLowByte(Byte lowByte)
    {
        value = lowByte | value & 0xffff00;
    }

    Byte getHighByte() const
    {
        return Byte(value >> 8);
    }

    void setHighByte(Byte highByte)
    {
        value = Long(getLowByte(), highByte, getBankByte());
    }

    Byte getBankByte() const
    {
        return Byte(value >> 16);
    }

    void setBankByte(Byte bankByte)
    {
        value = Long(Word(value), bankByte);
    }

private:
    uint32_t value;

    friend std::ostream& operator<<(std::ostream&, Long);
};

inline std::ostream& operator<<(std::ostream& output, Byte byte)
{
    return output << std::hex << std::right << std::setw(2) << std::setfill('0') << +byte.value << std::dec;
}

inline std::ostream& operator<<(std::ostream& output, Word word)
{
    return output << std::hex << std::right << std::setw(4) << std::setfill('0') << word.value << std::dec;
}

inline std::ostream& operator<<(std::ostream& output, Long long_)
{
    return output << std::hex << std::right << std::setw(6) << std::setfill('0') << long_.value << std::dec;
}
