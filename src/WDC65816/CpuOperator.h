#pragma once

#include "Exception.h"
#include "CpuState.h"

namespace CPU {

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
class ADC
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            throw OperatorNotYetImplementedException("ADC 16-bit");
            cycles += 1;
        }
        else {
            Byte accumulator = state.getAccumulatorA();
            bool carry = state.getFlag(State::c);
            bool overflow = false;
            accumulator.binaryAdd(memory->getValue(), carry, overflow);
            state.setFlag(State::c, carry);
            state.setFlag(State::v, overflow);
            state.setAccumulatorA(accumulator);
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
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("AND");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "AND"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
class ASL
{
public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("ASL");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
        }
        return cycles;
    }

    static std::string toString() { return "ASL"; }
};

static int branchIf(bool condition, State& state, int8_t offset)
{
    int cycles = 0;
    if (condition) {
        Word newAddress = state.getProgramCounter(offset);
        cycles += 1;
        if (!state.isNativeMode()) {
            Byte programPage = state.getProgramCounter() >> 8;
            Byte newAddressPage = newAddress >> 8;
            if (programPage != newAddressPage) {
                throw OperatorNotYetImplementedException("TODO08");
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
        throw OperatorNotYetImplementedException("BCC");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO08");
        }
        return cycles;
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
        throw OperatorNotYetImplementedException("BCS");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO08");
        }
        return cycles;
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
class BIT
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("BIT");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
        }
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
        throw OperatorNotYetImplementedException("BMI");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO08");
        }
        return cycles;
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
        throw OperatorNotYetImplementedException("BPL");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO08");
        }
        return cycles;
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
    static int invoke(State& state, const MemoryLocation* memory)
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
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("BRL");
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
        throw OperatorNotYetImplementedException("BVC");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw OperatorNotYetImplementedException("TODO08");
        }
        return cycles;
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

// CLC Clear Carry [Flags affected: c]
class CLC
{
public:
    static int invoke(State& state)
    {
        state.setFlag(State::c, false);
        return 0;
    }

    static std::string toString() { return "CLC"; }
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
class CLD
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("CLD");
        return 0;
    }

    static std::string toString() { return "CLD"; }
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
class CLI
{
public:
    static int invoke(State& state)
    {
        state.setFlag(State::i, false);
        return 0;
    }

    static std::string toString() { return "CLI"; }
};

// CLV Clear Overflow Flag [Flags affected: v]
class CLV
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("CLV");
        return 0;
    }

    static std::string toString() { return "CLV"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
class CMP
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            Word accumulator = state.getAccumulatorC();
            Word data = memory->getWordValue();
            state.setFlag(State::c, accumulator >= data);
            state.updateSignFlags(Word(accumulator - data));
        } else {
            Byte accumulator = state.getAccumulatorA();
            Byte data = memory->getValue();
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
    static int invoke(State& state, const MemoryLocation* memory)
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
class CP
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
            Word indexRegister = state.getIndexRegister<Register>();
            Word data = memory->getWordValue();
            state.setFlag(State::c, indexRegister >= data);
            state.updateSignFlags(Word(indexRegister - data));
        }
        else {
            Byte indexRegister(state.getIndexRegister<Register>());
            Byte data = memory->getValue();
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
    static int invoke(State& state, MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            Word data = memory->getWordValue();
            state.updateSignFlags(--data);
            memory->setWordValue(data);
        }
        else {
            state.updateSignFlags(--memory->get());
        }
        return cycles;
    }

    static std::string toString() { return "DEC"; }
};

// DEX/Y Decrement Index Register X/Y [Flags affected: n,z]
template<State::IndexRegister Register>
class DE
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
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("EOR");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
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
    static int invoke(State& state, MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            Word data = memory->getWordValue();
            state.updateSignFlags(++data);
            memory->setWordValue(data);
        }
        else {
            state.updateSignFlags(++memory->get());
        }
        return cycles;
    }

    static std::string toString() { return "INC"; }
};

// INX/Y Increment Index Register X/Y [Flags affected: n,z]
template<State::IndexRegister Register>
class IN
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
        throw OperatorNotYetImplementedException("JMP");
        return 0;
    }

    static std::string toString() { return "JMP"; }
};

class JML
{
public:
    static int invoke(State& state, Long address)
    {
        throw OperatorNotYetImplementedException("JML");
        return 0;
    }

    static std::string toString()
    {
        return "JML";
    }
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
        throw OperatorNotYetImplementedException("JSL");
        return 0;
    }

    static std::string toString()
    {
        return "JSL";
    }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
class LDA
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            state.setAccumulatorC(memory->getWordValue());
            cycles += 1;
        } else {
            state.setAccumulatorA(memory->getValue());
        }
        return cycles;
    }

    static std::string toString() { return "LDA"; }
};

// LDX/Y Load Index Register X/Y from Memory [Flags affected: n,z]
template<State::IndexRegister Register>
class LD
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            state.setIndexRegister<Register>(memory->getWordValue());
            cycles += 1;
        } else {
            state.setIndexRegister<Register>(memory->getValue());
        }
        return cycles;
    }

    static std::string toString() { return "LD" + State::getIndexRegisterName<Register>(); }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
class LSR
{
public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("LSR");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
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
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("MVN");
        return 0;
    }

    static std::string toString() { return "MVN"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
class MVP
{
public:
    // �13: 7 cycles per byte moved
    static int invoke(State& state, const MemoryLocation* memory)
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
        throw OperatorNotYetImplementedException("NOP");
        return 0;
    }

    static std::string toString() { return "NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
class ORA
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("ORA");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "ORA"; }
};

