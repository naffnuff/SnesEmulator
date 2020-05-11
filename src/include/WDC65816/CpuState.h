#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <bitset>
#include <iomanip>

#include "Output.h"
#include "Types.h"
#include "Memory.h"
#include "Util.h"

namespace CPU {

class State
{
public:
    typedef Long AddressType;
    typedef Memory<AddressType> MemoryType;
    typedef MemoryAccess<MemoryType> MemoryAccessType;
    typedef ConstMemoryAccess<MemoryType> ConstMemoryAccessType;

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

private:
    class Accumulator
    {
    public:
        Accumulator() = default;
        Accumulator(const Accumulator&) = delete;
        Accumulator& operator=(const Accumulator&) = delete;

        Byte readByte()
        {
            return accumulatorA;
        }

        Word readWord()
        {
            return getAccumulatorC();
        }

        void writeByte(Byte value)
        {
            accumulatorA = value;
        }
        
        void writeWord(Word value)
        {
            accumulatorA = value.getLowByte();
            accumulatorB = value.getHighByte();
        }

        void swap()
        {
            Byte newAccumulatorA = accumulatorB;
            accumulatorB = accumulatorA;
            accumulatorA = newAccumulatorA;
        }

        Byte getAccumulatorA() const
        {
            return accumulatorA;
        }

        Word getAccumulatorC() const
        {
            return Word(accumulatorA, accumulatorB);
        }

    private:
        Byte accumulatorA;
        Byte accumulatorB;
    };

public:
    class AccumulatorAccess : public Access
    {
    public:
        AccumulatorAccess(Accumulator& accumulator)
            : accumulator(accumulator)
        {
        }

        Byte readByte() override
        {
            return accumulator.readByte();
        }

        Word readWord() override
        {
            return accumulator.readWord();
        }

        void writeByte(Byte value) override
        {
            accumulator.writeByte(value);
        }

        void writeWord(Word value) override
        {
            accumulator.writeWord(value);
        }

    private:
        Accumulator& accumulator;
    };

    //static const size_t spcRegisterCount = 4;

    State()
    {
#ifdef DEBUGMEMORY
        for (int address = 0; address < memory.size(); ++address) {
            std::stringstream ss;
            ss << Long(address);
            memory[address].debugName = ss.str();
        }
#endif

        forceRegisters();
    }

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    void loadInterruptVectors()
    {
        nativeVectors.Coprocessor = memory.readWord<MemoryType::Bank>(0xFFE4);
        nativeVectors.Break = memory.readWord<MemoryType::Bank>(0xFFE6);
        nativeVectors.Abort = memory.readWord<MemoryType::Bank>(0xFFE8);
        nativeVectors.Nmi = memory.readWord<MemoryType::Bank>(0xFFEA);
        nativeVectors.Reset = memory.readWord<MemoryType::Bank>(0xFFEC);
        nativeVectors.Irq = memory.readWord<MemoryType::Bank>(0xFFEE);

        emulationVectors.Coprocessor = memory.readWord<MemoryType::Bank>(0xFFF4);
        emulationVectors.Break = memory.readWord<MemoryType::Bank>(0xFFF6);
        emulationVectors.Abort = memory.readWord<MemoryType::Bank>(0xFFF8);
        emulationVectors.Nmi = memory.readWord<MemoryType::Bank>(0xFFFA);
        emulationVectors.Reset = memory.readWord<MemoryType::Bank>(0xFFFC);
        emulationVectors.Irq = memory.readWord<MemoryType::Bank>(0xFFFE);
    }

    size_t getMemorySize() const
    {
        return memory.size();
    }

    void printRegisters(Output& output, Output::Lock& lock) const
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

        return output.print(lock,
            "PB=", programBank,
            ", PC=", programCounter,
            ", A=", getAccumulatorC(),
            ", X=", getIndexRegister<X>(),
            ", Y=", getIndexRegister<Y>(),
            ", S=", stackPointer,
            ", DP=", directPage,
            ", DB=", dataBank,
            ", flags=", flagSet, " (", flagsString, ", $", flags, ")",
            ", e=", emulationMode);
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

    Byte inspectProgramByte(int offset = 0) const
    {
        return memory.inspect(getProgramAddress(offset));
    }

    bool hasBreakpoint(int offset) const
    {
        return memory.hasBreakpoint(getProgramAddress(offset));
    }

    void applyBreakpoint(int offset) const
    {
        memory.applyBreakpoint(getProgramAddress(offset));
    }

