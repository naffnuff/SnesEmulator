#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>

#include "../IState.h"
#include "../Util.h"

namespace CPU {

class State : public IState
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

    enum Register
    {
        X = 0,
        Y = 1
    };

    State()
        : accumulatorA(0)
        , accumulatorB(0)
        , dataBank(0)
        , xIndex(0)
        , yIndex(0)
        , directPage(0)
        , stackPointer(0)
        , programBank(0)
        , programCounter(0)
        , resetAddress(0)
        , flags(0)
        , emulationMode(true)
        , memory(1 << 24, 0x55)
    {
        std::cout << "Memory size=" << memory.size() << std::endl;
        forceEmulationRegisters();
    }

    State(State&) = delete;
    State& operator=(State&) = delete;

    std::ostream& printMemoryPage(std::ostream& output, uint32_t startAddress) const override
    {
        output << "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        uint32_t address = startAddress - std::bitset<4>(startAddress).to_ulong();
        for (int i = 0; i < 16 && address < memory.size(); ++i) {
            uint8_t bank = uint8_t(address >> 16);
            uint16_t lowAddress = uint16_t(address);
            lowAddress = lowAddress >> 4;
            output << std::setw(2) << std::setfill('0') << +bank << ':' << std::setw(3) << std::setfill('0') << lowAddress << "x  ";

            for (int j = 0; j < 16 && address < memory.size(); ++j) {
                output << std::setw(2) << std::setfill('0') << +memory[address++] << ' ';
            }

            output << std::endl;
        }
        return output;
    }

    std::ostream& printRegisters(std::ostream& output) const
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

    void setFlag(uint8_t flag, bool value)
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

    void setFlags(uint8_t value)
    {
        flags = value;
    }

    bool isNativeMode() const
    {
        return !emulationMode;
    }

    bool is16Bit(Flag flag) const
    {
        return isNativeMode() && !getFlag(flag);
    }

    uint8_t readProgramByte(int offset = 0) const override
    {
        return memory[getProgramAddress(offset)];
    }

    void reset()
    {
        programCounter = resetAddress;
    }

    uint8_t nextProgramByte()
    {
        return memory[programCounter++];
    }

    void incrementProgramCounter(uint16_t increment)
    {
        programCounter += increment;
    }

    uint32_t getProgramAddress(int offset = 0) const override
    {
        return (programBank << 16 | programCounter) + offset;
    }

    uint16_t getProgramCounter(int offset = 0) const
    {
        return programCounter + offset;
    }

    uint8_t getAccumulatorA() const
    {
        return accumulatorA;
    }

    void setAccumulatorA(uint8_t value)
    {
        accumulatorA = value;
        updateSignFlags(value);
    }

    uint8_t getAccumulatorB() const
    {
        return accumulatorB;
    }

    void setAccumulatorC(uint16_t value)
    {
        accumulatorA = uint8_t(value);
        accumulatorB = uint8_t(value >> 8);
        updateSignFlags(value);
    }

    uint16_t getAccumulatorC() const
    {
        return accumulatorB << 8 | accumulatorA;
    }

    uint16_t getDirectPage() const
    {
        return directPage;
    }

    uint8_t* getMemoryPointer(uint32_t address)
    {
        return &memory[address];
    }

    uint8_t* getMemoryPointer(uint8_t lowByte, uint8_t highByte, uint8_t bankByte)
    {
        return getMemoryPointer(uint32_t(bankByte << 16 | highByte << 8 | lowByte));
    }

    uint8_t* getMemoryPointer(uint8_t lowByte, uint8_t highByte)
    {
        return getMemoryPointer(lowByte, highByte, dataBank);
    }

    uint8_t* getMemoryPointer(uint8_t lowByte)
    {
        return getMemoryPointer(uint32_t(directPage + lowByte));
    }

    void exchangeCarryAndEmulationFlags()
    {
        bool emulation = emulationMode;
        emulationMode = getFlag(c);
        setFlag(c, emulation);

        forceEmulationRegisters();
    }

    void forceEmulationRegisters()
    {
        if (emulationMode) {
            setFlag(x | m, true);
            ((uint8_t*)(&xIndex))[1] = 0;
            ((uint8_t*)(&yIndex))[1] = 0;
            ((uint8_t*)(&stackPointer))[1] = 1;
        }
    }

    void updateSignFlags(uint8_t value)
    {
        setFlag(State::z, value == 0);
        setFlag(State::n, value & 1 << 7);
    }

    void updateSignFlags(uint16_t value)
    {
        setFlag(State::z, value == 0);
        setFlag(State::n, value & 1 << 15);
    }

    void pushToStack(uint8_t byte)
    {
        memory[stackPointer--] = byte;
        forceEmulationRegisters();
    }

    void pushToStack(uint16_t byte)
    {
        pushToStack(uint8_t(byte >> 8));
        pushToStack(uint8_t(byte));
    }

    void pushFlagsToStack()
    {
        pushToStack(flags);
    }

    void setProgramCounter(uint16_t pc, uint8_t pbr)
    {
        programCounter = pc;
        programBank = pbr;
    }

    void setProgramCounter(uint16_t value)
    {
        setProgramCounter(value, programBank);
    }

    void setProgramCounter(uint32_t value)
    {
        setProgramCounter(uint16_t(value), uint8_t(value >> 16));
    }

    void setStackPointer(uint16_t value)
    {
        stackPointer = value;
        forceEmulationRegisters();
    }

    void setXIndexRegister(uint16_t value)
    {
        xIndex = value;
        forceEmulationRegisters();
        updateSignFlags(value);
    }

    void setXIndexRegister(uint8_t value)
    {
        xIndex = value;
        updateSignFlags(value);
    }

    void setYIndexRegister(uint16_t value)
    {
        yIndex = value;
        forceEmulationRegisters();
        updateSignFlags(value);
    }

    void setYIndexRegister(uint8_t value)
    {
        yIndex = value;
        updateSignFlags(value);
    }

    void setDirectPageRegister(uint16_t value)
    {
        directPage = value;
        updateSignFlags(value);
    }

    void loadRom(const std::string& path, std::ostream& output);

private:
    bool tryReadHeader(int offset, std::vector<char> rom, std::ostream& output);

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

}