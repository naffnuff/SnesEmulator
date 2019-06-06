#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <bitset>
#include <iomanip>
#include <condition_variable>

#include "Types.h"
#include "MemoryLocation.h"
#include "Util.h"

namespace CPU {

class State
{
public:
    struct InterruptVectors
    {
        Word Coprocessor;
        Word Break;
        Word Abort;
        Word Nmi;
        Word Reset;
        Word Irq;
    };

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

    //static const size_t spcRegisterCount = 4;

    State()
        : memory(0x1000000, MemoryLocation(0x55))
    {
        std::cout << "Memory size=" << memory.size() << std::endl;
        forceRegisters();

        for (MemoryLocation& a : accumulator) {
            a.setReadWrite();
        }
    }

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    void loadInterruptVectors()
    {
        nativeVectors.Coprocessor = memory[0xFFE4].getWordValue();
        nativeVectors.Break = memory[0xFFE6].getWordValue();
        nativeVectors.Abort = memory[0xFFE8].getWordValue();
        nativeVectors.Nmi = memory[0xFFEA].getWordValue();
        nativeVectors.Reset = memory[0xFFEC].getWordValue();
        nativeVectors.Irq = memory[0xFFEE].getWordValue();

        emulationVectors.Coprocessor = memory[0xFFF4].getWordValue();
        emulationVectors.Break = memory[0xFFF6].getWordValue();
        emulationVectors.Abort = memory[0xFFF8].getWordValue();
        emulationVectors.Nmi = memory[0xFFFA].getWordValue();
        emulationVectors.Reset = memory[0xFFFC].getWordValue();
        emulationVectors.Irq = memory[0xFFFE].getWordValue();
    }

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
        Byte oldFlags = flags;
        if (value) {
            flags |= flag;
        } else {
            flags &= ~flag;
        }
        if (oldFlags != flags) {
            forceRegisters();
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

    Byte getProgramBank() const
    {
        return programBank;
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

    MemoryLocation* getDirectMemoryLocation(Byte lowByte, Word offset = 0)
    {
        if (emulationMode && directPage.getLowByte() == 0) {
            return getMemoryLocation(Long(lowByte + offset, directPage.getHighByte(), 0));
        }
        else {
            return getMemoryLocation(Long(Word(directPage + lowByte + offset), 0));
        }
    }

    void exchangeCarryAndEmulationFlags()
    {
        forceRegisters();

        bool carry = emulationMode;
        emulationMode = getFlag(c);
        setFlag(c, carry);

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

    void setProgramCounter(Word address, Byte bank)
    {
        programCounter = address;
        programBank = bank;
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

    Word getStackPointer() const
    {
        return stackPointer;
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

    template<Flag Flag>
    static std::string getFlagName()
    {
        std::string names[] = { "C", "Z", "I", "D", "X", "M", "V", "N" };
        for (int i = 0; i < 8; ++i) {
            if (1 << i == Flag) {
                return names[i];
            }
        }
        return "";
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

    void setDataBank(Byte value)
    {
        dataBank = value;
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

    void startInterrupt(bool isNmi)
    {
        pushToStack(programBank);
        programBank = 0x00;

        pushWordToStack(programCounter);

        pushToStack(flags);

        if (isNmi) {
            programCounter = getInterruptVectors(isNativeMode()).Nmi;
            nmiActive = true;
            setFlag(i, true);
        }
        else {
            programCounter = getInterruptVectors(isNativeMode()).Irq;
            irqActive = true;
        }

        setFlag(d, false);
    }

    void endInterrupt()
    {
        setFlags(pullFromStack());
        programCounter = pullWordFromStack();
        programBank = pullFromStack();

        if (nmiActive) {
            nmiActive = false;
        }
        else if (irqActive) {
            irqActive = false;
        }
        else {
            throw std::logic_error("End interrupt with neither nmi not irq ongoing");
        }
    }

    bool isNmiActive() const
    {
        return nmiActive;
    }

    bool isIrqActive() const
    {
        return irqActive;
    }

    InterruptVectors& getInterruptVectors(bool native)
    {
        if (native) {
            return nativeVectors;
        }
        else {
            return emulationVectors;
        }
    }

    std::vector<MemoryLocation>& accessMemory()
    {
        return memory;
    }

    void reset()
    {
        for (int i = 0; i < memory.size(); ++i) {
            memory[i].reset();
        }

        dataBank = 0;
        directPage = 0;
        stackPointer = 0;
        programBank = 0;
        programCounter = emulationVectors.Reset;
        flags = 0;
        emulationMode = true;

        nmiActive = false;
        irqActive = false;

        for (MemoryLocation& a : accumulator) {
            a.reset();
        }

        for (Word& r : indexRegisters) {
            r = 0;
        }

        forceRegisters();
    }

private:
    Byte dataBank = 0;
    Word directPage = 0;
    Word stackPointer = 0;
    Byte programBank = 0;
    Word programCounter = 0;

    Byte flags = 0;
    bool emulationMode = true;

    std::vector<MemoryLocation> memory;
    std::array<MemoryLocation, 2> accumulator;
    std::array<Word, IndexRegisterCount> indexRegisters;

    InterruptVectors nativeVectors;
    InterruptVectors emulationVectors;

    bool nmiActive = false;
    bool irqActive = false;
};

}