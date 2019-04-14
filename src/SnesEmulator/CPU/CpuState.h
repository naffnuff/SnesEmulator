#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <map>
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

    static const size_t spcRegisterCount = 4;

    State()
        : emulationMode(true)
        , memory(1 << 24, MemoryLocation(0x42))
    {
        std::cout << "Memory size=" << memory.size() << std::endl;
        forceRegisters();

        for (MemoryLocation& a : accumulator) {
            a.setReadWrite();
        }
        //for (Byte bank = 0; bank < 0x40; ++bank) {
        for (size_t address = 0; address < 0x2000; ++address) {
            memory[address].setReadWrite();
        }
        //}
        for (size_t address = 0x2100; address < 0x2101; ++address) {
            memory[address].setWriteOnly();
        }
        for (size_t address = 0x4200; address < 0x4201; ++address) {
            memory[address].setWriteOnly();
        }
        for (size_t address = 0x420b; address < 0x420d; ++address) {
            memory[address].setWriteOnly();
        }
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
        forceRegisters();
    }

    Byte getFlags() const
    {
        return flags;
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
        return memory[getProgramAddress(offset)].getValue();
    }

    Byte applyProgramByte(int offset = 0)
    {
        return memory[getProgramAddress(offset)].apply();
    }

    void reset(Word resetAddress)
    {
        programCounter = resetAddress;
    }

    void incrementProgramCounter(Word increment)
    {
        programCounter += increment;
    }

    Long getProgramAddress(int offset = 0) const
    {
        return Long(programCounter, programBank) + offset;
    }

    Word getProgramCounter(int offset = 0) const
    {
        return programCounter + offset;
    }

    MemoryLocation* getAccumulatorPointer()
    {
        return accumulator.data();
    }

    Byte getAccumulatorA() const
    {
        return accumulator[0].getValue();
    }

    Byte getAccumulatorB() const
    {
        return accumulator[1].getValue();
    }

    void setAccumulatorA(Byte value)
    {
        accumulator[0].setValue(value);
        updateSignFlags(value);
    }

    void setAccumulatorC(Word value)
    {
        accumulator[0].setWordValue(value);
        updateSignFlags(value);
    }

    Word getAccumulatorC() const
    {
        return Word(accumulator[0].getValue(), accumulator[1].getValue());
    }

    Word getDirectPage() const
    {
        return directPage;
    }

    Byte getMemoryByte(Long address) const
    {
        return memory[address].getValue();
    }

    const MemoryLocation& getMemory(Long address) const
    {
        return memory[address];
    }

    MemoryLocation* getMemoryLocation(Long address)
    {
        return &memory[address];
    }

    MemoryLocation* getMemoryLocation(Byte lowByte, Byte highByte, Byte bankByte, Word offset = 0)
    {
        return getMemoryLocation(Long(Long(lowByte, highByte, bankByte) + offset));
    }

    MemoryLocation* getMemoryLocation(Byte lowByte, Byte highByte)
    {
        return getMemoryLocation(lowByte, highByte, dataBank);
    }

    MemoryLocation* getMemoryLocation(Byte lowByte)
    {
        return getMemoryLocation(Long(directPage + lowByte));
    }

    void exchangeCarryAndEmulationFlags()
    {
        forceRegisters();

        bool emulation = emulationMode;
        emulationMode = getFlag(c);
        setFlag(c, emulation);

        forceRegisters();
    }

    void forceRegisters()
    {
        if (emulationMode) {
            setFlag(x | m, true);
            ((Byte*)(&stackPointer))[1] = 1;
        }
        if (getFlag(x)) {
            ((Byte*)(&getIndexRegister<X>()))[1] = 0;
            ((Byte*)(&getIndexRegister<Y>()))[1] = 0;
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
        memory[stackPointer--].setValue(byte);
        forceRegisters();
    }

    void pushWordToStack(Word word)
    {
        pushToStack(word.getHighByte());
        pushToStack(word.getLowByte());
    }

    Byte pullFromStack()
    {
        ++stackPointer;
        forceRegisters();
        return memory[stackPointer].getValue();
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

    void setProgramAddress(Long value)
    {
        setProgramCounter(Word(value), Byte(value >> 16));
    }

    void setStackPointer(Word value)
    {
        stackPointer = value;
        forceRegisters();
    }

    template<IndexRegister Register>
    void setIndexRegister(Word value)
    {
        getIndexRegister<Register>() = value;
        forceRegisters();
        updateSignFlags(value);
    }

    template<IndexRegister Register>
    void setIndexRegister(Byte value)
    {
        getIndexRegister<Register>() = Word(value);
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
    static std::string getIndexRegisterName()
    {
        std::string names[] = { "X", "Y" };
        return names[Register];
    }

    void setDirectPageRegister(Word value)
    {
        directPage = value;
        updateSignFlags(value);
    }

    Byte getDataBank() const
    {
        return dataBank;
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

private:
    Byte dataBank;
    Word directPage;
    Word stackPointer;
    Byte programBank;
    Word programCounter;

    Byte flags;
    bool emulationMode;

    std::vector<MemoryLocation> memory;
    std::array<MemoryLocation, 2> accumulator;
    std::array<Word, IndexRegisterCount> indexRegisters;
};

}