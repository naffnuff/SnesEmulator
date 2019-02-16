#pragma once

#include <stdint.h>

#include "State.h"
#include "Instruction.h"
#include "AddressMode.h"
#include "Operator.h"

// ADC Add With Carry [Flags affected: n,v,z,c]

// ADC (dp,X)
// Direct Page Indexed Indirect,X
class ADC_61 : public AddressMode::DirectPageIndexedIndirectX<Operator::ADC>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// ADC sr,S
// Stack Relative
class ADC_63 : public AddressMode::StackRelative<Operator::ADC>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// ADC dp
// Direct Page
class ADC_65 : public AddressMode::DirectPage<Operator::ADC>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// ADC [dp]
// Direct Page Indirect Long
class ADC_67 : public AddressMode::DirectPageIndirectLong<Operator::ADC>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// ADC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class ADC_69 : public AddressMode::ImmediateFlagSize<Operator::ADC, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// ADC addr
// Absolute
class ADC_6D : public AddressMode::Absolute<Operator::ADC>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// ADC long
// Absolute Long
class ADC_6F : public AddressMode::AbsoluteLong<Operator::ADC>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// ADC (dp),Y
// Direct Page Indirect Indexed, Y
class ADC_71 : public AddressMode::DirectPageIndirectIndexedY<Operator::ADC>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// ADC (dp)
// Direct Page Indirect
class ADC_72 : public AddressMode::DirectPageIndirect<Operator::ADC>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// ADC (sr,S),Y
// Stack Relative Indirect Indexed,Y
class ADC_73 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ADC>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// ADC dp,X
// Direct Page Indexed,X
class ADC_75 : public AddressMode::DirectPageIndexedX<Operator::ADC>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// ADC [dp],Y
// Direct Page Indirect Long Indexed, Y
class ADC_77 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ADC>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// ADC addr,Y
// Absolute Indexed,Y
class ADC_79 : public AddressMode::AbsoluteIndexedY<Operator::ADC>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// ADC addr,X
// Absolute Indexed,X
class ADC_7D : public AddressMode::AbsoluteIndexedX<Operator::ADC>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// ADC long,X
// Absolute Long Indexed,X
class ADC_7F : public AddressMode::AbsoluteLongIndexedX<Operator::ADC>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]

// AND (dp,X)
// Direct Page Indexed Indirect,X
class AND_21 : public AddressMode::DirectPageIndexedIndirectX<Operator::AND>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// AND sr,S
// Stack Relative
class AND_23 : public AddressMode::StackRelative<Operator::AND>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// AND dp
// Direct Page
class AND_25 : public AddressMode::DirectPage<Operator::AND>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// AND [dp]
// Direct Page Indirect Long
class AND_27 : public AddressMode::DirectPageIndirectLong<Operator::AND>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// AND #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class AND_29 : public AddressMode::ImmediateFlagSize<Operator::AND, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// AND addr
// Absolute
class AND_2D : public AddressMode::Absolute<Operator::AND>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// AND long
// Absolute Long
class AND_2F : public AddressMode::AbsoluteLong<Operator::AND>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// AND (dp),Y
// Direct Page Indirect Indexed, Y
class AND_31 : public AddressMode::DirectPageIndirectIndexedY<Operator::AND>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// AND (dp)
// Direct Page Indirect
class AND_32 : public AddressMode::DirectPageIndirect<Operator::AND>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// AND (sr,S),Y
// Stack Relative Indirect Indexed,Y
class AND_33 : public AddressMode::StackRelativeIndirectIndexedY<Operator::AND>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// AND dp,X
// Direct Page Indexed,X
class AND_35 : public AddressMode::DirectPageIndexedX<Operator::AND>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// AND [dp],Y
// Direct Page Indirect Long Indexed, Y
class AND_37 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::AND>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// AND addr,Y
// Absolute Indexed,Y
class AND_39 : public AddressMode::AbsoluteIndexedY<Operator::AND>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// AND addr,X
// Absolute Indexed,X
class AND_3D : public AddressMode::AbsoluteIndexedX<Operator::AND>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// AND long,X
// Absolute Long Indexed,X
class AND_3F : public AddressMode::AbsoluteLongIndexedX<Operator::AND>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]

// ASL dp
// Direct Page
class ASL_06 : public AddressMode::DirectPage<Operator::ASL>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// ASL A
// Accumulator
class ASL_0A : public AddressMode::Accumulator<Operator::ASL>
{
    using Accumulator::Accumulator;
    int calculateCycles(const State& state) const override;
};

// ASL addr
// Absolute
class ASL_0E : public AddressMode::Absolute<Operator::ASL>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// ASL dp,X
// Direct Page Indexed,X
class ASL_16 : public AddressMode::DirectPageIndexedX<Operator::ASL>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// ASL addr,X
// Absolute Indexed,X
class ASL_1E : public AddressMode::AbsoluteIndexedX<Operator::ASL>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]

