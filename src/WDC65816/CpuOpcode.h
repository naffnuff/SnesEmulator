#pragma once

#include "Exception.h"
#include "CpuState.h"
#include "CpuAddressMode.h"
#include "CpuOperator.h"

namespace CPU {

namespace Opcode {

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
class ADC_61 : public AddressMode::DirectPageIndexedIndirectX<Operator::ADC>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   mm....mm . ADC ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_61");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "61: ADC (dp,X)"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC sr,S
// Stack Relative (2-Byte)
class ADC_63 : public AddressMode::StackRelative<Operator::ADC>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     mm....mm . ADC $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_63");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "63: ADC sr,S"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp
// Direct Page (2-Byte)
class ADC_65 : public AddressMode::DirectPage<Operator::ADC>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       mm....mm . ADC $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_65");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "65: ADC dp"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp]
// Direct Page Indirect Long (2-Byte)
class ADC_67 : public AddressMode::DirectPageIndirectLong<Operator::ADC>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     mm....mm . ADC [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_67");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "67: ADC [dp]"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class ADC_69_16Bit : public AddressMode::Immediate16Bit<Operator::ADC>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       mm....mm . ADC #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_69_16Bit");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "69: ADC #const (16-bit)"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class ADC_69 : public AddressMode::Immediate<Operator::ADC>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       mm....mm . ADC #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "69: ADC #const"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr
// Absolute (3-Byte)
class ADC_6D : public AddressMode::Absolute<Operator::ADC>
{
    using Absolute::Absolute;

    // 3   5-m         abs       mm....mm . ADC $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_6D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "6D: ADC addr"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long
// Absolute Long (4-Byte)
class ADC_6F : public AddressMode::AbsoluteLong<Operator::ADC>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      mm....mm . ADC $FEDBCA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_6F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "6F: ADC long"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class ADC_71 : public AddressMode::DirectPageIndirectIndexedY<Operator::ADC>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w-x+x*p (dir),Y   mm....mm . ADC ($10),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_71");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "71: ADC (dp),Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp)
// Direct Page Indirect (2-Byte)
class ADC_72 : public AddressMode::DirectPageIndirect<Operator::ADC>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     mm....mm . ADC ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_72");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "72: ADC (dp)"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class ADC_73 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ADC>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y mm....mm . ADC ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_73");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "73: ADC (sr,S),Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp,X
// Direct Page Indexed, X (2-Byte)
class ADC_75 : public AddressMode::DirectPageIndexed<Operator::ADC, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     mm....mm . ADC $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_75");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "75: ADC dp,X"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class ADC_77 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ADC>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   mm....mm . ADC [$10],Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_77");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "77: ADC [dp],Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,Y
// Absolute Indexed, Y (3-Byte)
class ADC_79 : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::ADC, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,Y     mm....mm . ADC $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_79");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "79: ADC addr,Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,X
// Absolute Indexed, X (3-Byte)
class ADC_7D : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::ADC, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     mm....mm . ADC $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_7D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "7D: ADC addr,X"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long,X
// Absolute Long Indexed, X (4-Byte)
class ADC_7F : public AddressMode::AbsoluteLongIndexedX<Operator::ADC>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    mm....mm . ADC $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_7F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "7F: ADC long,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
class AND_21 : public AddressMode::DirectPageIndexedIndirectX<Operator::AND>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   m.....m. . AND ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_21");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "21: AND (dp,X)"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND sr,S
// Stack Relative (2-Byte)
class AND_23 : public AddressMode::StackRelative<Operator::AND>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     m.....m. . AND $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_23");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "23: AND sr,S"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp
// Direct Page (2-Byte)
class AND_25 : public AddressMode::DirectPage<Operator::AND>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       m.....m. . AND $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_25");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "25: AND dp"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp]
// Direct Page Indirect Long (2-Byte)
class AND_27 : public AddressMode::DirectPageIndirectLong<Operator::AND>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     m.....m. . AND [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_27");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "27: AND [dp]"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class AND_29_16Bit : public AddressMode::Immediate16Bit<Operator::AND>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       m.....m. . AND #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_29_16Bit");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "29: AND #const (16-bit)"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class AND_29 : public AddressMode::Immediate<Operator::AND>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       m.....m. . AND #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_29");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "29: AND #const"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr
// Absolute (3-Byte)
class AND_2D : public AddressMode::Absolute<Operator::AND>
{
    using Absolute::Absolute;

    // 3   5-m         abs       m.....m. . AND $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_2D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "2D: AND addr"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long
// Absolute Long (4-Byte)
class AND_2F : public AddressMode::AbsoluteLong<Operator::AND>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      m.....m. . AND $FEDBCA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_2F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "2F: AND long"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class AND_31 : public AddressMode::DirectPageIndirectIndexedY<Operator::AND>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . AND ($10),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_31");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "31: AND (dp),Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp)
// Direct Page Indirect (2-Byte)
class AND_32 : public AddressMode::DirectPageIndirect<Operator::AND>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     m.....m. . AND ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_32");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "32: AND (dp)"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class AND_33 : public AddressMode::StackRelativeIndirectIndexedY<Operator::AND>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y m.....m. . AND ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_33");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "33: AND (sr,S),Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp,X
// Direct Page Indexed, X (2-Byte)
class AND_35 : public AddressMode::DirectPageIndexed<Operator::AND, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     m.....m. . AND $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_35");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "35: AND dp,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class AND_37 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::AND>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   m.....m. . AND [$10],Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_37");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "37: AND [dp],Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,Y
// Absolute Indexed, Y (3-Byte)
class AND_39 : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::AND, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,Y     m.....m. . AND $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_39");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "39: AND addr,Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,X
// Absolute Indexed, X (3-Byte)
class AND_3D : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::AND, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     m.....m. . AND $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_3D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "3D: AND addr,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long,X
// Absolute Long Indexed, X (4-Byte)
class AND_3F : public AddressMode::AbsoluteLongIndexedX<Operator::AND>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    m.....m. . AND $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_3F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "3F: AND long,X"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp
// Direct Page (2-Byte)
class ASL_06 : public AddressMode::DirectPage<Operator::ASL>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       m.....mm . ASL $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ASL_06");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "06: ASL dp"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL A
// Accumulator (1-Byte)
class ASL_0A : public AddressMode::Accumulator<Operator::ASL>
{
    using Accumulator::Accumulator;

    // 1   2           acc       m.....mm . ASL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ASL_0A");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "0A: ASL A"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr
// Absolute (3-Byte)
class ASL_0E : public AddressMode::Absolute<Operator::ASL>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       m.....mm . ASL $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ASL_0E");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "0E: ASL addr"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp,X
// Direct Page Indexed, X (2-Byte)
class ASL_16 : public AddressMode::DirectPageIndexed<Operator::ASL, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   8-2*m+w     dir,X     m.....mm . ASL $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ASL_16");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "16: ASL dp,X"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr,X
// Absolute Indexed, X (3-Byte)
class ASL_1E : public AddressMode::AbsoluteIndexed<Operator::ASL, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   9-2*m       abs,X     m.....mm . ASL $9876,X
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ASL_1E");
        throw OpcodeNotYetImplementedException("TODO20");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "1E: ASL addr,X"; }
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
// BCC nearlabel
// Program Counter Relative (2-Byte)
class BCC_90 : public AddressMode::ProgramCounterRelative<Operator::BCC>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BCC LABEL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BCC_90");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "90: BCC nearlabel"; }
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
// BCS nearlabel
// Program Counter Relative (2-Byte)
class BCS_B0 : public AddressMode::ProgramCounterRelative<Operator::BCS>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BCS LABEL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BCS_B0");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "B0: BCS nearlabel"; }
};

// BEQ Branch if Equal [Flags affected: none]
// BEQ nearlabel
// Program Counter Relative (2-Byte)
class BEQ_F0 : public AddressMode::ProgramCounterRelative<Operator::BEQ>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BEQ LABEL
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "F0: BEQ nearlabel"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp
// Direct Page (2-Byte)
class BIT_24 : public AddressMode::DirectPage<Operator::BIT>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       mm....m. . BIT $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BIT_24");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "24: BIT dp"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr
// Absolute (3-Byte)
class BIT_2C : public AddressMode::Absolute<Operator::BIT>
{
    using Absolute::Absolute;

