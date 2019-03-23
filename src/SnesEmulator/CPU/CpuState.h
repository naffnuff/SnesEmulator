#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>

#include "../Types.h"
#include "../Util.h"

namespace CPU {

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

    enum Register
    {
        X = 0,
        Y = 1
    };

    State()
        : xIndex(0)
        , yIndex(0)
        , directPage(0)
        , stackPointer(0)
        , programCounter(0)
        , resetAddress(0)
        , emulationMode(true)
        , memory(1 << 24, 0x55)
    {
        std::cout << "Memory size=" << memory.size() << std::endl;
        forceEmulationRegisters();
    }

    State(State&) = delete;
    State& operator=(State&) = delete;

    size_t getMemorySize() const
    {
        return memory.size();
    }

    std::ostream& printRegisters(std::ostream& output) const
    {
        std::string flagsString;
        if (emulationMode) {
            flagsString = "nv1bdizc";
        }
        else {
            flagsString = "nvmxdizc";
        }
        for (size_t i = 0; i < flagsString.size(); ++i) {
            if (flags & 1 << i) {
                flagsString[flagsString.size() - i - 1] = toupper(flagsString[flagsString.size() - i - 1]);
            }
        }

        std::bitset<8> flagSet(flags);
        
        return output
            << "PB=" << programBank
            << ", PC=" << std::hex << std::setw(4) << std::setfill('0') << programCounter
            << ", A=" << std::hex << std::setw(4) << std::setfill('0') << getAccumulatorC()
            << ", X=" << std::hex << std::setw(4) << std::setfill('0') << xIndex
            << ", Y=" << std::hex << std::setw(4) << std::setfill('0') << yIndex
            << ", S=" << std::hex << std::setw(4) << std::setfill('0') << stackPointer
            << ", DP=" << std::hex << std::setw(4) << std::setfill('0') << directPage
            << ", DB=" << dataBank
            << ", flags=" << flagSet << " (" << flagsString << ", $" << flags << ")"
            << ", e=" << emulationMode;
    }

    void setFlag(Byte flag, bool value)
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

    void setFlags(Byte value)
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

    Byte readProgramByte(int offset = 0) const
    {
        return memory[getProgramAddress(offset)];
    }

    void reset()
    {
        programCounter = resetAddress;
    }

    Byte nextProgramByte()
    {
        return memory[programCounter++];
    }

    void incrementProgramCounter(uint16_t increment)
    {
        programCounter += increment;
    }

    uint32_t getProgramAddress(int offset = 0) const
    {
        return (programBank << 16 | programCounter) + offset;
    }

    uint16_t getProgramCounter(int offset = 0) const
    {
        return programCounter + offset;
    }

    Byte getAccumulatorA() const
    {
        return accumulatorA;
    }

    void setAccumulatorA(Byte value)
    {
        accumulatorA = value;
        updateSignFlags(value);
    }

    Byte getAccumulatorB() const
    {
        return accumulatorB;
    }

    void setAccumulatorC(uint16_t value)
    {
        accumulatorA = Byte(value);
        accumulatorB = Byte(value >> 8);
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

    Byte getMemory(uint32_t address) const
    {
        return memory[address];
    }

    Byte* getMemoryPointer(uint32_t address)
    {
        return &memory[address];
    }

    Byte* getMemoryPointer(Byte lowByte, Byte highByte, Byte bankByte, uint16_t offset = 0)
    {
        return getMemoryPointer(uint32_t(bankByte << 16 | highByte << 8 | lowByte) + offset);
    }

    Byte* getMemoryPointer(Byte lowByte, Byte highByte)
    {
        return getMemoryPointer(lowByte, highByte, dataBank);
    }

    Byte* getMemoryPointer(Byte lowByte)
    {
        return getMemoryPointer(uint32_t(directPage + lowByte));
    }

    void exchangeCarryAndEmulationFlags()
    {
        forceEmulationRegisters();

        bool emulation = emulationMode;
        emulationMode = getFlag(c);
        setFlag(c, emulation);

        forceEmulationRegisters();
    }

    void forceEmulationRegisters()
    {
        if (emulationMode) {
            setFlag(x | m, true);
            ((Byte*)(&xIndex))[1] = 0;
            ((Byte*)(&yIndex))[1] = 0;
            ((Byte*)(&stackPointer))[1] = 1;
        }
    }

    void updateSignFlags(Byte value)
    {
        setFlag(State::z, value == 0);
        setFlag(State::n, value.isNegative());
    }

    void updateSignFlags(uint16_t value)
    {
        setFlag(State::z, value == 0);
        setFlag(State::n, value & 1 << 15);
    }

    void pushToStack(Byte byte)
    {
        memory[stackPointer--] = byte;
        forceEmulationRegisters();
    }

    void pushToStack(uint16_t byte)
    {
        pushToStack(Byte(byte >> 8));
        pushToStack(Byte(byte));
    }

    void pushFlagsToStack()
    {
        pushToStack(flags);
    }

    void setProgramCounter(uint16_t pc, Byte pbr)
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
        setProgramCounter(uint16_t(value), Byte(value >> 16));
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

    void setXIndexRegister(Byte value)
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

    void setYIndexRegister(Byte value)
    {
        yIndex = value;
        updateSignFlags(value);
    }

    uint16_t& getYIndexRegister()
    {
        return yIndex;
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
    Byte accumulatorA;
    Byte accumulatorB;
    Byte dataBank;
    uint16_t xIndex;
    uint16_t yIndex;
    uint16_t directPage;
    uint16_t stackPointer;
    Byte programBank;
    uint16_t programCounter;

    uint16_t resetAddress;

    Byte flags;
    bool emulationMode;

    std::vector<Byte> memory;
};

}