#pragma once

#include "Exception.h"

#include <stdint.h>
#include <iostream>
#include <iomanip>

#pragma warning( disable : 4702 ) // unreachable code
#pragma warning( disable : 4100 ) // unreferenced formal parameter

namespace Types {

template<int bitCount, typename ReturnT, typename T>
ReturnT signedClamp(T value)
{
    constexpr int32_t max = (1 << (bitCount - 1)) - 1;
    if (value > max) {
        value = max;
    } else if (value < ~max) {
        value = ~max;
    }
    return ReturnT(value);
}

template<int bitCount, typename ReturnT, typename T>
ReturnT unsignedClamp(T value)
{
    constexpr int32_t max = (1 << bitCount) - 1;
    if (value > max) {
        value = max;
    } else if (value < 0) {
        value = 0;
    }
    return ReturnT(value);
}

template<int bitCount, typename ReturnT, typename T>
ReturnT clip(T value)
{
    constexpr int32_t max = (1 << bitCount) - 1;
    return ReturnT(value & max);
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
bool isOverflow(T augend, T addend, T sum)
{
    return augend.isNegative() == addend.isNegative() && addend.isNegative() != sum.isNegative();
}

template<typename T>
T binaryAdd(T augend, T addend, bool& unsignedCarry, bool& signedOverflow, bool& halfCarry)
{
    uint32_t sum = uint32_t(augend) + uint32_t(addend) + unsignedCarry;
    T result(sum);
    T halfCarryHighBitMask = T(1) << (T::bitCount - 4);
    T halfCarryLowBitsMask = halfCarryHighBitMask - 1;
    halfCarry = ((augend & halfCarryLowBitsMask) + (addend & halfCarryLowBitsMask) + unsignedCarry) & halfCarryHighBitMask;
    bool halfCarryAlt = (augend ^ addend ^ result) & halfCarryHighBitMask;
    if (halfCarry != halfCarryAlt) {
        throw std::logic_error(__FUNCTION__ + std::string(" bad half-carry calculation"));
    }
    unsignedCarry = sum & 1 << T::bitCount;
    signedOverflow = isOverflow(augend, addend, result);
    return result;
}

template<typename T>
T binarySubtract(T minuhend, T subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow, bool& halfCarry)
{
    return binaryAdd(minuhend, T(~subtrahend), invertedUnsignedBorrow, signedOverflow, halfCarry);
}

template<typename T>
T decimalAdd(T augend, T addend, bool& carry, bool& overflow)
{
    T sum = carry ? T(1) : T(0);
    for (int offset = 0; offset < T::bitCount; offset += 4)
    {
        T nibbleMask = T(0xf) << offset;
        sum = sum + T(augend & nibbleMask) + T(addend & nibbleMask);
        carry = sum >= (T(0x0a) << offset);
        if (carry)
        {
            T fullBitmask = (T(0x10) << offset) - T(1);
            sum = ((sum + (T(0x06) << offset)) & fullBitmask) + (T(0x10) << offset);
        }
    }

    overflow = isOverflow(augend, addend, sum);

    return sum;
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

    Byte(const Byte& other)
	{
		*this = other;
	}

    Byte& operator=(const Byte& other)
	{
		value = other;
		return *this;
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

    /*
        SBC B: A = A-B+C-1

 	    6502	65C02	65816
        A	Seq. 3	Seq. 4	Seq. 3
        C	bin	bin	bin
        N	bin	dec	dec
        V	bin	bin	bin
        Z	bin	dec	dec
        Seq. 3:

        3a. AL = (A & $0F) - (B & $0F) + C-1
        3b. If AL < 0, then AL = ((AL - $06) & $0F) - $10
        3c. A = (A & $F0) - (B & $F0) + AL
        3d. If A < 0, then A = A - $60
        3e. The accumulator result is the lower 8 bits of A

        Seq. 4:

        4a. AL = (A & $0F) - (B & $0F) + C-1
        4b. A = A - B + C-1
        4c. If A < 0, then A = A - $60
        4d. If AL < 0, then A = A - $06
        4e. The accumulator result is the lower 8 bits of A
    */
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
        return Byte(difference);
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

#pragma warning(push)
#pragma warning(disable : 4702) // unreachable code
    Word(uint16_t value)
        : value(value)
    {
    }
#pragma warning(pop)

    explicit Word(uint32_t value)
        : value(uint16_t(value))
    {
    }

    explicit Word(int32_t value)
        : value(uint16_t(value))
    {
    }

    Word(Byte lowByte, Byte highByte)
        : value(lowByte | highByte << 8)
    {
	}

    Word(const Word& other)
	{
		*this = other;
	}

    Word& operator=(const Word& other)
	{
		value = other;
		return *this;
	}

    operator uint16_t() const
    {
        return value;
    }

    template<typename T>
    Word& operator+=(T operand)
    {
        value += uint16_t(operand);
        return *this;
    }

    template<typename T>
    Word& operator-=(T operand)
    {
        value -= uint16_t(operand);
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
        value = lowByte | (value & 0xff00);
    }

    Byte getHighByte() const
    {
        return Byte(value >> 8);
    }

    void setHighByte(Byte highByte)
    {
        value = Word(Byte(value), highByte);
    }

    static Word decimalSubtract(Word minuhend, Word subtrahend, bool& invertedUnsignedBorrow, bool& signedOverflow)
    {
        int differenceLow = (minuhend & 0x000f) - (subtrahend & 0x000f) + invertedUnsignedBorrow - 1;
        if (differenceLow < 0)
        {
            differenceLow = ((differenceLow - 0x0006) & 0x000f) - 0x0010;
        }
        int difference1 = (minuhend & 0x00f0) - (subtrahend & 0x00f0) + differenceLow;
        if (difference1 < 0)
        {
            difference1 -= 0x0060;
        }
        int difference2 = (minuhend & 0x0f00) - (subtrahend & 0x0f00) + difference1;
        if (difference2 < 0)
        {
            difference2 -= 0x0600;
        }
        int difference3 = (minuhend & 0xf000) - (subtrahend & 0xf000) + difference2;
        if (difference3 < 0)
        {
            difference3 -= 0x6000;
        }
        bool dummy = false;
        Types::binarySubtract(minuhend, subtrahend, invertedUnsignedBorrow, signedOverflow, dummy);
        return Word(difference3);
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

    Long(const Long& other)
    {
        *this = other;
    }

    Long& operator=(const Long& other)
    {
        value = other;
        return *this;
    }

    operator uint32_t() const
    {
        return value;
    }

    void wrapValue()
    {
        constexpr uint32_t mask = (1 << bitCount) - 1;
        value = value & mask;
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
        value = lowByte | (value & 0xffff00);
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
