#pragma once

#include <stdint.h>

#include "State.h"
#include "Instruction.h"
#include "AddressMode.h"
#include "Operator.h"

namespace Opcode {

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp,X)
// Direct Page Indexed Indirect, X
class ADC_61 : public AddressMode::DirectPageIndexedIndirectX<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC sr,S
// Stack Relative
class ADC_63 : public AddressMode::StackRelative<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC sr,S"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp
// Direct Page
class ADC_65 : public AddressMode::DirectPage<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC dp"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp]
// Direct Page Indirect Long
class ADC_67 : public AddressMode::DirectPageIndirectLong<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC [dp]"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class ADC_69 : public AddressMode::ImmediateFlagSize<Operator::ADC, State::m>
{
    std::string opcodeToString() const override { return "ADC #const"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr
// Absolute
class ADC_6D : public AddressMode::Absolute<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC addr"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long
// Absolute Long
class ADC_6F : public AddressMode::AbsoluteLong<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC long"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp),Y
// Direct Page Indirect Indexed, Y
class ADC_71 : public AddressMode::DirectPageIndirectIndexedY<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp)
// Direct Page Indirect
class ADC_72 : public AddressMode::DirectPageIndirect<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC (dp)"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (sr,S),Y
// Stack Relative Indirect Indexed, Y
class ADC_73 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp,X
// Direct Page Indexed,X
class ADC_75 : public AddressMode::DirectPageIndexedX<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC dp,X"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp],Y
// Direct Page Indirect Long Indexed, Y
class ADC_77 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,Y
// Absolute Indexed,Y
class ADC_79 : public AddressMode::AbsoluteIndexedY<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,X
// Absolute Indexed,X
class ADC_7D : public AddressMode::AbsoluteIndexedX<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC addr,X"; }
    int calculateCycles(const State& state) const override;
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long,X
// Absolute Long Indexed, X
class ADC_7F : public AddressMode::AbsoluteLongIndexedX<Operator::ADC>
{
    std::string opcodeToString() const override { return "ADC long,X"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp,X)
// Direct Page Indexed Indirect, X
class AND_21 : public AddressMode::DirectPageIndexedIndirectX<Operator::AND>
{
    std::string opcodeToString() const override { return "AND (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND sr,S
// Stack Relative
class AND_23 : public AddressMode::StackRelative<Operator::AND>
{
    std::string opcodeToString() const override { return "AND sr,S"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp
// Direct Page
class AND_25 : public AddressMode::DirectPage<Operator::AND>
{
    std::string opcodeToString() const override { return "AND dp"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp]
// Direct Page Indirect Long
class AND_27 : public AddressMode::DirectPageIndirectLong<Operator::AND>
{
    std::string opcodeToString() const override { return "AND [dp]"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class AND_29 : public AddressMode::ImmediateFlagSize<Operator::AND, State::m>
{
    std::string opcodeToString() const override { return "AND #const"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr
// Absolute
class AND_2D : public AddressMode::Absolute<Operator::AND>
{
    std::string opcodeToString() const override { return "AND addr"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long
// Absolute Long
class AND_2F : public AddressMode::AbsoluteLong<Operator::AND>
{
    std::string opcodeToString() const override { return "AND long"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp),Y
// Direct Page Indirect Indexed, Y
class AND_31 : public AddressMode::DirectPageIndirectIndexedY<Operator::AND>
{
    std::string opcodeToString() const override { return "AND (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp)
// Direct Page Indirect
class AND_32 : public AddressMode::DirectPageIndirect<Operator::AND>
{
    std::string opcodeToString() const override { return "AND (dp)"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (sr,S),Y
// Stack Relative Indirect Indexed, Y
class AND_33 : public AddressMode::StackRelativeIndirectIndexedY<Operator::AND>
{
    std::string opcodeToString() const override { return "AND (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp,X
// Direct Page Indexed, X
class AND_35 : public AddressMode::DirectPageIndexedX<Operator::AND>
{
    std::string opcodeToString() const override { return "AND dp,X"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp],Y
// Direct Page Indirect Long Indexed, Y
class AND_37 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::AND>
{
    std::string opcodeToString() const override { return "AND [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,Y
// Absolute Indexed, Y
class AND_39 : public AddressMode::AbsoluteIndexedY<Operator::AND>
{
    std::string opcodeToString() const override { return "AND addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,X
// Absolute Indexed, X
class AND_3D : public AddressMode::AbsoluteIndexedX<Operator::AND>
{
    std::string opcodeToString() const override { return "AND addr,X"; }
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long,X
// Absolute Long Indexed, X
class AND_3F : public AddressMode::AbsoluteLongIndexedX<Operator::AND>
{
    std::string opcodeToString() const override { return "AND long,X"; }
    int calculateCycles(const State& state) const override;
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp
// Direct Page
class ASL_06 : public AddressMode::DirectPage<Operator::ASL>
{
    std::string opcodeToString() const override { return "ASL dp"; }
    int calculateCycles(const State& state) const override;
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL A
// Accumulator
class ASL_0A : public AddressMode::Accumulator<Operator::ASL>
{
    std::string opcodeToString() const override { return "ASL A"; }
    int calculateCycles(const State& state) const override;
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr
// Absolute
class ASL_0E : public AddressMode::Absolute<Operator::ASL>
{
    std::string opcodeToString() const override { return "ASL addr"; }
    int calculateCycles(const State& state) const override;
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp,X
// Direct Page Indexed, X
class ASL_16 : public AddressMode::DirectPageIndexedX<Operator::ASL>
{
    std::string opcodeToString() const override { return "ASL dp,X"; }
    int calculateCycles(const State& state) const override;
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr,X
// Absolute Indexed, X
class ASL_1E : public AddressMode::AbsoluteIndexedX<Operator::ASL>
{
    std::string opcodeToString() const override { return "ASL addr,X"; }
    int calculateCycles(const State& state) const override;
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
// BCC nearlabel
// Program Counter Relative
class BCC_90 : public AddressMode::ProgramCounterRelative<Operator::BCC>
{
    std::string opcodeToString() const override { return "BCC nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
// BCS nearlabel
// Program Counter Relative
class BCS_B0 : public AddressMode::ProgramCounterRelative<Operator::BCS>
{
    std::string opcodeToString() const override { return "BCS nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BEQ Branch if Equal [Flags affected: none]
// BEQ nearlabel
// Program Counter Relative
class BEQ_F0 : public AddressMode::ProgramCounterRelative<Operator::BEQ>
{
    std::string opcodeToString() const override { return "BEQ nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp
// Direct Page
class BIT_24 : public AddressMode::DirectPage<Operator::BIT>
{
    std::string opcodeToString() const override { return "BIT dp"; }
    int calculateCycles(const State& state) const override;
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr
// Absolute
class BIT_2C : public AddressMode::Absolute<Operator::BIT>
{
    std::string opcodeToString() const override { return "BIT addr"; }
    int calculateCycles(const State& state) const override;
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp,X
// Direct Page Indexed, X
class BIT_34 : public AddressMode::DirectPageIndexedX<Operator::BIT>
{
    std::string opcodeToString() const override { return "BIT dp,X"; }
    int calculateCycles(const State& state) const override;
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr,X
// Absolute Indexed, X
class BIT_3C : public AddressMode::AbsoluteIndexedX<Operator::BIT>
{
    std::string opcodeToString() const override { return "BIT addr,X"; }
    int calculateCycles(const State& state) const override;
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class BIT_89 : public AddressMode::ImmediateFlagSize<Operator::BIT, State::m>
{
    std::string opcodeToString() const override { return "BIT #const"; }
    int calculateCycles(const State& state) const override;
};

// BMI Branch if Minus [Flags affected: none]
// BMI nearlabel
// Program Counter Relative
class BMI_30 : public AddressMode::ProgramCounterRelative<Operator::BMI>
{
    std::string opcodeToString() const override { return "BMI nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BNE Branch if Not Equal [Flags affected: none]
// BNE nearlabel
// Program Counter Relative
class BNE_D0 : public AddressMode::ProgramCounterRelative<Operator::BNE>
{
    std::string opcodeToString() const override { return "BNE nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BPL Branch if Plus [Flags affected: none]
// BPL nearlabel
// Program Counter Relative
class BPL_10 : public AddressMode::ProgramCounterRelative<Operator::BPL>
{
    std::string opcodeToString() const override { return "BPL nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BRA Branch Always [Flags affected: none]
// BRA nearlabel
// Program Counter Relative
class BRA_80 : public AddressMode::ProgramCounterRelative<Operator::BRA>
{
    std::string opcodeToString() const override { return "BRA nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
// BRK
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class BRK_00 : public AddressMode::StackInterrupt<Operator::BRK>
{
    std::string opcodeToString() const override { return "BRK"; }
    int calculateCycles(const State& state) const override;
};

// BRL Branch Long Always [Flags affected: none]
// BRL label
// Program Counter Relative Long
class BRL_82 : public AddressMode::ProgramCounterRelativeLong<Operator::BRL>
{
    std::string opcodeToString() const override { return "BRL label"; }
    int calculateCycles(const State& state) const override;
};

// BVC Branch if Overflow Clear [Flags affected: none]
// BVC nearlabel
// Program Counter Relative
class BVC_50 : public AddressMode::ProgramCounterRelative<Operator::BVC>
{
    std::string opcodeToString() const override { return "BVC nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// BVS Branch if Overflow Set [Flags affected: none]
// BVS nearlabel
// Program Counter Relative
class BVS_70 : public AddressMode::ProgramCounterRelative<Operator::BVS>
{
    std::string opcodeToString() const override { return "BVS nearlabel"; }
    int calculateCycles(const State& state) const override;
};

// CLC Clear Carry [Flags affected: c]
// CLC
// Implied
class CLC_18 : public AddressMode::Implied<Operator::CLC>
{
    std::string opcodeToString() const override { return "CLC"; }
    int calculateCycles(const State& state) const override;
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
// CLD
// Implied
class CLD_D8 : public AddressMode::Implied<Operator::CLD>
{
    std::string opcodeToString() const override { return "CLD"; }
    int calculateCycles(const State& state) const override;
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
// CLI
// Implied
class CLI_58 : public AddressMode::Implied<Operator::CLI>
{
    std::string opcodeToString() const override { return "CLI"; }
    int calculateCycles(const State& state) const override;
};

// CLV Clear Overflow Flag [Flags affected: v]
// CLV
// Implied
class CLV_B8 : public AddressMode::Implied<Operator::CLV>
{
    std::string opcodeToString() const override { return "CLV"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp,X)
// Direct Page Indexed Indirect,X
class CMP_C1 : public AddressMode::DirectPageIndexedIndirectX<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP sr,S
// Stack Relative
class CMP_C3 : public AddressMode::StackRelative<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP sr,S"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp
// Direct Page
class CMP_C5 : public AddressMode::DirectPage<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP dp"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp]
// Direct Page Indirect Long
class CMP_C7 : public AddressMode::DirectPageIndirectLong<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP [dp]"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class CMP_C9 : public AddressMode::ImmediateFlagSize<Operator::CMP, State::m>
{
    std::string opcodeToString() const override { return "CMP #const"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr
// Absolute
class CMP_CD : public AddressMode::Absolute<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP addr"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long
// Absolute Long
class CMP_CF : public AddressMode::AbsoluteLong<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP long"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp),Y
// Direct Page Indirect Indexed, Y
class CMP_D1 : public AddressMode::DirectPageIndirectIndexedY<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp)
// Direct Page Indirect
class CMP_D2 : public AddressMode::DirectPageIndirect<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP (dp)"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (sr,S),Y
// Stack Relative Indirect Indexed,Y
class CMP_D3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp,X
// Direct Page Indexed, X
class CMP_D5 : public AddressMode::DirectPageIndexedX<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP dp,X"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp],Y
// Direct Page Indirect Long Indexed, Y
class CMP_D7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,Y
// Absolute Indexed, Y
class CMP_D9 : public AddressMode::AbsoluteIndexedY<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,X
// Absolute Indexed, X
class CMP_DD : public AddressMode::AbsoluteIndexedX<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP addr,X"; }
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long,X
// Absolute Long Indexed, X
class CMP_DF : public AddressMode::AbsoluteLongIndexedX<Operator::CMP>
{
    std::string opcodeToString() const override { return "CMP long,X"; }
    int calculateCycles(const State& state) const override;
};

// COP Co-Processor Enable [Flags affected: d,i]
// COP const
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class COP_02 : public AddressMode::StackInterrupt<Operator::COP>
{
    std::string opcodeToString() const override { return "COP const"; }
    int calculateCycles(const State& state) const override;
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class CPX_E0 : public AddressMode::ImmediateFlagSize<Operator::CPX, State::x>
{
    std::string opcodeToString() const override { return "CPX #const"; }
    int calculateCycles(const State& state) const override;
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX dp
// Direct Page
class CPX_E4 : public AddressMode::DirectPage<Operator::CPX>
{
    std::string opcodeToString() const override { return "CPX dp"; }
    int calculateCycles(const State& state) const override;
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX addr
// Absolute
class CPX_EC : public AddressMode::Absolute<Operator::CPX>
{
    std::string opcodeToString() const override { return "CPX addr"; }
    int calculateCycles(const State& state) const override;
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class CPY_C0 : public AddressMode::ImmediateFlagSize<Operator::CPY, State::x>
{
    std::string opcodeToString() const override { return "CPY #const"; }
    int calculateCycles(const State& state) const override;
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY dp
// Direct Page
class CPY_C4 : public AddressMode::DirectPage<Operator::CPY>
{
    std::string opcodeToString() const override { return "CPY dp"; }
    int calculateCycles(const State& state) const override;
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY addr
// Absolute
class CPY_CC : public AddressMode::Absolute<Operator::CPY>
{
    std::string opcodeToString() const override { return "CPY addr"; }
    int calculateCycles(const State& state) const override;
};

// DEC Decrement [Flags affected: n,z]
// DEC A
// Accumulator
class DEC_3A : public AddressMode::Accumulator<Operator::DEC>
{
    std::string opcodeToString() const override { return "DEC A"; }
    int calculateCycles(const State& state) const override;
};

// DEC Decrement [Flags affected: n,z]
// DEC dp
// Direct Page
class DEC_C6 : public AddressMode::DirectPage<Operator::DEC>
{
    std::string opcodeToString() const override { return "DEC dp"; }
    int calculateCycles(const State& state) const override;
};

// DEC Decrement [Flags affected: n,z]
// DEC addr
// Absolute
class DEC_CE : public AddressMode::Absolute<Operator::DEC>
{
    std::string opcodeToString() const override { return "DEC addr"; }
    int calculateCycles(const State& state) const override;
};

// DEC Decrement [Flags affected: n,z]
// DEC dp,X
// Direct Page Indexed, X
class DEC_D6 : public AddressMode::DirectPageIndexedX<Operator::DEC>
{
    std::string opcodeToString() const override { return "DEC dp,X"; }
    int calculateCycles(const State& state) const override;
};

// DEC Decrement [Flags affected: n,z]
// DEC addr,X
// Absolute Indexed, X
class DEC_DE : public AddressMode::AbsoluteIndexedX<Operator::DEC>
{
    std::string opcodeToString() const override { return "DEC addr,X"; }
    int calculateCycles(const State& state) const override;
};

// DEX Decrement Index Register X [Flags affected: n,z]
// DEX
// Implied
class DEX_CA : public AddressMode::Implied<Operator::DEX>
{
    std::string opcodeToString() const override { return "DEX"; }
    int calculateCycles(const State& state) const override;
};

// DEY Decrement Index Register Y [Flags affected: n,z]
// DEY
// Implied
class DEY_88 : public AddressMode::Implied<Operator::DEY>
{
    std::string opcodeToString() const override { return "DEY"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp,X)
// Direct Page Indexed Indirect,X
class EOR_41 : public AddressMode::DirectPageIndexedIndirectX<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR sr,S
// Stack Relative
class EOR_43 : public AddressMode::StackRelative<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR sr,S"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp
// Direct Page
class EOR_45 : public AddressMode::DirectPage<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR dp"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp]
// Direct Page Indirect Long
class EOR_47 : public AddressMode::DirectPageIndirectLong<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR [dp]"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class EOR_49 : public AddressMode::ImmediateFlagSize<Operator::EOR, State::m>
{
    std::string opcodeToString() const override { return "EOR #const"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr
// Absolute
class EOR_4D : public AddressMode::Absolute<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR addr"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long
// Absolute Long
class EOR_4F : public AddressMode::AbsoluteLong<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR long"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp),Y
// Direct Page Indirect Indexed, Y
class EOR_51 : public AddressMode::DirectPageIndirectIndexedY<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp)
// Direct Page Indirect
class EOR_52 : public AddressMode::DirectPageIndirect<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR (dp)"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (sr,S),Y
// Stack Relative Indirect Indexed, Y
class EOR_53 : public AddressMode::StackRelativeIndirectIndexedY<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp,X
// Direct Page Indexed, X
class EOR_55 : public AddressMode::DirectPageIndexedX<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR dp,X"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp],Y
// Direct Page Indirect Long Indexed, Y
class EOR_57 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,Y
// Absolute Indexed, Y
class EOR_59 : public AddressMode::AbsoluteIndexedY<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,X
// Absolute Indexed, X
class EOR_5D : public AddressMode::AbsoluteIndexedX<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR addr,X"; }
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long,X
// Absolute Long Indexed,X
class EOR_5F : public AddressMode::AbsoluteLongIndexedX<Operator::EOR>
{
    std::string opcodeToString() const override { return "EOR long,X"; }
    int calculateCycles(const State& state) const override;
};

// INC Increment [Flags affected: n,z]
// INC A
// Accumulator
class INC_1A : public AddressMode::Accumulator<Operator::INC>
{
    std::string opcodeToString() const override { return "INC A"; }
    int calculateCycles(const State& state) const override;
};

// INC Increment [Flags affected: n,z]
// INC dp
// Direct Page
class INC_E6 : public AddressMode::DirectPage<Operator::INC>
{
    std::string opcodeToString() const override { return "INC dp"; }
    int calculateCycles(const State& state) const override;
};

// INC Increment [Flags affected: n,z]
// INC addr
// Absolute
class INC_EE : public AddressMode::Absolute<Operator::INC>
{
    std::string opcodeToString() const override { return "INC addr"; }
    int calculateCycles(const State& state) const override;
};

// INC Increment [Flags affected: n,z]
// INC dp,X
// Direct Page Indexed, X
class INC_F6 : public AddressMode::DirectPageIndexedX<Operator::INC>
{
    std::string opcodeToString() const override { return "INC dp,X"; }
    int calculateCycles(const State& state) const override;
};

// INC Increment [Flags affected: n,z]
// INC addr,X
// Absolute Indexed, X
class INC_FE : public AddressMode::AbsoluteIndexedX<Operator::INC>
{
    std::string opcodeToString() const override { return "INC addr,X"; }
    int calculateCycles(const State& state) const override;
};

// INX Increment Index Register X [Flags affected: n,z]
// INX
// Implied
class INX_E8 : public AddressMode::Implied<Operator::INX>
{
    std::string opcodeToString() const override { return "INX"; }
    int calculateCycles(const State& state) const override;
};

// INY Increment Index Register Y [Flags affected: n,z]
// INY
// Implied
class INY_C8 : public AddressMode::Implied<Operator::INY>
{
    std::string opcodeToString() const override { return "INY"; }
    int calculateCycles(const State& state) const override;
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP addr
// Absolute
class JMP_4C : public AddressMode::Absolute<Operator::JMP>
{
    std::string opcodeToString() const override { return "JMP addr"; }
    int calculateCycles(const State& state) const override;
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP long
// Absolute Long
class JMP_5C : public AddressMode::AbsoluteLong<Operator::JMP>
{
    std::string opcodeToString() const override { return "JMP long"; }
    int calculateCycles(const State& state) const override;
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr)
// Absolute Indirect
class JMP_6C : public AddressMode::AbsoluteIndirect<Operator::JMP>
{
    std::string opcodeToString() const override { return "JMP (addr)"; }
    int calculateCycles(const State& state) const override;
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr,X)
// Absolute Indexed Indirect
class JMP_7C : public AddressMode::AbsoluteIndexedIndirect<Operator::JMP>
{
    std::string opcodeToString() const override { return "JMP (addr,X)"; }
    int calculateCycles(const State& state) const override;
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP [addr]
// Absolute Indirect Long
class JMP_DC : public AddressMode::AbsoluteIndirectLong<Operator::JMP>
{
    std::string opcodeToString() const override { return "JMP [addr]"; }
    int calculateCycles(const State& state) const override;
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR addr
// Absolute
class JSR_20 : public AddressMode::Absolute<Operator::JSR>
{
    std::string opcodeToString() const override { return "JSR addr"; }
    int calculateCycles(const State& state) const override;
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR long
// Absolute Long
class JSR_22 : public AddressMode::AbsoluteLong<Operator::JSR>
{
    std::string opcodeToString() const override { return "JSR long"; }
    int calculateCycles(const State& state) const override;
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR (addr,X)
// Absolute Indexed Indirect
class JSR_FC : public AddressMode::AbsoluteIndexedIndirect<Operator::JSR>
{
    std::string opcodeToString() const override { return "JSR (addr,X)"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp,X)
// Direct Page Indexed Indirect, X
class LDA_A1 : public AddressMode::DirectPageIndexedIndirectX<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA sr,S
// Stack Relative
class LDA_A3 : public AddressMode::StackRelative<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA sr,S"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp
// Direct Page
class LDA_A5 : public AddressMode::DirectPage<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA dp"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp]
// Direct Page Indirect Long
class LDA_A7 : public AddressMode::DirectPageIndirectLong<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA [dp]"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class LDA_A9 : public AddressMode::ImmediateFlagSize<Operator::LDA, State::m>
{
    std::string opcodeToString() const override { return "LDA #const"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr
// Absolute
class LDA_AD : public AddressMode::Absolute<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA addr"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long
// Absolute Long
class LDA_AF : public AddressMode::AbsoluteLong<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA long"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp),Y
// Direct Page Indirect Indexed, Y
class LDA_B1 : public AddressMode::DirectPageIndirectIndexedY<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp)
// Direct Page Indirect
class LDA_B2 : public AddressMode::DirectPageIndirect<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA (dp)"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (sr,S),Y
// Stack Relative Indirect Indexed, Y
class LDA_B3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp,X
// Direct Page Indexed, X
class LDA_B5 : public AddressMode::DirectPageIndexedX<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA dp,X"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp],Y
// Direct Page Indirect Long Indexed, Y
class LDA_B7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,Y
// Absolute Indexed, Y
class LDA_B9 : public AddressMode::AbsoluteIndexedY<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,X
// Absolute Indexed, X
class LDA_BD : public AddressMode::AbsoluteIndexedX<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA addr,X"; }
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long,X
// Absolute Long Indexed, X
class LDA_BF : public AddressMode::AbsoluteLongIndexedX<Operator::LDA>
{
    std::string opcodeToString() const override { return "LDA long,X"; }
    int calculateCycles(const State& state) const override;
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class LDX_A2 : public AddressMode::ImmediateFlagSize<Operator::LDX, State::x>
{
    std::string opcodeToString() const override { return "LDX #const"; }
    int calculateCycles(const State& state) const override;
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp
// Direct Page
class LDX_A6 : public AddressMode::DirectPage<Operator::LDX>
{
    std::string opcodeToString() const override { return "LDX dp"; }
    int calculateCycles(const State& state) const override;
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr
// Absolute
class LDX_AE : public AddressMode::Absolute<Operator::LDX>
{
    std::string opcodeToString() const override { return "LDX addr"; }
    int calculateCycles(const State& state) const override;
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp,Y
// Direct Page Indexed, Y
class LDX_B6 : public AddressMode::DirectPageIndexedY<Operator::LDX>
{
    std::string opcodeToString() const override { return "LDX dp,Y"; }
    int calculateCycles(const State& state) const override;
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr,Y
// Absolute Indexed, Y
class LDX_BE : public AddressMode::AbsoluteIndexedY<Operator::LDX>
{
    std::string opcodeToString() const override { return "LDX addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class LDY_A0 : public AddressMode::ImmediateFlagSize<Operator::LDY, State::x>
{
    std::string opcodeToString() const override { return "LDY #const"; }
    int calculateCycles(const State& state) const override;
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp
// Direct Page
class LDY_A4 : public AddressMode::DirectPage<Operator::LDY>
{
    std::string opcodeToString() const override { return "LDY dp"; }
    int calculateCycles(const State& state) const override;
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr
// Absolute
class LDY_AC : public AddressMode::Absolute<Operator::LDY>
{
    std::string opcodeToString() const override { return "LDY addr"; }
    int calculateCycles(const State& state) const override;
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp,X
// Direct Page Indexed, X
class LDY_B4 : public AddressMode::DirectPageIndexedX<Operator::LDY>
{
    std::string opcodeToString() const override { return "LDY dp,X"; }
    int calculateCycles(const State& state) const override;
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr,X
// Absolute Indexed, X
class LDY_BC : public AddressMode::AbsoluteIndexedX<Operator::LDY>
{
    std::string opcodeToString() const override { return "LDY addr,X"; }
    int calculateCycles(const State& state) const override;
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp
// Direct Page
class LSR_46 : public AddressMode::DirectPage<Operator::LSR>
{
    std::string opcodeToString() const override { return "LSR dp"; }
    int calculateCycles(const State& state) const override;
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR A
// Accumulator
class LSR_4A : public AddressMode::Accumulator<Operator::LSR>
{
    std::string opcodeToString() const override { return "LSR A"; }
    int calculateCycles(const State& state) const override;
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr
// Absolute
class LSR_4E : public AddressMode::Absolute<Operator::LSR>
{
    std::string opcodeToString() const override { return "LSR addr"; }
    int calculateCycles(const State& state) const override;
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp,X
// Direct Page Indexed, X
class LSR_56 : public AddressMode::DirectPageIndexedX<Operator::LSR>
{
    std::string opcodeToString() const override { return "LSR dp,X"; }
    int calculateCycles(const State& state) const override;
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr,X
// Absolute Indexed, X
class LSR_5E : public AddressMode::AbsoluteIndexedX<Operator::LSR>
{
    std::string opcodeToString() const override { return "LSR addr,X"; }
    int calculateCycles(const State& state) const override;
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
// MVN srcbk,destbk
// Block Move
class MVN_54 : public AddressMode::BlockMove<Operator::MVN>
{
    std::string opcodeToString() const override { return "MVN srcbk,destbk"; }
    int calculateCycles(const State& state) const override;
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
// MVN srcbk,destbk
// Block Move
class MVN_44 : public AddressMode::BlockMove<Operator::MVN>
{
    std::string opcodeToString() const override { return "MVN srcbk,destbk"; }
    int calculateCycles(const State& state) const override;
};

// NOP No Operation [Flags affected: none]
// NOP
// Implied
class NOP_EA : public AddressMode::Implied<Operator::NOP>
{
    std::string opcodeToString() const override { return "NOP"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp,X)
// Direct Page Indexed Indirect, X
class ORA_01 : public AddressMode::DirectPageIndexedIndirectX<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA sr,S
// Stack Relative
class ORA_03 : public AddressMode::StackRelative<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA sr,S"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp
// Direct Page
class ORA_05 : public AddressMode::DirectPage<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA dp"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp]
// Direct Page Indirect Long
class ORA_07 : public AddressMode::DirectPageIndirectLong<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA [dp]"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class ORA_09 : public AddressMode::ImmediateFlagSize<Operator::ORA, State::m>
{
    std::string opcodeToString() const override { return "ORA #const"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr
// Absolute
class ORA_0D : public AddressMode::Absolute<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA addr"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long
// Absolute Long
class ORA_0F : public AddressMode::AbsoluteLong<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA long"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp),Y
// Direct Page Indirect Indexed, Y
class ORA_11 : public AddressMode::DirectPageIndirectIndexedY<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp)
// Direct Page Indirect
class ORA_12 : public AddressMode::DirectPageIndirect<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA (dp)"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (sr,S),Y
// Stack Relative Indirect Indexed, Y
class ORA_13 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp,X
// Direct Page Indexed, X
class ORA_15 : public AddressMode::DirectPageIndexedX<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA dp,X"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp],Y
// Direct Page Indirect Long Indexed, Y
class ORA_17 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,Y
// Absolute Indexed, Y
class ORA_19 : public AddressMode::AbsoluteIndexedY<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,X
// Absolute Indexed, X
class ORA_1D : public AddressMode::AbsoluteIndexedX<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA addr,X"; }
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long,X
// Absolute Long Indexed, X
class ORA_1F : public AddressMode::AbsoluteLongIndexedX<Operator::ORA>
{
    std::string opcodeToString() const override { return "ORA long,X"; }
    int calculateCycles(const State& state) const override;
};

// PEA Push Effective Absolute Address [Flags affected: none]
// PEA addr
// Stack (Absolute)
class PEA_F4 : public AddressMode::StackAbsolute<Operator::PEA>
{
    std::string opcodeToString() const override { return "PEA addr"; }
    int calculateCycles(const State& state) const override;
};

// PEI Push Effective Indirect Address [Flags affected: none]
// PEI (dp)
// Stack (Direct Page Indirect)
class PEI_D4 : public AddressMode::StackDirectPageIndirect<Operator::PEI>
{
    std::string opcodeToString() const override { return "PEI (dp)"; }
    int calculateCycles(const State& state) const override;
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
// PER label
// Stack (Program Counter Relative Long)
class PER_62 : public AddressMode::StackProgramCounterRelativeLong<Operator::PER>
{
    std::string opcodeToString() const override { return "PER label"; }
    int calculateCycles(const State& state) const override;
};

// PHA Push Accumulator [Flags affected: none]
// PHA
// Stack (Push)
class PHA_48 : public AddressMode::StackPush<Operator::PHA>
{
    std::string opcodeToString() const override { return "PHA"; }
    int calculateCycles(const State& state) const override;
};

// PHB Push Data Bank Register [Flags affected: none]
// PHB
// Stack (Push)
class PHB_8B : public AddressMode::StackPush<Operator::PHB>
{
    std::string opcodeToString() const override { return "PHB"; }
    int calculateCycles(const State& state) const override;
};

// PHD Push Direct Page Register [Flags affected: none]
// PHD
// Stack (Push)
class PHD_0B : public AddressMode::StackPush<Operator::PHD>
{
    std::string opcodeToString() const override { return "PHD"; }
    int calculateCycles(const State& state) const override;
};

// PHK Push Program Bank Register [Flags affected: none]
// PHK
// Stack (Push)
class PHK_4B : public AddressMode::StackPush<Operator::PHK>
{
    std::string opcodeToString() const override { return "PHK"; }
    int calculateCycles(const State& state) const override;
};

// PHP Push Processor Status Register [Flags affected: none]
// PHP
// Stack (Push)
class PHP_08 : public AddressMode::StackPush<Operator::PHP>
{
    std::string opcodeToString() const override { return "PHP"; }
    int calculateCycles(const State& state) const override;
};

// PHX Push Index Register X [Flags affected: none]
// PHX
// Stack (Push)
class PHX_DA : public AddressMode::StackPush<Operator::PHX>
{
    std::string opcodeToString() const override { return "PHX"; }
    int calculateCycles(const State& state) const override;
};

// PHY Push Index Register Y [Flags affected: none]
// PHY
// Stack (Push)
class PHY_5A : public AddressMode::StackPush<Operator::PHY>
{
    std::string opcodeToString() const override { return "PHY"; }
    int calculateCycles(const State& state) const override;
};

// PLA Pull Accumulator [Flags affected: n,z]
// PLA
// Stack (Pull)
class PLA_68 : public AddressMode::StackPull<Operator::PLA>
{
    std::string opcodeToString() const override { return "PLA"; }
    int calculateCycles(const State& state) const override;
};

// PLB Pull Data Bank Register [Flags affected: n,z]
// PLB
// Stack (Pull)
class PLB_AB : public AddressMode::StackPull<Operator::PLB>
{
    std::string opcodeToString() const override { return "PLB"; }
    int calculateCycles(const State& state) const override;
};

// PLD Pull Direct Page Register [Flags affected: n,z]
// PLD
// Stack (Pull)
class PLD_2B : public AddressMode::StackPull<Operator::PLD>
{
    std::string opcodeToString() const override { return "PLD"; }
    int calculateCycles(const State& state) const override;
};

// PLP Pull Processor Status Register [Flags affected: n,z]
// PLP
// Stack (Pull)
class PLP_28 : public AddressMode::StackPull<Operator::PLP>
{
    std::string opcodeToString() const override { return "PLP"; }
    int calculateCycles(const State& state) const override;
};

// PLX Pull Index Register X [Flags affected: n,z]
// PLX
// Stack (Pull)
class PLX_FA : public AddressMode::StackPull<Operator::PLX>
{
    std::string opcodeToString() const override { return "PLX"; }
    int calculateCycles(const State& state) const override;
};

// PLY Pull Index Register Y [Flags affected: n,z]
// PLY
// Stack (Pull)
class PLY_7A : public AddressMode::StackPull<Operator::PLY>
{
    std::string opcodeToString() const override { return "PLY"; }
    int calculateCycles(const State& state) const override;
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
// REP #const
// Immediate
class REP_C2 : public AddressMode::Immediate<Operator::REP>
{
    std::string opcodeToString() const override { return "REP #const"; }
    int calculateCycles(const State& state) const override;
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp
// Direct Page
class ROL_26 : public AddressMode::DirectPage<Operator::ROL>
{
    std::string opcodeToString() const override { return "ROL dp"; }
    int calculateCycles(const State& state) const override;
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL A
// Accumulator
class ROL_2A : public AddressMode::Accumulator<Operator::ROL>
{
    std::string opcodeToString() const override { return "ROL A"; }
    int calculateCycles(const State& state) const override;
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr
// Absolute
class ROL_2E : public AddressMode::Absolute<Operator::ROL>
{
    std::string opcodeToString() const override { return "ROL addr"; }
    int calculateCycles(const State& state) const override;
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp,X
// Direct Page Indexed, X
class ROL_36 : public AddressMode::DirectPageIndexedX<Operator::ROL>
{
    std::string opcodeToString() const override { return "ROL dp,X"; }
    int calculateCycles(const State& state) const override;
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr,X
// Absolute Indexed, X
class ROL_3E : public AddressMode::AbsoluteIndexedX<Operator::ROL>
{
    std::string opcodeToString() const override { return "ROL addr,X"; }
    int calculateCycles(const State& state) const override;
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp
// Direct Page
class ROR_66 : public AddressMode::DirectPage<Operator::ROR>
{
    std::string opcodeToString() const override { return "ROR dp"; }
    int calculateCycles(const State& state) const override;
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR A
// Accumulator
class ROR_6A : public AddressMode::Accumulator<Operator::ROR>
{
    std::string opcodeToString() const override { return "ROR A"; }
    int calculateCycles(const State& state) const override;
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr
// Absolute
class ROR_6E : public AddressMode::Absolute<Operator::ROR>
{
    std::string opcodeToString() const override { return "ROR addr"; }
    int calculateCycles(const State& state) const override;
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp,X
// Direct Page Indexed, X
class ROR_76 : public AddressMode::DirectPageIndexedX<Operator::ROR>
{
    std::string opcodeToString() const override { return "ROR dp,X"; }
    int calculateCycles(const State& state) const override;
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr,X
// Absolute Indexed, X
class ROR_7E : public AddressMode::AbsoluteIndexedX<Operator::ROR>
{
    std::string opcodeToString() const override { return "ROR addr,X"; }
    int calculateCycles(const State& state) const override;
};

// RTI Return from Interrupt [Flags affected: all except b]
// RTI
// Stack (RTI)
class RTI_40 : public AddressMode::StackRTI<Operator::RTI>
{
    std::string opcodeToString() const override { return "RTI"; }
    int calculateCycles(const State& state) const override;
};

// RTL Return from Subroutine Long [Flags affected: none]
// RTL
// Stack (RTL)
class RTL_6B : public AddressMode::StackRTL<Operator::RTL>
{
    std::string opcodeToString() const override { return "RTL"; }
    int calculateCycles(const State& state) const override;
};

// RTS Return from Subroutine [Flags affected: none]
// RTS
// Stack (RTS)
class RTS_60 : public AddressMode::StackRTS<Operator::RTS>
{
    std::string opcodeToString() const override { return "RTS"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp,X)
// Direct Page Indexed Indirect, X
class SBC_E1 : public AddressMode::DirectPageIndexedIndirectX<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC sr,S
// Stack Relative
class SBC_E3 : public AddressMode::StackRelative<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC sr,S"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp
// Direct Page
class SBC_E5 : public AddressMode::DirectPage<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC dp"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp]
// Direct Page Indirect Long
class SBC_E7 : public AddressMode::DirectPageIndirectLong<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC [dp]"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class SBC_E9 : public AddressMode::ImmediateFlagSize<Operator::SBC, State::m>
{
    std::string opcodeToString() const override { return "SBC #const"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr
// Absolute
class SBC_ED : public AddressMode::Absolute<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC addr"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long
// Absolute Long
class SBC_EF : public AddressMode::AbsoluteLong<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC long"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp),Y
// Direct Page Indirect Indexed, Y
class SBC_F1 : public AddressMode::DirectPageIndirectIndexedY<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp)
// Direct Page Indirect
class SBC_F2 : public AddressMode::DirectPageIndirect<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC (dp)"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (sr,S),Y
// Stack Relative Indirect Indexed, Y
class SBC_F3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp,X
// Direct Page Indexed, X
class SBC_F5 : public AddressMode::DirectPageIndexedX<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC dp,X"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp],Y
// Direct Page Indirect Long Indexed, Y
class SBC_F7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,Y
// Absolute Indexed, Y
class SBC_F9 : public AddressMode::AbsoluteIndexedY<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,X
// Absolute Indexed, X
class SBC_FD : public AddressMode::AbsoluteIndexedX<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC addr,X"; }
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long,X
// Absolute Long Indexed, X
class SBC_FF : public AddressMode::AbsoluteLongIndexedX<Operator::SBC>
{
    std::string opcodeToString() const override { return "SBC long,X"; }
    int calculateCycles(const State& state) const override;
};

// SEC Set Carry Flag [Flags affected: c]
// SEC
// Implied
class SEC_38 : public AddressMode::Implied<Operator::SEC>
{
    std::string opcodeToString() const override { return "SEC"; }
    int calculateCycles(const State& state) const override;
};

// SED Set Decimal Flag [Flags affected: d]
// SED
// Implied
class SED_F8 : public AddressMode::Implied<Operator::SED>
{
    std::string opcodeToString() const override { return "SED"; }
    int calculateCycles(const State& state) const override;
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
// SEI
// Implied
class SEI_78 : public AddressMode::Implied<Operator::SEI>
{
    std::string opcodeToString() const override { return "SEI"; }
    int calculateCycles(const State& state) const override;
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
// SEP #const
// Immediate
class SEP_E2 : public AddressMode::Immediate<Operator::SEP>
{
    std::string opcodeToString() const override { return "SEP #const"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp,X)
// Direct Page Indexed Indirect, X
class STA_81 : public AddressMode::DirectPageIndexedIndirectX<Operator::STA>
{
    std::string opcodeToString() const override { return "STA (dp,X)"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA sr,S
// Stack Relative
class STA_83 : public AddressMode::StackRelative<Operator::STA>
{
    std::string opcodeToString() const override { return "STA sr,S"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp
// Direct Page
class STA_85 : public AddressMode::DirectPage<Operator::STA>
{
    std::string opcodeToString() const override { return "STA dp"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp]
// Direct Page Indirect Long
class STA_87 : public AddressMode::DirectPageIndirectLong<Operator::STA>
{
    std::string opcodeToString() const override { return "STA [dp]"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr
// Absolute
class STA_8D : public AddressMode::Absolute<Operator::STA>
{
    std::string opcodeToString() const override { return "STA addr"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long
// Absolute Long
class STA_8F : public AddressMode::AbsoluteLong<Operator::STA>
{
    std::string opcodeToString() const override { return "STA long"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp),Y
// Direct Page Indirect Indexed, Y
class STA_91 : public AddressMode::DirectPageIndirectIndexedY<Operator::STA>
{
    std::string opcodeToString() const override { return "STA (dp),Y"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp)
// Direct Page Indirect
class STA_92 : public AddressMode::DirectPageIndirect<Operator::STA>
{
    std::string opcodeToString() const override { return "STA (dp)"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (sr,S),Y
// Stack Relative Indirect Indexed, Y
class STA_93 : public AddressMode::StackRelativeIndirectIndexedY<Operator::STA>
{
    std::string opcodeToString() const override { return "STA (sr,S),Y"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp,X
// Direct Page Indexed, X
class STA_95 : public AddressMode::DirectPageIndexedX<Operator::STA>
{
    std::string opcodeToString() const override { return "STA dp,X"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp],Y
// Direct Page Indirect Long Indexed, Y
class STA_97 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::STA>
{
    std::string opcodeToString() const override { return "STA [dp],Y"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,Y
// Absolute Indexed, Y
class STA_99 : public AddressMode::AbsoluteIndexedY<Operator::STA>
{
    std::string opcodeToString() const override { return "STA addr,Y"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,X
// Absolute Indexed, X
class STA_9D : public AddressMode::AbsoluteIndexedX<Operator::STA>
{
    std::string opcodeToString() const override { return "STA addr,X"; }
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long,X
// Absolute Long Indexed, X
class STA_9F : public AddressMode::AbsoluteLongIndexedX<Operator::STA>
{
    std::string opcodeToString() const override { return "STA long,X"; }
    int calculateCycles(const State& state) const override;
};

// STP Stop Processor [Flags affected: none]
// STP
// Implied
class STP_DB : public AddressMode::Implied<Operator::STP>
{
    std::string opcodeToString() const override { return "STP"; }
    int calculateCycles(const State& state) const override;
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp
// Direct Page
class STX_86 : public AddressMode::DirectPage<Operator::STX>
{
    std::string opcodeToString() const override { return "STX dp"; }
    int calculateCycles(const State& state) const override;
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX addr
// Absolute
class STX_8E : public AddressMode::Absolute<Operator::STX>
{
    std::string opcodeToString() const override { return "STX addr"; }
    int calculateCycles(const State& state) const override;
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp,Y
// Direct Page Indexed, Y
class STX_96 : public AddressMode::DirectPageIndexedY<Operator::STX>
{
    std::string opcodeToString() const override { return "STX dp,Y"; }
    int calculateCycles(const State& state) const override;
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp
// Direct Page
class STY_84 : public AddressMode::DirectPage<Operator::STY>
{
    std::string opcodeToString() const override { return "STY dp"; }
    int calculateCycles(const State& state) const override;
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY addr
// Absolute
class STY_8C : public AddressMode::Absolute<Operator::STY>
{
    std::string opcodeToString() const override { return "STY addr"; }
    int calculateCycles(const State& state) const override;
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp,X
// Direct Page Indexed, X
class STY_94 : public AddressMode::DirectPageIndexedX<Operator::STY>
{
    std::string opcodeToString() const override { return "STY dp,X"; }
    int calculateCycles(const State& state) const override;
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp
// Direct Page
class STZ_64 : public AddressMode::DirectPage<Operator::STZ>
{
    std::string opcodeToString() const override { return "STZ dp"; }
    int calculateCycles(const State& state) const override;
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp,X
// Direct Page Indexed, X
class STZ_74 : public AddressMode::DirectPageIndexedX<Operator::STZ>
{
    std::string opcodeToString() const override { return "STZ dp,X"; }
    int calculateCycles(const State& state) const override;
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr
// Absolute
class STZ_9C : public AddressMode::Absolute<Operator::STZ>
{
    std::string opcodeToString() const override { return "STZ addr"; }
    int calculateCycles(const State& state) const override;
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr,X
// Absolute Indexed, X
class STZ_9E : public AddressMode::AbsoluteIndexedX<Operator::STZ>
{
    std::string opcodeToString() const override { return "STZ addr,X"; }
    int calculateCycles(const State& state) const override;
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
// TAX
// Implied
class TAX_AA : public AddressMode::Implied<Operator::TAX>
{
    std::string opcodeToString() const override { return "TAX"; }
    int calculateCycles(const State& state) const override;
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
// TAY
// Implied
class TAY_A8 : public AddressMode::Implied<Operator::TAY>
{
    std::string opcodeToString() const override { return "TAY"; }
    int calculateCycles(const State& state) const override;
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
// TCD
// Implied
class TCD_5B : public AddressMode::Implied<Operator::TCD>
{
    std::string opcodeToString() const override { return "TCD"; }
    int calculateCycles(const State& state) const override;
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
// TCS
// Implied
class TCS_1B : public AddressMode::Implied<Operator::TCS>
{
    std::string opcodeToString() const override { return "TCS"; }
    int calculateCycles(const State& state) const override;
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
// TDC
// Implied
class TDC_7B : public AddressMode::Implied<Operator::TDC>
{
    std::string opcodeToString() const override { return "TDC"; }
    int calculateCycles(const State& state) const override;
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB dp
// Direct Page
class TRB_14 : public AddressMode::DirectPage<Operator::TRB>
{
    std::string opcodeToString() const override { return "TRB dp"; }
    int calculateCycles(const State& state) const override;
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB addr
// Absolute
class TRB_1C : public AddressMode::Absolute<Operator::TRB>
{
    std::string opcodeToString() const override { return "TRB addr"; }
    int calculateCycles(const State& state) const override;
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB dp
// Direct Page
class TSB_04 : public AddressMode::DirectPage<Operator::TSB>
{
    std::string opcodeToString() const override { return "TSB dp"; }
    int calculateCycles(const State& state) const override;
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB addr
// Absolute
class TSB_0C : public AddressMode::Absolute<Operator::TSB>
{
    std::string opcodeToString() const override { return "TSB addr"; }
    int calculateCycles(const State& state) const override;
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
// TSC
// Implied
class TSC_3B : public AddressMode::Implied<Operator::TSC>
{
    std::string opcodeToString() const override { return "TSC"; }
    int calculateCycles(const State& state) const override;
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
// TSX
// Implied
class TSX_BA : public AddressMode::Implied<Operator::TSX>
{
    std::string opcodeToString() const override { return "TSX"; }
    int calculateCycles(const State& state) const override;
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
// TXA
// Implied
class TXA_8A : public AddressMode::Implied<Operator::TXA>
{
    std::string opcodeToString() const override { return "TXA"; }
    int calculateCycles(const State& state) const override;
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
// TXS
// Implied
class TXS_9A : public AddressMode::Implied<Operator::TXS>
{
    std::string opcodeToString() const override { return "TXS"; }
    int calculateCycles(const State& state) const override;
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
// TXY
// Implied
class TXY_9B : public AddressMode::Implied<Operator::TXY>
{
    std::string opcodeToString() const override { return "TXY"; }
    int calculateCycles(const State& state) const override;
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
// TYA
// Implied
class TYA_98 : public AddressMode::Implied<Operator::TYA>
{
    std::string opcodeToString() const override { return "TYA"; }
    int calculateCycles(const State& state) const override;
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
// TYX
// Implied
class TYX_BB : public AddressMode::Implied<Operator::TYX>
{
    std::string opcodeToString() const override { return "TYX"; }
    int calculateCycles(const State& state) const override;
};

// WAI Wait for Interrupt [Flags affected: none]
// WAI
// Implied
class WAI_CB : public AddressMode::Implied<Operator::WAI>
{
    std::string opcodeToString() const override { return "WAI"; }
    int calculateCycles(const State& state) const override;
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
// WDM
// n/a
// 16: Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths
class WDM_42 : public AddressMode::na<Operator::WDM>
{
    std::string opcodeToString() const override { return "WDM"; }
    int calculateCycles(const State& state) const override;
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
// XBA
// Implied
class XBA_EB : public AddressMode::Implied<Operator::XBA>
{
    std::string opcodeToString() const override { return "XBA"; }
    int calculateCycles(const State& state) const override;
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
// XCE
// Implied
class XCE_FB : public AddressMode::Implied<Operator::XCE>
{
    std::string opcodeToString() const override { return "XCE"; }
    int calculateCycles(const State& state) const override;
};

}
