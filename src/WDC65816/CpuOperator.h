#pragma once

#include "Exception.h"
#include "CpuState.h"

#include "Profiler.h"

#define PROFILE_OPERATORS false

namespace CPU {

namespace Operator {

EXCEPTION(NotYetImplementedException, ::NotYetImplementedException);

CREATE_PROFILER();

// ADC Add With Carry [Flags affected: n,v,z,c]
class ADC
{
private:
    template<typename T>
    static T add(State& state, T accumulator, T memory)
    {
        T result;
        bool carry = state.getFlag(State::Flag::c);
        bool overflow = false;
        if (state.getFlag(State::Flag::d))
        {
            result = Types::decimalAdd(accumulator, memory, carry, overflow);
        }
        else
        {
            bool dummy = false;
            result = Types::binaryAdd(accumulator, memory, carry, overflow, dummy);
        }
        state.setFlag(State::Flag::c, carry);
        state.setFlag(State::Flag::v, overflow);
        return result;
    }

public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ADC");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            state.setAccumulatorA(add(state, state.getAccumulatorA(), access.readByte()));
            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ADC 16-bit");

        state.setAccumulatorC(add(state, state.getAccumulatorC(), access.readWord()));
        return 1;
    }

    static std::string toString() { return "ADC"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
class AND
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "AND");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            state.setAccumulatorA(state.getAccumulatorA() & access.readByte());
            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "AND 16-Bit");

        state.setAccumulatorC(state.getAccumulatorC() & access.readWord());
        return 1;
    }

    static std::string toString() { return "AND"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
class ASL
{
private:
    template<typename T>
    static T arithmeticShiftLeft(State& state, T value)
    {
        state.setFlag(State::Flag::c, value.isNegative());
        value <<= 1;
        state.updateSignFlags(value);
        return value;
    }

public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ASL");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 2;
            access.writeWord(arithmeticShiftLeft(state, access.readWord()));
        }
        else
        {
            access.writeByte(arithmeticShiftLeft(state, access.readByte()));
        }
        return cycles;
    }

    static std::string toString() { return "ASL"; }
};

static int branchIf(bool condition, State& state, int offset)
{
    int cycles = 0;
    if (condition)
    {
        Word newAddress = state.getProgramCounter(offset);
        cycles += 1;
        if (!state.isNativeMode())
        {
            Byte programPage = state.getProgramCounter() >> 8;
            Byte newAddressPage = newAddress >> 8;
            if (programPage != newAddressPage)
            {
                cycles += 1;
            }
        }
        state.setProgramCounter(newAddress);
    }
    return cycles;
}

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
class BCC
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BCC");

        return branchIf(!state.getFlag(State::Flag::c), state, offset);
    }

    static std::string toString() { return "BCC"; }
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
class BCS
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BCS");

        return branchIf(state.getFlag(State::Flag::c), state, offset);
    }

    static std::string toString() { return "BCS"; }
};

// BEQ Branch if Equal [Flags affected: none]
class BEQ
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BEQ");

        return branchIf(state.getFlag(State::Flag::z), state, offset);
    }

    static std::string toString() { return "BEQ"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
template<bool ImmediateMode>
class BIT
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BIT");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            bool zFlag = false;
            bool nFlag = false;
            bool vFlag = false;

            Byte data = access.readByte();
            nFlag = data.isNegative();
            vFlag = data.getBit(6);
            zFlag = (state.getAccumulatorA() & data) == 0;

            if (!ImmediateMode)
            {
                state.setFlag(State::Flag::n, nFlag);
                state.setFlag(State::Flag::v, vFlag);
            }
            state.setFlag(State::Flag::z, zFlag);

            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BIT 16-Bit");

        bool zFlag = false;
        bool nFlag = false;
        bool vFlag = false;

        Word data = access.readWord();
        nFlag = data.isNegative();
        vFlag = data.getBit(14);
        zFlag = (state.getAccumulatorC() & data) == 0;

        if (!ImmediateMode)
        {
            state.setFlag(State::Flag::n, nFlag);
            state.setFlag(State::Flag::v, vFlag);
        }
        state.setFlag(State::Flag::z, zFlag);

        return 1;
    }

    static std::string toString() { return "BIT"; }
};

