#pragma once

#include "State.h"

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
class ADC
{
public:
    static std::string toString() { return "ADC"; }
    static int operate(State& state, int* data);
};

// AND AND Accumulator With Memory [Flags affected: n,z]
class AND
{
public:
    static std::string toString() { return "AND"; }
    static int operate(State& state, int* data);
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
class ASL
{
public:
    static std::string toString() { return "ASL"; }
    static int operate(State& state, int* data);
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
class BCC
{
public:
    static std::string toString() { return "BCC"; }
    static int operate(State& state, int* data);
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
class BCS
{
public:
    static std::string toString() { return "BCS"; }
    static int operate(State& state, int* data);
};

// BEQ Branch if Equal [Flags affected: none]
class BEQ
{
public:
    static std::string toString() { return "BEQ"; }
    static int operate(State& state, int* data);
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
class BIT
{
public:
    static std::string toString() { return "BIT"; }
    static int operate(State& state, int* data);
};

// BMI Branch if Minus [Flags affected: none]
class BMI
{
public:
    static std::string toString() { return "BMI"; }
    static int operate(State& state, int* data);
};

// BNE Branch if Not Equal [Flags affected: none]
class BNE
{
public:
    static std::string toString() { return "BNE"; }
    static int operate(State& state, int* data);
};

// BPL Branch if Plus [Flags affected: none]
class BPL
{
public:
    static std::string toString() { return "BPL"; }
    static int operate(State& state, int* data);
};

// BRA Branch Always [Flags affected: none]
class BRA
{
public:
    static std::string toString() { return "BRA"; }
    static int operate(State& state, int* data);
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
class BRK
{
public:
    static std::string toString() { return "BRK"; }
    static int operate(State& state, int* data);
};

// BRL Branch Long Always [Flags affected: none]
class BRL
{
public:
    static std::string toString() { return "BRL"; }
    static int operate(State& state, int* data);
};

// BVC Branch if Overflow Clear [Flags affected: none]
class BVC
{
public:
    static std::string toString() { return "BVC"; }
    static int operate(State& state, int* data);
};

// BVS Branch if Overflow Set [Flags affected: none]
class BVS
{
public:
    static std::string toString() { return "BVS"; }
    static int operate(State& state, int* data);
};

// CLC Clear Carry [Flags affected: c]
class CLC
{
public:
    static std::string toString() { return "CLC"; }
    static int operate(State& state);
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
class CLD
{
public:
    static std::string toString() { return "CLD"; }
    static int operate(State& state);
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
class CLI
{
public:
    static std::string toString() { return "CLI"; }
    static int operate(State& state);
};

// CLV Clear Overflow Flag [Flags affected: v]
class CLV
{
public:
    static std::string toString() { return "CLV"; }
    static int operate(State& state);
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
class CMP
{
public:
    static std::string toString() { return "CMP"; }
    static int operate(State& state, int* data);
};

// COP Co-Processor Enable [Flags affected: d,i]
class COP
{
public:
    static std::string toString() { return "COP"; }
    static int operate(State& state, int* data);
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
class CPX
{
public:
    static std::string toString() { return "CPX"; }
    static int operate(State& state, int* data);
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
class CPY
{
public:
    static std::string toString() { return "CPY"; }
    static int operate(State& state, int* data);
};

// DEC Decrement [Flags affected: n,z]
class DEC
{
public:
    static std::string toString() { return "DEC"; }
    static int operate(State& state, int* data);
};

// DEX Decrement Index Register X [Flags affected: n,z]
class DEX
{
public:
    static std::string toString() { return "DEX"; }
    static int operate(State& state);
};

// DEY Decrement Index Register Y [Flags affected: n,z]
class DEY
{
public:
    static std::string toString() { return "DEY"; }
    static int operate(State& state);
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
class EOR
{
public:
    static std::string toString() { return "EOR"; }
    static int operate(State& state, int* data);
};

// INC Increment [Flags affected: n,z]
class INC
{
public:
    static std::string toString() { return "INC"; }
    static int operate(State& state, int* data);
};

// INX Increment Index Register X [Flags affected: n,z]
class INX
{
public:
    static std::string toString() { return "INX"; }
    static int operate(State& state);
};

// INY Increment Index Register Y [Flags affected: n,z]
class INY
{
public:
    static std::string toString() { return "INY"; }
    static int operate(State& state);
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
class JMP
{
public:
    static std::string toString() { return "JMP"; }
    static int operate(State& state, int* data);
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
class JSR
{
public:
    static std::string toString() { return "JSR"; }
    static int operate(State& state, int* data);
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
class LDA
{
public:
    static std::string toString() { return "LDA"; }
    static int operate(State& state, int* data);
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
class LDX
{
public:
    static std::string toString() { return "LDX"; }
    static int operate(State& state, int* data);
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
class LDY
{
public:
    static std::string toString() { return "LDY"; }
    static int operate(State& state, int* data);
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
class LSR
{
public:
    static std::string toString() { return "LSR"; }
    static int operate(State& state, int* data);
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
class MVN
{
public:
    static std::string toString() { return "MVN"; }
    static int operate(State& state, int* data);
};

// NOP No Operation [Flags affected: none]
class NOP
{
public:
    static std::string toString() { return "NOP"; }
    static int operate(State& state);
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
class ORA
{
public:
    static std::string toString() { return "ORA"; }
    static int operate(State& state, int* data);
};

// PEA Push Effective Absolute Address [Flags affected: none]
class PEA
{
public:
    static std::string toString() { return "PEA"; }
    static int operate(State& state, int* data);
};

// PEI Push Effective Indirect Address [Flags affected: none]
class PEI
{
public:
    static std::string toString() { return "PEI"; }
    static int operate(State& state, int* data);
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
class PER
{
public:
    static std::string toString() { return "PER"; }
    static int operate(State& state, int* data);
};

// PHA Push Accumulator [Flags affected: none]
class PHA
{
public:
    static std::string toString() { return "PHA"; }
    static int operate(State& state, int* data);
};

// PHB Push Data Bank Register [Flags affected: none]
class PHB
{
public:
    static std::string toString() { return "PHB"; }
    static int operate(State& state, int* data);
};

// PHD Push Direct Page Register [Flags affected: none]
class PHD
{
public:
    static std::string toString() { return "PHD"; }
    static int operate(State& state, int* data);
};

// PHK Push Program Bank Register [Flags affected: none]
class PHK
{
public:
    static std::string toString() { return "PHK"; }
    static int operate(State& state, int* data);
};

// PHP Push Processor Status Register [Flags affected: none]
class PHP
{
public:
    static std::string toString() { return "PHP"; }
    static int operate(State& state, int* data);
};

// PHX Push Index Register X [Flags affected: none]
class PHX
{
public:
    static std::string toString() { return "PHX"; }
    static int operate(State& state, int* data);
};

// PHY Push Index Register Y [Flags affected: none]
class PHY
{
public:
    static std::string toString() { return "PHY"; }
    static int operate(State& state, int* data);
};

// PLA Pull Accumulator [Flags affected: n,z]
class PLA
{
public:
    static std::string toString() { return "PLA"; }
    static int operate(State& state, int* data);
};

// PLB Pull Data Bank Register [Flags affected: n,z]
class PLB
{
public:
    static std::string toString() { return "PLB"; }
    static int operate(State& state, int* data);
};

// PLD Pull Direct Page Register [Flags affected: n,z]
class PLD
{
public:
    static std::string toString() { return "PLD"; }
    static int operate(State& state, int* data);
};

// PLP Pull Processor Status Register [Flags affected: n,z]
class PLP
{
public:
    static std::string toString() { return "PLP"; }
    static int operate(State& state, int* data);
};

// PLX Pull Index Register X [Flags affected: n,z]
class PLX
{
public:
    static std::string toString() { return "PLX"; }
    static int operate(State& state, int* data);
};

// PLY Pull Index Register Y [Flags affected: n,z]
class PLY
{
public:
    static std::string toString() { return "PLY"; }
    static int operate(State& state, int* data);
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
class REP
{
public:
    static std::string toString() { return "REP"; }
    static int operate(State& state, int* data);
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
class ROL
{
public:
    static std::string toString() { return "ROL"; }
    static int operate(State& state, int* data);
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
class ROR
{
public:
    static std::string toString() { return "ROR"; }
    static int operate(State& state, int* data);
};

// RTI Return from Interrupt [Flags affected: all except b]
class RTI
{
public:
    static std::string toString() { return "RTI"; }
    static int operate(State& state, int* data);
};

// RTL Return from Subroutine Long [Flags affected: none]
class RTL
{
public:
    static std::string toString() { return "RTL"; }
    static int operate(State& state, int* data);
};

// RTS Return from Subroutine [Flags affected: none]
class RTS
{
public:
    static std::string toString() { return "RTS"; }
    static int operate(State& state, int* data);
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
class SBC
{
public:
    static std::string toString() { return "SBC"; }
    static int operate(State& state, int* data);
};

// SEC Set Carry Flag [Flags affected: c]
class SEC
{
public:
    static std::string toString() { return "SEC"; }
    static int operate(State& state);
};

// SED Set Decimal Flag [Flags affected: d]
class SED
{
public:
    static std::string toString() { return "SED"; }
    static int operate(State& state);
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
class SEI
{
public:
    static std::string toString() { return "SEI"; }
    static int operate(State& state);
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
class SEP
{
public:
    static std::string toString() { return "SEP"; }
    static int operate(State& state, int* data);
};

// STA Store Accumulator to Memory [Flags affected: none]
class STA
{
public:
    static std::string toString() { return "STA"; }
    static int operate(State& state, int* data);
};

// STP Stop Processor [Flags affected: none]
class STP
{
public:
    static std::string toString() { return "STP"; }
    static int operate(State& state);
};

// STX Store Index Register X to Memory [Flags affected: none]
class STX
{
public:
    static std::string toString() { return "STX"; }
    static int operate(State& state, int* data);
};

// STY Store Index Register Y to Memory [Flags affected: none]
class STY
{
public:
    static std::string toString() { return "STY"; }
    static int operate(State& state, int* data);
};

// STZ Store Zero to Memory [Flags affected: none]
class STZ
{
public:
    static std::string toString() { return "STZ"; }
    static int operate(State& state, int* data);
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
class TAX
{
public:
    static std::string toString() { return "TAX"; }
    static int operate(State& state);
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
class TAY
{
public:
    static std::string toString() { return "TAY"; }
    static int operate(State& state);
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
class TCD
{
public:
    static std::string toString() { return "TCD"; }
    static int operate(State& state);
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
class TCS
{
public:
    static std::string toString() { return "TCS"; }
    static int operate(State& state);
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
class TDC
{
public:
    static std::string toString() { return "TDC"; }
    static int operate(State& state);
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
class TRB
{
public:
    static std::string toString() { return "TRB"; }
    static int operate(State& state, int* data);
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
class TSB
{
public:
    static std::string toString() { return "TSB"; }
    static int operate(State& state, int* data);
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
class TSC
{
public:
    static std::string toString() { return "TSC"; }
    static int operate(State& state);
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
class TSX
{
public:
    static std::string toString() { return "TSX"; }
    static int operate(State& state);
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
class TXA
{
public:
    static std::string toString() { return "TXA"; }
    static int operate(State& state);
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
class TXS
{
public:
    static std::string toString() { return "TXS"; }
    static int operate(State& state);
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
class TXY
{
public:
    static std::string toString() { return "TXY"; }
    static int operate(State& state);
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
class TYA
{
public:
    static std::string toString() { return "TYA"; }
    static int operate(State& state);
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
class TYX
{
public:
    static std::string toString() { return "TYX"; }
    static int operate(State& state);
};

// WAI Wait for Interrupt [Flags affected: none]
class WAI
{
public:
    static std::string toString() { return "WAI"; }
    static int operate(State& state);
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
class WDM
{
public:
    static std::string toString() { return "WDM"; }
    static int operate(State& state, int* data);
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
class XBA
{
public:
    static std::string toString() { return "XBA"; }
    static int operate(State& state);
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
class XCE
{
public:
    static std::string toString() { return "XCE"; }
    static int operate(State& state);
};

}
