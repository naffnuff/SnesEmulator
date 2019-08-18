#pragma once

#include "Exception.h"
#include "SpcState.h"
#include "SpcAddressMode.h"
#include "SpcOperator.h"

namespace SPC {

namespace Opcode {

// ADC (X), (Y)
// (X) = (X)+(Y)+C    	[NV..H.ZC]
// Indirect Indirect (1-Byte)
class ADC_99 : public AddressMode::IndirectIndirect<Operator::ADC>
{
    using IndirectIndirect::IndirectIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_99");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "99: ADC (X), (Y)"; }
};

// ADC A, #i
// A = A+i+C    	[NV..H.ZC]
// Register Immediate (2-Byte)
class ADC_88 : public AddressMode::RegisterImmediate<Operator::ADC, State::A>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "88: ADC A, #i"; }
};

// ADC A, (X)
// A = A+(X)+C    	[NV..H.ZC]
// Register Register Indirect (1-Byte)
class ADC_86 : public AddressMode::RegisterRegisterIndirect<Operator::ADC, State::A, State::X>
{
    using RegisterRegisterIndirect::RegisterRegisterIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_86");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "86: ADC A, (X)"; }
};

// ADC A, [d]+Y
// A = A+([d]+Y)+C    	[NV..H.ZC]
// Register Direct Indirect Indexed (2-Byte)
class ADC_97 : public AddressMode::RegisterDirectIndirectIndexed<Operator::ADC, State::A, State::Y>
{
    using RegisterDirectIndirectIndexed::RegisterDirectIndirectIndexed;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "97: ADC A, [d]+Y"; }
};

// ADC A, [d+X]
// A = A+([d+X])+C    	[NV..H.ZC]
// Register Direct Indexed Indirect (2-Byte)
class ADC_87 : public AddressMode::RegisterDirectIndexedIndirect<Operator::ADC, State::A, State::X>
{
    using RegisterDirectIndexedIndirect::RegisterDirectIndexedIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_87");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "87: ADC A, [d+X]"; }
};

// ADC A, d
// A = A+(d)+C    	[NV..H.ZC]
// Register Direct (2-Byte)
class ADC_84 : public AddressMode::RegisterDirect<Operator::ADC, State::A>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "84: ADC A, d"; }
};

// ADC A, d+X
// A = A+(d+X)+C    	[NV..H.ZC]
// Register Direct Indexed (2-Byte)
class ADC_94 : public AddressMode::RegisterDirectIndexed<Operator::ADC, State::A, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "94: ADC A, d+X"; }
};

// ADC A, !a
// A = A+(a)+C    	[NV..H.ZC]
// Register Absolute (3-Byte)
class ADC_85 : public AddressMode::RegisterAbsolute<Operator::ADC, State::A>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "85: ADC A, !a"; }
};

// ADC A, !a+X
// A = A+(a+X)+C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
class ADC_95 : public AddressMode::RegisterAbsoluteIndexed<Operator::ADC, State::A, State::X>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "95: ADC A, !a+X"; }
};

// ADC A, !a+Y
// A = A+(a+Y)+C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
class ADC_96 : public AddressMode::RegisterAbsoluteIndexed<Operator::ADC, State::A, State::Y>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "96: ADC A, !a+Y"; }
};

// ADC dd, ds
// (dd) = (dd)+(d)+C    	[NV..H.ZC]
// Direct Direct (3-Byte)
class ADC_89 : public AddressMode::DirectDirect<Operator::ADC>
{
    using DirectDirect::DirectDirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ADC_89");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "89: ADC dd, ds"; }
};

// ADC d, #i
// (d) = (d)+i+C    	[NV..H.ZC]
// Direct Immediate (3-Byte)
class ADC_98 : public AddressMode::DirectImmediate<Operator::ADC>
{
    using DirectImmediate::DirectImmediate;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "98: ADC d, #i"; }
};

// ADDW YA, d
// YA  = YA + (d), H on high byte    	[NV..H.ZC]
// Y Accumulator Direct (2-Byte)
class ADDW_7A : public AddressMode::YAccumulatorDirect<Operator::ADDW>
{
    using YAccumulatorDirect::YAccumulatorDirect;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "7A: ADDW YA, d"; }
};

// AND (X), (Y)
// (X) = (X) & (Y)    	[N.....Z.]
// Indirect Indirect (1-Byte)
class AND_39 : public AddressMode::IndirectIndirect<Operator::AND>
{
    using IndirectIndirect::IndirectIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_39");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "39: AND (X), (Y)"; }
};

// AND A, #i
// A = A & i    	[N.....Z.]
// Register Immediate (2-Byte)
class AND_28 : public AddressMode::RegisterImmediate<Operator::AND, State::A>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "28: AND A, #i"; }
};

// AND A, (X)
// A = A & (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
class AND_26 : public AddressMode::RegisterRegisterIndirect<Operator::AND, State::A, State::X>
{
    using RegisterRegisterIndirect::RegisterRegisterIndirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "26: AND A, (X)"; }
};

// AND A, [d]+Y
// A = A & ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
class AND_37 : public AddressMode::RegisterDirectIndirectIndexed<Operator::AND, State::A, State::Y>
{
    using RegisterDirectIndirectIndexed::RegisterDirectIndirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_37");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "37: AND A, [d]+Y"; }
};

// AND A, [d+X]
// A = A & ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
class AND_27 : public AddressMode::RegisterDirectIndexedIndirect<Operator::AND, State::A, State::X>
{
    using RegisterDirectIndexedIndirect::RegisterDirectIndexedIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_27");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "27: AND A, [d+X]"; }
};

// AND A, d
// A = A & (d)    	[N.....Z.]
// Register Direct (2-Byte)
class AND_24 : public AddressMode::RegisterDirect<Operator::AND, State::A>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "24: AND A, d"; }
};

// AND A, d+X
// A = A & (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
class AND_34 : public AddressMode::RegisterDirectIndexed<Operator::AND, State::A, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_34");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "34: AND A, d+X"; }
};

// AND A, !a
// A = A & (a)    	[N.....Z.]
// Register Absolute (3-Byte)
class AND_25 : public AddressMode::RegisterAbsolute<Operator::AND, State::A>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "25: AND A, !a"; }
};

// AND A, !a+X
// A = A & (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class AND_35 : public AddressMode::RegisterAbsoluteIndexed<Operator::AND, State::A, State::X>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_35");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "35: AND A, !a+X"; }
};

// AND A, !a+Y
// A = A & (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class AND_36 : public AddressMode::RegisterAbsoluteIndexed<Operator::AND, State::A, State::Y>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_36");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "36: AND A, !a+Y"; }
};

// AND dd, ds
// (dd) = (dd) & (ds)    	[N.....Z.]
// Direct Direct (3-Byte)
class AND_29 : public AddressMode::DirectDirect<Operator::AND>
{
    using DirectDirect::DirectDirect;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "29: AND dd, ds"; }
};

// AND d, #i
// (d) = (d) & i    	[N.....Z.]
// Direct Immediate (3-Byte)
class AND_38 : public AddressMode::DirectImmediate<Operator::AND>
{
    using DirectImmediate::DirectImmediate;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND_38");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "38: AND d, #i"; }
};

// AND1 C, /m.b
// C = C & ~(m.b)    	[.......C]
// Carry Negated Memory Bit (3-Byte)
class AND1_6A : public AddressMode::CarryNegatedMemoryBit<Operator::AND1>
{
    using CarryNegatedMemoryBit::CarryNegatedMemoryBit;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND1_6A");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "6A: AND1 C, /m.b"; }
};

// AND1 C, m.b
// C = C & (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
class AND1_4A : public AddressMode::CarryMemoryBit<Operator::AND1>
{
    using CarryMemoryBit::CarryMemoryBit;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("AND1_4A");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "4A: AND1 C, m.b"; }
};

// ASL A
// Left shift A: high->C, 0->low    	[N.....ZC]
// Register (1-Byte)
class ASL_1C : public AddressMode::Register<Operator::ASL, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "1C: ASL A"; }
};

// ASL d
// Left shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
class ASL_0B : public AddressMode::Direct<Operator::ASL>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "0B: ASL d"; }
};

// ASL d+X
// Left shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
class ASL_1B : public AddressMode::DirectIndexed<Operator::ASL, State::X>
{
    using DirectIndexed::DirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ASL_1B");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "1B: ASL d+X"; }
};

