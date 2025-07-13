#pragma once

#include "Exception.h"
#include "Instruction.h"
#include "Memory.h"
#include "CpuState.h"

#include "Profiler.h"

#define PROFILE_ADDRESS_MODES false

#pragma warning( disable : 4702 ) // unreachable code

namespace CPU {

using Instruction1Byte = InstructionType<State>;
using Instruction2Byte = InstructionType<State, Byte>;
using Instruction3Byte = InstructionType<State, Byte, Byte>;
using Instruction4Byte = InstructionType<State, Byte, Byte, Byte>;

namespace AddressMode {

CREATE_PROFILER();

EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)

// Absolute
// addr
template <typename Operator>
struct Absolute
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "Absolute");

        MemoryAccess access = state.getMemoryAccess(lowByte, highByte);
        return Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state);
    }
};

// Absolute (control flow)
// addr
template <typename Operator>
struct Absolute_ControlFlow
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "Absolute_ControlFlow");

        return Operator::invoke(state, Word(lowByte, highByte));
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state);
    }
};

// Absolute Indexed, X/Y
// addr,X/Y
template <typename Operator, State::IndexRegister Register, bool ExtraCycles>
struct AbsoluteIndexed
{
    using Type = Instruction3Byte;

    // §3: Add 1 cycle if adding index crosses a page boundary
    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "AbsoluteIndexed");

        Long staticAddress(lowByte, highByte, state.getDataBank());
        Long indexedAddress = staticAddress + state.getIndexRegister<Register>();
        MemoryAccess access = state.getMemoryAccess(indexedAddress);
        int cycles = 0;
        if constexpr (ExtraCycles)
        {
            Word addressPage(staticAddress >> 8);
            Word indexedAddressPage(indexedAddress >> 8);
            if (addressPage != indexedAddressPage)
            {
                cycles += 1;
            }
        }
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state) + "," + state.getIndexRegisterName<Register>();
    }
};

// Absolute Indexed Indirect
// (addr,X)
template <typename Operator>
struct AbsoluteIndexedIndirect
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "AbsoluteIndexedIndirect");

        Word indexedAddress = Word(lowByte, highByte) + state.getIndexRegister<State::IndexRegister::X>();
        Long longAddress(indexedAddress, state.getProgramBank());
        return Operator::invoke(state, state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(longAddress));
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " ($" + Type::operandToString(state) + ",X)";
    }
};

// Absolute Indirect
// (addr)
template <typename Operator>
struct AbsoluteIndirect
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "AbsoluteIndirect");

        return Operator::invoke(state, state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(Long(lowByte, highByte, 0)));
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " ($" + Type::operandToString(state) + ")";
    }
};

// Absolute Indirect Long
// [addr]
template <typename Operator>
struct AbsoluteIndirectLong
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "AbsoluteIndirectLong");

        return Operator::invoke(state, state.readMemoryLong<State::MemoryType::WrappingMask::Bank>(Long(lowByte, highByte, 0)));
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state);
    }
};

// Absolute Long
// long
template <typename Operator>
struct AbsoluteLong
{
    using Type = Instruction4Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte, Byte bankByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "AbsoluteLong");

        MemoryAccess access = state.getMemoryAccess(lowByte, highByte, bankByte);
        return Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state);
    }
};

// Absolute Long (control flow)
// long
template <typename Operator>
struct AbsoluteLong_ControlFlow
{
    using Type = Instruction4Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte, Byte bankByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "AbsoluteLong_ControlFlow");

        return Operator::invoke(state, Long(lowByte, highByte, bankByte));
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state);
    }
};

// Absolute Long Indexed, X
// long,X
template <typename Operator>
struct AbsoluteLongIndexedX
{
    using Type = Instruction4Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte, Byte bankByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "AbsoluteLongIndexedX");

        MemoryAccess access = state.getMemoryAccess(lowByte, highByte, bankByte, state.getIndexRegister<State::IndexRegister::X>());
        return Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state) + ",X";
    }
};

// Accumulator
// A
template <typename Operator>
struct Accumulator
{
    using Type = Instruction1Byte;

