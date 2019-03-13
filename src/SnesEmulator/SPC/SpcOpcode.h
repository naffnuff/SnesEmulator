#pragma once

#include <stdint.h>

#include "SpcState.h"
#include "../Instruction.h"
#include "SpcAddressMode.h"
#include "SpcOperator.h"

namespace SPC {

namespace Opcode {

// ADC (X), (Y)
// (X) = (X)+(Y)+C
// X Indirect Y Indirect (1-Byte)
class ADC_99 : public AddressMode::XIndirectYIndirect<Operator::ADC>
{
public:
    ADC_99(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_99 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "99: ADC (X), (Y)"; }

    State& state;
};

// ADC A, #i
// A = A+i+C
// Accumulator Immediate (2-Byte)
class ADC_88 : public AddressMode::AccumulatorImmediate<Operator::ADC>
{
public:
    ADC_88(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_88 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "88: ADC A, #i"; }

    State& state;
};

// ADC A, (X)
// A = A+(X)+C
// Accumulator X Indirect (1-Byte)
class ADC_86 : public AddressMode::AccumulatorXIndirect<Operator::ADC>
{
public:
    ADC_86(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_86 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "86: ADC A, (X)"; }

    State& state;
};

// ADC A, [d]+Y
// A = A+([d]+Y)+C
// Accumulator Direct Indirect Indexed, Y (2-Byte)
class ADC_97 : public AddressMode::AccumulatorDirectIndirectIndexedY<Operator::ADC>
{
public:
    ADC_97(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_97 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "97: ADC A, [d]+Y"; }

    State& state;
};

// ADC A, [d+X]
// A = A+([d+X])+C
// Accumulator Direct Indexed, X Indirect (2-Byte)
class ADC_87 : public AddressMode::AccumulatorDirectIndexedXIndirect<Operator::ADC>
{
public:
    ADC_87(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_87 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "87: ADC A, [d+X]"; }

    State& state;
};

// ADC A, d
// A = A+(d)+C
// Accumulator Direct (2-Byte)
class ADC_84 : public AddressMode::AccumulatorDirect<Operator::ADC>
{
public:
    ADC_84(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_84 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "84: ADC A, d"; }

    State& state;
};

// ADC A, d+X
// A = A+(d+X)+C
// Accumulator Direct Indexed, X (2-Byte)
class ADC_94 : public AddressMode::AccumulatorDirectIndexedX<Operator::ADC>
{
public:
    ADC_94(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_94 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "94: ADC A, d+X"; }

    State& state;
};

// ADC A, !a
// A = A+(a)+C
// Accumulator Absolute (3-Byte)
class ADC_85 : public AddressMode::AccumulatorAbsolute<Operator::ADC>
{
public:
    ADC_85(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_85 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "85: ADC A, !a"; }

    State& state;
};

// ADC A, !a+X
// A = A+(a+X)+C
// Accumulator Absolute Indexed, X (3-Byte)
class ADC_95 : public AddressMode::AccumulatorAbsoluteIndexedX<Operator::ADC>
{
public:
    ADC_95(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_95 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "95: ADC A, !a+X"; }

    State& state;
};

// ADC A, !a+Y
// A = A+(a+Y)+C
// Accumulator Absolute Indexed, Y (3-Byte)
class ADC_96 : public AddressMode::AccumulatorAbsoluteIndexedY<Operator::ADC>
{
public:
    ADC_96(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_96 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "96: ADC A, !a+Y"; }

    State& state;
};

// ADC dd, ds
// (dd) = (dd)+(d)+C
// Direct Direct (3-Byte)
class ADC_89 : public AddressMode::DirectDirect<Operator::ADC>
{
public:
    ADC_89(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_89 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "89: ADC dd, ds"; }

    State& state;
};

// ADC d, #i
// (d) = (d)+i+C
// Direct Immediate (3-Byte)
class ADC_98 : public AddressMode::DirectImmediate<Operator::ADC>
{
public:
    ADC_98(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADC_98 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "98: ADC d, #i"; }

    State& state;
};

// ADDW YA, d
// YA  = YA + (d), H on high byte
// Y Accumulator Direct (2-Byte)
class ADDW_7A : public AddressMode::YAccumulatorDirect<Operator::ADDW>
{
public:
    ADDW_7A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ADDW_7A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7A: ADDW YA, d"; }

    State& state;
};

// AND (X), (Y)
// (X) = (X) & (Y)
// X Indirect Y Indirect (1-Byte)
class AND_39 : public AddressMode::XIndirectYIndirect<Operator::AND>
{
public:
    AND_39(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_39 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "39: AND (X), (Y)"; }

    State& state;
};

// AND A, #i
// A = A & i
// Accumulator Immediate (2-Byte)
class AND_28 : public AddressMode::AccumulatorImmediate<Operator::AND>
{
public:
    AND_28(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_28 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "28: AND A, #i"; }

    State& state;
};

// AND A, (X)
// A = A & (X)
// Accumulator X Indirect (1-Byte)
class AND_26 : public AddressMode::AccumulatorXIndirect<Operator::AND>
{
public:
    AND_26(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_26 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "26: AND A, (X)"; }

    State& state;
};

// AND A, [d]+Y
// A = A & ([d]+Y)
// Accumulator Direct Indirect Indexed, Y (2-Byte)
class AND_37 : public AddressMode::AccumulatorDirectIndirectIndexedY<Operator::AND>
{
public:
    AND_37(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_37 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "37: AND A, [d]+Y"; }

    State& state;
};

// AND A, [d+X]
// A = A & ([d+X])
// Accumulator Direct Indexed, X Indirect (2-Byte)
class AND_27 : public AddressMode::AccumulatorDirectIndexedXIndirect<Operator::AND>
{
public:
    AND_27(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_27 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "27: AND A, [d+X]"; }

    State& state;
};

// AND A, d
// A = A & (d)
// Accumulator Direct (2-Byte)
class AND_24 : public AddressMode::AccumulatorDirect<Operator::AND>
{
public:
    AND_24(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_24 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "24: AND A, d"; }

    State& state;
};

// AND A, d+X
// A = A & (d+X)
// Accumulator Direct Indexed, X (2-Byte)
class AND_34 : public AddressMode::AccumulatorDirectIndexedX<Operator::AND>
{
public:
    AND_34(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_34 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "34: AND A, d+X"; }

    State& state;
};

// AND A, !a
// A = A & (a)
// Accumulator Absolute (3-Byte)
class AND_25 : public AddressMode::AccumulatorAbsolute<Operator::AND>
{
public:
    AND_25(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_25 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "25: AND A, !a"; }

    State& state;
};

// AND A, !a+X
// A = A & (a+X)
// Accumulator Absolute Indexed, X (3-Byte)
class AND_35 : public AddressMode::AccumulatorAbsoluteIndexedX<Operator::AND>
{
public:
    AND_35(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_35 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "35: AND A, !a+X"; }

    State& state;
};

// AND A, !a+Y
// A = A & (a+Y)
// Accumulator Absolute Indexed, Y (3-Byte)
class AND_36 : public AddressMode::AccumulatorAbsoluteIndexedY<Operator::AND>
{
public:
    AND_36(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_36 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "36: AND A, !a+Y"; }

    State& state;
};

// AND dd, ds
// (dd) = (dd) & (ds)
// Direct Direct (3-Byte)
class AND_29 : public AddressMode::DirectDirect<Operator::AND>
{
public:
    AND_29(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_29 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "29: AND dd, ds"; }

    State& state;
};

// AND d, #i
// (d) = (d) & i
// Direct Immediate (3-Byte)
class AND_38 : public AddressMode::DirectImmediate<Operator::AND>
{
public:
    AND_38(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND_38 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "38: AND d, #i"; }

    State& state;
};

// AND1 C, /m.b
// C = C & ~(m.b)
// Carry Not Memory Bit (3-Byte)
class AND1_6A : public AddressMode::CarryNotMemoryBit<Operator::AND1>
{
public:
    AND1_6A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND1_6A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6A: AND1 C, /m.b"; }

    State& state;
};

// AND1 C, m.b
// C = C & (m.b)
// Carry Memory Bit (3-Byte)
class AND1_4A : public AddressMode::CarryMemoryBit<Operator::AND1>
{
public:
    AND1_4A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("AND1_4A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4A: AND1 C, m.b"; }

    State& state;
};

// ASL A
// Left shift A: high->C, 0->low
// Accumulator (1-Byte)
class ASL_1C : public AddressMode::Accumulator<Operator::ASL>
{
public:
    ASL_1C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ASL_1C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1C: ASL A"; }

    State& state;
};

// ASL d
// Left shift (d) as above
// Direct (2-Byte)
class ASL_0B : public AddressMode::Direct<Operator::ASL>
{
public:
    ASL_0B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ASL_0B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0B: ASL d"; }