// BCC nearlabel
// Program Counter Relative
class BCC_90 : public AddressMode::ProgramCounterRelative<Operator::BCC>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]

// BCS nearlabel
// Program Counter Relative
class BCS_B0 : public AddressMode::ProgramCounterRelative<Operator::BCS>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BEQ Branch if Equal [Flags affected: none]

// BEQ nearlabel
// Program Counter Relative
class BEQ_F0 : public AddressMode::ProgramCounterRelative<Operator::BEQ>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]

// BIT dp
// Direct Page
class BIT_24 : public AddressMode::DirectPage<Operator::BIT>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// BIT addr
// Absolute
class BIT_2C : public AddressMode::Absolute<Operator::BIT>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// BIT dp,X
// Direct Page Indexed,X
class BIT_34 : public AddressMode::DirectPageIndexedX<Operator::BIT>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// BIT addr,X
// Absolute Indexed,X
class BIT_3C : public AddressMode::AbsoluteIndexedX<Operator::BIT>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// BIT #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class BIT_89 : public AddressMode::ImmediateFlagSize<Operator::BIT, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// BMI Branch if Minus [Flags affected: none]

// BMI nearlabel
// Program Counter Relative
class BMI_30 : public AddressMode::ProgramCounterRelative<Operator::BMI>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BNE Branch if Not Equal [Flags affected: none]

// BNE nearlabel
// Program Counter Relative
class BNE_D0 : public AddressMode::ProgramCounterRelative<Operator::BNE>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BPL Branch if Plus [Flags affected: none]

// BPL nearlabel
// Program Counter Relative
class BPL_10 : public AddressMode::ProgramCounterRelative<Operator::BPL>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BRA Branch Always [Flags affected: none]

// BRA nearlabel
// Program Counter Relative
class BRA_80 : public AddressMode::ProgramCounterRelative<Operator::BRA>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]

// BRK
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class BRK_00 : public AddressMode::StackInterrupt<Operator::BRK>
{
    using StackInterrupt::StackInterrupt;
    int calculateCycles(const State& state) const override;
};

// BRL Branch Long Always [Flags affected: none]

// BRL label
// Program Counter Relative Long
class BRL_82 : public AddressMode::ProgramCounterRelativeLong<Operator::BRL>
{
    using ProgramCounterRelativeLong::ProgramCounterRelativeLong;
    int calculateCycles(const State& state) const override;
};

// BVC Branch if Overflow Clear [Flags affected: none]

// BVC nearlabel
// Program Counter Relative
class BVC_50 : public AddressMode::ProgramCounterRelative<Operator::BVC>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// BVS Branch if Overflow Set [Flags affected: none]

// BVS nearlabel
// Program Counter Relative
class BVS_70 : public AddressMode::ProgramCounterRelative<Operator::BVS>
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int calculateCycles(const State& state) const override;
};

// CLC Clear Carry [Flags affected: c]

// CLC
// Implied
class CLC_18 : public AddressMode::Implied<Operator::CLC>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// CLD Clear Decimal Mode Flag [Flags affected: d]

// CLD
// Implied
class CLD_D8 : public AddressMode::Implied<Operator::CLD>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]

// CLI
// Implied
class CLI_58 : public AddressMode::Implied<Operator::CLI>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// CLV Clear Overflow Flag [Flags affected: v]

// CLV
// Implied
class CLV_B8 : public AddressMode::Implied<Operator::CLV>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]

// CMP (dp,X)
// Direct Page Indexed Indirect,X
class CMP_C1 : public AddressMode::DirectPageIndexedIndirectX<Operator::CMP>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// CMP sr,S
// Stack Relative
class CMP_C3 : public AddressMode::StackRelative<Operator::CMP>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// CMP dp
// Direct Page
class CMP_C5 : public AddressMode::DirectPage<Operator::CMP>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// CMP [dp]
// Direct Page Indirect Long
class CMP_C7 : public AddressMode::DirectPageIndirectLong<Operator::CMP>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// CMP #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class CMP_C9 : public AddressMode::ImmediateFlagSize<Operator::CMP, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// CMP addr
// Absolute
class CMP_CD : public AddressMode::Absolute<Operator::CMP>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// CMP long
// Absolute Long
class CMP_CF : public AddressMode::AbsoluteLong<Operator::CMP>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// CMP (dp),Y
// Direct Page Indirect Indexed, Y
class CMP_D1 : public AddressMode::DirectPageIndirectIndexedY<Operator::CMP>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// CMP (dp)
// Direct Page Indirect
class CMP_D2 : public AddressMode::DirectPageIndirect<Operator::CMP>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// CMP (sr,S),Y
// Stack Relative Indirect Indexed,Y
class CMP_D3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::CMP>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// CMP dp,X
// Direct Page Indexed,X
class CMP_D5 : public AddressMode::DirectPageIndexedX<Operator::CMP>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// CMP [dp],Y
// Direct Page Indirect Long Indexed, Y
class CMP_D7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::CMP>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// CMP addr,Y
// Absolute Indexed,Y
class CMP_D9 : public AddressMode::AbsoluteIndexedY<Operator::CMP>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// CMP addr,X
// Absolute Indexed,X
class CMP_DD : public AddressMode::AbsoluteIndexedX<Operator::CMP>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// CMP long,X
// Absolute Long Indexed,X
class CMP_DF : public AddressMode::AbsoluteLongIndexedX<Operator::CMP>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// COP Co-Processor Enable [Flags affected: d,i]

