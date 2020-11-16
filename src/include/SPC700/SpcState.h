#pragma once

#include <sstream>
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

namespace SPC {

class State
{
public:
    typedef Word AddressType;
    typedef Memory<AddressType> MemoryType;
    typedef MemoryAccess<MemoryType> MemoryAccessType;
    typedef ConstMemoryAccess<MemoryType> ConstMemoryAccessType;

    enum class Flag
    {
        c = 1 << 0, // Carry
        z = 1 << 1, // Zero
        i = 1 << 2, // IRQ Disable
        h = 1 << 3, // 
        b = 1 << 4, // Break
        p = 1 << 5, // 
        v = 1 << 6, // Overflow
        n = 1 << 7  // Negative
    };

    enum class Register
    {
        A,
        Y,
        X,
        SP,
        PSW,
        Count
    };

private:
    class Registers
    {
    public:
        template<Register RegisterIndex>
        Byte readByte() const
        {
            return registers[size_t(RegisterIndex)];
        }

        template<Register RegisterIndex>
        Word readWord() const
        {
            return Word(registers[size_t(RegisterIndex)], registers[size_t(RegisterIndex) + 1]);
        }

        template<Register RegisterIndex>
        void writeByte(Byte value)
        {
            registers[size_t(RegisterIndex)] = value;
        }

        template<Register RegisterIndex>
        void writeWord(Word value)
        {
            registers[size_t(RegisterIndex)] = value.getLowByte();
            registers[size_t(RegisterIndex) + 1] = value.getHighByte();
        }

    private:
        std::array<Byte, size_t(Register::Count)> registers;
    };

public:
    template<Register RegisterIndex>
    class RegisterAccess : public Access
    {
    public:
        RegisterAccess(Registers& registers)//, Register registerIndex)
            : registers(registers)
            //, registerIndex(registerIndex)
        {
        }

        Byte readByte() override
        {
            return registers.readByte<RegisterIndex>();
        }

        Word readWord() override
        {
            return registers.readWord<RegisterIndex>();
        }

        void writeByte(Byte value) override
        {
            registers.writeByte<RegisterIndex>(value);
        }

        void writeWord(Word value) override
        {
            registers.writeWord<RegisterIndex>(value);
        }

    private:
        Registers& registers;
        //Register registerIndex;
    };

    State()
        : programCounter(0xffc0)
    {
        for (Word address = 0; address < 0xf0; ++address) {
            memory.createLocation<ReadWriteMemory>(address, Byte(0x55));
        }
        for (Word address = 0x100; address < 0xffc0; ++address) {
            memory.createLocation<ReadWriteMemory>(address, Byte(0x55));
        }
    }

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    void reset()
    {
        programCounter = 0xffc0;
        for (uint32_t i = 0; i < memory.size(); ++i) {
            memory.reset(Word(i));
        }
    }

    size_t getMemorySize() const
    {
        return memory.size();
    }

    void printRegisters(Output& output, Output::Lock& lock) const
    {
        std::string flagsString = "nvpbhizc";

        for (size_t i = 0; i < flagsString.size(); ++i) {
            if (readRegister<Register::PSW>() & 1 << i) {
                flagsString[flagsString.size() - i - 1] = (char)toupper(flagsString[flagsString.size() - i - 1]);
            }
        }

        std::bitset<8> flagSet(readRegister<Register::PSW>());

        output.print(lock,
            "PC=", programCounter,
            ", A=", readRegister<Register::A>(),
            ", X=", readRegister<Register::X>(),
            ", Y=", readRegister<Register::Y>(),
            ", S=", getStackPointer(),
            ", YA=", getYAccumulator(),
            ", flags=", flagSet, " (", flagsString, ", $", readRegister<Register::PSW>(), ")");
    }

    Word getProgramAddress(int offset = 0) const
    {
        return getProgramCounter(offset);
    }

    Word getProgramCounter(int offset = 0) const
    {
        return Word(int(programCounter) + offset);
    }

    void setProgramCounter(Word value)
    {
        programCounter = value;
    }

    void setProgramAddress(Word address)
    {
        setProgramCounter(address);
    }

    Byte inspectProgramByte(int offset = 0) const
    {
        return memory.inspect(getProgramAddress(offset));
    }

    Byte applyProgramByte()
    {
        return memory.applyByte(programCounter++);
    }

    template<typename LocationType, typename... Args>
    void createMemoryLocation(Word address, Args&&... args)
    {
        memory.createLocation<LocationType, Args...>(address, std::forward<Args>(args)...);
    }

    bool hasBreakpoint(int offset) const
    {
        return memory.hasBreakpoint(getProgramAddress(offset));
    }

    void applyBreakpoint(int offset) const
    {
        memory.applyBreakpoint(getProgramAddress(offset));
    }

    void printProgramByte(int offset, std::ostream& out) const
    {
        memory.print(getProgramAddress(offset), out);
    }
    
    void incrementProgramCounter(Word increment)
    {
        programCounter += increment;
    }