// BMI Branch if Minus [Flags affected: none]
class BMI
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BMI");

        return branchIf(state.getFlag(State::Flag::n), state, offset);
    }

    static std::string toString() { return "BMI"; }
};

// BNE Branch if Not Equal [Flags affected: none]
class BNE
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BNE");

        return branchIf(!state.getFlag(State::Flag::z), state, offset);
    }

    static std::string toString() { return "BNE"; }
};

// BPL Branch if Plus [Flags affected: none]
class BPL
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BPL");

        return branchIf(!state.getFlag(State::Flag::n), state, offset);
    }

    static std::string toString() { return "BPL"; }
};

// BRA Branch Always [Flags affected: none]
class BRA
{
public:
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BRA");

        return branchIf(true, state, offset);
    }

    static std::string toString() { return "BRA"; }
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
class BRK
{
public:
    // §9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state, const Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BRK");

        throw NotYetImplementedException("BRK");
        int cycles = 0;
        if (state.isNativeMode())
        {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "BRK"; }
};

// BRL Branch Long Always [Flags affected: none]
class BRL
{
public:
    static int invoke(State& state, int16_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BRL");

        return branchIf(true, state, offset);
    }

    static std::string toString() { return "BRL"; }
};

// BVC Branch if Overflow Clear [Flags affected: none]
class BVC
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BVC");

        return branchIf(!state.getFlag(State::Flag::v), state, offset);
    }

    static std::string toString() { return "BVC"; }
};

// BVS Branch if Overflow Set [Flags affected: none]
class BVS
{
public:
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "BVS");

        return branchIf(state.getFlag(State::Flag::v), state, offset);
    }

    static std::string toString() { return "BVS"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
class CMP
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "CMP");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            Byte accumulator = state.getAccumulatorA();
            Byte data = access.readByte();
            state.setFlag(State::Flag::c, accumulator >= data);
            state.updateSignFlags(Byte(accumulator - data));
            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "CMP 16-Bit");

        Word accumulator = state.getAccumulatorC();
        Word data = access.readWord();
        state.setFlag(State::Flag::c, accumulator >= data);
        state.updateSignFlags(Word(accumulator - data));
        return 1;
    }

    static std::string toString() { return "CMP"; }
};

// COP Co-Processor Enable [Flags affected: d,i]
class COP
{
public:
    // §9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state, const Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "COP");

        throw NotYetImplementedException("COP");
        int cycles = 0;
        if (state.isNativeMode())
        {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "COP"; }
};

// CPX/Y Compare Index Register X/Y with Memory [Flags affected: n,z,c]
template<State::IndexRegister Register>
class CP_
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "CP_");

        if (state.is16Bit(State::Flag::x))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            Byte indexRegister(state.getIndexRegister<Register>());
            Byte data = access.readByte();
            state.setFlag(State::Flag::c, indexRegister >= data);
            state.updateSignFlags(Byte(indexRegister - data));
            return 0;
        }
    }

    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "CPX/Y 16-Bit");

        Word indexRegister = state.getIndexRegister<Register>();
        Word data = access.readWord();
        state.setFlag(State::Flag::c, indexRegister >= data);
        state.updateSignFlags(Word(indexRegister - data));
        return 1;
    }

    static std::string toString() { return "CP" + State::getIndexRegisterName<Register>(); }
};

// DEC Decrement [Flags affected: n,z]
class DEC
{
public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "DEC");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 2;
            Word value = access.readWord() - 1;
            access.writeWord(value);
            state.updateSignFlags(value);
        }
        else
        {
            Byte value = access.readByte() - 1;
            access.writeByte(value);
            state.updateSignFlags(value);
        }
        return cycles;
    }

    static std::string toString() { return "DEC"; }
};

