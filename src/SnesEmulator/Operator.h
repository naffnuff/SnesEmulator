#pragma once

#include "State.h"

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
class ADC
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "ADC"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
class AND
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "AND"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
class ASL
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "ASL"; }
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
class BCC
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BCC"; }
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
class BCS
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BCS"; }
};

// BEQ Branch if Equal [Flags affected: none]
class BEQ
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BEQ"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
class BIT
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BIT"; }
};

// BMI Branch if Minus [Flags affected: none]
class BMI
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BMI"; }
};

// BNE Branch if Not Equal [Flags affected: none]
class BNE
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BNE"; }
};

// BPL Branch if Plus [Flags affected: none]
class BPL
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BPL"; }
};

// BRA Branch Always [Flags affected: none]
class BRA
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BRA"; }
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
class BRK
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BRK"; }
};

// BRL Branch Long Always [Flags affected: none]
class BRL
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BRL"; }
};

// BVC Branch if Overflow Clear [Flags affected: none]
class BVC
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BVC"; }
};

// BVS Branch if Overflow Set [Flags affected: none]
class BVS
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "BVS"; }
};

// CLC Clear Carry [Flags affected: c]
class CLC
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "CLC"; }
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
class CLD
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "CLD"; }
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
class CLI
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "CLI"; }
};

// CLV Clear Overflow Flag [Flags affected: v]
class CLV
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "CLV"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
class CMP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "CMP"; }
};

// COP Co-Processor Enable [Flags affected: d,i]
class COP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "COP"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
class CPX
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "CPX"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
class CPY
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "CPY"; }
};

// DEC Decrement [Flags affected: n,z]
class DEC
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "DEC"; }
};

// DEX Decrement Index Register X [Flags affected: n,z]
class DEX
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "DEX"; }
};

// DEY Decrement Index Register Y [Flags affected: n,z]
class DEY
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "DEY"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
class EOR
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "EOR"; }
};

// INC Increment [Flags affected: n,z]
class INC
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "INC"; }
};

// INX Increment Index Register X [Flags affected: n,z]
class INX
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "INX"; }
};

// INY Increment Index Register Y [Flags affected: n,z]
class INY
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "INY"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
class JMP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "JMP"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
class JSR
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "JSR"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
class LDA
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "LDA"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
class LDX
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "LDX"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
class LDY
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "LDY"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
class LSR
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "LSR"; }
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
class MVN
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "MVN"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
class MVP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "MVP"; }
};

// NOP No Operation [Flags affected: none]
class NOP
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
class ORA
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "ORA"; }
};

// PEA Push Effective Absolute Address [Flags affected: none]
class PEA
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PEA"; }
};

// PEI Push Effective Indirect Address [Flags affected: none]
class PEI
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PEI"; }
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
class PER
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PER"; }
};

// PHA Push Accumulator [Flags affected: none]
class PHA
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PHA"; }
};

// PHB Push Data Bank Register [Flags affected: none]
class PHB
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PHB"; }
};

// PHD Push Direct Page Register [Flags affected: none]
class PHD
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PHD"; }
};

// PHK Push Program Bank Register [Flags affected: none]
class PHK
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PHK"; }
};

// PHP Push Processor Status Register [Flags affected: none]
class PHP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PHP"; }
};

// PHX Push Index Register X [Flags affected: none]
class PHX
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PHX"; }
};

// PHY Push Index Register Y [Flags affected: none]
class PHY
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PHY"; }
};

// PLA Pull Accumulator [Flags affected: n,z]
class PLA
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PLA"; }
};

// PLB Pull Data Bank Register [Flags affected: n,z]
class PLB
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PLB"; }
};

// PLD Pull Direct Page Register [Flags affected: n,z]
class PLD
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PLD"; }
};

// PLP Pull Processor Status Register [Flags affected: n,z]
class PLP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PLP"; }
};

// PLX Pull Index Register X [Flags affected: n,z]
class PLX
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PLX"; }
};

// PLY Pull Index Register Y [Flags affected: n,z]
class PLY
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "PLY"; }
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
class REP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "REP"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
class ROL
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "ROL"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
class ROR
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "ROR"; }
};

// RTI Return from Interrupt [Flags affected: all except b]
class RTI
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "RTI"; }
};

// RTL Return from Subroutine Long [Flags affected: none]
class RTL
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "RTL"; }
};

// RTS Return from Subroutine [Flags affected: none]
class RTS
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "RTS"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
class SBC
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "SBC"; }
};

// SEC Set Carry Flag [Flags affected: c]
class SEC
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "SEC"; }
};

// SED Set Decimal Flag [Flags affected: d]
class SED
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "SED"; }
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
class SEI
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "SEI"; }
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
class SEP
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "SEP"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
class STA
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "STA"; }
};

// STP Stop Processor [Flags affected: none]
class STP
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "STP"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
class STX
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "STX"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
class STY
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "STY"; }
};

// STZ Store Zero to Memory [Flags affected: none]
class STZ
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "STZ"; }
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
class TAX
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TAX"; }
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
class TAY
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TAY"; }
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
class TCD
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TCD"; }
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
class TCS
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TCS"; }
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
class TDC
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TDC"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
class TRB
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TRB"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
class TSB
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TSB"; }
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
class TSC
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TSC"; }
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
class TSX
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TSX"; }
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
class TXA
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TXA"; }
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
class TXS
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TXS"; }
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
class TXY
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TXY"; }
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
class TYA
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TYA"; }
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
class TYX
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "TYX"; }
};

// WAI Wait for Interrupt [Flags affected: none]
class WAI
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "WAI"; }
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
class WDM
{
public:
    static int operate(State& state, int* data)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "WDM"; }
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
class XBA
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "XBA"; }
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
class XCE
{
public:
    static int operate(State& state)
    {
        int cycles = 0;
        return cycles;
    }

    static std::string toString() { return "XCE"; }
};

}
