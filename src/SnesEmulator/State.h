#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <stdint.h>

class State
{
public:
    enum Flag
    {
        c = 0, // Carry
        z = 1, // Zero
        i = 2, // IRQ Disable
        d = 3, // Decimal Mode
        x = 4, // Index Register Select, 1 = 8-bit, 0 = 16-bit
        m = 5, // Memory/Accumulator Select, 1 = 8-bit, 0 = 16-bit
        v = 6, // Overflow
        n = 7  // Negative
    };

    State()
        : programCounter(0)
        , resetAddress(0)
        , emulationMode(true)
    {
        memory.resize(1 << 24);
        std::cout << "Memory size=" << memory.size() << std::endl;
    }

    State(State&) = delete;
    State& operator=(State&) = delete;

    void setFlag(Flag flag, bool value)
    {
        flags[flag] = value;
    }

    bool getFlag(Flag flag) const
    {
        return flags[flag];
    }

    bool isEmulationMode() const
    {
        return emulationMode;
    }

    uint8_t readNextInstruction() const
    {
        return memory[programCounter];
    }

    uint8_t readOneByteValue() const
    {
        uint8_t value = memory[programCounter + 1];
        return value;
    }

    uint16_t readTwoByteValue() const
    {
        uint16_t value = memory[programCounter + 1];
        value += memory[programCounter + 2] << 8;
        return value;
    }

    uint32_t readThreeByteValue() const
    {
        uint32_t value = memory[programCounter + 1];
        value += memory[programCounter + 2] << 8;
        value += memory[programCounter + 3] << 16;
        return value;
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

private:
    bool tryReadHeader(int offset, std::vector<char> rom);

private:
    std::vector<uint8_t> memory;
    int programCounter;
    int resetAddress;
    std::bitset<8> flags;
    bool emulationMode;
};