    // 3   5-m         abs       mm....m. . BIT $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BIT_2C");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "2C: BIT addr"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp,X
// Direct Page Indexed, X (2-Byte)
class BIT_34 : public AddressMode::DirectPageIndexed<Operator::BIT, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     mm....m. . BIT $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BIT_34");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "34: BIT dp,X"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr,X
// Absolute Indexed, X (3-Byte)
class BIT_3C : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::BIT, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     mm....m. . BIT $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BIT_3C");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "3C: BIT addr,X"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class BIT_89_16Bit : public AddressMode::Immediate16Bit<Operator::BIT>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       ......m. . BIT #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BIT_89_16Bit");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "89: BIT #const (16-bit)"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class BIT_89 : public AddressMode::Immediate<Operator::BIT>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       ......m. . BIT #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BIT_89");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "89: BIT #const"; }
};

// BMI Branch if Minus [Flags affected: none]
// BMI nearlabel
// Program Counter Relative (2-Byte)
class BMI_30 : public AddressMode::ProgramCounterRelative<Operator::BMI>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BMI LABEL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BMI_30");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "30: BMI nearlabel"; }
};

// BNE Branch if Not Equal [Flags affected: none]
// BNE nearlabel
// Program Counter Relative (2-Byte)
class BNE_D0 : public AddressMode::ProgramCounterRelative<Operator::BNE>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BNE LABEL
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "D0: BNE nearlabel"; }
};

// BPL Branch if Plus [Flags affected: none]
// BPL nearlabel
// Program Counter Relative (2-Byte)
class BPL_10 : public AddressMode::ProgramCounterRelative<Operator::BPL>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BPL LABEL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BPL_10");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "10: BPL nearlabel"; }
};

// BRA Branch Always [Flags affected: none]
// BRA nearlabel
// Program Counter Relative (2-Byte)
class BRA_80 : public AddressMode::ProgramCounterRelative<Operator::BRA>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   3+e*p       rel8      ........ . BRA LABEL
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "80: BRA nearlabel"; }
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
// BRK
// Immediate (2-Byte [18])
// ¤18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class BRK_00 : public AddressMode::Immediate<Operator::BRK>
{
    using Immediate::Immediate;

    // 1   8-e         imp       ....01.. . BRK
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BRK_00");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "00: BRK"; }
};

// BRL Branch Long Always [Flags affected: none]
// BRL label
// Program Counter Relative Long (3-Byte)
class BRL_82 : public AddressMode::ProgramCounterRelativeLong<Operator::BRL>
{
    using ProgramCounterRelativeLong::ProgramCounterRelativeLong;

    // 3   4           rel16     ........ . BRL LABEL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BRL_82");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "82: BRL label"; }
};

// BVC Branch if Overflow Clear [Flags affected: none]
// BVC nearlabel
// Program Counter Relative (2-Byte)
class BVC_50 : public AddressMode::ProgramCounterRelative<Operator::BVC>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BVC LABEL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("BVC_50");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "50: BVC nearlabel"; }
};

// BVS Branch if Overflow Set [Flags affected: none]
// BVS nearlabel
// Program Counter Relative (2-Byte)
class BVS_70 : public AddressMode::ProgramCounterRelative<Operator::BVS>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    // 2   2+t+t*e*p   rel8      ........ . BVS LABEL
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "70: BVS nearlabel"; }
};

// CLC Clear Carry [Flags affected: c]
// CLC
// Implied (1-Byte)
class CLC_18 : public AddressMode::Implied<Operator::SE<State::c, false>>
{
    using Implied::Implied;

    // 1   2           imp       .......0 . CLC
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "18: CLC"; }
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
// CLD
// Implied (1-Byte)
class CLD_D8 : public AddressMode::Implied<Operator::SE<State::d, false>>
{
    using Implied::Implied;

    // 1   2           imp       ....0... . CLD
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CLD_D8");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "D8: CLD"; }
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
// CLI
// Implied (1-Byte)
class CLI_58 : public AddressMode::Implied<Operator::SE<State::i, false>>
{
    using Implied::Implied;

    // 1   2           imp       .....0.. . CLI
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "58: CLI"; }
};

// CLV Clear Overflow Flag [Flags affected: v]
// CLV
// Implied (1-Byte)
class CLV_B8 : public AddressMode::Implied<Operator::SE<State::v, false>>
{
    using Implied::Implied;

    // 1   2           imp       .0...... . CLV
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CLV_B8");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "B8: CLV"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp,X)
// Direct Page Indexed Indirect,X (2-Byte)
class CMP_C1 : public AddressMode::DirectPageIndexedIndirectX<Operator::CMP>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   m.....mm . CMP ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_C1");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "C1: CMP (dp,X)"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP sr,S
// Stack Relative (2-Byte)
class CMP_C3 : public AddressMode::StackRelative<Operator::CMP>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     m.....mm . CMP $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_C3");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "C3: CMP sr,S"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp
// Direct Page (2-Byte)
class CMP_C5 : public AddressMode::DirectPage<Operator::CMP>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       m.....mm . CMP $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_C5");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "C5: CMP dp"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp]
// Direct Page Indirect Long (2-Byte)
class CMP_C7 : public AddressMode::DirectPageIndirectLong<Operator::CMP>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     m.....mm . CMP [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_C7");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "C7: CMP [dp]"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class CMP_C9_16Bit : public AddressMode::Immediate16Bit<Operator::CMP>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       m.....mm . CMP #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "C9: CMP #const (16-bit)"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class CMP_C9 : public AddressMode::Immediate<Operator::CMP>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       m.....mm . CMP #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_C9");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "C9: CMP #const"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr
// Absolute (3-Byte)
class CMP_CD : public AddressMode::Absolute<Operator::CMP>
{
    using Absolute::Absolute;

    // 3   5-m         abs       m.....mm . CMP $9876
    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "CD: CMP addr"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long
// Absolute Long (4-Byte)
class CMP_CF : public AddressMode::AbsoluteLong<Operator::CMP>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      m.....mm . CMP $FEDBCA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_CF");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "CF: CMP long"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class CMP_D1 : public AddressMode::DirectPageIndirectIndexedY<Operator::CMP>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w-x+x*p (dir),Y   m.....mm . CMP ($10),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_D1");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "D1: CMP (dp),Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp)
// Direct Page Indirect (2-Byte)
class CMP_D2 : public AddressMode::DirectPageIndirect<Operator::CMP>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     m.....mm . CMP ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_D2");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "D2: CMP (dp)"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class CMP_D3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::CMP>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y m.....mm . CMP ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_D3");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "D3: CMP (sr,S),Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp,X
// Direct Page Indexed, X (2-Byte)
class CMP_D5 : public AddressMode::DirectPageIndexed<Operator::CMP, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     m.....mm . CMP $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_D5");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "D5: CMP dp,X"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class CMP_D7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::CMP>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   m.....mm . CMP [$10],Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_D7");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "D7: CMP [dp],Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,Y
// Absolute Indexed, Y (3-Byte)
class CMP_D9 : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::CMP, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,Y     m.....mm . CMP $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_D9");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "D9: CMP addr,Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,X
// Absolute Indexed, X (3-Byte)
class CMP_DD : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::CMP, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     m.....mm . CMP $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_DD");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "DD: CMP addr,X"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long,X
// Absolute Long Indexed, X (4-Byte)
class CMP_DF : public AddressMode::AbsoluteLongIndexedX<Operator::CMP>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    m.....mm . CMP $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_DF");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "DF: CMP long,X"; }
};

