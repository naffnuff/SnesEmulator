#pragma once

#include <stdint.h>

#include "State.h"
#include "Instruction.h"

namespace AddressMode {

// Absolute
template <typename Operator>
class Absolute : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string Absolute<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int Absolute<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Absolute Indexed Indirect
template <typename Operator>
class AbsoluteIndexedIndirect : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string AbsoluteIndexedIndirect<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int AbsoluteIndexedIndirect<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Absolute Indexed, X
template <typename Operator>
class AbsoluteIndexedX : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string AbsoluteIndexedX<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int AbsoluteIndexedX<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Absolute Indexed, Y
template <typename Operator>
class AbsoluteIndexedY : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string AbsoluteIndexedY<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int AbsoluteIndexedY<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Absolute Indirect
template <typename Operator>
class AbsoluteIndirect : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string AbsoluteIndirect<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int AbsoluteIndirect<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Absolute Indirect Long
template <typename Operator>
class AbsoluteIndirectLong : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string AbsoluteIndirectLong<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int AbsoluteIndirectLong<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Absolute Long
template <typename Operator>
class AbsoluteLong : public Instruction4Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint32_t value) const override;
};

template <typename Operator>
std::string AbsoluteLong<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction4Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int AbsoluteLong<Operator>::apply(State& state, uint32_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Absolute Long Indexed, X
template <typename Operator>
class AbsoluteLongIndexedX : public Instruction4Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint32_t value) const override;
};

template <typename Operator>
std::string AbsoluteLongIndexedX<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction4Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int AbsoluteLongIndexedX<Operator>::apply(State& state, uint32_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Accumulator
template <typename Operator>
class Accumulator : public Instruction1Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state) const override;
};

template <typename Operator>
std::string Accumulator<Operator>::toString(const State& state) const
{
    return Operator::toString() + " TODO";
}

template <typename Operator>
int Accumulator<Operator>::apply(State& state) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Block Move
template <typename Operator>
class BlockMove : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string BlockMove<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int BlockMove<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page
template <typename Operator>
class DirectPage : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPage<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPage<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page Indexed Indirect, X
template <typename Operator>
class DirectPageIndexedIndirectX : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPageIndexedIndirectX<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPageIndexedIndirectX<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page Indexed, X
template <typename Operator>
class DirectPageIndexedX : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPageIndexedX<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPageIndexedX<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page Indexed, Y
template <typename Operator>
class DirectPageIndexedY : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPageIndexedY<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPageIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page Indirect
template <typename Operator>
class DirectPageIndirect : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPageIndirect<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPageIndirect<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page Indirect Indexed, Y
template <typename Operator>
class DirectPageIndirectIndexedY : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPageIndirectIndexedY<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPageIndirectIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page Indirect Long
template <typename Operator>
class DirectPageIndirectLong : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPageIndirectLong<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPageIndirectLong<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Direct Page Indirect Long Indexed, Y
template <typename Operator>
class DirectPageIndirectLongIndexedY : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string DirectPageIndirectLongIndexedY<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int DirectPageIndirectLongIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Immediate
template <typename Operator>
class Immediate : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string Immediate<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int Immediate<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
template <typename Operator, State::Flag Flag>
class ImmediateFlagSize : public InstructionFlagSize<Flag>
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator, State::Flag Flag>
std::string ImmediateFlagSize<Operator, Flag>::toString(const State& state) const
{
    return Operator::toString() + " $" + InstructionFlagSize<Flag>::operandToString(state) + " TODO";
}

template <typename Operator, State::Flag Flag>
int ImmediateFlagSize<Operator, Flag>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Implied
template <typename Operator>
class Implied : public Instruction1Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state) const override;
};

template <typename Operator>
std::string Implied<Operator>::toString(const State& state) const
{
    return Operator::toString() + " TODO";
}

template <typename Operator>
int Implied<Operator>::apply(State& state) const
{
    return Operator::operate(state);
}

// Program Counter Relative
template <typename Operator>
class ProgramCounterRelative : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string ProgramCounterRelative<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int ProgramCounterRelative<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Program Counter Relative Long
template <typename Operator>
class ProgramCounterRelativeLong : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string ProgramCounterRelativeLong<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int ProgramCounterRelativeLong<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (Absolute)
template <typename Operator>
class StackAbsolute : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string StackAbsolute<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int StackAbsolute<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (Direct Page Indirect)
template <typename Operator>
class StackDirectPageIndirect : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string StackDirectPageIndirect<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int StackDirectPageIndirect<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack/Interrupt
template <typename Operator>
class StackInterrupt : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string StackInterrupt<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int StackInterrupt<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (Program Counter Relative Long)
template <typename Operator>
class StackProgramCounterRelativeLong : public Instruction3Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
std::string StackProgramCounterRelativeLong<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction3Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int StackProgramCounterRelativeLong<Operator>::apply(State& state, uint16_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (Pull)
template <typename Operator>
class StackPull : public Instruction1Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state) const override;
};

template <typename Operator>
std::string StackPull<Operator>::toString(const State& state) const
{
    return Operator::toString() + " TODO";
}

template <typename Operator>
int StackPull<Operator>::apply(State& state) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (Push)
template <typename Operator>
class StackPush : public Instruction1Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state) const override;
};

template <typename Operator>
std::string StackPush<Operator>::toString(const State& state) const
{
    return Operator::toString() + " TODO";
}

template <typename Operator>
int StackPush<Operator>::apply(State& state) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (RTI)
template <typename Operator>
class StackRTI : public Instruction1Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state) const override;
};

template <typename Operator>
std::string StackRTI<Operator>::toString(const State& state) const
{
    return Operator::toString() + " TODO";
}

template <typename Operator>
int StackRTI<Operator>::apply(State& state) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (RTL)
template <typename Operator>
class StackRTL : public Instruction1Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state) const override;
};

template <typename Operator>
std::string StackRTL<Operator>::toString(const State& state) const
{
    return Operator::toString() + " TODO";
}

template <typename Operator>
int StackRTL<Operator>::apply(State& state) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack (RTS)
template <typename Operator>
class StackRTS : public Instruction1Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state) const override;
};

template <typename Operator>
std::string StackRTS<Operator>::toString(const State& state) const
{
    return Operator::toString() + " TODO";
}

template <typename Operator>
int StackRTS<Operator>::apply(State& state) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack Relative
template <typename Operator>
class StackRelative : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string StackRelative<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int StackRelative<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// Stack Relative Indirect Indexed, Y
template <typename Operator>
class StackRelativeIndirectIndexedY : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string StackRelativeIndirectIndexedY<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int StackRelativeIndirectIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

// n/a
template <typename Operator>
class na : public Instruction2Byte
{
    std::string toString(const State& state) const override;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
std::string na<Operator>::toString(const State& state) const
{
    return Operator::toString() + " $" + Instruction2Byte::operandToString(state) + " TODO";
}

template <typename Operator>
int na<Operator>::apply(State& state, uint8_t value) const
{
    int* dataAddress = nullptr;
    return Operator::operate(state, dataAddress);
}

}
