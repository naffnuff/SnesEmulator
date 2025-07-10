#pragma once

#include "Exception.h"
#include "SpcState.h"
#include "SpcAddressMode.h"
#include "SpcOperator.h"

#include "Profiler.h"

#define PROFILE_OPCODES false

namespace SPC {

EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)

CREATE_PROFILER();

// ADC (X), (Y)
// (X) = (X)+(Y)+C    	[NV..H.ZC]
// Indirect Indirect (1-Byte)
template<>
struct Opcode<State, 0x99>
{
    using Instruction = AddressMode::IndirectIndirect<Operator::ADC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "99: ADC (X), (Y)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x99>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "99: ADC (X), (Y)"; }
};

// ADC A, #i
// A = A+i+C    	[NV..H.ZC]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0x88>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::ADC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "88: ADC A, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "88: ADC A, #i"; }
};

// ADC A, (X)
// A = A+(X)+C    	[NV..H.ZC]
// Register Register Indirect (1-Byte)
template<>
struct Opcode<State, 0x86>
{
    using Instruction = AddressMode::RegisterRegisterIndirect<Operator::ADC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "86: ADC A, (X)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x86>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "86: ADC A, (X)"; }
};

// ADC A, [d]+Y
// A = A+([d]+Y)+C    	[NV..H.ZC]
// Register Direct Indirect Indexed (2-Byte)
template<>
struct Opcode<State, 0x97>
{
    using Instruction = AddressMode::RegisterDirectIndirectIndexed<Operator::ADC, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "97: ADC A, [d]+Y");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "97: ADC A, [d]+Y"; }
};

// ADC A, [d+X]
// A = A+([d+X])+C    	[NV..H.ZC]
// Register Direct Indexed Indirect (2-Byte)
template<>
struct Opcode<State, 0x87>
{
    using Instruction = AddressMode::RegisterDirectIndexedIndirect<Operator::ADC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "87: ADC A, [d+X]");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x87>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "87: ADC A, [d+X]"; }
};

// ADC A, d
// A = A+(d)+C    	[NV..H.ZC]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0x84>
{
    using Instruction = AddressMode::RegisterDirect<Operator::ADC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "84: ADC A, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "84: ADC A, d"; }
};

// ADC A, d+X
// A = A+(d+X)+C    	[NV..H.ZC]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x94>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::ADC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "94: ADC A, d+X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "94: ADC A, d+X"; }
};

// ADC A, !a
// A = A+(a)+C    	[NV..H.ZC]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0x85>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::ADC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "85: ADC A, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "85: ADC A, !a"; }
};

// ADC A, !a+X
// A = A+(a+X)+C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x95>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::ADC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "95: ADC A, !a+X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "95: ADC A, !a+X"; }
};

// ADC A, !a+Y
// A = A+(a+Y)+C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x96>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::ADC, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "96: ADC A, !a+Y");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "96: ADC A, !a+Y"; }
};

// ADC dd, ds
// (dd) = (dd)+(d)+C    	[NV..H.ZC]
// Direct Direct (3-Byte)
template<>
struct Opcode<State, 0x89>
{
    using Instruction = AddressMode::DirectDirect<Operator::ADC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "89: ADC dd, ds");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x89>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "89: ADC dd, ds"; }
};

// ADC d, #i
// (d) = (d)+i+C    	[NV..H.ZC]
// Direct Immediate (3-Byte)
template<>
struct Opcode<State, 0x98>
{
    using Instruction = AddressMode::DirectImmediate<Operator::ADC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "98: ADC d, #i");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "98: ADC d, #i"; }
};

// ADDW YA, d
// YA  = YA + (d), H on high byte    	[NV..H.ZC]
// Y Accumulator Direct (2-Byte)
template<>
struct Opcode<State, 0x7A>
{
    using Instruction = AddressMode::YAccumulatorDirect<Operator::ADDW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7A: ADDW YA, d");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7A: ADDW YA, d"; }
};

// AND (X), (Y)
// (X) = (X) & (Y)    	[N.....Z.]
// Indirect Indirect (1-Byte)
template<>
struct Opcode<State, 0x39>
{
    using Instruction = AddressMode::IndirectIndirect<Operator::AND>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "39: AND (X), (Y)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x39>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "39: AND (X), (Y)"; }
};

// AND A, #i
// A = A & i    	[N.....Z.]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0x28>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::AND, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "28: AND A, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "28: AND A, #i"; }
};

// AND A, (X)
// A = A & (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
template<>
struct Opcode<State, 0x26>
{
    using Instruction = AddressMode::RegisterRegisterIndirect<Operator::AND, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "26: AND A, (X)");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "26: AND A, (X)"; }
};

// AND A, [d]+Y
// A = A & ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
template<>
struct Opcode<State, 0x37>
{
    using Instruction = AddressMode::RegisterDirectIndirectIndexed<Operator::AND, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "37: AND A, [d]+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x37>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "37: AND A, [d]+Y"; }
};

// AND A, [d+X]
// A = A & ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
template<>
struct Opcode<State, 0x27>
{
    using Instruction = AddressMode::RegisterDirectIndexedIndirect<Operator::AND, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "27: AND A, [d+X]");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x27>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "27: AND A, [d+X]"; }
};

// AND A, d
// A = A & (d)    	[N.....Z.]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0x24>
{
    using Instruction = AddressMode::RegisterDirect<Operator::AND, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "24: AND A, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "24: AND A, d"; }
};

// AND A, d+X
// A = A & (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x34>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::AND, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "34: AND A, d+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x34>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "34: AND A, d+X"; }
};

// AND A, !a
// A = A & (a)    	[N.....Z.]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0x25>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::AND, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "25: AND A, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "25: AND A, !a"; }
};

// AND A, !a+X
// A = A & (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x35>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::AND, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "35: AND A, !a+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x35>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "35: AND A, !a+X"; }
};

// AND A, !a+Y
// A = A & (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x36>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::AND, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "36: AND A, !a+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x36>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "36: AND A, !a+Y"; }
};

// AND dd, ds
// (dd) = (dd) & (ds)    	[N.....Z.]
// Direct Direct (3-Byte)
template<>
struct Opcode<State, 0x29>
{
    using Instruction = AddressMode::DirectDirect<Operator::AND>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "29: AND dd, ds");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "29: AND dd, ds"; }
};

// AND d, #i
// (d) = (d) & i    	[N.....Z.]
// Direct Immediate (3-Byte)
template<>
struct Opcode<State, 0x38>
{
    using Instruction = AddressMode::DirectImmediate<Operator::AND>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "38: AND d, #i");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x38>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "38: AND d, #i"; }
};

// AND1 C, /m.b
// C = C & ~(m.b)    	[.......C]
// Carry Negated Memory Bit (3-Byte)
template<>
struct Opcode<State, 0x6A>
{
    using Instruction = AddressMode::CarryNegatedMemoryBit<Operator::AND1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6A: AND1 C, /m.b");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x6A>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6A: AND1 C, /m.b"; }
};

// AND1 C, m.b
// C = C & (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
template<>
struct Opcode<State, 0x4A>
{
    using Instruction = AddressMode::CarryMemoryBit<Operator::AND1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4A: AND1 C, m.b");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x4A>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4A: AND1 C, m.b"; }
};

// ASL A
// Left shift A: high->C, 0->low    	[N.....ZC]
// Register (1-Byte)
template<>
struct Opcode<State, 0x1C>
{
    using Instruction = AddressMode::Register<Operator::ASL, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1C: ASL A");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1C: ASL A"; }
};

// ASL d
// Left shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x0B>
{
    using Instruction = AddressMode::Direct<Operator::ASL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0B: ASL d");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0B: ASL d"; }
};