    Word getStackPointer() const
    {
        return 0x0100 | readRegister<Register::SP>();
    }

    Word getYAccumulator() const
    {
        return registers.readWord<Register::A>();
    }

    MemoryType& getMemory()
    {
        return memory;
    }

    Byte readMemoryByte(Word address)
    {
        return memory.readByte(address);
    }

    Byte readMemoryByte(Byte lowByte, Byte highByte)
    {
        return readMemoryByte(Word(lowByte, highByte));
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::WrappingMask::Full>
    Word readMemoryWord(Word address)
    {
        return memory.readWord<Wrapping>(address);
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::WrappingMask::Full>
    ConstMemoryAccessType getConstMemoryAccess(Word address) const
    {
        return ConstMemoryAccessType(memory, address, Wrapping);
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::WrappingMask::Full>
    MemoryAccessType getMemoryAccess(Word address)
    {
        return MemoryAccess(memory, address, Wrapping);
    }

    template<MemoryType::WrappingMask Wrapping = MemoryType::WrappingMask::Full>
    MemoryAccessType getMemoryAccess(Byte lowByte, Byte highByte)
    {
        return getMemoryAccess(Word(lowByte, highByte));
    }

    Word getDirectAddress(Byte lowByte) const
    {
        if (getFlag(Flag::p)) {
            return Word(lowByte, 0x01);
        }
        else {
            return Word(lowByte);
        }
    }

    Byte readDirectMemoryByte(Byte address)
    {
        return readMemoryByte(getDirectAddress(address));
    }

    Word readDirectMemoryWord(Byte address)
    {
        return readMemoryWord(getDirectAddress(address));
    }

    MemoryAccessType getDirectMemoryAccess(Byte address)
    {
        return getMemoryAccess(getDirectAddress(address));
    }

    template<Register RegisterIndex>
    RegisterAccess<RegisterIndex> getRegisterAccess()
    {
        return RegisterAccess<RegisterIndex>(registers);
    }

    template<Register RegisterIndex>
    Byte readRegister() const
    {
        return registers.readByte<RegisterIndex>();
    }

    template<Register RegisterIndex>
    void writeRegister(Byte value)
    {
        registers.writeByte<RegisterIndex>(value);
    }

    template<Register RegisterIndex>
    static std::string getRegisterName()
    {
        std::string names[] = { "A", "Y", "X", "SP", "PSW" };
        return names[size_t(RegisterIndex)];
    }

    template<Flag Flag>
    static std::string getFlagName()
    {
        std::string names[] = { "C", "Z", "I", "H", "B", "P", "V", "N" };
        for (int i = 0; i < 8; ++i) {
            if (1 << i == int(Flag)) {
                return names[i];
            }
        }
        return "";
    }

    void setFlag(Flag flag, bool value)
    {
        setMultipleFlags(uint8_t(flag), value);
    }

    void setMultipleFlags(Byte flags, bool value)
    {
        if (value) {
            writeRegister<Register::PSW>(readRegister<Register::PSW>() | flags);
        }
        else {
            writeRegister<Register::PSW>(readRegister<Register::PSW>() & ~flags);
        }
    }

    bool getFlag(Flag flag) const
    {
        return readRegister<Register::PSW>() & int(flag);
    }

    void setFlags(Byte value)
    {
        writeRegister<Register::PSW>(value);
    }

    template<typename T>
    void updateSignFlags(T value)
    {
        setFlag(State::Flag::z, value == 0);
        setFlag(State::Flag::n, value.isNegative());
    }

    void pushToStack(Byte byte)
    {
        Byte stackLowByte = registers.readByte<Register::SP>();
        MemoryAccess access = getMemoryAccess(stackLowByte, 0x01);
        registers.writeByte<Register::SP>(stackLowByte - 1);
        access.writeByte(byte);
    }

    void pushWordToStack(Word word)
    {
        pushToStack(word.getHighByte());
        pushToStack(word.getLowByte());
    }

    Byte pullFromStack()
    {
        Byte stackLowByte = registers.readByte<Register::SP>();
        MemoryAccess access = getMemoryAccess(++stackLowByte, 0x01);
        registers.writeByte<Register::SP>(stackLowByte);
        return access.readByte();
    }

    Word pullWordFromStack()
    {
        Byte lowByte = pullFromStack();
        Byte highByte = pullFromStack();
        return Word(lowByte, highByte);
    }

    void setRegisterDebug(char name, Word value)
    {
        switch (name) {
        case 'p':
            setProgramCounter(value);
            break;
        case 's':
            //setStackPointer(value);
            break;
        case 'a':
            //setAccumulatorC(value);
            break;
        case 'x':
            //setIndexRegister<State::X>(value);
            break;
        case 'y':
            //setIndexRegister<State::Y>(value);
            break;
        case 'd':
            //setDirectPageRegister(value);
            break;
        case 'f':
            setFlags((Byte)value);
            break;
        default:
            break;
        }
    }

private:
    Word programCounter;

    MemoryType memory;
    Registers registers;
};

}