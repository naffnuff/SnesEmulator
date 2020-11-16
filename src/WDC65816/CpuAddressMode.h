#pragma once

#include "Exception.h"
#include "Instruction.h"
#include "Memory.h"
#include "CpuState.h"

#pragma warning( disable : 4702 ) // unreachable code

namespace CPU {

typedef InstructionBase<State> Instruction1Byte;
typedef InstructionBase<State, Byte> Instruction2Byte;
typedef InstructionBase<State, Byte, Byte> Instruction3Byte;
typedef InstructionBase<State, Byte, Byte, Byte> Instruction4Byte;

namespace AddressMode {

EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)

// Absolute
// addr
template <typename Operator>
class Absolute : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        MemoryAccess access = state.getMemoryAccess(lowByte, highByte);
        return Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

template <typename Operator>
class Absolute_ControlFlow : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, Word(lowByte, highByte));
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

// Absolute Indexed Indirect
// (addr,X)
template <typename Operator>
class AbsoluteIndexedIndirect : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        Word indexedAddress = Word(lowByte, highByte) + state.getIndexRegister<State::IndexRegister::X>();
        Long longAddress(indexedAddress, state.getProgramBank());
        return Operator::invoke(state, state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(longAddress));
    }

    std::string toString() const override
    {
        return Operator::toString() + " ($" + operandToString() + ",X)";
    }
};

// Absolute Indexed, X/Y
// addr,X/Y
template <typename Operator, State::IndexRegister Register>
class AbsoluteIndexed : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        Long staticAddress(lowByte, highByte, state.getDataBank());
        Long indexedAddress = staticAddress + state.getIndexRegister<Register>();
        MemoryAccess access = state.getMemoryAccess(indexedAddress);
        return getCycles(staticAddress, indexedAddress) + Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + "," + state.getIndexRegisterName<Register>();
    }

    virtual int getCycles(Long, Long) const
    {
        return 0;
    }
};

template <typename Operator, State::IndexRegister Register>
class AbsoluteIndexed_ExtraCycle : public AbsoluteIndexed<Operator, Register>
{
    using AbsoluteIndexed<Operator, Register>::AbsoluteIndexed;

    // §3: Add 1 cycle if adding index crosses a page boundary
    int getCycles(Long staticAddress, Long indexedAddress) const override
    {
        int cycles = 0;
        Word addressPage(staticAddress >> 8);
        Word indexedAddressPage(indexedAddress >> 8);
        if (addressPage != indexedAddressPage) {
            cycles += 1;
        }
        return cycles;
    }
};

// Absolute Indirect
// (addr)
template <typename Operator>
class AbsoluteIndirect : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(Long(lowByte, highByte, 0)));
    }

    std::string toString() const override
    {
        return Operator::toString() + " ($" + operandToString() + ")";
    }
};

// Absolute Indirect Long
// [addr]
template <typename Operator>
class AbsoluteIndirectLong : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, state.readMemoryLong<State::MemoryType::WrappingMask::Bank>(Long(lowByte, highByte, 0)));
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

// Absolute Long
// long
template <typename Operator>
class AbsoluteLong : public Instruction4Byte
{
    using Instruction4Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte, Byte bankByte) override
    {
        MemoryAccess access = state.getMemoryAccess(lowByte, highByte, bankByte);
        return Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

template <typename Operator>
class AbsoluteLong_ControlFlow : public Instruction4Byte
{
    using Instruction4Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte, Byte bankByte) override
    {
        return Operator::invoke(state, Long(lowByte, highByte, bankByte));
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

// Absolute Long Indexed, X
// long,X
template <typename Operator>
class AbsoluteLongIndexedX : public Instruction4Byte
{
    using Instruction4Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte, Byte bankByte) override
    {
        MemoryAccess access = state.getMemoryAccess(lowByte, highByte, bankByte, state.getIndexRegister<State::IndexRegister::X>());
        return Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + ",X";
    }
};

// Accumulator
// A
template <typename Operator>
class Accumulator : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    // §21: Remove 2 cycles for the special case of Accumulator
    int invokeOperator() override
    {
        int cycles = 0;
        if (state.is16Bit(State::Flag::m)) {
            cycles -= 2;
        }
        State::AccumulatorAccess accumulatorAccess = state.getAccumulatorAccess();
        return cycles + Operator::invoke(state, accumulatorAccess);
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
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        Word byteCount = state.getAccumulatorC();
        if (byteCount != 0) {
            state.incrementProgramCounter(Word(-size()));
        }
        state.setAccumulatorC(byteCount - 1);
        return Operator::invoke(state, highByte, lowByte, byteCount);
    }

    std::string toString() const override
    {
        std::string operands = operandToString();
        return Operator::toString() + " $" + operands.substr(0, 2) + ",$" + operands.substr(2, 2);
    }
};