// ASL !a
// Left shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
class ASL_0C : public AddressMode::Absolute<Operator::ASL>
{
    using Absolute::Absolute;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "0C: ASL !a"; }
};

// BBC d.0, r
// PC+=r  if d.0 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_13 : public AddressMode::DirectProgramCounterRelative<Operator::BB<0, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "13: BBC d.0, r"; }
};

// BBC d.1, r
// PC+=r  if d.1 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_33 : public AddressMode::DirectProgramCounterRelative<Operator::BB<1, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "33: BBC d.1, r"; }
};

// BBC d.2, r
// PC+=r  if d.2 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_53 : public AddressMode::DirectProgramCounterRelative<Operator::BB<2, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBC_53");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "53: BBC d.2, r"; }
};

// BBC d.3, r
// PC+=r  if d.3 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_73 : public AddressMode::DirectProgramCounterRelative<Operator::BB<3, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBC_73");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "73: BBC d.3, r"; }
};

// BBC d.4, r
// PC+=r  if d.4 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_93 : public AddressMode::DirectProgramCounterRelative<Operator::BB<4, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBC_93");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "93: BBC d.4, r"; }
};

// BBC d.5, r
// PC+=r  if d.5 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_B3 : public AddressMode::DirectProgramCounterRelative<Operator::BB<5, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "B3: BBC d.5, r"; }
};

// BBC d.6, r
// PC+=r  if d.6 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_D3 : public AddressMode::DirectProgramCounterRelative<Operator::BB<6, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBC_D3");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "D3: BBC d.6, r"; }
};

// BBC d.7, r
// PC+=r  if d.7 == 0    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBC_F3 : public AddressMode::DirectProgramCounterRelative<Operator::BB<7, false>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "F3: BBC d.7, r"; }
};

// BBS d.0, r
// PC+=r  if d.0 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_03 : public AddressMode::DirectProgramCounterRelative<Operator::BB<0, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBS_03");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "03: BBS d.0, r"; }
};

// BBS d.1, r
// PC+=r  if d.1 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_23 : public AddressMode::DirectProgramCounterRelative<Operator::BB<1, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "23: BBS d.1, r"; }
};

// BBS d.2, r
// PC+=r  if d.2 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_43 : public AddressMode::DirectProgramCounterRelative<Operator::BB<2, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBS_43");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "43: BBS d.2, r"; }
};

// BBS d.3, r
// PC+=r  if d.3 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_63 : public AddressMode::DirectProgramCounterRelative<Operator::BB<3, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBS_63");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "63: BBS d.3, r"; }
};

// BBS d.4, r
// PC+=r  if d.4 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_83 : public AddressMode::DirectProgramCounterRelative<Operator::BB<4, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BBS_83");
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "83: BBS d.4, r"; }
};

// BBS d.5, r
// PC+=r  if d.5 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_A3 : public AddressMode::DirectProgramCounterRelative<Operator::BB<5, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "A3: BBS d.5, r"; }
};

// BBS d.6, r
// PC+=r  if d.6 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_C3 : public AddressMode::DirectProgramCounterRelative<Operator::BB<6, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "C3: BBS d.6, r"; }
};

// BBS d.7, r
// PC+=r  if d.7 == 1    	[........]
// Direct Bit Program Counter Relative (3-Byte)
class BBS_E3 : public AddressMode::DirectProgramCounterRelative<Operator::BB<7, true>>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "E3: BBS d.7, r"; }
};

// BCC r
// PC+=r  if C == 0    	[........]
// Program Counter Relative (2-Byte)
class BCC_90 : public AddressMode::ProgramCounterRelative<Operator::B<State::c, false>>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "90: BCC r"; }
};

// BCS r
// PC+=r  if C == 1    	[........]
// Program Counter Relative (2-Byte)
class BCS_B0 : public AddressMode::ProgramCounterRelative<Operator::B<State::c, true>>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "B0: BCS r"; }
};

// BEQ r
// PC+=r  if Z == 1    	[........]
// Program Counter Relative (2-Byte)
class BEQ_F0 : public AddressMode::ProgramCounterRelative<Operator::BEQ>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "F0: BEQ r"; }
};

// BMI r
// PC+=r  if N == 1    	[........]
// Program Counter Relative (2-Byte)
class BMI_30 : public AddressMode::ProgramCounterRelative<Operator::BMI>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "30: BMI r"; }
};

// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
class BNE_D0 : public AddressMode::ProgramCounterRelative<Operator::BNE>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "D0: BNE r"; }
};

// BPL r
// PC+=r  if N == 0    	[........]
// Program Counter Relative (2-Byte)
class BPL_10 : public AddressMode::ProgramCounterRelative<Operator::BPL>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "10: BPL r"; }
};

// BVC r
// PC+=r  if V == 0    	[........]
// Program Counter Relative (2-Byte)
class BVC_50 : public AddressMode::ProgramCounterRelative<Operator::B<State::v, false>>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BVC_50");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "50: BVC r"; }
};

// BVS r
// PC+=r  if V == 1    	[........]
// Program Counter Relative (2-Byte)
class BVS_70 : public AddressMode::ProgramCounterRelative<Operator::B<State::v, true>>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BVS_70");
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "70: BVS r"; }
};

// BRA r
// PC+=r    	[........]
// Program Counter Relative (2-Byte)
class BRA_2F : public AddressMode::ProgramCounterRelative<Operator::BRA>
{
    using ProgramCounterRelative::ProgramCounterRelative;

    int execute() override
    {
        return 2 + applyOperand();
    }

    std::string opcodeToString() const override { return "2F: BRA r"; }
};

// BRK 
// Push PC and Flags, PC = [$FFDE]    	[...1.0..]
// Implied (1-Byte)
class BRK_0F : public AddressMode::Implied<Operator::BRK>
{
    using Implied::Implied;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("BRK_0F");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "0F: BRK "; }
};

// CALL !a
// (SP--)=PCh, (SP--)=PCl, PC=a    	[........]
// Absolute (3-Byte)
class CALL_3F : public AddressMode::Absolute_ControlFlow<Operator::CALL>
{
    using Absolute_ControlFlow::Absolute_ControlFlow;

    int execute() override
    {
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "3F: CALL !a"; }
};

// CBNE d+X, r
// CMP A, (d+X) then BNE    	[........]
// Direct Indexed Program Counter Relative (3-Byte)
class CBNE_DE : public AddressMode::DirectIndexedProgramCounterRelative<Operator::CBNE, State::X>
{
    using DirectIndexedProgramCounterRelative::DirectIndexedProgramCounterRelative;

    int execute() override
    {
        return 6 + applyOperand();
    }

    std::string opcodeToString() const override { return "DE: CBNE d+X, r"; }
};

// CBNE d, r
// CMP A, (d) then BNE    	[........]
// Direct Program Counter Relative (3-Byte)
class CBNE_2E : public AddressMode::DirectProgramCounterRelative<Operator::CBNE>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "2E: CBNE d, r"; }
};

// CLR1 d.0
// d.0 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_12 : public AddressMode::Direct<Operator::SET1<0, false>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "12: CLR1 d.0"; }
};

// CLR1 d.1
// d.1 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_32 : public AddressMode::Direct<Operator::SET1<1, false>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "32: CLR1 d.1"; }
};

// CLR1 d.2
// d.2 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_52 : public AddressMode::Direct<Operator::SET1<2, false>>
{
    using Direct::Direct;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CLR1_52");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "52: CLR1 d.2"; }
};

// CLR1 d.3
// d.3 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_72 : public AddressMode::Direct<Operator::SET1<3, false>>
{
    using Direct::Direct;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CLR1_72");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "72: CLR1 d.3"; }
};

// CLR1 d.4
// d.4 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_92 : public AddressMode::Direct<Operator::SET1<4, false>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "92: CLR1 d.4"; }
};

// CLR1 d.5
// d.5 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_B2 : public AddressMode::Direct<Operator::SET1<5, false>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "B2: CLR1 d.5"; }
};

// CLR1 d.6
// d.6 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_D2 : public AddressMode::Direct<Operator::SET1<6, false>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "D2: CLR1 d.6"; }
};

// CLR1 d.7
// d.7 = 0    	[........]
// Direct Bit (2-Byte)
class CLR1_F2 : public AddressMode::Direct<Operator::SET1<7, false>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "F2: CLR1 d.7"; }
};

// CLRC 
// C = 0    	[.......0]
// Implied (1-Byte)
class CLRC_60 : public AddressMode::Implied<Operator::SET<State::c, false>>
{
    using Implied::Implied;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "60: CLRC "; }
};

