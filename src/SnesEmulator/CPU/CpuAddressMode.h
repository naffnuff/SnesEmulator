#pragma once
 
#include "../Instruction.h"
#include "CpuOperator.h"
#include "CpuState.h"

namespace CPU {

typedef InstructionBase<State> Instruction1Byte;
typedef InstructionBase<State, Byte> Instruction2Byte;
typedef InstructionBase<State, Byte, Byte> Instruction3Byte;
typedef InstructionBase<State, Byte, Byte, Byte> Instruction4Byte;

namespace AddressMode {

// Absolute
// addr
template <typename Operator>
class Absolute : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, state.getMemoryPointer(lowByte, highByte));
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString();
    }
};

int Absolute<Operator::JSR>::invokeOperator(Byte lowByte, Byte highByte)
{
    return Operator::JSR::invoke(state, Word(lowByte, highByte));
}

// Absolute Indexed Indirect
// (addr,X)
template <typename Operator>
class AbsoluteIndexedIndirect : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw std::runtime_error("AbsoluteIndexedIndirect is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Indexed, X/Y
// addr,X/Y
template <typename Operator, State::IndexRegister Register>
class AbsoluteIndexed : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    // §3: Add 1 cycle if adding index crosses a page boundary
    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw std::runtime_error("AbsoluteIndexed is not implemented");
        int cycles = 0;
        if (true /*index added crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO03");
        }
        Byte* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Indirect
// (addr)
template <typename Operator>
class AbsoluteIndirect : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw std::runtime_error("AbsoluteIndirect is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Indirect Long
// [addr]
template <typename Operator>
class AbsoluteIndirectLong : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw std::runtime_error("AbsoluteIndirectLong is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Long
// long
template <typename Operator>
class AbsoluteLong : public Instruction4Byte
{
    using Instruction4Byte::Instruction4Byte;

    int invokeOperator(Byte lowByte, Byte highByte, Byte bankByte) override
    {
        throw std::runtime_error("AbsoluteLong is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Absolute Long Indexed, X
// long,X
template <typename Operator>
class AbsoluteLongIndexedX : public Instruction4Byte
{
    using Instruction4Byte::Instruction4Byte;

    int invokeOperator(Byte lowByte, Byte highByte, Byte bankByte) override
    {
        throw std::runtime_error("AbsoluteLongIndexedX is not implemented");
        Byte* data = nullptr;
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
class Accumulator : public Instruction1Byte
{
    using Instruction1Byte::Instruction1Byte;

    // §21: Remove 2 cycles for the special case of Accumulator
    int invokeOperator() override
    {
        int cycles = 0;
        if (state.is16Bit(State::m)) {
            cycles -= 2;
        }
        Byte* accumulator = state.getAccumulatorPointer();
        return cycles + Operator::invoke(state, accumulator);
    }

    std::string toString() const override
    {
        return Operator::toString() + " A";
    }
};

// Block Move
// srcbk,destbk
template <typename Operator>
class BlockMove : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw std::runtime_error("BlockMove is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Page
// dp
template <typename Operator>
class DirectPage : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        Byte* data = state.getMemoryPointer(lowByte);
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

// Direct Page Indexed Indirect, X
// (dp,X)
template <typename Operator>
class DirectPageIndexedIndirectX : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        throw std::runtime_error("DirectPageIndexedIndirectX is not implemented");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        Byte* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Page Indexed, X/Y
// dp,X/Y
template <typename Operator, State::IndexRegister Register>
class DirectPageIndexed : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        throw std::runtime_error("DirectPageIndexed is not implemented");
        int cycles = 0;
        if (Byte(state.getDirectPage())) {
            cycles += 1;
        }
        Byte* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Page Indirect
// (dp)
template <typename Operator>
class DirectPageIndirect : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        throw std::runtime_error("DirectPageIndirect is not implemented");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        Byte* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Page Indirect Indexed, Y
// (dp),Y
template <typename Operator>
class DirectPageIndirectIndexedY : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    // §3: Add 1 cycle if adding index crosses a page boundary
    int invokeOperator(Byte lowByte) override
    {
        throw std::runtime_error("DirectPageIndirectIndexedY is not implemented");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        if (true /*index added crosses page boundary*/) {
            cycles += 1;
            throw std::runtime_error("TODO03");
        }
        Byte* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Page Indirect Long
// [dp]
template <typename Operator>
class DirectPageIndirectLong : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        throw std::runtime_error("DirectPageIndirectLong is not implemented");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        Byte* data = nullptr;
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Page Indirect Long Indexed, Y
// [dp],Y
template <typename Operator>
class DirectPageIndirectLongIndexedY : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        Byte* address = state.getMemoryPointer(lowByte);
        Byte* data = state.getMemoryPointer(address[0], address[1], address[2], state.getIndexRegister<State::Y>());
        return cycles + Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " [$" + operandToString() + "], Y";
    }
};

// Immediate
// #const
template <typename Operator>
class Immediate : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, &lowByte);
    }

    std::string toString() const override
    {
        return Operator::toString() + " #$" + operandToString();
    }
};

// Immediate
// #const
template <typename Operator>
class Immediate16Bit : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        Word data = lowByte | highByte << 8;
        return Operator::invoke(state, (Byte*)&data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " #$" + operandToString();
    }
};

// Implied
template <typename Operator>
class Implied : public Instruction1Byte
{
    using Instruction1Byte::Instruction1Byte;

    int invokeOperator() override
    {
        return Operator::invoke(state);
    }

    std::string toString() const override
    {
        return Operator::toString();
    }
};

// Program Counter Relative
// nearlabel
template <typename Operator>
class ProgramCounterRelative : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, (int8_t)lowByte);
    }

    std::string toString() const override
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.readProgramByte(1)));
        return ss.str();
    }
};

// Program Counter Relative Long
// label
template <typename Operator>
class ProgramCounterRelativeLong : public Instruction3Byte
{
    using Instruction3Byte::Instruction3Byte;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw std::runtime_error("ProgramCounterRelativeLong is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Stack Relative
// sr,S
template <typename Operator>
class StackRelative : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    int invokeOperator(Byte lowByte) override
    {
        throw std::runtime_error("StackRelative is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Stack Relative Indirect Indexed, Y
// (sr,S),Y
template <typename Operator>
class StackRelativeIndirectIndexedY : public Instruction2Byte
{
    using Instruction2Byte::Instruction2Byte;

    int invokeOperator(Byte lowByte) override
    {
        throw std::runtime_error("StackRelativeIndirectIndexedY is not implemented");
        Byte* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

}

}