// ASL d+X
// Left shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x1B>
{
    using Instruction = AddressMode::DirectIndexed<Operator::ASL, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1B: ASL d+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x1B>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1B: ASL d+X"; }
};

// ASL !a
// Left shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x0C>
{
    using Instruction = AddressMode::Absolute<Operator::ASL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0C: ASL !a");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0C: ASL !a"; }
};

// BBC d.0, r
// PC+=r  if d.0 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x13>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<0, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "13: BBC d.0, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "13: BBC d.0, r"; }
};

// BBC d.1, r
// PC+=r  if d.1 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x33>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<1, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "33: BBC d.1, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "33: BBC d.1, r"; }
};

// BBC d.2, r
// PC+=r  if d.2 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x53>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<2, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "53: BBC d.2, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x53>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "53: BBC d.2, r"; }
};

// BBC d.3, r
// PC+=r  if d.3 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x73>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<3, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "73: BBC d.3, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x73>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "73: BBC d.3, r"; }
};

// BBC d.4, r
// PC+=r  if d.4 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x93>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<4, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "93: BBC d.4, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x93>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "93: BBC d.4, r"; }
};

// BBC d.5, r
// PC+=r  if d.5 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0xB3>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<5, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B3: BBC d.5, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B3: BBC d.5, r"; }
};

// BBC d.6, r
// PC+=r  if d.6 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0xD3>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<6, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D3: BBC d.6, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xD3>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D3: BBC d.6, r"; }
};

// BBC d.7, r
// PC+=r  if d.7 == 0    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0xF3>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<7, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F3: BBC d.7, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F3: BBC d.7, r"; }
};

// BBS d.0, r
// PC+=r  if d.0 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x03>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<0, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "03: BBS d.0, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x03>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "03: BBS d.0, r"; }
};

// BBS d.1, r
// PC+=r  if d.1 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x23>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<1, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "23: BBS d.1, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "23: BBS d.1, r"; }
};

// BBS d.2, r
// PC+=r  if d.2 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x43>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<2, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "43: BBS d.2, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x43>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "43: BBS d.2, r"; }
};

// BBS d.3, r
// PC+=r  if d.3 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x63>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<3, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "63: BBS d.3, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x63>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "63: BBS d.3, r"; }
};

// BBS d.4, r
// PC+=r  if d.4 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x83>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<4, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "83: BBS d.4, r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x83>");
        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "83: BBS d.4, r"; }
};

// BBS d.5, r
// PC+=r  if d.5 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0xA3>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<5, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A3: BBS d.5, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A3: BBS d.5, r"; }
};

// BBS d.6, r
// PC+=r  if d.6 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0xC3>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<6, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C3: BBS d.6, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C3: BBS d.6, r"; }
};

// BBS d.7, r
// PC+=r  if d.7 == 1    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0xE3>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::BB_<7, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E3: BBS d.7, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E3: BBS d.7, r"; }
};

// BCC r
// PC+=r  if C == 0    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x90>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::B__<State::Flag::c, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "90: BCC r");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "90: BCC r"; }
};

// BCS r
// PC+=r  if C == 1    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0xB0>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::B__<State::Flag::c, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B0: BCS r");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B0: BCS r"; }
};

// BEQ r
// PC+=r  if Z == 1    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0xF0>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BEQ>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F0: BEQ r");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F0: BEQ r"; }
};

// BMI r
// PC+=r  if N == 1    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x30>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BMI>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "30: BMI r");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "30: BMI r"; }
};

// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0xD0>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BNE>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D0: BNE r");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D0: BNE r"; }
};

// BPL r
// PC+=r  if N == 0    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x10>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BPL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "10: BPL r");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "10: BPL r"; }
};

// BVC r
// PC+=r  if V == 0    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x50>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::B__<State::Flag::v, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "50: BVC r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x50>");
        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "50: BVC r"; }
};

// BVS r
// PC+=r  if V == 1    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x70>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::B__<State::Flag::v, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "70: BVS r");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x70>");
        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "70: BVS r"; }
};

// BRA r
// PC+=r    	[........]
// Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0x2F>
{
    using Instruction = AddressMode::ProgramCounterRelative<Operator::BRA>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2F: BRA r");

        return 2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2F: BRA r"; }
};

// BRK 
// Push PC and Flags, PC = [$FFDE]    	[...1.0..]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x0F>
{
    using Instruction = AddressMode::Implied<Operator::BRK>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0F: BRK ");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x0F>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0F: BRK "; }
};

// CALL !a
// (SP--)=PCh, (SP--)=PCl, PC=a    	[........]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x3F>
{
    using Instruction = AddressMode::Absolute_ControlFlow<Operator::CALL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3F: CALL !a");

        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3F: CALL !a"; }
};

// CBNE d+X, r
// CMP A, (d+X) then BNE    	[........]
// Direct Indexed Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0xDE>
{
    using Instruction = AddressMode::DirectIndexedProgramCounterRelative<Operator::CBNE, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DE: CBNE d+X, r");

        return 6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DE: CBNE d+X, r"; }
};

// CBNE d, r
// CMP A, (d) then BNE    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x2E>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::CBNE>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2E: CBNE d, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2E: CBNE d, r"; }
};

// CLR1 d.0
// d.0 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x12>
{
    using Instruction = AddressMode::Direct<Operator::SET1<0, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "12: CLR1 d.0");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "12: CLR1 d.0"; }
};

// CLR1 d.1
// d.1 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x32>
{
    using Instruction = AddressMode::Direct<Operator::SET1<1, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "32: CLR1 d.1");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "32: CLR1 d.1"; }
};

// CLR1 d.2
// d.2 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x52>
{
    using Instruction = AddressMode::Direct<Operator::SET1<2, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "52: CLR1 d.2");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x52>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "52: CLR1 d.2"; }
};

// CLR1 d.3
// d.3 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x72>
{
    using Instruction = AddressMode::Direct<Operator::SET1<3, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "72: CLR1 d.3");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "72: CLR1 d.3"; }
};

// CLR1 d.4
// d.4 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x92>
{
    using Instruction = AddressMode::Direct<Operator::SET1<4, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "92: CLR1 d.4");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "92: CLR1 d.4"; }
};

// CLR1 d.5
// d.5 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0xB2>
{
    using Instruction = AddressMode::Direct<Operator::SET1<5, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B2: CLR1 d.5");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B2: CLR1 d.5"; }
};

// CLR1 d.6
// d.6 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0xD2>
{
    using Instruction = AddressMode::Direct<Operator::SET1<6, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D2: CLR1 d.6");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D2: CLR1 d.6"; }
};

// CLR1 d.7
// d.7 = 0    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0xF2>
{
    using Instruction = AddressMode::Direct<Operator::SET1<7, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F2: CLR1 d.7");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F2: CLR1 d.7"; }
};

// CLRC 
// C = 0    	[.......0]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x60>
{
    using Instruction = AddressMode::Implied<Operator::SET<State::Flag::c, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "60: CLRC ");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "60: CLRC "; }
};

// CLRP 
// P = 0    	[..0.....]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x20>
{
    using Instruction = AddressMode::Implied<Operator::SET<State::Flag::p, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "20: CLRP ");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "20: CLRP "; }
};

// CLRV 
// V = 0, H = 0    	[.0..0...]
// Implied (1-Byte)
template<>
struct Opcode<State, 0xE0>
{
    using Instruction = AddressMode::Implied<Operator::SET<State::Flag::v, false>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E0: CLRV ");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xE0>");
        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E0: CLRV "; }
};

// CMP (X), (Y)
// (X) - (Y)    	[N.....ZC]
// Indirect Indirect (1-Byte)
template<>
struct Opcode<State, 0x79>
{
    using Instruction = AddressMode::IndirectIndirect<Operator::CMP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "79: CMP (X), (Y)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x79>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "79: CMP (X), (Y)"; }
};