// COP Co-Processor Enable [Flags affected: d,i]
// COP const
// Immediate (2-Byte [18])
// ¤18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class COP_02 : public AddressMode::Immediate<Operator::COP>
{
    using Immediate::Immediate;

    // 2   8-e         imm       ....01.. . COP #$12
    int execute() override
    {
        throw OpcodeNotYetImplementedException("COP_02");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "02: COP const"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class CPX_E0_16Bit : public AddressMode::Immediate16Bit<Operator::CP<State::X>>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-x 3-x         imm       x.....xx . CPX #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "E0: CPX #const (16-bit)"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class CPX_E0 : public AddressMode::Immediate<Operator::CP<State::X>>
{
    using Immediate::Immediate;

    // 3-x 3-x         imm       x.....xx . CPX #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CPX_E0");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "E0: CPX #const"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX dp
// Direct Page (2-Byte)
class CPX_E4 : public AddressMode::DirectPage<Operator::CP<State::X>>
{
    using DirectPage::DirectPage;

    // 2   4-x+w       dir       x.....xx . CPX $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CPX_E4");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "E4: CPX dp"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX addr
// Absolute (3-Byte)
class CPX_EC : public AddressMode::Absolute<Operator::CP<State::X>>
{
    using Absolute::Absolute;

    // 3   5-x         abs       x.....xx . CPX $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CPX_EC");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "EC: CPX addr"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class CPY_C0_16Bit : public AddressMode::Immediate16Bit<Operator::CP<State::Y>>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-x 3-x         imm       x.....xx . CPY #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "C0: CPY #const (16-bit)"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class CPY_C0 : public AddressMode::Immediate<Operator::CP<State::Y>>
{
    using Immediate::Immediate;

    // 3-x 3-x         imm       x.....xx . CPY #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CPY_C0");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "C0: CPY #const"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY dp
// Direct Page (2-Byte)
class CPY_C4 : public AddressMode::DirectPage<Operator::CP<State::Y>>
{
    using DirectPage::DirectPage;

    // 2   4-x+w       dir       x.....xx . CPY $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CPY_C4");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "C4: CPY dp"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY addr
// Absolute (3-Byte)
class CPY_CC : public AddressMode::Absolute<Operator::CP<State::Y>>
{
    using Absolute::Absolute;

    // 3   5-x         abs       x.....xx . CPY $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("CPY_CC");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "CC: CPY addr"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC A
// Accumulator (1-Byte)
class DEC_3A : public AddressMode::Accumulator<Operator::DEC>
{
    using Accumulator::Accumulator;

    // 1   2           acc       m.....m. . DEC
    int execute() override
    {
        throw OpcodeNotYetImplementedException("DEC_3A");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "3A: DEC A"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC dp
// Direct Page (2-Byte)
class DEC_C6 : public AddressMode::DirectPage<Operator::DEC>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       m.....m. . DEC $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("DEC_C6");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "C6: DEC dp"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC addr
// Absolute (3-Byte)
class DEC_CE : public AddressMode::Absolute<Operator::DEC>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       m.....m. . DEC $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("DEC_CE");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "CE: DEC addr"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC dp,X
// Direct Page Indexed, X (2-Byte)
class DEC_D6 : public AddressMode::DirectPageIndexed<Operator::DEC, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   8-2*m+w     dir,X     m.....m. . DEC $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("DEC_D6");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "D6: DEC dp,X"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC addr,X
// Absolute Indexed, X (3-Byte)
class DEC_DE : public AddressMode::AbsoluteIndexed<Operator::DEC, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   9-2*m       abs,X     m.....m. . DEC $9876,X
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("DEC_DE");
        throw OpcodeNotYetImplementedException("TODO20");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "DE: DEC addr,X"; }
};

// DEX Decrement Index Register X [Flags affected: n,z]
// DEX
// Implied (1-Byte)
class DEX_CA : public AddressMode::Implied<Operator::DE<State::X>>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . DEX
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "CA: DEX"; }
};

// DEY Decrement Index Register Y [Flags affected: n,z]
// DEY
// Implied (1-Byte)
class DEY_88 : public AddressMode::Implied<Operator::DE<State::Y>>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . DEY
    int execute() override
    {
        throw OpcodeNotYetImplementedException("DEY_88");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "88: DEY"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp,X)
// Direct Page Indexed Indirect,X (2-Byte)
class EOR_41 : public AddressMode::DirectPageIndexedIndirectX<Operator::EOR>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   m.....m. . EOR ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_41");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "41: EOR (dp,X)"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR sr,S
// Stack Relative (2-Byte)
class EOR_43 : public AddressMode::StackRelative<Operator::EOR>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     m.....m. . EOR $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_43");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "43: EOR sr,S"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp
// Direct Page (2-Byte)
class EOR_45 : public AddressMode::DirectPage<Operator::EOR>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       m.....m. . EOR $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_45");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "45: EOR dp"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp]
// Direct Page Indirect Long (2-Byte)
class EOR_47 : public AddressMode::DirectPageIndirectLong<Operator::EOR>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     m.....m. . EOR [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_47");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "47: EOR [dp]"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class EOR_49_16Bit : public AddressMode::Immediate16Bit<Operator::EOR>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       m.....m. . EOR #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_49_16Bit");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "49: EOR #const (16-bit)"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class EOR_49 : public AddressMode::Immediate<Operator::EOR>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       m.....m. . EOR #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_49");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "49: EOR #const"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr
// Absolute (3-Byte)
class EOR_4D : public AddressMode::Absolute<Operator::EOR>
{
    using Absolute::Absolute;

    // 3   5-m         abs       m.....m. . EOR $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_4D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "4D: EOR addr"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long
// Absolute Long (4-Byte)
class EOR_4F : public AddressMode::AbsoluteLong<Operator::EOR>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      m.....m. . EOR $FEDBCA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_4F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "4F: EOR long"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class EOR_51 : public AddressMode::DirectPageIndirectIndexedY<Operator::EOR>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . EOR ($10),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_51");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "51: EOR (dp),Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp)
// Direct Page Indirect (2-Byte)
class EOR_52 : public AddressMode::DirectPageIndirect<Operator::EOR>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     m.....m. . EOR ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_52");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "52: EOR (dp)"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class EOR_53 : public AddressMode::StackRelativeIndirectIndexedY<Operator::EOR>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y m.....m. . EOR ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_53");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "53: EOR (sr,S),Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp,X
// Direct Page Indexed, X (2-Byte)
class EOR_55 : public AddressMode::DirectPageIndexed<Operator::EOR, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     m.....m. . EOR $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_55");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "55: EOR dp,X"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class EOR_57 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::EOR>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   m.....m. . EOR [$10],Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_57");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "57: EOR [dp],Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,Y
// Absolute Indexed, Y (3-Byte)
class EOR_59 : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::EOR, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,Y     m.....m. . EOR $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_59");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "59: EOR addr,Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,X
// Absolute Indexed, X (3-Byte)
class EOR_5D : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::EOR, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     m.....m. . EOR $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_5D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "5D: EOR addr,X"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long,X
// Absolute Long Indexed, X (4-Byte)
class EOR_5F : public AddressMode::AbsoluteLongIndexedX<Operator::EOR>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    m.....m. . EOR $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_5F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "5F: EOR long,X"; }
};

// INC Increment [Flags affected: n,z]
// INC A
// Accumulator (1-Byte)
class INC_1A : public AddressMode::Accumulator<Operator::INC>
{
    using Accumulator::Accumulator;

    // 1   2           acc       m.....m. . INC
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "1A: INC A"; }
};

// INC Increment [Flags affected: n,z]
// INC dp
// Direct Page (2-Byte)
class INC_E6 : public AddressMode::DirectPage<Operator::INC>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       m.....m. . INC $10
    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "E6: INC dp"; }
};

// INC Increment [Flags affected: n,z]
// INC addr
// Absolute (3-Byte)
class INC_EE : public AddressMode::Absolute<Operator::INC>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       m.....m. . INC $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("INC_EE");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "EE: INC addr"; }
};

// INC Increment [Flags affected: n,z]
// INC dp,X
// Direct Page Indexed, X (2-Byte)
class INC_F6 : public AddressMode::DirectPageIndexed<Operator::INC, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   8-2*m+w     dir,X     m.....m. . INC $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("INC_F6");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "F6: INC dp,X"; }
};