// CLRP 
// P = 0    	[..0.....]
// Implied (1-Byte)
class CLRP_20 : public AddressMode::Implied<Operator::SET<State::p, false>>
{
    using Implied::Implied;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "20: CLRP "; }
};

// CLRV 
// V = 0, H = 0    	[.0..0...]
// Implied (1-Byte)
class CLRV_E0 : public AddressMode::Implied<Operator::CLRV>
{
    using Implied::Implied;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CLRV_E0");
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "E0: CLRV "; }
};

// CMP (X), (Y)
// (X) - (Y)    	[N.....ZC]
// Indirect Indirect (1-Byte)
class CMP_79 : public AddressMode::IndirectIndirect<Operator::CMP>
{
    using IndirectIndirect::IndirectIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_79");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "79: CMP (X), (Y)"; }
};

// CMP A, #i
// A - i    	[N.....ZC]
// Register Immediate (2-Byte)
class CMP_68 : public AddressMode::RegisterImmediate<Operator::CMP, State::A>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "68: CMP A, #i"; }
};

// CMP A, (X)
// A - (X)    	[N.....ZC]
// Register Register Indirect (1-Byte)
class CMP_66 : public AddressMode::RegisterRegisterIndirect<Operator::CMP, State::A, State::X>
{
    using RegisterRegisterIndirect::RegisterRegisterIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_66");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "66: CMP A, (X)"; }
};

// CMP A, [d]+Y
// A - ([d]+Y)    	[N.....ZC]
// Register Direct Indirect Indexed (2-Byte)
class CMP_77 : public AddressMode::RegisterDirectIndirectIndexed<Operator::CMP, State::A, State::Y>
{
    using RegisterDirectIndirectIndexed::RegisterDirectIndirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_77");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "77: CMP A, [d]+Y"; }
};

// CMP A, [d+X]
// A - ([d+X])    	[N.....ZC]
// Register Direct Indexed Indirect (2-Byte)
class CMP_67 : public AddressMode::RegisterDirectIndexedIndirect<Operator::CMP, State::A, State::X>
{
    using RegisterDirectIndexedIndirect::RegisterDirectIndexedIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_67");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "67: CMP A, [d+X]"; }
};

// CMP A, d
// A - (d)    	[N.....ZC]
// Register Direct (2-Byte)
class CMP_64 : public AddressMode::RegisterDirect<Operator::CMP, State::A>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "64: CMP A, d"; }
};

// CMP A, d+X
// A - (d+X)    	[N.....ZC]
// Register Direct Indexed (2-Byte)
class CMP_74 : public AddressMode::RegisterDirectIndexed<Operator::CMP, State::A, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "74: CMP A, d+X"; }
};

// CMP A, !a
// A - (a)    	[N.....ZC]
// Register Absolute (3-Byte)
class CMP_65 : public AddressMode::RegisterAbsolute<Operator::CMP, State::A>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "65: CMP A, !a"; }
};

// CMP A, !a+X
// A - (a+X)    	[N.....ZC]
// Register Absolute Indexed (3-Byte)
class CMP_75 : public AddressMode::RegisterAbsoluteIndexed<Operator::CMP, State::A, State::X>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "75: CMP A, !a+X"; }
};

// CMP A, !a+Y
// A - (a+Y)    	[N.....ZC]
// Register Absolute Indexed (3-Byte)
class CMP_76 : public AddressMode::RegisterAbsoluteIndexed<Operator::CMP, State::A, State::Y>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_76");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "76: CMP A, !a+Y"; }
};

// CMP X, #i
// X - i    	[N.....ZC]
// Register Immediate (2-Byte)
class CMP_C8 : public AddressMode::RegisterImmediate<Operator::CMP, State::X>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "C8: CMP X, #i"; }
};

// CMP X, d
// X - (d)    	[N.....ZC]
// Register Direct (2-Byte)
class CMP_3E : public AddressMode::RegisterDirect<Operator::CMP, State::X>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_3E");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "3E: CMP X, d"; }
};

// CMP X, !a
// X - (a)    	[N.....ZC]
// Register Absolute (3-Byte)
class CMP_1E : public AddressMode::RegisterAbsolute<Operator::CMP, State::X>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("CMP_1E");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "1E: CMP X, !a"; }
};

// CMP Y, #i
// Y - i    	[N.....ZC]
// Register Immediate (2-Byte)
class CMP_AD : public AddressMode::RegisterImmediate<Operator::CMP, State::Y>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "AD: CMP Y, #i"; }
};

// CMP Y, d
// Y - (d)    	[N.....ZC]
// Register Direct (2-Byte)
class CMP_7E : public AddressMode::RegisterDirect<Operator::CMP, State::Y>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "7E: CMP Y, d"; }
};

// CMP Y, !a
// Y - (a)    	[N.....ZC]
// Register Absolute (3-Byte)
class CMP_5E : public AddressMode::RegisterAbsolute<Operator::CMP, State::Y>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "5E: CMP Y, !a"; }
};

// CMP dd, ds
// (dd) - (ds)    	[N.....ZC]
// Direct Direct (3-Byte)
class CMP_69 : public AddressMode::DirectDirect<Operator::CMP>
{
    using DirectDirect::DirectDirect;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "69: CMP dd, ds"; }
};

// CMP d, #i
// (d) - i    	[N.....ZC]
// Direct Immediate (3-Byte)
class CMP_78 : public AddressMode::DirectImmediate<Operator::CMP>
{
    using DirectImmediate::DirectImmediate;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "78: CMP d, #i"; }
};

// CMPW YA, d
// YA - (d)    	[N.....ZC]
// Y Accumulator Direct (2-Byte)
class CMPW_5A : public AddressMode::YAccumulatorDirect<Operator::CMPW>
{
    using YAccumulatorDirect::YAccumulatorDirect;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "5A: CMPW YA, d"; }
};

// DAA A
// decimal adjust for addition    	[N.....ZC]
// Register (1-Byte)
class DAA_DF : public AddressMode::Register<Operator::DAA, State::A>
{
    using Register::Register;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("DAA_DF");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "DF: DAA A"; }
};

// DAS A
// decimal adjust for subtraction    	[N.....ZC]
// Register (1-Byte)
class DAS_BE : public AddressMode::Register<Operator::DAS, State::A>
{
    using Register::Register;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("DAS_BE");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "BE: DAS A"; }
};

// DBNZ Y, r
// Y-- then JNZ    	[........]
// Register Program Counter Relative (2-Byte)
class DBNZ_FE : public AddressMode::RegisterProgramCounterRelative<Operator::DBNZ, State::Y>
{
    using RegisterProgramCounterRelative::RegisterProgramCounterRelative;

    int execute() override
    {
        return 4 + applyOperand();
    }

    std::string opcodeToString() const override { return "FE: DBNZ Y, r"; }
};

// DBNZ d, r
// (d)-- then JNZ    	[........]
// Direct Program Counter Relative (3-Byte)
class DBNZ_6E : public AddressMode::DirectProgramCounterRelative<Operator::DBNZ>
{
    using DirectProgramCounterRelative::DirectProgramCounterRelative;

    int execute() override
    {
        return 5 + applyOperand();
    }

    std::string opcodeToString() const override { return "6E: DBNZ d, r"; }
};

// DEC A
// A--    	[N.....Z.]
// Register (1-Byte)
class DEC_9C : public AddressMode::Register<Operator::DEC, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "9C: DEC A"; }
};

// DEC X
// X--    	[N.....Z.]
// Register (1-Byte)
class DEC_1D : public AddressMode::Register<Operator::DEC, State::X>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "1D: DEC X"; }
};

// DEC Y
// Y--    	[N.....Z.]
// Register (1-Byte)
class DEC_DC : public AddressMode::Register<Operator::DEC, State::Y>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "DC: DEC Y"; }
};

// DEC d
// (d)--    	[N.....Z.]
// Direct (2-Byte)
class DEC_8B : public AddressMode::Direct<Operator::DEC>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "8B: DEC d"; }
};

// DEC d+X
// (d+X)--    	[N.....Z.]
// Direct Indexed (2-Byte)
class DEC_9B : public AddressMode::DirectIndexed<Operator::DEC, State::X>
{
    using DirectIndexed::DirectIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "9B: DEC d+X"; }
};