// CMP A, #i
// A - i    	[N.....ZC]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0x68>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::CMP, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "68: CMP A, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "68: CMP A, #i"; }
};

// CMP A, (X)
// A - (X)    	[N.....ZC]
// Register Register Indirect (1-Byte)
template<>
struct Opcode<State, 0x66>
{
    using Instruction = AddressMode::RegisterRegisterIndirect<Operator::CMP, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "66: CMP A, (X)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x66>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "66: CMP A, (X)"; }
};

// CMP A, [d]+Y
// A - ([d]+Y)    	[N.....ZC]
// Register Direct Indirect Indexed (2-Byte)
template<>
struct Opcode<State, 0x77>
{
    using Instruction = AddressMode::RegisterDirectIndirectIndexed<Operator::CMP, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "77: CMP A, [d]+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x77>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "77: CMP A, [d]+Y"; }
};

// CMP A, [d+X]
// A - ([d+X])    	[N.....ZC]
// Register Direct Indexed Indirect (2-Byte)
template<>
struct Opcode<State, 0x67>
{
    using Instruction = AddressMode::RegisterDirectIndexedIndirect<Operator::CMP, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "67: CMP A, [d+X]");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x67>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "67: CMP A, [d+X]"; }
};

// CMP A, d
// A - (d)    	[N.....ZC]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0x64>
{
    using Instruction = AddressMode::RegisterDirect<Operator::CMP, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "64: CMP A, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "64: CMP A, d"; }
};

// CMP A, d+X
// A - (d+X)    	[N.....ZC]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x74>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::CMP, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "74: CMP A, d+X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "74: CMP A, d+X"; }
};

// CMP A, !a
// A - (a)    	[N.....ZC]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0x65>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::CMP, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "65: CMP A, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "65: CMP A, !a"; }
};

// CMP A, !a+X
// A - (a+X)    	[N.....ZC]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x75>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::CMP, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "75: CMP A, !a+X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "75: CMP A, !a+X"; }
};

// CMP A, !a+Y
// A - (a+Y)    	[N.....ZC]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x76>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::CMP, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "76: CMP A, !a+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x76>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "76: CMP A, !a+Y"; }
};

// CMP X, #i
// X - i    	[N.....ZC]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0xC8>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::CMP, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C8: CMP X, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C8: CMP X, #i"; }
};

// CMP X, d
// X - (d)    	[N.....ZC]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0x3E>
{
    using Instruction = AddressMode::RegisterDirect<Operator::CMP, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3E: CMP X, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3E: CMP X, d"; }
};

// CMP X, !a
// X - (a)    	[N.....ZC]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0x1E>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::CMP, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1E: CMP X, !a");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x1E>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1E: CMP X, !a"; }
};

// CMP Y, #i
// Y - i    	[N.....ZC]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0xAD>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::CMP, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AD: CMP Y, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AD: CMP Y, #i"; }
};

// CMP Y, d
// Y - (d)    	[N.....ZC]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0x7E>
{
    using Instruction = AddressMode::RegisterDirect<Operator::CMP, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7E: CMP Y, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7E: CMP Y, d"; }
};

// CMP Y, !a
// Y - (a)    	[N.....ZC]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0x5E>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::CMP, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5E: CMP Y, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5E: CMP Y, !a"; }
};

// CMP dd, ds
// (dd) - (ds)    	[N.....ZC]
// Direct Direct (3-Byte)
template<>
struct Opcode<State, 0x69>
{
    using Instruction = AddressMode::DirectDirect<Operator::CMP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "69: CMP dd, ds");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "69: CMP dd, ds"; }
};

// CMP d, #i
// (d) - i    	[N.....ZC]
// Direct Immediate (3-Byte)
template<>
struct Opcode<State, 0x78>
{
    using Instruction = AddressMode::DirectImmediate<Operator::CMP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "78: CMP d, #i");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "78: CMP d, #i"; }
};

// CMPW YA, d
// YA - (d)    	[N.....ZC]
// Y Accumulator Direct (2-Byte)
template<>
struct Opcode<State, 0x5A>
{
    using Instruction = AddressMode::YAccumulatorDirect<Operator::CMPW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5A: CMPW YA, d");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5A: CMPW YA, d"; }
};

// DAA A
// decimal adjust for addition    	[N.....ZC]
// Register (1-Byte)
template<>
struct Opcode<State, 0xDF>
{
    using Instruction = AddressMode::Register<Operator::DAA, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DF: DAA A");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xDF>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DF: DAA A"; }
};

// DAS A
// decimal adjust for subtraction    	[N.....ZC]
// Register (1-Byte)
template<>
struct Opcode<State, 0xBE>
{
    using Instruction = AddressMode::Register<Operator::DAS, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BE: DAS A");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xBE>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BE: DAS A"; }
};

// DBNZ Y, r
// Y-- then JNZ    	[........]
// Register Program Counter Relative (2-Byte)
template<>
struct Opcode<State, 0xFE>
{
    using Instruction = AddressMode::RegisterProgramCounterRelative<Operator::DBNZ, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FE: DBNZ Y, r");

        return 4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FE: DBNZ Y, r"; }
};

// DBNZ d, r
// (d)-- then JNZ    	[........]
// Direct Program Counter Relative (3-Byte)
template<>
struct Opcode<State, 0x6E>
{
    using Instruction = AddressMode::DirectProgramCounterRelative<Operator::DBNZ>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6E: DBNZ d, r");

        return 5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6E: DBNZ d, r"; }
};

// DEC A
// A--    	[N.....Z.]
// Register (1-Byte)
template<>
struct Opcode<State, 0x9C>
{
    using Instruction = AddressMode::Register<Operator::DEC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9C: DEC A");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9C: DEC A"; }
};

// DEC X
// X--    	[N.....Z.]
// Register (1-Byte)
template<>
struct Opcode<State, 0x1D>
{
    using Instruction = AddressMode::Register<Operator::DEC, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1D: DEC X");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1D: DEC X"; }
};

// DEC Y
// Y--    	[N.....Z.]
// Register (1-Byte)
template<>
struct Opcode<State, 0xDC>
{
    using Instruction = AddressMode::Register<Operator::DEC, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DC: DEC Y");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DC: DEC Y"; }
};

// DEC d
// (d)--    	[N.....Z.]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x8B>
{
    using Instruction = AddressMode::Direct<Operator::DEC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8B: DEC d");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8B: DEC d"; }
};

// DEC d+X
// (d+X)--    	[N.....Z.]
// Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x9B>
{
    using Instruction = AddressMode::DirectIndexed<Operator::DEC, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9B: DEC d+X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9B: DEC d+X"; }
};

// DEC !a
// (a)--    	[N.....Z.]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x8C>
{
    using Instruction = AddressMode::Absolute<Operator::DEC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8C: DEC !a");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8C: DEC !a"; }
};

// DECW d
// Word (d)--    	[N.....Z.]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x1A>
{
    using Instruction = AddressMode::Direct<Operator::DECW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1A: DECW d");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1A: DECW d"; }
};

// DI 
// I = 0    	[.....0..]
// Implied (1-Byte)
template<>
struct Opcode<State, 0xC0>
{
    using Instruction = AddressMode::Implied<Operator::DI>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C0: DI ");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xC0>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C0: DI "; }
};

// DIV YA, X
// A=YA/X, Y=mod(YA,X)    	[NV..H.Z.]
// Y Accumulator Index (1-Byte)
template<>
struct Opcode<State, 0x9E>
{
    using Instruction = AddressMode::YAccumulatorIndex<Operator::DIV, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9E: DIV YA, X");

        return 12 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9E: DIV YA, X"; }
};