// COP const
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class COP_02 : public AddressMode::StackInterrupt<Operator::COP>
{
    using StackInterrupt::StackInterrupt;
    int calculateCycles(const State& state) const override;
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]

// CPX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class CPX_E0 : public AddressMode::ImmediateFlagSize<Operator::CPX, State::x>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// CPX dp
// Direct Page
class CPX_E4 : public AddressMode::DirectPage<Operator::CPX>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// CPX addr
// Absolute
class CPX_EC : public AddressMode::Absolute<Operator::CPX>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]

// CPY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class CPY_C0 : public AddressMode::ImmediateFlagSize<Operator::CPY, State::x>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// CPY dp
// Direct Page
class CPY_C4 : public AddressMode::DirectPage<Operator::CPY>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// CPY addr
// Absolute
class CPY_CC : public AddressMode::Absolute<Operator::CPY>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// DEC Decrement [Flags affected: n,z]

// DEC A
// Accumulator
class DEC_3A : public AddressMode::Accumulator<Operator::DEC>
{
    using Accumulator::Accumulator;
    int calculateCycles(const State& state) const override;
};

// DEC dp
// Direct Page
class DEC_C6 : public AddressMode::DirectPage<Operator::DEC>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// DEC addr
// Absolute
class DEC_CE : public AddressMode::Absolute<Operator::DEC>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// DEC dp,X
// Direct Page Indexed,X
class DEC_D6 : public AddressMode::DirectPageIndexedX<Operator::DEC>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// DEC addr,X
// Absolute Indexed,X
class DEC_DE : public AddressMode::AbsoluteIndexedX<Operator::DEC>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// DEX Decrement Index Register X [Flags affected: n,z]

// DEX
// Implied
class DEX_CA : public AddressMode::Implied<Operator::DEX>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// DEY Decrement Index Register Y [Flags affected: n,z]

// DEY
// Implied
class DEY_88 : public AddressMode::Implied<Operator::DEY>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]

// EOR (dp,X)
// Direct Page Indexed Indirect,X
class EOR_41 : public AddressMode::DirectPageIndexedIndirectX<Operator::EOR>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// EOR sr,S
// Stack Relative
class EOR_43 : public AddressMode::StackRelative<Operator::EOR>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// EOR dp
// Direct Page
class EOR_45 : public AddressMode::DirectPage<Operator::EOR>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// EOR [dp]
// Direct Page Indirect Long
class EOR_47 : public AddressMode::DirectPageIndirectLong<Operator::EOR>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// EOR #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class EOR_49 : public AddressMode::ImmediateFlagSize<Operator::EOR, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// EOR addr
// Absolute
class EOR_4D : public AddressMode::Absolute<Operator::EOR>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// EOR long
// Absolute Long
class EOR_4F : public AddressMode::AbsoluteLong<Operator::EOR>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// EOR (dp),Y
// Direct Page Indirect Indexed, Y
class EOR_51 : public AddressMode::DirectPageIndirectIndexedY<Operator::EOR>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// EOR (dp)
// Direct Page Indirect
class EOR_52 : public AddressMode::DirectPageIndirect<Operator::EOR>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// EOR (sr,S),Y
// Stack Relative Indirect Indexed,Y
class EOR_53 : public AddressMode::StackRelativeIndirectIndexedY<Operator::EOR>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// EOR dp,X
// Direct Page Indexed,X
class EOR_55 : public AddressMode::DirectPageIndexedX<Operator::EOR>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// EOR [dp],Y
// Direct Page Indirect Long Indexed, Y
class EOR_57 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::EOR>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// EOR addr,Y
// Absolute Indexed,Y
class EOR_59 : public AddressMode::AbsoluteIndexedY<Operator::EOR>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// EOR addr,X
// Absolute Indexed,X
class EOR_5D : public AddressMode::AbsoluteIndexedX<Operator::EOR>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// EOR long,X
// Absolute Long Indexed,X
class EOR_5F : public AddressMode::AbsoluteLongIndexedX<Operator::EOR>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// INC Increment [Flags affected: n,z]

// INC A
// Accumulator
class INC_1A : public AddressMode::Accumulator<Operator::INC>
{
    using Accumulator::Accumulator;
    int calculateCycles(const State& state) const override;
};

