#pragma once

#include "Exception.h"
#include "CpuState.h"
#include "CpuAddressMode.h"
#include "CpuOperator.h"

#include "Profiler.h"

#define PROFILE_OPCODES false

namespace CPU {

EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)

CREATE_PROFILER();

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
template<>
struct Opcode<State, 0x61>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::ADC>;

    // 2   7-m+w       (dir,X)   mm....mm . ADC ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "61: ADC (dp,X)");

        throw NotYetImplementedException("61");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "61: ADC (dp,X)"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0x63>
{
    using Instruction = AddressMode::StackRelative<Operator::ADC>;

    // 2   5-m         stk,S     mm....mm . ADC $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "63: ADC sr,S");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "63: ADC sr,S"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x65>
{
    using Instruction = AddressMode::DirectPage<Operator::ADC>;

    // 2   4-m+w       dir       mm....mm . ADC $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "65: ADC dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "65: ADC dp"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0x67>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::ADC>;

    // 2   7-m+w       [dir]     mm....mm . ADC [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "67: ADC [dp]");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "67: ADC [dp]"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0x69>
{
    using Instruction = AddressMode::Immediate<Operator::ADC>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::ADC>;

    // 3-m 3-m         imm       mm....mm . ADC #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "69: ADC #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "69: ADC #const"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x6D>
{
    using Instruction = AddressMode::Absolute<Operator::ADC>;

    // 3   5-m         abs       mm....mm . ADC $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6D: ADC addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6D: ADC addr"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0x6F>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::ADC>;

    // 4   6-m         long      mm....mm . ADC $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6F: ADC long");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6F: ADC long"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x71>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::ADC>;

    // 2   7-m+w-x+x*p (dir),Y   mm....mm . ADC ($10),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "71: ADC (dp),Y");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "71: ADC (dp),Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0x72>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::ADC>;

    // 2   6-m+w       (dir)     mm....mm . ADC ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "72: ADC (dp)");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "72: ADC (dp)"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x73>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::ADC>;

    // 2   8-m         (stk,S),Y mm....mm . ADC ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "73: ADC (sr,S),Y");

        throw NotYetImplementedException("73");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "73: ADC (sr,S),Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x75>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::ADC, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     mm....mm . ADC $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "75: ADC dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "75: ADC dp,X"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x77>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::ADC>;

    // 2   7-m+w       [dir],Y   mm....mm . ADC [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "77: ADC [dp],Y");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "77: ADC [dp],Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0x79>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::ADC, State::IndexRegister::Y, true>;

    // 3   6-m-x+x*p   abs,Y     mm....mm . ADC $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "79: ADC addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "79: ADC addr,Y"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x7D>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::ADC, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     mm....mm . ADC $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7D: ADC addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7D: ADC addr,X"; }
};

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0x7F>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::ADC>;

    // 4   6-m         long,X    mm....mm . ADC $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7F: ADC long,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7F: ADC long,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
template<>
struct Opcode<State, 0x21>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::AND>;

    // 2   7-m+w       (dir,X)   m.....m. . AND ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "21: AND (dp,X)");

        throw NotYetImplementedException("21");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "21: AND (dp,X)"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0x23>
{
    using Instruction = AddressMode::StackRelative<Operator::AND>;

    // 2   5-m         stk,S     m.....m. . AND $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "23: AND sr,S");

        throw NotYetImplementedException("23");
        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "23: AND sr,S"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x25>
{
    using Instruction = AddressMode::DirectPage<Operator::AND>;

    // 2   4-m+w       dir       m.....m. . AND $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "25: AND dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "25: AND dp"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0x27>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::AND>;

    // 2   7-m+w       [dir]     m.....m. . AND [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "27: AND [dp]");

        throw NotYetImplementedException("27");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "27: AND [dp]"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0x29>
{
    using Instruction = AddressMode::Immediate<Operator::AND>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::AND>;

    // 3-m 3-m         imm       m.....m. . AND #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "29: AND #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "29: AND #const"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x2D>
{
    using Instruction = AddressMode::Absolute<Operator::AND>;

    // 3   5-m         abs       m.....m. . AND $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2D: AND addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2D: AND addr"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0x2F>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::AND>;

    // 4   6-m         long      m.....m. . AND $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2F: AND long");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2F: AND long"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x31>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::AND>;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . AND ($10),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "31: AND (dp),Y");

        throw NotYetImplementedException("31");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "31: AND (dp),Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0x32>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::AND>;

    // 2   6-m+w       (dir)     m.....m. . AND ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "32: AND (dp)");

        throw NotYetImplementedException("32");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "32: AND (dp)"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x33>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::AND>;

    // 2   8-m         (stk,S),Y m.....m. . AND ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "33: AND (sr,S),Y");

        throw NotYetImplementedException("33");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "33: AND (sr,S),Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x35>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::AND, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     m.....m. . AND $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "35: AND dp,X");

        throw NotYetImplementedException("35");
        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "35: AND dp,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x37>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::AND>;

    // 2   7-m+w       [dir],Y   m.....m. . AND [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "37: AND [dp],Y");

        throw NotYetImplementedException("37");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "37: AND [dp],Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0x39>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::AND, State::IndexRegister::Y, true>;

    // 3   6-m-x+x*p   abs,Y     m.....m. . AND $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "39: AND addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "39: AND addr,Y"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x3D>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::AND, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     m.....m. . AND $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3D: AND addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3D: AND addr,X"; }
};

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0x3F>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::AND>;

    // 4   6-m         long,X    m.....m. . AND $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3F: AND long,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3F: AND long,X"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x06>
{
    using Instruction = AddressMode::DirectPage<Operator::ASL>;

    // 2   7-2*m+w     dir       m.....mm . ASL $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "06: ASL dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "06: ASL dp"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL A
// Accumulator (1-Byte)
template<>
struct Opcode<State, 0x0A>
{
    using Instruction = AddressMode::Accumulator<Operator::ASL>;

    // 1   2           acc       m.....mm . ASL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0A: ASL A");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0A: ASL A"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x0E>
{
    using Instruction = AddressMode::Absolute<Operator::ASL>;

    // 3   8-2*m       abs       m.....mm . ASL $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0E: ASL addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0E: ASL addr"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x16>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::ASL, State::IndexRegister::X>;

    // 2   8-2*m+w     dir,X     m.....mm . ASL $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "16: ASL dp,X");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "16: ASL dp,X"; }
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x1E>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::ASL, State::IndexRegister::X, false>;

    // 3   9-2*m       abs,X     m.....mm . ASL $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1E: ASL addr,X");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1E: ASL addr,X"; }
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
// BCC nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x90>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BCC>;

    // 2   2+t+t*e*p   rel8      ........ . BCC LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "90: BCC nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "90: BCC nearlabel"; }
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
// BCS nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0xB0>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BCS>;

    // 2   2+t+t*e*p   rel8      ........ . BCS LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B0: BCS nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B0: BCS nearlabel"; }
};

// BEQ Branch if Equal [Flags affected: none]
// BEQ nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0xF0>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BEQ>;

    // 2   2+t+t*e*p   rel8      ........ . BEQ LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F0: BEQ nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F0: BEQ nearlabel"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x24>
{
    using Instruction = AddressMode::DirectPage<Operator::BIT<false>>;

    // 2   4-m+w       dir       mm....m. . BIT $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "24: BIT dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "24: BIT dp"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x2C>
{
    using Instruction = AddressMode::Absolute<Operator::BIT<false>>;

    // 3   5-m         abs       mm....m. . BIT $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2C: BIT addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2C: BIT addr"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x34>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::BIT<false>, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     mm....m. . BIT $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "34: BIT dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "34: BIT dp,X"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x3C>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::BIT<false>, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     mm....m. . BIT $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3C: BIT addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3C: BIT addr,X"; }
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0x89>
{
    using Instruction = AddressMode::Immediate<Operator::BIT<true>>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::BIT<true>>;

    // 3-m 3-m         imm       ......m. . BIT #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "89: BIT #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "89: BIT #const"; }
};

// BMI Branch if Minus [Flags affected: none]
// BMI nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x30>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BMI>;

    // 2   2+t+t*e*p   rel8      ........ . BMI LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "30: BMI nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "30: BMI nearlabel"; }
};

// BNE Branch if Not Equal [Flags affected: none]
// BNE nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0xD0>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BNE>;

    // 2   2+t+t*e*p   rel8      ........ . BNE LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D0: BNE nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D0: BNE nearlabel"; }
};

// BPL Branch if Plus [Flags affected: none]
// BPL nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x10>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BPL>;

    // 2   2+t+t*e*p   rel8      ........ . BPL LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "10: BPL nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "10: BPL nearlabel"; }
};

// BRA Branch Always [Flags affected: none]
// BRA nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x80>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BRA>;

    // 2   3+e*p       rel8      ........ . BRA LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "80: BRA nearlabel");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "80: BRA nearlabel"; }
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
// BRK
// Immediate (2-Byte [18])
template<>
struct Opcode<State, 0x00>
{
    using Instruction = AddressMode::Immediate<Operator::BRK>;

    // 1   8-e         imp       ....01.. . BRK
    // ¤18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "00: BRK");

        throw NotYetImplementedException("00");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "00: BRK"; }
};

// BRL Branch Long Always [Flags affected: none]
// BRL label
// Program Counter Relative Long (3-Byte)
template<>
struct Opcode<State, 0x82>
{
    using Instruction = AddressMode::ProgramCounterRelativeLong<Operator::BRL>;

    // 3   4           rel16     ........ . BRL LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "82: BRL label");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "82: BRL label"; }
};

// BVC Branch if Overflow Clear [Flags affected: none]
// BVC nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x50>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BVC>;

    // 2   2+t+t*e*p   rel8      ........ . BVC LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "50: BVC nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "50: BVC nearlabel"; }
};

// BVS Branch if Overflow Set [Flags affected: none]
// BVS nearlabel
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x70>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BVS>;

    // 2   2+t+t*e*p   rel8      ........ . BVS LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "70: BVS nearlabel");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "70: BVS nearlabel"; }
};

// CLC Clear Carry [Flags affected: c]
// CLC
// Implied (1-Byte)
template<>
struct Opcode<State, 0x18>
{
    using Instruction = AddressMode::Implied<Operator::SE_<State::Flag::c, false>>;

    // 1   2           imp       .......0 . CLC
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "18: CLC");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "18: CLC"; }
};

// CLD Clear Decimal Mode Flag [Flags affected: d]
// CLD
// Implied (1-Byte)
template<>
struct Opcode<State, 0xD8>
{
    using Instruction = AddressMode::Implied<Operator::SE_<State::Flag::d, false>>;

    // 1   2           imp       ....0... . CLD
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D8: CLD");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D8: CLD"; }
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]
// CLI
// Implied (1-Byte)
template<>
struct Opcode<State, 0x58>
{
    using Instruction = AddressMode::Implied<Operator::SE_<State::Flag::i, false>>;

    // 1   2           imp       .....0.. . CLI
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "58: CLI");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "58: CLI"; }
};