// EI 
// I = 1    	[.....1..]
// Implied (1-Byte)
template<>
struct Opcode<State, 0xA0>
{
    using Instruction = AddressMode::Implied<Operator::EI>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A0: EI ");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xA0>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A0: EI "; }
};

// EOR (X), (Y)
// (X) = (X) EOR (Y)    	[N.....Z.]
// Indirect Indirect (1-Byte)
template<>
struct Opcode<State, 0x59>
{
    using Instruction = AddressMode::IndirectIndirect<Operator::EOR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "59: EOR (X), (Y)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x59>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "59: EOR (X), (Y)"; }
};

// EOR A, #i
// A = A EOR i    	[N.....Z.]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0x48>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::EOR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "48: EOR A, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "48: EOR A, #i"; }
};

// EOR A, (X)
// A = A EOR (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
template<>
struct Opcode<State, 0x46>
{
    using Instruction = AddressMode::RegisterRegisterIndirect<Operator::EOR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "46: EOR A, (X)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x46>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "46: EOR A, (X)"; }
};

// EOR A, [d]+Y
// A = A EOR ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
template<>
struct Opcode<State, 0x57>
{
    using Instruction = AddressMode::RegisterDirectIndirectIndexed<Operator::EOR, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "57: EOR A, [d]+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x57>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "57: EOR A, [d]+Y"; }
};

// EOR A, [d+X]
// A = A EOR ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
template<>
struct Opcode<State, 0x47>
{
    using Instruction = AddressMode::RegisterDirectIndexedIndirect<Operator::EOR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "47: EOR A, [d+X]");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x47>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "47: EOR A, [d+X]"; }
};

// EOR A, d
// A = A EOR (d)    	[N.....Z.]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0x44>
{
    using Instruction = AddressMode::RegisterDirect<Operator::EOR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "44: EOR A, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "44: EOR A, d"; }
};

// EOR A, d+X
// A = A EOR (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x54>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::EOR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "54: EOR A, d+X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "54: EOR A, d+X"; }
};

// EOR A, !a
// A = A EOR (a)    	[N.....Z.]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0x45>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::EOR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "45: EOR A, !a");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x45>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "45: EOR A, !a"; }
};

// EOR A, !a+X
// A = A EOR (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x55>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::EOR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "55: EOR A, !a+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x55>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "55: EOR A, !a+X"; }
};

// EOR A, !a+Y
// A = A EOR (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x56>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::EOR, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "56: EOR A, !a+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x56>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "56: EOR A, !a+Y"; }
};

// EOR dd, ds
// (dd) = (dd) EOR (ds)    	[N.....Z.]
// Direct Direct (3-Byte)
template<>
struct Opcode<State, 0x49>
{
    using Instruction = AddressMode::DirectDirect<Operator::EOR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "49: EOR dd, ds");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x49>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "49: EOR dd, ds"; }
};

// EOR d, #i
// (d) = (d) EOR i    	[N.....Z.]
// Direct Immediate (3-Byte)
template<>
struct Opcode<State, 0x58>
{
    using Instruction = AddressMode::DirectImmediate<Operator::EOR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "58: EOR d, #i");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "58: EOR d, #i"; }
};

// EOR1 C, m.b
// C = C EOR (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
template<>
struct Opcode<State, 0x8A>
{
    using Instruction = AddressMode::CarryMemoryBit<Operator::EOR1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8A: EOR1 C, m.b");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x8A>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8A: EOR1 C, m.b"; }
};

// INC A
// A++    	[N.....Z.]
// Register (1-Byte)
template<>
struct Opcode<State, 0xBC>
{
    using Instruction = AddressMode::Register<Operator::INC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BC: INC A");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BC: INC A"; }
};

// INC X
// X++    	[N.....Z.]
// Register (1-Byte)
template<>
struct Opcode<State, 0x3D>
{
    using Instruction = AddressMode::Register<Operator::INC, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3D: INC X");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3D: INC X"; }
};

// INC Y
// Y++    	[N.....Z.]
// Register (1-Byte)
template<>
struct Opcode<State, 0xFC>
{
    using Instruction = AddressMode::Register<Operator::INC, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FC: INC Y");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FC: INC Y"; }
};

// INC d
// (d)++    	[N.....Z.]
// Direct (2-Byte)
template<>
struct Opcode<State, 0xAB>
{
    using Instruction = AddressMode::Direct<Operator::INC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AB: INC d");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AB: INC d"; }
};

// INC d+X
// (d+X)++    	[N.....Z.]
// Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0xBB>
{
    using Instruction = AddressMode::DirectIndexed<Operator::INC, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BB: INC d+X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BB: INC d+X"; }
};

// INC !a
// (a)++    	[N.....Z.]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0xAC>
{
    using Instruction = AddressMode::Absolute<Operator::INC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AC: INC !a");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AC: INC !a"; }
};

// INCW d
// Word (d)++    	[N.....Z.]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x3A>
{
    using Instruction = AddressMode::Direct<Operator::INCW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3A: INCW d");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3A: INCW d"; }
};

// JMP [!a+X]
// PC = [a+X]    	[........]
// Absolute Indexed Indirect (3-Byte)
template<>
struct Opcode<State, 0x1F>
{
    using Instruction = AddressMode::AbsoluteIndexedIndirect<Operator::JMP, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "1F: JMP [!a+X]");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "1F: JMP [!a+X]"; }
};

// JMP !a
// PC = a    	[........]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x5F>
{
    using Instruction = AddressMode::Absolute_ControlFlow<Operator::JMP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5F: JMP !a");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5F: JMP !a"; }
};

// LSR A
// Right shift A: 0->high, low->C    	[N.....ZC]
// Register (1-Byte)
template<>
struct Opcode<State, 0x5C>
{
    using Instruction = AddressMode::Register<Operator::LSR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5C: LSR A");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5C: LSR A"; }
};

// LSR d
// Right shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x4B>
{
    using Instruction = AddressMode::Direct<Operator::LSR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4B: LSR d");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4B: LSR d"; }
};

// LSR d+X
// Right shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x5B>
{
    using Instruction = AddressMode::DirectIndexed<Operator::LSR, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5B: LSR d+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x5B>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5B: LSR d+X"; }
};

// LSR !a
// Right shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x4C>
{
    using Instruction = AddressMode::Absolute<Operator::LSR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4C: LSR !a");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4C: LSR !a"; }
};

// MOV (X)+, A
// (X++) = A      (no read)    	[........]
// Register Indirect Increment Register (1-Byte)
template<>
struct Opcode<State, 0xAF>
{
    using Instruction = AddressMode::RegisterIndirectIncrementRegister<Operator::MOV, State::Register::X, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AF: MOV (X)+, A");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AF: MOV (X)+, A"; }
};

// MOV (X), A
// (X) = A        (read)    	[........]
// Register Indirect Register (1-Byte)
template<>
struct Opcode<State, 0xC6>
{
    using Instruction = AddressMode::RegisterIndirectRegister<Operator::MOV, State::Register::X, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C6: MOV (X), A");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C6: MOV (X), A"; }
};

// MOV [d]+Y, A
// ([d]+Y) = A    (read)    	[........]
// Direct Indirect Indexed Register (2-Byte)
template<>
struct Opcode<State, 0xD7>
{
    using Instruction = AddressMode::DirectIndirectIndexedRegister<Operator::MOV, State::Register::Y, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D7: MOV [d]+Y, A");

        return  7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D7: MOV [d]+Y, A"; }
};

// MOV [d+X], A
// ([d+X]) = A    (read)    	[........]
// Direct Indexed Indirect Register (2-Byte)
template<>
struct Opcode<State, 0xC7>
{
    using Instruction = AddressMode::DirectIndexedIndirectRegister<Operator::MOV, State::Register::X, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C7: MOV [d+X], A");