// DEX/Y Decrement Index Register X/Y [Flags affected: n,z]
template<State::IndexRegister Register>
class DE_
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "DE_");

        int cycles = 0;
        if (state.is16Bit(State::Flag::x))
        {
            cycles += 2;
            Word& indexRegister = state.getIndexRegister<Register>();
            state.updateSignFlags(--indexRegister);
        }
        else
        {
            Byte& indexRegister = (Byte&)state.getIndexRegister<Register>();
            state.updateSignFlags(--indexRegister);
        }
        return 0;
    }

    static std::string toString() { return "DE" + State::getIndexRegisterName<Register>(); }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
class EOR
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "EOR");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            state.setAccumulatorA(state.getAccumulatorA() ^ access.readByte());
            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "EOR 16-Bit");

        state.setAccumulatorC(state.getAccumulatorC() ^ access.readWord());
        return 1;
    }

    static std::string toString() { return "EOR"; }
};

// INC Increment [Flags affected: n,z]
class INC
{
public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "INC");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 2;
            Word value = access.readWord() + 1;
            access.writeWord(value);
            state.updateSignFlags(value);
        }
        else
        {
            Byte value = access.readByte() + 1;
            access.writeByte(value);
            state.updateSignFlags(value);
        }
        return cycles;
    }

    static std::string toString() { return "INC"; }
};

// INX/Y Increment Index Register X/Y [Flags affected: n,z]
template<State::IndexRegister Register>
class IN_
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "IN_");

        if (state.is16Bit(State::Flag::x))
        {
            Word& indexRegister = state.getIndexRegister<Register>();
            state.updateSignFlags(++indexRegister);
        }
        else
        {
            Byte& indexRegister = (Byte&)state.getIndexRegister<Register>();
            state.updateSignFlags(++indexRegister);
        }
        return 0;
    }

    static std::string toString() { return "IN" + State::getIndexRegisterName<Register>(); }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
class JMP
{
public:
    static int invoke(State& state, Word address)
    {
        PROFILE_IF(PROFILE_OPERATORS, "JMP");

        state.setProgramCounter(address);
        return 0;
    }

    static std::string toString() { return "JMP"; }
};

class JML
{
public:
    static int invoke(State& state, Long address)
    {
        PROFILE_IF(PROFILE_OPERATORS, "JML");

        state.setProgramAddress(address);
        return 0;
    }

    static std::string toString() { return "JML"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
class JSR
{
public:
    static int invoke(State& state, Word address)
    {
        PROFILE_IF(PROFILE_OPERATORS, "JSR");

        state.pushWordToStack(state.getProgramCounter(-1));
        state.setProgramCounter(address);
        return 0;
    }

    static std::string toString() { return "JSR"; }
};

class JSL
{
public:
    static int invoke(State& state, Long address)
    {
        PROFILE_IF(PROFILE_OPERATORS, "JSL");

        state.pushToStack(state.getProgramBank());
        state.pushWordToStack(state.getProgramCounter(-1));
        state.setProgramAddress(address);
        return 0;
    }

    static std::string toString() { return "JSL"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
class LDA
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "LDA");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            state.setAccumulatorA(access.readByte());
            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "LDA 16-Bit");

        state.setAccumulatorC(access.readWord());
        return 1;
    }

    static std::string toString() { return "LDA"; }
};

// LDX/Y Load Index Register X/Y from Memory [Flags affected: n,z]
template<State::IndexRegister Register>
class LD_
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "LD_");

        if (state.is16Bit(State::Flag::x))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            state.setIndexRegister<Register>(access.readByte());
            return 0;
        }
    }

    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "LD_ 16-Bit");

        state.setIndexRegister<Register>(access.readWord());
        return 1;
    }

    static std::string toString() { return "LD" + State::getIndexRegisterName<Register>(); }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
