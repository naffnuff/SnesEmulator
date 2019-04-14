#pragma once


#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <bitset>
#include <iomanip>

#include "../Types.h"
#include "../Util.h"

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
        : programCounter(0xFFC0)
        , memory(1 << 16, MemoryLocation(0xFF))
    {
        std::array<Byte, 64> bootRomData = {
           0xCD, 0xEF, 0xBD, 0xE8, 0x00, 0xC6, 0x1D, 0xD0, 0xFC, 0x8F, 0xAA, 0xF4, 0x8F, 0xBB, 0xF5, 0x78,
           0xCC, 0xF4, 0xD0, 0xFB, 0x2F, 0x19, 0xEB, 0xF4, 0xD0, 0xFC, 0x7E, 0xF4, 0xD0, 0x0B, 0xE4, 0xF5,
           0xCB, 0xF4, 0xD7, 0x00, 0xFC, 0xD0, 0xF3, 0xAB, 0x01, 0x10, 0xEF, 0x7E, 0xF4, 0x10, 0xEB, 0xBA,
           0xF6, 0xDA, 0x00, 0xBA, 0xF4, 0xC4, 0xF4, 0xDD, 0x5D, 0xD0, 0xDB, 0x1F, 0x00, 0x00, 0xC0, 0xFF,
        };

        for (size_t i = 0; i < bootRomData.size(); ++i) {
            memory[programCounter + i].setReadOnlyValue(bootRomData[i]);
        }

        for (MemoryLocation& r : registers) {
            r.setReadWrite();
        }

        for (size_t address = 0; address < 0xf0; ++address) {
            memory[address].setReadWrite();
        }
        for (size_t address = 0x100; address < 0xFFC0; ++address) {
            memory[address].setReadWrite();
        }

        for (size_t address = 0xf2; address < 0xf3; ++address) {
            memory[address].setWriteOnly();
        }

        for (size_t address = 0xf3; address < 0xf4; ++address) {
            memory[address].setReadWrite();
            memory[address].setValue(0);
        }
    }

    State(State&) = delete;
    State& operator=(State&) = delete;

    /*std::ostream& printMemoryPage(std::ostream& output, Long startAddress) const
    {
        output << "       0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        Long address = startAddress - std::bitset<4>(startAddress).to_ulong();
        for (int i = 0; i < 16 && address < memory.size(); ++i) {
            Word lowAddress = Word(address);
            lowAddress = lowAddress >> 4;
            output << std::setw(3) << std::setfill('0') << lowAddress << "x  ";

            for (int j = 0; j < 16 && address < memory.size(); ++j) {
                output << memory[address++] << ' ';
            }

            output << std::endl;
        }
        return output;
    }*/

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

    Byte getDirectMemoryByte(Byte address) const
    {
        return getMemoryByte(Word(address));
    }

    Word getMemoryWord(Word address) const
    {
        return memory[address].getWordValue();
    }

    Word getDirectMemoryWord(Byte address) const
    {
        return getMemoryWord(Word(address));
    }

    MemoryLocation* getMemoryLocation(Word address)
    {
        return &memory[address];
    }

    MemoryLocation* getMemoryLocation(Byte lowByte, Byte highByte)
    {
        return getMemoryLocation(Word(lowByte, highByte));
    }

    MemoryLocation* getDirectMemoryLocation(Byte address)
    {
        return getMemoryLocation(Word(address));
    }

    MemoryLocation* getMemoryLocation(Long address)
    {
        return &memory[address];
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
            if (1 << i == 1) {
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
        MemoryLocation* memory = getMemoryLocation(registers[SP].get()--, 0x01);
        memory->setValue(byte);
    }

    void pushWordToStack(Word word)
    {
        pushToStack(word.getHighByte());
        pushToStack(word.getLowByte());
    }

    Byte pullFromStack()
    {
        MemoryLocation* memory = getMemoryLocation(++registers[SP].get(), 0x01);
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
    std::array<MemoryLocation, RegisterCount> registers;
};

}