// DEC !a
// (a)--    	[N.....Z.]
// Absolute (3-Byte)
class DEC_8C : public AddressMode::Absolute<Operator::DEC>
{
    using Absolute::Absolute;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "8C: DEC !a"; }
};

// DECW d
// Word (d)--    	[N.....Z.]
// Direct (2-Byte)
class DECW_1A : public AddressMode::Direct<Operator::DECW>
{
    using Direct::Direct;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("DECW_1A");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "1A: DECW d"; }
};

// DI 
// I = 0    	[.....0..]
// Implied (1-Byte)
class DI_C0 : public AddressMode::Implied<Operator::DI>
{
    using Implied::Implied;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("DI_C0");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "C0: DI "; }
};

// DIV YA, X
// A=YA/X, Y=mod(YA,X)    	[NV..H.Z.]
// Y Accumulator Index (1-Byte)
class DIV_9E : public AddressMode::YAccumulatorRegister<Operator::DIV, State::X>
{
    using YAccumulatorRegister::YAccumulatorRegister;

    int execute() override
    {
        return 12 + applyOperand();
    }

    std::string opcodeToString() const override { return "9E: DIV YA, X"; }
};

// EI 
// I = 1    	[.....1..]
// Implied (1-Byte)
class EI_A0 : public AddressMode::Implied<Operator::EI>
{
    using Implied::Implied;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EI_A0");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "A0: EI "; }
};

// EOR (X), (Y)
// (X) = (X) EOR (Y)    	[N.....Z.]
// Indirect Indirect (1-Byte)
class EOR_59 : public AddressMode::IndirectIndirect<Operator::EOR>
{
    using IndirectIndirect::IndirectIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_59");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "59: EOR (X), (Y)"; }
};

// EOR A, #i
// A = A EOR i    	[N.....Z.]
// Register Immediate (2-Byte)
class EOR_48 : public AddressMode::RegisterImmediate<Operator::EOR, State::A>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "48: EOR A, #i"; }
};

// EOR A, (X)
// A = A EOR (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
class EOR_46 : public AddressMode::RegisterRegisterIndirect<Operator::EOR, State::A, State::X>
{
    using RegisterRegisterIndirect::RegisterRegisterIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_46");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "46: EOR A, (X)"; }
};

// EOR A, [d]+Y
// A = A EOR ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
class EOR_57 : public AddressMode::RegisterDirectIndirectIndexed<Operator::EOR, State::A, State::Y>
{
    using RegisterDirectIndirectIndexed::RegisterDirectIndirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_57");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "57: EOR A, [d]+Y"; }
};

// EOR A, [d+X]
// A = A EOR ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
class EOR_47 : public AddressMode::RegisterDirectIndexedIndirect<Operator::EOR, State::A, State::X>
{
    using RegisterDirectIndexedIndirect::RegisterDirectIndexedIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_47");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "47: EOR A, [d+X]"; }
};

// EOR A, d
// A = A EOR (d)    	[N.....Z.]
// Register Direct (2-Byte)
class EOR_44 : public AddressMode::RegisterDirect<Operator::EOR, State::A>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "44: EOR A, d"; }
};

// EOR A, d+X
// A = A EOR (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
class EOR_54 : public AddressMode::RegisterDirectIndexed<Operator::EOR, State::A, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "54: EOR A, d+X"; }
};

// EOR A, !a
// A = A EOR (a)    	[N.....Z.]
// Register Absolute (3-Byte)
class EOR_45 : public AddressMode::RegisterAbsolute<Operator::EOR, State::A>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_45");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "45: EOR A, !a"; }
};

// EOR A, !a+X
// A = A EOR (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class EOR_55 : public AddressMode::RegisterAbsoluteIndexed<Operator::EOR, State::A, State::X>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_55");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "55: EOR A, !a+X"; }
};

// EOR A, !a+Y
// A = A EOR (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class EOR_56 : public AddressMode::RegisterAbsoluteIndexed<Operator::EOR, State::A, State::Y>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_56");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "56: EOR A, !a+Y"; }
};

// EOR dd, ds
// (dd) = (dd) EOR (ds)    	[N.....Z.]
// Direct Direct (3-Byte)
class EOR_49 : public AddressMode::DirectDirect<Operator::EOR>
{
    using DirectDirect::DirectDirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR_49");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "49: EOR dd, ds"; }
};

// EOR d, #i
// (d) = (d) EOR i    	[N.....Z.]
// Direct Immediate (3-Byte)
class EOR_58 : public AddressMode::DirectImmediate<Operator::EOR>
{
    using DirectImmediate::DirectImmediate;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "58: EOR d, #i"; }
};

// EOR1 C, m.b
// C = C EOR (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
class EOR1_8A : public AddressMode::CarryMemoryBit<Operator::EOR1>
{
    using CarryMemoryBit::CarryMemoryBit;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("EOR1_8A");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "8A: EOR1 C, m.b"; }
};

// INC A
// A++    	[N.....Z.]
// Register (1-Byte)
class INC_BC : public AddressMode::Register<Operator::INC, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "BC: INC A"; }
};

// INC X
// X++    	[N.....Z.]
// Register (1-Byte)
class INC_3D : public AddressMode::Register<Operator::INC, State::X>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "3D: INC X"; }
};

// INC Y
// Y++    	[N.....Z.]
// Register (1-Byte)
class INC_FC : public AddressMode::Register<Operator::INC, State::Y>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "FC: INC Y"; }
};

// INC d
// (d)++    	[N.....Z.]
// Direct (2-Byte)
class INC_AB : public AddressMode::Direct<Operator::INC>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AB: INC d"; }
};

// INC d+X
// (d+X)++    	[N.....Z.]
// Direct Indexed (2-Byte)
class INC_BB : public AddressMode::DirectIndexed<Operator::INC, State::X>
{
    using DirectIndexed::DirectIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "BB: INC d+X"; }
};

// INC !a
// (a)++    	[N.....Z.]
// Absolute (3-Byte)
class INC_AC : public AddressMode::Absolute<Operator::INC>
{
    using Absolute::Absolute;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "AC: INC !a"; }
};

// INCW d
// Word (d)++    	[N.....Z.]
// Direct (2-Byte)
class INCW_3A : public AddressMode::Direct<Operator::INCW>
{
    using Direct::Direct;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "3A: INCW d"; }
};

// JMP [!a+X]
// PC = [a+X]    	[........]
// Absolute Indexed Indirect (3-Byte)
class JMP_1F : public AddressMode::AbsoluteIndexedIndirect<Operator::JMP, State::X>
{
    using AbsoluteIndexedIndirect::AbsoluteIndexedIndirect;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "1F: JMP [!a+X]"; }
};

// JMP !a
// PC = a    	[........]
// Absolute (3-Byte)
class JMP_5F : public AddressMode::Absolute_ControlFlow<Operator::JMP>
{
    using Absolute_ControlFlow::Absolute_ControlFlow;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "5F: JMP !a"; }
};

// LSR A
// Right shift A: 0->high, low->C    	[N.....ZC]
// Register (1-Byte)
class LSR_5C : public AddressMode::Register<Operator::LSR, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "5C: LSR A"; }
};

// LSR d
// Right shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
class LSR_4B : public AddressMode::Direct<Operator::LSR>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "4B: LSR d"; }
};

// LSR d+X
// Right shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
class LSR_5B : public AddressMode::DirectIndexed<Operator::LSR, State::X>
{
    using DirectIndexed::DirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("LSR_5B");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "5B: LSR d+X"; }
};

// LSR !a
// Right shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
class LSR_4C : public AddressMode::Absolute<Operator::LSR>
{
    using Absolute::Absolute;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "4C: LSR !a"; }
};

// MOV (X)+, A
// (X++) = A      (no read)    	[........]
// Register Indirect Increment Register (1-Byte)
class MOV_AF : public AddressMode::RegisterIndirectIncrementRegister<Operator::MOV, State::X, State::A>
{
    using RegisterIndirectIncrementRegister::RegisterIndirectIncrementRegister;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AF: MOV (X)+, A"; }
};

// MOV (X), A
// (X) = A        (read)    	[........]
// Register Indirect Register (1-Byte)
class MOV_C6 : public AddressMode::RegisterIndirectRegister<Operator::MOV, State::X, State::A>
{
    using RegisterIndirectRegister::RegisterIndirectRegister;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "C6: MOV (X), A"; }
};