class LSR
{
private:
    template<typename T>
    static T logicalShiftLeft(State& state, T value)
    {
        state.setFlag(State::Flag::c, value.getBit(0));
        value >>= 1;
        state.updateSignFlags(value);
        return value;
    }

public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "LSR");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 2;
            access.writeWord(logicalShiftLeft(state, access.readWord()));
        }
        else
        {
            access.writeByte(logicalShiftLeft(state, access.readByte()));
        }
        return cycles;
    }

    static std::string toString() { return "LSR"; }
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
class MVN
{
public:
    // §13: 7 cycles per byte moved
    static int invoke(State& state, Byte sourceBank, Byte destinationBank, Word byteCount)
    {
        PROFILE_IF(PROFILE_OPERATORS, "MVN");

        Word sourceAddress = state.getIndexRegister<State::IndexRegister::X>();
        Word destinationAddress = state.getIndexRegister<State::IndexRegister::Y>();
        
        Byte value = state.readMemoryByte(Long(sourceAddress, sourceBank));
        state.writeMemoryByte(value, Long(destinationAddress, destinationBank));

        state.setIndexRegister<State::IndexRegister::X>(Word(sourceAddress + 1));
        state.setIndexRegister<State::IndexRegister::Y>(Word(destinationAddress + 1));
        return 0;
    }

    static std::string toString() { return "MVN"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
class MVP
{
public:
    // §13: 7 cycles per byte moved
    static int invoke(State& state, Byte sourceBank, Byte destinationBank, Word byteCount)
    {
        PROFILE_IF(PROFILE_OPERATORS, "MVP");

        throw NotYetImplementedException("MVP");
        return 0;
    }

    static std::string toString() { return "MVP"; }
};

// NOP No Operation [Flags affected: none]
class NOP
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "NOP");

        return 0;
    }

    static std::string toString() { return "NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
class ORA
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ORA");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            state.setAccumulatorA(state.getAccumulatorA() | access.readByte());
            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ORA 16-Bit");

        state.setAccumulatorC(state.getAccumulatorC() | access.readWord());
        return 1;
    }

    static std::string toString() { return "ORA"; }
};

// PEA/I Push Effective Absolute/Indirect Address [Flags affected: none]
template<char AddressingModeCharacter>
class PE_
{
public:
    static int invoke(State& state, Word address)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PE_");

        state.pushWordToStack(address);
        return 0;
    }

    static std::string toString() { return std::string("PE") + AddressingModeCharacter; }
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
class PER
{
public:
    static int invoke(State& state, int16_t offset)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PER");

        state.pushWordToStack(state.getProgramCounter(offset));
        return 0;
    }

    static std::string toString() { return "PER"; }
};

// PHA Push Accumulator [Flags affected: none]
class PHA
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PHA");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 1;
            state.pushWordToStack(state.getAccumulatorC());
        }
        else
        {
            state.pushToStack(state.getAccumulatorA());
        }
        return cycles;
    }

    static std::string toString() { return "PHA"; }
};

// PHB Push Data Bank Register [Flags affected: none]
class PHB
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PHB");

        state.pushToStack(state.getDataBank());
        return 0;
    }

    static std::string toString() { return "PHB"; }
};

// PHD Push Direct Page Register [Flags affected: none]
class PHD
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PHD");

        state.pushWordToStack(state.getDirectPageRegister());
        return 0;
    }

    static std::string toString() { return "PHD"; }
};

// PHK Push Program Bank Register [Flags affected: none]
class PHK
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PHK");

        state.pushToStack(state.getProgramBank());
        return 0;
    }

    static std::string toString() { return "PHK"; }
};

// PHP Push Processor Status Register [Flags affected: none]
class PHP
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PHP");

        state.pushToStack(state.getFlags());
        return 0;
    }

    static std::string toString() { return "PHP"; }
};