// INC Increment [Flags affected: n,z]
// INC addr,X
// Absolute Indexed, X (3-Byte)
class INC_FE : public AddressMode::AbsoluteIndexed<Operator::INC, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   9-2*m       abs,X     m.....m. . INC $9876,X
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("INC_FE");
        throw OpcodeNotYetImplementedException("TODO20");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "FE: INC addr,X"; }
};

// INX Increment Index Register X [Flags affected: n,z]
// INX
// Implied (1-Byte)
class INX_E8 : public AddressMode::Implied<Operator::IN<State::X>>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . INX
    int execute() override
    {
        throw OpcodeNotYetImplementedException("INX_E8");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "E8: INX"; }
};

// INY Increment Index Register Y [Flags affected: n,z]
// INY
// Implied (1-Byte)
class INY_C8 : public AddressMode::Implied<Operator::IN<State::Y>>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . INY
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "C8: INY"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP addr
// Absolute (3-Byte)
class JMP_4C : public AddressMode::Absolute_ControlFlow<Operator::JMP>
{
    using Absolute_ControlFlow::Absolute_ControlFlow;

    // 3   3           abs       ........ . JMP $1234
    int execute() override
    {
        throw OpcodeNotYetImplementedException("JMP_4C");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "4C: JMP addr"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP long
// Absolute Long (4-Byte)
class JMP_5C : public AddressMode::AbsoluteLong_ControlFlow<Operator::JML>
{
    using AbsoluteLong_ControlFlow::AbsoluteLong_ControlFlow;

    // 4   4           long      ........ . JMP $FEDCBA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("JMP_5C");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "5C: JMP long"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr)
// Absolute Indirect (3-Byte)
class JMP_6C : public AddressMode::AbsoluteIndirect<Operator::JMP>
{
    using AbsoluteIndirect::AbsoluteIndirect;

    // 3   5           (abs)     ........ . JMP ($1234)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("JMP_6C");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "6C: JMP (addr)"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr,X)
// Absolute Indexed Indirect (3-Byte)
class JMP_7C : public AddressMode::AbsoluteIndexedIndirect<Operator::JMP>
{
    using AbsoluteIndexedIndirect::AbsoluteIndexedIndirect;

    // 3   6           (abs,X)   ........ . JMP ($1234,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("JMP_7C");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "7C: JMP (addr,X)"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP [addr]
// Absolute Indirect Long (3-Byte)
class JMP_DC : public AddressMode::AbsoluteIndirectLong<Operator::JML>
{
    using AbsoluteIndirectLong::AbsoluteIndirectLong;

    // 3   6           [abs]     ........ . JMP [$1234]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("JMP_DC");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "DC: JMP [addr]"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR addr
// Absolute (3-Byte)
class JSR_20 : public AddressMode::Absolute_ControlFlow<Operator::JSR>
{
    using Absolute_ControlFlow::Absolute_ControlFlow;

    // 3   6           abs       ........ . JSR $1234
    int execute() override
    {
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "20: JSR addr"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR long
// Absolute Long (4-Byte)
class JSR_22 : public AddressMode::AbsoluteLong_ControlFlow<Operator::JSL>
{
    using AbsoluteLong_ControlFlow::AbsoluteLong_ControlFlow;

    // 4   8           long      ........ . JSL $123456
    int execute() override
    {
        throw OpcodeNotYetImplementedException("JSR_22");
        return 8 + applyOperand();
    }

    std::string opcodeToString() const override { return "22: JSR long"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR (addr,X)
// Absolute Indexed Indirect (3-Byte)
class JSR_FC : public AddressMode::AbsoluteIndexedIndirect<Operator::JSR>
{
    using AbsoluteIndexedIndirect::AbsoluteIndexedIndirect;

    // 3   8           (abs,X)   ........ . JSR ($1234,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("JSR_FC");
        return 8 + applyOperand();
    }

    std::string opcodeToString() const override { return "FC: JSR (addr,X)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
class LDA_A1 : public AddressMode::DirectPageIndexedIndirectX<Operator::LDA>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   m.....m. . LDA ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_A1");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "A1: LDA (dp,X)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA sr,S
// Stack Relative (2-Byte)
class LDA_A3 : public AddressMode::StackRelative<Operator::LDA>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     m.....m. . LDA $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_A3");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "A3: LDA sr,S"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp
// Direct Page (2-Byte)
class LDA_A5 : public AddressMode::DirectPage<Operator::LDA>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       m.....m. . LDA $10
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "A5: LDA dp"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp]
// Direct Page Indirect Long (2-Byte)
class LDA_A7 : public AddressMode::DirectPageIndirectLong<Operator::LDA>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     m.....m. . LDA [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_A7");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "A7: LDA [dp]"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class LDA_A9_16Bit : public AddressMode::Immediate16Bit<Operator::LDA>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       m.....m. . LDA #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A9: LDA #const (16-bit)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class LDA_A9 : public AddressMode::Immediate<Operator::LDA>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       m.....m. . LDA #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A9: LDA #const"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr
// Absolute (3-Byte)
class LDA_AD : public AddressMode::Absolute<Operator::LDA>
{
    using Absolute::Absolute;

    // 3   5-m         abs       m.....m. . LDA $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_AD");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AD: LDA addr"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long
// Absolute Long (4-Byte)
class LDA_AF : public AddressMode::AbsoluteLong<Operator::LDA>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      m.....m. . LDA $FEDBCA
    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "AF: LDA long"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class LDA_B1 : public AddressMode::DirectPageIndirectIndexedY<Operator::LDA>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . LDA ($10),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_B1");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "B1: LDA (dp),Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp)
// Direct Page Indirect (2-Byte)
class LDA_B2 : public AddressMode::DirectPageIndirect<Operator::LDA>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     m.....m. . LDA ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_B2");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "B2: LDA (dp)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class LDA_B3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::LDA>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y m.....m. . LDA ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_B3");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "B3: LDA (sr,S),Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp,X
// Direct Page Indexed, X (2-Byte)
class LDA_B5 : public AddressMode::DirectPageIndexed<Operator::LDA, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     m.....m. . LDA $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_B5");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "B5: LDA dp,X"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class LDA_B7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::LDA>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   m.....m. . LDA [$10],Y
    int execute() override
    {
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "B7: LDA [dp],Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,Y
// Absolute Indexed, Y (3-Byte)
class LDA_B9 : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::LDA, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,Y     m.....m. . LDA $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_B9");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "B9: LDA addr,Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,X
// Absolute Indexed, X (3-Byte)
class LDA_BD : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::LDA, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     m.....m. . LDA $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_BD");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "BD: LDA addr,X"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long,X
// Absolute Long Indexed, X (4-Byte)
class LDA_BF : public AddressMode::AbsoluteLongIndexedX<Operator::LDA>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    m.....m. . LDA $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDA_BF");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "BF: LDA long,X"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class LDX_A2_16Bit : public AddressMode::Immediate16Bit<Operator::LD<State::X>>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-x 3-x         imm       x.....x. . LDX #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A2: LDX #const (16-bit)"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class LDX_A2 : public AddressMode::Immediate<Operator::LD<State::X>>
{
    using Immediate::Immediate;

    // 3-x 3-x         imm       x.....x. . LDX #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDX_A2");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A2: LDX #const"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp
// Direct Page (2-Byte)
class LDX_A6 : public AddressMode::DirectPage<Operator::LD<State::X>>
{
    using DirectPage::DirectPage;

    // 2   4-x+w       dir       x.....x. . LDX $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDX_A6");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "A6: LDX dp"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr
// Absolute (3-Byte)
class LDX_AE : public AddressMode::Absolute<Operator::LD<State::X>>
{
    using Absolute::Absolute;

    // 3   5-x         abs       x.....x. . LDX $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDX_AE");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AE: LDX addr"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp,Y
// Direct Page Indexed, Y (2-Byte)
class LDX_B6 : public AddressMode::DirectPageIndexed<Operator::LD<State::X>, State::Y>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-x+w       dir,Y     x.....x. . LDX $10,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDX_B6");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "B6: LDX dp,Y"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr,Y
// Absolute Indexed, Y (3-Byte)
class LDX_BE : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::LD<State::X>, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-2*x+x*p   abs,Y     x.....x. . LDX $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDX_BE");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "BE: LDX addr,Y"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class LDY_A0_16Bit : public AddressMode::Immediate16Bit<Operator::LD<State::Y>>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-x 3-x         imm       x.....x. . LDY #$54
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A0: LDY #const (16-bit)"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY #const
// Immediate (2-Byte [19])
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class LDY_A0 : public AddressMode::Immediate<Operator::LD<State::Y>>
{
    using Immediate::Immediate;

    // 3-x 3-x         imm       x.....x. . LDY #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDY_A0");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A0: LDY #const"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp
// Direct Page (2-Byte)
class LDY_A4 : public AddressMode::DirectPage<Operator::LD<State::Y>>
{
    using DirectPage::DirectPage;

    // 2   4-x+w       dir       x.....x. . LDY $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDY_A4");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "A4: LDY dp"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr
// Absolute (3-Byte)
class LDY_AC : public AddressMode::Absolute<Operator::LD<State::Y>>
{
    using Absolute::Absolute;

    // 3   5-x         abs       x.....x. . LDY $9876
    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AC: LDY addr"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp,X
// Direct Page Indexed, X (2-Byte)
class LDY_B4 : public AddressMode::DirectPageIndexed<Operator::LD<State::Y>, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-x+w       dir,X     x.....x. . LDY $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDY_B4");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "B4: LDY dp,X"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr,X
// Absolute Indexed, X (3-Byte)
class LDY_BC : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::LD<State::Y>, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-2*x+x*p   abs,X     x.....x. . LDY $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LDY_BC");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "BC: LDY addr,X"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp
// Direct Page (2-Byte)
class LSR_46 : public AddressMode::DirectPage<Operator::LSR>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       0.....m* . LSR $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LSR_46");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "46: LSR dp"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR A
// Accumulator (1-Byte)
class LSR_4A : public AddressMode::Accumulator<Operator::LSR>
{
    using Accumulator::Accumulator;

    // 1   2           acc       0.....m* . LSR
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LSR_4A");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "4A: LSR A"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr
// Absolute (3-Byte)
class LSR_4E : public AddressMode::Absolute<Operator::LSR>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       0.....m* . LSR $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LSR_4E");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "4E: LSR addr"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp,X
// Direct Page Indexed, X (2-Byte)
class LSR_56 : public AddressMode::DirectPageIndexed<Operator::LSR, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   8-2*m+w     dir,X     0.....m* . LSR $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LSR_56");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "56: LSR dp,X"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr,X
// Absolute Indexed, X (3-Byte)
class LSR_5E : public AddressMode::AbsoluteIndexed<Operator::LSR, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   9-2*m       abs,X     0.....m* . LSR $9876,X
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("LSR_5E");
        throw OpcodeNotYetImplementedException("TODO20");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "5E: LSR addr,X"; }
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
// MVN srcbk,destbk
// Block Move (3-Byte)
class MVN_54 : public AddressMode::BlockMove<Operator::MVN>
{
    using BlockMove::BlockMove;

    // 3   7           src,dest  ........ . MVN #$12,#$34
    int execute() override
    {
        throw OpcodeNotYetImplementedException("MVN_54");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "54: MVN srcbk,destbk"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
// MVP srcbk,destbk
// Block Move (3-Byte)
class MVP_44 : public AddressMode::BlockMove<Operator::MVP>
{
    using BlockMove::BlockMove;

    // 3   7           src,dest  ........ . MVP #$12,#$34
    int execute() override
    {
        throw OpcodeNotYetImplementedException("MVP_44");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "44: MVP srcbk,destbk"; }
};

// NOP No Operation [Flags affected: none]
// NOP
// Implied (1-Byte)
class NOP_EA : public AddressMode::Implied<Operator::NOP>
{
    using Implied::Implied;

    // 1   2           imp       ........ . NOP
    int execute() override
    {
        throw OpcodeNotYetImplementedException("NOP_EA");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "EA: NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
class ORA_01 : public AddressMode::DirectPageIndexedIndirectX<Operator::ORA>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   m.....m. . ORA ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_01");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "01: ORA (dp,X)"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA sr,S
// Stack Relative (2-Byte)
class ORA_03 : public AddressMode::StackRelative<Operator::ORA>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     m.....m. . ORA $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_03");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "03: ORA sr,S"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp
// Direct Page (2-Byte)
class ORA_05 : public AddressMode::DirectPage<Operator::ORA>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       m.....m. . ORA $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_05");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "05: ORA dp"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp]
// Direct Page Indirect Long (2-Byte)
class ORA_07 : public AddressMode::DirectPageIndirectLong<Operator::ORA>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     m.....m. . ORA [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_07");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "07: ORA [dp]"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class ORA_09_16Bit : public AddressMode::Immediate16Bit<Operator::ORA>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       m.....m. . ORA #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_09_16Bit");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "09: ORA #const (16-bit)"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class ORA_09 : public AddressMode::Immediate<Operator::ORA>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       m.....m. . ORA #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_09");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "09: ORA #const"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr
// Absolute (3-Byte)
class ORA_0D : public AddressMode::Absolute<Operator::ORA>
{
    using Absolute::Absolute;

    // 3   5-m         abs       m.....m. . ORA $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_0D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "0D: ORA addr"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long
// Absolute Long (4-Byte)
class ORA_0F : public AddressMode::AbsoluteLong<Operator::ORA>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      m.....m. . ORA $FEDBCA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_0F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "0F: ORA long"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class ORA_11 : public AddressMode::DirectPageIndirectIndexedY<Operator::ORA>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . ORA ($10),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_11");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "11: ORA (dp),Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp)
// Direct Page Indirect (2-Byte)
class ORA_12 : public AddressMode::DirectPageIndirect<Operator::ORA>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     m.....m. . ORA ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_12");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "12: ORA (dp)"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class ORA_13 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ORA>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y m.....m. . ORA ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_13");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "13: ORA (sr,S),Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp,X
// Direct Page Indexed, X (2-Byte)
class ORA_15 : public AddressMode::DirectPageIndexed<Operator::ORA, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     m.....m. . ORA $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_15");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "15: ORA dp,X"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class ORA_17 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ORA>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   m.....m. . ORA [$10],Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_17");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "17: ORA [dp],Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,Y
// Absolute Indexed, Y (3-Byte)
class ORA_19 : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::ORA, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,Y     m.....m. . ORA $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_19");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "19: ORA addr,Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,X
// Absolute Indexed, X (3-Byte)
class ORA_1D : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::ORA, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     m.....m. . ORA $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_1D");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "1D: ORA addr,X"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long,X
// Absolute Long Indexed, X (4-Byte)
class ORA_1F : public AddressMode::AbsoluteLongIndexedX<Operator::ORA>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    m.....m. . ORA $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ORA_1F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "1F: ORA long,X"; }
};

// PEA Push Effective Absolute Address [Flags affected: none]
// PEA addr
// Absolute (3-Byte)
class PEA_F4 : public AddressMode::Absolute<Operator::PEA>
{
    using Absolute::Absolute;

    // 3   5           imm       ........ . PEA #$1234
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PEA_F4");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "F4: PEA addr"; }
};

// PEI Push Effective Indirect Address [Flags affected: none]
// PEI (dp)
// Direct Page Indirect (2-Byte)
class PEI_D4 : public AddressMode::DirectPageIndirect<Operator::PEI>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6+w         dir       ........ . PEI $12
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PEI_D4");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "D4: PEI (dp)"; }
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
// PER label
// Program Counter Relative Long (3-Byte)
class PER_62 : public AddressMode::ProgramCounterRelativeLong<Operator::PER>
{
    using ProgramCounterRelativeLong::ProgramCounterRelativeLong;

    // 3   6           imm       ........ . PER LABEL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PER_62");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "62: PER label"; }
};

// PHA Push Accumulator [Flags affected: none]
// PHA
// Implied (1-Byte)
class PHA_48 : public AddressMode::Implied<Operator::PHA>
{
    using Implied::Implied;

    // 1   4-m         imp       ........ . PHA
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "48: PHA"; }
};

// PHB Push Data Bank Register [Flags affected: none]
// PHB
// Implied (1-Byte)
class PHB_8B : public AddressMode::Implied<Operator::PHB>
{
    using Implied::Implied;

    // 1   3           imp       ........ . PHB
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PHB_8B");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "8B: PHB"; }
};

// PHD Push Direct Page Register [Flags affected: none]
// PHD
// Implied (1-Byte)
class PHD_0B : public AddressMode::Implied<Operator::PHD>
{
    using Implied::Implied;

    // 1   4           imp       ........ . PHD
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PHD_0B");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "0B: PHD"; }
};

// PHK Push Program Bank Register [Flags affected: none]
// PHK
// Implied (1-Byte)
class PHK_4B : public AddressMode::Implied<Operator::PHK>
{
    using Implied::Implied;

    // 1   3           imp       ........ . PHK
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PHK_4B");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "4B: PHK"; }
};

// PHP Push Processor Status Register [Flags affected: none]
// PHP
// Implied (1-Byte)
class PHP_08 : public AddressMode::Implied<Operator::PHP>
{
    using Implied::Implied;

    // 1   3           imp       ........ . PHP
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "08: PHP"; }
};

// PHX Push Index Register X [Flags affected: none]
// PHX
// Implied (1-Byte)
class PHX_DA : public AddressMode::Implied<Operator::PHX>
{
    using Implied::Implied;

    // 1   4-x         imp       ........ . PHX
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "DA: PHX"; }
};

// PHY Push Index Register Y [Flags affected: none]
// PHY
// Implied (1-Byte)
class PHY_5A : public AddressMode::Implied<Operator::PHY>
{
    using Implied::Implied;

    // 1   4-x         imp       ........ . PHY
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PHY_5A");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "5A: PHY"; }
};

// PLA Pull Accumulator [Flags affected: n,z]
// PLA
// Implied (1-Byte)
class PLA_68 : public AddressMode::Implied<Operator::PLA>
{
    using Implied::Implied;

    // 1   5-m         imp       m.....m. . PLA
    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "68: PLA"; }
};

// PLB Pull Data Bank Register [Flags affected: n,z]
// PLB
// Implied (1-Byte)
class PLB_AB : public AddressMode::Implied<Operator::PLB>
{
    using Implied::Implied;

    // 1   4           imp       *.....*. . PLB
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PLB_AB");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AB: PLB"; }
};

// PLD Pull Direct Page Register [Flags affected: n,z]
// PLD
// Implied (1-Byte)
class PLD_2B : public AddressMode::Implied<Operator::PLD>
{
    using Implied::Implied;

    // 1   5           imp       *.....*. . PLD
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PLD_2B");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "2B: PLD"; }
};

// PLP Pull Processor Status Register [Flags affected: n,z]
// PLP
// Implied (1-Byte)
class PLP_28 : public AddressMode::Implied<Operator::PLP>
{
    using Implied::Implied;

    // 1   4           imp       ******** . PLP
    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "28: PLP"; }
};

// PLX Pull Index Register X [Flags affected: n,z]
// PLX
// Implied (1-Byte)
class PLX_FA : public AddressMode::Implied<Operator::PLX>
{
    using Implied::Implied;

    // 1   5-x         imp       x.....x. . PLX
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PLX_FA");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "FA: PLX"; }
};

// PLY Pull Index Register Y [Flags affected: n,z]
// PLY
// Implied (1-Byte)
class PLY_7A : public AddressMode::Implied<Operator::PLY>
{
    using Implied::Implied;

    // 1   5-x         imp       x.....x. . PLY
    int execute() override
    {
        throw OpcodeNotYetImplementedException("PLY_7A");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "7A: PLY"; }
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
// REP #const
// Immediate (2-Byte)
class REP_C2 : public AddressMode::Immediate<Operator::REP>
{
    using Immediate::Immediate;

    // 2   3           imm       ******** . REP #$12
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "C2: REP #const"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp
// Direct Page (2-Byte)
class ROL_26 : public AddressMode::DirectPage<Operator::ROL>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       m.....mm . ROL $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROL_26");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "26: ROL dp"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL A
// Accumulator (1-Byte)
class ROL_2A : public AddressMode::Accumulator<Operator::ROL>
{
    using Accumulator::Accumulator;

    // 1   2           acc       m.....mm . ROL
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "2A: ROL A"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr
// Absolute (3-Byte)
class ROL_2E : public AddressMode::Absolute<Operator::ROL>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       m.....mm . ROL $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROL_2E");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "2E: ROL addr"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp,X
// Direct Page Indexed, X (2-Byte)
class ROL_36 : public AddressMode::DirectPageIndexed<Operator::ROL, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   8-2*m+w     dir,X     m.....mm . ROL $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROL_36");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "36: ROL dp,X"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr,X
// Absolute Indexed, X (3-Byte)
class ROL_3E : public AddressMode::AbsoluteIndexed<Operator::ROL, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   9-2*m       abs,X     m.....mm . ROL $9876,X
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROL_3E");
        throw OpcodeNotYetImplementedException("TODO20");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "3E: ROL addr,X"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp
// Direct Page (2-Byte)
class ROR_66 : public AddressMode::DirectPage<Operator::ROR>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       m.....m* . ROR $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROR_66");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "66: ROR dp"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR A
// Accumulator (1-Byte)
class ROR_6A : public AddressMode::Accumulator<Operator::ROR>
{
    using Accumulator::Accumulator;

    // 1   2           acc       m.....m* . ROR
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROR_6A");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "6A: ROR A"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr
// Absolute (3-Byte)
class ROR_6E : public AddressMode::Absolute<Operator::ROR>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       m.....m* . ROR $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROR_6E");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "6E: ROR addr"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp,X
// Direct Page Indexed, X (2-Byte)
class ROR_76 : public AddressMode::DirectPageIndexed<Operator::ROR, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   8-2*m+w     dir,X     m.....m* . ROR $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROR_76");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "76: ROR dp,X"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr,X
// Absolute Indexed, X (3-Byte)
class ROR_7E : public AddressMode::AbsoluteIndexed<Operator::ROR, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   9-2*m       abs,X     m.....m* . ROR $9876,X
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROR_7E");
        throw OpcodeNotYetImplementedException("TODO20");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "7E: ROR addr,X"; }
};

// RTI Return from Interrupt [Flags affected: all except b]
// RTI
// Implied (1-Byte)
class RTI_40 : public AddressMode::Implied<Operator::RTI>
{
    using Implied::Implied;

    // 1   7-e         imp       ******** . RTI
    int execute() override
    {
        throw OpcodeNotYetImplementedException("RTI_40");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "40: RTI"; }
};

// RTL Return from Subroutine Long [Flags affected: none]
// RTL
// Implied (1-Byte)
class RTL_6B : public AddressMode::Implied<Operator::RTL>
{
    using Implied::Implied;

    // 1   6           imp       ........ . RTL
    int execute() override
    {
        throw OpcodeNotYetImplementedException("RTL_6B");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "6B: RTL"; }
};

// RTS Return from Subroutine [Flags affected: none]
// RTS
// Implied (1-Byte)
class RTS_60 : public AddressMode::Implied<Operator::RTS>
{
    using Implied::Implied;

    // 1   6           imp       ........ . RTS
    int execute() override
    {
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "60: RTS"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
class SBC_E1 : public AddressMode::DirectPageIndexedIndirectX<Operator::SBC>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   mm....mm . SBC ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_E1");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "E1: SBC (dp,X)"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC sr,S
// Stack Relative (2-Byte)
class SBC_E3 : public AddressMode::StackRelative<Operator::SBC>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     mm....mm . SBC $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_E3");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "E3: SBC sr,S"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp
// Direct Page (2-Byte)
class SBC_E5 : public AddressMode::DirectPage<Operator::SBC>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       mm....mm . SBC $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_E5");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "E5: SBC dp"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp]
// Direct Page Indirect Long (2-Byte)
class SBC_E7 : public AddressMode::DirectPageIndirectLong<Operator::SBC>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     mm....mm . SBC [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_E7");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "E7: SBC [dp]"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class SBC_E9_16Bit : public AddressMode::Immediate16Bit<Operator::SBC>
{
    using Immediate16Bit::Immediate16Bit;

    // 3-m 3-m         imm       mm....mm . SBC #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_E9_16Bit");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "E9: SBC #const (16-bit)"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC #const
// Immediate (2-Byte [17])
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class SBC_E9 : public AddressMode::Immediate<Operator::SBC>
{
    using Immediate::Immediate;

    // 3-m 3-m         imm       mm....mm . SBC #$54
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_E9");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "E9: SBC #const"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr
// Absolute (3-Byte)
class SBC_ED : public AddressMode::Absolute<Operator::SBC>
{
    using Absolute::Absolute;

    // 3   5-m         abs       mm....mm . SBC $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_ED");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "ED: SBC addr"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long
// Absolute Long (4-Byte)
class SBC_EF : public AddressMode::AbsoluteLong<Operator::SBC>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      mm....mm . SBC $FEDBCA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_EF");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "EF: SBC long"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class SBC_F1 : public AddressMode::DirectPageIndirectIndexedY<Operator::SBC>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w-x+x*p (dir),Y   mm....mm . SBC ($10),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_F1");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "F1: SBC (dp),Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp)
// Direct Page Indirect (2-Byte)
class SBC_F2 : public AddressMode::DirectPageIndirect<Operator::SBC>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     mm....mm . SBC ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_F2");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "F2: SBC (dp)"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class SBC_F3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::SBC>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y mm....mm . SBC ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_F3");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "F3: SBC (sr,S),Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp,X
// Direct Page Indexed, X (2-Byte)
class SBC_F5 : public AddressMode::DirectPageIndexed<Operator::SBC, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     mm....mm . SBC $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_F5");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "F5: SBC dp,X"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class SBC_F7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::SBC>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   mm....mm . SBC [$10],Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_F7");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "F7: SBC [dp],Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,Y
// Absolute Indexed, Y (3-Byte)
class SBC_F9 : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::SBC, State::Y>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,Y     mm....mm . SBC $9876,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_F9");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "F9: SBC addr,Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,X
// Absolute Indexed, X (3-Byte)
class SBC_FD : public AddressMode::AbsoluteIndexed_ExtraCycle<Operator::SBC, State::X>
{
    using AbsoluteIndexed_ExtraCycle::AbsoluteIndexed_ExtraCycle;

    // 3   6-m-x+x*p   abs,X     mm....mm . SBC $9876,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_FD");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "FD: SBC addr,X"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long,X
// Absolute Long Indexed, X (4-Byte)
class SBC_FF : public AddressMode::AbsoluteLongIndexedX<Operator::SBC>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    mm....mm . SBC $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_FF");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "FF: SBC long,X"; }
};

// SEC Set Carry Flag [Flags affected: c]
// SEC
// Implied (1-Byte)
class SEC_38 : public AddressMode::Implied<Operator::SE<State::c, true>>
{
    using Implied::Implied;

    // 1   2           imp       .......1 . SEC
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SEC_38");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "38: SEC"; }
};

// SED Set Decimal Flag [Flags affected: d]
// SED
// Implied (1-Byte)
class SED_F8 : public AddressMode::Implied<Operator::SE<State::d, true>>
{
    using Implied::Implied;

    // 1   2           imp       ....1... . SED
    int execute() override
    {
        throw OpcodeNotYetImplementedException("SED_F8");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "F8: SED"; }
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
// SEI
// Implied (1-Byte)
class SEI_78 : public AddressMode::Implied<Operator::SE<State::i, true>>
{
    using Implied::Implied;

    // 1   2           imp       .....1.. . SEI
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "78: SEI"; }
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
// SEP #const
// Immediate (2-Byte)
class SEP_E2 : public AddressMode::Immediate<Operator::SEP>
{
    using Immediate::Immediate;

    // 2   3           imm       ******** . SEP #$12
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "E2: SEP #const"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
class STA_81 : public AddressMode::DirectPageIndexedIndirectX<Operator::STA>
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;

    // 2   7-m+w       (dir,X)   ........ . STA ($10,X)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_81");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "81: STA (dp,X)"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA sr,S
// Stack Relative (2-Byte)
class STA_83 : public AddressMode::StackRelative<Operator::STA>
{
    using StackRelative::StackRelative;

    // 2   5-m         stk,S     ........ . STA $32,S
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_83");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "83: STA sr,S"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp
// Direct Page (2-Byte)
class STA_85 : public AddressMode::DirectPage<Operator::STA>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       ........ . STA $10
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "85: STA dp"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp]
// Direct Page Indirect Long (2-Byte)
class STA_87 : public AddressMode::DirectPageIndirectLong<Operator::STA>
{
    using DirectPageIndirectLong::DirectPageIndirectLong;

    // 2   7-m+w       [dir]     ........ . STA [$10]
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_87");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "87: STA [dp]"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr
// Absolute (3-Byte)
class STA_8D : public AddressMode::Absolute<Operator::STA>
{
    using Absolute::Absolute;

    // 3   5-m         abs       ........ . STA $9876
    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "8D: STA addr"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long
// Absolute Long (4-Byte)
class STA_8F : public AddressMode::AbsoluteLong<Operator::STA>
{
    using AbsoluteLong::AbsoluteLong;

    // 4   6-m         long      ........ . STA $FEDBCA
    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "8F: STA long"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
class STA_91 : public AddressMode::DirectPageIndirectIndexedY<Operator::STA>
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;

    // 2   7-m+w       (dir),Y   ........ . STA ($10),Y
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_91");
        throw OpcodeNotYetImplementedException("TODO20");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "91: STA (dp),Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp)
// Direct Page Indirect (2-Byte)
class STA_92 : public AddressMode::DirectPageIndirect<Operator::STA>
{
    using DirectPageIndirect::DirectPageIndirect;

    // 2   6-m+w       (dir)     ........ . STA ($10)
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_92");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "92: STA (dp)"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
class STA_93 : public AddressMode::StackRelativeIndirectIndexedY<Operator::STA>
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;

    // 2   8-m         (stk,S),Y ........ . STA ($32,S),Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_93");
        return 7 + applyOperand();
    }

    std::string opcodeToString() const override { return "93: STA (sr,S),Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp,X
// Direct Page Indexed, X (2-Byte)
class STA_95 : public AddressMode::DirectPageIndexed<Operator::STA, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     ........ . STA $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_95");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "95: STA dp,X"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
class STA_97 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::STA>
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;

    // 2   7-m+w       [dir],Y   ........ . STA [$10],Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_97");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "97: STA [dp],Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,Y
// Absolute Indexed, Y (3-Byte)
class STA_99 : public AddressMode::AbsoluteIndexed<Operator::STA, State::Y>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   6-m         abs,Y     ........ . STA $9876,Y
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_99");
        throw OpcodeNotYetImplementedException("TODO20");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "99: STA addr,Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,X
// Absolute Indexed, X (3-Byte)
class STA_9D : public AddressMode::AbsoluteIndexed<Operator::STA, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   6-m         abs,X     ........ . STA $9876,X
    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "9D: STA addr,X"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long,X
// Absolute Long Indexed, X (4-Byte)
class STA_9F : public AddressMode::AbsoluteLongIndexedX<Operator::STA>
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;

    // 4   6-m         long,X    ........ . STA $FEDCBA,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STA_9F");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "9F: STA long,X"; }
};

// STP Stop Processor [Flags affected: none]
// STP
// Implied (1-Byte)
class STP_DB : public AddressMode::Implied<Operator::STP>
{
    using Implied::Implied;

    // 1   3           imp       ........ . STP
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STP_DB");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "DB: STP"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp
// Direct Page (2-Byte)
class STX_86 : public AddressMode::DirectPage<Operator::ST<State::X>>
{
    using DirectPage::DirectPage;

    // 2   4-x+w       dir       ........ . STX $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STX_86");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "86: STX dp"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX addr
// Absolute (3-Byte)
class STX_8E : public AddressMode::Absolute<Operator::ST<State::X>>
{
    using Absolute::Absolute;

    // 3   5-x         abs       ........ . STX $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STX_8E");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "8E: STX addr"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp,Y
// Direct Page Indexed, Y (2-Byte)
class STX_96 : public AddressMode::DirectPageIndexed<Operator::ST<State::X>, State::Y>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-x+w       dir,Y     ........ . STX $10,Y
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STX_96");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "96: STX dp,Y"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp
// Direct Page (2-Byte)
class STY_84 : public AddressMode::DirectPage<Operator::ST<State::Y>>
{
    using DirectPage::DirectPage;

    // 2   4-x+w       dir       ........ . STY $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STY_84");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "84: STY dp"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY addr
// Absolute (3-Byte)
class STY_8C : public AddressMode::Absolute<Operator::ST<State::Y>>
{
    using Absolute::Absolute;

    // 3   5-x         abs       ........ . STY $9876
    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "8C: STY addr"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp,X
// Direct Page Indexed, X (2-Byte)
class STY_94 : public AddressMode::DirectPageIndexed<Operator::ST<State::Y>, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-x+w       dir,X     ........ . STY $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STY_94");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "94: STY dp,X"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp
// Direct Page (2-Byte)
class STZ_64 : public AddressMode::DirectPage<Operator::STZ>
{
    using DirectPage::DirectPage;

    // 2   4-m+w       dir       ........ . STZ $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STZ_64");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "64: STZ dp"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp,X
// Direct Page Indexed, X (2-Byte)
class STZ_74 : public AddressMode::DirectPageIndexed<Operator::STZ, State::X>
{
    using DirectPageIndexed::DirectPageIndexed;

    // 2   5-m+w       dir,X     ........ . STZ $10,X
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STZ_74");
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "74: STZ dp,X"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr
// Absolute (3-Byte)
class STZ_9C : public AddressMode::Absolute<Operator::STZ>
{
    using Absolute::Absolute;

    // 3   5-m         abs       ........ . STZ $9876
    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "9C: STZ addr"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr,X
// Absolute Indexed, X (3-Byte)
class STZ_9E : public AddressMode::AbsoluteIndexed<Operator::STZ, State::X>
{
    using AbsoluteIndexed::AbsoluteIndexed;

    // 3   6-m         abs,X     ........ . STZ $9876,X
    // §20: TODO manually add exception for 3
    int execute() override
    {
        throw OpcodeNotYetImplementedException("STZ_9E");
        throw OpcodeNotYetImplementedException("TODO20");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "9E: STZ addr,X"; }
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
// TAX
// Implied (1-Byte)
class TAX_AA : public AddressMode::Implied<Operator::TA<State::X>>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . TAX
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "AA: TAX"; }
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
// TAY
// Implied (1-Byte)
class TAY_A8 : public AddressMode::Implied<Operator::TA<State::Y>>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . TAY
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TAY_A8");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A8: TAY"; }
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
// TCD
// Implied (1-Byte)
class TCD_5B : public AddressMode::Implied<Operator::TCD>
{
    using Implied::Implied;

    // 1   2           imp       *.....*. . TCD
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "5B: TCD"; }
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
// TCS
// Implied (1-Byte)
class TCS_1B : public AddressMode::Implied<Operator::TCS>
{
    using Implied::Implied;

    // 1   2           imp       ........ . TCS
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "1B: TCS"; }
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
// TDC
// Implied (1-Byte)
class TDC_7B : public AddressMode::Implied<Operator::TDC>
{
    using Implied::Implied;

    // 1   2           imp       *.....*. . TDC
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TDC_7B");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "7B: TDC"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB dp
// Direct Page (2-Byte)
class TRB_14 : public AddressMode::DirectPage<Operator::TRB>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       ......m. . TRB $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TRB_14");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "14: TRB dp"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB addr
// Absolute (3-Byte)
class TRB_1C : public AddressMode::Absolute<Operator::TRB>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       ......m. . TRB $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TRB_1C");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "1C: TRB addr"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB dp
// Direct Page (2-Byte)
class TSB_04 : public AddressMode::DirectPage<Operator::TSB>
{
    using DirectPage::DirectPage;

    // 2   7-2*m+w     dir       ......m. . TSB $10
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TSB_04");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "04: TSB dp"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB addr
// Absolute (3-Byte)
class TSB_0C : public AddressMode::Absolute<Operator::TSB>
{
    using Absolute::Absolute;

    // 3   8-2*m       abs       ......m. . TSB $9876
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TSB_0C");
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "0C: TSB addr"; }
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
// TSC
// Implied (1-Byte)
class TSC_3B : public AddressMode::Implied<Operator::TSC>
{
    using Implied::Implied;

    // 1   2           imp       *.....*. . TSC
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TSC_3B");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "3B: TSC"; }
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
// TSX
// Implied (1-Byte)
class TSX_BA : public AddressMode::Implied<Operator::TSX>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . TSX
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TSX_BA");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "BA: TSX"; }
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
// TXA
// Implied (1-Byte)
class TXA_8A : public AddressMode::Implied<Operator::TXA>
{
    using Implied::Implied;

    // 1   2           imp       m.....m. . TXA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TXA_8A");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "8A: TXA"; }
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
// TXS
// Implied (1-Byte)
class TXS_9A : public AddressMode::Implied<Operator::TXS>
{
    using Implied::Implied;

    // 1   2           imp       ........ . TXS
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TXS_9A");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "9A: TXS"; }
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
// TXY
// Implied (1-Byte)
class TXY_9B : public AddressMode::Implied<Operator::TXY>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . TXY
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TXY_9B");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "9B: TXY"; }
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
// TYA
// Implied (1-Byte)
class TYA_98 : public AddressMode::Implied<Operator::TYA>
{
    using Implied::Implied;

    // 1   2           imp       m.....m. . TYA
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TYA_98");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "98: TYA"; }
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
// TYX
// Implied (1-Byte)
class TYX_BB : public AddressMode::Implied<Operator::TYX>
{
    using Implied::Implied;

    // 1   2           imp       x.....x. . TYX
    int execute() override
    {
        throw OpcodeNotYetImplementedException("TYX_BB");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "BB: TYX"; }
};

// WAI Wait for Interrupt [Flags affected: none]
// WAI
// Implied (1-Byte)
class WAI_CB : public AddressMode::Implied<Operator::WAI>
{
    using Implied::Implied;

    // 1   3           imp       ........ . WAI
    int execute() override
    {
        throw OpcodeNotYetImplementedException("WAI_CB");
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "CB: WAI"; }
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
// WDM
// Immediate (2-Byte)
class WDM_42 : public AddressMode::Immediate<Operator::WDM>
{
    using Immediate::Immediate;

    // 2   2           imm       ........ . WDM
    int execute() override
    {
        throw OpcodeNotYetImplementedException("WDM_42");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "42: WDM"; }
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
// XBA
// Implied (1-Byte)
class XBA_EB : public AddressMode::Implied<Operator::XBA>
{
    using Implied::Implied;

    // 1   3           imp       *.....*. . XBA
    int execute() override
    {
        return 3 + applyOperand();
    }

    std::string opcodeToString() const override { return "EB: XBA"; }
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
// XCE
// Implied (1-Byte)
class XCE_FB : public AddressMode::Implied<Operator::XCE>
{
    using Implied::Implied;

    // 1   2           imp       .......* * XCE
    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "FB: XCE"; }
};

}

}