// MOV [d]+Y, A
// ([d]+Y) = A    (read)    	[........]
// Direct Indirect Indexed Register (2-Byte)
class MOV_D7 : public AddressMode::DirectIndirectIndexedRegister<Operator::MOV, State::Y, State::A>
{
    using DirectIndirectIndexedRegister::DirectIndirectIndexedRegister;

    int execute() override
    {
        return  7 + applyOperand();
    }

    std::string opcodeToString() const override { return "D7: MOV [d]+Y, A"; }
};

// MOV [d+X], A
// ([d+X]) = A    (read)    	[........]
// Direct Indexed Indirect Register (2-Byte)
class MOV_C7 : public AddressMode::DirectIndexedIndirectRegister<Operator::MOV, State::X, State::A>
{
    using DirectIndexedIndirectRegister::DirectIndexedIndirectRegister;

    int execute() override
    {
        return  7 + applyOperand();
    }

    std::string opcodeToString() const override { return "C7: MOV [d+X], A"; }
};

// MOV A, #i
// A = i    	[N.....Z.]
// Register Immediate (2-Byte)
class MOV_E8 : public AddressMode::RegisterImmediate<Operator::MOV_SignedResult, State::A>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "E8: MOV A, #i"; }
};

// MOV A, (X)
// A = (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
class MOV_E6 : public AddressMode::RegisterRegisterIndirect<Operator::MOV_SignedResult, State::A, State::X>
{
    using RegisterRegisterIndirect::RegisterRegisterIndirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "E6: MOV A, (X)"; }
};

// MOV A, (X)+
// A = (X++)    	[N.....Z.]
// Register Register Indirect Increment (1-Byte)
class MOV_BF : public AddressMode::RegisterRegisterIndirectIncrement<Operator::MOV_SignedResult, State::A, State::X>
{
    using RegisterRegisterIndirectIncrement::RegisterRegisterIndirectIncrement;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("MOV_BF");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "BF: MOV A, (X)+"; }
};

// MOV A, [d]+Y
// A = ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
class MOV_F7 : public AddressMode::RegisterDirectIndirectIndexed<Operator::MOV_SignedResult, State::A, State::Y>
{
    using RegisterDirectIndirectIndexed::RegisterDirectIndirectIndexed;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "F7: MOV A, [d]+Y"; }
};

// MOV A, [d+X]
// A = ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
class MOV_E7 : public AddressMode::RegisterDirectIndexedIndirect<Operator::MOV_SignedResult, State::A, State::X>
{
    using RegisterDirectIndexedIndirect::RegisterDirectIndexedIndirect;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "E7: MOV A, [d+X]"; }
};

// MOV A, X
// A = X    	[N.....Z.]
// Register Register (1-Byte)
class MOV_7D : public AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::A, State::X>
{
    using RegisterRegister::RegisterRegister;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "7D: MOV A, X"; }
};

// MOV A, Y
// A = Y    	[N.....Z.]
// Register Register (1-Byte)
class MOV_DD : public AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::A, State::Y>
{
    using RegisterRegister::RegisterRegister;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "DD: MOV A, Y"; }
};

// MOV A, d
// A = (d)    	[N.....Z.]
// Register Direct (2-Byte)
class MOV_E4 : public AddressMode::RegisterDirect<Operator::MOV_SignedResult, State::A>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "E4: MOV A, d"; }
};

// MOV A, d+X
// A = (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
class MOV_F4 : public AddressMode::RegisterDirectIndexed<Operator::MOV_SignedResult, State::A, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "F4: MOV A, d+X"; }
};

// MOV A, !a
// A = (a)    	[N.....Z.]
// Register Absolute (3-Byte)
class MOV_E5 : public AddressMode::RegisterAbsolute<Operator::MOV_SignedResult, State::A>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "E5: MOV A, !a"; }
};

// MOV A, !a+X
// A = (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class MOV_F5 : public AddressMode::RegisterAbsoluteIndexed<Operator::MOV_SignedResult, State::A, State::X>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "F5: MOV A, !a+X"; }
};

// MOV A, !a+Y
// A = (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class MOV_F6 : public AddressMode::RegisterAbsoluteIndexed<Operator::MOV_SignedResult, State::A, State::Y>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "F6: MOV A, !a+Y"; }
};

// MOV SP, X
// SP = X    	[........]
// Register Register (1-Byte)
class MOV_BD : public AddressMode::RegisterRegister<Operator::MOV, State::SP, State::X>
{
    using RegisterRegister::RegisterRegister;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "BD: MOV SP, X"; }
};

// MOV X, #i
// X = i    	[N.....Z.]
// Register Immediate (2-Byte)
class MOV_CD : public AddressMode::RegisterImmediate<Operator::MOV_SignedResult, State::X>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "CD: MOV X, #i"; }
};

// MOV X, A
// X = A    	[N.....Z.]
// Register Register (1-Byte)
class MOV_5D : public AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::X, State::A>
{
    using RegisterRegister::RegisterRegister;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "5D: MOV X, A"; }
};

// MOV X, SP
// X = SP    	[N.....Z.]
// Register Register (1-Byte)
class MOV_9D : public AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::X, State::SP>
{
    using RegisterRegister::RegisterRegister;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("MOV_9D");
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "9D: MOV X, SP"; }
};

// MOV X, d
// X = (d)    	[N.....Z.]
// Register Direct (2-Byte)
class MOV_F8 : public AddressMode::RegisterDirect<Operator::MOV_SignedResult, State::X>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "F8: MOV X, d"; }
};

// MOV X, d+Y
// X = (d+Y)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
class MOV_F9 : public AddressMode::RegisterDirectIndexed<Operator::MOV_SignedResult, State::X, State::Y>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("MOV_F9");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "F9: MOV X, d+Y"; }
};

// MOV X, !a
// X = (a)    	[N.....Z.]
// Register Absolute (3-Byte)
class MOV_E9 : public AddressMode::RegisterAbsolute<Operator::MOV_SignedResult, State::X>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "E9: MOV X, !a"; }
};

// MOV Y, #i
// Y = i    	[N.....Z.]
// Register Immediate (2-Byte)
class MOV_8D : public AddressMode::RegisterImmediate<Operator::MOV_SignedResult, State::Y>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "8D: MOV Y, #i"; }
};

// MOV Y, A
// Y = A    	[N.....Z.]
// Register Register (1-Byte)
class MOV_FD : public AddressMode::RegisterRegister<Operator::MOV_SignedResult, State::Y, State::A>
{
    using RegisterRegister::RegisterRegister;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "FD: MOV Y, A"; }
};

// MOV Y, d
// Y = (d)    	[N.....Z.]
// Register Direct (2-Byte)
class MOV_EB : public AddressMode::RegisterDirect<Operator::MOV_SignedResult, State::Y>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "EB: MOV Y, d"; }
};

// MOV Y, d+X
// Y = (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
class MOV_FB : public AddressMode::RegisterDirectIndexed<Operator::MOV_SignedResult, State::Y, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "FB: MOV Y, d+X"; }
};

// MOV Y, !a
// Y = (a)    	[N.....Z.]
// Register Absolute (3-Byte)
class MOV_EC : public AddressMode::RegisterAbsolute<Operator::MOV_SignedResult, State::Y>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "EC: MOV Y, !a"; }
};

// MOV dd, ds
// (dd) = (ds)    (no read)    	[........]
// Direct Direct (3-Byte)
class MOV_FA : public AddressMode::DirectDirect<Operator::MOV>
{
    using DirectDirect::DirectDirect;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "FA: MOV dd, ds"; }
};

// MOV d+X, A
// (d+X) = A      (read)    	[........]
// Direct Indexed Register (2-Byte)
class MOV_D4 : public AddressMode::DirectIndexedRegister<Operator::MOV, State::X, State::A>
{
    using DirectIndexedRegister::DirectIndexedRegister;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "D4: MOV d+X, A"; }
};

// MOV d+X, Y
// (d+X) = Y      (read)    	[........]
// Direct Indexed Register (2-Byte)
class MOV_DB : public AddressMode::DirectIndexedRegister<Operator::MOV, State::X, State::Y>
{
    using DirectIndexedRegister::DirectIndexedRegister;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "DB: MOV d+X, Y"; }
};

// MOV d+Y, X
// (d+Y) = X      (read)    	[........]
// Direct Indexed Register (2-Byte)
class MOV_D9 : public AddressMode::DirectIndexedRegister<Operator::MOV, State::Y, State::X>
{
    using DirectIndexedRegister::DirectIndexedRegister;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("MOV_D9");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "D9: MOV d+Y, X"; }
};