// PHX/Y Push Index Register X/Y [Flags affected: none]
template<State::IndexRegister Register>
class PH_
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PH_");

        int cycles = 0;
        Word indexRegister = state.getIndexRegister<Register>();
        if (state.is16Bit(State::Flag::x))
        {
            cycles += 1;
            state.pushWordToStack(indexRegister);
        }
        else
        {
            state.pushToStack(Byte(indexRegister));
        }
        return cycles;
    }

    static std::string toString() { return "PH" + State::getIndexRegisterName<Register>(); }
};

// PLA Pull Accumulator [Flags affected: n,z]
class PLA
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PLA");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 1;
            state.setAccumulatorC(state.pullWordFromStack());
        }
        else
        {
            state.setAccumulatorA(state.pullFromStack());
        }
        return cycles;
    }

    static std::string toString() { return "PLA"; }
};

// PLB Pull Data Bank Register [Flags affected: n,z]
class PLB
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PLB");

        state.setDataBank(state.pullFromStack());
        return 0;
    }

    static std::string toString() { return "PLB"; }
};

// PLD Pull Direct Page Register [Flags affected: n,z]
class PLD
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PLD");

        state.setDirectPageRegister(state.pullWordFromStack());
        return 0;
    }

    static std::string toString() { return "PLD"; }
};

// PLP Pull Processor Status Register [Flags affected: n,z (obviously wrong)]
class PLP
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PLP");

        state.setFlags(state.pullFromStack());
        return 0;
    }

    static std::string toString() { return "PLP"; }
};

// PL Pull Index Register X [Flags affected: n,z]
template<State::IndexRegister Register>
class PL_
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "PL_");

        int cycles = 0;
        if (state.is16Bit(State::Flag::x))
        {
            cycles += 1;
            state.setIndexRegister<Register>(state.pullWordFromStack());
        }
        else
        {
            state.setIndexRegister<Register>(state.pullFromStack());
        }
        return cycles;
    }

    static std::string toString() { return "PL" + State::getIndexRegisterName<Register>(); }
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
class REP
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "REP");

        state.setMultipleFlags(false, access.readByte());
        return 0;
    }

    static std::string toString() { return "REP"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
class ROL
{
private:
    template<typename T>
    static T rotateLeft(State& state, T value)
    {
        bool carry = value.isNegative();
        value <<= 1;
        value.setBit(0, state.getFlag(State::Flag::c));
        state.setFlag(State::Flag::c, carry);
        state.updateSignFlags(value);
        return value;
    }

public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ROL");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 2;
            access.writeWord(rotateLeft(state, access.readWord()));
        }
        else
        {
            access.writeByte(rotateLeft(state, access.readByte()));
        }
        return cycles;
    }

    static std::string toString() { return "ROL"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
class ROR
{
private:
    template<typename T>
    static T rotateRight(State& state, T value)
    {
        bool carry = value.getBit(0);
        value >>= 1;
        value.setBit(T::bitCount - 1, state.getFlag(State::Flag::c));
        state.setFlag(State::Flag::c, carry);
        state.updateSignFlags(value);
        return value;
    }

public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ROR");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 2;
            access.writeWord(rotateRight(state, access.readWord()));
        }
        else
        {
            access.writeByte(rotateRight(state, access.readByte()));
        }
        return cycles;
    }

    static std::string toString() { return "ROR"; }
};

// RTI Return from Interrupt [Flags affected: all except b]
class RTI
{
public:
    // §9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "RTI");

        int cycles = 0;
        if (state.isNativeMode())
        {
            cycles += 1;
        }
        state.endInterrupt();
        return cycles;
    }

    static std::string toString() { return "RTI"; }
};

// RTL Return from Subroutine Long [Flags affected: none]
class RTL
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "RTL");

        Word programCounter(state.pullWordFromStack() + 1);
        Byte programBank(state.pullFromStack());
        state.setProgramCounter(programCounter, programBank);
        return 0;
    }

    static std::string toString() { return "RTL"; }
};

