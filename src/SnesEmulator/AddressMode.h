#pragma once

#include <stdint.h>

#include "State.h"
#include "Instruction.h"

namespace AddressMode {

// Absolute
template <typename Operator>
class Absolute : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("Absolute is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Absolute Indexed Indirect
template <typename Operator>
class AbsoluteIndexedIndirect : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("AbsoluteIndexedIndirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Absolute Indexed, X
template <typename Operator>
class AbsoluteIndexedX : public Instruction3Byte
{
    // �3: Add 1 cycle if adding index crosses a page boundary
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("AbsoluteIndexedX is not implemented");
        int cycles = 0;
        if (true /*index added crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO03");
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Absolute Indexed, Y
template <typename Operator>
class AbsoluteIndexedY : public Instruction3Byte
{
    // �3: Add 1 cycle if adding index crosses a page boundary
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("AbsoluteIndexedY is not implemented");
        int cycles = 0;
        if (true /*index added crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO03");
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Absolute Indirect
template <typename Operator>
class AbsoluteIndirect : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("AbsoluteIndirect is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Absolute Indirect Long
template <typename Operator>
class AbsoluteIndirectLong : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("AbsoluteIndirectLong is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Absolute Long
template <typename Operator>
class AbsoluteLong : public Instruction4Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte, uint8_t bankByte) const override
    {
        throw std::runtime_error("AbsoluteLong is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction4Byte::operandToString(state) + " TODO";
    }
};

// Absolute Long Indexed, X
template <typename Operator>
class AbsoluteLongIndexedX : public Instruction4Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte, uint8_t bankByte) const override
    {
        throw std::runtime_error("AbsoluteLongIndexedX is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction4Byte::operandToString(state) + " TODO";
    }
};

// Accumulator
template <typename Operator>
class Accumulator : public Instruction1Byte
{
    // �21: Remove 2 cycles for the special case of Accumulator
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Accumulator is not implemented");
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles -= 2;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " TODO";
    }
};

// Block Move
template <typename Operator>
class BlockMove : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("BlockMove is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Direct Page
template <typename Operator>
class DirectPage : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPage is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Direct Page Indexed Indirect, X
template <typename Operator>
class DirectPageIndexedIndirectX : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPageIndexedIndirectX is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Direct Page Indexed, X
template <typename Operator>
class DirectPageIndexedX : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPageIndexedX is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Direct Page Indexed, Y
template <typename Operator>
class DirectPageIndexedY : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPageIndexedY is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Direct Page Indirect
template <typename Operator>
class DirectPageIndirect : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPageIndirect is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Direct Page Indirect Indexed, Y
template <typename Operator>
class DirectPageIndirectIndexedY : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    // �3: Add 1 cycle if adding index crosses a page boundary
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPageIndirectIndexedY is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        if (true /*index added crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO03");
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Direct Page Indirect Long
template <typename Operator>
class DirectPageIndirectLong : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPageIndirectLong is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Direct Page Indirect Long Indexed, Y
template <typename Operator>
class DirectPageIndirectLongIndexedY : public Instruction2Byte
{
    // �2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("DirectPageIndirectLongIndexedY is not implemented");
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Immediate
template <typename Operator>
class Immediate : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Immediate is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Immediate
// �17: Add 1 byte if m=0 (16-bit memory/accumulator)
template <typename Operator, State::Flag Flag>
class ImmediateVariableSize : public InstructionVariableSize<Flag>
{
    int invokeOperator(State& state, uint8_t lowByte) const override    {
        throw std::runtime_error("ImmediateVariableSize is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override    {
        throw std::runtime_error("ImmediateVariableSize is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + InstructionVariableSize<Flag>::operandToString(state) + " TODO";
    }
};

// Implied
template <typename Operator>
class Implied : public Instruction1Byte
{
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Implied is not implemented");
        return Operator::invoke(state);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " TODO";
    }
};

// Program Counter Relative
template <typename Operator>
class ProgramCounterRelative : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("ProgramCounterRelative is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Program Counter Relative Long
template <typename Operator>
class ProgramCounterRelativeLong : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("ProgramCounterRelativeLong is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Stack Relative
template <typename Operator>
class StackRelative : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("StackRelative is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Stack Relative Indirect Indexed, Y
template <typename Operator>
class StackRelativeIndirectIndexedY : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("StackRelativeIndirectIndexedY is not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

}
