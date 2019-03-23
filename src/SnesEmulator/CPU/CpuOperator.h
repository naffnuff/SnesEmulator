#pragma once

#include "CpuState.h"

namespace CPU {

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
class ADC
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("ADC is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "ADC"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
class AND
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("AND is not implemented");
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
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("ASL is not implemented");
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
        uint16_t newAddress = state.getProgramCounter(offset);
        cycles += 1;
        if (!state.isNativeMode()) {
            Byte programPage = Byte(state.getProgramCounter() >> 8);
            Byte newAddressPage = Byte(newAddress >> 8);
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
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BCC is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw std::runtime_error("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO08");
        }
        return cycles;
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
        throw std::runtime_error("BCS is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw std::runtime_error("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO08");
        }
        return cycles;
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
        throw std::runtime_error("BEQ is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw std::runtime_error("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO08");
        }
        return cycles;
    }

    static std::string toString() { return "BEQ"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
class BIT
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("BIT is not implemented");
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
    // §7: Add 1 cycle if branch is taken
    // §8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BMI is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw std::runtime_error("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO08");
        }
        return cycles;
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
        return branchIf(!state.getFlag(State::z), state, offset);
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
        throw std::runtime_error("BPL is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw std::runtime_error("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO08");
        }
        return cycles;
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
        return branchIf(true, state, offset);
    }

    static std::string toString() { return "BRA"; }
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
class BRK
{
public:
    // §9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("BRK is not implemented");
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
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("BRL is not implemented");
        return 0;
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
        throw std::runtime_error("BVC is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw std::runtime_error("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO08");
        }
        return cycles;
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
        throw std::runtime_error("BVS is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 1;
            throw std::runtime_error("TODO07");
        }
        if (true /*branch taken crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO08");
        }
        return cycles;
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
        throw std::runtime_error("CLD is not implemented");
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
        throw std::runtime_error("CLI is not implemented");
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
        throw std::runtime_error("CLV is not implemented");
        return 0;
    }

    static std::string toString() { return "CLV"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
class CMP
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            uint16_t accumulator = state.getAccumulatorC();
            uint16_t data16Bit = data[0] | data[1] << 8;
            state.setFlag(State::c, accumulator >= data16Bit);
            state.updateSignFlags(uint16_t(accumulator - data16Bit));
        } else {
            Byte accumulator = state.getAccumulatorA();
            state.setFlag(State::c, accumulator >= data[0]);
            state.updateSignFlags(Byte(accumulator - data[0]));
        }
        return cycles;
    }

    static std::string toString() { return "CMP"; }
};

// COP Co-Processor Enable [Flags affected: d,i]
class COP
{
public:
    // §9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("COP is not implemented");
        int cycles = 0;
        if (state.isNativeMode()) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "COP"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
class CPX
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("CPX is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "CPX"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
class CPY
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("CPY is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "CPY"; }
};

// DEC Decrement [Flags affected: n,z]
class DEC
{
public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("DEC is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
        }
        return cycles;
    }

    static std::string toString() { return "DEC"; }
};

// DEX Decrement Index Register X [Flags affected: n,z]
class DEX
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("DEX is not implemented");
        return 0;
    }

    static std::string toString() { return "DEX"; }
};

// DEY Decrement Index Register Y [Flags affected: n,z]
class DEY
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("DEY is not implemented");
        return 0;
    }

    static std::string toString() { return "DEY"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
class EOR
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("EOR is not implemented");
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
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("INC is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
        }
        return cycles;
    }

    static std::string toString() { return "INC"; }
};

// INX Increment Index Register X [Flags affected: n,z]
class INX
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("INX is not implemented");
        return 0;
    }

    static std::string toString() { return "INX"; }
};

// INY Increment Index Register Y [Flags affected: n,z]
class INY
{
public:
    static int invoke(State& state)
    {
        state.updateSignFlags(++state.getYIndexRegister());
        return 0;
    }

    static std::string toString() { return "INY"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
class JMP
{
public:
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("JMP is not implemented");
        return 0;
    }

    static std::string toString() { return "JMP"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
class JSR
{
public:
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("JSR is not implemented");
        return 0;
    }

    static int invoke(State& state, uint16_t address)
    {
        uint16_t programCounter = uint16_t(state.getProgramAddress(-1));
        state.pushToStack(programCounter);
        state.setProgramCounter(address);
        return 0;
    }

    static std::string toString() { return "JSR"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
class LDA
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            state.setAccumulatorC(uint16_t(data[0] | data[1] << 8));
            cycles += 1;
        } else {
            state.setAccumulatorA(data[0]);
        }
        return cycles;
    }

    static std::string toString() { return "LDA"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
class LDX
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Byte* data)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            state.setXIndexRegister(uint16_t(data[0] | data[1] << 8));
            cycles += 1;
        } else {
            state.setXIndexRegister(data[0]);
        }
        return cycles;
    }

    static std::string toString() { return "LDX"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
class LDY
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Byte* data)
    {
        int cycles = 0;
        if (state.is16Bit(State::x)) {
            state.setYIndexRegister(uint16_t(data[0] | data[1] << 8));
            cycles += 1;
        } else {
            state.setYIndexRegister(data[0]);
        }
        return cycles;
    }

    static std::string toString() { return "LDY"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
class LSR
{
public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("LSR is not implemented");
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
    // §13: 7 cycles per byte moved
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("MVN is not implemented");
        return 0;
    }

    static std::string toString() { return "MVN"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
class MVP
{
public:
    // §13: 7 cycles per byte moved
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("MVP is not implemented");
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
        throw std::runtime_error("NOP is not implemented");
        return 0;
    }

    static std::string toString() { return "NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
class ORA
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("ORA is not implemented");
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
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("PEA is not implemented");
        return 0;
    }

    static std::string toString() { return "PEA"; }
};

// PEI Push Effective Indirect Address [Flags affected: none]
class PEI
{
public:
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("PEI is not implemented");
        return 0;
    }

    static std::string toString() { return "PEI"; }
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
class PER
{
public:
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("PER is not implemented");
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
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
            Byte highByte = state.getAccumulatorB();
            state.pushToStack(highByte);
        }
        Byte lowByte = state.getAccumulatorA();
        state.pushToStack(lowByte);
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
        throw std::runtime_error("PHB is not implemented");
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
        throw std::runtime_error("PHD is not implemented");
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
        throw std::runtime_error("PHK is not implemented");
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
        state.pushFlagsToStack();
        return 0;
    }

    static std::string toString() { return "PHP"; }
};

// PHX Push Index Register X [Flags affected: none]
class PHX
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw std::runtime_error("PHX is not implemented");
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
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw std::runtime_error("PHY is not implemented");
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
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state)
    {
        throw std::runtime_error("PLA is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 1;
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
        throw std::runtime_error("PLB is not implemented");
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
        throw std::runtime_error("PLD is not implemented");
        return 0;
    }

    static std::string toString() { return "PLD"; }
};

// PLP Pull Processor Status Register [Flags affected: n,z]
class PLP
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("PLP is not implemented");
        return 0;
    }

    static std::string toString() { return "PLP"; }
};

// PLX Pull Index Register X [Flags affected: n,z]
class PLX
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw std::runtime_error("PLX is not implemented");
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
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state)
    {
        throw std::runtime_error("PLY is not implemented");
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
    static int invoke(State& state, Byte* data)
    {
        state.setFlag(*data, false);
        return 0;
    }

    static std::string toString() { return "REP"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
class ROL
{
public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("ROL is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles += 2;
        }
        return cycles;
    }

    static std::string toString() { return "ROL"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
class ROR
{
public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("ROR is not implemented");
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
    // §9: Add 1 cycle for 65816 native mode (e=0)
    static int invoke(State& state)
    {
        throw std::runtime_error("RTI is not implemented");
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
        throw std::runtime_error("RTL is not implemented");
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
        throw std::runtime_error("RTS is not implemented");
        return 0;
    }

    static std::string toString() { return "RTS"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
class SBC
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("SBC is not implemented");
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
        throw std::runtime_error("SEC is not implemented");
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
        throw std::runtime_error("SED is not implemented");
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
    static int invoke(State& state, Byte* data)
    {
        state.setFlag(*data, true);
        return 0;
    }

    static std::string toString() { return "SEP"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
class STA
{
public:
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        int cycles = 0;

        data[0] = state.getAccumulatorA();

        if (state.is16Bit(State::m)) {
            data[1] = state.getAccumulatorB();
            cycles += 1;
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
        throw std::runtime_error("STP is not implemented");
        return 0;
    }

    static std::string toString() { return "STP"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
class STX
{
public:
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("STX is not implemented");
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
    // §10: Add 1 cycle if x=0 (16-bit index registers)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("STY is not implemented");
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
    // §1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        data[0] = 0;
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            data[1] = 0;
            cycles += 1;
        }
        return cycles;
    }

    static std::string toString() { return "STZ"; }
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
class TAX
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("TAX is not implemented");
        return 0;
    }

    static std::string toString() { return "TAX"; }
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
class TAY
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("TAY is not implemented");
        return 0;
    }

    static std::string toString() { return "TAY"; }
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
        throw std::runtime_error("TDC is not implemented");
        return 0;
    }

    static std::string toString() { return "TDC"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
class TRB
{
public:
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("TRB is not implemented");
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
    // §5: Add 2 cycles if m=0 (16-bit memory/accumulator)
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("TSB is not implemented");
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
        throw std::runtime_error("TSC is not implemented");
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
        throw std::runtime_error("TSX is not implemented");
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
        throw std::runtime_error("TXA is not implemented");
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
        throw std::runtime_error("TXS is not implemented");
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
        throw std::runtime_error("TXY is not implemented");
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
        throw std::runtime_error("TYA is not implemented");
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
        throw std::runtime_error("TYX is not implemented");
        return 0;
    }

    static std::string toString() { return "TYX"; }
};

// WAI Wait for Interrupt [Flags affected: none]
class WAI
{
public:
    // §15: Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it
    static int invoke(State& state)
    {
        throw std::runtime_error("WAI is not implemented");
        return 0;
    }

    static std::string toString() { return "WAI"; }
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
class WDM
{
public:
    // §16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths
    static int invoke(State& state, Byte* data)
    {
        throw std::runtime_error("WDM is not implemented");
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
        throw std::runtime_error("XBA is not implemented");
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