// MOV d, #i
// (d) = i        (read)    	[........]
// Direct Immediate (3-Byte)
class MOV_8F : public AddressMode::DirectImmediate<Operator::MOV>
{
    using DirectImmediate::DirectImmediate;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "8F: MOV d, #i"; }
};

// MOV d, A
// (d) = A        (read)    	[........]
// Direct Register (2-Byte)
class MOV_C4 : public AddressMode::DirectRegister<Operator::MOV, State::A>
{
    using DirectRegister::DirectRegister;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "C4: MOV d, A"; }
};

// MOV d, X
// (d) = X        (read)    	[........]
// Direct Register (2-Byte)
class MOV_D8 : public AddressMode::DirectRegister<Operator::MOV, State::X>
{
    using DirectRegister::DirectRegister;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "D8: MOV d, X"; }
};

// MOV d, Y
// (d) = Y        (read)    	[........]
// Direct Register (2-Byte)
class MOV_CB : public AddressMode::DirectRegister<Operator::MOV, State::Y>
{
    using DirectRegister::DirectRegister;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "CB: MOV d, Y"; }
};

// MOV !a+X, A
// (a+X) = A      (read)    	[........]
// Absolute Indexed Register (3-Byte)
class MOV_D5 : public AddressMode::AbsoluteIndexedRegister<Operator::MOV, State::X, State::A>
{
    using AbsoluteIndexedRegister::AbsoluteIndexedRegister;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "D5: MOV !a+X, A"; }
};

// MOV !a+Y, A
// (a+Y) = A      (read)    	[........]
// Absolute Indexed Register (3-Byte)
class MOV_D6 : public AddressMode::AbsoluteIndexedRegister<Operator::MOV, State::Y, State::A>
{
    using AbsoluteIndexedRegister::AbsoluteIndexedRegister;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "D6: MOV !a+Y, A"; }
};

// MOV !a, A
// (a) = A        (read)    	[........]
// Absolute Register (3-Byte)
class MOV_C5 : public AddressMode::AbsoluteRegister<Operator::MOV, State::A>
{
    using AbsoluteRegister::AbsoluteRegister;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "C5: MOV !a, A"; }
};

// MOV !a, X
// (a) = X        (read)    	[........]
// Absolute Register (3-Byte)
class MOV_C9 : public AddressMode::AbsoluteRegister<Operator::MOV, State::X>
{
    using AbsoluteRegister::AbsoluteRegister;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "C9: MOV !a, X"; }
};

// MOV !a, Y
// (a) = Y        (read)    	[........]
// Absolute Register (3-Byte)
class MOV_CC : public AddressMode::AbsoluteRegister<Operator::MOV, State::Y>
{
    using AbsoluteRegister::AbsoluteRegister;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "CC: MOV !a, Y"; }
};

// MOV1 C, m.b
// C = (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
class MOV1_AA : public AddressMode::CarryMemoryBit<Operator::MOV1>
{
    using CarryMemoryBit::CarryMemoryBit;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("MOV1_AA");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AA: MOV1 C, m.b"; }
};

// MOV1 m.b, C
// (m.b) = C    	[........]
// Memory Bit Carry (3-Byte)
class MOV1_CA : public AddressMode::MemoryBitCarry<Operator::MOV1>
{
    using MemoryBitCarry::MemoryBitCarry;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("MOV1_CA");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "CA: MOV1 m.b, C"; }
};

// MOVW YA, d
// YA = word (d)    	[N.....Z.]
// Y Accumulator Direct (2-Byte)
class MOVW_BA : public AddressMode::YAccumulatorDirect<Operator::MOVW_SignedResult>
{
    using YAccumulatorDirect::YAccumulatorDirect;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "BA: MOVW YA, d"; }
};

// MOVW d, YA
// word (d) = YA  (read low only)    	[........]
// Direct Y Accumulator (2-Byte)
class MOVW_DA : public AddressMode::DirectYAccumulator<Operator::MOVW>
{
    using DirectYAccumulator::DirectYAccumulator;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "DA: MOVW d, YA"; }
};

// MUL YA
// YA = Y * A, NZ on Y only    	[N.....Z.]
// Y Accumulator (1-Byte)
class MUL_CF : public AddressMode::YAccumulator<Operator::MUL>
{
    using YAccumulator::YAccumulator;

    int execute() override
    {
        return  9 + applyOperand();
    }

    std::string opcodeToString() const override { return "CF: MUL YA"; }
};

// NOP 
// do nothing    	[........]
// Implied (1-Byte)
class NOP_00 : public AddressMode::Implied<Operator::NOP>
{
    using Implied::Implied;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "00: NOP "; }
};

// NOT1 m.b
// m.b = ~m.b    	[........]
// Memory Bit (3-Byte)
class NOT1_EA : public AddressMode::MemoryBit<Operator::NOT1>
{
    using MemoryBit::MemoryBit;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("NOT1_EA");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "EA: NOT1 m.b"; }
};

// NOTC 
// C = !C    	[.......C]
// Implied (1-Byte)
class NOTC_ED : public AddressMode::Implied<Operator::NOTC>
{
    using Implied::Implied;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "ED: NOTC "; }
};

// OR (X), (Y)
// (X) = (X) | (Y)    	[N.....Z.]
// Indirect Indirect (1-Byte)
class OR_19 : public AddressMode::IndirectIndirect<Operator::OR>
{
    using IndirectIndirect::IndirectIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR_19");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "19: OR (X), (Y)"; }
};

// OR A, #i
// A = A | i    	[N.....Z.]
// Register Immediate (2-Byte)
class OR_08 : public AddressMode::RegisterImmediate<Operator::OR, State::A>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "08: OR A, #i"; }
};

// OR A, (X)
// A = A | (X)    	[N.....Z.]
// Register Register Indirect (1-Byte)
class OR_06 : public AddressMode::RegisterRegisterIndirect<Operator::OR, State::A, State::X>
{
    using RegisterRegisterIndirect::RegisterRegisterIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR_06");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "06: OR A, (X)"; }
};

// OR A, [d]+Y
// A = A | ([d]+Y)    	[N.....Z.]
// Register Direct Indirect Indexed (2-Byte)
class OR_17 : public AddressMode::RegisterDirectIndirectIndexed<Operator::OR, State::A, State::Y>
{
    using RegisterDirectIndirectIndexed::RegisterDirectIndirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR_17");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "17: OR A, [d]+Y"; }
};

// OR A, [d+X]
// A = A | ([d+X])    	[N.....Z.]
// Register Direct Indexed Indirect (2-Byte)
class OR_07 : public AddressMode::RegisterDirectIndexedIndirect<Operator::OR, State::A, State::X>
{
    using RegisterDirectIndexedIndirect::RegisterDirectIndexedIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR_07");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "07: OR A, [d+X]"; }
};

// OR A, d
// A = A | (d)    	[N.....Z.]
// Register Direct (2-Byte)
class OR_04 : public AddressMode::RegisterDirect<Operator::OR, State::A>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "04: OR A, d"; }
};

// OR A, d+X
// A = A | (d+X)    	[N.....Z.]
// Register Direct Indexed (2-Byte)
class OR_14 : public AddressMode::RegisterDirectIndexed<Operator::OR, State::A, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "14: OR A, d+X"; }
};

// OR A, !a
// A = A | (a)    	[N.....Z.]
// Register Absolute (3-Byte)
class OR_05 : public AddressMode::RegisterAbsolute<Operator::OR, State::A>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "05: OR A, !a"; }
};

// OR A, !a+X
// A = A | (a+X)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class OR_15 : public AddressMode::RegisterAbsoluteIndexed<Operator::OR, State::A, State::X>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "15: OR A, !a+X"; }
};

// OR A, !a+Y
// A = A | (a+Y)    	[N.....Z.]
// Register Absolute Indexed (3-Byte)
class OR_16 : public AddressMode::RegisterAbsoluteIndexed<Operator::OR, State::A, State::Y>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR_16");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "16: OR A, !a+Y"; }
};

// OR dd, ds
// (dd) = (dd) | (ds)    	[N.....Z.]
// Direct Direct (3-Byte)
class OR_09 : public AddressMode::DirectDirect<Operator::OR>
{
    using DirectDirect::DirectDirect;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "09: OR dd, ds"; }
};

