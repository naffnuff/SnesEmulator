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
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
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
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("Not implemented");
        int cycles = 0;
        // 3: Add 1 cycle if adding index crosses a page boundary
        cycles += 0 /* TODO03 */;
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
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("Not implemented");
        int cycles = 0;
        // 3: Add 1 cycle if adding index crosses a page boundary
        cycles += 0 /* TODO03 */;
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
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
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
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
        throw std::runtime_error("Not implemented");
        int cycles = 0;
        // 3: Add 1 cycle if adding index crosses a page boundary
        cycles += 0 /* TODO03 */;
        uint8_t* data = nullptr;
        return cycles + Operator::invoke(state, data);
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        int cycles = 0;
        // 3: Add 1 cycle if adding index crosses a page boundary
        cycles += 0 /* TODO03 */;
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
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
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Immediate
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
template <typename Operator, State::Flag Flag>
class ImmediateVariableSize : public InstructionVariableSize<Flag>
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Stack (Absolute)
template <typename Operator>
class StackAbsolute : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Stack (Direct Page Indirect)
template <typename Operator>
class StackDirectPageIndirect : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Stack/Interrupt
template <typename Operator>
class StackInterrupt : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// Stack (Program Counter Relative Long)
template <typename Operator>
class StackProgramCounterRelativeLong : public Instruction3Byte
{
    int invokeOperator(State& state, uint8_t lowByte, uint8_t highByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
    }
};

// Stack (Pull)
template <typename Operator>
class StackPull : public Instruction1Byte
{
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " TODO";
    }
};

// Stack (Push)
template <typename Operator>
class StackPush : public Instruction1Byte
{
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " TODO";
    }
};

// Stack (RTI)
template <typename Operator>
class StackRTI : public Instruction1Byte
{
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " TODO";
    }
};

// Stack (RTL)
template <typename Operator>
class StackRTL : public Instruction1Byte
{
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " TODO";
    }
};

// Stack (RTS)
template <typename Operator>
class StackRTS : public Instruction1Byte
{
    int invokeOperator(State& state) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " TODO";
    }
};

// Stack Relative
template <typename Operator>
class StackRelative : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
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
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

// n/a
template <typename Operator>
class na : public Instruction2Byte
{
    int invokeOperator(State& state, uint8_t lowByte) const override
    {
        throw std::runtime_error("Not implemented");
        uint8_t* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString(const State& state) const override
    {
        return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
    }
};

}
