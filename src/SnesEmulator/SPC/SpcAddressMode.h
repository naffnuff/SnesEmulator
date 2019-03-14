#pragma once

#include <stdint.h>

#include "../Instruction.h"
#include "SpcState.h"

namespace SPC {

namespace AddressMode {

// Absolute
// !a
template <typename Operator>
class Absolute : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("Absolute is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Accumulator
// !a, A
template <typename Operator>
class AbsoluteAccumulator : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AbsoluteAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Index X
// !a, X
template <typename Operator>
class AbsoluteIndexX : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AbsoluteIndexX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Index Y
// !a, Y
template <typename Operator>
class AbsoluteIndexY : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AbsoluteIndexY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Indexed, X Accumulator
// !a+X, A
template <typename Operator>
class AbsoluteIndexedXAccumulator : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AbsoluteIndexedXAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Indexed, X Indirect
// [!a+X]
template <typename Operator>
class AbsoluteIndexedXIndirect : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AbsoluteIndexedXIndirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Indexed, Y Accumulator
// !a+Y, A
template <typename Operator>
class AbsoluteIndexedYAccumulator : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AbsoluteIndexedYAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator
// A
template <typename Operator>
class Accumulator : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("Accumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Accumulator Absolute
// A, !a
template <typename Operator>
class AccumulatorAbsolute : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AccumulatorAbsolute is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Absolute Indexed, X
// A, !a+X
template <typename Operator>
class AccumulatorAbsoluteIndexedX : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AccumulatorAbsoluteIndexedX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Absolute Indexed, Y
// A, !a+Y
template <typename Operator>
class AccumulatorAbsoluteIndexedY : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("AccumulatorAbsoluteIndexedY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Direct
// A, d
template <typename Operator>
class AccumulatorDirect : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("AccumulatorDirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Direct Indexed, X
// A, d+X
template <typename Operator>
class AccumulatorDirectIndexedX : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("AccumulatorDirectIndexedX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Direct Indexed, X Indirect
// A, [d+X]
template <typename Operator>
class AccumulatorDirectIndexedXIndirect : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("AccumulatorDirectIndexedXIndirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Direct Indirect Indexed, Y
// A, [d]+Y
template <typename Operator>
class AccumulatorDirectIndirectIndexedY : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("AccumulatorDirectIndirectIndexedY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Immediate
// A, #i
template <typename Operator>
class AccumulatorImmediate : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("AccumulatorImmediate is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Accumulator Index X
// A, X
template <typename Operator>
class AccumulatorIndexX : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("AccumulatorIndexX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Accumulator Index Y
// A, Y
template <typename Operator>
class AccumulatorIndexY : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("AccumulatorIndexY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Accumulator X Indirect
// A, (X)
template <typename Operator>
class AccumulatorXIndirect : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("AccumulatorXIndirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Accumulator X Indirect Plus
// A, (X)+
template <typename Operator>
class AccumulatorXIndirectPlus : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("AccumulatorXIndirectPlus is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Carry Memory Bit
// C, m.b
template <typename Operator>
class CarryMemoryBit : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("CarryMemoryBit is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Carry Not Memory Bit
// C, /m.b
template <typename Operator>
class CarryNotMemoryBit : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("CarryNotMemoryBit is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct
// d
template <typename Operator>
class Direct : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("Direct is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Accumulator
// d, A
template <typename Operator>
class DirectAccumulator : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Bit
// d.7
template <typename Operator, uint8_t bitMask>
class DirectBit : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectBit is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Bit Program Counter Relative
// d.7, r
template <typename Operator, uint8_t bitMask>
class DirectBitProgramCounterRelative : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("DirectBitProgramCounterRelative is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Direct
// dd, ds
template <typename Operator>
class DirectDirect : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("DirectDirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Immediate
// d, #i
template <typename Operator>
class DirectImmediate : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("DirectImmediate is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Index X
// d, X
template <typename Operator>
class DirectIndexX : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndexX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Index Y
// d, Y
template <typename Operator>
class DirectIndexY : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndexY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed, X
// d+X
template <typename Operator>
class DirectIndexedX : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndexedX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed, X Accumulator
// d+X, A
template <typename Operator>
class DirectIndexedXAccumulator : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndexedXAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed, X Index Y
// d+X, Y
template <typename Operator>
class DirectIndexedXIndexY : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndexedXIndexY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed, X Indirect Accumulator
// [d+X], A
template <typename Operator>
class DirectIndexedXIndirectAccumulator : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndexedXIndirectAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed, X Program Counter Relative
// d+X, r
template <typename Operator>
class DirectIndexedXProgramCounterRelative : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("DirectIndexedXProgramCounterRelative is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed, Y Index X
// d+Y, X
template <typename Operator>
class DirectIndexedYIndexX : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndexedYIndexX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indirect Indexed, Y Accumulator
// [d]+Y, A
template <typename Operator>
class DirectIndirectIndexedYAccumulator : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectIndirectIndexedYAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Program Counter Relative
// d, r
template <typename Operator>
class DirectProgramCounterRelative : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("DirectProgramCounterRelative is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Y Accumulator
// d, YA
template <typename Operator>
class DirectYAccumulator : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("DirectYAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Implied
// 
template <typename Operator>
class Implied : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("Implied is not implemented");
        return Operator::invoke(state);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Index X
// X
template <typename Operator>
class IndexX : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("IndexX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Index X Absolute
// X, !a
template <typename Operator>
class IndexXAbsolute : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("IndexXAbsolute is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index X Accumulator
// X, A
template <typename Operator>
class IndexXAccumulator : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("IndexXAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Index X Direct
// X, d
template <typename Operator>
class IndexXDirect : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("IndexXDirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index X Direct Indexed, Y
// X, d+Y
template <typename Operator>
class IndexXDirectIndexedY : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("IndexXDirectIndexedY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index X Immediate
// X, #i
template <typename Operator>
class IndexXImmediate : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("IndexXImmediate is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index X Stack Pointer
// X, SP
template <typename Operator>
class IndexXStackPointer : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("IndexXStackPointer is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Index Y
// Y
template <typename Operator>
class IndexY : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("IndexY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Index Y Absolute
// Y, !a
template <typename Operator>
class IndexYAbsolute : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("IndexYAbsolute is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index Y Accumulator
// YA
template <typename Operator>
class IndexYAccumulator : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("IndexYAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Index Y Direct
// Y, d
template <typename Operator>
class IndexYDirect : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("IndexYDirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index Y Direct Indexed, X
// Y, d+X
template <typename Operator>
class IndexYDirectIndexedX : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("IndexYDirectIndexedX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index Y Immediate
// Y, #i
template <typename Operator>
class IndexYImmediate : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("IndexYImmediate is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Index Y Program Counter Relative
// Y, r
template <typename Operator>
class IndexYProgramCounterRelative : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("IndexYProgramCounterRelative is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Memory Bit
// m.b
template <typename Operator>
class MemoryBit : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("MemoryBit is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Memory Bit Carry
// m.b, C
template <typename Operator>
class MemoryBitCarry : public Instruction3Byte<State>
{
    Instruction3Byte::Instruction3Byte;

    int invokeOperator(uint8_t lowByte, uint8_t highByte) override
    {
        throw std::runtime_error("MemoryBitCarry is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Program Counter Relative
// r
template <typename Operator>
class ProgramCounterRelative : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("ProgramCounterRelative is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Stack Pointer Index X
// SP, X
template <typename Operator>
class StackPointerIndexX : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("StackPointerIndexX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// State Flags
// PSW
template <typename Operator>
class StateFlags : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("StateFlags is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Table
// 15
template <typename Operator, uint8_t index>
class Table : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("Table is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// U Page
// u
template <typename Operator>
class UPage : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("UPage is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// X Indirect Accumulator
// (X), A
template <typename Operator>
class XIndirectAccumulator : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("XIndirectAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// X Indirect Plus Accumulator
// (X)+, A
template <typename Operator>
class XIndirectPlusAccumulator : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("XIndirectPlusAccumulator is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// X Indirect Y Indirect
// (X), (Y)
template <typename Operator>
class XIndirectYIndirect : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("XIndirectYIndirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Y Accumulator Direct
// YA, d
template <typename Operator>
class YAccumulatorDirect : public Instruction2Byte<State>
{
    Instruction2Byte::Instruction2Byte;

    int invokeOperator(uint8_t lowByte) override
    {
        throw std::runtime_error("YAccumulatorDirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Y Accumulator Index X
// YA, X
template <typename Operator>
class YAccumulatorIndexX : public Instruction1Byte<State>
{
    Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        throw std::runtime_error("YAccumulatorIndexX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

}

}