// RTS Return from Subroutine [Flags affected: none]
class RTS
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "RTS");

        state.setProgramCounter(Word(state.pullWordFromStack() + 1));
        return 0;
    }

    static std::string toString() { return "RTS"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
class SBC
{
private:
    template<typename T>
    static T subtract(State& state, T accumulator, T memory)
    {
        T result;
        bool carry = state.getFlag(State::Flag::c);
        bool overflow = false;
        if (state.getFlag(State::Flag::d))
        {
            result = Types::decimalSubtract(accumulator, memory, carry, overflow);
        }
        else
        {
            bool dummy = false;
            result = Types::binarySubtract(accumulator, memory, carry, overflow, dummy);
        }
        state.setFlag(State::Flag::c, carry);
        state.setFlag(State::Flag::v, overflow);
        return result;
    }

public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "SBC");

        if (state.is16Bit(State::Flag::m))
        {
            return invoke16Bit(state, access);
        }
        else
        {
            state.setAccumulatorA(subtract(state, state.getAccumulatorA(), access.readByte()));
            return 0;
        }
    }

    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke16Bit(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "SBC 16-Bit");

        state.setAccumulatorC(subtract(state, state.getAccumulatorC(), access.readWord()));
        return 1;
    }

    static std::string toString() { return "SBC"; }
};

// CLC Clear Carry [Flags affected: c]
// CLD Clear Decimal Mode Flag [Flags affected: d]
// CLI Clear Interrupt Disable Flag [Flags affected: i]
// CLV Clear Overflow Flag [Flags affected: v]
// SEC Set Carry Flag [Flags affected: c]
// SED Set Decimal Flag [Flags affected: d]
// SEI Set Interrupt Disable Flag [Flags affected: i]
template<State::Flag Flag, bool Value>
class SE_
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "SE_");

        state.setFlag(Flag, Value);
        return 0;
    }

    static std::string toString() { return (Value ? "SE" : "CL") + State::getFlagName<Flag>(); }
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
class SEP
{
public:
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "SEP");

        state.setMultipleFlags(true, access.readByte());
        return 0;
    }

    static std::string toString() { return "SEP"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
class STA
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "STA");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles += 1;
            access.writeWord(state.getAccumulatorC());
        }
        else
        {
            access.writeByte(state.getAccumulatorA());
        }
        return cycles;
    }

    static std::string toString() { return "STA"; }
};

// STP Stop Processor [Flags affected: none]
class STP
{
public:
    // §14: Uses 3 cycles to shut the processor down; additional cycles are required by reset to restart it
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "STP");

        throw NotYetImplementedException("STP");
        return 0;
    }

    static std::string toString() { return "STP"; }
};

// STX Store Index Register X/Y to Memory [Flags affected: none]
template<State::IndexRegister Register>
class ST_
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "ST_");

        int cycles = 0;
        if (state.is16Bit(State::Flag::x))
        {
            cycles += 1;
            access.writeWord(state.getIndexRegister<Register>());
        }
        else
        {
            access.writeByte(Byte(state.getIndexRegister<Register>()));
        }
        return cycles;
    }

    static std::string toString() { return "ST" + State::getIndexRegisterName<Register>(); }
};

// STZ Store Zero to Memory [Flags affected: none]
class STZ
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "STZ");

        int cycles = 0;

        if (state.is16Bit(State::Flag::m))
        {
            cycles += 1;
            access.writeWord(0);
        }
        else
        {
            access.writeByte(0);
        }

        return cycles;
    }

    static std::string toString() { return "STZ"; }
};