        return  7 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C7: MOV [d+X], A"; }
};

// MOV A, #i
// A = i    	[N.....Z.]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0xE8>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::MOV_SignedResult, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E8: MOV A, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E8: MOV A, #i"; }
};

// MOV A, (X)
// A = (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
template<>
struct Opcode<State, 0xE6>
{
    using Instruction = AddressMode::RegisterRegisterIndirect<Operator::MOV_SignedResult, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E6: MOV A, (X)");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E6: MOV A, (X)"; }
};

// MOV A, (X)+
// A = (X++)    	[N.....Z.]
// Register Register Indirect Increment (1-Byte)
template<>
struct Opcode<State, 0xBF>
{
    using Instruction = AddressMode::RegisterRegisterIndirectIncrement<Operator::MOV_SignedResult, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BF: MOV A, (X)+");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xBF>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BF: MOV A, (X)+"; }
};

// MOV A, [d]+Y
// A = ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
template<>
struct Opcode<State, 0xF7>
{
    using Instruction = AddressMode::RegisterDirectIndirectIndexed<Operator::MOV_SignedResult, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F7: MOV A, [d]+Y");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F7: MOV A, [d]+Y"; }
};

// MOV A, [d+X]
// A = ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
template<>
struct Opcode<State, 0xE7>
{
    using Instruction = AddressMode::RegisterDirectIndexedIndirect<Operator::MOV_SignedResult, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E7: MOV A, [d+X]");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E7: MOV A, [d+X]"; }
};

// MOV A, X
// A = X    	[N.....Z.]
// Register Register (1-Byte)
template<>
struct Opcode<State, 0x7D>
{
    using Instruction = AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7D: MOV A, X");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7D: MOV A, X"; }
};

// MOV A, Y
// A = Y    	[N.....Z.]
// Register Register (1-Byte)
template<>
struct Opcode<State, 0xDD>
{
    using Instruction = AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DD: MOV A, Y");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DD: MOV A, Y"; }
};

// MOV A, d
// A = (d)    	[N.....Z.]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0xE4>
{
    using Instruction = AddressMode::RegisterDirect<Operator::MOV_SignedResult, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E4: MOV A, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E4: MOV A, d"; }
};

// MOV A, d+X
// A = (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0xF4>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::MOV_SignedResult, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F4: MOV A, d+X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F4: MOV A, d+X"; }
};

// MOV A, !a
// A = (a)    	[N.....Z.]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0xE5>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::MOV_SignedResult, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E5: MOV A, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E5: MOV A, !a"; }
};

// MOV A, !a+X
// A = (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0xF5>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::MOV_SignedResult, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F5: MOV A, !a+X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F5: MOV A, !a+X"; }
};

// MOV A, !a+Y
// A = (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0xF6>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::MOV_SignedResult, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F6: MOV A, !a+Y");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F6: MOV A, !a+Y"; }
};

// MOV SP, X
// SP = X    	[........]
// Register Register (1-Byte)
template<>
struct Opcode<State, 0xBD>
{
    using Instruction = AddressMode::RegisterRegister<Operator::MOV, State::Register::SP, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BD: MOV SP, X");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BD: MOV SP, X"; }
};

// MOV X, #i
// X = i    	[N.....Z.]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0xCD>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::MOV_SignedResult, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CD: MOV X, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CD: MOV X, #i"; }
};

// MOV X, A
// X = A    	[N.....Z.]
// Register Register (1-Byte)
template<>
struct Opcode<State, 0x5D>
{
    using Instruction = AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::Register::X, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "5D: MOV X, A");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "5D: MOV X, A"; }
};

// MOV X, SP
// X = SP    	[N.....Z.]
// Register Register (1-Byte)
template<>
struct Opcode<State, 0x9D>
{
    using Instruction = AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::Register::X, State::Register::SP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9D: MOV X, SP");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x9D>");
        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9D: MOV X, SP"; }
};

// MOV X, d
// X = (d)    	[N.....Z.]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0xF8>
{
    using Instruction = AddressMode::RegisterDirect<Operator::MOV_SignedResult, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F8: MOV X, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F8: MOV X, d"; }
};

// MOV X, d+Y
// X = (d+Y)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0xF9>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::MOV_SignedResult, State::Register::X, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F9: MOV X, d+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xF9>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F9: MOV X, d+Y"; }
};

// MOV X, !a
// X = (a)    	[N.....Z.]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0xE9>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::MOV_SignedResult, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E9: MOV X, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E9: MOV X, !a"; }
};

// MOV Y, #i
// Y = i    	[N.....Z.]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0x8D>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::MOV_SignedResult, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8D: MOV Y, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8D: MOV Y, #i"; }
};

// MOV Y, A
// Y = A    	[N.....Z.]
// Register Register (1-Byte)
template<>
struct Opcode<State, 0xFD>
{
    using Instruction = AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::Register::Y, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FD: MOV Y, A");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FD: MOV Y, A"; }
};

// MOV Y, d
// Y = (d)    	[N.....Z.]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0xEB>
{
    using Instruction = AddressMode::RegisterDirect<Operator::MOV_SignedResult, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EB: MOV Y, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EB: MOV Y, d"; }
};

// MOV Y, d+X
// Y = (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0xFB>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::MOV_SignedResult, State::Register::Y, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FB: MOV Y, d+X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FB: MOV Y, d+X"; }
};

// MOV Y, !a
// Y = (a)    	[N.....Z.]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0xEC>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::MOV_SignedResult, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EC: MOV Y, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EC: MOV Y, !a"; }
};

// MOV dd, ds
// (dd) = (ds)    (no read)    	[........]
// Direct Direct (3-Byte)
template<>
struct Opcode<State, 0xFA>
{
    using Instruction = AddressMode::DirectDirect<Operator::MOV>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FA: MOV dd, ds");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FA: MOV dd, ds"; }
};

// MOV d+X, A
// (d+X) = A      (read)    	[........]
// Direct Indexed Register (2-Byte)
template<>
struct Opcode<State, 0xD4>
{
    using Instruction = AddressMode::DirectIndexedRegister<Operator::MOV, State::Register::X, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D4: MOV d+X, A");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D4: MOV d+X, A"; }
};

// MOV d+X, Y
// (d+X) = Y      (read)    	[........]
// Direct Indexed Register (2-Byte)
template<>
struct Opcode<State, 0xDB>
{
    using Instruction = AddressMode::DirectIndexedRegister<Operator::MOV, State::Register::X, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DB: MOV d+X, Y");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DB: MOV d+X, Y"; }
};

// MOV d+Y, X
// (d+Y) = X      (read)    	[........]
// Direct Indexed Register (2-Byte)
template<>
struct Opcode<State, 0xD9>
{
    using Instruction = AddressMode::DirectIndexedRegister<Operator::MOV, State::Register::Y, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D9: MOV d+Y, X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xD9>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D9: MOV d+Y, X"; }
};

// MOV d, #i
// (d) = i        (read)    	[........]
// Direct Immediate (3-Byte)
template<>
struct Opcode<State, 0x8F>
{
    using Instruction = AddressMode::DirectImmediate<Operator::MOV>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8F: MOV d, #i");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8F: MOV d, #i"; }
};

// MOV d, A
// (d) = A        (read)    	[........]
// Direct Register (2-Byte)
template<>
struct Opcode<State, 0xC4>
{
    using Instruction = AddressMode::DirectRegister<Operator::MOV, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C4: MOV d, A");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C4: MOV d, A"; }
};

// MOV d, X
// (d) = X        (read)    	[........]
// Direct Register (2-Byte)
template<>
struct Opcode<State, 0xD8>
{
    using Instruction = AddressMode::DirectRegister<Operator::MOV, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D8: MOV d, X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D8: MOV d, X"; }
};

