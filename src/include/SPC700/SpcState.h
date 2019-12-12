#pragma once

#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <bitset>
#include <iomanip>

#include "Types.h"
#include "MemoryLocation.h"
#include "Util.h"

namespace SPC {

class State
{
public:
    enum Flag
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

    enum Register
    {
        A,
        Y,
        X,
        SP,
        PSW,
        RegisterCount
    };

    State()
        : programCounter(0xffc0)
        , memory(Word::spaceSize, MemoryLocation(0xff, std::bind(&State::debugNameQuery, this, std::placeholders::_1)))
    {
        for (MemoryLocation& r : registers) {
            r.setReadWrite();
        }

        for (size_t address = 0; address < 0xf0; ++address) {
            memory[address].setReadWrite();
        }
        for (size_t address = 0x100; address < 0xffc0; ++address) {
            memory[address].setReadWrite();
        }

        /*for (size_t address = 0xf1; address < 0xf3; ++address) {
            memory[address].setWriteOnly();
        }
        for (size_t address = 0xfa; address < 0xfb; ++address) {
            memory[address].setWriteOnly();
        }

        for (size_t address = 0xfd; address < 0xfe; ++address) {
            memory[address].setReadOnlyValue(0);
        }

        for (size_t address = 0xf3; address < 0xf4; ++address) {
            memory[address].setReadWrite();
            memory[address].setValue(0);
        }*/
    }

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    std::string debugNameQuery(const MemoryLocation* memoryLocation)
    {
        std::stringstream ss;
        for (int i = 0; i < memory.size(); ++i) {
            if (&memory[i] == memoryLocation) {
                ss << Long(i);
                break;
            }
        }
        return ss.str();
    }

    void reset()
    {
        programCounter = 0xffc0;
        for (int i = 0; i < memory.size(); ++i) {
            //memory[i].reset();
        }
    }

    size_t getMemorySize() const
    {
        return memory.size();
    }

    std::ostream& printRegisters(std::ostream& output) const
    {
        std::string flagsString = "nvpbhizc";

        for (size_t i = 0; i < flagsString.size(); ++i) {
            if (getRegisterValue<PSW>() & 1 << i) {
                flagsString[flagsString.size() - i - 1] = toupper(flagsString[flagsString.size() - i - 1]);
            }
        }

        std::bitset<8> flagSet(getRegisterValue<PSW>());

        return output
            << "PC=" << programCounter
            << ", A=" << getRegisterValue<A>()
            << ", X=" << getRegisterValue<X>()
            << ", Y=" << getRegisterValue<Y>()
            << ", S=" << getStackPointer()
            << ", YA=" << getYAccumulator()
            << ", flags=" << flagSet << " (" << flagsString << ", $" << getRegisterValue<PSW>() << ")";
    }

    Long getProgramAddress(int offset = 0) const
    {
        return programCounter + offset;
    }

    Word getProgramCounter(int offset = 0) const
    {
        return programCounter + offset;
    }

    void setProgramCounter(Word value)
    {
        programCounter = value;
    }

    void setProgramAddress(Long address)
    {
        setProgramCounter(Word(address));
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

    Word getStackPointer() const
    {
        return 0x0100 | getRegisterValue<SP>();
    }

    Word getYAccumulator() const
    {
        return registers[A].getWordValue();
    }

    Byte getMemoryByte(Word address) const
    {
        return memory[address].getValue();
    }

    Byte getMemoryByte(Byte lowByte, Byte highByte) const
    {
        return getMemoryByte(Word(lowByte, highByte));
    }

    Word getMemoryWord(Word address) const
    {
        return memory[address].getWordValue();
    }

    MemoryLocation* getMemoryLocation(Word address)
    {
        return &memory[address];
    }

    MemoryLocation* getMemoryLocation(Byte lowByte, Byte highByte)
    {
        return getMemoryLocation(Word(lowByte, highByte));
    }

    MemoryLocation* getMemoryLocation(Long address)
    {
        return &memory[address];
    }

    Word getDirectAddress(Byte lowByte) const
    {
        if (getFlag(p)) {
            return Word(lowByte, 0x01);
        }
        else {
            return Word(lowByte);
        }
    }

    Byte getDirectMemoryByte(Byte address) const
    {
        return getMemoryByte(getDirectAddress(address));
    }

    Word getDirectMemoryWord(Byte address) const
    {
        return getMemoryWord(getDirectAddress(address));
    }

    MemoryLocation* getDirectMemoryLocation(Byte address)
    {
        return getMemoryLocation(getDirectAddress(address));
    }

    const MemoryLocation& getMemory(Long address) const
    {
        return memory[address];
    }

    template<Register RegisterIndex>
    MemoryLocation* getRegister()
    {
        return &registers[RegisterIndex];
    }

    template<Register RegisterIndex>
    Byte getRegisterValue() const
    {
        return registers[RegisterIndex].getValue();
    }

    template<Register RegisterIndex>
    static std::string getRegisterName()
    {
        std::string names[] = { "A", "Y", "X", "SP", "PSW" };
        return names[RegisterIndex];
    }

    template<Flag Flag>
    static std::string getFlagName()
    {
        std::string names[] = { "C", "Z", "I", "H", "B", "P", "V", "N" };
        for (int i = 0; i < 8; ++i) {
            if (1 << i == Flag) {
                return names[i];
            }
        }
        return "";
    }

    void setFlag(Byte flag, bool value)
    {
        if (value) {
            getRegister<PSW>()->setValue(getRegisterValue<PSW>() | flag);
        }
        else {
            getRegister<PSW>()->setValue(getRegisterValue<PSW>() & ~flag);
        }
    }

    bool getFlag(Flag flag) const
    {
        return getRegisterValue<PSW>() & flag;
    }

    void setFlags(Byte value)
    {
        getRegister<PSW>()->setValue(value);
    }

    template<typename T>
    void updateSignFlags(T value)
    {
        setFlag(State::z, value == 0);
        setFlag(State::n, value.isNegative());
    }

    void pushToStack(Byte byte)
    {
        Byte stackLowByte = registers[SP].getValue();
        MemoryLocation* memory = getMemoryLocation(stackLowByte, 0x01);
        registers[SP].setValue(stackLowByte - 1);
        memory->setValue(byte);
    }

    void pushWordToStack(Word word)
    {
        pushToStack(word.getHighByte());
        pushToStack(word.getLowByte());
    }

    Byte pullFromStack()
    {
        Byte stackLowByte = registers[SP].getValue();
        MemoryLocation* memory = getMemoryLocation(++stackLowByte, 0x01);
        registers[SP].setValue(stackLowByte);
        return memory->getValue();
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

    std::vector<MemoryLocation> memory;
    std::array<MemoryLocation, RegisterCount> registers = {
        MemoryLocation(0, [](const MemoryLocation*) { return "SPC State Accumulator"; }),
        MemoryLocation(0, [](const MemoryLocation*) { return "SPC State Index Register Y"; }),
        MemoryLocation(0, [](const MemoryLocation*) { return "SPC State Index Register X"; }),
        MemoryLocation(0, [](const MemoryLocation*) { return "SPC State Stack Pointer"; }),
        MemoryLocation(0, [](const MemoryLocation*) { return "SPC State Flags"; })
    };
};

}