// INC dp
// Direct Page
class INC_E6 : public AddressMode::DirectPage<Operator::INC>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// INC addr
// Absolute
class INC_EE : public AddressMode::Absolute<Operator::INC>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// INC dp,X
// Direct Page Indexed,X
class INC_F6 : public AddressMode::DirectPageIndexedX<Operator::INC>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// INC addr,X
// Absolute Indexed,X
class INC_FE : public AddressMode::AbsoluteIndexedX<Operator::INC>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// INX Increment Index Register X [Flags affected: n,z]

// INX
// Implied
class INX_E8 : public AddressMode::Implied<Operator::INX>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// INY Increment Index Register Y [Flags affected: n,z]

// INY
// Implied
class INY_C8 : public AddressMode::Implied<Operator::INY>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]

// JMP addr
// Absolute
class JMP_4C : public AddressMode::Absolute<Operator::JMP>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// JMP long
// Absolute Long
class JMP_5C : public AddressMode::AbsoluteLong<Operator::JMP>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// JMP (addr)
// Absolute Indirect
class JMP_6C : public AddressMode::AbsoluteIndirect<Operator::JMP>
{
    using AbsoluteIndirect::AbsoluteIndirect;
    int calculateCycles(const State& state) const override;
};

// JMP (addr,X)
// Absolute Indexed Indirect
class JMP_7C : public AddressMode::AbsoluteIndexedIndirect<Operator::JMP>
{
    using AbsoluteIndexedIndirect::AbsoluteIndexedIndirect;
    int calculateCycles(const State& state) const override;
};

// JMP [addr]
// Absolute Indirect Long
class JMP_DC : public AddressMode::AbsoluteIndirectLong<Operator::JMP>
{
    using AbsoluteIndirectLong::AbsoluteIndirectLong;
    int calculateCycles(const State& state) const override;
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]

// JSR addr
// Absolute
class JSR_20 : public AddressMode::Absolute<Operator::JSR>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// JSR long
// Absolute Long
class JSR_22 : public AddressMode::AbsoluteLong<Operator::JSR>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// JSR (addr,X)
// Absolute Indexed Indirect
class JSR_FC : public AddressMode::AbsoluteIndexedIndirect<Operator::JSR>
{
    using AbsoluteIndexedIndirect::AbsoluteIndexedIndirect;
    int calculateCycles(const State& state) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]

// LDA (dp,X)
// Direct Page Indexed Indirect,X
class LDA_A1 : public AddressMode::DirectPageIndexedIndirectX<Operator::LDA>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// LDA sr,S
// Stack Relative
class LDA_A3 : public AddressMode::StackRelative<Operator::LDA>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// LDA dp
// Direct Page
class LDA_A5 : public AddressMode::DirectPage<Operator::LDA>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// LDA [dp]
// Direct Page Indirect Long
class LDA_A7 : public AddressMode::DirectPageIndirectLong<Operator::LDA>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// LDA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class LDA_A9 : public AddressMode::ImmediateFlagSize<Operator::LDA, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// LDA addr
// Absolute
class LDA_AD : public AddressMode::Absolute<Operator::LDA>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// LDA long
// Absolute Long
class LDA_AF : public AddressMode::AbsoluteLong<Operator::LDA>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// LDA (dp),Y
// Direct Page Indirect Indexed, Y
class LDA_B1 : public AddressMode::DirectPageIndirectIndexedY<Operator::LDA>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// LDA (dp)
// Direct Page Indirect
class LDA_B2 : public AddressMode::DirectPageIndirect<Operator::LDA>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// LDA (sr,S),Y
// Stack Relative Indirect Indexed,Y
class LDA_B3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::LDA>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// LDA dp,X
// Direct Page Indexed,X
class LDA_B5 : public AddressMode::DirectPageIndexedX<Operator::LDA>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// LDA [dp],Y
// Direct Page Indirect Long Indexed, Y
class LDA_B7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::LDA>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// LDA addr,Y
// Absolute Indexed,Y
class LDA_B9 : public AddressMode::AbsoluteIndexedY<Operator::LDA>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// LDA addr,X
// Absolute Indexed,X
class LDA_BD : public AddressMode::AbsoluteIndexedX<Operator::LDA>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// LDA long,X
// Absolute Long Indexed,X
class LDA_BF : public AddressMode::AbsoluteLongIndexedX<Operator::LDA>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// LDX Load Index Register X from Memory [Flags affected: n,z]

// LDX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class LDX_A2 : public AddressMode::ImmediateFlagSize<Operator::LDX, State::x>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// LDX dp
// Direct Page
class LDX_A6 : public AddressMode::DirectPage<Operator::LDX>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// LDX addr
// Absolute
class LDX_AE : public AddressMode::Absolute<Operator::LDX>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// LDX dp,Y
// Direct Page Indexed,Y
class LDX_B6 : public AddressMode::DirectPageIndexedY<Operator::LDX>
{
    using DirectPageIndexedY::DirectPageIndexedY;
    int calculateCycles(const State& state) const override;
};

// LDX addr,Y
// Absolute Indexed,Y
class LDX_BE : public AddressMode::AbsoluteIndexedY<Operator::LDX>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]