// MOV d, Y
// (d) = Y        (read)    	[........]
// Direct Register (2-Byte)
template<>
struct Opcode<State, 0xCB>
{
    using Instruction = AddressMode::DirectRegister<Operator::MOV, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CB: MOV d, Y");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CB: MOV d, Y"; }
};

// MOV !a+X, A
// (a+X) = A      (read)    	[........]
// Absolute Indexed Register (3-Byte)
template<>
struct Opcode<State, 0xD5>
{
    using Instruction = AddressMode::AbsoluteIndexedRegister<Operator::MOV, State::Register::X, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D5: MOV !a+X, A");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D5: MOV !a+X, A"; }
};

// MOV !a+Y, A
// (a+Y) = A      (read)    	[........]
// Absolute Indexed Register (3-Byte)
template<>
struct Opcode<State, 0xD6>
{
    using Instruction = AddressMode::AbsoluteIndexedRegister<Operator::MOV, State::Register::Y, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D6: MOV !a+Y, A");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D6: MOV !a+Y, A"; }
};

// MOV !a, A
// (a) = A        (read)    	[........]
// Absolute Register (3-Byte)
template<>
struct Opcode<State, 0xC5>
{
    using Instruction = AddressMode::AbsoluteRegister<Operator::MOV, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C5: MOV !a, A");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C5: MOV !a, A"; }
};

// MOV !a, X
// (a) = X        (read)    	[........]
// Absolute Register (3-Byte)
template<>
struct Opcode<State, 0xC9>
{
    using Instruction = AddressMode::AbsoluteRegister<Operator::MOV, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C9: MOV !a, X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C9: MOV !a, X"; }
};

// MOV !a, Y
// (a) = Y        (read)    	[........]
// Absolute Register (3-Byte)
template<>
struct Opcode<State, 0xCC>
{
    using Instruction = AddressMode::AbsoluteRegister<Operator::MOV, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CC: MOV !a, Y");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CC: MOV !a, Y"; }
};

// MOV1 C, m.b
// C = (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
template<>
struct Opcode<State, 0xAA>
{
    using Instruction = AddressMode::CarryMemoryBit<Operator::MOV1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AA: MOV1 C, m.b");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xAA>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AA: MOV1 C, m.b"; }
};

// MOV1 m.b, C
// (m.b) = C    	[........]
// Memory Bit Carry (3-Byte)
template<>
struct Opcode<State, 0xCA>
{
    using Instruction = AddressMode::MemoryBitCarry<Operator::MOV1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CA: MOV1 m.b, C");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xCA>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CA: MOV1 m.b, C"; }
};

// MOVW YA, d
// YA = word (d)    	[N.....Z.]
// Y Accumulator Direct (2-Byte)
template<>
struct Opcode<State, 0xBA>
{
    using Instruction = AddressMode::YAccumulatorDirect<Operator::MOVW_SignedResult>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "BA: MOVW YA, d");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "BA: MOVW YA, d"; }
};

// MOVW d, YA
// word (d) = YA  (read low only)    	[........]
// Direct Y Accumulator (2-Byte)
template<>
struct Opcode<State, 0xDA>
{
    using Instruction = AddressMode::DirectYAccumulator<Operator::MOVW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "DA: MOVW d, YA");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "DA: MOVW d, YA"; }
};

// MUL YA
// YA = Y * A, NZ on Y only    	[N.....Z.]
// Y Accumulator (1-Byte)
template<>
struct Opcode<State, 0xCF>
{
    using Instruction = AddressMode::YAccumulator<Operator::MUL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CF: MUL YA");

        return  9 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CF: MUL YA"; }
};

// NOP 
// do nothing    	[........]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x00>
{
    using Instruction = AddressMode::Implied<Operator::NOP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "00: NOP ");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "00: NOP "; }
};

// NOT1 m.b
// m.b = ~m.b    	[........]
// Memory Bit (3-Byte)
template<>
struct Opcode<State, 0xEA>
{
    using Instruction = AddressMode::MemoryBit<Operator::NOT1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EA: NOT1 m.b");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xEA>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EA: NOT1 m.b"; }
};

// NOTC 
// C = !C    	[.......C]
// Implied (1-Byte)
template<>
struct Opcode<State, 0xED>
{
    using Instruction = AddressMode::Implied<Operator::NOTC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "ED: NOTC ");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "ED: NOTC "; }
};

// OR (X), (Y)
// (X) = (X) | (Y)    	[N.....Z.]
// Indirect Indirect (1-Byte)
template<>
struct Opcode<State, 0x19>
{
    using Instruction = AddressMode::IndirectIndirect<Operator::OR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "19: OR (X), (Y)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x19>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "19: OR (X), (Y)"; }
};

// OR A, #i
// A = A | i    	[N.....Z.]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0x08>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::OR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "08: OR A, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "08: OR A, #i"; }
};

// OR A, (X)
// A = A | (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
template<>
struct Opcode<State, 0x06>
{
    using Instruction = AddressMode::RegisterRegisterIndirect<Operator::OR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "06: OR A, (X)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x06>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "06: OR A, (X)"; }
};

// OR A, [d]+Y
// A = A | ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
template<>
struct Opcode<State, 0x17>
{
    using Instruction = AddressMode::RegisterDirectIndirectIndexed<Operator::OR, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "17: OR A, [d]+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x17>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "17: OR A, [d]+Y"; }
};

// OR A, [d+X]
// A = A | ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
template<>
struct Opcode<State, 0x07>
{
    using Instruction = AddressMode::RegisterDirectIndexedIndirect<Operator::OR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "07: OR A, [d+X]");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x07>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "07: OR A, [d+X]"; }
};

// OR A, d
// A = A | (d)    	[N.....Z.]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0x04>
{
    using Instruction = AddressMode::RegisterDirect<Operator::OR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "04: OR A, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "04: OR A, d"; }
};

// OR A, d+X
// A = A | (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x14>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::OR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "14: OR A, d+X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "14: OR A, d+X"; }
};

// OR A, !a
// A = A | (a)    	[N.....Z.]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0x05>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::OR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "05: OR A, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "05: OR A, !a"; }
};

// OR A, !a+X
// A = A | (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x15>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::OR, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "15: OR A, !a+X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "15: OR A, !a+X"; }
};

// OR A, !a+Y
// A = A | (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0x16>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::OR, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "16: OR A, !a+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x16>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "16: OR A, !a+Y"; }
};

// OR dd, ds
// (dd) = (dd) | (ds)    	[N.....Z.]
// Direct Direct (3-Byte)
template<>
struct Opcode<State, 0x09>
{
    using Instruction = AddressMode::DirectDirect<Operator::OR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "09: OR dd, ds");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "09: OR dd, ds"; }
};

// OR d, #i
// (d) = (d) | i    	[N.....Z.]
// Direct Immediate (3-Byte)
template<>
struct Opcode<State, 0x18>
{
    using Instruction = AddressMode::DirectImmediate<Operator::OR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "18: OR d, #i");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x18>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "18: OR d, #i"; }
};

// OR1 C, /m.b
// C = C | ~(m.b)    	[.......C]
// Carry Negated Memory Bit (3-Byte)
template<>
struct Opcode<State, 0x2A>
{
    using Instruction = AddressMode::CarryNegatedMemoryBit<Operator::OR1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2A: OR1 C, /m.b");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x2A>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2A: OR1 C, /m.b"; }
};

// OR1 C, m.b
// C = C | (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
template<>
struct Opcode<State, 0x0A>
{
    using Instruction = AddressMode::CarryMemoryBit<Operator::OR1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0A: OR1 C, m.b");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x0A>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0A: OR1 C, m.b"; }
};

