#pragma once

#include "Exception.h"
#include "Instruction.h"
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
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, state.getMemoryLocation(lowByte, highByte));
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
        Long address = Long(lowByte, highByte, state.getDataBank());
        Long indexedAddress = address + state.getIndexRegister<State::X>();
        MemoryLocation* memory = state.getMemoryLocation(indexedAddress);
        return Operator::invoke(state, memory->getWordValue());
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
        Long address = Long(lowByte, highByte, state.getDataBank());
        Long indexedAddress = address + state.getIndexRegister<Register>();
        MemoryLocation* memory = state.getMemoryLocation(indexedAddress);
        return getCycles(address, indexedAddress) + Operator::invoke(state, memory);
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
    int getCycles(Long address, Long indexedAddress) const override
    {
        int cycles = 0;
        Word addressPage = address >> 8;
        Word indexedAddressPage = indexedAddress >> 8;
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
        throw AddressModeNotYetImplementedException("AbsoluteIndirect");
        return Operator::invoke(state, Word());
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
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        MemoryLocation* memory = state.getMemoryLocation(lowByte, highByte);
        return Operator::invoke(state, Long(memory[0].getWordValue(), memory[2].getValue()));
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
        return Operator::invoke(state, state.getMemoryLocation(lowByte, highByte, bankByte));
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
        Long address = Long(lowByte, highByte, bankByte);
        Long indexedAddress = address + state.getIndexRegister<State::X>();
        MemoryLocation* memory = state.getMemoryLocation(indexedAddress);
        return Operator::invoke(state, memory);
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
        if (state.is16Bit(State::m)) {
            cycles -= 2;
        }
        return cycles + Operator::invoke(state, state.getAccumulatorPointer());
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
            state.incrementProgramCounter(-size());
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
        if ((uint8_t)state.getDirectPage()) {
            cycles += 1;
        }
        return cycles + Operator::invoke(state, state.getDirectMemoryLocation(lowByte));
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
        throw AddressModeNotYetImplementedException("DirectPageIndexedIndirectX");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        MemoryLocation* memory = nullptr;
        return cycles + Operator::invoke(state, memory);
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
        if (Byte(state.getDirectPage())) {
            cycles += 1;
        }
        MemoryLocation* memory = state.getDirectMemoryLocation(lowByte, state.getIndexRegister<Register>());
        return cycles + Operator::invoke(state, memory);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + ",X";
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
        throw AddressModeNotYetImplementedException("DirectPageIndirect");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        MemoryLocation* memory = nullptr;
        return cycles + Operator::invoke(state, memory);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Page Indirect
// (dp)
template <typename Operator>
class DirectPageIndirect_NewInstruction : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("DirectPageIndirect_NewInstruction");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        MemoryLocation* memory = nullptr;
        return cycles + Operator::invoke(state, memory);
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
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    // §3: Add 1 cycle if adding index crosses a page boundary
    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("DirectPageIndirectIndexedY");
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        if (true /*index added crosses page boundary*/) {
            cycles += 1;
            throw AddressModeNotYetImplementedException("TODO03");
        }
        MemoryLocation* memory = nullptr;
        return cycles + Operator::invoke(state, memory);
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
    using Instruction2Byte::InstructionBase;

    // §2: Add 1 cycle if low byte of Direct Page Register is non-zero
    int invokeOperator(Byte lowByte) override
    {
        int cycles = 0;
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        MemoryLocation* directMemory = state.getDirectMemoryLocation(lowByte);
        Long effectiveAddress(directMemory[0].getWordValue(), directMemory[2].getValue());
        return cycles + Operator::invoke(state, state.getMemoryLocation(effectiveAddress));
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
        if ((Byte)state.getDirectPage()) {
            cycles += 1;
        }
        MemoryLocation* address = state.getDirectMemoryLocation(lowByte);
        MemoryLocation* memory = state.getMemoryLocation(address[0].getValue(), address[1].getValue(), address[2].getValue(), state.getIndexRegister<State::Y>());
        return cycles + Operator::invoke(state, memory);
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
        MemoryLocation memory;
        memory.setReadOnlyValue(lowByte);
        return Operator::invoke(state, &memory);
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
        std::array<MemoryLocation, 2> memory;
        memory[0].setReadOnlyValue(lowByte);
        memory[1].setReadOnlyValue(highByte);
        return Operator::invoke(state, memory.data());
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
        ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.readProgramByte(1)));
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
        throw AddressModeNotYetImplementedException("ProgramCounterRelativeLong");
        MemoryLocation* memory = nullptr;
        return Operator::invoke(state, memory);
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
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("StackRelative");
        MemoryLocation* memory = nullptr;
        return Operator::invoke(state, memory);
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
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("StackRelativeIndirectIndexedY");
        MemoryLocation* memory = nullptr;
        return Operator::invoke(state, memory);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

}

}