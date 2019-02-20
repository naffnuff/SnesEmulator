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
        : programCounter(0)
        , resetAddress(0)
        , emulationMode(true)
    {
        memory.resize(1 << 24);
        std::cout << "Memory size=" << memory.size() << std::endl;
    }

    State(State&) = delete;
    State& operator=(State&) = delete;

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

    friend std::ostream& operator<<(std::ostream& output, const State& state);

private:
    bool tryReadHeader(int offset, std::vector<char> rom);

private:
    uint8_t accumulatorA;
    uint8_t accumulatorB;
    uint8_t dataBankRegister;
    uint16_t xIndexRegister;
    uint16_t yIndexRegister;
    uint16_t directPagePointer;
    uint16_t stackPointer;
    uint8_t programBankRegister;
    uint16_t programCounter;
    uint16_t resetAddress;

    uint8_t flags;
    bool emulationMode;

    std::vector<uint8_t> memory;
};

std::ostream& operator<<(std::ostream& output, const State& state);
