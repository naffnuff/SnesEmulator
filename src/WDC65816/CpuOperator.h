#pragma once

#include "Exception.h"
#include "CpuState.h"

namespace CPU {

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
class ADC
{
private:
    template<typename T>
    static T add(State& state, T accumulator, T memory)
    {
        T result;
        bool carry = state.getFlag(State::c);
        bool overflow = false;
        if (state.getFlag(State::d)) {
            result = Types::decimalAdd(accumulator, memory, carry, overflow);
        }
        else {
            bool dummy = false;
            result = Types::binaryAdd(accumulator, memory, carry, overflow, dummy);
        }
        state.setFlag(State::c, carry);
        state.setFlag(State::v, overflow);
        return result;
    }

public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.setAccumulatorC(add(state, state.getAccumulatorC(), access.readWord()));
        }
        else {
            state.setAccumulatorA(add(state, state.getAccumulatorA(), access.readByte()));
        }
        return cycles;
    }

    static std::string toString() { return "ADC"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
class AND
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.setAccumulatorC(state.getAccumulatorC() & access.readWord());
        }
        else {
            state.setAccumulatorA(state.getAccumulatorA() & access.readByte());
        }
        return cycles;
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
        state.setFlag(State::c, value.isNegative());
        value <<= 1;
        state.updateSignFlags(value);
        return value;
    }

public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            access.writeWord(arithmeticShiftLeft(state, access.readWord()));
        }
        else {
            access.writeByte(arithmeticShiftLeft(state, access.readByte()));
        }
        return cycles;
    }

    static std::string toString() { return "ASL"; }
};

static int branchIf(bool condition, State& state, int offset)
{
    int cycles = 0;
    if (condition) {
        Word newAddress = state.getProgramCounter(offset);
        cycles += 1;
        if (!state.isNativeMode()) {
            Byte programPage = state.getProgramCounter() >> 8;
            Byte newAddressPage = newAddress >> 8;
            if (programPage != newAddressPage) {
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
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(!state.getFlag(State::c), state, offset);
    }

    static std::string toString() { return "BCC"; }
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
class BCS
{
public:
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(state.getFlag(State::c), state, offset);
    }

    static std::string toString() { return "BCS"; }
};

// BEQ Branch if Equal [Flags affected: none]
class BEQ
{
public:
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(state.getFlag(State::z), state, offset);
    }

    static std::string toString() { return "BEQ"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
template<bool ImmediateMode>
class BIT
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        bool zFlag = false;
        bool nFlag = false;
        bool vFlag = false;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            Word data = access.readWord();
            nFlag = data.isNegative();
            vFlag = data.getBit(14);
            zFlag = (state.getAccumulatorC() & data) == 0;
        }
        else {
            Byte data = access.readByte();
            nFlag = data.isNegative();
            vFlag = data.getBit(6);
            zFlag = (state.getAccumulatorA() & data) == 0;
        }
        if (!ImmediateMode) {
            state.setFlag(State::n, nFlag);
            state.setFlag(State::v, vFlag);
        }
        state.setFlag(State::z, zFlag);
        return cycles;
    }

    static std::string toString() { return "BIT"; }
};

// BMI Branch if Minus [Flags affected: none]
class BMI
{
public:
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(state.getFlag(State::n), state, offset);
    }

    static std::string toString() { return "BMI"; }
};

// BNE Branch if Not Equal [Flags affected: none]
class BNE
{
public:
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(!state.getFlag(State::z), state, offset);
    }

    static std::string toString() { return "BNE"; }
};

// BPL Branch if Plus [Flags affected: none]
class BPL
{
public:
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(!state.getFlag(State::n), state, offset);
    }

    static std::string toString() { return "BPL"; }
};

// BRA Branch Always [Flags affected: none]
class BRA
{
public:
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(true, state, offset);
    }

    static std::string toString() { return "BRA"; }
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
class BRK
{
public:
    // �9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state, const Access& access)
    {
        throw OperatorNotYetImplementedException("BRK");
        int cycles = 0;
        if (state.isNativeMode()) {
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
        return branchIf(true, state, offset);
        return 0;
    }

    static std::string toString() { return "BRL"; }
};

// BVC Branch if Overflow Clear [Flags affected: none]
class BVC
{
public:
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(!state.getFlag(State::v), state, offset);
    }

    static std::string toString() { return "BVC"; }
};