// LDY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class LDY_A0 : public AddressMode::ImmediateFlagSize<Operator::LDY, State::x>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// LDY dp
// Direct Page
class LDY_A4 : public AddressMode::DirectPage<Operator::LDY>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// LDY addr
// Absolute
class LDY_AC : public AddressMode::Absolute<Operator::LDY>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// LDY dp,X
// Direct Page Indexed,X
class LDY_B4 : public AddressMode::DirectPageIndexedX<Operator::LDY>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// LDY addr,X
// Absolute Indexed,X
class LDY_BC : public AddressMode::AbsoluteIndexedX<Operator::LDY>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]

// LSR dp
// Direct Page
class LSR_46 : public AddressMode::DirectPage<Operator::LSR>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// LSR A
// Accumulator
class LSR_4A : public AddressMode::Accumulator<Operator::LSR>
{
    using Accumulator::Accumulator;
    int calculateCycles(const State& state) const override;
};

// LSR addr
// Absolute
class LSR_4E : public AddressMode::Absolute<Operator::LSR>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// LSR dp,X
// Direct Page Indexed,X
class LSR_56 : public AddressMode::DirectPageIndexedX<Operator::LSR>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// LSR addr,X
// Absolute Indexed,X
class LSR_5E : public AddressMode::AbsoluteIndexedX<Operator::LSR>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]

// MVN srcbk,destbk
// Block Move
class MVN_54 : public AddressMode::BlockMove<Operator::MVN>
{
    using BlockMove::BlockMove;
    int calculateCycles(const State& state) const override;
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]

// MVN srcbk,destbk
// Block Move
class MVN_44 : public AddressMode::BlockMove<Operator::MVN>
{
    using BlockMove::BlockMove;
    int calculateCycles(const State& state) const override;
};

// NOP No Operation [Flags affected: none]

// NOP
// Implied
class NOP_EA : public AddressMode::Implied<Operator::NOP>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]

// ORA (dp,X)
// Direct Page Indexed Indirect,X
class ORA_01 : public AddressMode::DirectPageIndexedIndirectX<Operator::ORA>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// ORA sr,S
// Stack Relative
class ORA_03 : public AddressMode::StackRelative<Operator::ORA>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// ORA dp
// Direct Page
class ORA_05 : public AddressMode::DirectPage<Operator::ORA>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// ORA [dp]
// Direct Page Indirect Long
class ORA_07 : public AddressMode::DirectPageIndirectLong<Operator::ORA>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// ORA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class ORA_09 : public AddressMode::ImmediateFlagSize<Operator::ORA, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// ORA addr
// Absolute
class ORA_0D : public AddressMode::Absolute<Operator::ORA>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// ORA long
// Absolute Long
class ORA_0F : public AddressMode::AbsoluteLong<Operator::ORA>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// ORA (dp),Y
// Direct Page Indirect Indexed, Y
class ORA_11 : public AddressMode::DirectPageIndirectIndexedY<Operator::ORA>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// ORA (dp)
// Direct Page Indirect
class ORA_12 : public AddressMode::DirectPageIndirect<Operator::ORA>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// ORA (sr,S),Y
// Stack Relative Indirect Indexed,Y
class ORA_13 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ORA>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// ORA dp,X
// Direct Page Indexed,X
class ORA_15 : public AddressMode::DirectPageIndexedX<Operator::ORA>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// ORA [dp],Y
// Direct Page Indirect Long Indexed, Y
class ORA_17 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ORA>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// ORA addr,Y
// Absolute Indexed,Y
class ORA_19 : public AddressMode::AbsoluteIndexedY<Operator::ORA>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// ORA addr,X
// Absolute Indexed,X
class ORA_1D : public AddressMode::AbsoluteIndexedX<Operator::ORA>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// ORA long,X
// Absolute Long Indexed,X
class ORA_1F : public AddressMode::AbsoluteLongIndexedX<Operator::ORA>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// PEA Push Effective Absolute Address [Flags affected: none]

// PEA addr
// Stack (Absolute)
class PEA_F4 : public AddressMode::StackAbsolute<Operator::PEA>
{
    using StackAbsolute::StackAbsolute;
    int calculateCycles(const State& state) const override;
};

// PEI Push Effective Indirect Address [Flags affected: none]

// PEI (dp)
// Stack (Direct Page Indirect)
class PEI_D4 : public AddressMode::StackDirectPageIndirect<Operator::PEI>
{
    using StackDirectPageIndirect::StackDirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]

// PER label
// Stack (Program Counter Relative Long)
class PER_62 : public AddressMode::StackProgramCounterRelativeLong<Operator::PER>
{
    using StackProgramCounterRelativeLong::StackProgramCounterRelativeLong;
    int calculateCycles(const State& state) const override;
};

// PHA Push Accumulator [Flags affected: none]

// PHA
// Stack (Push)
class PHA_48 : public AddressMode::StackPush<Operator::PHA>
{
    using StackPush::StackPush;
    int calculateCycles(const State& state) const override;
};

