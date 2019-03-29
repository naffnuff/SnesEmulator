#pragma once

#include <iostream>
#include <vector>
#include <array>
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

    enum IndexRegister
    {
        X = 0,
        Y = 1,
        IndexRegisterCount
    };

    State()
        : emulationMode(true)
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
            << ", PC=" << programCounter
            << ", A=" << getAccumulatorC()
            << ", X=" << getIndexRegister<X>()
            << ", Y=" << getIndexRegister<Y>()
            << ", S=" << stackPointer
            << ", DP=" << directPage
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

    void incrementProgramCounter(Word increment)
    {
        programCounter += increment;
    }

    Long getProgramAddress(int offset = 0) const
    {
        return (programBank << 16 | programCounter) + offset;
    }

    Word getProgramCounter(int offset = 0) const
    {
        return programCounter + offset;
    }

    Byte* getAccumulatorPointer()
    {
        return &accumulatorA;
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

    void setAccumulatorC(Word value)
    {
        accumulatorA = Byte(value);
        accumulatorB = Byte(value >> 8);
        updateSignFlags(value);
    }

    Word getAccumulatorC() const
    {
        return accumulatorB << 8 | accumulatorA;
    }

    Word getDirectPage() const
    {
        return directPage;
    }

    Byte getMemory(Long address) const
    {
        return memory[address];
    }

    Byte* getMemoryPointer(Long address)
    {
        return &memory[address];
    }

    Byte* getMemoryPointer(Byte lowByte, Byte highByte, Byte bankByte, Word offset = 0)
    {
        return getMemoryPointer(Long(Long(lowByte, highByte, bankByte) + offset));
    }

    Byte* getMemoryPointer(Byte lowByte, Byte highByte)
    {
        return getMemoryPointer(lowByte, highByte, dataBank);
    }

    Byte* getMemoryPointer(Byte lowByte)
    {
        return getMemoryPointer(Long(directPage + lowByte));
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
            ((Byte*)(&getIndexRegister<X>()))[1] = 0;
            ((Byte*)(&getIndexRegister<Y>()))[1] = 0;
            ((Byte*)(&stackPointer))[1] = 1;
        }
    }

    template<typename T>
    void updateSignFlags(T value)
    {
        setFlag(State::z, value == 0);
        setFlag(State::n, value.isNegative());
    }

    void pushToStack(Byte byte)
    {
        memory[stackPointer--] = byte;
        forceEmulationRegisters();
    }

    void pushToStack(Word byte)
    {
        pushToStack(Byte(byte >> 8));
        pushToStack(Byte(byte));
    }

    void pushFlagsToStack()
    {
        pushToStack(flags);
    }

    Byte pullFromStack()
    {
        ++stackPointer;
        forceEmulationRegisters();
        return memory[stackPointer];
    }

    Word pullWordFromStack()
    {
        Byte lowByte = pullFromStack();
        Byte highByte = pullFromStack();
        return Word(lowByte, highByte);
    }

    void setProgramCounter(Word pc, Byte pbr)
    {
        programCounter = pc;
        programBank = pbr;
    }

    void setProgramCounter(Word value)
    {
        setProgramCounter(value, programBank);
    }

    void setProgramCounter(Long value)
    {
        setProgramCounter(Word(value), Byte(value >> 16));
    }

    void setStackPointer(Word value)
    {
        stackPointer = value;
        forceEmulationRegisters();
    }

    template<IndexRegister Register>
    void setIndexRegister(Word value)
    {
        getIndexRegister<Register>() = value;
        forceEmulationRegisters();
        updateSignFlags(value);
    }

    template<IndexRegister Register>
    void setIndexRegister(Byte value)
    {
        getIndexRegister<Register>() = value;
        updateSignFlags(value);
    }

    template<IndexRegister Register>
    Word& getIndexRegister()
    {
        return indexRegisters[Register];
    }

    template<IndexRegister Register>
    Word getIndexRegister() const
    {
        return indexRegisters[Register];
    }

    template<IndexRegister Register>
    static std::string getRegisterName()
    {
        std::string names[] = { "X", "Y" };
        return names[Register];
    }

    void setDirectPageRegister(Word value)
    {
        directPage = value;
        updateSignFlags(value);
    }

    void setRegisterDebug(char name, Word value)
    {
        switch (name) {
        case 'p':
            setProgramCounter(value);
            break;
        case 's':
            setStackPointer(value);
            break;
        case 'a':
            setAccumulatorC(value);
            break;
        case 'x':
            setIndexRegister<State::X>(value);
            break;
        case 'y':
            setIndexRegister<State::Y>(value);
            break;
        case 'd':
            setDirectPageRegister(value);
            break;
        case 'f':
            setFlags((Byte)value);
            break;
        default:
            break;
        }
    }

    void loadRom(const std::string& path, std::ostream& output);

private:
    bool tryReadHeader(int offset, std::vector<char> rom, std::ostream& output);

private:
    Byte accumulatorA;
    Byte accumulatorB;
    Byte dataBank;
    Word directPage;
    Word stackPointer;
    Byte programBank;
    Word programCounter;

    Word resetAddress;

    Byte flags;
    bool emulationMode;

    std::vector<Byte> memory;
    std::array<Word, IndexRegisterCount> indexRegisters;
};

}