    // §21: Remove 2 cycles for the special case of Accumulator
    static int invokeOperator(State& state)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "Accumulator");

        int cycles = 0;
        if (state.is16Bit(State::Flag::m))
        {
            cycles -= 2;
        }
        State::AccumulatorAccess accumulatorAccess = state.getAccumulatorAccess();
        return cycles + Operator::invoke(state, accumulatorAccess);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " A";
    }
};

// Block Move
// srcbk,destbk
template <typename Operator>
struct BlockMove
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "BlockMove");

        Word byteCount = state.getAccumulatorC();
        if (byteCount != 0)
        {
            state.incrementProgramCounter(Word(-Type::size()));
        }
        state.setAccumulatorC(byteCount - 1);
        return Operator::invoke(state, highByte, lowByte, byteCount);
    }

    static std::string toString(const State& state)
    {
        std::string operands = Type::operandToString(state);
        return Operator::toString() + " $" + operands.substr(0, 2) + ",$" + operands.substr(2, 2);
    }
};

// Direct Page
// dp
template <typename Operator>
struct DirectPage
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPage");

        int cycles = 0;
        if (state.getDirectPageRegister().getLowByte() != 0)
        {
            cycles += 1;
        }
        MemoryAccess access = state.getDirectMemoryAccess(lowByte);
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state);
    }
};

// Direct Page Indexed, X/Y
// dp,X/Y
template <typename Operator, State::IndexRegister Register>
struct DirectPageIndexed
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPageIndexed");

        int cycles = 0;
        if (Byte(state.getDirectPageRegister()))
        {
            cycles += 1;
        }
        MemoryAccess access = state.getDirectMemoryAccess(lowByte, state.getIndexRegister<Register>());
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state) + "," + State::getIndexRegisterName<Register>();
    }
};

// Direct Page Indexed Indirect, X
// (dp,X)
template <typename Operator>
struct DirectPageIndexedIndirectX
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPageIndexedIndirectX");

        throw NotYetImplementedException("CPU::AddressMode::DirectPageIndexedIndirectX");
        int cycles = 0;
        if ((Byte)state.getDirectPageRegister())
        {
            cycles += 1;
        }
        MemoryAccess access = state.getMemoryAccess(0, 0, 0, 0);
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state) + " TODO";
    }
};

// Direct Page Indirect
// (dp)
template <typename Operator>
struct DirectPageIndirect
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPageIndirect");

        int cycles = 0;
        if ((Byte)state.getDirectPageRegister())
        {
            cycles += 1;
        }
        Long address(state.getDirectMemoryAccess(lowByte).readWord(), state.getDataBank());
        MemoryAccess access = state.getMemoryAccess(address);
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " ($" + Type::operandToString(state) + ")";
    }
};

// Direct Page Indirect (control flow)
// (dp)
template <typename Operator>
struct DirectPageIndirect_ControlFlow
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPageIndirect_ControlFlow");

        int cycles = 0;
        if ((Byte)state.getDirectPageRegister())
        {
            cycles += 1;
        }
        Word address = state.getDirectMemoryAccess(lowByte).readWord();
        return cycles + Operator::invoke(state, address);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " ($" + Type::operandToString(state) + ")";
    }
};

// Direct Page Indirect Indexed, Y
// (dp),Y
template <typename Operator, bool ExtraCycles>
struct DirectPageIndirectIndexedY
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    // §3: Add 1 cycle if adding index crosses a page boundary
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPageIndirectIndexedY");

        int cycles = 0;
        if ((Byte)state.getDirectPageRegister())
        {
            cycles += 1;
        }
        Long address(state.getDirectMemoryAccess(lowByte).readWord(), state.getDataBank());
        Long indexedAddress = address + state.getIndexRegister<State::IndexRegister::Y>();
        if constexpr (ExtraCycles)
        {
            if (address >> 8 != indexedAddress >> 8)
            {
                cycles += 1;
            }
        }
        MemoryAccess access = state.getMemoryAccess(indexedAddress);
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " ($" + Type::operandToString(state) + "),Y";
    }
};