// PHB Push Data Bank Register [Flags affected: none]

// PHB
// Stack (Push)
class PHB_8B : public AddressMode::StackPush<Operator::PHB>
{
    using StackPush::StackPush;
    int calculateCycles(const State& state) const override;
};

// PHD Push Direct Page Register [Flags affected: none]

// PHD
// Stack (Push)
class PHD_0B : public AddressMode::StackPush<Operator::PHD>
{
    using StackPush::StackPush;
    int calculateCycles(const State& state) const override;
};

// PHK Push Program Bank Register [Flags affected: none]

// PHK
// Stack (Push)
class PHK_4B : public AddressMode::StackPush<Operator::PHK>
{
    using StackPush::StackPush;
    int calculateCycles(const State& state) const override;
};

// PHP Push Processor Status Register [Flags affected: none]

// PHP
// Stack (Push)
class PHP_08 : public AddressMode::StackPush<Operator::PHP>
{
    using StackPush::StackPush;
    int calculateCycles(const State& state) const override;
};

// PHX Push Index Register X [Flags affected: none]

// PHX
// Stack (Push)
class PHX_DA : public AddressMode::StackPush<Operator::PHX>
{
    using StackPush::StackPush;
    int calculateCycles(const State& state) const override;
};

// PHY Push Index Register Y [Flags affected: none]

// PHY
// Stack (Push)
class PHY_5A : public AddressMode::StackPush<Operator::PHY>
{
    using StackPush::StackPush;
    int calculateCycles(const State& state) const override;
};

// PLA Pull Accumulator [Flags affected: n,z]

// PLA
// Stack (Pull)
class PLA_68 : public AddressMode::StackPull<Operator::PLA>
{
    using StackPull::StackPull;
    int calculateCycles(const State& state) const override;
};

// PLB Pull Data Bank Register [Flags affected: n,z]

// PLB
// Stack (Pull)
class PLB_AB : public AddressMode::StackPull<Operator::PLB>
{
    using StackPull::StackPull;
    int calculateCycles(const State& state) const override;
};

// PLD Pull Direct Page Register [Flags affected: n,z]

// PLD
// Stack (Pull)
class PLD_2B : public AddressMode::StackPull<Operator::PLD>
{
    using StackPull::StackPull;
    int calculateCycles(const State& state) const override;
};

// PLP Pull Processor Status Register [Flags affected: n,z]

// PLP
// Stack (Pull)
class PLP_28 : public AddressMode::StackPull<Operator::PLP>
{
    using StackPull::StackPull;
    int calculateCycles(const State& state) const override;
};

// PLX Pull Index Register X [Flags affected: n,z]

// PLX
// Stack (Pull)
class PLX_FA : public AddressMode::StackPull<Operator::PLX>
{
    using StackPull::StackPull;
    int calculateCycles(const State& state) const override;
};

// PLY Pull Index Register Y [Flags affected: n,z]

// PLY
// Stack (Pull)
class PLY_7A : public AddressMode::StackPull<Operator::PLY>
{
    using StackPull::StackPull;
    int calculateCycles(const State& state) const override;
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]

// REP #const
// Immediate
class REP_C2 : public AddressMode::Immediate<Operator::REP>
{
    using Immediate::Immediate;
    int calculateCycles(const State& state) const override;
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]

// ROL dp
// Direct Page
class ROL_26 : public AddressMode::DirectPage<Operator::ROL>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// ROL A
// Accumulator
class ROL_2A : public AddressMode::Accumulator<Operator::ROL>
{
    using Accumulator::Accumulator;
    int calculateCycles(const State& state) const override;
};

// ROL addr
// Absolute
class ROL_2E : public AddressMode::Absolute<Operator::ROL>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// ROL dp,X
// Direct Page Indexed,X
class ROL_36 : public AddressMode::DirectPageIndexedX<Operator::ROL>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// ROL addr,X
// Absolute Indexed,X
class ROL_3E : public AddressMode::AbsoluteIndexedX<Operator::ROL>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]

// ROR dp
// Direct Page
class ROR_66 : public AddressMode::DirectPage<Operator::ROR>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// ROR A
// Accumulator
class ROR_6A : public AddressMode::Accumulator<Operator::ROR>
{
    using Accumulator::Accumulator;
    int calculateCycles(const State& state) const override;
};

// ROR addr
// Absolute
class ROR_6E : public AddressMode::Absolute<Operator::ROR>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// ROR dp,X
// Direct Page Indexed,X
class ROR_76 : public AddressMode::DirectPageIndexedX<Operator::ROR>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// ROR addr,X
// Absolute Indexed,X
class ROR_7E : public AddressMode::AbsoluteIndexedX<Operator::ROR>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// RTI Return from Interrupt [Flags affected: all except b]

// RTI
// Stack (RTI)
class RTI_40 : public AddressMode::StackRTI<Operator::RTI>
{
    using StackRTI::StackRTI;
    int calculateCycles(const State& state) const override;
};

