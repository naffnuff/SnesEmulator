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
// 2<>
class ADC_61 : public AddressMode::DirectPageIndexedIndirectX<Operator::ADC>
{
    // 2   7-m+w       (dir,X)   mm....mm . ADC ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_61 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "61: ADC (dp,X)"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC sr,S
// Stack Relative
// 2<>
class ADC_63 : public AddressMode::StackRelative<Operator::ADC>
{
    // 2   5-m         stk,S     mm....mm . ADC $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_63 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "63: ADC sr,S"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp
// Direct Page
// 2<>
class ADC_65 : public AddressMode::DirectPage<Operator::ADC>
{
    // 2   4-m+w       dir       mm....mm . ADC $10
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_65 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "65: ADC dp"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp]
// Direct Page Indirect Long
// 2<>
class ADC_67 : public AddressMode::DirectPageIndirectLong<Operator::ADC>
{
    // 2   7-m+w       [dir]     mm....mm . ADC [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_67 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "67: ADC [dp]"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class ADC_69 : public AddressMode::ImmediateVariableSize<Operator::ADC, State::m>
{
    // 3-m 3-m         imm       mm....mm . ADC #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_69 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "69: ADC #const"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr
// Absolute
// 3<>
class ADC_6D : public AddressMode::Absolute<Operator::ADC>
{
    // 3   5-m         abs       mm....mm . ADC $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_6D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6D: ADC addr"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long
// Absolute Long
// 4<>
class ADC_6F : public AddressMode::AbsoluteLong<Operator::ADC>
{
    // 4   6-m         long      mm....mm . ADC $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_6F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6F: ADC long"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class ADC_71 : public AddressMode::DirectPageIndirectIndexedY<Operator::ADC>
{
    // 2   7-m+w-x+x*p (dir),Y   mm....mm . ADC ($10),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_71 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "71: ADC (dp),Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp)
// Direct Page Indirect
// 2<>
class ADC_72 : public AddressMode::DirectPageIndirect<Operator::ADC>
{
    // 2   6-m+w       (dir)     mm....mm . ADC ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_72 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "72: ADC (dp)"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class ADC_73 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ADC>
{
    // 2   8-m         (stk,S),Y mm....mm . ADC ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_73 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "73: ADC (sr,S),Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp,X
// Direct Page Indexed, X
// 2<>
class ADC_75 : public AddressMode::DirectPageIndexedX<Operator::ADC>
{
    // 2   5-m+w       dir,X     mm....mm . ADC $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_75 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "75: ADC dp,X"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class ADC_77 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ADC>
{
    // 2   7-m+w       [dir],Y   mm....mm . ADC [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_77 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "77: ADC [dp],Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,Y
// Absolute Indexed, Y
// 3<>
class ADC_79 : public AddressMode::AbsoluteIndexedY<Operator::ADC>
{
    // 3   6-m-x+x*p   abs,Y     mm....mm . ADC $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_79 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "79: ADC addr,Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,X
// Absolute Indexed, X
// 3<>
class ADC_7D : public AddressMode::AbsoluteIndexedX<Operator::ADC>
{
    // 3   6-m-x+x*p   abs,X     mm....mm . ADC $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_7D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7D: ADC addr,X"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long,X
// Absolute Long Indexed, X
// 4<>
class ADC_7F : public AddressMode::AbsoluteLongIndexedX<Operator::ADC>
{
    // 4   6-m         long,X    mm....mm . ADC $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ADC_7F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7F: ADC long,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
class AND_21 : public AddressMode::DirectPageIndexedIndirectX<Operator::AND>
{
    // 2   7-m+w       (dir,X)   m.....m. . AND ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_21 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "21: AND (dp,X)"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND sr,S
// Stack Relative
// 2<>
class AND_23 : public AddressMode::StackRelative<Operator::AND>
{
    // 2   5-m         stk,S     m.....m. . AND $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_23 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "23: AND sr,S"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp
// Direct Page
// 2<>
class AND_25 : public AddressMode::DirectPage<Operator::AND>
{
    // 2   4-m+w       dir       m.....m. . AND $10
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_25 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "25: AND dp"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp]
// Direct Page Indirect Long
// 2<>
class AND_27 : public AddressMode::DirectPageIndirectLong<Operator::AND>
{
    // 2   7-m+w       [dir]     m.....m. . AND [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_27 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "27: AND [dp]"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class AND_29 : public AddressMode::ImmediateVariableSize<Operator::AND, State::m>
{
    // 3-m 3-m         imm       m.....m. . AND #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_29 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "29: AND #const"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr
// Absolute
// 3<>
class AND_2D : public AddressMode::Absolute<Operator::AND>
{
    // 3   5-m         abs       m.....m. . AND $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_2D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2D: AND addr"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long
// Absolute Long
// 4<>
class AND_2F : public AddressMode::AbsoluteLong<Operator::AND>
{
    // 4   6-m         long      m.....m. . AND $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_2F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2F: AND long"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class AND_31 : public AddressMode::DirectPageIndirectIndexedY<Operator::AND>
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . AND ($10),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_31 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "31: AND (dp),Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp)
// Direct Page Indirect
// 2<>
class AND_32 : public AddressMode::DirectPageIndirect<Operator::AND>
{
    // 2   6-m+w       (dir)     m.....m. . AND ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_32 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "32: AND (dp)"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class AND_33 : public AddressMode::StackRelativeIndirectIndexedY<Operator::AND>
{
    // 2   8-m         (stk,S),Y m.....m. . AND ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_33 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "33: AND (sr,S),Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp,X
// Direct Page Indexed, X
// 2<>
class AND_35 : public AddressMode::DirectPageIndexedX<Operator::AND>
{
    // 2   5-m+w       dir,X     m.....m. . AND $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_35 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "35: AND dp,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class AND_37 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::AND>
{
    // 2   7-m+w       [dir],Y   m.....m. . AND [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_37 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "37: AND [dp],Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,Y
// Absolute Indexed, Y
// 3<>
class AND_39 : public AddressMode::AbsoluteIndexedY<Operator::AND>
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . AND $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_39 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "39: AND addr,Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,X
// Absolute Indexed, X
// 3<>
class AND_3D : public AddressMode::AbsoluteIndexedX<Operator::AND>
{
    // 3   6-m-x+x*p   abs,X     m.....m. . AND $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_3D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3D: AND addr,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long,X
// Absolute Long Indexed, X
// 4<>
class AND_3F : public AddressMode::AbsoluteLongIndexedX<Operator::AND>
{
    // 4   6-m         long,X    m.....m. . AND $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("AND_3F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3F: AND long,X"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp
// Direct Page
// 2<>
class ASL_06 : public AddressMode::DirectPage<Operator::ASL>
{
    // 2   7-2*m+w     dir       m.....mm . ASL $10
    int execute(State& state) const override
    {
        throw std::runtime_error("ASL_06 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "06: ASL dp"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL A
// Accumulator
// 1<>
class ASL_0A : public AddressMode::Accumulator<Operator::ASL>
{
    // 1   2           acc       m.....mm . ASL
    int execute(State& state) const override
    {
        throw std::runtime_error("ASL_0A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0A: ASL A"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr
// Absolute
// 3<>
class ASL_0E : public AddressMode::Absolute<Operator::ASL>
{
    // 3   8-2*m       abs       m.....mm . ASL $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("ASL_0E is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0E: ASL addr"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp,X
// Direct Page Indexed, X
// 2<>
class ASL_16 : public AddressMode::DirectPageIndexedX<Operator::ASL>
{
    // 2   8-2*m+w     dir,X     m.....mm . ASL $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ASL_16 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "16: ASL dp,X"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr,X
// Absolute Indexed, X
// 3<>
class ASL_1E : public AddressMode::AbsoluteIndexedX<Operator::ASL>
{
    // 3   9-2*m       abs,X     m.....mm . ASL $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("ASL_1E is not implemented");
        throw std::runtime_error("TODO20");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1E: ASL addr,X"; }
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
// BCC nearlabel
// Program Counter Relative
// 2<>
class BCC_90 : public AddressMode::ProgramCounterRelative<Operator::BCC>
{
    // 2   2+t+t*e*p   rel8      ........ . BCC LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BCC_90 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "90: BCC nearlabel"; }
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
// BCS nearlabel
// Program Counter Relative
// 2<>
class BCS_B0 : public AddressMode::ProgramCounterRelative<Operator::BCS>
{
    // 2   2+t+t*e*p   rel8      ........ . BCS LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BCS_B0 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B0: BCS nearlabel"; }
};

// BEQ Branch if Equal [Flags affected: none]
// BEQ nearlabel
// Program Counter Relative
// 2<>
class BEQ_F0 : public AddressMode::ProgramCounterRelative<Operator::BEQ>
{
    // 2   2+t+t*e*p   rel8      ........ . BEQ LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BEQ_F0 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F0: BEQ nearlabel"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp
// Direct Page
// 2<>
class BIT_24 : public AddressMode::DirectPage<Operator::BIT>
{
    // 2   4-m+w       dir       mm....m. . BIT $10
    int execute(State& state) const override
    {
        throw std::runtime_error("BIT_24 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "24: BIT dp"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr
// Absolute
// 3<>
class BIT_2C : public AddressMode::Absolute<Operator::BIT>
{
    // 3   5-m         abs       mm....m. . BIT $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("BIT_2C is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2C: BIT addr"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp,X
// Direct Page Indexed, X
// 2<>
class BIT_34 : public AddressMode::DirectPageIndexedX<Operator::BIT>
{
    // 2   5-m+w       dir,X     mm....m. . BIT $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("BIT_34 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "34: BIT dp,X"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr,X
// Absolute Indexed, X
// 3<>
class BIT_3C : public AddressMode::AbsoluteIndexedX<Operator::BIT>
{
    // 3   6-m-x+x*p   abs,X     mm....m. . BIT $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("BIT_3C is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3C: BIT addr,X"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class BIT_89 : public AddressMode::ImmediateVariableSize<Operator::BIT, State::m>
{
    // 3-m 3-m         imm       ......m. . BIT #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("BIT_89 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "89: BIT #const"; }
};

// BMI Branch if Minus [Flags affected: none]
// BMI nearlabel
// Program Counter Relative
// 2<>
class BMI_30 : public AddressMode::ProgramCounterRelative<Operator::BMI>
{
    // 2   2+t+t*e*p   rel8      ........ . BMI LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BMI_30 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "30: BMI nearlabel"; }
};

// BNE Branch if Not Equal [Flags affected: none]
// BNE nearlabel
// Program Counter Relative
// 2<>
class BNE_D0 : public AddressMode::ProgramCounterRelative<Operator::BNE>
{
    // 2   2+t+t*e*p   rel8      ........ . BNE LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BNE_D0 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D0: BNE nearlabel"; }
};

// BPL Branch if Plus [Flags affected: none]
// BPL nearlabel
// Program Counter Relative
// 2<>
class BPL_10 : public AddressMode::ProgramCounterRelative<Operator::BPL>
{
    // 2   2+t+t*e*p   rel8      ........ . BPL LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BPL_10 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "10: BPL nearlabel"; }
};

// BRA Branch Always [Flags affected: none]
// BRA nearlabel
// Program Counter Relative
// 2<>
class BRA_80 : public AddressMode::ProgramCounterRelative<Operator::BRA>
{
    // 2   3+e*p       rel8      ........ . BRA LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BRA_80 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "80: BRA nearlabel"; }
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
// BRK
// Immediate
// 2<18>
// ¤18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class BRK_00 : public AddressMode::Immediate<Operator::BRK>
{
    // 1   8-e         imp       ....01.. . BRK
    int execute(State& state) const override
    {
        throw std::runtime_error("BRK_00 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "00: BRK"; }
};

// BRL Branch Long Always [Flags affected: none]
// BRL label
// Program Counter Relative Long
// 3<>
class BRL_82 : public AddressMode::ProgramCounterRelativeLong<Operator::BRL>
{
    // 3   4           rel16     ........ . BRL LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BRL_82 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "82: BRL label"; }
};

// BVC Branch if Overflow Clear [Flags affected: none]
// BVC nearlabel
// Program Counter Relative
// 2<>
class BVC_50 : public AddressMode::ProgramCounterRelative<Operator::BVC>
{
    // 2   2+t+t*e*p   rel8      ........ . BVC LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BVC_50 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "50: BVC nearlabel"; }
};

// BVS Branch if Overflow Set [Flags affected: none]
// BVS nearlabel
// Program Counter Relative
// 2<>
class BVS_70 : public AddressMode::ProgramCounterRelative<Operator::BVS>
{
    // 2   2+t+t*e*p   rel8      ........ . BVS LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("BVS_70 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "70: BVS nearlabel"; }
};

// CLC Clear Carry [Flags affected: c]
// CLC
// Implied
// 1<>
class CLC_18 : public AddressMode::Implied<Operator::CLC>
{
    // 1   2           imp       .......0 . CLC
    int execute(State& state) const override
    {
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "18: CLC"; }
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
// CLD
// Implied
// 1<>
class CLD_D8 : public AddressMode::Implied<Operator::CLD>
{
    // 1   2           imp       ....0... . CLD
    int execute(State& state) const override
    {
        throw std::runtime_error("CLD_D8 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D8: CLD"; }
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
// CLI
// Implied
// 1<>
class CLI_58 : public AddressMode::Implied<Operator::CLI>
{
    // 1   2           imp       .....0.. . CLI
    int execute(State& state) const override
    {
        throw std::runtime_error("CLI_58 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "58: CLI"; }
};

// CLV Clear Overflow Flag [Flags affected: v]
// CLV
// Implied
// 1<>
class CLV_B8 : public AddressMode::Implied<Operator::CLV>
{
    // 1   2           imp       .0...... . CLV
    int execute(State& state) const override
    {
        throw std::runtime_error("CLV_B8 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B8: CLV"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp,X)
// Direct Page Indexed Indirect,X
// 2<>
class CMP_C1 : public AddressMode::DirectPageIndexedIndirectX<Operator::CMP>
{
    // 2   7-m+w       (dir,X)   m.....mm . CMP ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_C1 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C1: CMP (dp,X)"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP sr,S
// Stack Relative
// 2<>
class CMP_C3 : public AddressMode::StackRelative<Operator::CMP>
{
    // 2   5-m         stk,S     m.....mm . CMP $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_C3 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C3: CMP sr,S"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp
// Direct Page
// 2<>
class CMP_C5 : public AddressMode::DirectPage<Operator::CMP>
{
    // 2   4-m+w       dir       m.....mm . CMP $10
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_C5 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C5: CMP dp"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp]
// Direct Page Indirect Long
// 2<>
class CMP_C7 : public AddressMode::DirectPageIndirectLong<Operator::CMP>
{
    // 2   7-m+w       [dir]     m.....mm . CMP [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_C7 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C7: CMP [dp]"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class CMP_C9 : public AddressMode::ImmediateVariableSize<Operator::CMP, State::m>
{
    // 3-m 3-m         imm       m.....mm . CMP #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_C9 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C9: CMP #const"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr
// Absolute
// 3<>
class CMP_CD : public AddressMode::Absolute<Operator::CMP>
{
    // 3   5-m         abs       m.....mm . CMP $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_CD is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CD: CMP addr"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long
// Absolute Long
// 4<>
class CMP_CF : public AddressMode::AbsoluteLong<Operator::CMP>
{
    // 4   6-m         long      m.....mm . CMP $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_CF is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CF: CMP long"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class CMP_D1 : public AddressMode::DirectPageIndirectIndexedY<Operator::CMP>
{
    // 2   7-m+w-x+x*p (dir),Y   m.....mm . CMP ($10),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_D1 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D1: CMP (dp),Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp)
// Direct Page Indirect
// 2<>
class CMP_D2 : public AddressMode::DirectPageIndirect<Operator::CMP>
{
    // 2   6-m+w       (dir)     m.....mm . CMP ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_D2 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D2: CMP (dp)"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class CMP_D3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::CMP>
{
    // 2   8-m         (stk,S),Y m.....mm . CMP ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_D3 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D3: CMP (sr,S),Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp,X
// Direct Page Indexed, X
// 2<>
class CMP_D5 : public AddressMode::DirectPageIndexedX<Operator::CMP>
{
    // 2   5-m+w       dir,X     m.....mm . CMP $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_D5 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D5: CMP dp,X"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class CMP_D7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::CMP>
{
    // 2   7-m+w       [dir],Y   m.....mm . CMP [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_D7 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D7: CMP [dp],Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,Y
// Absolute Indexed, Y
// 3<>
class CMP_D9 : public AddressMode::AbsoluteIndexedY<Operator::CMP>
{
    // 3   6-m-x+x*p   abs,Y     m.....mm . CMP $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_D9 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D9: CMP addr,Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,X
// Absolute Indexed, X
// 3<>
class CMP_DD : public AddressMode::AbsoluteIndexedX<Operator::CMP>
{
    // 3   6-m-x+x*p   abs,X     m.....mm . CMP $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_DD is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DD: CMP addr,X"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long,X
// Absolute Long Indexed, X
// 4<>
class CMP_DF : public AddressMode::AbsoluteLongIndexedX<Operator::CMP>
{
    // 4   6-m         long,X    m.....mm . CMP $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("CMP_DF is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DF: CMP long,X"; }
};

// COP Co-Processor Enable [Flags affected: d,i]
// COP const
// Immediate
// 2<18>
// ¤18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class COP_02 : public AddressMode::Immediate<Operator::COP>
{
    // 2   8-e         imm       ....01.. . COP #$12
    int execute(State& state) const override
    {
        throw std::runtime_error("COP_02 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "02: COP const"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX #const
// Immediate
// 2<19>
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class CPX_E0 : public AddressMode::ImmediateVariableSize<Operator::CPX, State::x>
{
    // 3-x 3-x         imm       x.....xx . CPX #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("CPX_E0 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E0: CPX #const"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX dp
// Direct Page
// 2<>
class CPX_E4 : public AddressMode::DirectPage<Operator::CPX>
{
    // 2   4-x+w       dir       x.....xx . CPX $10
    int execute(State& state) const override
    {
        throw std::runtime_error("CPX_E4 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E4: CPX dp"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX addr
// Absolute
// 3<>
class CPX_EC : public AddressMode::Absolute<Operator::CPX>
{
    // 3   5-x         abs       x.....xx . CPX $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("CPX_EC is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EC: CPX addr"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY #const
// Immediate
// 2<19>
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class CPY_C0 : public AddressMode::ImmediateVariableSize<Operator::CPY, State::x>
{
    // 3-x 3-x         imm       x.....xx . CPY #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("CPY_C0 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C0: CPY #const"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY dp
// Direct Page
// 2<>
class CPY_C4 : public AddressMode::DirectPage<Operator::CPY>
{
    // 2   4-x+w       dir       x.....xx . CPY $10
    int execute(State& state) const override
    {
        throw std::runtime_error("CPY_C4 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C4: CPY dp"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY addr
// Absolute
// 3<>
class CPY_CC : public AddressMode::Absolute<Operator::CPY>
{
    // 3   5-x         abs       x.....xx . CPY $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("CPY_CC is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CC: CPY addr"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC A
// Accumulator
// 1<>
class DEC_3A : public AddressMode::Accumulator<Operator::DEC>
{
    // 1   2           acc       m.....m. . DEC
    int execute(State& state) const override
    {
        throw std::runtime_error("DEC_3A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3A: DEC A"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC dp
// Direct Page
// 2<>
class DEC_C6 : public AddressMode::DirectPage<Operator::DEC>
{
    // 2   7-2*m+w     dir       m.....m. . DEC $10
    int execute(State& state) const override
    {
        throw std::runtime_error("DEC_C6 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C6: DEC dp"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC addr
// Absolute
// 3<>
class DEC_CE : public AddressMode::Absolute<Operator::DEC>
{
    // 3   8-2*m       abs       m.....m. . DEC $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("DEC_CE is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CE: DEC addr"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC dp,X
// Direct Page Indexed, X
// 2<>
class DEC_D6 : public AddressMode::DirectPageIndexedX<Operator::DEC>
{
    // 2   8-2*m+w     dir,X     m.....m. . DEC $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("DEC_D6 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D6: DEC dp,X"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC addr,X
// Absolute Indexed, X
// 3<>
class DEC_DE : public AddressMode::AbsoluteIndexedX<Operator::DEC>
{
    // 3   9-2*m       abs,X     m.....m. . DEC $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("DEC_DE is not implemented");
        throw std::runtime_error("TODO20");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DE: DEC addr,X"; }
};

// DEX Decrement Index Register X [Flags affected: n,z]
// DEX
// Implied
// 1<>
class DEX_CA : public AddressMode::Implied<Operator::DEX>
{
    // 1   2           imp       x.....x. . DEX
    int execute(State& state) const override
    {
        throw std::runtime_error("DEX_CA is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CA: DEX"; }
};

// DEY Decrement Index Register Y [Flags affected: n,z]
// DEY
// Implied
// 1<>
class DEY_88 : public AddressMode::Implied<Operator::DEY>
{
    // 1   2           imp       x.....x. . DEY
    int execute(State& state) const override
    {
        throw std::runtime_error("DEY_88 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "88: DEY"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp,X)
// Direct Page Indexed Indirect,X
// 2<>
class EOR_41 : public AddressMode::DirectPageIndexedIndirectX<Operator::EOR>
{
    // 2   7-m+w       (dir,X)   m.....m. . EOR ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_41 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "41: EOR (dp,X)"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR sr,S
// Stack Relative
// 2<>
class EOR_43 : public AddressMode::StackRelative<Operator::EOR>
{
    // 2   5-m         stk,S     m.....m. . EOR $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_43 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "43: EOR sr,S"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp
// Direct Page
// 2<>
class EOR_45 : public AddressMode::DirectPage<Operator::EOR>
{
    // 2   4-m+w       dir       m.....m. . EOR $10
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_45 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "45: EOR dp"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp]
// Direct Page Indirect Long
// 2<>
class EOR_47 : public AddressMode::DirectPageIndirectLong<Operator::EOR>
{
    // 2   7-m+w       [dir]     m.....m. . EOR [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_47 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "47: EOR [dp]"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class EOR_49 : public AddressMode::ImmediateVariableSize<Operator::EOR, State::m>
{
    // 3-m 3-m         imm       m.....m. . EOR #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_49 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "49: EOR #const"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr
// Absolute
// 3<>
class EOR_4D : public AddressMode::Absolute<Operator::EOR>
{
    // 3   5-m         abs       m.....m. . EOR $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_4D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4D: EOR addr"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long
// Absolute Long
// 4<>
class EOR_4F : public AddressMode::AbsoluteLong<Operator::EOR>
{
    // 4   6-m         long      m.....m. . EOR $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_4F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4F: EOR long"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class EOR_51 : public AddressMode::DirectPageIndirectIndexedY<Operator::EOR>
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . EOR ($10),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_51 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "51: EOR (dp),Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp)
// Direct Page Indirect
// 2<>
class EOR_52 : public AddressMode::DirectPageIndirect<Operator::EOR>
{
    // 2   6-m+w       (dir)     m.....m. . EOR ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_52 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "52: EOR (dp)"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class EOR_53 : public AddressMode::StackRelativeIndirectIndexedY<Operator::EOR>
{
    // 2   8-m         (stk,S),Y m.....m. . EOR ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_53 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "53: EOR (sr,S),Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp,X
// Direct Page Indexed, X
// 2<>
class EOR_55 : public AddressMode::DirectPageIndexedX<Operator::EOR>
{
    // 2   5-m+w       dir,X     m.....m. . EOR $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_55 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "55: EOR dp,X"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class EOR_57 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::EOR>
{
    // 2   7-m+w       [dir],Y   m.....m. . EOR [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_57 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "57: EOR [dp],Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,Y
// Absolute Indexed, Y
// 3<>
class EOR_59 : public AddressMode::AbsoluteIndexedY<Operator::EOR>
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . EOR $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_59 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "59: EOR addr,Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,X
// Absolute Indexed, X
// 3<>
class EOR_5D : public AddressMode::AbsoluteIndexedX<Operator::EOR>
{
    // 3   6-m-x+x*p   abs,X     m.....m. . EOR $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_5D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5D: EOR addr,X"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long,X
// Absolute Long Indexed, X
// 4<>
class EOR_5F : public AddressMode::AbsoluteLongIndexedX<Operator::EOR>
{
    // 4   6-m         long,X    m.....m. . EOR $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("EOR_5F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5F: EOR long,X"; }
};

// INC Increment [Flags affected: n,z]
// INC A
// Accumulator
// 1<>
class INC_1A : public AddressMode::Accumulator<Operator::INC>
{
    // 1   2           acc       m.....m. . INC
    int execute(State& state) const override
    {
        throw std::runtime_error("INC_1A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1A: INC A"; }
};

// INC Increment [Flags affected: n,z]
// INC dp
// Direct Page
// 2<>
class INC_E6 : public AddressMode::DirectPage<Operator::INC>
{
    // 2   7-2*m+w     dir       m.....m. . INC $10
    int execute(State& state) const override
    {
        throw std::runtime_error("INC_E6 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E6: INC dp"; }
};

// INC Increment [Flags affected: n,z]
// INC addr
// Absolute
// 3<>
class INC_EE : public AddressMode::Absolute<Operator::INC>
{
    // 3   8-2*m       abs       m.....m. . INC $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("INC_EE is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EE: INC addr"; }
};

// INC Increment [Flags affected: n,z]
// INC dp,X
// Direct Page Indexed, X
// 2<>
class INC_F6 : public AddressMode::DirectPageIndexedX<Operator::INC>
{
    // 2   8-2*m+w     dir,X     m.....m. . INC $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("INC_F6 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F6: INC dp,X"; }
};

// INC Increment [Flags affected: n,z]
// INC addr,X
// Absolute Indexed, X
// 3<>
class INC_FE : public AddressMode::AbsoluteIndexedX<Operator::INC>
{
    // 3   9-2*m       abs,X     m.....m. . INC $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("INC_FE is not implemented");
        throw std::runtime_error("TODO20");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FE: INC addr,X"; }
};

// INX Increment Index Register X [Flags affected: n,z]
// INX
// Implied
// 1<>
class INX_E8 : public AddressMode::Implied<Operator::INX>
{
    // 1   2           imp       x.....x. . INX
    int execute(State& state) const override
    {
        throw std::runtime_error("INX_E8 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E8: INX"; }
};

// INY Increment Index Register Y [Flags affected: n,z]
// INY
// Implied
// 1<>
class INY_C8 : public AddressMode::Implied<Operator::INY>
{
    // 1   2           imp       x.....x. . INY
    int execute(State& state) const override
    {
        throw std::runtime_error("INY_C8 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C8: INY"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP addr
// Absolute
// 3<>
class JMP_4C : public AddressMode::Absolute<Operator::JMP>
{
    // 3   3           abs       ........ . JMP $1234
    int execute(State& state) const override
    {
        throw std::runtime_error("JMP_4C is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4C: JMP addr"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP long
// Absolute Long
// 4<>
class JMP_5C : public AddressMode::AbsoluteLong<Operator::JMP>
{
    // 4   4           long      ........ . JMP $FEDCBA
    int execute(State& state) const override
    {
        throw std::runtime_error("JMP_5C is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5C: JMP long"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr)
// Absolute Indirect
// 3<>
class JMP_6C : public AddressMode::AbsoluteIndirect<Operator::JMP>
{
    // 3   5           (abs)     ........ . JMP ($1234)
    int execute(State& state) const override
    {
        throw std::runtime_error("JMP_6C is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6C: JMP (addr)"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr,X)
// Absolute Indexed Indirect
// 3<>
class JMP_7C : public AddressMode::AbsoluteIndexedIndirect<Operator::JMP>
{
    // 3   6           (abs,X)   ........ . JMP ($1234,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("JMP_7C is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7C: JMP (addr,X)"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP [addr]
// Absolute Indirect Long
// 3<>
class JMP_DC : public AddressMode::AbsoluteIndirectLong<Operator::JMP>
{
    // 3   6           [abs]     ........ . JMP [$1234]
    int execute(State& state) const override
    {
        throw std::runtime_error("JMP_DC is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DC: JMP [addr]"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR addr
// Absolute
// 3<>
class JSR_20 : public AddressMode::Absolute<Operator::JSR>
{
    // 3   6           abs       ........ . JSR $1234
    int execute(State& state) const override
    {
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "20: JSR addr"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR long
// Absolute Long
// 4<>
class JSR_22 : public AddressMode::AbsoluteLong<Operator::JSR>
{
    // 4   8           long      ........ . JSL $123456
    int execute(State& state) const override
    {
        throw std::runtime_error("JSR_22 is not implemented");
        return 8 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "22: JSR long"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR (addr,X)
// Absolute Indexed Indirect
// 3<>
class JSR_FC : public AddressMode::AbsoluteIndexedIndirect<Operator::JSR>
{
    // 3   8           (abs,X)   ........ . JSR ($1234,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("JSR_FC is not implemented");
        return 8 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FC: JSR (addr,X)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
class LDA_A1 : public AddressMode::DirectPageIndexedIndirectX<Operator::LDA>
{
    // 2   7-m+w       (dir,X)   m.....m. . LDA ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_A1 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A1: LDA (dp,X)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA sr,S
// Stack Relative
// 2<>
class LDA_A3 : public AddressMode::StackRelative<Operator::LDA>
{
    // 2   5-m         stk,S     m.....m. . LDA $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_A3 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A3: LDA sr,S"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp
// Direct Page
// 2<>
class LDA_A5 : public AddressMode::DirectPage<Operator::LDA>
{
    // 2   4-m+w       dir       m.....m. . LDA $10
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_A5 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A5: LDA dp"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp]
// Direct Page Indirect Long
// 2<>
class LDA_A7 : public AddressMode::DirectPageIndirectLong<Operator::LDA>
{
    // 2   7-m+w       [dir]     m.....m. . LDA [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_A7 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A7: LDA [dp]"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class LDA_A9 : public AddressMode::ImmediateVariableSize<Operator::LDA, State::m>
{
    // 3-m 3-m         imm       m.....m. . LDA #$54
    int execute(State& state) const override
    {
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A9: LDA #const"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr
// Absolute
// 3<>
class LDA_AD : public AddressMode::Absolute<Operator::LDA>
{
    // 3   5-m         abs       m.....m. . LDA $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_AD is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AD: LDA addr"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long
// Absolute Long
// 4<>
class LDA_AF : public AddressMode::AbsoluteLong<Operator::LDA>
{
    // 4   6-m         long      m.....m. . LDA $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_AF is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AF: LDA long"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class LDA_B1 : public AddressMode::DirectPageIndirectIndexedY<Operator::LDA>
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . LDA ($10),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_B1 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B1: LDA (dp),Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp)
// Direct Page Indirect
// 2<>
class LDA_B2 : public AddressMode::DirectPageIndirect<Operator::LDA>
{
    // 2   6-m+w       (dir)     m.....m. . LDA ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_B2 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B2: LDA (dp)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class LDA_B3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::LDA>
{
    // 2   8-m         (stk,S),Y m.....m. . LDA ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_B3 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B3: LDA (sr,S),Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp,X
// Direct Page Indexed, X
// 2<>
class LDA_B5 : public AddressMode::DirectPageIndexedX<Operator::LDA>
{
    // 2   5-m+w       dir,X     m.....m. . LDA $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_B5 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B5: LDA dp,X"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class LDA_B7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::LDA>
{
    // 2   7-m+w       [dir],Y   m.....m. . LDA [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_B7 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B7: LDA [dp],Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,Y
// Absolute Indexed, Y
// 3<>
class LDA_B9 : public AddressMode::AbsoluteIndexedY<Operator::LDA>
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . LDA $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_B9 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B9: LDA addr,Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,X
// Absolute Indexed, X
// 3<>
class LDA_BD : public AddressMode::AbsoluteIndexedX<Operator::LDA>
{
    // 3   6-m-x+x*p   abs,X     m.....m. . LDA $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_BD is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BD: LDA addr,X"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long,X
// Absolute Long Indexed, X
// 4<>
class LDA_BF : public AddressMode::AbsoluteLongIndexedX<Operator::LDA>
{
    // 4   6-m         long,X    m.....m. . LDA $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("LDA_BF is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BF: LDA long,X"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX #const
// Immediate
// 2<19>
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class LDX_A2 : public AddressMode::ImmediateVariableSize<Operator::LDX, State::x>
{
    // 3-x 3-x         imm       x.....x. . LDX #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("LDX_A2 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A2: LDX #const"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp
// Direct Page
// 2<>
class LDX_A6 : public AddressMode::DirectPage<Operator::LDX>
{
    // 2   4-x+w       dir       x.....x. . LDX $10
    int execute(State& state) const override
    {
        throw std::runtime_error("LDX_A6 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A6: LDX dp"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr
// Absolute
// 3<>
class LDX_AE : public AddressMode::Absolute<Operator::LDX>
{
    // 3   5-x         abs       x.....x. . LDX $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("LDX_AE is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AE: LDX addr"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp,Y
// Direct Page Indexed, Y
// 2<>
class LDX_B6 : public AddressMode::DirectPageIndexedY<Operator::LDX>
{
    // 2   5-x+w       dir,Y     x.....x. . LDX $10,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("LDX_B6 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B6: LDX dp,Y"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr,Y
// Absolute Indexed, Y
// 3<>
class LDX_BE : public AddressMode::AbsoluteIndexedY<Operator::LDX>
{
    // 3   6-2*x+x*p   abs,Y     x.....x. . LDX $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("LDX_BE is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BE: LDX addr,Y"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY #const
// Immediate
// 2<19>
// ¤19: Add 1 byte if x=0 (16-bit index registers)
class LDY_A0 : public AddressMode::ImmediateVariableSize<Operator::LDY, State::x>
{
    // 3-x 3-x         imm       x.....x. . LDY #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("LDY_A0 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A0: LDY #const"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp
// Direct Page
// 2<>
class LDY_A4 : public AddressMode::DirectPage<Operator::LDY>
{
    // 2   4-x+w       dir       x.....x. . LDY $10
    int execute(State& state) const override
    {
        throw std::runtime_error("LDY_A4 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A4: LDY dp"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr
// Absolute
// 3<>
class LDY_AC : public AddressMode::Absolute<Operator::LDY>
{
    // 3   5-x         abs       x.....x. . LDY $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("LDY_AC is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AC: LDY addr"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp,X
// Direct Page Indexed, X
// 2<>
class LDY_B4 : public AddressMode::DirectPageIndexedX<Operator::LDY>
{
    // 2   5-x+w       dir,X     x.....x. . LDY $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("LDY_B4 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B4: LDY dp,X"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr,X
// Absolute Indexed, X
// 3<>
class LDY_BC : public AddressMode::AbsoluteIndexedX<Operator::LDY>
{
    // 3   6-2*x+x*p   abs,X     x.....x. . LDY $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("LDY_BC is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BC: LDY addr,X"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp
// Direct Page
// 2<>
class LSR_46 : public AddressMode::DirectPage<Operator::LSR>
{
    // 2   7-2*m+w     dir       0.....m* . LSR $10
    int execute(State& state) const override
    {
        throw std::runtime_error("LSR_46 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "46: LSR dp"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR A
// Accumulator
// 1<>
class LSR_4A : public AddressMode::Accumulator<Operator::LSR>
{
    // 1   2           acc       0.....m* . LSR
    int execute(State& state) const override
    {
        throw std::runtime_error("LSR_4A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4A: LSR A"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr
// Absolute
// 3<>
class LSR_4E : public AddressMode::Absolute<Operator::LSR>
{
    // 3   8-2*m       abs       0.....m* . LSR $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("LSR_4E is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4E: LSR addr"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp,X
// Direct Page Indexed, X
// 2<>
class LSR_56 : public AddressMode::DirectPageIndexedX<Operator::LSR>
{
    // 2   8-2*m+w     dir,X     0.....m* . LSR $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("LSR_56 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "56: LSR dp,X"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr,X
// Absolute Indexed, X
// 3<>
class LSR_5E : public AddressMode::AbsoluteIndexedX<Operator::LSR>
{
    // 3   9-2*m       abs,X     0.....m* . LSR $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("LSR_5E is not implemented");
        throw std::runtime_error("TODO20");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5E: LSR addr,X"; }
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
// MVN srcbk,destbk
// Block Move
// 3<>
class MVN_54 : public AddressMode::BlockMove<Operator::MVN>
{
    // 3   7           src,dest  ........ . MVN #$12,#$34
    int execute(State& state) const override
    {
        throw std::runtime_error("MVN_54 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "54: MVN srcbk,destbk"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
// MVP srcbk,destbk
// Block Move
// 3<>
class MVP_44 : public AddressMode::BlockMove<Operator::MVP>
{
    // 3   7           src,dest  ........ . MVP #$12,#$34
    int execute(State& state) const override
    {
        throw std::runtime_error("MVP_44 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "44: MVP srcbk,destbk"; }
};

// NOP No Operation [Flags affected: none]
// NOP
// Implied
// 1<>
class NOP_EA : public AddressMode::Implied<Operator::NOP>
{
    // 1   2           imp       ........ . NOP
    int execute(State& state) const override
    {
        throw std::runtime_error("NOP_EA is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EA: NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
class ORA_01 : public AddressMode::DirectPageIndexedIndirectX<Operator::ORA>
{
    // 2   7-m+w       (dir,X)   m.....m. . ORA ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_01 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "01: ORA (dp,X)"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA sr,S
// Stack Relative
// 2<>
class ORA_03 : public AddressMode::StackRelative<Operator::ORA>
{
    // 2   5-m         stk,S     m.....m. . ORA $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_03 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "03: ORA sr,S"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp
// Direct Page
// 2<>
class ORA_05 : public AddressMode::DirectPage<Operator::ORA>
{
    // 2   4-m+w       dir       m.....m. . ORA $10
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_05 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "05: ORA dp"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp]
// Direct Page Indirect Long
// 2<>
class ORA_07 : public AddressMode::DirectPageIndirectLong<Operator::ORA>
{
    // 2   7-m+w       [dir]     m.....m. . ORA [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_07 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "07: ORA [dp]"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class ORA_09 : public AddressMode::ImmediateVariableSize<Operator::ORA, State::m>
{
    // 3-m 3-m         imm       m.....m. . ORA #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_09 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "09: ORA #const"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr
// Absolute
// 3<>
class ORA_0D : public AddressMode::Absolute<Operator::ORA>
{
    // 3   5-m         abs       m.....m. . ORA $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_0D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0D: ORA addr"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long
// Absolute Long
// 4<>
class ORA_0F : public AddressMode::AbsoluteLong<Operator::ORA>
{
    // 4   6-m         long      m.....m. . ORA $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_0F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0F: ORA long"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class ORA_11 : public AddressMode::DirectPageIndirectIndexedY<Operator::ORA>
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . ORA ($10),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_11 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "11: ORA (dp),Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp)
// Direct Page Indirect
// 2<>
class ORA_12 : public AddressMode::DirectPageIndirect<Operator::ORA>
{
    // 2   6-m+w       (dir)     m.....m. . ORA ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_12 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "12: ORA (dp)"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class ORA_13 : public AddressMode::StackRelativeIndirectIndexedY<Operator::ORA>
{
    // 2   8-m         (stk,S),Y m.....m. . ORA ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_13 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "13: ORA (sr,S),Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp,X
// Direct Page Indexed, X
// 2<>
class ORA_15 : public AddressMode::DirectPageIndexedX<Operator::ORA>
{
    // 2   5-m+w       dir,X     m.....m. . ORA $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_15 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "15: ORA dp,X"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class ORA_17 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::ORA>
{
    // 2   7-m+w       [dir],Y   m.....m. . ORA [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_17 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "17: ORA [dp],Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,Y
// Absolute Indexed, Y
// 3<>
class ORA_19 : public AddressMode::AbsoluteIndexedY<Operator::ORA>
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . ORA $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_19 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "19: ORA addr,Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,X
// Absolute Indexed, X
// 3<>
class ORA_1D : public AddressMode::AbsoluteIndexedX<Operator::ORA>
{
    // 3   6-m-x+x*p   abs,X     m.....m. . ORA $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_1D is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1D: ORA addr,X"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long,X
// Absolute Long Indexed, X
// 4<>
class ORA_1F : public AddressMode::AbsoluteLongIndexedX<Operator::ORA>
{
    // 4   6-m         long,X    m.....m. . ORA $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ORA_1F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1F: ORA long,X"; }
};

// PEA Push Effective Absolute Address [Flags affected: none]
// PEA addr
// Absolute
// 3<>
class PEA_F4 : public AddressMode::Absolute<Operator::PEA>
{
    // 3   5           imm       ........ . PEA #$1234
    int execute(State& state) const override
    {
        throw std::runtime_error("PEA_F4 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F4: PEA addr"; }
};

// PEI Push Effective Indirect Address [Flags affected: none]
// PEI (dp)
// Direct Page Indirect
// 2<>
class PEI_D4 : public AddressMode::DirectPageIndirect<Operator::PEI>
{
    // 2   6+w         dir       ........ . PEI $12
    int execute(State& state) const override
    {
        throw std::runtime_error("PEI_D4 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D4: PEI (dp)"; }
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
// PER label
// Program Counter Relative Long
// 3<>
class PER_62 : public AddressMode::ProgramCounterRelativeLong<Operator::PER>
{
    // 3   6           imm       ........ . PER LABEL
    int execute(State& state) const override
    {
        throw std::runtime_error("PER_62 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "62: PER label"; }
};

// PHA Push Accumulator [Flags affected: none]
// PHA
// Implied
// 1<>
class PHA_48 : public AddressMode::Implied<Operator::PHA>
{
    // 1   4-m         imp       ........ . PHA
    int execute(State& state) const override
    {
        throw std::runtime_error("PHA_48 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "48: PHA"; }
};

// PHB Push Data Bank Register [Flags affected: none]
// PHB
// Implied
// 1<>
class PHB_8B : public AddressMode::Implied<Operator::PHB>
{
    // 1   3           imp       ........ . PHB
    int execute(State& state) const override
    {
        throw std::runtime_error("PHB_8B is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8B: PHB"; }
};

// PHD Push Direct Page Register [Flags affected: none]
// PHD
// Implied
// 1<>
class PHD_0B : public AddressMode::Implied<Operator::PHD>
{
    // 1   4           imp       ........ . PHD
    int execute(State& state) const override
    {
        throw std::runtime_error("PHD_0B is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0B: PHD"; }
};

// PHK Push Program Bank Register [Flags affected: none]
// PHK
// Implied
// 1<>
class PHK_4B : public AddressMode::Implied<Operator::PHK>
{
    // 1   3           imp       ........ . PHK
    int execute(State& state) const override
    {
        throw std::runtime_error("PHK_4B is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4B: PHK"; }
};

// PHP Push Processor Status Register [Flags affected: none]
// PHP
// Implied
// 1<>
class PHP_08 : public AddressMode::Implied<Operator::PHP>
{
    // 1   3           imp       ........ . PHP
    int execute(State& state) const override
    {
        throw std::runtime_error("PHP_08 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "08: PHP"; }
};

// PHX Push Index Register X [Flags affected: none]
// PHX
// Implied
// 1<>
class PHX_DA : public AddressMode::Implied<Operator::PHX>
{
    // 1   4-x         imp       ........ . PHX
    int execute(State& state) const override
    {
        throw std::runtime_error("PHX_DA is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DA: PHX"; }
};

// PHY Push Index Register Y [Flags affected: none]
// PHY
// Implied
// 1<>
class PHY_5A : public AddressMode::Implied<Operator::PHY>
{
    // 1   4-x         imp       ........ . PHY
    int execute(State& state) const override
    {
        throw std::runtime_error("PHY_5A is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5A: PHY"; }
};

// PLA Pull Accumulator [Flags affected: n,z]
// PLA
// Implied
// 1<>
class PLA_68 : public AddressMode::Implied<Operator::PLA>
{
    // 1   5-m         imp       m.....m. . PLA
    int execute(State& state) const override
    {
        throw std::runtime_error("PLA_68 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "68: PLA"; }
};

// PLB Pull Data Bank Register [Flags affected: n,z]
// PLB
// Implied
// 1<>
class PLB_AB : public AddressMode::Implied<Operator::PLB>
{
    // 1   4           imp       *.....*. . PLB
    int execute(State& state) const override
    {
        throw std::runtime_error("PLB_AB is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AB: PLB"; }
};

// PLD Pull Direct Page Register [Flags affected: n,z]
// PLD
// Implied
// 1<>
class PLD_2B : public AddressMode::Implied<Operator::PLD>
{
    // 1   5           imp       *.....*. . PLD
    int execute(State& state) const override
    {
        throw std::runtime_error("PLD_2B is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2B: PLD"; }
};

// PLP Pull Processor Status Register [Flags affected: n,z]
// PLP
// Implied
// 1<>
class PLP_28 : public AddressMode::Implied<Operator::PLP>
{
    // 1   4           imp       ******** . PLP
    int execute(State& state) const override
    {
        throw std::runtime_error("PLP_28 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "28: PLP"; }
};

// PLX Pull Index Register X [Flags affected: n,z]
// PLX
// Implied
// 1<>
class PLX_FA : public AddressMode::Implied<Operator::PLX>
{
    // 1   5-x         imp       x.....x. . PLX
    int execute(State& state) const override
    {
        throw std::runtime_error("PLX_FA is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FA: PLX"; }
};

// PLY Pull Index Register Y [Flags affected: n,z]
// PLY
// Implied
// 1<>
class PLY_7A : public AddressMode::Implied<Operator::PLY>
{
    // 1   5-x         imp       x.....x. . PLY
    int execute(State& state) const override
    {
        throw std::runtime_error("PLY_7A is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7A: PLY"; }
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
// REP #const
// Immediate
// 2<>
class REP_C2 : public AddressMode::Immediate<Operator::REP>
{
    // 2   3           imm       ******** . REP #$12
    int execute(State& state) const override
    {
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C2: REP #const"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp
// Direct Page
// 2<>
class ROL_26 : public AddressMode::DirectPage<Operator::ROL>
{
    // 2   7-2*m+w     dir       m.....mm . ROL $10
    int execute(State& state) const override
    {
        throw std::runtime_error("ROL_26 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "26: ROL dp"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL A
// Accumulator
// 1<>
class ROL_2A : public AddressMode::Accumulator<Operator::ROL>
{
    // 1   2           acc       m.....mm . ROL
    int execute(State& state) const override
    {
        throw std::runtime_error("ROL_2A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2A: ROL A"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr
// Absolute
// 3<>
class ROL_2E : public AddressMode::Absolute<Operator::ROL>
{
    // 3   8-2*m       abs       m.....mm . ROL $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("ROL_2E is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2E: ROL addr"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp,X
// Direct Page Indexed, X
// 2<>
class ROL_36 : public AddressMode::DirectPageIndexedX<Operator::ROL>
{
    // 2   8-2*m+w     dir,X     m.....mm . ROL $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ROL_36 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "36: ROL dp,X"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr,X
// Absolute Indexed, X
// 3<>
class ROL_3E : public AddressMode::AbsoluteIndexedX<Operator::ROL>
{
    // 3   9-2*m       abs,X     m.....mm . ROL $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("ROL_3E is not implemented");
        throw std::runtime_error("TODO20");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3E: ROL addr,X"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp
// Direct Page
// 2<>
class ROR_66 : public AddressMode::DirectPage<Operator::ROR>
{
    // 2   7-2*m+w     dir       m.....m* . ROR $10
    int execute(State& state) const override
    {
        throw std::runtime_error("ROR_66 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "66: ROR dp"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR A
// Accumulator
// 1<>
class ROR_6A : public AddressMode::Accumulator<Operator::ROR>
{
    // 1   2           acc       m.....m* . ROR
    int execute(State& state) const override
    {
        throw std::runtime_error("ROR_6A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6A: ROR A"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr
// Absolute
// 3<>
class ROR_6E : public AddressMode::Absolute<Operator::ROR>
{
    // 3   8-2*m       abs       m.....m* . ROR $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("ROR_6E is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6E: ROR addr"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp,X
// Direct Page Indexed, X
// 2<>
class ROR_76 : public AddressMode::DirectPageIndexedX<Operator::ROR>
{
    // 2   8-2*m+w     dir,X     m.....m* . ROR $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("ROR_76 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "76: ROR dp,X"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr,X
// Absolute Indexed, X
// 3<>
class ROR_7E : public AddressMode::AbsoluteIndexedX<Operator::ROR>
{
    // 3   9-2*m       abs,X     m.....m* . ROR $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("ROR_7E is not implemented");
        throw std::runtime_error("TODO20");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7E: ROR addr,X"; }
};

// RTI Return from Interrupt [Flags affected: all except b]
// RTI
// Implied
// 1<>
class RTI_40 : public AddressMode::Implied<Operator::RTI>
{
    // 1   7-e         imp       ******** . RTI
    int execute(State& state) const override
    {
        throw std::runtime_error("RTI_40 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "40: RTI"; }
};

// RTL Return from Subroutine Long [Flags affected: none]
// RTL
// Implied
// 1<>
class RTL_6B : public AddressMode::Implied<Operator::RTL>
{
    // 1   6           imp       ........ . RTL
    int execute(State& state) const override
    {
        throw std::runtime_error("RTL_6B is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6B: RTL"; }
};

// RTS Return from Subroutine [Flags affected: none]
// RTS
// Implied
// 1<>
class RTS_60 : public AddressMode::Implied<Operator::RTS>
{
    // 1   6           imp       ........ . RTS
    int execute(State& state) const override
    {
        throw std::runtime_error("RTS_60 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "60: RTS"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
class SBC_E1 : public AddressMode::DirectPageIndexedIndirectX<Operator::SBC>
{
    // 2   7-m+w       (dir,X)   mm....mm . SBC ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_E1 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E1: SBC (dp,X)"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC sr,S
// Stack Relative
// 2<>
class SBC_E3 : public AddressMode::StackRelative<Operator::SBC>
{
    // 2   5-m         stk,S     mm....mm . SBC $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_E3 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E3: SBC sr,S"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp
// Direct Page
// 2<>
class SBC_E5 : public AddressMode::DirectPage<Operator::SBC>
{
    // 2   4-m+w       dir       mm....mm . SBC $10
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_E5 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E5: SBC dp"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp]
// Direct Page Indirect Long
// 2<>
class SBC_E7 : public AddressMode::DirectPageIndirectLong<Operator::SBC>
{
    // 2   7-m+w       [dir]     mm....mm . SBC [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_E7 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E7: SBC [dp]"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC #const
// Immediate
// 2<17>
// ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
class SBC_E9 : public AddressMode::ImmediateVariableSize<Operator::SBC, State::m>
{
    // 3-m 3-m         imm       mm....mm . SBC #$54
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_E9 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E9: SBC #const"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr
// Absolute
// 3<>
class SBC_ED : public AddressMode::Absolute<Operator::SBC>
{
    // 3   5-m         abs       mm....mm . SBC $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_ED is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "ED: SBC addr"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long
// Absolute Long
// 4<>
class SBC_EF : public AddressMode::AbsoluteLong<Operator::SBC>
{
    // 4   6-m         long      mm....mm . SBC $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_EF is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EF: SBC long"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class SBC_F1 : public AddressMode::DirectPageIndirectIndexedY<Operator::SBC>
{
    // 2   7-m+w-x+x*p (dir),Y   mm....mm . SBC ($10),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_F1 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F1: SBC (dp),Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp)
// Direct Page Indirect
// 2<>
class SBC_F2 : public AddressMode::DirectPageIndirect<Operator::SBC>
{
    // 2   6-m+w       (dir)     mm....mm . SBC ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_F2 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F2: SBC (dp)"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class SBC_F3 : public AddressMode::StackRelativeIndirectIndexedY<Operator::SBC>
{
    // 2   8-m         (stk,S),Y mm....mm . SBC ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_F3 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F3: SBC (sr,S),Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp,X
// Direct Page Indexed, X
// 2<>
class SBC_F5 : public AddressMode::DirectPageIndexedX<Operator::SBC>
{
    // 2   5-m+w       dir,X     mm....mm . SBC $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_F5 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F5: SBC dp,X"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class SBC_F7 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::SBC>
{
    // 2   7-m+w       [dir],Y   mm....mm . SBC [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_F7 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F7: SBC [dp],Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,Y
// Absolute Indexed, Y
// 3<>
class SBC_F9 : public AddressMode::AbsoluteIndexedY<Operator::SBC>
{
    // 3   6-m-x+x*p   abs,Y     mm....mm . SBC $9876,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_F9 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F9: SBC addr,Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,X
// Absolute Indexed, X
// 3<>
class SBC_FD : public AddressMode::AbsoluteIndexedX<Operator::SBC>
{
    // 3   6-m-x+x*p   abs,X     mm....mm . SBC $9876,X
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_FD is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FD: SBC addr,X"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long,X
// Absolute Long Indexed, X
// 4<>
class SBC_FF : public AddressMode::AbsoluteLongIndexedX<Operator::SBC>
{
    // 4   6-m         long,X    mm....mm . SBC $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("SBC_FF is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FF: SBC long,X"; }
};

// SEC Set Carry Flag [Flags affected: c]
// SEC
// Implied
// 1<>
class SEC_38 : public AddressMode::Implied<Operator::SEC>
{
    // 1   2           imp       .......1 . SEC
    int execute(State& state) const override
    {
        throw std::runtime_error("SEC_38 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "38: SEC"; }
};

// SED Set Decimal Flag [Flags affected: d]
// SED
// Implied
// 1<>
class SED_F8 : public AddressMode::Implied<Operator::SED>
{
    // 1   2           imp       ....1... . SED
    int execute(State& state) const override
    {
        throw std::runtime_error("SED_F8 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F8: SED"; }
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
// SEI
// Implied
// 1<>
class SEI_78 : public AddressMode::Implied<Operator::SEI>
{
    // 1   2           imp       .....1.. . SEI
    int execute(State& state) const override
    {
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "78: SEI"; }
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
// SEP #const
// Immediate
// 2<>
class SEP_E2 : public AddressMode::Immediate<Operator::SEP>
{
    // 2   3           imm       ******** . SEP #$12
    int execute(State& state) const override
    {
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E2: SEP #const"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
class STA_81 : public AddressMode::DirectPageIndexedIndirectX<Operator::STA>
{
    // 2   7-m+w       (dir,X)   ........ . STA ($10,X)
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_81 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "81: STA (dp,X)"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA sr,S
// Stack Relative
// 2<>
class STA_83 : public AddressMode::StackRelative<Operator::STA>
{
    // 2   5-m         stk,S     ........ . STA $32,S
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_83 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "83: STA sr,S"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp
// Direct Page
// 2<>
class STA_85 : public AddressMode::DirectPage<Operator::STA>
{
    // 2   4-m+w       dir       ........ . STA $10
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_85 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "85: STA dp"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp]
// Direct Page Indirect Long
// 2<>
class STA_87 : public AddressMode::DirectPageIndirectLong<Operator::STA>
{
    // 2   7-m+w       [dir]     ........ . STA [$10]
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_87 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "87: STA [dp]"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr
// Absolute
// 3<>
class STA_8D : public AddressMode::Absolute<Operator::STA>
{
    // 3   5-m         abs       ........ . STA $9876
    int execute(State& state) const override
    {
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8D: STA addr"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long
// Absolute Long
// 4<>
class STA_8F : public AddressMode::AbsoluteLong<Operator::STA>
{
    // 4   6-m         long      ........ . STA $FEDBCA
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_8F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8F: STA long"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
class STA_91 : public AddressMode::DirectPageIndirectIndexedY<Operator::STA>
{
    // 2   7-m+w       (dir),Y   ........ . STA ($10),Y
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_91 is not implemented");
        throw std::runtime_error("TODO20");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "91: STA (dp),Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp)
// Direct Page Indirect
// 2<>
class STA_92 : public AddressMode::DirectPageIndirect<Operator::STA>
{
    // 2   6-m+w       (dir)     ........ . STA ($10)
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_92 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "92: STA (dp)"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
class STA_93 : public AddressMode::StackRelativeIndirectIndexedY<Operator::STA>
{
    // 2   8-m         (stk,S),Y ........ . STA ($32,S),Y
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_93 is not implemented");
        return 7 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "93: STA (sr,S),Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp,X
// Direct Page Indexed, X
// 2<>
class STA_95 : public AddressMode::DirectPageIndexedX<Operator::STA>
{
    // 2   5-m+w       dir,X     ........ . STA $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_95 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "95: STA dp,X"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
class STA_97 : public AddressMode::DirectPageIndirectLongIndexedY<Operator::STA>
{
    // 2   7-m+w       [dir],Y   ........ . STA [$10],Y
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_97 is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "97: STA [dp],Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,Y
// Absolute Indexed, Y
// 3<>
class STA_99 : public AddressMode::AbsoluteIndexedY<Operator::STA>
{
    // 3   6-m         abs,Y     ........ . STA $9876,Y
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_99 is not implemented");
        throw std::runtime_error("TODO20");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "99: STA addr,Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,X
// Absolute Indexed, X
// 3<>
class STA_9D : public AddressMode::AbsoluteIndexedX<Operator::STA>
{
    // 3   6-m         abs,X     ........ . STA $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_9D is not implemented");
        throw std::runtime_error("TODO20");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9D: STA addr,X"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long,X
// Absolute Long Indexed, X
// 4<>
class STA_9F : public AddressMode::AbsoluteLongIndexedX<Operator::STA>
{
    // 4   6-m         long,X    ........ . STA $FEDCBA,X
    int execute(State& state) const override
    {
        throw std::runtime_error("STA_9F is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9F: STA long,X"; }
};

// STP Stop Processor [Flags affected: none]
// STP
// Implied
// 1<>
class STP_DB : public AddressMode::Implied<Operator::STP>
{
    // 1   3           imp       ........ . STP
    int execute(State& state) const override
    {
        throw std::runtime_error("STP_DB is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DB: STP"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp
// Direct Page
// 2<>
class STX_86 : public AddressMode::DirectPage<Operator::STX>
{
    // 2   4-x+w       dir       ........ . STX $10
    int execute(State& state) const override
    {
        throw std::runtime_error("STX_86 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "86: STX dp"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX addr
// Absolute
// 3<>
class STX_8E : public AddressMode::Absolute<Operator::STX>
{
    // 3   5-x         abs       ........ . STX $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("STX_8E is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8E: STX addr"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp,Y
// Direct Page Indexed, Y
// 2<>
class STX_96 : public AddressMode::DirectPageIndexedY<Operator::STX>
{
    // 2   5-x+w       dir,Y     ........ . STX $10,Y
    int execute(State& state) const override
    {
        throw std::runtime_error("STX_96 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "96: STX dp,Y"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp
// Direct Page
// 2<>
class STY_84 : public AddressMode::DirectPage<Operator::STY>
{
    // 2   4-x+w       dir       ........ . STY $10
    int execute(State& state) const override
    {
        throw std::runtime_error("STY_84 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "84: STY dp"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY addr
// Absolute
// 3<>
class STY_8C : public AddressMode::Absolute<Operator::STY>
{
    // 3   5-x         abs       ........ . STY $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("STY_8C is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8C: STY addr"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp,X
// Direct Page Indexed, X
// 2<>
class STY_94 : public AddressMode::DirectPageIndexedX<Operator::STY>
{
    // 2   5-x+w       dir,X     ........ . STY $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("STY_94 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "94: STY dp,X"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp
// Direct Page
// 2<>
class STZ_64 : public AddressMode::DirectPage<Operator::STZ>
{
    // 2   4-m+w       dir       ........ . STZ $10
    int execute(State& state) const override
    {
        throw std::runtime_error("STZ_64 is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "64: STZ dp"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp,X
// Direct Page Indexed, X
// 2<>
class STZ_74 : public AddressMode::DirectPageIndexedX<Operator::STZ>
{
    // 2   5-m+w       dir,X     ........ . STZ $10,X
    int execute(State& state) const override
    {
        throw std::runtime_error("STZ_74 is not implemented");
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "74: STZ dp,X"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr
// Absolute
// 3<>
class STZ_9C : public AddressMode::Absolute<Operator::STZ>
{
    // 3   5-m         abs       ........ . STZ $9876
    int execute(State& state) const override
    {
        return 4 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9C: STZ addr"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr,X
// Absolute Indexed, X
// 3<>
class STZ_9E : public AddressMode::AbsoluteIndexedX<Operator::STZ>
{
    // 3   6-m         abs,X     ........ . STZ $9876,X
    // §20: TODO manually add exception for 3
    int execute(State& state) const override
    {
        throw std::runtime_error("STZ_9E is not implemented");
        throw std::runtime_error("TODO20");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9E: STZ addr,X"; }
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
// TAX
// Implied
// 1<>
class TAX_AA : public AddressMode::Implied<Operator::TAX>
{
    // 1   2           imp       x.....x. . TAX
    int execute(State& state) const override
    {
        throw std::runtime_error("TAX_AA is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AA: TAX"; }
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
// TAY
// Implied
// 1<>
class TAY_A8 : public AddressMode::Implied<Operator::TAY>
{
    // 1   2           imp       x.....x. . TAY
    int execute(State& state) const override
    {
        throw std::runtime_error("TAY_A8 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A8: TAY"; }
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
// TCD
// Implied
// 1<>
class TCD_5B : public AddressMode::Implied<Operator::TCD>
{
    // 1   2           imp       *.....*. . TCD
    int execute(State& state) const override
    {
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5B: TCD"; }
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
// TCS
// Implied
// 1<>
class TCS_1B : public AddressMode::Implied<Operator::TCS>
{
    // 1   2           imp       ........ . TCS
    int execute(State& state) const override
    {
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1B: TCS"; }
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
// TDC
// Implied
// 1<>
class TDC_7B : public AddressMode::Implied<Operator::TDC>
{
    // 1   2           imp       *.....*. . TDC
    int execute(State& state) const override
    {
        throw std::runtime_error("TDC_7B is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7B: TDC"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB dp
// Direct Page
// 2<>
class TRB_14 : public AddressMode::DirectPage<Operator::TRB>
{
    // 2   7-2*m+w     dir       ......m. . TRB $10
    int execute(State& state) const override
    {
        throw std::runtime_error("TRB_14 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "14: TRB dp"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB addr
// Absolute
// 3<>
class TRB_1C : public AddressMode::Absolute<Operator::TRB>
{
    // 3   8-2*m       abs       ......m. . TRB $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("TRB_1C is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1C: TRB addr"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB dp
// Direct Page
// 2<>
class TSB_04 : public AddressMode::DirectPage<Operator::TSB>
{
    // 2   7-2*m+w     dir       ......m. . TSB $10
    int execute(State& state) const override
    {
        throw std::runtime_error("TSB_04 is not implemented");
        return 5 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "04: TSB dp"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB addr
// Absolute
// 3<>
class TSB_0C : public AddressMode::Absolute<Operator::TSB>
{
    // 3   8-2*m       abs       ......m. . TSB $9876
    int execute(State& state) const override
    {
        throw std::runtime_error("TSB_0C is not implemented");
        return 6 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0C: TSB addr"; }
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
// TSC
// Implied
// 1<>
class TSC_3B : public AddressMode::Implied<Operator::TSC>
{
    // 1   2           imp       *.....*. . TSC
    int execute(State& state) const override
    {
        throw std::runtime_error("TSC_3B is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3B: TSC"; }
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
// TSX
// Implied
// 1<>
class TSX_BA : public AddressMode::Implied<Operator::TSX>
{
    // 1   2           imp       x.....x. . TSX
    int execute(State& state) const override
    {
        throw std::runtime_error("TSX_BA is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BA: TSX"; }
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
// TXA
// Implied
// 1<>
class TXA_8A : public AddressMode::Implied<Operator::TXA>
{
    // 1   2           imp       m.....m. . TXA
    int execute(State& state) const override
    {
        throw std::runtime_error("TXA_8A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8A: TXA"; }
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
// TXS
// Implied
// 1<>
class TXS_9A : public AddressMode::Implied<Operator::TXS>
{
    // 1   2           imp       ........ . TXS
    int execute(State& state) const override
    {
        throw std::runtime_error("TXS_9A is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9A: TXS"; }
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
// TXY
// Implied
// 1<>
class TXY_9B : public AddressMode::Implied<Operator::TXY>
{
    // 1   2           imp       x.....x. . TXY
    int execute(State& state) const override
    {
        throw std::runtime_error("TXY_9B is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9B: TXY"; }
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
// TYA
// Implied
// 1<>
class TYA_98 : public AddressMode::Implied<Operator::TYA>
{
    // 1   2           imp       m.....m. . TYA
    int execute(State& state) const override
    {
        throw std::runtime_error("TYA_98 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "98: TYA"; }
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
// TYX
// Implied
// 1<>
class TYX_BB : public AddressMode::Implied<Operator::TYX>
{
    // 1   2           imp       x.....x. . TYX
    int execute(State& state) const override
    {
        throw std::runtime_error("TYX_BB is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BB: TYX"; }
};

// WAI Wait for Interrupt [Flags affected: none]
// WAI
// Implied
// 1<>
class WAI_CB : public AddressMode::Implied<Operator::WAI>
{
    // 1   3           imp       ........ . WAI
    int execute(State& state) const override
    {
        throw std::runtime_error("WAI_CB is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CB: WAI"; }
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
// WDM
// Immediate
// 2<>
class WDM_42 : public AddressMode::Immediate<Operator::WDM>
{
    // 2   2           imm       ........ . WDM
    int execute(State& state) const override
    {
        throw std::runtime_error("WDM_42 is not implemented");
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "42: WDM"; }
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
// XBA
// Implied
// 1<>
class XBA_EB : public AddressMode::Implied<Operator::XBA>
{
    // 1   3           imp       *.....*. . XBA
    int execute(State& state) const override
    {
        throw std::runtime_error("XBA_EB is not implemented");
        return 3 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EB: XBA"; }
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
// XCE
// Implied
// 1<>
class XCE_FB : public AddressMode::Implied<Operator::XCE>
{
    // 1   2           imp       .......* * XCE
    int execute(State& state) const override
    {
        return 2 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FB: XCE"; }
};

}
