#include "Operator.h"

namespace Operator {

// ADC Add With Carry [Flags affected: n,v,z,c]
int ADC::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
int AND::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
int ASL::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
int BCC::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
int BCS::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BEQ Branch if Equal [Flags affected: none]
int BEQ::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
int BIT::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BMI Branch if Minus [Flags affected: none]
int BMI::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BNE Branch if Not Equal [Flags affected: none]
int BNE::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BPL Branch if Plus [Flags affected: none]
int BPL::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BRA Branch Always [Flags affected: none]
int BRA::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
int BRK::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BRL Branch Long Always [Flags affected: none]
int BRL::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BVC Branch if Overflow Clear [Flags affected: none]
int BVC::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// BVS Branch if Overflow Set [Flags affected: none]
int BVS::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// CLC Clear Carry [Flags affected: c]
int CLC::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// CLD Clear Decimal Mode Flag [Flags affected: d]
int CLD::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// CLI Clear Interrupt Disable Flag [Flags affected: i]
int CLI::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// CLV Clear Overflow Flag [Flags affected: v]
int CLV::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
int CMP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// COP Co-Processor Enable [Flags affected: d,i]
int COP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
int CPX::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
int CPY::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// DEC Decrement [Flags affected: n,z]
int DEC::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// DEX Decrement Index Register X [Flags affected: n,z]
int DEX::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// DEY Decrement Index Register Y [Flags affected: n,z]
int DEY::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
int EOR::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// INC Increment [Flags affected: n,z]
int INC::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// INX Increment Index Register X [Flags affected: n,z]
int INX::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// INY Increment Index Register Y [Flags affected: n,z]
int INY::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
int JMP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
int JSR::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
int LDA::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]
int LDX::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]
int LDY::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
int LSR::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
int MVN::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
int MVP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// NOP No Operation [Flags affected: none]
int NOP::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
int ORA::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PEA Push Effective Absolute Address [Flags affected: none]
int PEA::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PEI Push Effective Indirect Address [Flags affected: none]
int PEI::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
int PER::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PHA Push Accumulator [Flags affected: none]
int PHA::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PHB Push Data Bank Register [Flags affected: none]
int PHB::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PHD Push Direct Page Register [Flags affected: none]
int PHD::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PHK Push Program Bank Register [Flags affected: none]
int PHK::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PHP Push Processor Status Register [Flags affected: none]
int PHP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PHX Push Index Register X [Flags affected: none]
int PHX::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PHY Push Index Register Y [Flags affected: none]
int PHY::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PLA Pull Accumulator [Flags affected: n,z]
int PLA::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PLB Pull Data Bank Register [Flags affected: n,z]
int PLB::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PLD Pull Direct Page Register [Flags affected: n,z]
int PLD::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PLP Pull Processor Status Register [Flags affected: n,z]
int PLP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PLX Pull Index Register X [Flags affected: n,z]
int PLX::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// PLY Pull Index Register Y [Flags affected: n,z]
int PLY::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
int REP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
int ROL::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
int ROR::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// RTI Return from Interrupt [Flags affected: all except b]
int RTI::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// RTL Return from Subroutine Long [Flags affected: none]
int RTL::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// RTS Return from Subroutine [Flags affected: none]
int RTS::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
int SBC::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// SEC Set Carry Flag [Flags affected: c]
int SEC::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// SED Set Decimal Flag [Flags affected: d]
int SED::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// SEI Set Interrupt Disable Flag [Flags affected: i]
int SEI::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
int SEP::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
int STA::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// STP Stop Processor [Flags affected: none]
int STP::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// STX Store Index Register X to Memory [Flags affected: none]
int STX::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// STY Store Index Register Y to Memory [Flags affected: none]
int STY::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// STZ Store Zero to Memory [Flags affected: none]
int STZ::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
int TAX::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
int TAY::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
int TCD::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
int TCS::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
int TDC::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
int TRB::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
int TSB::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
int TSC::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
int TSX::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
int TXA::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
int TXS::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
int TXY::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
int TYA::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
int TYX::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// WAI Wait for Interrupt [Flags affected: none]
int WAI::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
int WDM::operate(State& state, int* data)
{
    int cycles = 0;
    return cycles;
}

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
int XBA::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
int XCE::operate(State& state)
{
    int cycles = 0;
    return cycles;
}

}