// TAX/Y Transfer Accumulator to Index Register X/Y [Flags affected: n,z]
template<State::IndexRegister Register>
class TA_
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TA_");

        if (state.is16Bit(State::Flag::x))
        {
            state.setIndexRegister<Register>(state.getAccumulatorC());
        }
        else
        {
            state.setIndexRegister<Register>(state.getAccumulatorA());
        }
        return 0;
    }

    static std::string toString() { return "TA" + State::getIndexRegisterName<Register>(); }
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
class TCD
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TCD");

        state.setDirectPageRegister(state.getAccumulatorC());
        return 0;
    }

    static std::string toString() { return "TCD"; }
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
class TCS
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TCS");

        state.setStackPointer(state.getAccumulatorC());
        return 0;
    }

    static std::string toString() { return "TCS"; }
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
class TDC
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TDC");

        state.setAccumulatorC(state.getDirectPageRegister());
        return 0;
    }

    static std::string toString() { return "TDC"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
class TRB
{
private:
    template<typename T>
    static T testAndReset(State& state, T data, T accumulator)
    {
        state.setFlag(State::Flag::z, (data & accumulator) == 0);
        return data & ~accumulator;
    }

public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TRB");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            access.writeWord(testAndReset(state, access.readWord(), state.getAccumulatorC()));
            cycles += 2;
        }
        else
        {
            access.writeByte(testAndReset(state, access.readByte(), state.getAccumulatorA()));
        }
        return cycles;
    }

    static std::string toString() { return "TRB"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
class TSB
{
private:
    template<typename T>
    static T testAndSet(State& state, T data, T accumulator)
    {
        state.setFlag(State::Flag::z, (data & accumulator) == 0);
        return data | accumulator;
    }

public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TSB");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            access.writeWord(testAndSet(state, access.readWord(), state.getAccumulatorC()));
            cycles += 2;
        }
        else
        {
            access.writeByte(testAndSet(state, access.readByte(), state.getAccumulatorA()));
        }
        return cycles;
    }

    static std::string toString() { return "TSB"; }
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
class TSC
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TSC");

        state.setAccumulatorC(state.getStackPointer());
        return 0;
    }

    static std::string toString() { return "TSC"; }
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
class TSX
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TSX");

        throw NotYetImplementedException("TSX");
        return 0;
    }

    static std::string toString() { return "TSX"; }
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
template<State::IndexRegister Register>
class T_A
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "T_A");

        if (state.is16Bit(State::Flag::m))
        {
            state.setAccumulatorC(state.getIndexRegister<Register>());
        }
        else
        {
            state.setAccumulatorA(Byte(state.getIndexRegister<Register>()));
        }
        return 0;
    }

    static std::string toString() { return "T" + State::getIndexRegisterName<Register>() + "A"; }
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
class TXS
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "TXS");

        state.setStackPointer(state.getIndexRegister<State::IndexRegister::X>());
        return 0;
    }

    static std::string toString() { return "TXS"; }
};

// TXY/YX Transfer Index Register X/Y to Index Register Y/X [Flags affected: n,z]
template<State::IndexRegister SourceRegister, State::IndexRegister TargetRegister>
class T__
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "T__");

        state.setIndexRegister<TargetRegister>(state.getIndexRegister<SourceRegister>());
        return 0;
    }

    static std::string toString() { return "T" + State::getIndexRegisterName<SourceRegister>() + State::getIndexRegisterName<TargetRegister>(); }
};

// WAI Wait for Interrupt [Flags affected: none]
class WAI
{
public:
    // §15: Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "WAI");

        throw NotYetImplementedException("WAI");
        return 0;
    }

    static std::string toString() { return "WAI"; }
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
class WDM
{
public:
    // §16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths
    static int invoke(State& state, const Access& access)
    {
        PROFILE_IF(PROFILE_OPERATORS, "WDM");

        throw NotYetImplementedException("WDM");
        return 0;
    }

    static std::string toString() { return "WDM"; }
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
class XBA
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "XBA");

        state.swapAccumulators();
        return 0;
    }

    static std::string toString() { return "XBA"; }
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
class XCE
{
public:
    static int invoke(State& state)
    {
        PROFILE_IF(PROFILE_OPERATORS, "XCE");

        state.exchangeCarryAndEmulationFlags();
        return 0;
    }

    static std::string toString() { return "XCE"; }
};

}

}