// RTL Return from Subroutine Long [Flags affected: none]

// RTL
// Stack (RTL)
class RTL_6B : public AddressMode::StackRTL<Operator::RTL>
{
    using StackRTL::StackRTL;
    int calculateCycles(const State& state) const override;
};

// RTS Return from Subroutine [Flags affected: none]

// RTS
// Stack (RTS)
class RTS_60 : public AddressMode::StackRTS<Operator::RTS>
{
    using StackRTS::StackRTS;
    int calculateCycles(const State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]

// SBC (dp,X)
// Direct Page Indexed Indirect,X
class SBC_E1 : public AddressMode::DirectPageIndexedIndirectX<Operator::SBC>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// SBC sr,S
// Stack Relative
class SBC_E3 : public AddressMode::StackRelative<Operator::SBC>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// SBC dp
// Direct Page
class SBC_E5 : public AddressMode::DirectPage<Operator::SBC>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// SBC [dp]
// Direct Page Indirect Long
class SBC_E7 : public AddressMode::DirectPageIndirectLong<Operator::SBC>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// SBC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class SBC_E9 : public AddressMode::ImmediateFlagSize<Operator::SBC, State::m>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int calculateCycles(const State& state) const override;
};

// SBC addr
// Absolute
class SBC_ED : public AddressMode::Absolute<Operator::SBC>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// SBC long
// Absolute Long
class SBC_EF : public AddressMode::AbsoluteLong<Operator::SBC>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// SBC (dp),Y
// Direct Page Indirect Indexed, Y
class SBC_F1 : public AddressMode::DirectPageIndirectIndexedY<Operator::SBC>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// SBC (dp)
// Direct Page Indirect
class SBC_F2 : public AddressMode::DirectPageIndirect<Operator::SBC>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// SBC (sr,S),Y
// Stack Relative Indirect Indexed,Y
class SBC_F3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::SBC>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// SBC dp,X
// Direct Page Indexed,X
class SBC_F5 : public AddressMode::DirectPageIndexedX<Operator::SBC>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// SBC [dp],Y
// Direct Page Indirect Long Indexed, Y
class SBC_F7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::SBC>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// SBC addr,Y
// Absolute Indexed,Y
class SBC_F9 : public AddressMode::AbsoluteIndexedY<Operator::SBC>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// SBC addr,X
// Absolute Indexed,X
class SBC_FD : public AddressMode::AbsoluteIndexedX<Operator::SBC>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// SBC long,X
// Absolute Long Indexed,X
class SBC_FF : public AddressMode::AbsoluteLongIndexedX<Operator::SBC>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// SEC Set Carry Flag [Flags affected: c]

// SEC
// Implied
class SEC_38 : public AddressMode::Implied<Operator::SEC>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// SED Set Decimal Flag [Flags affected: d]

// SED
// Implied
class SED_F8 : public AddressMode::Implied<Operator::SED>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// SEI Set Interrupt Disable Flag [Flags affected: i]

// SEI
// Implied
class SEI_78 : public AddressMode::Implied<Operator::SEI>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]

// SEP #const
// Immediate
class SEP_E2 : public AddressMode::Immediate<Operator::SEP>
{
    using Immediate::Immediate;
    int calculateCycles(const State& state) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]

// STA (dp,X)
// Direct Page Indexed Indirect,X
class STA_81 : public AddressMode::DirectPageIndexedIndirectX<Operator::STA>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int calculateCycles(const State& state) const override;
};

// STA sr,S
// Stack Relative
class STA_83 : public AddressMode::StackRelative<Operator::STA>
{
    using StackRelative::StackRelative;
    int calculateCycles(const State& state) const override;
};

// STA dp
// Direct Page
class STA_85 : public AddressMode::DirectPage<Operator::STA>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// STA [dp]
// Direct Page Indirect Long
class STA_87 : public AddressMode::DirectPageIndirectLong<Operator::STA>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int calculateCycles(const State& state) const override;
};

// STA addr
// Absolute
class STA_8D : public AddressMode::Absolute<Operator::STA>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// STA long
// Absolute Long
class STA_8F : public AddressMode::AbsoluteLong<Operator::STA>
{
    using AbsoluteLong::AbsoluteLong;
    int calculateCycles(const State& state) const override;
};

// STA (dp),Y
// Direct Page Indirect Indexed, Y
class STA_91 : public AddressMode::DirectPageIndirectIndexedY<Operator::STA>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// STA (dp)
// Direct Page Indirect
class STA_92 : public AddressMode::DirectPageIndirect<Operator::STA>
{
    using DirectPageIndirect::DirectPageIndirect;
    int calculateCycles(const State& state) const override;
};

// STA (sr,S),Y
// Stack Relative Indirect Indexed,Y
class STA_93 : public AddressMode::StackRelativeIndirectIndexedY<Operator::STA>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int calculateCycles(const State& state) const override;
};

