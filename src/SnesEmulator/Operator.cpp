#include "Operator.h"

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
int ADC::operate(State& state, int* address)
{
    return 0;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
int AND::operate(State& state, int* address)
{
    return 0;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
int ASL::operate(State& state, int* address)
{
    return 0;
}

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
int BCC::operate(State& state, int* address)
{
    return 0;
}

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
int BCS::operate(State& state, int* address)
{
    return 0;
}

// BEQ Branch if Equal [Flags affected: none]
int BEQ::operate(State& state, int* address)
{
    return 0;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
int BIT::operate(State& state, int* address)
{
    return 0;
}

// BMI Branch if Minus [Flags affected: none]
int BMI::operate(State& state, int* address)
{
    return 0;
}

// BNE Branch if Not Equal [Flags affected: none]
int BNE::operate(State& state, int* address)
{
    return 0;
}

// BPL Branch if Plus [Flags affected: none]
int BPL::operate(State& state, int* address)
{
    return 0;
}

// BRA Branch Always [Flags affected: none]
int BRA::operate(State& state, int* address)
{
    return 0;
}

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
int BRK::operate(State& state, int* address)
{
    return 0;
}

// BRL Branch Long Always [Flags affected: none]
int BRL::operate(State& state, int* address)
{
    return 0;
}

// BVC Branch if Overflow Clear [Flags affected: none]
int BVC::operate(State& state, int* address)
{
    return 0;
}

// BVS Branch if Overflow Set [Flags affected: none]
int BVS::operate(State& state, int* address)
{
    return 0;
}

// CLC Clear Carry [Flags affected: c]
int CLC::operate(State& state)
{
    return 0;
}

// CLD Clear Decimal Mode Flag [Flags affected: d]
int CLD::operate(State& state)
{
    return 0;
}

// CLI Clear Interrupt Disable Flag [Flags affected: i]
int CLI::operate(State& state)
{
    return 0;
}

// CLV Clear Overflow Flag [Flags affected: v]
int CLV::operate(State& state)
{
    return 0;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
int CMP::operate(State& state, int* address)
{
    return 0;
}

// COP Co-Processor Enable [Flags affected: d,i]
int COP::operate(State& state, int* address)
{
    return 0;
}

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
int CPX::operate(State& state, int* address)
{
    return 0;
}

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
int CPY::operate(State& state, int* address)
{
    return 0;
}

// DEC Decrement [Flags affected: n,z]
int DEC::operate(State& state, int* address)
{
    return 0;
}

// DEX Decrement Index Register X [Flags affected: n,z]
int DEX::operate(State& state)
{
    return 0;
}

// DEY Decrement Index Register Y [Flags affected: n,z]
int DEY::operate(State& state)
{
    return 0;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
int EOR::operate(State& state, int* address)
{
    return 0;
}

// INC Increment [Flags affected: n,z]
int INC::operate(State& state, int* address)
{
    return 0;
}

// INX Increment Index Register X [Flags affected: n,z]
int INX::operate(State& state)
{
    return 0;
}

// INY Increment Index Register Y [Flags affected: n,z]
int INY::operate(State& state)
{
    return 0;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
int JMP::operate(State& state, int* address)
{
    return 0;
}

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
int JSR::operate(State& state, int* address)
{
    return 0;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
int LDA::operate(State& state, int* address)
{
    return 0;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]
int LDX::operate(State& state, int* address)
{
    return 0;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]
int LDY::operate(State& state, int* address)
{
    return 0;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
int LSR::operate(State& state, int* address)
{
    return 0;
}

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
int MVN::operate(State& state, int* address)
{
    return 0;
}

// NOP No Operation [Flags affected: none]
int NOP::operate(State& state)
{
    return 0;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
int ORA::operate(State& state, int* address)
{
    return 0;
}

// PEA Push Effective Absolute Address [Flags affected: none]
int PEA::operate(State& state, int* address)
{
    return 0;
}

// PEI Push Effective Indirect Address [Flags affected: none]
int PEI::operate(State& state, int* address)
{
    return 0;
}

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
int PER::operate(State& state, int* address)
{
    return 0;
}

// PHA Push Accumulator [Flags affected: none]
int PHA::operate(State& state, int* address)
{
    return 0;
}

// PHB Push Data Bank Register [Flags affected: none]
int PHB::operate(State& state, int* address)
{
    return 0;
}

// PHD Push Direct Page Register [Flags affected: none]
int PHD::operate(State& state, int* address)
{
    return 0;
}

// PHK Push Program Bank Register [Flags affected: none]
int PHK::operate(State& state, int* address)
{
    return 0;
}

// PHP Push Processor Status Register [Flags affected: none]
int PHP::operate(State& state, int* address)
{
    return 0;
}

// PHX Push Index Register X [Flags affected: none]
int PHX::operate(State& state, int* address)
{
    return 0;
}

// PHY Push Index Register Y [Flags affected: none]
int PHY::operate(State& state, int* address)
{
    return 0;
}

// PLA Pull Accumulator [Flags affected: n,z]
int PLA::operate(State& state, int* address)
{
    return 0;
}

// PLB Pull Data Bank Register [Flags affected: n,z]
int PLB::operate(State& state, int* address)
{
    return 0;
}

// PLD Pull Direct Page Register [Flags affected: n,z]
int PLD::operate(State& state, int* address)
{
    return 0;
}

// PLP Pull Processor Status Register [Flags affected: n,z]
int PLP::operate(State& state, int* address)
{
    return 0;
}

// PLX Pull Index Register X [Flags affected: n,z]
int PLX::operate(State& state, int* address)
{
    return 0;
}

// PLY Pull Index Register Y [Flags affected: n,z]
int PLY::operate(State& state, int* address)
{
    return 0;
}

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
int REP::operate(State& state, int* address)
{
    return 0;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
int ROL::operate(State& state, int* address)
{
    return 0;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
int ROR::operate(State& state, int* address)
{
    return 0;
}

// RTI Return from Interrupt [Flags affected: all except b]
int RTI::operate(State& state, int* address)
{
    return 0;
}

// RTL Return from Subroutine Long [Flags affected: none]
int RTL::operate(State& state, int* address)
{
    return 0;
}

// RTS Return from Subroutine [Flags affected: none]
int RTS::operate(State& state, int* address)
{
    return 0;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
int SBC::operate(State& state, int* address)
{
    return 0;
}

// SEC Set Carry Flag [Flags affected: c]
int SEC::operate(State& state)
{
    return 0;
}

// SED Set Decimal Flag [Flags affected: d]
int SED::operate(State& state)
{
    return 0;
}

// SEI Set Interrupt Disable Flag [Flags affected: i]
int SEI::operate(State& state)
{
    return 0;
}

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
int SEP::operate(State& state, int* address)
{
    return 0;
}

// STA Store Accumulator to Memory [Flags affected: none]
int STA::operate(State& state, int* address)
{
    return 0;
}

// STP Stop Processor [Flags affected: none]
int STP::operate(State& state)
{
    return 0;
}

// STX Store Index Register X to Memory [Flags affected: none]
int STX::operate(State& state, int* address)
{
    return 0;
}

// STY Store Index Register Y to Memory [Flags affected: none]
int STY::operate(State& state, int* address)
{
    return 0;
}

// STZ Store Zero to Memory [Flags affected: none]
int STZ::operate(State& state, int* address)
{
    return 0;
}

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
int TAX::operate(State& state)
{
    return 0;
}

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
int TAY::operate(State& state)
{
    return 0;
}

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
int TCD::operate(State& state)
{
    return 0;
}

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
int TCS::operate(State& state)
{
    return 0;
}

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
int TDC::operate(State& state)
{
    return 0;
}

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
int TRB::operate(State& state, int* address)
{
    return 0;
}

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
int TSB::operate(State& state, int* address)
{
    return 0;
}

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
int TSC::operate(State& state)
{
    return 0;
}

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
int TSX::operate(State& state)
{
    return 0;
}

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
int TXA::operate(State& state)
{
    return 0;
}

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
int TXS::operate(State& state)
{
    return 0;
}

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
int TXY::operate(State& state)
{
    return 0;
}

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
int TYA::operate(State& state)
{
    return 0;
}

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
int TYX::operate(State& state)
{
    return 0;
}

// WAI Wait for Interrupt [Flags affected: none]
int WAI::operate(State& state)
{
    return 0;
}

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
int WDM::operate(State& state, int* address)
{
    return 0;
}

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
int XBA::operate(State& state)
{
    return 0;
}

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
int XCE::operate(State& state)
{
    return 0;
}

}
