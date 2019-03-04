#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <stdint.h>
#include <iomanip>

class State
{
public:
    enum Flag
    {
        c = 1 << 0, // Carry
        z = 1 << 1, // Zero
        i = 1 << 2, // IRQ Disable
        d = 1 << 3, // Decimal Mode
        x = 1 << 4, // Index Register Select, 1 = 8-bit, 0 = 16-bit
        b = 1 << 4, // Break (emulation mode only)
        m = 1 << 5, // Memory/Accumulator Select, 1 = 8-bit, 0 = 16-bit
        v = 1 << 6, // Overflow
        n = 1 << 7  // Negative
    };

    State()
        : accumulatorA(0)
        , accumulatorB(0)
        , dataBank(0)
        , xIndex(0)
        , yIndex(0)
        , directPage(0)
        , stackPointer(0x1ff)
        , programBank(0)
        , programCounter(0)
        , resetAddress(0)
        , flags(i)
        , emulationMode(true)
    {
        memory.resize(1 << 24);
        std::cout << "Memory size=" << memory.size() << std::endl;
    }

    State(State&) = delete;
    State& operator=(State&) = delete;

    std::ostream& printMemoryPage(std::ostream& output, uint32_t startAddress)
    {
        output << "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        uint32_t address = startAddress - std::bitset<4>(startAddress).to_ulong();
        for (int i = 0; i < 16 && address < memory.size(); ++i) {
            uint8_t bank = address >> 16;
            uint16_t lowAddress = address;
            lowAddress = lowAddress >> 4;
            output << std::setw(2) << std::setfill('0') << +bank << ':' << std::setw(3) << std::setfill('0') << lowAddress << "x  ";

            for (int j = 0; j < 16 && address < memory.size(); ++j) {
                output << std::setw(2) << std::setfill('0') << +memory[address++] << ' ';
            }

            output << std::endl;
        }
        return output;
    }

    std::ostream& printRegisters(std::ostream& output)
    {
        std::bitset<8> flagSet(flags);
        if (emulationMode) {
            flagSet |= Flag::m;
        }
        return output
            << "PB=" << std::setw(2) << std::setfill('0') << +programBank
            << ", PC=" << std::setw(4) << std::setfill('0') << programCounter
            << ", A=" << std::setw(4) << std::setfill('0') << getAccumulatorC()
            << ", X=" << std::setw(4) << std::setfill('0') << xIndex
            << ", Y=" << std::setw(4) << std::setfill('0') << yIndex
            << ", S=" << std::setw(4) << std::setfill('0') << stackPointer
            << ", DP=" << std::setw(4) << std::setfill('0') << directPage
            << ", DB=" << std::setw(2) << std::setfill('0') << +dataBank
            << ", flags=" << flagSet
            << ", e=" << emulationMode;
    }

    void setFlag(int flag, bool value)
    {
        if (value) {
            flags |= flag;
        } else {
            flags &= ~flag;
        }
    }

    bool getFlag(Flag flag) const
    {
        return flags & flag;
    }

    bool isNativeMode() const
    {
        return !emulationMode;
    }

    bool is16Bit(Flag flag) const
    {
        if (emulationMode) {
            return false;
        } else {
            return getFlag(flag);
        }
    }

    uint8_t readProgramByte(int offset = 0) const
    {
        return memory[getProgramAddress(offset)];
    }

    void loadRom(const std::string& path);

    void reset()
    {
        programCounter = resetAddress;
    }

    void incrementProgramCounter(int increment)
    {
        programCounter += increment;
    }

    uint32_t getProgramAddress(int offset = 0) const
    {
        return (programBank << 16 | programCounter) + offset;
    }

    uint8_t getAccumulatorA() const
    {
        return accumulatorA;
    }

    void setAccumulatorA(uint8_t value)
    {
        accumulatorA = value;
    }

    void setAccumulatorB(uint8_t value)
    {
        accumulatorB = value;
    }

    uint8_t getAccumulatorB() const
    {
        return accumulatorB;
    }

    uint32_t getAccumulatorC() const
    {
        return accumulatorB << 8 | accumulatorA;
    }

    uint16_t getDirectPage() const
    {
        return directPage;
    }

    uint8_t* getMemoryPointer(uint8_t lowByte, uint8_t highByte)
    {
        return &memory[dataBank << 16 | highByte << 8 | lowByte];
    }

private:
    bool tryReadHeader(int offset, std::vector<char> rom);

private:
    uint8_t accumulatorA;
    uint8_t accumulatorB;
    uint8_t dataBank;
    uint16_t xIndex;
    uint16_t yIndex;
    uint16_t directPage;
    uint16_t stackPointer;
    uint8_t programBank;
    uint16_t programCounter;

    uint16_t resetAddress;

    uint8_t flags;
    bool emulationMode;

    std::vector<uint8_t> memory;
};