// OR d, #i
// (d) = (d) | i    	[N.....Z.]
// Direct Immediate (3-Byte)
class OR_18 : public AddressMode::DirectImmediate<Operator::OR>
{
    using DirectImmediate::DirectImmediate;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR_18");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "18: OR d, #i"; }
};

// OR1 C, /m.b
// C = C | ~(m.b)    	[.......C]
// Carry Negated Memory Bit (3-Byte)
class OR1_2A : public AddressMode::CarryNegatedMemoryBit<Operator::OR1>
{
    using CarryNegatedMemoryBit::CarryNegatedMemoryBit;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR1_2A");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "2A: OR1 C, /m.b"; }
};

// OR1 C, m.b
// C = C | (m.b)    	[.......C]
// Carry Memory Bit (3-Byte)
class OR1_0A : public AddressMode::CarryMemoryBit<Operator::OR1>
{
    using CarryMemoryBit::CarryMemoryBit;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("OR1_0A");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "0A: OR1 C, m.b"; }
};

// PCALL u
// CALL $FF00+u    	[........]
// U Page (2-Byte)
class PCALL_4F : public AddressMode::UPage<Operator::PCALL>
{
    using UPage::UPage;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("PCALL_4F");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "4F: PCALL u"; }
};

// POP A
// A = (++SP)    	[........]
// Register (1-Byte)
class POP_AE : public AddressMode::Register<Operator::POP, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "AE: POP A"; }
};

// POP PSW
// Flags = (++SP)    	[NVPBHIZC]
// Register (1-Byte)
class POP_8E : public AddressMode::Register<Operator::POP, State::PSW>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "8E: POP PSW"; }
};

// POP X
// X = (++SP)    	[........]
// Register (1-Byte)
class POP_CE : public AddressMode::Register<Operator::POP, State::X>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "CE: POP X"; }
};

// POP Y
// Y = (++SP)    	[........]
// Register (1-Byte)
class POP_EE : public AddressMode::Register<Operator::POP, State::Y>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "EE: POP Y"; }
};

// PUSH A
// (SP--) = A    	[........]
// Register (1-Byte)
class PUSH_2D : public AddressMode::Register<Operator::PUSH, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "2D: PUSH A"; }
};

// PUSH PSW
// (SP--) = Flags    	[........]
// Register (1-Byte)
class PUSH_0D : public AddressMode::Register<Operator::PUSH, State::PSW>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "0D: PUSH PSW"; }
};

// PUSH X
// (SP--) = X    	[........]
// Register (1-Byte)
class PUSH_4D : public AddressMode::Register<Operator::PUSH, State::X>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "4D: PUSH X"; }
};

// PUSH Y
// (SP--) = Y    	[........]
// Register (1-Byte)
class PUSH_6D : public AddressMode::Register<Operator::PUSH, State::Y>
{
    using Register::Register;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "6D: PUSH Y"; }
};

// RET 
// Pop PC    	[........]
// Implied (1-Byte)
class RET_6F : public AddressMode::Implied<Operator::RET>
{
    using Implied::Implied;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "6F: RET "; }
};

// RET1 
// Pop Flags, PC    	[NVPBHIZC]
// Implied (1-Byte)
class RET1_7F : public AddressMode::Implied<Operator::RET1>
{
    using Implied::Implied;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("RET1_7F");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "7F: RET1 "; }
};

// ROL A
// Left shift A: low=C, C=high    	[N.....ZC]
// Register (1-Byte)
class ROL_3C : public AddressMode::Register<Operator::ROL, State::A>
{
    using Register::Register;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROL_3C");
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "3C: ROL A"; }
};

// ROL d
// Left shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
class ROL_2B : public AddressMode::Direct<Operator::ROL>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "2B: ROL d"; }
};

// ROL d+X
// Left shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
class ROL_3B : public AddressMode::DirectIndexed<Operator::ROL, State::X>
{
    using DirectIndexed::DirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROL_3B");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "3B: ROL d+X"; }
};

// ROL !a
// Left shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
class ROL_2C : public AddressMode::Absolute<Operator::ROL>
{
    using Absolute::Absolute;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROL_2C");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "2C: ROL !a"; }
};

// ROR A
// Right shift A: high=C, C=low    	[N.....ZC]
// Register (1-Byte)
class ROR_7C : public AddressMode::Register<Operator::ROR, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "7C: ROR A"; }
};

// ROR d
// Right shift (d) as above    	[N.....ZC]
// Direct (2-Byte)
class ROR_6B : public AddressMode::Direct<Operator::ROR>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "6B: ROR d"; }
};

// ROR d+X
// Right shift (d+X) as above    	[N.....ZC]
// Direct Indexed (2-Byte)
class ROR_7B : public AddressMode::DirectIndexed<Operator::ROR, State::X>
{
    using DirectIndexed::DirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROR_7B");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "7B: ROR d+X"; }
};

// ROR !a
// Right shift (a) as above    	[N.....ZC]
// Absolute (3-Byte)
class ROR_6C : public AddressMode::Absolute<Operator::ROR>
{
    using Absolute::Absolute;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("ROR_6C");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "6C: ROR !a"; }
};

// SBC (X), (Y)
// (X) = (X)-(Y)-!C    	[NV..H.ZC]
// Indirect Indirect (1-Byte)
class SBC_B9 : public AddressMode::IndirectIndirect<Operator::SBC>
{
    using IndirectIndirect::IndirectIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_B9");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "B9: SBC (X), (Y)"; }
};

// SBC A, #i
// A = A-i-!C    	[NV..H.ZC]
// Register Immediate (2-Byte)
class SBC_A8 : public AddressMode::RegisterImmediate<Operator::SBC, State::A>
{
    using RegisterImmediate::RegisterImmediate;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "A8: SBC A, #i"; }
};

// SBC A, (X)
// A = A-(X)-!C    	[NV..H.ZC]
// Register Register Indirect (1-Byte)
class SBC_A6 : public AddressMode::RegisterRegisterIndirect<Operator::SBC, State::A, State::X>
{
    using RegisterRegisterIndirect::RegisterRegisterIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_A6");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "A6: SBC A, (X)"; }
};

// SBC A, [d]+Y
// A = A-([d]+Y)-!C    	[NV..H.ZC]
// Register Direct Indirect Indexed (2-Byte)
class SBC_B7 : public AddressMode::RegisterDirectIndirectIndexed<Operator::SBC, State::A, State::Y>
{
    using RegisterDirectIndirectIndexed::RegisterDirectIndirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_B7");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "B7: SBC A, [d]+Y"; }
};

// SBC A, [d+X]
// A = A-([d+X])-!C    	[NV..H.ZC]
// Register Direct Indexed Indirect (2-Byte)
class SBC_A7 : public AddressMode::RegisterDirectIndexedIndirect<Operator::SBC, State::A, State::X>
{
    using RegisterDirectIndexedIndirect::RegisterDirectIndexedIndirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_A7");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "A7: SBC A, [d+X]"; }
};

// SBC A, d
// A = A-(d)-!C    	[NV..H.ZC]
// Register Direct (2-Byte)
class SBC_A4 : public AddressMode::RegisterDirect<Operator::SBC, State::A>
{
    using RegisterDirect::RegisterDirect;

    int execute() override
    {
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "A4: SBC A, d"; }
};

// SBC A, d+X
// A = A-(d+X)-!C    	[NV..H.ZC]
// Register Direct Indexed (2-Byte)
class SBC_B4 : public AddressMode::RegisterDirectIndexed<Operator::SBC, State::A, State::X>
{
    using RegisterDirectIndexed::RegisterDirectIndexed;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_B4");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "B4: SBC A, d+X"; }
};

// SBC A, !a
// A = A-(a)-!C    	[NV..H.ZC]
// Register Absolute (3-Byte)
class SBC_A5 : public AddressMode::RegisterAbsolute<Operator::SBC, State::A>
{
    using RegisterAbsolute::RegisterAbsolute;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "A5: SBC A, !a"; }
};

// SBC A, !a+X
// A = A-(a+X)-!C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
class SBC_B5 : public AddressMode::RegisterAbsoluteIndexed<Operator::SBC, State::A, State::X>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "B5: SBC A, !a+X"; }
};

// SBC A, !a+Y
// A = A-(a+Y)-!C    	[NV..H.ZC]
// Register Absolute Indexed (3-Byte)
class SBC_B6 : public AddressMode::RegisterAbsoluteIndexed<Operator::SBC, State::A, State::Y>
{
    using RegisterAbsoluteIndexed::RegisterAbsoluteIndexed;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "B6: SBC A, !a+Y"; }
};