    State& state;
};

// ASL d+X
// Left shift (d+X) as above
// Direct Indexed, X (2-Byte)
class ASL_1B : public AddressMode::DirectIndexedX<Operator::ASL>
{
public:
    ASL_1B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ASL_1B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1B: ASL d+X"; }

    State& state;
};

// ASL !a
// Left shift (a) as above
// Absolute (3-Byte)
class ASL_0C : public AddressMode::Absolute<Operator::ASL>
{
public:
    ASL_0C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ASL_0C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0C: ASL !a"; }

    State& state;
};

// BBC d.0, r
// PC+=r  if d.0 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_13 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 0>
{
public:
    BBC_13(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_13 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "13: BBC d.0, r"; }

    State& state;
};

// BBC d.1, r
// PC+=r  if d.1 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_33 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 1>
{
public:
    BBC_33(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_33 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "33: BBC d.1, r"; }

    State& state;
};

// BBC d.2, r
// PC+=r  if d.2 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_53 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 2>
{
public:
    BBC_53(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_53 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "53: BBC d.2, r"; }

    State& state;
};

// BBC d.3, r
// PC+=r  if d.3 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_73 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 3>
{
public:
    BBC_73(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_73 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "73: BBC d.3, r"; }

    State& state;
};

// BBC d.4, r
// PC+=r  if d.4 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_93 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 4>
{
public:
    BBC_93(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_93 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "93: BBC d.4, r"; }

    State& state;
};

// BBC d.5, r
// PC+=r  if d.5 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_B3 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 5>
{
public:
    BBC_B3(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_B3 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B3: BBC d.5, r"; }

    State& state;
};

// BBC d.6, r
// PC+=r  if d.6 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_D3 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 6>
{
public:
    BBC_D3(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_D3 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D3: BBC d.6, r"; }

    State& state;
};

// BBC d.7, r
// PC+=r  if d.7 == 0
// Direct Bit Program Counter Relative (3-Byte)
class BBC_F3 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBC, 1 << 7>
{
public:
    BBC_F3(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBC_F3 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F3: BBC d.7, r"; }

    State& state;
};

// BBS d.0, r
// PC+=r  if d.0 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_03 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 0>
{
public:
    BBS_03(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_03 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "03: BBS d.0, r"; }

    State& state;
};

// BBS d.1, r
// PC+=r  if d.1 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_23 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 1>
{
public:
    BBS_23(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_23 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "23: BBS d.1, r"; }

    State& state;
};

// BBS d.2, r
// PC+=r  if d.2 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_43 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 2>
{
public:
    BBS_43(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_43 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "43: BBS d.2, r"; }

    State& state;
};

// BBS d.3, r
// PC+=r  if d.3 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_63 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 3>
{
public:
    BBS_63(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_63 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "63: BBS d.3, r"; }

    State& state;
};

// BBS d.4, r
// PC+=r  if d.4 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_83 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 4>
{
public:
    BBS_83(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_83 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "83: BBS d.4, r"; }

    State& state;
};

// BBS d.5, r
// PC+=r  if d.5 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_A3 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 5>
{
public:
    BBS_A3(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_A3 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A3: BBS d.5, r"; }

    State& state;
};

// BBS d.6, r
// PC+=r  if d.6 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_C3 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 6>
{
public:
    BBS_C3(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_C3 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C3: BBS d.6, r"; }

    State& state;
};

// BBS d.7, r
// PC+=r  if d.7 == 1
// Direct Bit Program Counter Relative (3-Byte)
class BBS_E3 : public AddressMode::DirectBitProgramCounterRelative<Operator::BBS, 1 << 7>
{
public:
    BBS_E3(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BBS_E3 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E3: BBS d.7, r"; }

    State& state;
};

// BCC r
// PC+=r  if C == 0
// Program Counter Relative (2-Byte)
class BCC_90 : public AddressMode::ProgramCounterRelative<Operator::BCC>
{
public:
    BCC_90(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BCC_90 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "90: BCC r"; }

    State& state;
};

// BCS r
// PC+=r  if C == 1
// Program Counter Relative (2-Byte)
class BCS_B0 : public AddressMode::ProgramCounterRelative<Operator::BCS>
{
public:
    BCS_B0(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BCS_B0 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B0: BCS r"; }

    State& state;
};

// BEQ r
// PC+=r  if Z == 1
// Program Counter Relative (2-Byte)
class BEQ_F0 : public AddressMode::ProgramCounterRelative<Operator::BEQ>
{
public:
    BEQ_F0(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BEQ_F0 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F0: BEQ r"; }

    State& state;
};

// BMI r
// PC+=r  if N == 1
// Program Counter Relative (2-Byte)
class BMI_30 : public AddressMode::ProgramCounterRelative<Operator::BMI>
{
public:
    BMI_30(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BMI_30 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "30: BMI r"; }

    State& state;
};

// BNE r
// PC+=r  if Z == 0
// Program Counter Relative (2-Byte)
class BNE_D0 : public AddressMode::ProgramCounterRelative<Operator::BNE>
{
public:
    BNE_D0(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BNE_D0 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D0: BNE r"; }

    State& state;
};

// BPL r
// PC+=r  if N == 0
// Program Counter Relative (2-Byte)
class BPL_10 : public AddressMode::ProgramCounterRelative<Operator::BPL>
{
public:
    BPL_10(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BPL_10 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "10: BPL r"; }

    State& state;
};

// BVC r
// PC+=r  if V == 0
// Program Counter Relative (2-Byte)
class BVC_50 : public AddressMode::ProgramCounterRelative<Operator::BVC>
{
public:
    BVC_50(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BVC_50 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "50: BVC r"; }

    State& state;
};

// BVS r
// PC+=r  if V == 1
// Program Counter Relative (2-Byte)
class BVS_70 : public AddressMode::ProgramCounterRelative<Operator::BVS>
{
public:
    BVS_70(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BVS_70 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "70: BVS r"; }

    State& state;
};

// BRA r
// PC+=r
// Program Counter Relative (2-Byte)
class BRA_2F : public AddressMode::ProgramCounterRelative<Operator::BRA>
{
public:
    BRA_2F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BRA_2F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2F: BRA r"; }

    State& state;
};

// BRK 
// Push PC and Flags, PC = [$FFDE]
// Implied (1-Byte)
class BRK_0F : public AddressMode::Implied<Operator::BRK>
{
public:
    BRK_0F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("BRK_0F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0F: BRK "; }

    State& state;
};

// CALL !a
// (SP--)=PCh, (SP--)=PCl, PC=a
// Absolute (3-Byte)
class CALL_3F : public AddressMode::Absolute<Operator::CALL>
{
public:
    CALL_3F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CALL_3F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3F: CALL !a"; }

    State& state;
};

// CBNE d+X, r
// CMP A, (d+X) then BNE
// Direct Indexed, X Program Counter Relative (3-Byte)
class CBNE_DE : public AddressMode::DirectIndexedXProgramCounterRelative<Operator::CBNE>
{
public:
    CBNE_DE(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CBNE_DE is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DE: CBNE d+X, r"; }

    State& state;
};

// CBNE d, r
// CMP A, (d) then BNE
// Direct Program Counter Relative (3-Byte)
class CBNE_2E : public AddressMode::DirectProgramCounterRelative<Operator::CBNE>
{
public:
    CBNE_2E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CBNE_2E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2E: CBNE d, r"; }

    State& state;
};

// CLR1 d.0
// d.0 = 0
// Direct Bit (2-Byte)
class CLR1_12 : public AddressMode::DirectBit<Operator::CLR1, 1 << 0>
{
public:
    CLR1_12(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_12 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "12: CLR1 d.0"; }

    State& state;
};

// CLR1 d.1
// d.1 = 0
// Direct Bit (2-Byte)
class CLR1_32 : public AddressMode::DirectBit<Operator::CLR1, 1 << 1>
{
public:
    CLR1_32(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_32 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "32: CLR1 d.1"; }

    State& state;
};

// CLR1 d.2
// d.2 = 0
// Direct Bit (2-Byte)
class CLR1_52 : public AddressMode::DirectBit<Operator::CLR1, 1 << 2>
{
public:
    CLR1_52(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_52 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "52: CLR1 d.2"; }

    State& state;
};

// CLR1 d.3
// d.3 = 0
// Direct Bit (2-Byte)
class CLR1_72 : public AddressMode::DirectBit<Operator::CLR1, 1 << 3>
{
public:
    CLR1_72(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_72 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "72: CLR1 d.3"; }

    State& state;
};

// CLR1 d.4
// d.4 = 0
// Direct Bit (2-Byte)
class CLR1_92 : public AddressMode::DirectBit<Operator::CLR1, 1 << 4>
{
public:
    CLR1_92(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_92 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "92: CLR1 d.4"; }

    State& state;
};

// CLR1 d.5
// d.5 = 0
// Direct Bit (2-Byte)
class CLR1_B2 : public AddressMode::DirectBit<Operator::CLR1, 1 << 5>
{
public:
    CLR1_B2(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_B2 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B2: CLR1 d.5"; }

    State& state;
};

// CLR1 d.6
// d.6 = 0
// Direct Bit (2-Byte)
class CLR1_D2 : public AddressMode::DirectBit<Operator::CLR1, 1 << 6>
{
public:
    CLR1_D2(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_D2 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D2: CLR1 d.6"; }

    State& state;
};

// CLR1 d.7
// d.7 = 0
// Direct Bit (2-Byte)
class CLR1_F2 : public AddressMode::DirectBit<Operator::CLR1, 1 << 7>
{
public:
    CLR1_F2(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLR1_F2 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F2: CLR1 d.7"; }

    State& state;
};

// CLRC 
// C = 0
// Implied (1-Byte)
class CLRC_60 : public AddressMode::Implied<Operator::CLRC>
{
public:
    CLRC_60(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLRC_60 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "60: CLRC "; }

    State& state;
};

// CLRP 
// P = 0
// Implied (1-Byte)
class CLRP_20 : public AddressMode::Implied<Operator::CLRP>
{
public:
    CLRP_20(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLRP_20 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "20: CLRP "; }

    State& state;
};

// CLRV 
// V = 0, H = 0
// Implied (1-Byte)
class CLRV_E0 : public AddressMode::Implied<Operator::CLRV>
{
public:
    CLRV_E0(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CLRV_E0 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E0: CLRV "; }

    State& state;
};

// CMP (X), (Y)
// (X) - (Y)
// X Indirect Y Indirect (1-Byte)
class CMP_79 : public AddressMode::XIndirectYIndirect<Operator::CMP>
{
public:
    CMP_79(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_79 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "79: CMP (X), (Y)"; }

    State& state;
};

// CMP A, #i
// A - i
// Accumulator Immediate (2-Byte)
class CMP_68 : public AddressMode::AccumulatorImmediate<Operator::CMP>
{
public:
    CMP_68(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_68 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "68: CMP A, #i"; }

    State& state;
};

// CMP A, (X)
// A - (X)
// Accumulator X Indirect (1-Byte)
class CMP_66 : public AddressMode::AccumulatorXIndirect<Operator::CMP>
{
public:
    CMP_66(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_66 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "66: CMP A, (X)"; }

    State& state;
};

// CMP A, [d]+Y
// A - ([d]+Y)
// Accumulator Direct Indirect Indexed, Y (2-Byte)
class CMP_77 : public AddressMode::AccumulatorDirectIndirectIndexedY<Operator::CMP>
{
public:
    CMP_77(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_77 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "77: CMP A, [d]+Y"; }

    State& state;
};

// CMP A, [d+X]
// A - ([d+X])
// Accumulator Direct Indexed, X Indirect (2-Byte)
class CMP_67 : public AddressMode::AccumulatorDirectIndexedXIndirect<Operator::CMP>
{
public:
    CMP_67(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_67 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "67: CMP A, [d+X]"; }

    State& state;
};

// CMP A, d
// A - (d)
// Accumulator Direct (2-Byte)
class CMP_64 : public AddressMode::AccumulatorDirect<Operator::CMP>
{
public:
    CMP_64(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_64 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "64: CMP A, d"; }

    State& state;
};

// CMP A, d+X
// A - (d+X)
// Accumulator Direct Indexed, X (2-Byte)
class CMP_74 : public AddressMode::AccumulatorDirectIndexedX<Operator::CMP>
{
public:
    CMP_74(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_74 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "74: CMP A, d+X"; }

    State& state;
};

// CMP A, !a
// A - (a)
// Accumulator Absolute (3-Byte)
class CMP_65 : public AddressMode::AccumulatorAbsolute<Operator::CMP>
{
public:
    CMP_65(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_65 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "65: CMP A, !a"; }

    State& state;
};

// CMP A, !a+X
// A - (a+X)
// Accumulator Absolute Indexed, X (3-Byte)
class CMP_75 : public AddressMode::AccumulatorAbsoluteIndexedX<Operator::CMP>
{
public:
    CMP_75(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_75 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "75: CMP A, !a+X"; }

    State& state;
};

// CMP A, !a+Y
// A - (a+Y)
// Accumulator Absolute Indexed, Y (3-Byte)
class CMP_76 : public AddressMode::AccumulatorAbsoluteIndexedY<Operator::CMP>
{
public:
    CMP_76(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_76 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "76: CMP A, !a+Y"; }

    State& state;
};

// CMP X, #i
// X - i
// Index X Immediate (2-Byte)
class CMP_C8 : public AddressMode::IndexXImmediate<Operator::CMP>
{
public:
    CMP_C8(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_C8 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C8: CMP X, #i"; }

    State& state;
};

// CMP X, d
// X - (d)
// Index X Direct (2-Byte)
class CMP_3E : public AddressMode::IndexXDirect<Operator::CMP>
{
public:
    CMP_3E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_3E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3E: CMP X, d"; }

    State& state;
};

// CMP X, !a
// X - (a)
// Index X Absolute (3-Byte)
class CMP_1E : public AddressMode::IndexXAbsolute<Operator::CMP>
{
public:
    CMP_1E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_1E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1E: CMP X, !a"; }

    State& state;
};

// CMP Y, #i
// Y - i
// Index Y Immediate (2-Byte)
class CMP_AD : public AddressMode::IndexYImmediate<Operator::CMP>
{
public:
    CMP_AD(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_AD is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AD: CMP Y, #i"; }

    State& state;
};

// CMP Y, d
// Y - (d)
// Index Y Direct (2-Byte)
class CMP_7E : public AddressMode::IndexYDirect<Operator::CMP>
{
public:
    CMP_7E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_7E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7E: CMP Y, d"; }

    State& state;
};

// CMP Y, !a
// Y - (a)
// Index Y Absolute (3-Byte)
class CMP_5E : public AddressMode::IndexYAbsolute<Operator::CMP>
{
public:
    CMP_5E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_5E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5E: CMP Y, !a"; }

    State& state;
};

// CMP dd, ds
// (dd) - (ds)
// Direct Direct (3-Byte)
class CMP_69 : public AddressMode::DirectDirect<Operator::CMP>
{
public:
    CMP_69(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_69 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "69: CMP dd, ds"; }

    State& state;
};

// CMP d, #i
// (d) - i
// Direct Immediate (3-Byte)
class CMP_78 : public AddressMode::DirectImmediate<Operator::CMP>
{
public:
    CMP_78(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMP_78 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "78: CMP d, #i"; }

    State& state;
};

// CMPW YA, d
// YA - (d)
// Y Accumulator Direct (2-Byte)
class CMPW_5A : public AddressMode::YAccumulatorDirect<Operator::CMPW>
{
public:
    CMPW_5A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("CMPW_5A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5A: CMPW YA, d"; }

    State& state;
};

// DAA A
// decimal adjust for addition
// Accumulator (1-Byte)
class DAA_DF : public AddressMode::Accumulator<Operator::DAA>
{
public:
    DAA_DF(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DAA_DF is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DF: DAA A"; }

    State& state;
};

// DAS A
// decimal adjust for subtraction
// Accumulator (1-Byte)
class DAS_BE : public AddressMode::Accumulator<Operator::DAS>
{
public:
    DAS_BE(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DAS_BE is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BE: DAS A"; }

    State& state;
};

// DBNZ Y, r
// Y-- then JNZ
// Index Y Program Counter Relative (2-Byte)
class DBNZ_FE : public AddressMode::IndexYProgramCounterRelative<Operator::DBNZ>
{
public:
    DBNZ_FE(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DBNZ_FE is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FE: DBNZ Y, r"; }

    State& state;
};

// DBNZ d, r
// (d)-- then JNZ
// Direct Program Counter Relative (3-Byte)
class DBNZ_6E : public AddressMode::DirectProgramCounterRelative<Operator::DBNZ>
{
public:
    DBNZ_6E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DBNZ_6E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6E: DBNZ d, r"; }

    State& state;
};

// DEC A
// A--
// Accumulator (1-Byte)
class DEC_9C : public AddressMode::Accumulator<Operator::DEC>
{
public:
    DEC_9C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DEC_9C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9C: DEC A"; }

    State& state;
};

// DEC X
// X--
// Index X (1-Byte)
class DEC_1D : public AddressMode::IndexX<Operator::DEC>
{
public:
    DEC_1D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DEC_1D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1D: DEC X"; }

    State& state;
};

// DEC Y
// Y--
// Index Y (1-Byte)
class DEC_DC : public AddressMode::IndexY<Operator::DEC>
{
public:
    DEC_DC(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DEC_DC is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DC: DEC Y"; }

    State& state;
};

// DEC d
// (d)--
// Direct (2-Byte)
class DEC_8B : public AddressMode::Direct<Operator::DEC>
{
public:
    DEC_8B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DEC_8B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8B: DEC d"; }

    State& state;
};

// DEC d+X
// (d+X)--
// Direct Indexed, X (2-Byte)
class DEC_9B : public AddressMode::DirectIndexedX<Operator::DEC>
{
public:
    DEC_9B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DEC_9B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9B: DEC d+X"; }

    State& state;
};

// DEC !a
// (a)--
// Absolute (3-Byte)
class DEC_8C : public AddressMode::Absolute<Operator::DEC>
{
public:
    DEC_8C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DEC_8C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8C: DEC !a"; }

    State& state;
};

// DECW d
// Word (d)--
// Direct (2-Byte)
class DECW_1A : public AddressMode::Direct<Operator::DECW>
{
public:
    DECW_1A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DECW_1A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1A: DECW d"; }

    State& state;
};

// DI 
// I = 0
// Implied (1-Byte)
class DI_C0 : public AddressMode::Implied<Operator::DI>
{
public:
    DI_C0(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DI_C0 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C0: DI "; }

    State& state;
};

// DIV YA, X
// A=YA/X, Y=mod(YA,X)
// Y Accumulator Index X (1-Byte)
class DIV_9E : public AddressMode::YAccumulatorIndexX<Operator::DIV>
{
public:
    DIV_9E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("DIV_9E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9E: DIV YA, X"; }

    State& state;
};

// EI 
// I = 1
// Implied (1-Byte)
class EI_A0 : public AddressMode::Implied<Operator::EI>
{
public:
    EI_A0(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EI_A0 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A0: EI "; }

    State& state;
};

// EOR (X), (Y)
// (X) = (X) EOR (Y)
// X Indirect Y Indirect (1-Byte)
class EOR_59 : public AddressMode::XIndirectYIndirect<Operator::EOR>
{
public:
    EOR_59(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_59 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "59: EOR (X), (Y)"; }

    State& state;
};

// EOR A, #i
// A = A EOR i
// Accumulator Immediate (2-Byte)
class EOR_48 : public AddressMode::AccumulatorImmediate<Operator::EOR>
{
public:
    EOR_48(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_48 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "48: EOR A, #i"; }

    State& state;
};

// EOR A, (X)
// A = A EOR (X)
// Accumulator X Indirect (1-Byte)
class EOR_46 : public AddressMode::AccumulatorXIndirect<Operator::EOR>
{
public:
    EOR_46(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_46 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "46: EOR A, (X)"; }

    State& state;
};

// EOR A, [d]+Y
// A = A EOR ([d]+Y)
// Accumulator Direct Indirect Indexed, Y (2-Byte)
class EOR_57 : public AddressMode::AccumulatorDirectIndirectIndexedY<Operator::EOR>
{
public:
    EOR_57(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_57 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "57: EOR A, [d]+Y"; }

    State& state;
};

// EOR A, [d+X]
// A = A EOR ([d+X])
// Accumulator Direct Indexed, X Indirect (2-Byte)
class EOR_47 : public AddressMode::AccumulatorDirectIndexedXIndirect<Operator::EOR>
{
public:
    EOR_47(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_47 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "47: EOR A, [d+X]"; }

    State& state;
};

// EOR A, d
// A = A EOR (d)
// Accumulator Direct (2-Byte)
class EOR_44 : public AddressMode::AccumulatorDirect<Operator::EOR>
{
public:
    EOR_44(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_44 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "44: EOR A, d"; }

    State& state;
};

// EOR A, d+X
// A = A EOR (d+X)
// Accumulator Direct Indexed, X (2-Byte)
class EOR_54 : public AddressMode::AccumulatorDirectIndexedX<Operator::EOR>
{
public:
    EOR_54(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_54 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "54: EOR A, d+X"; }

    State& state;
};

// EOR A, !a
// A = A EOR (a)
// Accumulator Absolute (3-Byte)
class EOR_45 : public AddressMode::AccumulatorAbsolute<Operator::EOR>
{
public:
    EOR_45(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_45 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "45: EOR A, !a"; }

    State& state;
};

// EOR A, !a+X
// A = A EOR (a+X)
// Accumulator Absolute Indexed, X (3-Byte)
class EOR_55 : public AddressMode::AccumulatorAbsoluteIndexedX<Operator::EOR>
{
public:
    EOR_55(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_55 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "55: EOR A, !a+X"; }

    State& state;
};

// EOR A, !a+Y
// A = A EOR (a+Y)
// Accumulator Absolute Indexed, Y (3-Byte)
class EOR_56 : public AddressMode::AccumulatorAbsoluteIndexedY<Operator::EOR>
{
public:
    EOR_56(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_56 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "56: EOR A, !a+Y"; }

    State& state;
};

// EOR dd, ds
// (dd) = (dd) EOR (ds)
// Direct Direct (3-Byte)
class EOR_49 : public AddressMode::DirectDirect<Operator::EOR>
{
public:
    EOR_49(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_49 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "49: EOR dd, ds"; }

    State& state;
};

// EOR d, #i
// (d) = (d) EOR i
// Direct Immediate (3-Byte)
class EOR_58 : public AddressMode::DirectImmediate<Operator::EOR>
{
public:
    EOR_58(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR_58 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "58: EOR d, #i"; }

    State& state;
};

// EOR1 C, m.b
// C = C EOR (m.b)
// Carry Memory Bit (3-Byte)
class EOR1_8A : public AddressMode::CarryMemoryBit<Operator::EOR1>
{
public:
    EOR1_8A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("EOR1_8A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8A: EOR1 C, m.b"; }

    State& state;
};

// INC A
// A++
// Accumulator (1-Byte)
class INC_BC : public AddressMode::Accumulator<Operator::INC>
{
public:
    INC_BC(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("INC_BC is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BC: INC A"; }

    State& state;
};

// INC X
// X++
// Index X (1-Byte)
class INC_3D : public AddressMode::IndexX<Operator::INC>
{
public:
    INC_3D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("INC_3D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3D: INC X"; }

    State& state;
};

// INC Y
// Y++
// Index Y (1-Byte)
class INC_FC : public AddressMode::IndexY<Operator::INC>
{
public:
    INC_FC(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("INC_FC is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FC: INC Y"; }

    State& state;
};

// INC d
// (d)++
// Direct (2-Byte)
class INC_AB : public AddressMode::Direct<Operator::INC>
{
public:
    INC_AB(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("INC_AB is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AB: INC d"; }

    State& state;
};

// INC d+X
// (d+X)++
// Direct Indexed, X (2-Byte)
class INC_BB : public AddressMode::DirectIndexedX<Operator::INC>
{
public:
    INC_BB(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("INC_BB is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BB: INC d+X"; }

    State& state;
};

// INC !a
// (a)++
// Absolute (3-Byte)
class INC_AC : public AddressMode::Absolute<Operator::INC>
{
public:
    INC_AC(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("INC_AC is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AC: INC !a"; }

    State& state;
};

// INCW d
// Word (d)++
// Direct (2-Byte)
class INCW_3A : public AddressMode::Direct<Operator::INCW>
{
public:
    INCW_3A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("INCW_3A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3A: INCW d"; }

    State& state;
};

// JMP [!a+X]
// PC = [a+X]
// Absolute Indexed, X Indirect (3-Byte)
class JMP_1F : public AddressMode::AbsoluteIndexedXIndirect<Operator::JMP>
{
public:
    JMP_1F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("JMP_1F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "1F: JMP [!a+X]"; }

    State& state;
};

// JMP !a
// PC = a
// Absolute (3-Byte)
class JMP_5F : public AddressMode::Absolute<Operator::JMP>
{
public:
    JMP_5F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("JMP_5F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5F: JMP !a"; }

    State& state;
};

// LSR A
// Right shift A: 0->high, low->C
// Accumulator (1-Byte)
class LSR_5C : public AddressMode::Accumulator<Operator::LSR>
{
public:
    LSR_5C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("LSR_5C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5C: LSR A"; }

    State& state;
};

// LSR d
// Right shift (d) as above
// Direct (2-Byte)
class LSR_4B : public AddressMode::Direct<Operator::LSR>
{
public:
    LSR_4B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("LSR_4B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4B: LSR d"; }

    State& state;
};

// LSR d+X
// Right shift (d+X) as above
// Direct Indexed, X (2-Byte)
class LSR_5B : public AddressMode::DirectIndexedX<Operator::LSR>
{
public:
    LSR_5B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("LSR_5B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5B: LSR d+X"; }

    State& state;
};

// LSR !a
// Right shift (a) as above
// Absolute (3-Byte)
class LSR_4C : public AddressMode::Absolute<Operator::LSR>
{
public:
    LSR_4C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("LSR_4C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4C: LSR !a"; }

    State& state;
};

// MOV (X)+, A
// (X++) = A      (no read)
// X Indirect Plus Accumulator (1-Byte)
class MOV_AF : public AddressMode::XIndirectPlusAccumulator<Operator::MOV>
{
public:
    MOV_AF(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_AF is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AF: MOV (X)+, A"; }

    State& state;
};

// MOV (X), A
// (X) = A        (read)
// X Indirect Accumulator (1-Byte)
class MOV_C6 : public AddressMode::XIndirectAccumulator<Operator::MOV>
{
public:
    MOV_C6(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_C6 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C6: MOV (X), A"; }

    State& state;
};

// MOV [d]+Y, A
// ([d]+Y) = A    (read)
// Direct Indirect Indexed, Y Accumulator (2-Byte)
class MOV_D7 : public AddressMode::DirectIndirectIndexedYAccumulator<Operator::MOV>
{
public:
    MOV_D7(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_D7 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D7: MOV [d]+Y, A"; }

    State& state;
};

// MOV [d+X], A
// ([d+X]) = A    (read)
// Direct Indexed, X Indirect Accumulator (2-Byte)
class MOV_C7 : public AddressMode::DirectIndexedXIndirectAccumulator<Operator::MOV>
{
public:
    MOV_C7(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_C7 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C7: MOV [d+X], A"; }

    State& state;
};

// MOV A, #i
// A = i
// Accumulator Immediate (2-Byte)
class MOV_E8 : public AddressMode::AccumulatorImmediate<Operator::MOV>
{
public:
    MOV_E8(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_E8 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E8: MOV A, #i"; }

    State& state;
};

// MOV A, (X)
// A = (X)
// Accumulator X Indirect (1-Byte)
class MOV_E6 : public AddressMode::AccumulatorXIndirect<Operator::MOV>
{
public:
    MOV_E6(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_E6 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E6: MOV A, (X)"; }

    State& state;
};

// MOV A, (X)+
// A = (X++)
// Accumulator X Indirect Plus (1-Byte)
class MOV_BF : public AddressMode::AccumulatorXIndirectPlus<Operator::MOV>
{
public:
    MOV_BF(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_BF is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BF: MOV A, (X)+"; }

    State& state;
};

// MOV A, [d]+Y
// A = ([d]+Y)
// Accumulator Direct Indirect Indexed, Y (2-Byte)
class MOV_F7 : public AddressMode::AccumulatorDirectIndirectIndexedY<Operator::MOV>
{
public:
    MOV_F7(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_F7 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F7: MOV A, [d]+Y"; }

    State& state;
};

// MOV A, [d+X]
// A = ([d+X])
// Accumulator Direct Indexed, X Indirect (2-Byte)
class MOV_E7 : public AddressMode::AccumulatorDirectIndexedXIndirect<Operator::MOV>
{
public:
    MOV_E7(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_E7 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E7: MOV A, [d+X]"; }

    State& state;
};

// MOV A, X
// A = X
// Accumulator Index X (1-Byte)
class MOV_7D : public AddressMode::AccumulatorIndexX<Operator::MOV>
{
public:
    MOV_7D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_7D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7D: MOV A, X"; }

    State& state;
};

// MOV A, Y
// A = Y
// Accumulator Index Y (1-Byte)
class MOV_DD : public AddressMode::AccumulatorIndexY<Operator::MOV>
{
public:
    MOV_DD(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_DD is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DD: MOV A, Y"; }

    State& state;
};

// MOV A, d
// A = (d)
// Accumulator Direct (2-Byte)
class MOV_E4 : public AddressMode::AccumulatorDirect<Operator::MOV>
{
public:
    MOV_E4(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_E4 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E4: MOV A, d"; }

    State& state;
};

// MOV A, d+X
// A = (d+X)
// Accumulator Direct Indexed, X (2-Byte)
class MOV_F4 : public AddressMode::AccumulatorDirectIndexedX<Operator::MOV>
{
public:
    MOV_F4(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_F4 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F4: MOV A, d+X"; }

    State& state;
};

// MOV A, !a
// A = (a)
// Accumulator Absolute (3-Byte)
class MOV_E5 : public AddressMode::AccumulatorAbsolute<Operator::MOV>
{
public:
    MOV_E5(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_E5 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E5: MOV A, !a"; }

    State& state;
};

// MOV A, !a+X
// A = (a+X)
// Accumulator Absolute Indexed, X (3-Byte)
class MOV_F5 : public AddressMode::AccumulatorAbsoluteIndexedX<Operator::MOV>
{
public:
    MOV_F5(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_F5 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F5: MOV A, !a+X"; }

    State& state;
};

// MOV A, !a+Y
// A = (a+Y)
// Accumulator Absolute Indexed, Y (3-Byte)
class MOV_F6 : public AddressMode::AccumulatorAbsoluteIndexedY<Operator::MOV>
{
public:
    MOV_F6(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_F6 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F6: MOV A, !a+Y"; }

    State& state;
};

// MOV SP, X
// SP = X
// Stack Pointer Index X (1-Byte)
class MOV_BD : public AddressMode::StackPointerIndexX<Operator::MOV>
{
public:
    MOV_BD(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_BD is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BD: MOV SP, X"; }

    State& state;
};

// MOV X, #i
// X = i
// Index X Immediate (2-Byte)
class MOV_CD : public AddressMode::IndexXImmediate<Operator::MOV>
{
public:
    MOV_CD(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_CD is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CD: MOV X, #i"; }

    State& state;
};

// MOV X, A
// X = A
// Index X Accumulator (1-Byte)
class MOV_5D : public AddressMode::IndexXAccumulator<Operator::MOV>
{
public:
    MOV_5D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_5D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "5D: MOV X, A"; }

    State& state;
};

// MOV X, SP
// X = SP
// Index X Stack Pointer (1-Byte)
class MOV_9D : public AddressMode::IndexXStackPointer<Operator::MOV>
{
public:
    MOV_9D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_9D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9D: MOV X, SP"; }

    State& state;
};

// MOV X, d
// X = (d)
// Index X Direct (2-Byte)
class MOV_F8 : public AddressMode::IndexXDirect<Operator::MOV>
{
public:
    MOV_F8(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_F8 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F8: MOV X, d"; }

    State& state;
};

// MOV X, d+Y
// X = (d+Y)
// Index X Direct Indexed, Y (2-Byte)
class MOV_F9 : public AddressMode::IndexXDirectIndexedY<Operator::MOV>
{
public:
    MOV_F9(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_F9 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F9: MOV X, d+Y"; }

    State& state;
};

// MOV X, !a
// X = (a)
// Index X Absolute (3-Byte)
class MOV_E9 : public AddressMode::IndexXAbsolute<Operator::MOV>
{
public:
    MOV_E9(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_E9 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E9: MOV X, !a"; }

    State& state;
};

// MOV Y, #i
// Y = i
// Index Y Immediate (2-Byte)
class MOV_8D : public AddressMode::IndexYImmediate<Operator::MOV>
{
public:
    MOV_8D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_8D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8D: MOV Y, #i"; }

    State& state;
};

// MOV Y, A
// Y = A
// Index Y Accumulator (1-Byte)
class MOV_FD : public AddressMode::IndexYAccumulator<Operator::MOV>
{
public:
    MOV_FD(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_FD is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FD: MOV Y, A"; }

    State& state;
};

// MOV Y, d
// Y = (d)
// Index Y Direct (2-Byte)
class MOV_EB : public AddressMode::IndexYDirect<Operator::MOV>
{
public:
    MOV_EB(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_EB is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EB: MOV Y, d"; }

    State& state;
};

// MOV Y, d+X
// Y = (d+X)
// Index Y Direct Indexed, X (2-Byte)
class MOV_FB : public AddressMode::IndexYDirectIndexedX<Operator::MOV>
{
public:
    MOV_FB(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_FB is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FB: MOV Y, d+X"; }

    State& state;
};

// MOV Y, !a
// Y = (a)
// Index Y Absolute (3-Byte)
class MOV_EC : public AddressMode::IndexYAbsolute<Operator::MOV>
{
public:
    MOV_EC(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_EC is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EC: MOV Y, !a"; }

    State& state;
};

// MOV dd, ds
// (dd) = (ds)    (no read)
// Direct Direct (3-Byte)
class MOV_FA : public AddressMode::DirectDirect<Operator::MOV>
{
public:
    MOV_FA(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_FA is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FA: MOV dd, ds"; }

    State& state;
};

// MOV d+X, A
// (d+X) = A      (read)
// Direct Indexed, X Accumulator (2-Byte)
class MOV_D4 : public AddressMode::DirectIndexedXAccumulator<Operator::MOV>
{
public:
    MOV_D4(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_D4 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D4: MOV d+X, A"; }

    State& state;
};

// MOV d+X, Y
// (d+X) = Y      (read)
// Direct Indexed, X Index Y (2-Byte)
class MOV_DB : public AddressMode::DirectIndexedXIndexY<Operator::MOV>
{
public:
    MOV_DB(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_DB is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DB: MOV d+X, Y"; }

    State& state;
};

// MOV d+Y, X
// (d+Y) = X      (read)
// Direct Indexed, Y Index X (2-Byte)
class MOV_D9 : public AddressMode::DirectIndexedYIndexX<Operator::MOV>
{
public:
    MOV_D9(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_D9 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D9: MOV d+Y, X"; }

    State& state;
};

// MOV d, #i
// (d) = i        (read)
// Direct Immediate (3-Byte)
class MOV_8F : public AddressMode::DirectImmediate<Operator::MOV>
{
public:
    MOV_8F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_8F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8F: MOV d, #i"; }

    State& state;
};

// MOV d, A
// (d) = A        (read)
// Direct Accumulator (2-Byte)
class MOV_C4 : public AddressMode::DirectAccumulator<Operator::MOV>
{
public:
    MOV_C4(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_C4 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C4: MOV d, A"; }

    State& state;
};

// MOV d, X
// (d) = X        (read)
// Direct Index X (2-Byte)
class MOV_D8 : public AddressMode::DirectIndexX<Operator::MOV>
{
public:
    MOV_D8(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_D8 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D8: MOV d, X"; }

    State& state;
};

// MOV d, Y
// (d) = Y        (read)
// Direct Index Y (2-Byte)
class MOV_CB : public AddressMode::DirectIndexY<Operator::MOV>
{
public:
    MOV_CB(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_CB is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CB: MOV d, Y"; }

    State& state;
};

// MOV !a+X, A
// (a+X) = A      (read)
// Absolute Indexed, X Accumulator (3-Byte)
class MOV_D5 : public AddressMode::AbsoluteIndexedXAccumulator<Operator::MOV>
{
public:
    MOV_D5(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_D5 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D5: MOV !a+X, A"; }

    State& state;
};

// MOV !a+Y, A
// (a+Y) = A      (read)
// Absolute Indexed, Y Accumulator (3-Byte)
class MOV_D6 : public AddressMode::AbsoluteIndexedYAccumulator<Operator::MOV>
{
public:
    MOV_D6(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_D6 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D6: MOV !a+Y, A"; }

    State& state;
};

// MOV !a, A
// (a) = A        (read)
// Absolute Accumulator (3-Byte)
class MOV_C5 : public AddressMode::AbsoluteAccumulator<Operator::MOV>
{
public:
    MOV_C5(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_C5 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C5: MOV !a, A"; }

    State& state;
};

// MOV !a, X
// (a) = X        (read)
// Absolute Index X (3-Byte)
class MOV_C9 : public AddressMode::AbsoluteIndexX<Operator::MOV>
{
public:
    MOV_C9(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_C9 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C9: MOV !a, X"; }

    State& state;
};

// MOV !a, Y
// (a) = Y        (read)
// Absolute Index Y (3-Byte)
class MOV_CC : public AddressMode::AbsoluteIndexY<Operator::MOV>
{
public:
    MOV_CC(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV_CC is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CC: MOV !a, Y"; }

    State& state;
};

// MOV1 C, m.b
// C = (m.b)
// Carry Memory Bit (3-Byte)
class MOV1_AA : public AddressMode::CarryMemoryBit<Operator::MOV1>
{
public:
    MOV1_AA(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV1_AA is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AA: MOV1 C, m.b"; }

    State& state;
};

// MOV1 m.b, C
// (m.b) = C
// Memory Bit Carry (3-Byte)
class MOV1_CA : public AddressMode::MemoryBitCarry<Operator::MOV1>
{
public:
    MOV1_CA(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOV1_CA is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CA: MOV1 m.b, C"; }

    State& state;
};

// MOVW YA, d
// YA = word (d)
// Y Accumulator Direct (2-Byte)
class MOVW_BA : public AddressMode::YAccumulatorDirect<Operator::MOVW>
{
public:
    MOVW_BA(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOVW_BA is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "BA: MOVW YA, d"; }

    State& state;
};

// MOVW d, YA
// word (d) = YA  (read low only)
// Direct Y Accumulator (2-Byte)
class MOVW_DA : public AddressMode::DirectYAccumulator<Operator::MOVW>
{
public:
    MOVW_DA(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MOVW_DA is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "DA: MOVW d, YA"; }

    State& state;
};

// MUL YA
// YA = Y * A, NZ on Y only
// Index Y Accumulator (1-Byte)
class MUL_CF : public AddressMode::IndexYAccumulator<Operator::MUL>
{
public:
    MUL_CF(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("MUL_CF is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CF: MUL YA"; }

    State& state;
};

// NOP 
// do nothing
// Implied (1-Byte)
class NOP_00 : public AddressMode::Implied<Operator::NOP>
{
public:
    NOP_00(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("NOP_00 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "00: NOP "; }

    State& state;
};

// NOT1 m.b
// m.b = ~m.b
// Memory Bit (3-Byte)
class NOT1_EA : public AddressMode::MemoryBit<Operator::NOT1>
{
public:
    NOT1_EA(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("NOT1_EA is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EA: NOT1 m.b"; }

    State& state;
};

// NOTC 
// C = !C
// Implied (1-Byte)
class NOTC_ED : public AddressMode::Implied<Operator::NOTC>
{
public:
    NOTC_ED(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("NOTC_ED is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "ED: NOTC "; }

    State& state;
};

// OR (X), (Y)
// (X) = (X) | (Y)
// X Indirect Y Indirect (1-Byte)
class OR_19 : public AddressMode::XIndirectYIndirect<Operator::OR>
{
public:
    OR_19(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_19 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "19: OR (X), (Y)"; }

    State& state;
};

// OR A, #i
// A = A | i
// Accumulator Immediate (2-Byte)
class OR_08 : public AddressMode::AccumulatorImmediate<Operator::OR>
{
public:
    OR_08(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_08 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "08: OR A, #i"; }

    State& state;
};

// OR A, (X)
// A = A | (X)
// Accumulator X Indirect (1-Byte)
class OR_06 : public AddressMode::AccumulatorXIndirect<Operator::OR>
{
public:
    OR_06(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_06 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "06: OR A, (X)"; }

    State& state;
};

// OR A, [d]+Y
// A = A | ([d]+Y)
// Accumulator Direct Indirect Indexed, Y (2-Byte)
class OR_17 : public AddressMode::AccumulatorDirectIndirectIndexedY<Operator::OR>
{
public:
    OR_17(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_17 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "17: OR A, [d]+Y"; }

    State& state;
};

// OR A, [d+X]
// A = A | ([d+X])
// Accumulator Direct Indexed, X Indirect (2-Byte)
class OR_07 : public AddressMode::AccumulatorDirectIndexedXIndirect<Operator::OR>
{
public:
    OR_07(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_07 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "07: OR A, [d+X]"; }

    State& state;
};

// OR A, d
// A = A | (d)
// Accumulator Direct (2-Byte)
class OR_04 : public AddressMode::AccumulatorDirect<Operator::OR>
{
public:
    OR_04(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_04 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "04: OR A, d"; }

    State& state;
};

// OR A, d+X
// A = A | (d+X)
// Accumulator Direct Indexed, X (2-Byte)
class OR_14 : public AddressMode::AccumulatorDirectIndexedX<Operator::OR>
{
public:
    OR_14(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_14 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "14: OR A, d+X"; }

    State& state;
};

// OR A, !a
// A = A | (a)
// Accumulator Absolute (3-Byte)
class OR_05 : public AddressMode::AccumulatorAbsolute<Operator::OR>
{
public:
    OR_05(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_05 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "05: OR A, !a"; }

    State& state;
};

// OR A, !a+X
// A = A | (a+X)
// Accumulator Absolute Indexed, X (3-Byte)
class OR_15 : public AddressMode::AccumulatorAbsoluteIndexedX<Operator::OR>
{
public:
    OR_15(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_15 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "15: OR A, !a+X"; }

    State& state;
};

// OR A, !a+Y
// A = A | (a+Y)
// Accumulator Absolute Indexed, Y (3-Byte)
class OR_16 : public AddressMode::AccumulatorAbsoluteIndexedY<Operator::OR>
{
public:
    OR_16(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_16 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "16: OR A, !a+Y"; }

    State& state;
};

// OR dd, ds
// (dd) = (dd) | (ds)
// Direct Direct (3-Byte)
class OR_09 : public AddressMode::DirectDirect<Operator::OR>
{
public:
    OR_09(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_09 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "09: OR dd, ds"; }

    State& state;
};

// OR d, #i
// (d) = (d) | i
// Direct Immediate (3-Byte)
class OR_18 : public AddressMode::DirectImmediate<Operator::OR>
{
public:
    OR_18(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR_18 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "18: OR d, #i"; }

    State& state;
};

// OR1 C, /m.b
// C = C | ~(m.b)
// Carry Not Memory Bit (3-Byte)
class OR1_2A : public AddressMode::CarryNotMemoryBit<Operator::OR1>
{
public:
    OR1_2A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR1_2A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2A: OR1 C, /m.b"; }

    State& state;
};

// OR1 C, m.b
// C = C | (m.b)
// Carry Memory Bit (3-Byte)
class OR1_0A : public AddressMode::CarryMemoryBit<Operator::OR1>
{
public:
    OR1_0A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("OR1_0A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0A: OR1 C, m.b"; }

    State& state;
};

// PCALL u
// CALL $FF00+u
// U Page (2-Byte)
class PCALL_4F : public AddressMode::UPage<Operator::PCALL>
{
public:
    PCALL_4F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("PCALL_4F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4F: PCALL u"; }

    State& state;
};

// POP A
// A = (++SP)
// Accumulator (1-Byte)
class POP_AE : public AddressMode::Accumulator<Operator::POP>
{
public:
    POP_AE(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("POP_AE is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "AE: POP A"; }

    State& state;
};

// POP PSW
// Flags = (++SP)
// State Flags (1-Byte)
class POP_8E : public AddressMode::StateFlags<Operator::POP>
{
public:
    POP_8E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("POP_8E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "8E: POP PSW"; }

    State& state;
};

// POP X
// X = (++SP)
// Index X (1-Byte)
class POP_CE : public AddressMode::IndexX<Operator::POP>
{
public:
    POP_CE(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("POP_CE is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "CE: POP X"; }

    State& state;
};

// POP Y
// Y = (++SP)
// Index Y (1-Byte)
class POP_EE : public AddressMode::IndexY<Operator::POP>
{
public:
    POP_EE(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("POP_EE is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EE: POP Y"; }

    State& state;
};

// PUSH A
// (SP--) = A
// Accumulator (1-Byte)
class PUSH_2D : public AddressMode::Accumulator<Operator::PUSH>
{
public:
    PUSH_2D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("PUSH_2D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2D: PUSH A"; }

    State& state;
};

// PUSH PSW
// (SP--) = Flags
// State Flags (1-Byte)
class PUSH_0D : public AddressMode::StateFlags<Operator::PUSH>
{
public:
    PUSH_0D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("PUSH_0D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0D: PUSH PSW"; }

    State& state;
};

// PUSH X
// (SP--) = X
// Index X (1-Byte)
class PUSH_4D : public AddressMode::IndexX<Operator::PUSH>
{
public:
    PUSH_4D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("PUSH_4D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4D: PUSH X"; }

    State& state;
};

// PUSH Y
// (SP--) = Y
// Index Y (1-Byte)
class PUSH_6D : public AddressMode::IndexY<Operator::PUSH>
{
public:
    PUSH_6D(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("PUSH_6D is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6D: PUSH Y"; }

    State& state;
};

// RET 
// Pop PC
// Implied (1-Byte)
class RET_6F : public AddressMode::Implied<Operator::RET>
{
public:
    RET_6F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("RET_6F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6F: RET "; }

    State& state;
};

// RET1 
// Pop Flags, PC
// Implied (1-Byte)
class RET1_7F : public AddressMode::Implied<Operator::RET1>
{
public:
    RET1_7F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("RET1_7F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7F: RET1 "; }

    State& state;
};

// ROL A
// Left shift A: low=C, C=high
// Accumulator (1-Byte)
class ROL_3C : public AddressMode::Accumulator<Operator::ROL>
{
public:
    ROL_3C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROL_3C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3C: ROL A"; }

    State& state;
};

// ROL d
// Left shift (d) as above
// Direct (2-Byte)
class ROL_2B : public AddressMode::Direct<Operator::ROL>
{
public:
    ROL_2B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROL_2B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2B: ROL d"; }

    State& state;
};

// ROL d+X
// Left shift (d+X) as above
// Direct Indexed, X (2-Byte)
class ROL_3B : public AddressMode::DirectIndexedX<Operator::ROL>
{
public:
    ROL_3B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROL_3B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "3B: ROL d+X"; }

    State& state;
};

// ROL !a
// Left shift (a) as above
// Absolute (3-Byte)
class ROL_2C : public AddressMode::Absolute<Operator::ROL>
{
public:
    ROL_2C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROL_2C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "2C: ROL !a"; }

    State& state;
};

// ROR A
// Right shift A: high=C, C=low
// Accumulator (1-Byte)
class ROR_7C : public AddressMode::Accumulator<Operator::ROR>
{
public:
    ROR_7C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROR_7C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7C: ROR A"; }

    State& state;
};

// ROR d
// Right shift (d) as above
// Direct (2-Byte)
class ROR_6B : public AddressMode::Direct<Operator::ROR>
{
public:
    ROR_6B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROR_6B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6B: ROR d"; }

    State& state;
};

// ROR d+X
// Right shift (d+X) as above
// Direct Indexed, X (2-Byte)
class ROR_7B : public AddressMode::DirectIndexedX<Operator::ROR>
{
public:
    ROR_7B(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROR_7B is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "7B: ROR d+X"; }

    State& state;
};

// ROR !a
// Right shift (a) as above
// Absolute (3-Byte)
class ROR_6C : public AddressMode::Absolute<Operator::ROR>
{
public:
    ROR_6C(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("ROR_6C is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "6C: ROR !a"; }

    State& state;
};

// SBC (X), (Y)
// (X) = (X)-(Y)-!C
// X Indirect Y Indirect (1-Byte)
class SBC_B9 : public AddressMode::XIndirectYIndirect<Operator::SBC>
{
public:
    SBC_B9(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_B9 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B9: SBC (X), (Y)"; }

    State& state;
};

// SBC A, #i
// A = A-i-!C
// Accumulator Immediate (2-Byte)
class SBC_A8 : public AddressMode::AccumulatorImmediate<Operator::SBC>
{
public:
    SBC_A8(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_A8 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A8: SBC A, #i"; }

    State& state;
};

// SBC A, (X)
// A = A-(X)-!C
// Accumulator X Indirect (1-Byte)
class SBC_A6 : public AddressMode::AccumulatorXIndirect<Operator::SBC>
{
public:
    SBC_A6(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_A6 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A6: SBC A, (X)"; }

    State& state;
};

// SBC A, [d]+Y
// A = A-([d]+Y)-!C
// Accumulator Direct Indirect Indexed, Y (2-Byte)
class SBC_B7 : public AddressMode::AccumulatorDirectIndirectIndexedY<Operator::SBC>
{
public:
    SBC_B7(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_B7 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B7: SBC A, [d]+Y"; }

    State& state;
};

// SBC A, [d+X]
// A = A-([d+X])-!C
// Accumulator Direct Indexed, X Indirect (2-Byte)
class SBC_A7 : public AddressMode::AccumulatorDirectIndexedXIndirect<Operator::SBC>
{
public:
    SBC_A7(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_A7 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A7: SBC A, [d+X]"; }

    State& state;
};

// SBC A, d
// A = A-(d)-!C
// Accumulator Direct (2-Byte)
class SBC_A4 : public AddressMode::AccumulatorDirect<Operator::SBC>
{
public:
    SBC_A4(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_A4 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A4: SBC A, d"; }

    State& state;
};

// SBC A, d+X
// A = A-(d+X)-!C
// Accumulator Direct Indexed, X (2-Byte)
class SBC_B4 : public AddressMode::AccumulatorDirectIndexedX<Operator::SBC>
{
public:
    SBC_B4(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_B4 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B4: SBC A, d+X"; }

    State& state;
};

// SBC A, !a
// A = A-(a)-!C
// Accumulator Absolute (3-Byte)
class SBC_A5 : public AddressMode::AccumulatorAbsolute<Operator::SBC>
{
public:
    SBC_A5(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_A5 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A5: SBC A, !a"; }

    State& state;
};

// SBC A, !a+X
// A = A-(a+X)-!C
// Accumulator Absolute Indexed, X (3-Byte)
class SBC_B5 : public AddressMode::AccumulatorAbsoluteIndexedX<Operator::SBC>
{
public:
    SBC_B5(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_B5 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B5: SBC A, !a+X"; }

    State& state;
};

// SBC A, !a+Y
// A = A-(a+Y)-!C
// Accumulator Absolute Indexed, Y (3-Byte)
class SBC_B6 : public AddressMode::AccumulatorAbsoluteIndexedY<Operator::SBC>
{
public:
    SBC_B6(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_B6 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B6: SBC A, !a+Y"; }

    State& state;
};

// SBC dd, ds
// (dd) = (dd)-(ds)-!C
// Direct Direct (3-Byte)
class SBC_A9 : public AddressMode::DirectDirect<Operator::SBC>
{
public:
    SBC_A9(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_A9 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A9: SBC dd, ds"; }

    State& state;
};

// SBC d, #i
// (d) = (d)-i-!C
// Direct Immediate (3-Byte)
class SBC_B8 : public AddressMode::DirectImmediate<Operator::SBC>
{
public:
    SBC_B8(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SBC_B8 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B8: SBC d, #i"; }

    State& state;
};

// SET1 d.0
// d.0 = 1
// Direct Bit (2-Byte)
class SET1_02 : public AddressMode::DirectBit<Operator::SET1, 1 << 0>
{
public:
    SET1_02(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_02 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "02: SET1 d.0"; }

    State& state;
};

// SET1 d.1
// d.1 = 1
// Direct Bit (2-Byte)
class SET1_22 : public AddressMode::DirectBit<Operator::SET1, 1 << 1>
{
public:
    SET1_22(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_22 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "22: SET1 d.1"; }

    State& state;
};

// SET1 d.2
// d.2 = 1
// Direct Bit (2-Byte)
class SET1_42 : public AddressMode::DirectBit<Operator::SET1, 1 << 2>
{
public:
    SET1_42(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_42 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "42: SET1 d.2"; }

    State& state;
};

// SET1 d.3
// d.3 = 1
// Direct Bit (2-Byte)
class SET1_62 : public AddressMode::DirectBit<Operator::SET1, 1 << 3>
{
public:
    SET1_62(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_62 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "62: SET1 d.3"; }

    State& state;
};

// SET1 d.4
// d.4 = 1
// Direct Bit (2-Byte)
class SET1_82 : public AddressMode::DirectBit<Operator::SET1, 1 << 4>
{
public:
    SET1_82(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_82 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "82: SET1 d.4"; }

    State& state;
};

// SET1 d.5
// d.5 = 1
// Direct Bit (2-Byte)
class SET1_A2 : public AddressMode::DirectBit<Operator::SET1, 1 << 5>
{
public:
    SET1_A2(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_A2 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A2: SET1 d.5"; }

    State& state;
};

// SET1 d.6
// d.6 = 1
// Direct Bit (2-Byte)
class SET1_C2 : public AddressMode::DirectBit<Operator::SET1, 1 << 6>
{
public:
    SET1_C2(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_C2 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C2: SET1 d.6"; }

    State& state;
};

// SET1 d.7
// d.7 = 1
// Direct Bit (2-Byte)
class SET1_E2 : public AddressMode::DirectBit<Operator::SET1, 1 << 7>
{
public:
    SET1_E2(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SET1_E2 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E2: SET1 d.7"; }

    State& state;
};

// SETC 
// C = 1
// Implied (1-Byte)
class SETC_80 : public AddressMode::Implied<Operator::SETC>
{
public:
    SETC_80(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SETC_80 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "80: SETC "; }

    State& state;
};

// SETP 
// P = 1
// Implied (1-Byte)
class SETP_40 : public AddressMode::Implied<Operator::SETP>
{
public:
    SETP_40(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SETP_40 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "40: SETP "; }

    State& state;
};

// SLEEP 
// Halts the processor
// Implied (1-Byte)
class SLEEP_EF : public AddressMode::Implied<Operator::SLEEP>
{
public:
    SLEEP_EF(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SLEEP_EF is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "EF: SLEEP "; }

    State& state;
};

// STOP 
// Halts the processor
// Implied (1-Byte)
class STOP_FF : public AddressMode::Implied<Operator::STOP>
{
public:
    STOP_FF(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("STOP_FF is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "FF: STOP "; }

    State& state;
};

// SUBW YA, d
// YA  = YA - (d), H on high byte
// Y Accumulator Direct (2-Byte)
class SUBW_9A : public AddressMode::YAccumulatorDirect<Operator::SUBW>
{
public:
    SUBW_9A(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("SUBW_9A is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9A: SUBW YA, d"; }

    State& state;
};

// TCALL 0
// CALL [$FFDE]
// Table (1-Byte)
class TCALL_01 : public AddressMode::Table<Operator::TCALL, 0>
{
public:
    TCALL_01(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_01 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "01: TCALL 0"; }

    State& state;
};

// TCALL 1
// CALL [$FFDC]
// Table (1-Byte)
class TCALL_11 : public AddressMode::Table<Operator::TCALL, 1>
{
public:
    TCALL_11(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_11 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "11: TCALL 1"; }

    State& state;
};

// TCALL 2
// CALL [$FFDA]
// Table (1-Byte)
class TCALL_21 : public AddressMode::Table<Operator::TCALL, 2>
{
public:
    TCALL_21(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_21 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "21: TCALL 2"; }

    State& state;
};

// TCALL 3
// CALL [$FFD8]
// Table (1-Byte)
class TCALL_31 : public AddressMode::Table<Operator::TCALL, 3>
{
public:
    TCALL_31(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_31 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "31: TCALL 3"; }

    State& state;
};

// TCALL 4
// CALL [$FFD6]
// Table (1-Byte)
class TCALL_41 : public AddressMode::Table<Operator::TCALL, 4>
{
public:
    TCALL_41(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_41 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "41: TCALL 4"; }

    State& state;
};

// TCALL 5
// CALL [$FFD4]
// Table (1-Byte)
class TCALL_51 : public AddressMode::Table<Operator::TCALL, 5>
{
public:
    TCALL_51(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_51 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "51: TCALL 5"; }

    State& state;
};

// TCALL 6
// CALL [$FFD2]
// Table (1-Byte)
class TCALL_61 : public AddressMode::Table<Operator::TCALL, 6>
{
public:
    TCALL_61(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_61 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "61: TCALL 6"; }

    State& state;
};

// TCALL 7
// CALL [$FFD0]
// Table (1-Byte)
class TCALL_71 : public AddressMode::Table<Operator::TCALL, 7>
{
public:
    TCALL_71(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_71 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "71: TCALL 7"; }

    State& state;
};

// TCALL 8
// CALL [$FFCE]
// Table (1-Byte)
class TCALL_81 : public AddressMode::Table<Operator::TCALL, 8>
{
public:
    TCALL_81(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_81 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "81: TCALL 8"; }

    State& state;
};

// TCALL 9
// CALL [$FFCC]
// Table (1-Byte)
class TCALL_91 : public AddressMode::Table<Operator::TCALL, 9>
{
public:
    TCALL_91(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_91 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "91: TCALL 9"; }

    State& state;
};

// TCALL 10
// CALL [$FFCA]
// Table (1-Byte)
class TCALL_A1 : public AddressMode::Table<Operator::TCALL, 10>
{
public:
    TCALL_A1(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_A1 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "A1: TCALL 10"; }

    State& state;
};

// TCALL 11
// CALL [$FFC8]
// Table (1-Byte)
class TCALL_B1 : public AddressMode::Table<Operator::TCALL, 11>
{
public:
    TCALL_B1(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_B1 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "B1: TCALL 11"; }

    State& state;
};

// TCALL 12
// CALL [$FFC6]
// Table (1-Byte)
class TCALL_C1 : public AddressMode::Table<Operator::TCALL, 12>
{
public:
    TCALL_C1(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_C1 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "C1: TCALL 12"; }

    State& state;
};

// TCALL 13
// CALL [$FFC4]
// Table (1-Byte)
class TCALL_D1 : public AddressMode::Table<Operator::TCALL, 13>
{
public:
    TCALL_D1(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_D1 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "D1: TCALL 13"; }

    State& state;
};

// TCALL 14
// CALL [$FFC2]
// Table (1-Byte)
class TCALL_E1 : public AddressMode::Table<Operator::TCALL, 14>
{
public:
    TCALL_E1(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_E1 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "E1: TCALL 14"; }

    State& state;
};

// TCALL 15
// CALL [$FFC0]
// Table (1-Byte)
class TCALL_F1 : public AddressMode::Table<Operator::TCALL, 15>
{
public:
    TCALL_F1(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCALL_F1 is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "F1: TCALL 15"; }

    State& state;
};

// TCLR1 !a
// (a) = (a)&~A, ZN as for A-(a)
// Absolute (3-Byte)
class TCLR1_4E : public AddressMode::Absolute<Operator::TCLR1>
{
public:
    TCLR1_4E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TCLR1_4E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "4E: TCLR1 !a"; }

    State& state;
};

// TSET1 !a
// (a) = (a)|A, ZN as for A-(a)
// Absolute (3-Byte)
class TSET1_0E : public AddressMode::Absolute<Operator::TSET1>
{
public:
    TSET1_0E(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("TSET1_0E is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "0E: TSET1 !a"; }

    State& state;
};

// XCN A
// A = (A>>4) | (A<<4)
// Accumulator (1-Byte)
class XCN_9F : public AddressMode::Accumulator<Operator::XCN>
{
public:
    XCN_9F(State& state) : state(state)
    {
    }

private:
    int execute() const override
    {
        throw std::runtime_error("XCN_9F is not implemented");
        return 0 + applyOperand(state);
    }

    std::string opcodeToString() const override { return "9F: XCN A"; }

    State& state;
};

}

}