// STA dp,X
// Direct Page Indexed,X
class STA_95 : public AddressMode::DirectPageIndexedX<Operator::STA>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// STA [dp],Y
// Direct Page Indirect Long Indexed, Y
class STA_97 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::STA>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int calculateCycles(const State& state) const override;
};

// STA addr,Y
// Absolute Indexed,Y
class STA_99 : public AddressMode::AbsoluteIndexedY<Operator::STA>
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int calculateCycles(const State& state) const override;
};

// STA addr,X
// Absolute Indexed,X
class STA_9D : public AddressMode::AbsoluteIndexedX<Operator::STA>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// STA long,X
// Absolute Long Indexed,X
class STA_9F : public AddressMode::AbsoluteLongIndexedX<Operator::STA>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int calculateCycles(const State& state) const override;
};

// STP Stop Processor [Flags affected: none]

// STP
// Implied
class STP_DB : public AddressMode::Implied<Operator::STP>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// STX Store Index Register X to Memory [Flags affected: none]

// STX dp
// Direct Page
class STX_86 : public AddressMode::DirectPage<Operator::STX>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// STX addr
// Absolute
class STX_8E : public AddressMode::Absolute<Operator::STX>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// STX dp,Y
// Direct Page Indexed,Y
class STX_96 : public AddressMode::DirectPageIndexedY<Operator::STX>
{
    using DirectPageIndexedY::DirectPageIndexedY;
    int calculateCycles(const State& state) const override;
};

// STY Store Index Register Y to Memory [Flags affected: none]

// STY dp
// Direct Page
class STY_84 : public AddressMode::DirectPage<Operator::STY>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// STY addr
// Absolute
class STY_8C : public AddressMode::Absolute<Operator::STY>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// STY dp,X
// Direct Page Indexed,X
class STY_94 : public AddressMode::DirectPageIndexedX<Operator::STY>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// STZ Store Zero to Memory [Flags affected: none]

// STZ dp
// Direct Page
class STZ_64 : public AddressMode::DirectPage<Operator::STZ>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// STZ dp,X
// Direct Page Indexed,X
class STZ_74 : public AddressMode::DirectPageIndexedX<Operator::STZ>
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int calculateCycles(const State& state) const override;
};

// STZ addr
// Absolute
class STZ_9C : public AddressMode::Absolute<Operator::STZ>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// STZ addr,X
// Absolute Indexed,X
class STZ_9E : public AddressMode::AbsoluteIndexedX<Operator::STZ>
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int calculateCycles(const State& state) const override;
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]

// TAX
// Implied
class TAX_AA : public AddressMode::Implied<Operator::TAX>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]

// TAY
// Implied
class TAY_A8 : public AddressMode::Implied<Operator::TAY>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]

// TCD
// Implied
class TCD_5B : public AddressMode::Implied<Operator::TCD>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]

// TCS
// Implied
class TCS_1B : public AddressMode::Implied<Operator::TCS>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]

// TDC
// Implied
class TDC_7B : public AddressMode::Implied<Operator::TDC>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]

// TRB dp
// Direct Page
class TRB_14 : public AddressMode::DirectPage<Operator::TRB>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// TRB addr
// Absolute
class TRB_1C : public AddressMode::Absolute<Operator::TRB>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]

// TSB dp
// Direct Page
class TSB_04 : public AddressMode::DirectPage<Operator::TSB>
{
    using DirectPage::DirectPage;
    int calculateCycles(const State& state) const override;
};

// TSB addr
// Absolute
class TSB_0C : public AddressMode::Absolute<Operator::TSB>
{
    using Absolute::Absolute;
    int calculateCycles(const State& state) const override;
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]

// TSC
// Implied
class TSC_3B : public AddressMode::Implied<Operator::TSC>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]

// TSX
// Implied
class TSX_BA : public AddressMode::Implied<Operator::TSX>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]

// TXA
// Implied
class TXA_8A : public AddressMode::Implied<Operator::TXA>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]

// TXS
// Implied
class TXS_9A : public AddressMode::Implied<Operator::TXS>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]

// TXY
// Implied
class TXY_9B : public AddressMode::Implied<Operator::TXY>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]

// TYA
// Implied
class TYA_98 : public AddressMode::Implied<Operator::TYA>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]

// TYX
// Implied
class TYX_BB : public AddressMode::Implied<Operator::TYX>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// WAI Wait for Interrupt [Flags affected: none]

// WAI
// Implied
class WAI_CB : public AddressMode::Implied<Operator::WAI>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]

// WDM
// n/a
// 16: Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths
class WDM_42 : public AddressMode::na<Operator::WDM>
{
    using na::na;
    int calculateCycles(const State& state) const override;
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]

// XBA
// Implied
class XBA_EB : public AddressMode::Implied<Operator::XBA>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]

// XCE
// Implied
class XCE_FB : public AddressMode::Implied<Operator::XCE>
{
    using Implied::Implied;
    int calculateCycles(const State& state) const override;
};