// PCALL u
// CALL $FF00+u    	[........]
// U Page (2-Byte)
template<>
struct Opcode<State, 0x4F>
{
    using Instruction = AddressMode::UPage<Operator::PCALL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4F: PCALL u");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x4F>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4F: PCALL u"; }
};

// POP A
// A = (++SP)    	[........]
// Register (1-Byte)
template<>
struct Opcode<State, 0xAE>
{
    using Instruction = AddressMode::Register<Operator::POP, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "AE: POP A");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "AE: POP A"; }
};

// POP PSW
// Flags = (++SP)    	[NVPBHIZC]
// Register (1-Byte)
template<>
struct Opcode<State, 0x8E>
{
    using Instruction = AddressMode::Register<Operator::POP, State::Register::PSW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "8E: POP PSW");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "8E: POP PSW"; }
};

// POP X
// X = (++SP)    	[........]
// Register (1-Byte)
template<>
struct Opcode<State, 0xCE>
{
    using Instruction = AddressMode::Register<Operator::POP, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "CE: POP X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "CE: POP X"; }
};

// POP Y
// Y = (++SP)    	[........]
// Register (1-Byte)
template<>
struct Opcode<State, 0xEE>
{
    using Instruction = AddressMode::Register<Operator::POP, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EE: POP Y");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EE: POP Y"; }
};

// PUSH A
// (SP--) = A    	[........]
// Register (1-Byte)
template<>
struct Opcode<State, 0x2D>
{
    using Instruction = AddressMode::Register<Operator::PUSH, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2D: PUSH A");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2D: PUSH A"; }
};

// PUSH PSW
// (SP--) = Flags    	[........]
// Register (1-Byte)
template<>
struct Opcode<State, 0x0D>
{
    using Instruction = AddressMode::Register<Operator::PUSH, State::Register::PSW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0D: PUSH PSW");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0D: PUSH PSW"; }
};

// PUSH X
// (SP--) = X    	[........]
// Register (1-Byte)
template<>
struct Opcode<State, 0x4D>
{
    using Instruction = AddressMode::Register<Operator::PUSH, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4D: PUSH X");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4D: PUSH X"; }
};

// PUSH Y
// (SP--) = Y    	[........]
// Register (1-Byte)
template<>
struct Opcode<State, 0x6D>
{
    using Instruction = AddressMode::Register<Operator::PUSH, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6D: PUSH Y");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6D: PUSH Y"; }
};

// RET 
// Pop PC    	[........]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x6F>
{
    using Instruction = AddressMode::Implied<Operator::RET>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6F: RET ");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6F: RET "; }
};

// RET1 
// Pop Flags, PC    	[NVPBHIZC]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x7F>
{
    using Instruction = AddressMode::Implied<Operator::RET1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7F: RET1 ");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x7F>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7F: RET1 "; }
};

// ROL A
// Left shift A: low=C, C=high    	[N.....ZC]
// Register (1-Byte)
template<>
struct Opcode<State, 0x3C>
{
    using Instruction = AddressMode::Register<Operator::ROL, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3C: ROL A");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x3C>");
        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3C: ROL A"; }
};

// ROL d
// Left shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x2B>
{
    using Instruction = AddressMode::Direct<Operator::ROL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2B: ROL d");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2B: ROL d"; }
};

// ROL d+X
// Left shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x3B>
{
    using Instruction = AddressMode::DirectIndexed<Operator::ROL, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "3B: ROL d+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x3B>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "3B: ROL d+X"; }
};

// ROL !a
// Left shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x2C>
{
    using Instruction = AddressMode::Absolute<Operator::ROL>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "2C: ROL !a");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x2C>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "2C: ROL !a"; }
};

// ROR A
// Right shift A: high=C, C=low    	[N.....ZC]
// Register (1-Byte)
template<>
struct Opcode<State, 0x7C>
{
    using Instruction = AddressMode::Register<Operator::ROR, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7C: ROR A");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7C: ROR A"; }
};

// ROR d
// Right shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x6B>
{
    using Instruction = AddressMode::Direct<Operator::ROR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6B: ROR d");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6B: ROR d"; }
};

// ROR d+X
// Right shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0x7B>
{
    using Instruction = AddressMode::DirectIndexed<Operator::ROR, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "7B: ROR d+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x7B>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "7B: ROR d+X"; }
};

// ROR !a
// Right shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x6C>
{
    using Instruction = AddressMode::Absolute<Operator::ROR>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "6C: ROR !a");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x6C>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "6C: ROR !a"; }
};

// SBC (X), (Y)
// (X) = (X)-(Y)-!C    	[NV..H.ZC]
// Indirect Indirect (1-Byte)
template<>
struct Opcode<State, 0xB9>
{
    using Instruction = AddressMode::IndirectIndirect<Operator::SBC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B9: SBC (X), (Y)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xB9>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B9: SBC (X), (Y)"; }
};

// SBC A, #i
// A = A-i-!C    	[NV..H.ZC]
// Register Immediate (2-Byte)
template<>
struct Opcode<State, 0xA8>
{
    using Instruction = AddressMode::RegisterImmediate<Operator::SBC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A8: SBC A, #i");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A8: SBC A, #i"; }
};

// SBC A, (X)
// A = A-(X)-!C    	[NV..H.ZC]
// Register Register Indirect (1-Byte)
template<>
struct Opcode<State, 0xA6>
{
    using Instruction = AddressMode::RegisterRegisterIndirect<Operator::SBC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A6: SBC A, (X)");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xA6>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A6: SBC A, (X)"; }
};

// SBC A, [d]+Y
// A = A-([d]+Y)-!C    	[NV..H.ZC]
// Register Direct Indirect Indexed (2-Byte)
template<>
struct Opcode<State, 0xB7>
{
    using Instruction = AddressMode::RegisterDirectIndirectIndexed<Operator::SBC, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B7: SBC A, [d]+Y");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xB7>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B7: SBC A, [d]+Y"; }
};

// SBC A, [d+X]
// A = A-([d+X])-!C    	[NV..H.ZC]
// Register Direct Indexed Indirect (2-Byte)
template<>
struct Opcode<State, 0xA7>
{
    using Instruction = AddressMode::RegisterDirectIndexedIndirect<Operator::SBC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A7: SBC A, [d+X]");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xA7>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A7: SBC A, [d+X]"; }
};

// SBC A, d
// A = A-(d)-!C    	[NV..H.ZC]
// Register Direct (2-Byte)
template<>
struct Opcode<State, 0xA4>
{
    using Instruction = AddressMode::RegisterDirect<Operator::SBC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A4: SBC A, d");

        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A4: SBC A, d"; }
};

// SBC A, d+X
// A = A-(d+X)-!C    	[NV..H.ZC]
// Register Direct Indexed (2-Byte)
template<>
struct Opcode<State, 0xB4>
{
    using Instruction = AddressMode::RegisterDirectIndexed<Operator::SBC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B4: SBC A, d+X");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xB4>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B4: SBC A, d+X"; }
};

// SBC A, !a
// A = A-(a)-!C    	[NV..H.ZC]
// Register Absolute (3-Byte)
template<>
struct Opcode<State, 0xA5>
{
    using Instruction = AddressMode::RegisterAbsolute<Operator::SBC, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A5: SBC A, !a");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A5: SBC A, !a"; }
};

// SBC A, !a+X
// A = A-(a+X)-!C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0xB5>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::SBC, State::Register::A, State::Register::X>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B5: SBC A, !a+X");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B5: SBC A, !a+X"; }
};