// CLV Clear Overflow Flag [Flags affected: v]
// CLV
// Implied (1-Byte)
template<>
struct Opcode<State, 0xB8>
{
    using Instruction = AddressMode::Implied<Operator::SE_<State::Flag::v, false>>;

    // 1   2           imp       .0...... . CLV
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B8: CLV");

        throw NotYetImplementedException("B8");
        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B8: CLV"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp,X)
// Direct Page Indexed Indirect,X (2-Byte)
template<>
struct Opcode<State, 0xC1>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::CMP>;

    // 2   7-m+w       (dir,X)   m.....mm . CMP ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C1: CMP (dp,X)");

        throw NotYetImplementedException("C1");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C1: CMP (dp,X)"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0xC3>
{
    using Instruction = AddressMode::StackRelative<Operator::CMP>;

    // 2   5-m         stk,S     m.....mm . CMP $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C3: CMP sr,S");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C3: CMP sr,S"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xC5>
{
    using Instruction = AddressMode::DirectPage<Operator::CMP>;

    // 2   4-m+w       dir       m.....mm . CMP $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C5: CMP dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C5: CMP dp"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0xC7>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::CMP>;

    // 2   7-m+w       [dir]     m.....mm . CMP [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C7: CMP [dp]");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C7: CMP [dp]"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0xC9>
{
    using Instruction = AddressMode::Immediate<Operator::CMP>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::CMP>;

    // 3-m 3-m         imm       m.....mm . CMP #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C9: CMP #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "C9: CMP #const"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xCD>
{
    using Instruction = AddressMode::Absolute<Operator::CMP>;

    // 3   5-m         abs       m.....mm . CMP $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CD: CMP addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CD: CMP addr"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0xCF>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::CMP>;

    // 4   6-m         long      m.....mm . CMP $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CF: CMP long");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CF: CMP long"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xD1>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::CMP>;

    // 2   7-m+w-x+x*p (dir),Y   m.....mm . CMP ($10),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D1: CMP (dp),Y");

        throw NotYetImplementedException("D1");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D1: CMP (dp),Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0xD2>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::CMP>;

    // 2   6-m+w       (dir)     m.....mm . CMP ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D2: CMP (dp)");

        throw NotYetImplementedException("D2");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D2: CMP (dp)"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xD3>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::CMP>;

    // 2   8-m         (stk,S),Y m.....mm . CMP ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D3: CMP (sr,S),Y");

        throw NotYetImplementedException("D3");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D3: CMP (sr,S),Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0xD5>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::CMP, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     m.....mm . CMP $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D5: CMP dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D5: CMP dp,X"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xD7>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::CMP>;

    // 2   7-m+w       [dir],Y   m.....mm . CMP [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D7: CMP [dp],Y");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D7: CMP [dp],Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0xD9>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::CMP, State::IndexRegister::Y, true>;

    // 3   6-m-x+x*p   abs,Y     m.....mm . CMP $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D9: CMP addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D9: CMP addr,Y"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0xDD>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::CMP, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     m.....mm . CMP $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DD: CMP addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DD: CMP addr,X"; }
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0xDF>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::CMP>;

    // 4   6-m         long,X    m.....mm . CMP $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DF: CMP long,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DF: CMP long,X"; }
};

// COP Co-Processor Enable [Flags affected: d,i]
// COP const
// Immediate (2-Byte [18])
template<>
struct Opcode<State, 0x02>
{
    using Instruction = AddressMode::Immediate<Operator::COP>;

    // 2   8-e         imm       ....01.. . COP #$12
    // ¤18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "02: COP const");

        throw NotYetImplementedException("02");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "02: COP const"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX #const
// Immediate (2-Byte [19])
template<>
struct Opcode<State, 0xE0>
{
    using Instruction = AddressMode::Immediate<Operator::CP_<State::IndexRegister::X>>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::CP_<State::IndexRegister::X>>;

    // 3-x 3-x         imm       x.....xx . CPX #$54
    // ¤19: Add 1 byte if x=0 (16-bit index registers)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E0: CPX #const");

        if (state.is16Bit(State::Flag::x))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "E0: CPX #const"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xE4>
{
    using Instruction = AddressMode::DirectPage<Operator::CP_<State::IndexRegister::X>>;

    // 2   4-x+w       dir       x.....xx . CPX $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E4: CPX dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E4: CPX dp"; }
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xEC>
{
    using Instruction = AddressMode::Absolute<Operator::CP_<State::IndexRegister::X>>;

    // 3   5-x         abs       x.....xx . CPX $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EC: CPX addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EC: CPX addr"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY #const
// Immediate (2-Byte [19])
template<>
struct Opcode<State, 0xC0>
{
    using Instruction = AddressMode::Immediate<Operator::CP_<State::IndexRegister::Y>>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::CP_<State::IndexRegister::Y>>;

    // 3-x 3-x         imm       x.....xx . CPY #$54
    // ¤19: Add 1 byte if x=0 (16-bit index registers)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C0: CPY #const");

        if (state.is16Bit(State::Flag::x))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "C0: CPY #const"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xC4>
{
    using Instruction = AddressMode::DirectPage<Operator::CP_<State::IndexRegister::Y>>;

    // 2   4-x+w       dir       x.....xx . CPY $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C4: CPY dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C4: CPY dp"; }
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xCC>
{
    using Instruction = AddressMode::Absolute<Operator::CP_<State::IndexRegister::Y>>;

    // 3   5-x         abs       x.....xx . CPY $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CC: CPY addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CC: CPY addr"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC A
// Accumulator (1-Byte)
template<>
struct Opcode<State, 0x3A>
{
    using Instruction = AddressMode::Accumulator<Operator::DEC>;

    // 1   2           acc       m.....m. . DEC
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3A: DEC A");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3A: DEC A"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xC6>
{
    using Instruction = AddressMode::DirectPage<Operator::DEC>;

    // 2   7-2*m+w     dir       m.....m. . DEC $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C6: DEC dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C6: DEC dp"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xCE>
{
    using Instruction = AddressMode::Absolute<Operator::DEC>;

    // 3   8-2*m       abs       m.....m. . DEC $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CE: DEC addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CE: DEC addr"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0xD6>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::DEC, State::IndexRegister::X>;

    // 2   8-2*m+w     dir,X     m.....m. . DEC $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D6: DEC dp,X");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D6: DEC dp,X"; }
};

// DEC Decrement [Flags affected: n,z]
// DEC addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0xDE>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::DEC, State::IndexRegister::X, false>;

    // 3   9-2*m       abs,X     m.....m. . DEC $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DE: DEC addr,X");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DE: DEC addr,X"; }
};

// DEX Decrement Index Register X [Flags affected: n,z]
// DEX
// Implied (1-Byte)
template<>
struct Opcode<State, 0xCA>
{
    using Instruction = AddressMode::Implied<Operator::DE_<State::IndexRegister::X>>;

    // 1   2           imp       x.....x. . DEX
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CA: DEX");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CA: DEX"; }
};

// DEY Decrement Index Register Y [Flags affected: n,z]
// DEY
// Implied (1-Byte)
template<>
struct Opcode<State, 0x88>
{
    using Instruction = AddressMode::Implied<Operator::DE_<State::IndexRegister::Y>>;

    // 1   2           imp       x.....x. . DEY
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "88: DEY");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "88: DEY"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp,X)
// Direct Page Indexed Indirect,X (2-Byte)
template<>
struct Opcode<State, 0x41>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::EOR>;

    // 2   7-m+w       (dir,X)   m.....m. . EOR ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "41: EOR (dp,X)");

        throw NotYetImplementedException("41");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "41: EOR (dp,X)"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0x43>
{
    using Instruction = AddressMode::StackRelative<Operator::EOR>;

    // 2   5-m         stk,S     m.....m. . EOR $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "43: EOR sr,S");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "43: EOR sr,S"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x45>
{
    using Instruction = AddressMode::DirectPage<Operator::EOR>;

    // 2   4-m+w       dir       m.....m. . EOR $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "45: EOR dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "45: EOR dp"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0x47>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::EOR>;

    // 2   7-m+w       [dir]     m.....m. . EOR [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "47: EOR [dp]");

        throw NotYetImplementedException("47");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "47: EOR [dp]"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0x49>
{
    using Instruction = AddressMode::Immediate<Operator::EOR>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::EOR>;

    // 3-m 3-m         imm       m.....m. . EOR #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "49: EOR #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "49: EOR #const"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x4D>
{
    using Instruction = AddressMode::Absolute<Operator::EOR>;

    // 3   5-m         abs       m.....m. . EOR $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4D: EOR addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4D: EOR addr"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0x4F>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::EOR>;

    // 4   6-m         long      m.....m. . EOR $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4F: EOR long");

        throw NotYetImplementedException("4F");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4F: EOR long"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x51>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::EOR>;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . EOR ($10),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "51: EOR (dp),Y");

        throw NotYetImplementedException("51");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "51: EOR (dp),Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0x52>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::EOR>;

    // 2   6-m+w       (dir)     m.....m. . EOR ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "52: EOR (dp)");

        throw NotYetImplementedException("52");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "52: EOR (dp)"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x53>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::EOR>;

    // 2   8-m         (stk,S),Y m.....m. . EOR ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "53: EOR (sr,S),Y");

        throw NotYetImplementedException("53");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "53: EOR (sr,S),Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x55>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::EOR, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     m.....m. . EOR $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "55: EOR dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "55: EOR dp,X"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x57>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::EOR>;

    // 2   7-m+w       [dir],Y   m.....m. . EOR [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "57: EOR [dp],Y");

        throw NotYetImplementedException("57");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "57: EOR [dp],Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0x59>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::EOR, State::IndexRegister::Y, true>;

    // 3   6-m-x+x*p   abs,Y     m.....m. . EOR $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "59: EOR addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "59: EOR addr,Y"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x5D>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::EOR, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     m.....m. . EOR $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5D: EOR addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5D: EOR addr,X"; }
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0x5F>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::EOR>;

    // 4   6-m         long,X    m.....m. . EOR $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5F: EOR long,X");

        throw NotYetImplementedException("5F");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5F: EOR long,X"; }
};

// INC Increment [Flags affected: n,z]
// INC A
// Accumulator (1-Byte)
template<>
struct Opcode<State, 0x1A>
{
    using Instruction = AddressMode::Accumulator<Operator::INC>;

    // 1   2           acc       m.....m. . INC
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1A: INC A");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1A: INC A"; }
};

// INC Increment [Flags affected: n,z]
// INC dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xE6>
{
    using Instruction = AddressMode::DirectPage<Operator::INC>;

    // 2   7-2*m+w     dir       m.....m. . INC $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E6: INC dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E6: INC dp"; }
};

// INC Increment [Flags affected: n,z]
// INC addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xEE>
{
    using Instruction = AddressMode::Absolute<Operator::INC>;

    // 3   8-2*m       abs       m.....m. . INC $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EE: INC addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EE: INC addr"; }
};

// INC Increment [Flags affected: n,z]
// INC dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0xF6>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::INC, State::IndexRegister::X>;

    // 2   8-2*m+w     dir,X     m.....m. . INC $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F6: INC dp,X");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F6: INC dp,X"; }
};

// INC Increment [Flags affected: n,z]
// INC addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0xFE>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::INC, State::IndexRegister::X, false>;

    // 3   9-2*m       abs,X     m.....m. . INC $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FE: INC addr,X");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FE: INC addr,X"; }
};

// INX Increment Index Register X [Flags affected: n,z]
// INX
// Implied (1-Byte)
template<>
struct Opcode<State, 0xE8>
{
    using Instruction = AddressMode::Implied<Operator::IN_<State::IndexRegister::X>>;

    // 1   2           imp       x.....x. . INX
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E8: INX");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E8: INX"; }
};

// INY Increment Index Register Y [Flags affected: n,z]
// INY
// Implied (1-Byte)
template<>
struct Opcode<State, 0xC8>
{
    using Instruction = AddressMode::Implied<Operator::IN_<State::IndexRegister::Y>>;

    // 1   2           imp       x.....x. . INY
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C8: INY");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C8: INY"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x4C>
{
    using Instruction = AddressMode::Absolute_ControlFlow<Operator::JMP>;

    // 3   3           abs       ........ . JMP $1234
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4C: JMP addr");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4C: JMP addr"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0x5C>
{
    using Instruction = AddressMode::AbsoluteLong_ControlFlow<Operator::JML>;

    // 4   4           long      ........ . JMP $FEDCBA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5C: JMP long");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5C: JMP long"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr)
// Absolute Indirect (3-Byte)
template<>
struct Opcode<State, 0x6C>
{
    using Instruction = AddressMode::AbsoluteIndirect<Operator::JMP>;

    // 3   5           (abs)     ........ . JMP ($1234)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6C: JMP (addr)");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6C: JMP (addr)"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr,X)
// Absolute Indexed Indirect (3-Byte)
template<>
struct Opcode<State, 0x7C>
{
    using Instruction = AddressMode::AbsoluteIndexedIndirect<Operator::JMP>;

    // 3   6           (abs,X)   ........ . JMP ($1234,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7C: JMP (addr,X)");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7C: JMP (addr,X)"; }
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP [addr]
// Absolute Indirect Long (3-Byte)
template<>
struct Opcode<State, 0xDC>
{
    using Instruction = AddressMode::AbsoluteIndirectLong<Operator::JML>;

    // 3   6           [abs]     ........ . JMP [$1234]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DC: JMP [addr]");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DC: JMP [addr]"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x20>
{
    using Instruction = AddressMode::Absolute_ControlFlow<Operator::JSR>;

    // 3   6           abs       ........ . JSR $1234
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "20: JSR addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "20: JSR addr"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0x22>
{
    using Instruction = AddressMode::AbsoluteLong_ControlFlow<Operator::JSL>;

    // 4   8           long      ........ . JSL $123456
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "22: JSR long");

        return 8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "22: JSR long"; }
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR (addr,X)
// Absolute Indexed Indirect (3-Byte)
template<>
struct Opcode<State, 0xFC>
{
    using Instruction = AddressMode::AbsoluteIndexedIndirect<Operator::JSR>;

    // 3   8           (abs,X)   ........ . JSR ($1234,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FC: JSR (addr,X)");

        return 8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FC: JSR (addr,X)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
template<>
struct Opcode<State, 0xA1>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::LDA>;

    // 2   7-m+w       (dir,X)   m.....m. . LDA ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A1: LDA (dp,X)");

        throw NotYetImplementedException("A1");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A1: LDA (dp,X)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0xA3>
{
    using Instruction = AddressMode::StackRelative<Operator::LDA>;

    // 2   5-m         stk,S     m.....m. . LDA $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A3: LDA sr,S");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A3: LDA sr,S"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xA5>
{
    using Instruction = AddressMode::DirectPage<Operator::LDA>;

    // 2   4-m+w       dir       m.....m. . LDA $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A5: LDA dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A5: LDA dp"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0xA7>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::LDA>;

    // 2   7-m+w       [dir]     m.....m. . LDA [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A7: LDA [dp]");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A7: LDA [dp]"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0xA9>
{
    using Instruction = AddressMode::Immediate<Operator::LDA>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::LDA>;

    // 3-m 3-m         imm       m.....m. . LDA #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A9: LDA #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "A9: LDA #const"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xAD>
{
    using Instruction = AddressMode::Absolute<Operator::LDA>;

    // 3   5-m         abs       m.....m. . LDA $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AD: LDA addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AD: LDA addr"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0xAF>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::LDA>;

    // 4   6-m         long      m.....m. . LDA $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AF: LDA long");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AF: LDA long"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xB1>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::LDA>;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . LDA ($10),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B1: LDA (dp),Y");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B1: LDA (dp),Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0xB2>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::LDA>;

    // 2   6-m+w       (dir)     m.....m. . LDA ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B2: LDA (dp)");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B2: LDA (dp)"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xB3>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::LDA>;

    // 2   8-m         (stk,S),Y m.....m. . LDA ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B3: LDA (sr,S),Y");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B3: LDA (sr,S),Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0xB5>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::LDA, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     m.....m. . LDA $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B5: LDA dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B5: LDA dp,X"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xB7>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::LDA>;

    // 2   7-m+w       [dir],Y   m.....m. . LDA [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B7: LDA [dp],Y");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B7: LDA [dp],Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0xB9>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::LDA, State::IndexRegister::Y, true>;

    // 3   6-m-x+x*p   abs,Y     m.....m. . LDA $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B9: LDA addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B9: LDA addr,Y"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0xBD>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::LDA, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     m.....m. . LDA $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BD: LDA addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BD: LDA addr,X"; }
};

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0xBF>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::LDA>;

    // 4   6-m         long,X    m.....m. . LDA $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BF: LDA long,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BF: LDA long,X"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX #const
// Immediate (2-Byte [19])
template<>
struct Opcode<State, 0xA2>
{
    using Instruction = AddressMode::Immediate<Operator::LD_<State::IndexRegister::X>>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::LD_<State::IndexRegister::X>>;

    // 3-x 3-x         imm       x.....x. . LDX #$54
    // ¤19: Add 1 byte if x=0 (16-bit index registers)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A2: LDX #const");

        if (state.is16Bit(State::Flag::x))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "A2: LDX #const"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xA6>
{
    using Instruction = AddressMode::DirectPage<Operator::LD_<State::IndexRegister::X>>;

    // 2   4-x+w       dir       x.....x. . LDX $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A6: LDX dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A6: LDX dp"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xAE>
{
    using Instruction = AddressMode::Absolute<Operator::LD_<State::IndexRegister::X>>;

    // 3   5-x         abs       x.....x. . LDX $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AE: LDX addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AE: LDX addr"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp,Y
// Direct Page Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xB6>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::LD_<State::IndexRegister::X>, State::IndexRegister::Y>;

    // 2   5-x+w       dir,Y     x.....x. . LDX $10,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B6: LDX dp,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B6: LDX dp,Y"; }
};

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0xBE>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::LD_<State::IndexRegister::X>, State::IndexRegister::Y, true>;

    // 3   6-2*x+x*p   abs,Y     x.....x. . LDX $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BE: LDX addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BE: LDX addr,Y"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY #const
// Immediate (2-Byte [19])
template<>
struct Opcode<State, 0xA0>
{
    using Instruction = AddressMode::Immediate<Operator::LD_<State::IndexRegister::Y>>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::LD_<State::IndexRegister::Y>>;

    // 3-x 3-x         imm       x.....x. . LDY #$54
    // ¤19: Add 1 byte if x=0 (16-bit index registers)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A0: LDY #const");

        if (state.is16Bit(State::Flag::x))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "A0: LDY #const"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xA4>
{
    using Instruction = AddressMode::DirectPage<Operator::LD_<State::IndexRegister::Y>>;

    // 2   4-x+w       dir       x.....x. . LDY $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A4: LDY dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A4: LDY dp"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xAC>
{
    using Instruction = AddressMode::Absolute<Operator::LD_<State::IndexRegister::Y>>;

    // 3   5-x         abs       x.....x. . LDY $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AC: LDY addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AC: LDY addr"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0xB4>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::LD_<State::IndexRegister::Y>, State::IndexRegister::X>;

    // 2   5-x+w       dir,X     x.....x. . LDY $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B4: LDY dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B4: LDY dp,X"; }
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0xBC>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::LD_<State::IndexRegister::Y>, State::IndexRegister::X, true>;

    // 3   6-2*x+x*p   abs,X     x.....x. . LDY $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BC: LDY addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BC: LDY addr,X"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x46>
{
    using Instruction = AddressMode::DirectPage<Operator::LSR>;

    // 2   7-2*m+w     dir       0.....m* . LSR $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "46: LSR dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "46: LSR dp"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR A
// Accumulator (1-Byte)
template<>
struct Opcode<State, 0x4A>
{
    using Instruction = AddressMode::Accumulator<Operator::LSR>;

    // 1   2           acc       0.....m* . LSR
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4A: LSR A");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4A: LSR A"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x4E>
{
    using Instruction = AddressMode::Absolute<Operator::LSR>;

    // 3   8-2*m       abs       0.....m* . LSR $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4E: LSR addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4E: LSR addr"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x56>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::LSR, State::IndexRegister::X>;

    // 2   8-2*m+w     dir,X     0.....m* . LSR $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "56: LSR dp,X");

        throw NotYetImplementedException("56");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "56: LSR dp,X"; }
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x5E>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::LSR, State::IndexRegister::X, false>;

    // 3   9-2*m       abs,X     0.....m* . LSR $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5E: LSR addr,X");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5E: LSR addr,X"; }
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
// MVN srcbk,destbk
// Block Move (3-Byte)
template<>
struct Opcode<State, 0x54>
{
    using Instruction = AddressMode::BlockMove<Operator::MVN>;

    // 3   7           src,dest  ........ . MVN #$12,#$34
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "54: MVN srcbk,destbk");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "54: MVN srcbk,destbk"; }
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
// MVP srcbk,destbk
// Block Move (3-Byte)
template<>
struct Opcode<State, 0x44>
{
    using Instruction = AddressMode::BlockMove<Operator::MVP>;

    // 3   7           src,dest  ........ . MVP #$12,#$34
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "44: MVP srcbk,destbk");

        throw NotYetImplementedException("44");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "44: MVP srcbk,destbk"; }
};

// NOP No Operation [Flags affected: none]
// NOP
// Implied (1-Byte)
template<>
struct Opcode<State, 0xEA>
{
    using Instruction = AddressMode::Implied<Operator::NOP>;

    // 1   2           imp       ........ . NOP
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EA: NOP");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EA: NOP"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
template<>
struct Opcode<State, 0x01>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::ORA>;

    // 2   7-m+w       (dir,X)   m.....m. . ORA ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "01: ORA (dp,X)");

        throw NotYetImplementedException("01");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "01: ORA (dp,X)"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0x03>
{
    using Instruction = AddressMode::StackRelative<Operator::ORA>;

    // 2   5-m         stk,S     m.....m. . ORA $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "03: ORA sr,S");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "03: ORA sr,S"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x05>
{
    using Instruction = AddressMode::DirectPage<Operator::ORA>;

    // 2   4-m+w       dir       m.....m. . ORA $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "05: ORA dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "05: ORA dp"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0x07>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::ORA>;

    // 2   7-m+w       [dir]     m.....m. . ORA [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "07: ORA [dp]");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "07: ORA [dp]"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0x09>
{
    using Instruction = AddressMode::Immediate<Operator::ORA>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::ORA>;

    // 3-m 3-m         imm       m.....m. . ORA #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "09: ORA #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "09: ORA #const"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x0D>
{
    using Instruction = AddressMode::Absolute<Operator::ORA>;

    // 3   5-m         abs       m.....m. . ORA $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0D: ORA addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0D: ORA addr"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0x0F>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::ORA>;

    // 4   6-m         long      m.....m. . ORA $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0F: ORA long");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0F: ORA long"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x11>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::ORA>;

    // 2   7-m+w-x+x*p (dir),Y   m.....m. . ORA ($10),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "11: ORA (dp),Y");

        throw NotYetImplementedException("11");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "11: ORA (dp),Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0x12>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::ORA>;

    // 2   6-m+w       (dir)     m.....m. . ORA ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "12: ORA (dp)");

        throw NotYetImplementedException("12");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "12: ORA (dp)"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x13>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::ORA>;

    // 2   8-m         (stk,S),Y m.....m. . ORA ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "13: ORA (sr,S),Y");

        throw NotYetImplementedException("13");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "13: ORA (sr,S),Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x15>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::ORA, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     m.....m. . ORA $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "15: ORA dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "15: ORA dp,X"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x17>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::ORA>;

    // 2   7-m+w       [dir],Y   m.....m. . ORA [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "17: ORA [dp],Y");

        throw NotYetImplementedException("17");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "17: ORA [dp],Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0x19>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::ORA, State::IndexRegister::Y, true>;

    // 3   6-m-x+x*p   abs,Y     m.....m. . ORA $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "19: ORA addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "19: ORA addr,Y"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x1D>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::ORA, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     m.....m. . ORA $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1D: ORA addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1D: ORA addr,X"; }
};

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0x1F>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::ORA>;

    // 4   6-m         long,X    m.....m. . ORA $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1F: ORA long,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1F: ORA long,X"; }
};

// PEA Push Effective Absolute Address [Flags affected: none]
// PEA addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xF4>
{
    using Instruction = AddressMode::Absolute_ControlFlow<Operator::PE_<'A'>>;

    // 3   5           imm       ........ . PEA #$1234
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F4: PEA addr");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F4: PEA addr"; }
};

// PEI Push Effective Indirect Address [Flags affected: none]
// PEI (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0xD4>
{
    using Instruction = AddressMode::DirectPageIndirect_ControlFlow<Operator::PE_<'I'>>;

    // 2   6+w         dir       ........ . PEI $12
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D4: PEI (dp)");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D4: PEI (dp)"; }
};

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
// PER label
// Program Counter Relative Long (3-Byte)
template<>
struct Opcode<State, 0x62>
{
    using Instruction = AddressMode::ProgramCounterRelativeLong<Operator::PER>;

    // 3   6           imm       ........ . PER LABEL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "62: PER label");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "62: PER label"; }
};

// PHA Push Accumulator [Flags affected: none]
// PHA
// Implied (1-Byte)
template<>
struct Opcode<State, 0x48>
{
    using Instruction = AddressMode::Implied<Operator::PHA>;

    // 1   4-m         imp       ........ . PHA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "48: PHA");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "48: PHA"; }
};

// PHB Push Data Bank Register [Flags affected: none]
// PHB
// Implied (1-Byte)
template<>
struct Opcode<State, 0x8B>
{
    using Instruction = AddressMode::Implied<Operator::PHB>;

    // 1   3           imp       ........ . PHB
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8B: PHB");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8B: PHB"; }
};

// PHD Push Direct Page Register [Flags affected: none]
// PHD
// Implied (1-Byte)
template<>
struct Opcode<State, 0x0B>
{
    using Instruction = AddressMode::Implied<Operator::PHD>;

    // 1   4           imp       ........ . PHD
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0B: PHD");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0B: PHD"; }
};

// PHK Push Program Bank Register [Flags affected: none]
// PHK
// Implied (1-Byte)
template<>
struct Opcode<State, 0x4B>
{
    using Instruction = AddressMode::Implied<Operator::PHK>;

    // 1   3           imp       ........ . PHK
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4B: PHK");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4B: PHK"; }
};

// PHP Push Processor Status Register [Flags affected: none]
// PHP
// Implied (1-Byte)
template<>
struct Opcode<State, 0x08>
{
    using Instruction = AddressMode::Implied<Operator::PHP>;

    // 1   3           imp       ........ . PHP
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "08: PHP");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "08: PHP"; }
};

// PHX Push Index Register X [Flags affected: none]
// PHX
// Implied (1-Byte)
template<>
struct Opcode<State, 0xDA>
{
    using Instruction = AddressMode::Implied<Operator::PH_<State::IndexRegister::X>>;

    // 1   4-x         imp       ........ . PHX
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DA: PHX");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DA: PHX"; }
};

// PHY Push Index Register Y [Flags affected: none]
// PHY
// Implied (1-Byte)
template<>
struct Opcode<State, 0x5A>
{
    using Instruction = AddressMode::Implied<Operator::PH_<State::IndexRegister::Y>>;

    // 1   4-x         imp       ........ . PHY
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5A: PHY");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5A: PHY"; }
};

// PLA Pull Accumulator [Flags affected: n,z]
// PLA
// Implied (1-Byte)
template<>
struct Opcode<State, 0x68>
{
    using Instruction = AddressMode::Implied<Operator::PLA>;

    // 1   5-m         imp       m.....m. . PLA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "68: PLA");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "68: PLA"; }
};

// PLB Pull Data Bank Register [Flags affected: n,z]
// PLB
// Implied (1-Byte)
template<>
struct Opcode<State, 0xAB>
{
    using Instruction = AddressMode::Implied<Operator::PLB>;

    // 1   4           imp       *.....*. . PLB
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AB: PLB");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AB: PLB"; }
};

// PLD Pull Direct Page Register [Flags affected: n,z]
// PLD
// Implied (1-Byte)
template<>
struct Opcode<State, 0x2B>
{
    using Instruction = AddressMode::Implied<Operator::PLD>;

    // 1   5           imp       *.....*. . PLD
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2B: PLD");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2B: PLD"; }
};

// PLP Pull Processor Status Register [Flags affected: n,z]
// PLP
// Implied (1-Byte)
template<>
struct Opcode<State, 0x28>
{
    using Instruction = AddressMode::Implied<Operator::PLP>;

    // 1   4           imp       ******** . PLP
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "28: PLP");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "28: PLP"; }
};

// PLX Pull Index Register X [Flags affected: n,z]
// PLX
// Implied (1-Byte)
template<>
struct Opcode<State, 0xFA>
{
    using Instruction = AddressMode::Implied<Operator::PL_<State::IndexRegister::X>>;

    // 1   5-x         imp       x.....x. . PLX
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FA: PLX");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FA: PLX"; }
};

// PLY Pull Index Register Y [Flags affected: n,z]
// PLY
// Implied (1-Byte)
template<>
struct Opcode<State, 0x7A>
{
    using Instruction = AddressMode::Implied<Operator::PL_<State::IndexRegister::Y>>;

    // 1   5-x         imp       x.....x. . PLY
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7A: PLY");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7A: PLY"; }
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
// REP #const
// Immediate (2-Byte)
template<>
struct Opcode<State, 0xC2>
{
    using Instruction = AddressMode::Immediate<Operator::REP>;

    // 2   3           imm       ******** . REP #$12
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C2: REP #const");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C2: REP #const"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x26>
{
    using Instruction = AddressMode::DirectPage<Operator::ROL>;

    // 2   7-2*m+w     dir       m.....mm . ROL $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "26: ROL dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "26: ROL dp"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL A
// Accumulator (1-Byte)
template<>
struct Opcode<State, 0x2A>
{
    using Instruction = AddressMode::Accumulator<Operator::ROL>;

    // 1   2           acc       m.....mm . ROL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2A: ROL A");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2A: ROL A"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x2E>
{
    using Instruction = AddressMode::Absolute<Operator::ROL>;

    // 3   8-2*m       abs       m.....mm . ROL $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2E: ROL addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2E: ROL addr"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x36>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::ROL, State::IndexRegister::X>;

    // 2   8-2*m+w     dir,X     m.....mm . ROL $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "36: ROL dp,X");

        throw NotYetImplementedException("36");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "36: ROL dp,X"; }
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x3E>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::ROL, State::IndexRegister::X, false>;

    // 3   9-2*m       abs,X     m.....mm . ROL $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3E: ROL addr,X");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3E: ROL addr,X"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x66>
{
    using Instruction = AddressMode::DirectPage<Operator::ROR>;

    // 2   7-2*m+w     dir       m.....m* . ROR $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "66: ROR dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "66: ROR dp"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR A
// Accumulator (1-Byte)
template<>
struct Opcode<State, 0x6A>
{
    using Instruction = AddressMode::Accumulator<Operator::ROR>;

    // 1   2           acc       m.....m* . ROR
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6A: ROR A");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6A: ROR A"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x6E>
{
    using Instruction = AddressMode::Absolute<Operator::ROR>;

    // 3   8-2*m       abs       m.....m* . ROR $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6E: ROR addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6E: ROR addr"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x76>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::ROR, State::IndexRegister::X>;

    // 2   8-2*m+w     dir,X     m.....m* . ROR $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "76: ROR dp,X");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "76: ROR dp,X"; }
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x7E>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::ROR, State::IndexRegister::X, false>;

    // 3   9-2*m       abs,X     m.....m* . ROR $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7E: ROR addr,X");

        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7E: ROR addr,X"; }
};

// RTI Return from Interrupt [Flags affected: all except b]
// RTI
// Implied (1-Byte)
template<>
struct Opcode<State, 0x40>
{
    using Instruction = AddressMode::Implied<Operator::RTI>;

    // 1   7-e         imp       ******** . RTI
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "40: RTI");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "40: RTI"; }
};

// RTL Return from Subroutine Long [Flags affected: none]
// RTL
// Implied (1-Byte)
template<>
struct Opcode<State, 0x6B>
{
    using Instruction = AddressMode::Implied<Operator::RTL>;

    // 1   6           imp       ........ . RTL
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6B: RTL");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6B: RTL"; }
};

// RTS Return from Subroutine [Flags affected: none]
// RTS
// Implied (1-Byte)
template<>
struct Opcode<State, 0x60>
{
    using Instruction = AddressMode::Implied<Operator::RTS>;

    // 1   6           imp       ........ . RTS
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "60: RTS");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "60: RTS"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
template<>
struct Opcode<State, 0xE1>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::SBC>;

    // 2   7-m+w       (dir,X)   mm....mm . SBC ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E1: SBC (dp,X)");

        throw NotYetImplementedException("E1");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E1: SBC (dp,X)"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0xE3>
{
    using Instruction = AddressMode::StackRelative<Operator::SBC>;

    // 2   5-m         stk,S     mm....mm . SBC $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E3: SBC sr,S");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E3: SBC sr,S"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0xE5>
{
    using Instruction = AddressMode::DirectPage<Operator::SBC>;

    // 2   4-m+w       dir       mm....mm . SBC $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E5: SBC dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E5: SBC dp"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0xE7>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::SBC>;

    // 2   7-m+w       [dir]     mm....mm . SBC [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E7: SBC [dp]");

        throw NotYetImplementedException("E7");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E7: SBC [dp]"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC #const
// Immediate (2-Byte [17])
template<>
struct Opcode<State, 0xE9>
{
    using Instruction = AddressMode::Immediate<Operator::SBC>;
    using Instruction16Bit = AddressMode::Immediate16Bit<Operator::SBC>;

    // 3-m 3-m         imm       mm....mm . SBC #$54
    // ¤17: Add 1 byte if m=0 (16-bit memory/accumulator)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E9: SBC #const");

        if (state.is16Bit(State::Flag::m))
        {
                return 2 + Instruction16Bit::Type::applyOperand<Instruction16Bit>(state);
        }
        else
        {
                return 2 + Instruction::Type::applyOperand<Instruction>(state);
        }
    }

    static std::string opcodeToString() { return "E9: SBC #const"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xED>
{
    using Instruction = AddressMode::Absolute<Operator::SBC>;

    // 3   5-m         abs       mm....mm . SBC $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "ED: SBC addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "ED: SBC addr"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0xEF>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::SBC>;

    // 4   6-m         long      mm....mm . SBC $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EF: SBC long");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EF: SBC long"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xF1>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::SBC>;

    // 2   7-m+w-x+x*p (dir),Y   mm....mm . SBC ($10),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F1: SBC (dp),Y");

        throw NotYetImplementedException("F1");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F1: SBC (dp),Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0xF2>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::SBC>;

    // 2   6-m+w       (dir)     mm....mm . SBC ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F2: SBC (dp)");

        throw NotYetImplementedException("F2");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F2: SBC (dp)"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xF3>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::SBC>;

    // 2   8-m         (stk,S),Y mm....mm . SBC ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F3: SBC (sr,S),Y");

        throw NotYetImplementedException("F3");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F3: SBC (sr,S),Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0xF5>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::SBC, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     mm....mm . SBC $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F5: SBC dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F5: SBC dp,X"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0xF7>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::SBC>;

    // 2   7-m+w       [dir],Y   mm....mm . SBC [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F7: SBC [dp],Y");

        throw NotYetImplementedException("F7");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F7: SBC [dp],Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0xF9>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::SBC, State::IndexRegister::Y, true>;

    // 3   6-m-x+x*p   abs,Y     mm....mm . SBC $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F9: SBC addr,Y");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F9: SBC addr,Y"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0xFD>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::SBC, State::IndexRegister::X, true>;

    // 3   6-m-x+x*p   abs,X     mm....mm . SBC $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FD: SBC addr,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FD: SBC addr,X"; }
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0xFF>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::SBC>;

    // 4   6-m         long,X    mm....mm . SBC $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FF: SBC long,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FF: SBC long,X"; }
};

// SEC Set Carry Flag [Flags affected: c]
// SEC
// Implied (1-Byte)
template<>
struct Opcode<State, 0x38>
{
    using Instruction = AddressMode::Implied<Operator::SE_<State::Flag::c, true>>;

    // 1   2           imp       .......1 . SEC
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "38: SEC");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "38: SEC"; }
};

// SED Set Decimal Flag [Flags affected: d]
// SED
// Implied (1-Byte)
template<>
struct Opcode<State, 0xF8>
{
    using Instruction = AddressMode::Implied<Operator::SE_<State::Flag::d, true>>;

    // 1   2           imp       ....1... . SED
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F8: SED");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F8: SED"; }
};

// SEI Set Interrupt Disable Flag [Flags affected: i]
// SEI
// Implied (1-Byte)
template<>
struct Opcode<State, 0x78>
{
    using Instruction = AddressMode::Implied<Operator::SE_<State::Flag::i, true>>;

    // 1   2           imp       .....1.. . SEI
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "78: SEI");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "78: SEI"; }
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
// SEP #const
// Immediate (2-Byte)
template<>
struct Opcode<State, 0xE2>
{
    using Instruction = AddressMode::Immediate<Operator::SEP>;

    // 2   3           imm       ******** . SEP #$12
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E2: SEP #const");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E2: SEP #const"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp,X)
// Direct Page Indexed Indirect, X (2-Byte)
template<>
struct Opcode<State, 0x81>
{
    using Instruction = AddressMode::DirectPageIndexedIndirectX<Operator::STA>;

    // 2   7-m+w       (dir,X)   ........ . STA ($10,X)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "81: STA (dp,X)");

        throw NotYetImplementedException("81");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "81: STA (dp,X)"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA sr,S
// Stack Relative (2-Byte)
template<>
struct Opcode<State, 0x83>
{
    using Instruction = AddressMode::StackRelative<Operator::STA>;

    // 2   5-m         stk,S     ........ . STA $32,S
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "83: STA sr,S");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "83: STA sr,S"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x85>
{
    using Instruction = AddressMode::DirectPage<Operator::STA>;

    // 2   4-m+w       dir       ........ . STA $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "85: STA dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "85: STA dp"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp]
// Direct Page Indirect Long (2-Byte)
template<>
struct Opcode<State, 0x87>
{
    using Instruction = AddressMode::DirectPageIndirectLong<Operator::STA>;

    // 2   7-m+w       [dir]     ........ . STA [$10]
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "87: STA [dp]");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "87: STA [dp]"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x8D>
{
    using Instruction = AddressMode::Absolute<Operator::STA>;

    // 3   5-m         abs       ........ . STA $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8D: STA addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8D: STA addr"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long
// Absolute Long (4-Byte)
template<>
struct Opcode<State, 0x8F>
{
    using Instruction = AddressMode::AbsoluteLong<Operator::STA>;

    // 4   6-m         long      ........ . STA $FEDBCA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8F: STA long");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8F: STA long"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp),Y
// Direct Page Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x91>
{
    using Instruction = AddressMode::DirectPageIndirectIndexedY<Operator::STA>;

    // 2   7-m+w       (dir),Y   ........ . STA ($10),Y
    // §20: TODO manually add exception for 3
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "91: STA (dp),Y");

        throw NotYetImplementedException("TODO20");
        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "91: STA (dp),Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp)
// Direct Page Indirect (2-Byte)
template<>
struct Opcode<State, 0x92>
{
    using Instruction = AddressMode::DirectPageIndirect<Operator::STA>;

    // 2   6-m+w       (dir)     ........ . STA ($10)
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "92: STA (dp)");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "92: STA (dp)"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA (sr,S),Y
// Stack Relative Indirect Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x93>
{
    using Instruction = AddressMode::StackRelativeIndirectIndexedY<Operator::STA>;

    // 2   8-m         (stk,S),Y ........ . STA ($32,S),Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "93: STA (sr,S),Y");

        throw NotYetImplementedException("93");
        return 7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "93: STA (sr,S),Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x95>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::STA, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     ........ . STA $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "95: STA dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "95: STA dp,X"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp],Y
// Direct Page Indirect Long Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x97>
{
    using Instruction = AddressMode::DirectPageIndirectLongIndexedY<Operator::STA>;

    // 2   7-m+w       [dir],Y   ........ . STA [$10],Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "97: STA [dp],Y");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "97: STA [dp],Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,Y
// Absolute Indexed, Y (3-Byte)
template<>
struct Opcode<State, 0x99>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::STA, State::IndexRegister::Y, false>;

    // 3   6-m         abs,Y     ........ . STA $9876,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "99: STA addr,Y");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "99: STA addr,Y"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x9D>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::STA, State::IndexRegister::X, false>;

    // 3   6-m         abs,X     ........ . STA $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9D: STA addr,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9D: STA addr,X"; }
};

// STA Store Accumulator to Memory [Flags affected: none]
// STA long,X
// Absolute Long Indexed, X (4-Byte)
template<>
struct Opcode<State, 0x9F>
{
    using Instruction = AddressMode::AbsoluteLongIndexedX<Operator::STA>;

    // 4   6-m         long,X    ........ . STA $FEDCBA,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9F: STA long,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9F: STA long,X"; }
};

// STP Stop Processor [Flags affected: none]
// STP
// Implied (1-Byte)
template<>
struct Opcode<State, 0xDB>
{
    using Instruction = AddressMode::Implied<Operator::STP>;

    // 1   3           imp       ........ . STP
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DB: STP");

        throw NotYetImplementedException("DB");
        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DB: STP"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x86>
{
    using Instruction = AddressMode::DirectPage<Operator::ST_<State::IndexRegister::X>>;

    // 2   4-x+w       dir       ........ . STX $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "86: STX dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "86: STX dp"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x8E>
{
    using Instruction = AddressMode::Absolute<Operator::ST_<State::IndexRegister::X>>;

    // 3   5-x         abs       ........ . STX $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8E: STX addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8E: STX addr"; }
};

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp,Y
// Direct Page Indexed, Y (2-Byte)
template<>
struct Opcode<State, 0x96>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::ST_<State::IndexRegister::X>, State::IndexRegister::Y>;

    // 2   5-x+w       dir,Y     ........ . STX $10,Y
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "96: STX dp,Y");

        throw NotYetImplementedException("96");
        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "96: STX dp,Y"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x84>
{
    using Instruction = AddressMode::DirectPage<Operator::ST_<State::IndexRegister::Y>>;

    // 2   4-x+w       dir       ........ . STY $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "84: STY dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "84: STY dp"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x8C>
{
    using Instruction = AddressMode::Absolute<Operator::ST_<State::IndexRegister::Y>>;

    // 3   5-x         abs       ........ . STY $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8C: STY addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8C: STY addr"; }
};

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x94>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::ST_<State::IndexRegister::Y>, State::IndexRegister::X>;

    // 2   5-x+w       dir,X     ........ . STY $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "94: STY dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "94: STY dp,X"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x64>
{
    using Instruction = AddressMode::DirectPage<Operator::STZ>;

    // 2   4-m+w       dir       ........ . STZ $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "64: STZ dp");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "64: STZ dp"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp,X
// Direct Page Indexed, X (2-Byte)
template<>
struct Opcode<State, 0x74>
{
    using Instruction = AddressMode::DirectPageIndexed<Operator::STZ, State::IndexRegister::X>;

    // 2   5-m+w       dir,X     ........ . STZ $10,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "74: STZ dp,X");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "74: STZ dp,X"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x9C>
{
    using Instruction = AddressMode::Absolute<Operator::STZ>;

    // 3   5-m         abs       ........ . STZ $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9C: STZ addr");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9C: STZ addr"; }
};

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr,X
// Absolute Indexed, X (3-Byte)
template<>
struct Opcode<State, 0x9E>
{
    using Instruction = AddressMode::AbsoluteIndexed<Operator::STZ, State::IndexRegister::X, false>;

    // 3   6-m         abs,X     ........ . STZ $9876,X
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9E: STZ addr,X");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9E: STZ addr,X"; }
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
// TAX
// Implied (1-Byte)
template<>
struct Opcode<State, 0xAA>
{
    using Instruction = AddressMode::Implied<Operator::TA_<State::IndexRegister::X>>;

    // 1   2           imp       x.....x. . TAX
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AA: TAX");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AA: TAX"; }
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
// TAY
// Implied (1-Byte)
template<>
struct Opcode<State, 0xA8>
{
    using Instruction = AddressMode::Implied<Operator::TA_<State::IndexRegister::Y>>;

    // 1   2           imp       x.....x. . TAY
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A8: TAY");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A8: TAY"; }
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
// TCD
// Implied (1-Byte)
template<>
struct Opcode<State, 0x5B>
{
    using Instruction = AddressMode::Implied<Operator::TCD>;

    // 1   2           imp       *.....*. . TCD
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5B: TCD");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5B: TCD"; }
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
// TCS
// Implied (1-Byte)
template<>
struct Opcode<State, 0x1B>
{
    using Instruction = AddressMode::Implied<Operator::TCS>;

    // 1   2           imp       ........ . TCS
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1B: TCS");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1B: TCS"; }
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
// TDC
// Implied (1-Byte)
template<>
struct Opcode<State, 0x7B>
{
    using Instruction = AddressMode::Implied<Operator::TDC>;

    // 1   2           imp       *.....*. . TDC
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7B: TDC");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7B: TDC"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x14>
{
    using Instruction = AddressMode::DirectPage<Operator::TRB>;

    // 2   7-2*m+w     dir       ......m. . TRB $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "14: TRB dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "14: TRB dp"; }
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x1C>
{
    using Instruction = AddressMode::Absolute<Operator::TRB>;

    // 3   8-2*m       abs       ......m. . TRB $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1C: TRB addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1C: TRB addr"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB dp
// Direct Page (2-Byte)
template<>
struct Opcode<State, 0x04>
{
    using Instruction = AddressMode::DirectPage<Operator::TSB>;

    // 2   7-2*m+w     dir       ......m. . TSB $10
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "04: TSB dp");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "04: TSB dp"; }
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB addr
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x0C>
{
    using Instruction = AddressMode::Absolute<Operator::TSB>;

    // 3   8-2*m       abs       ......m. . TSB $9876
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0C: TSB addr");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0C: TSB addr"; }
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
// TSC
// Implied (1-Byte)
template<>
struct Opcode<State, 0x3B>
{
    using Instruction = AddressMode::Implied<Operator::TSC>;

    // 1   2           imp       *.....*. . TSC
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3B: TSC");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3B: TSC"; }
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
// TSX
// Implied (1-Byte)
template<>
struct Opcode<State, 0xBA>
{
    using Instruction = AddressMode::Implied<Operator::TSX>;

    // 1   2           imp       x.....x. . TSX
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BA: TSX");

        throw NotYetImplementedException("BA");
        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BA: TSX"; }
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
// TXA
// Implied (1-Byte)
template<>
struct Opcode<State, 0x8A>
{
    using Instruction = AddressMode::Implied<Operator::T_A<State::IndexRegister::X>>;

    // 1   2           imp       m.....m. . TXA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8A: TXA");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8A: TXA"; }
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
// TXS
// Implied (1-Byte)
template<>
struct Opcode<State, 0x9A>
{
    using Instruction = AddressMode::Implied<Operator::TXS>;

    // 1   2           imp       ........ . TXS
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9A: TXS");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9A: TXS"; }
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
// TXY
// Implied (1-Byte)
template<>
struct Opcode<State, 0x9B>
{
    using Instruction = AddressMode::Implied<Operator::T__<State::IndexRegister::X, State::IndexRegister::Y>>;

    // 1   2           imp       x.....x. . TXY
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9B: TXY");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9B: TXY"; }
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
// TYA
// Implied (1-Byte)
template<>
struct Opcode<State, 0x98>
{
    using Instruction = AddressMode::Implied<Operator::T_A<State::IndexRegister::Y>>;

    // 1   2           imp       m.....m. . TYA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "98: TYA");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "98: TYA"; }
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
// TYX
// Implied (1-Byte)
template<>
struct Opcode<State, 0xBB>
{
    using Instruction = AddressMode::Implied<Operator::T__<State::IndexRegister::Y, State::IndexRegister::X>>;

    // 1   2           imp       x.....x. . TYX
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BB: TYX");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BB: TYX"; }
};

// WAI Wait for Interrupt [Flags affected: none]
// WAI
// Implied (1-Byte)
template<>
struct Opcode<State, 0xCB>
{
    using Instruction = AddressMode::Implied<Operator::WAI>;

    // 1   3           imp       ........ . WAI
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CB: WAI");

        throw NotYetImplementedException("CB");
        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CB: WAI"; }
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
// WDM #const
// Immediate (2-Byte)
template<>
struct Opcode<State, 0x42>
{
    using Instruction = AddressMode::Immediate<Operator::WDM>;

    // 2   2           imm       ........ . WDM
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "42: WDM #const");

        throw NotYetImplementedException("42");
        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "42: WDM #const"; }
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
// XBA
// Implied (1-Byte)
template<>
struct Opcode<State, 0xEB>
{
    using Instruction = AddressMode::Implied<Operator::XBA>;

    // 1   3           imp       *.....*. . XBA
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EB: XBA");

        return 3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EB: XBA"; }
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
// XCE
// Implied (1-Byte)
template<>
struct Opcode<State, 0xFB>
{
    using Instruction = AddressMode::Implied<Operator::XCE>;

    // 1   2           imp       .......* * XCE
    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FB: XCE");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FB: XCE"; }
};

}