// SBC dd, ds
// (dd) = (dd)-(ds)-!C    	[NV..H.ZC]
// Direct Direct (3-Byte)
class SBC_A9 : public AddressMode::DirectDirect<Operator::SBC>
{
    using DirectDirect::DirectDirect;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_A9");
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "A9: SBC dd, ds"; }
};

// SBC d, #i
// (d) = (d)-i-!C    	[NV..H.ZC]
// Direct Immediate (3-Byte)
class SBC_B8 : public AddressMode::DirectImmediate<Operator::SBC>
{
    using DirectImmediate::DirectImmediate;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SBC_B8");
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "B8: SBC d, #i"; }
};

// SET1 d.0
// d.0 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_02 : public AddressMode::Direct<Operator::SET1<0, true>>
{
    using Direct::Direct;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SET1_02");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "02: SET1 d.0"; }
};

// SET1 d.1
// d.1 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_22 : public AddressMode::Direct<Operator::SET1<1, true>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "22: SET1 d.1"; }
};

// SET1 d.2
// d.2 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_42 : public AddressMode::Direct<Operator::SET1<2, true>>
{
    using Direct::Direct;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SET1_42");
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "42: SET1 d.2"; }
};

// SET1 d.3
// d.3 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_62 : public AddressMode::Direct<Operator::SET1<3, true>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "62: SET1 d.3"; }
};

// SET1 d.4
// d.4 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_82 : public AddressMode::Direct<Operator::SET1<4, true>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "82: SET1 d.4"; }
};

// SET1 d.5
// d.5 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_A2 : public AddressMode::Direct<Operator::SET1<5, true>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "A2: SET1 d.5"; }
};

// SET1 d.6
// d.6 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_C2 : public AddressMode::Direct<Operator::SET1<6, true>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "C2: SET1 d.6"; }
};

// SET1 d.7
// d.7 = 1    	[........]
// Direct Bit (2-Byte)
class SET1_E2 : public AddressMode::Direct<Operator::SET1<7, true>>
{
    using Direct::Direct;

    int execute() override
    {
        return  4 + applyOperand();
    }

    std::string opcodeToString() const override { return "E2: SET1 d.7"; }
};

// SETC 
// C = 1    	[.......1]
// Implied (1-Byte)
class SETC_80 : public AddressMode::Implied<Operator::SET<State::c, true>>
{
    using Implied::Implied;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "80: SETC "; }
};

// SETP 
// P = 1    	[..1.....]
// Implied (1-Byte)
class SETP_40 : public AddressMode::Implied<Operator::SET<State::p, true>>
{
    using Implied::Implied;

    int execute() override
    {
        return  2 + applyOperand();
    }

    std::string opcodeToString() const override { return "40: SETP "; }
};

// SLEEP 
// Halts the processor    	[........]
// Implied (1-Byte)
class SLEEP_EF : public AddressMode::Implied<Operator::SLEEP>
{
    using Implied::Implied;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("SLEEP_EF");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "EF: SLEEP "; }
};

// STOP 
// Halts the processor    	[........]
// Implied (1-Byte)
class STOP_FF : public AddressMode::Implied<Operator::STOP>
{
    using Implied::Implied;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("STOP_FF");
        return  3 + applyOperand();
    }

    std::string opcodeToString() const override { return "FF: STOP "; }
};

// SUBW YA, d
// YA  = YA - (d), H on high byte    	[NV..H.ZC]
// Y Accumulator Direct (2-Byte)
class SUBW_9A : public AddressMode::YAccumulatorDirect<Operator::SUBW>
{
    using YAccumulatorDirect::YAccumulatorDirect;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "9A: SUBW YA, d"; }
};

// TCALL 0
// CALL [$FFDE]    	[........]
// Table (1-Byte)
class TCALL_01 : public AddressMode::Table<Operator::TCALL, 0>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_01");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "01: TCALL 0"; }
};

// TCALL 1
// CALL [$FFDC]    	[........]
// Table (1-Byte)
class TCALL_11 : public AddressMode::Table<Operator::TCALL, 1>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_11");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "11: TCALL 1"; }
};

// TCALL 2
// CALL [$FFDA]    	[........]
// Table (1-Byte)
class TCALL_21 : public AddressMode::Table<Operator::TCALL, 2>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_21");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "21: TCALL 2"; }
};

// TCALL 3
// CALL [$FFD8]    	[........]
// Table (1-Byte)
class TCALL_31 : public AddressMode::Table<Operator::TCALL, 3>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_31");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "31: TCALL 3"; }
};

// TCALL 4
// CALL [$FFD6]    	[........]
// Table (1-Byte)
class TCALL_41 : public AddressMode::Table<Operator::TCALL, 4>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_41");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "41: TCALL 4"; }
};

// TCALL 5
// CALL [$FFD4]    	[........]
// Table (1-Byte)
class TCALL_51 : public AddressMode::Table<Operator::TCALL, 5>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_51");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "51: TCALL 5"; }
};

// TCALL 6
// CALL [$FFD2]    	[........]
// Table (1-Byte)
class TCALL_61 : public AddressMode::Table<Operator::TCALL, 6>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_61");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "61: TCALL 6"; }
};

// TCALL 7
// CALL [$FFD0]    	[........]
// Table (1-Byte)
class TCALL_71 : public AddressMode::Table<Operator::TCALL, 7>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_71");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "71: TCALL 7"; }
};

// TCALL 8
// CALL [$FFCE]    	[........]
// Table (1-Byte)
class TCALL_81 : public AddressMode::Table<Operator::TCALL, 8>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_81");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "81: TCALL 8"; }
};

// TCALL 9
// CALL [$FFCC]    	[........]
// Table (1-Byte)
class TCALL_91 : public AddressMode::Table<Operator::TCALL, 9>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_91");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "91: TCALL 9"; }
};

// TCALL 10
// CALL [$FFCA]    	[........]
// Table (1-Byte)
class TCALL_A1 : public AddressMode::Table<Operator::TCALL, 10>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_A1");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "A1: TCALL 10"; }
};

// TCALL 11
// CALL [$FFC8]    	[........]
// Table (1-Byte)
class TCALL_B1 : public AddressMode::Table<Operator::TCALL, 11>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_B1");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "B1: TCALL 11"; }
};

// TCALL 12
// CALL [$FFC6]    	[........]
// Table (1-Byte)
class TCALL_C1 : public AddressMode::Table<Operator::TCALL, 12>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_C1");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "C1: TCALL 12"; }
};

// TCALL 13
// CALL [$FFC4]    	[........]
// Table (1-Byte)
class TCALL_D1 : public AddressMode::Table<Operator::TCALL, 13>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_D1");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "D1: TCALL 13"; }
};

// TCALL 14
// CALL [$FFC2]    	[........]
// Table (1-Byte)
class TCALL_E1 : public AddressMode::Table<Operator::TCALL, 14>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_E1");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "E1: TCALL 14"; }
};

// TCALL 15
// CALL [$FFC0]    	[........]
// Table (1-Byte)
class TCALL_F1 : public AddressMode::Table<Operator::TCALL, 15>
{
    using Table::Table;

    int execute() override
    {
        throw OpcodeNotYetImplementedException("TCALL_F1");
        return  8 + applyOperand();
    }

    std::string opcodeToString() const override { return "F1: TCALL 15"; }
};

// TCLR1 !a
// (a) = (a)&~A, ZN as for A-(a)    	[N.....Z.]
// Absolute (3-Byte)
class TCLR1_4E : public AddressMode::Absolute<Operator::TCLR1>
{
    using Absolute::Absolute;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "4E: TCLR1 !a"; }
};

// TSET1 !a
// (a) = (a)|A, ZN as for A-(a)    	[N.....Z.]
// Absolute (3-Byte)
class TSET1_0E : public AddressMode::Absolute<Operator::TSET1>
{
    using Absolute::Absolute;

    int execute() override
    {
        return  6 + applyOperand();
    }

    std::string opcodeToString() const override { return "0E: TSET1 !a"; }
};

// XCN A
// A = (A>>4) | (A<<4)    	[N.....Z.]
// Register (1-Byte)
class XCN_9F : public AddressMode::Register<Operator::XCN, State::A>
{
    using Register::Register;

    int execute() override
    {
        return  5 + applyOperand();
    }

    std::string opcodeToString() const override { return "9F: XCN A"; }
};

}

}