// BVS Branch if Overflow Set [Flags affected: none]
class BVS
{
public:
    // �7: Add 1 cycle if branch is taken
    // �8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(state.getFlag(State::v), state, offset);
    }

    static std::string toString() { return "BVS"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
class CMP
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            Word accumulator = state.getAccumulatorC();
            Word data = access.readWord();
            state.setFlag(State::c, accumulator >= data);
            state.updateSignFlags(Word(accumulator - data));
        } else {
            Byte accumulator = state.getAccumulatorA();
            Byte data = access.readByte();
            state.setFlag(State::c, accumulator >= data);
            state.updateSignFlags(Byte(accumulator - data));
        }
        return cycles;
    }

    static std::string toString() { return "CMP"; }
};

// COP Co-Processor Enable [Flags affected: d,i]
class COP
{
public:
    // �9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state, const Access& access)
    {
        throw OperatorNotYetImplementedException("COP");
        int cycles = 0;
        if (state.isNativeMode()) {
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
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
            Word indexRegister = state.getIndexRegister<Register>();
            Word data = access.readWord();
            state.setFlag(State::c, indexRegister >= data);
            state.updateSignFlags(Word(indexRegister - data));
        }
        else {
            Byte indexRegister(state.getIndexRegister<Register>());
            Byte data = access.readByte();
            state.setFlag(State::c, indexRegister >= data);
            state.updateSignFlags(Byte(indexRegister - data));
        }
        return cycles;
    }

    static std::string toString() { return "CP" + State::getIndexRegisterName<Register>(); }
};

// DEC Decrement [Flags affected: n,z]
class DEC
{
public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            Word value = access.readWord() - 1;
            access.writeWord(value);
            state.updateSignFlags(value);
        }
        else {
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
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 2;
            Word& indexRegister = state.getIndexRegister<Register>();
            state.updateSignFlags(--indexRegister);
        }
        else {
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
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.setAccumulatorC(state.getAccumulatorC() ^ access.readWord());
        }
        else {
            state.setAccumulatorA(state.getAccumulatorA() ^ access.readByte());
        }
        return cycles;
    }

    static std::string toString() { return "EOR"; }
};

// INC Increment [Flags affected: n,z]
class INC
{
public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            Word value = access.readWord() + 1;
            access.writeWord(value);
            state.updateSignFlags(value);
        }
        else {
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
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            Word& indexRegister = state.getIndexRegister<Register>();
            state.updateSignFlags(++indexRegister);
        }
        else {
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
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.setAccumulatorC(access.readWord());
        } else {
            state.setAccumulatorA(access.readByte());
        }
        return cycles;
    }

    static std::string toString() { return "LDA"; }
};

// LDX/Y Load Index Register X/Y from Memory [Flags affected: n,z]
template<State::IndexRegister Register>
class LD_
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            state.setIndexRegister<Register>(access.readWord());
            cycles += 1;
        } else {
            state.setIndexRegister<Register>(access.readByte());
        }
        return cycles;
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
        state.setFlag(State::c, value.getBit(0));
        value >>= 1;
        state.updateSignFlags(value);
        return value;
    }