// PEA Push Effective Absolute Address [Flags affected: none]
class PEA
{
public:
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("PEA");
        return 0;
    }

    static std::string toString() { return "PEA"; }
};

// PEI Push Effective Indirect Address [Flags affected: none]
class PEI
{
public:
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("PEI");
        return 0;
    }

    static std::string toString() { return "PEI"; }
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
class PER
{
public:
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("PER");
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
        throw OperatorNotYetImplementedException("PHB");
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
        throw OperatorNotYetImplementedException("PHD");
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
        throw OperatorNotYetImplementedException("PHK");
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

// PHX Push Index Register X [Flags affected: none]
class PHX
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("PHX");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "PHX"; }
};

// PHY Push Index Register Y [Flags affected: none]
class PHY
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("PHY");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "PHY"; }
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
        throw OperatorNotYetImplementedException("PLB");
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
        throw OperatorNotYetImplementedException("PLD");
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

// PLX Pull Index Register X [Flags affected: n,z]
class PLX
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("PLX");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "PLX"; }
};

// PLY Pull Index Register Y [Flags affected: n,z]
class PLY
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("PLY");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "PLY"; }
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
class REP
{
public:
    static int invoke(State& state, const MemoryLocation* memory)
    {
        state.setFlag(memory->getValue(), false);
        return 0;
    }

    static std::string toString() { return "REP"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
class ROL
{
private:
    template<typename T>
    static void rotateLeft(State& state, T& data)
    {
        bool carry = data.isNegative();
        data <<= 1;
        data |= T(state.getFlag(State::c));
        state.setFlag(State::c, carry);
        state.updateSignFlags(data);
    }

public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, MemoryLocation* memory)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
            Word data = memory->getWordValue();
            rotateLeft(state, data);
            memory->setWordValue(data);
        }
        else {
            Byte data = memory->getValue();
            rotateLeft(state, data);
            memory->setValue(data);
        }
        return cycles;
    }

    static std::string toString() { return "ROL"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
class ROR
{
public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("ROR");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
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
        throw OperatorNotYetImplementedException("RTI");
        int cycles = 0;
        if (state.isNativeMode()) {
            cycles += 1;
        }
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
        throw OperatorNotYetImplementedException("RTL");
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
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("SBC");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "SBC"; }
};

// SEC Set Carry Flag [Flags affected: c]
class SEC
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("SEC");
        return 0;
    }

    static std::string toString() { return "SEC"; }
};

// SED Set Decimal Flag [Flags affected: d]
class SED
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("SED");
        return 0;
    }

    static std::string toString() { return "SED"; }
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
class SEI
{
public:
    static int invoke(State& state)
    {
        state.setFlag(State::i, true);
        return 0;
    }

    static std::string toString() { return "SEI"; }
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
class SEP
{
public:
    static int invoke(State& state, const MemoryLocation* memory)
    {
        state.setFlag(memory->getValue(), true);
        return 0;
    }

    static std::string toString() { return "SEP"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
class STA
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, MemoryLocation* memory)
    {
        int cycles = 0;

        if (state.is16Bit(State::m)) {
            cycles += 1;
            memory->setWordValue(state.getAccumulatorC());
        }
        else {
            memory->setValue(state.getAccumulatorA());
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

// STX Store Index Register X to Memory [Flags affected: none]
class STX
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("STX");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "STX"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
class STY
{
public:
    // �10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("STY");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "STY"; }
};

// STZ Store Zero to Memory [Flags affected: none]
class STZ
{
public:
    // �1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, MemoryLocation* memory)
    {
        int cycles = 0;

        if (state.is16Bit(State::m)) {
            cycles += 1;
            memory->setWordValue(0);
        }
        else {
            memory->setValue(0);
        }

        return cycles;
    }

    static std::string toString() { return "STZ"; }
};

// TAX/Y Transfer Accumulator to Index Register X/Y [Flags affected: n,z]
template<State::IndexRegister Register>
class TA
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
        throw OperatorNotYetImplementedException("TDC");
        return 0;
    }

    static std::string toString() { return "TDC"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
class TRB
{
public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("TRB");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
        }
        return cycles;
    }

    static std::string toString() { return "TRB"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
class TSB
{
public:
    // �5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, const MemoryLocation* memory)
    {
        throw OperatorNotYetImplementedException("TSB");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
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
        throw OperatorNotYetImplementedException("TSC");
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
class TXA
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("TXA");
        return 0;
    }

    static std::string toString() { return "TXA"; }
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
class TXS
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("TXS");
        return 0;
    }

    static std::string toString() { return "TXS"; }
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
class TXY
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("TXY");
        return 0;
    }

    static std::string toString() { return "TXY"; }
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
class TYA
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("TYA");
        return 0;
    }

    static std::string toString() { return "TYA"; }
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
class TYX
{
public:
    static int invoke(State& state)
    {
        throw OperatorNotYetImplementedException("TYX");
        return 0;
    }

    static std::string toString() { return "TYX"; }
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
    static int invoke(State& state, const MemoryLocation* memory)
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
        Byte accumulatorB = state.getAccumulatorB();
        MemoryLocation* accumulator = state.getAccumulatorPointer();
        accumulator[1].setValue(accumulator[0].getValue());
        state.setAccumulatorA(accumulatorB);
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