// Direct Page Indirect Long
// [dp]
template <typename Operator>
struct DirectPageIndirectLong
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPageIndirectLong");

        int cycles = 0;
        if ((Byte)state.getDirectPageRegister())
        {
            cycles += 1;
        }
        Long address = state.getDirectMemoryAccess(lowByte).readLong();
        MemoryAccess access = state.getMemoryAccess(address);
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " [$" + Type::operandToString(state) + "]";
    }
};

// Direct Page Indirect Long Indexed, Y
// [dp],Y
template <typename Operator>
struct DirectPageIndirectLongIndexedY
{
    using Type = Instruction2Byte;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "DirectPageIndirectLongIndexedY");

        int cycles = 0;
        if ((Byte)state.getDirectPageRegister())
        {
            cycles += 1;
        }
        Long address = state.getDirectMemoryAccess(lowByte).readLong();
        MemoryAccess access = state.getMemoryAccess(address, state.getIndexRegister<State::IndexRegister::Y>());
        return cycles + Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " [$" + Type::operandToString(state) + "], Y";
    }
};

// Immediate
// #const
template <typename Operator>
struct Immediate
{
    using Type = Instruction2Byte;

    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "Immediate");

        Memory<Byte> memory(1);
        memory.createLocation<ReadOnlyMemory>(0, lowByte);
        MemoryAccess<Memory<Byte>> access(memory, 0);
        return Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " #$" + Type::operandToString(state);
    }
};

// Immediate
// #const
template <typename Operator>
struct Immediate16Bit
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "Immediate16Bit");

        Memory<Byte> memory(2);
        memory.createLocation<ReadOnlyMemory>(0, lowByte);
        memory.createLocation<ReadOnlyMemory>(1, highByte);
        MemoryAccess access(memory, 0);
        return Operator::invoke16Bit(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " #$" + Type::operandToString(state);
    }
};

// Implied
template <typename Operator>
struct Implied
{
    using Type = Instruction1Byte;

    static int invokeOperator(State& state)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "Implied");

        return Operator::invoke(state);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString();
    }
};

// Program Counter Relative
// nearlabel
template <typename Operator>
struct ProgramCounterRelative
{
    using Type = Instruction2Byte;

    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "ProgramCounterRelative");

        return Operator::invoke(state, (int8_t)lowByte);
    }

    static std::string toString(const State& state)
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.getProgramCounter(int((int8_t)Type::size() + (int8_t)state.inspectProgramByte(1)));
        return ss.str();
    }
};

// Program Counter Relative Long
// label
template <typename Operator>
struct ProgramCounterRelativeLong
{
    using Type = Instruction3Byte;

    static int invokeOperator(State& state, Byte lowByte, Byte highByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "ProgramCounterRelativeLong");

        return Operator::invoke(state, int16_t(highByte << 8 | lowByte));
    }

    static std::string toString(const State& state)
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.getProgramCounter(int((int8_t)Type::size() + int16_t(state.inspectProgramByte(2) << 8 | state.inspectProgramByte(1))));
        return ss.str();
    }
};

// Stack Relative
// sr,S
template <typename Operator>
struct StackRelative
{
    using Type = Instruction2Byte;

    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "StackRelative");

        MemoryAccess access = state.getMemoryAccess<State::MemoryType::WrappingMask::Bank>(Long(state.getStackPointer() + lowByte, 0));
        return Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " $" + Type::operandToString(state) + ",S";
    }
};

// Stack Relative Indirect Indexed, Y
// (sr,S),Y
template <typename Operator>
struct StackRelativeIndirectIndexedY
{
    using Type = Instruction2Byte;

    static int invokeOperator(State& state, Byte lowByte)
    {
        PROFILE_IF(PROFILE_ADDRESS_MODES, "StackRelativeIndirectIndexedY");

        Word address = state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(Long(state.getStackPointer() + lowByte, 0));
        MemoryAccess access = state.getMemoryAccess(Long(address, state.getDataBank()), state.getIndexRegister<State::IndexRegister::Y>());
        return Operator::invoke(state, access);
    }

    static std::string toString(const State& state)
    {
        return Operator::toString() + " ($" + Type::operandToString(state) + ",S), Y";
    }
};

}

}