public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            access.writeWord(logicalShiftLeft(state, access.readWord()));
        } else {
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
    // �13: 7 cycles per byte moved
    static int invoke(State& state, Byte sourceBank, Byte destinationBank, Word byteCount)
    {
        Word sourceAddress = state.getIndexRegister<State::X>();
        Word destinationAddress = state.getIndexRegister<State::Y>();
        
        Byte value = state.readMemoryByte(Long(sourceAddress, sourceBank));
        state.writeMemoryByte(value, Long(destinationAddress, destinationBank));

        state.setIndexRegister<State::X>(Word(sourceAddress + 1));
        state.setIndexRegister<State::Y>(Word(destinationAddress + 1));
        return 0;
    }

    static std::string toString() { return "MVN"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
class MVP
{
public:
    // �13: 7 cycles per byte moved
    static int invoke(State& state, Byte sourceBank, Byte destinationBank, Word byteCount)
    {
        throw OperatorNotYetImplementedException("MVP");
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
        return 0;
    }

    static std::string toString() { return "NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
class ORA
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.setAccumulatorC(state.getAccumulatorC() | access.readWord());
        }
        else {
            state.setAccumulatorA(state.getAccumulatorA() | access.readByte());
        }
        return cycles;
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
        state.pushWordToStack(state.getProgramCounter(offset));
        return 0;
    }

    static std::string toString() { return "PER"; }
};

// PHA Push Accumulator [Flags affected: none]
class PHA
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.pushWordToStack(state.getAccumulatorC());
        }
        else {
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
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        int cycles = 0;
        Word indexRegister = state.getIndexRegister<Register>();
        if (state.is16Bit(State::x)) {
            cycles += 1;
            state.pushWordToStack(indexRegister);
        }
        else {
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
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.setAccumulatorC(state.pullWordFromStack());
        }
        else {
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
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
            state.setIndexRegister<Register>(state.pullWordFromStack());
        } else {
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
    static int invoke(State& state, const Access& access)
    {
        state.setFlag(access.readByte(), false);
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
        value.setBit(0, state.getFlag(State::c));
        state.setFlag(State::c, carry);
        state.updateSignFlags(value);
        return value;
    }

public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            access.writeWord(rotateLeft(state, access.readWord()));
        }
        else {
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
        value.setBit(T::bitCount - 1, state.getFlag(State::c));
        state.setFlag(State::c, carry);
        state.updateSignFlags(value);
        return value;
    }

public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            access.writeWord(rotateRight(state, access.readWord()));
        } else {
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
    // �9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state)
    {
        int cycles = 0;
        if (state.isNativeMode()) {
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
        bool carry = state.getFlag(State::c);
        bool overflow = false;
        if (state.getFlag(State::d)) {
            result = Types::decimalSubtract(accumulator, memory, carry, overflow);
        }
        else {
            bool dummy = false;
            result = Types::binarySubtract(accumulator, memory, carry, overflow, dummy);
        }
        state.setFlag(State::c, carry);
        state.setFlag(State::v, overflow);
        return result;
    }

public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            state.setAccumulatorC(subtract(state, state.getAccumulatorC(), access.readWord()));
        }
        else {
            state.setAccumulatorA(subtract(state, state.getAccumulatorA(), access.readByte()));
        }
        return cycles;
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
        state.setFlag(Flag, Value);
        return 0;
    }

    static std::string toString() { return (Value ? "SE" : "CL") + State::getFlagName<Flag>(); }
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
class SEP
{
public:
    static int invoke(State& state, const Access& access)
    {
        state.setFlag(access.readByte(), true);
        return 0;
    }

    static std::string toString() { return "SEP"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
class STA
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            access.writeWord(state.getAccumulatorC());
        }
        else {
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
    // �14: Uses 3 cycles to shut the processor down; additional cycles are required by reset to restart it
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("STP");
        return 0;
    }

    static std::string toString() { return "STP"; }
};

// STX Store Index Register X/Y to Memory [Flags affected: none]
template<State::IndexRegister Register>
class ST_
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
            access.writeWord(state.getIndexRegister<Register>());
        }
        else {
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
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;

        if (state.is16Bit(State::m)) {
            cycles += 1;
            access.writeWord(0);
        }
        else {
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
        if (state.is16Bit(State::x)) {
            state.setIndexRegister<Register>(state.getAccumulatorC());
        }
        else {
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
        state.setFlag(State::z, (data & accumulator) == 0);
        return data & ~accumulator;
    }

public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            access.writeWord(testAndReset(state, access.readWord(), state.getAccumulatorC()));
            cycles += 2;
        }
        else {
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
        state.setFlag(State::z, (data & accumulator) == 0);
        return data | accumulator;
    }

public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Access& access)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            access.writeWord(testAndSet(state, access.readWord(), state.getAccumulatorC()));
            cycles += 2;
        }
        else {
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
        throw OperatorNotYetImplementedException("TSX");
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
        if (state.is16Bit(State::m)) {
            state.setAccumulatorC(state.getIndexRegister<Register>());
        }
        else {
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
        state.setStackPointer(state.getIndexRegister<State::X>());
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
        state.setIndexRegister<TargetRegister>(state.getIndexRegister<SourceRegister>());
        return 0;
    }

    static std::string toString() { return "T" + State::getIndexRegisterName<SourceRegister>() + State::getIndexRegisterName<TargetRegister>(); }
};

// WAI Wait for Interrupt [Flags affected: none]
class WAI
{
public:
    // �15: Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("WAI");
        return 0;
    }

    static std::string toString() { return "WAI"; }
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
class WDM
{
public:
    // �16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths
    static int invoke(State& state, const Access& access)
    {
        throw OperatorNotYetImplementedException("WDM");
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
        state.exchangeCarryAndEmulationFlags();
        return 0;
    }

    static std::string toString() { return "XCE"; }
};

}

}