    Byte applyProgramByte()
    {
        return memory.applyByte(Long(programCounter++, programBank));
    }

    void printProgramByte(int offset, std::ostream& out) const
    {
        memory.print(getProgramAddress(offset), out);
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

    AccumulatorAccess getAccumulatorAccess()
    {
        return AccumulatorAccess(accumulator);
    }

    Byte getAccumulatorA() const
    {
        return accumulator.getAccumulatorA();
    }

    Word getAccumulatorC() const
    {
        return accumulator.getAccumulatorC();
    }

    void setAccumulatorA(Byte value)
    {
        accumulator.writeByte(value);
        updateSignFlags(value);
    }

    void setAccumulatorC(Word value)
    {
        accumulator.writeWord(value);
        updateSignFlags(value);
    }

    void swapAccumulators()
    {
        accumulator.swap();
        updateSignFlags(accumulator.readByte());
    }

    Word getDirectPageRegister() const
    {
        return directPage;
    }

    template<typename LocationType, typename... Args>
    void createMemoryLocation(Long address, Args&&... args)
    {
        memory.createLocation<LocationType, Args...>(address, std::forward<Args>(args)...);
    }

    Byte readMemoryByte(Long address)
    {
        return memory.readByte(address);
    }

    void writeMemoryByte(Byte value, Long address)
    {
        memory.writeByte(value, address);
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::Full>
    Word readMemoryWord(Long address)
    {
        return memory.readWord<Wrapping>(address);
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::Full>
    Long readMemoryLong(Long address)
    {
        return memory.readLong<Wrapping>(address);
    }

    MemoryType& getMemory()
    {
        return memory;
    }

    const MemoryType& getMemory() const
    {
        return memory;
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::Full>
    MemoryAccessType getMemoryAccess(Long address, Word offset = 0)
    {
        return MemoryAccess(memory, Long(address + offset), Wrapping);
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::Full>
    ConstMemoryAccessType getConstMemoryAccess(Long address, Word offset = 0) const
    {
        return ConstMemoryAccessType(memory, Long(address + offset), Wrapping);
    }

    template<MemoryType::WrappingMask Wrapping  = MemoryType::Full>
    MemoryAccessType getMemoryAccess(Byte lowByte, Byte highByte, Byte bankByte, Word offset = 0)
    {
        return getMemoryAccess<Wrapping>(Long(lowByte, highByte, bankByte), offset);
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::Full>
    MemoryAccessType getMemoryAccess(Byte lowByte, Byte highByte)
    {
        return getMemoryAccess<Wrapping>(lowByte, highByte, dataBank);
    }

    MemoryAccessType getDirectMemoryAccess(Byte lowByte, Word offset = 0)
    {
        if (emulationMode && directPage.getLowByte() == 0) {
            return getMemoryAccess<MemoryType::Page>(lowByte + offset, directPage.getHighByte(), 0);
        }
        else {
            return getMemoryAccess<MemoryType::Bank>(Long(Word(directPage + lowByte + offset), 0));
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

    void pushToStack(Byte value)
    {
        memory.writeByte(value, Long(stackPointer, 0));
        --stackPointer;
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
        return memory.readByte(Long(stackPointer, 0));
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
        if (getFlag(x)) {
            updateSignFlags(Byte(value));
        }
        else {
            updateSignFlags(value);
        }
    }

    template<IndexRegister Register>
    void setIndexRegister(Byte value)
    {
        getIndexRegister<Register>() = Word(value, 0);
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

    void reset()
    {
        for (uint32_t i = 0; i < memory.size(); ++i) {
            memory.reset(i);
        }

        dataBank = 0;
        directPage = 0;
        stackPointer = 0;
        programBank = 0;
        programCounter = emulationVectors.Reset;
        flags = i;
        emulationMode = true;

        nmiActive = false;
        irqActive = false;

        // DMA Enable
        memory.writeByte(0, 0x420b);
        // HDMA Enable
        memory.writeByte(0, 0x420c);

        forceRegisters();
    }

private:
    Byte dataBank = 0;
    Word directPage = 0;
    Word stackPointer = 0;
    Byte programBank = 0;
    Word programCounter = 0;

    Byte flags = i;
    bool emulationMode = true;

    MemoryType memory;
    Accumulator accumulator;

    std::array<Word, IndexRegisterCount> indexRegisters;

    InterruptVectors nativeVectors;
    InterruptVectors emulationVectors;

    bool nmiActive = false;
    bool irqActive = false;
};

}