// Direct Page
// dp
template <typename Operator>
class DirectPage : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if (state.getDirectPageRegister().getLowByte() != 0) {
            cycles += 1;
        }
        MemoryAccess access = state.getDirectMemoryAccess(lowByte);
        return cycles + Operator::invoke(state, access);
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
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        throw NotYetImplementedException("DirectPageIndexedIndirectX");
        int cycles = 0;
        if ((Byte)state.getDirectPageRegister()) {
            cycles += 1;
        }
        MemoryAccess access = state.getMemoryAccess(0, 0, 0, 0);
        return cycles + Operator::invoke(state, access);
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
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if (Byte(state.getDirectPageRegister())) {
            cycles += 1;
        }
        MemoryAccess access = state.getDirectMemoryAccess(lowByte, state.getIndexRegister<Register>());
        return cycles + Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + "," + State::getIndexRegisterName<Register>();
    }
};

// Direct Page Indirect
// (dp)
template <typename Operator>
class DirectPageIndirect : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((Byte)state.getDirectPageRegister()) {
            cycles += 1;
        }
        Long address(state.getDirectMemoryAccess(lowByte).readWord(), state.getDataBank());
        MemoryAccess access = state.getMemoryAccess(address);
        return cycles + Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " ($" + operandToString() + ")";
    }
};

// Direct Page Indirect
// (dp)
template <typename Operator>
class DirectPageIndirect_ControlFlow : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((Byte)state.getDirectPageRegister()) {
            cycles += 1;
        }
        Word address = state.getDirectMemoryAccess(lowByte).readWord();
        return cycles + Operator::invoke(state, address);
    }

    std::string toString() const override
    {
        return Operator::toString() + " ($" + operandToString() + ")";
    }
};

// Direct Page Indirect Indexed, Y
// (dp),Y
template <typename Operator>
class DirectPageIndirectIndexedY : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    // §3: Add 1 cycle if adding index crosses a page boundary
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((Byte)state.getDirectPageRegister()) {
            cycles += 1;
        }
        Long address(state.getDirectMemoryAccess(lowByte).readWord(), state.getDataBank());
        Long indexedAddress = address + state.getIndexRegister<State::IndexRegister::Y>();
        if (address >> 8 != indexedAddress >> 8) {
            cycles += 1;
        }
        MemoryAccess access = state.getMemoryAccess(indexedAddress);
        return cycles + Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " ($" + operandToString() + "),Y";
    }
};

// Direct Page Indirect Long
// [dp]
template <typename Operator>
class DirectPageIndirectLong : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((Byte)state.getDirectPageRegister()) {
            cycles += 1;
        }
        Long address = state.getDirectMemoryAccess(lowByte).readLong();
        MemoryAccess access = state.getMemoryAccess(address);
        return cycles + Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " [$" + operandToString() + "]";
    }
};

// Direct Page Indirect Long Indexed, Y
// [dp],Y
template <typename Operator>
class DirectPageIndirectLongIndexedY : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((Byte)state.getDirectPageRegister()) {
            cycles += 1;
        }
        Long address = state.getDirectMemoryAccess(lowByte).readLong();
        MemoryAccess access = state.getMemoryAccess(address, state.getIndexRegister<State::IndexRegister::Y>());
        return cycles + Operator::invoke(state, access);
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
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        Memory<Byte> memory(1);
        memory.createLocation<ReadOnlyMemory>(0, lowByte);
        MemoryAccess<Memory<Byte>> access(memory, 0);
        return Operator::invoke(state, access);
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
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        Memory<Byte> memory(2);
        memory.createLocation<ReadOnlyMemory>(0, lowByte);
        memory.createLocation<ReadOnlyMemory>(1, highByte);
        MemoryAccess access(memory, 0);
        return Operator::invoke(state, access);
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
    using Instruction1Byte::InstructionBase;

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
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, (int8_t)lowByte);
    }

    std::string toString() const override
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.inspectProgramByte(1)));
        return ss.str();
    }
};

// Program Counter Relative Long
// label
template <typename Operator>
class ProgramCounterRelativeLong : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, int16_t(highByte << 8 | lowByte));
    }

    std::string toString() const override
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.getProgramCounter(int((int8_t)size() + int16_t(state.inspectProgramByte(2) << 8 | state.inspectProgramByte(1))));
        return ss.str();
    }
};

// Stack Relative
// sr,S
template <typename Operator>
class StackRelative : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        MemoryAccess access = state.getMemoryAccess<State::MemoryType::WrappingMask::Bank>(Long(state.getStackPointer() + lowByte, 0));
        return Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + ",S";
    }
};

// Stack Relative Indirect Indexed, Y
// (sr,S),Y
template <typename Operator>
class StackRelativeIndirectIndexedY : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        Word address = state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(Long(state.getStackPointer() + lowByte, 0));
        MemoryAccess access = state.getMemoryAccess(Long(address, state.getDataBank()), state.getIndexRegister<State::IndexRegister::Y>());
        return Operator::invoke(state, access);
    }

    std::string toString() const override
    {
        return Operator::toString() + " ($" + operandToString() + ",S), Y";
    }
};

}

}