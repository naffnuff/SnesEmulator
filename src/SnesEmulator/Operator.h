#pragma once

#include "State.h"

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
class ADC
{
public:
    static int operate(State& state, int* address);
};

// AND AND Accumulator With Memory [Flags affected: n,z]
class AND
{
public:
    static int operate(State& state, int* address);
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
class ASL
{
public:
    static int operate(State& state, int* address);
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
class BCC
{
public:
    static int operate(State& state, int* address);
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
class BCS
{
public:
    static int operate(State& state, int* address);
};

// BEQ Branch if Equal [Flags affected: none]
class BEQ
{
public:
    static int operate(State& state, int* address);
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
class BIT
{
public:
    static int operate(State& state, int* address);
};

// BMI Branch if Minus [Flags affected: none]
class BMI
{
public:
    static int operate(State& state, int* address);
};

// BNE Branch if Not Equal [Flags affected: none]
class BNE
{
public:
    static int operate(State& state, int* address);
};

// BPL Branch if Plus [Flags affected: none]
class BPL
{
public:
    static int operate(State& state, int* address);
};

// BRA Branch Always [Flags affected: none]
class BRA
{
public:
    static int operate(State& state, int* address);
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
class BRK
{
public:
    static int operate(State& state, int* address);
};

// BRL Branch Long Always [Flags affected: none]
class BRL
{
public:
    static int operate(State& state, int* address);
};

// BVC Branch if Overflow Clear [Flags affected: none]
class BVC
{
public:
    static int operate(State& state, int* address);
};

// BVS Branch if Overflow Set [Flags affected: none]
class BVS
{
public:
    static int operate(State& state, int* address);
};

// CLC Clear Carry [Flags affected: c]
class CLC
{
public:
    static int operate(State& state, int* address);
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
class CLD
{
public:
    static int operate(State& state, int* address);
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
class CLI
{
public:
    static int operate(State& state, int* address);
};

// CLV Clear Overflow Flag [Flags affected: v]
class CLV
{
public:
    static int operate(State& state, int* address);
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
class CMP
{
public:
    static int operate(State& state, int* address);
};

// COP Co-Processor Enable [Flags affected: d,i]
class COP
{
public:
    static int operate(State& state, int* address);
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
class CPX
{
public:
    static int operate(State& state, int* address);
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
class CPY
{
public:
    static int operate(State& state, int* address);
};

// DEC Decrement [Flags affected: n,z]
class DEC
{
public:
    static int operate(State& state, int* address);
};

// DEX Decrement Index Register X [Flags affected: n,z]
class DEX
{
public:
    static int operate(State& state, int* address);
};

// DEY Decrement Index Register Y [Flags affected: n,z]
class DEY
{
public:
    static int operate(State& state, int* address);
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
class EOR
{
public:
    static int operate(State& state, int* address);
};

// INC Increment [Flags affected: n,z]
class INC
{
public:
    static int operate(State& state, int* address);
};

// INX Increment Index Register X [Flags affected: n,z]
class INX
{
public:
    static int operate(State& state, int* address);
};

// INY Increment Index Register Y [Flags affected: n,z]
class INY
{
public:
    static int operate(State& state, int* address);
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
class JMP
{
public:
    static int operate(State& state, int* address);
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
class JSR
{
public:
    static int operate(State& state, int* address);
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
class LDA
{
public:
    static int operate(State& state, int* address);
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
class LDX
{
public:
    static int operate(State& state, int* address);
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
class LDY
{
public:
    static int operate(State& state, int* address);
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
class LSR
{
public:
    static int operate(State& state, int* address);
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
class MVN
{
public:
    static int operate(State& state, int* address);
};

// NOP No Operation [Flags affected: none]
class NOP
{
public:
    static int operate(State& state, int* address);
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
class ORA
{
public:
    static int operate(State& state, int* address);
};

// PEA Push Effective Absolute Address [Flags affected: none]
class PEA
{
public:
    static int operate(State& state, int* address);
};

// PEI Push Effective Indirect Address [Flags affected: none]
class PEI
{
public:
    static int operate(State& state, int* address);
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
class PER
{
public:
    static int operate(State& state, int* address);
};

// PHA Push Accumulator [Flags affected: none]
class PHA
{
public:
    static int operate(State& state, int* address);
};

// PHB Push Data Bank Register [Flags affected: none]
class PHB
{
public:
    static int operate(State& state, int* address);
};

// PHD Push Direct Page Register [Flags affected: none]
class PHD
{
public:
    static int operate(State& state, int* address);
};

// PHK Push Program Bank Register [Flags affected: none]
class PHK
{
public:
    static int operate(State& state, int* address);
};

// PHP Push Processor Status Register [Flags affected: none]
class PHP
{
public:
    static int operate(State& state, int* address);
};

// PHX Push Index Register X [Flags affected: none]
class PHX
{
public:
    static int operate(State& state, int* address);
};

// PHY Push Index Register Y [Flags affected: none]
class PHY
{
public:
    static int operate(State& state, int* address);
};

// PLA Pull Accumulator [Flags affected: n,z]
class PLA
{
public:
    static int operate(State& state, int* address);
};

// PLB Pull Data Bank Register [Flags affected: n,z]
class PLB
{
public:
    static int operate(State& state, int* address);
};

// PLD Pull Direct Page Register [Flags affected: n,z]
class PLD
{
public:
    static int operate(State& state, int* address);
};

// PLP Pull Processor Status Register [Flags affected: n,z]
class PLP
{
public:
    static int operate(State& state, int* address);
};

// PLX Pull Index Register X [Flags affected: n,z]
class PLX
{
public:
    static int operate(State& state, int* address);
};

// PLY Pull Index Register Y [Flags affected: n,z]
class PLY
{
public:
    static int operate(State& state, int* address);
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
class REP
{
public:
    static int operate(State& state, int* address);
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
class ROL
{
public:
    static int operate(State& state, int* address);
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
class ROR
{
public:
    static int operate(State& state, int* address);
};

// RTI Return from Interrupt [Flags affected: all except b]
class RTI
{
public:
    static int operate(State& state, int* address);
};

// RTL Return from Subroutine Long [Flags affected: none]
class RTL
{
public:
    static int operate(State& state, int* address);
};

// RTS Return from Subroutine [Flags affected: none]
class RTS
{
public:
    static int operate(State& state, int* address);
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
class SBC
{
public:
    static int operate(State& state, int* address);
};

// SEC Set Carry Flag [Flags affected: c]
class SEC
{
public:
    static int operate(State& state, int* address);
};

// SED Set Decimal Flag [Flags affected: d]
class SED
{
public:
    static int operate(State& state, int* address);
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
class SEI
{
public:
    static int operate(State& state, int* address);
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
class SEP
{
public:
    static int operate(State& state, int* address);
};

// STA Store Accumulator to Memory [Flags affected: none]
class STA
{
public:
    static int operate(State& state, int* address);
};

// STP Stop Processor [Flags affected: none]
class STP
{
public:
    static int operate(State& state, int* address);
};

// STX Store Index Register X to Memory [Flags affected: none]
class STX
{
public:
    static int operate(State& state, int* address);
};

// STY Store Index Register Y to Memory [Flags affected: none]
class STY
{
public:
    static int operate(State& state, int* address);
};

// STZ Store Zero to Memory [Flags affected: none]
class STZ
{
public:
    static int operate(State& state, int* address);
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
class TAX
{
public:
    static int operate(State& state, int* address);
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
class TAY
{
public:
    static int operate(State& state, int* address);
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
class TCD
{
public:
    static int operate(State& state, int* address);
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
class TCS
{
public:
    static int operate(State& state, int* address);
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
class TDC
{
public:
    static int operate(State& state, int* address);
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
class TRB
{
public:
    static int operate(State& state, int* address);
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
class TSB
{
public:
    static int operate(State& state, int* address);
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
class TSC
{
public:
    static int operate(State& state, int* address);
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
class TSX
{
public:
    static int operate(State& state, int* address);
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
class TXA
{
public:
    static int operate(State& state, int* address);
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
class TXS
{
public:
    static int operate(State& state, int* address);
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
class TXY
{
public:
    static int operate(State& state, int* address);
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
class TYA
{
public:
    static int operate(State& state, int* address);
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
class TYX
{
public:
    static int operate(State& state, int* address);
};

// WAI Wait for Interrupt [Flags affected: none]
class WAI
{
public:
    static int operate(State& state, int* address);
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
class WDM
{
public:
    static int operate(State& state, int* address);
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
class XBA
{
public:
    static int operate(State& state, int* address);
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
class XCE
{
public:
    static int operate(State& state, int* address);
};

}