// SBC A, !a+Y
// A = A-(a+Y)-!C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
template<>
struct Opcode<State, 0xB6>
{
    using Instruction = AddressMode::RegisterAbsoluteIndexed<Operator::SBC, State::Register::A, State::Register::Y>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B6: SBC A, !a+Y");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B6: SBC A, !a+Y"; }
};

// SBC dd, ds
// (dd) = (dd)-(ds)-!C    	[NV..H.ZC]
// Direct Direct (3-Byte)
template<>
struct Opcode<State, 0xA9>
{
    using Instruction = AddressMode::DirectDirect<Operator::SBC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A9: SBC dd, ds");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xA9>");
        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A9: SBC dd, ds"; }
};

// SBC d, #i
// (d) = (d)-i-!C    	[NV..H.ZC]
// Direct Immediate (3-Byte)
template<>
struct Opcode<State, 0xB8>
{
    using Instruction = AddressMode::DirectImmediate<Operator::SBC>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B8: SBC d, #i");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xB8>");
        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B8: SBC d, #i"; }
};

// SET1 d.0
// d.0 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x02>
{
    using Instruction = AddressMode::Direct<Operator::SET1<0, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "02: SET1 d.0");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x02>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "02: SET1 d.0"; }
};

// SET1 d.1
// d.1 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x22>
{
    using Instruction = AddressMode::Direct<Operator::SET1<1, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "22: SET1 d.1");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "22: SET1 d.1"; }
};

// SET1 d.2
// d.2 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x42>
{
    using Instruction = AddressMode::Direct<Operator::SET1<2, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "42: SET1 d.2");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x42>");
        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "42: SET1 d.2"; }
};

// SET1 d.3
// d.3 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x62>
{
    using Instruction = AddressMode::Direct<Operator::SET1<3, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "62: SET1 d.3");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "62: SET1 d.3"; }
};

// SET1 d.4
// d.4 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0x82>
{
    using Instruction = AddressMode::Direct<Operator::SET1<4, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "82: SET1 d.4");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "82: SET1 d.4"; }
};

// SET1 d.5
// d.5 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0xA2>
{
    using Instruction = AddressMode::Direct<Operator::SET1<5, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A2: SET1 d.5");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A2: SET1 d.5"; }
};

// SET1 d.6
// d.6 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0xC2>
{
    using Instruction = AddressMode::Direct<Operator::SET1<6, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C2: SET1 d.6");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C2: SET1 d.6"; }
};

// SET1 d.7
// d.7 = 1    	[........]
// Direct (2-Byte)
template<>
struct Opcode<State, 0xE2>
{
    using Instruction = AddressMode::Direct<Operator::SET1<7, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E2: SET1 d.7");

        return  4 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E2: SET1 d.7"; }
};

// SETC 
// C = 1    	[.......1]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x80>
{
    using Instruction = AddressMode::Implied<Operator::SET<State::Flag::c, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "80: SETC ");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "80: SETC "; }
};

// SETP 
// P = 1    	[..1.....]
// Implied (1-Byte)
template<>
struct Opcode<State, 0x40>
{
    using Instruction = AddressMode::Implied<Operator::SET<State::Flag::p, true>>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "40: SETP ");

        return  2 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "40: SETP "; }
};

// SLEEP 
// Halts the processor    	[........]
// Implied (1-Byte)
template<>
struct Opcode<State, 0xEF>
{
    using Instruction = AddressMode::Implied<Operator::SLEEP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "EF: SLEEP ");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xEF>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "EF: SLEEP "; }
};

// STOP 
// Halts the processor    	[........]
// Implied (1-Byte)
template<>
struct Opcode<State, 0xFF>
{
    using Instruction = AddressMode::Implied<Operator::STOP>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "FF: STOP ");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xFF>");
        return  3 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "FF: STOP "; }
};

// SUBW YA, d
// YA  = YA - (d), H on high byte    	[NV..H.ZC]
// Y Accumulator Direct (2-Byte)
template<>
struct Opcode<State, 0x9A>
{
    using Instruction = AddressMode::YAccumulatorDirect<Operator::SUBW>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9A: SUBW YA, d");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9A: SUBW YA, d"; }
};

// TCALL 0
// CALL [$FFDE]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x01>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 0>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "01: TCALL 0");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x01>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "01: TCALL 0"; }
};

// TCALL 1
// CALL [$FFDC]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x11>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "11: TCALL 1");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x11>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "11: TCALL 1"; }
};

// TCALL 2
// CALL [$FFDA]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x21>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 2>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "21: TCALL 2");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x21>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "21: TCALL 2"; }
};

// TCALL 3
// CALL [$FFD8]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x31>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 3>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "31: TCALL 3");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x31>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "31: TCALL 3"; }
};

// TCALL 4
// CALL [$FFD6]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x41>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 4>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "41: TCALL 4");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x41>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "41: TCALL 4"; }
};

// TCALL 5
// CALL [$FFD4]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x51>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 5>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "51: TCALL 5");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x51>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "51: TCALL 5"; }
};

// TCALL 6
// CALL [$FFD2]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x61>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 6>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "61: TCALL 6");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x61>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "61: TCALL 6"; }
};

// TCALL 7
// CALL [$FFD0]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x71>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 7>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "71: TCALL 7");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x71>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "71: TCALL 7"; }
};

// TCALL 8
// CALL [$FFCE]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x81>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 8>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "81: TCALL 8");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x81>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "81: TCALL 8"; }
};

// TCALL 9
// CALL [$FFCC]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0x91>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 9>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "91: TCALL 9");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0x91>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "91: TCALL 9"; }
};

// TCALL 10
// CALL [$FFCA]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0xA1>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 10>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "A1: TCALL 10");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xA1>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "A1: TCALL 10"; }
};

// TCALL 11
// CALL [$FFC8]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0xB1>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 11>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "B1: TCALL 11");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xB1>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "B1: TCALL 11"; }
};

// TCALL 12
// CALL [$FFC6]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0xC1>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 12>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "C1: TCALL 12");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xC1>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "C1: TCALL 12"; }
};

// TCALL 13
// CALL [$FFC4]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0xD1>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 13>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "D1: TCALL 13");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xD1>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "D1: TCALL 13"; }
};

// TCALL 14
// CALL [$FFC2]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0xE1>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 14>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "E1: TCALL 14");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xE1>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "E1: TCALL 14"; }
};

// TCALL 15
// CALL [$FFC0]    	[........]
// Table (1-Byte)
template<>
struct Opcode<State, 0xF1>
{
    using Instruction = AddressMode::Table<Operator::TCALL, 15>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "F1: TCALL 15");

        throw NotYetImplementedException("SPC::Opcode<SPC::State, 0xF1>");
        return  8 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "F1: TCALL 15"; }
};

// TCLR1 !a
// (a) = (a)&~A, ZN as for A-(a)    	[N.....Z.]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x4E>
{
    using Instruction = AddressMode::Absolute<Operator::TCLR1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "4E: TCLR1 !a");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "4E: TCLR1 !a"; }
};

// TSET1 !a
// (a) = (a)|A, ZN as for A-(a)    	[N.....Z.]
// Absolute (3-Byte)
template<>
struct Opcode<State, 0x0E>
{
    using Instruction = AddressMode::Absolute<Operator::TSET1>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "0E: TSET1 !a");

        return  6 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "0E: TSET1 !a"; }
};

// XCN A
// A = (A>>4) | (A<<4)    	[N.....Z.]
// Register (1-Byte)
template<>
struct Opcode<State, 0x9F>
{
    using Instruction = AddressMode::Register<Operator::XCN, State::Register::A>;

    static int execute(State& state)
    {
        PROFILE_IF(PROFILE_OPCODES, "9F: XCN A");

        return  5 + Instruction::Type::applyOperand<Instruction>(state);
    }

    static std::string opcodeToString() { return "9F: XCN A"; }
};

}
