#pragma once

#include <stdint.h>

#include "State.h"
#include "Instruction.h"

namespace AddressMode {

// Absolute
template <typename Operator>
class Absolute : public Instruction3Byte
{
    using Absolute::Absolute;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int Absolute<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Absolute Indexed Indirect
template <typename Operator>
class AbsoluteIndexedIndirect : public Instruction3Byte
{
    using AbsoluteIndexedIndirect::AbsoluteIndexedIndirect;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int AbsoluteIndexedIndirect<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Absolute Indexed, X
template <typename Operator>
class AbsoluteIndexedX : public Instruction3Byte
{
    using AbsoluteIndexedX::AbsoluteIndexedX;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int AbsoluteIndexedX<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Absolute Indexed, Y
template <typename Operator>
class AbsoluteIndexedY : public Instruction3Byte
{
    using AbsoluteIndexedY::AbsoluteIndexedY;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int AbsoluteIndexedY<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Absolute Indirect
template <typename Operator>
class AbsoluteIndirect : public Instruction3Byte
{
    using AbsoluteIndirect::AbsoluteIndirect;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int AbsoluteIndirect<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Absolute Indirect Long
template <typename Operator>
class AbsoluteIndirectLong : public Instruction3Byte
{
    using AbsoluteIndirectLong::AbsoluteIndirectLong;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int AbsoluteIndirectLong<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Absolute Long
template <typename Operator>
class AbsoluteLong : public Instruction4Byte
{
    using AbsoluteLong::AbsoluteLong;
    int apply(State& state, uint32_t value) const override;
};

template <typename Operator>
int AbsoluteLong<Operator>::apply(State& state, uint32_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Absolute Long Indexed, X
template <typename Operator>
class AbsoluteLongIndexedX : public Instruction4Byte
{
    using AbsoluteLongIndexedX::AbsoluteLongIndexedX;
    int apply(State& state, uint32_t value) const override;
};

template <typename Operator>
int AbsoluteLongIndexedX<Operator>::apply(State& state, uint32_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Accumulator
template <typename Operator>
class Accumulator : public Instruction1Byte
{
    using Accumulator::Accumulator;
    int apply(State& state) const override;
};

template <typename Operator>
int Accumulator<Operator>::apply(State& state) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Block Move
template <typename Operator>
class BlockMove : public Instruction3Byte
{
    using BlockMove::BlockMove;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int BlockMove<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page
template <typename Operator>
class DirectPage : public Instruction2Byte
{
    using DirectPage::DirectPage;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPage<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page Indexed Indirect, X
template <typename Operator>
class DirectPageIndexedIndirectX : public Instruction2Byte
{
    using DirectPageIndexedIndirectX::DirectPageIndexedIndirectX;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPageIndexedIndirectX<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page Indexed, X
template <typename Operator>
class DirectPageIndexedX : public Instruction2Byte
{
    using DirectPageIndexedX::DirectPageIndexedX;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPageIndexedX<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page Indexed, Y
template <typename Operator>
class DirectPageIndexedY : public Instruction2Byte
{
    using DirectPageIndexedY::DirectPageIndexedY;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPageIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page Indirect
template <typename Operator>
class DirectPageIndirect : public Instruction2Byte
{
    using DirectPageIndirect::DirectPageIndirect;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPageIndirect<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page Indirect Indexed, Y
template <typename Operator>
class DirectPageIndirectIndexedY : public Instruction2Byte
{
    using DirectPageIndirectIndexedY::DirectPageIndirectIndexedY;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPageIndirectIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page Indirect Long
template <typename Operator>
class DirectPageIndirectLong : public Instruction2Byte
{
    using DirectPageIndirectLong::DirectPageIndirectLong;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPageIndirectLong<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Direct Page Indirect Long Indexed, Y
template <typename Operator>
class DirectPageIndirectLongIndexedY : public Instruction2Byte
{
    using DirectPageIndirectLongIndexedY::DirectPageIndirectLongIndexedY;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int DirectPageIndirectLongIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Immediate
template <typename Operator>
class Immediate : public Instruction2Byte
{
    using Immediate::Immediate;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int Immediate<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
template <typename Operator, State::Flag Flag>
class ImmediateFlagSize : public InstructionFlagSize<Flag>
{
    using ImmediateFlagSize::ImmediateFlagSize;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator, State::Flag Flag>
int ImmediateFlagSize<Operator, Flag>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Implied
template <typename Operator>
class Implied : public Instruction1Byte
{
    using Implied::Implied;
    int apply(State& state) const override;
};

template <typename Operator>
int Implied<Operator>::apply(State& state) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Program Counter Relative
template <typename Operator>
class ProgramCounterRelative : public Instruction2Byte
{
    using ProgramCounterRelative::ProgramCounterRelative;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int ProgramCounterRelative<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Program Counter Relative Long
template <typename Operator>
class ProgramCounterRelativeLong : public Instruction3Byte
{
    using ProgramCounterRelativeLong::ProgramCounterRelativeLong;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int ProgramCounterRelativeLong<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (Absolute)
template <typename Operator>
class StackAbsolute : public Instruction3Byte
{
    using StackAbsolute::StackAbsolute;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int StackAbsolute<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (Direct Page Indirect)
template <typename Operator>
class StackDirectPageIndirect : public Instruction2Byte
{
    using StackDirectPageIndirect::StackDirectPageIndirect;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int StackDirectPageIndirect<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack/Interrupt
template <typename Operator>
class StackInterrupt : public Instruction2Byte
{
    using StackInterrupt::StackInterrupt;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int StackInterrupt<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (Program Counter Relative Long)
template <typename Operator>
class StackProgramCounterRelativeLong : public Instruction3Byte
{
    using StackProgramCounterRelativeLong::StackProgramCounterRelativeLong;
    int apply(State& state, uint16_t value) const override;
};

template <typename Operator>
int StackProgramCounterRelativeLong<Operator>::apply(State& state, uint16_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (Pull)
template <typename Operator>
class StackPull : public Instruction1Byte
{
    using StackPull::StackPull;
    int apply(State& state) const override;
};

template <typename Operator>
int StackPull<Operator>::apply(State& state) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (Push)
template <typename Operator>
class StackPush : public Instruction1Byte
{
    using StackPush::StackPush;
    int apply(State& state) const override;
};

template <typename Operator>
int StackPush<Operator>::apply(State& state) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (RTI)
template <typename Operator>
class StackRTI : public Instruction1Byte
{
    using StackRTI::StackRTI;
    int apply(State& state) const override;
};

template <typename Operator>
int StackRTI<Operator>::apply(State& state) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (RTL)
template <typename Operator>
class StackRTL : public Instruction1Byte
{
    using StackRTL::StackRTL;
    int apply(State& state) const override;
};

template <typename Operator>
int StackRTL<Operator>::apply(State& state) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack (RTS)
template <typename Operator>
class StackRTS : public Instruction1Byte
{
    using StackRTS::StackRTS;
    int apply(State& state) const override;
};

template <typename Operator>
int StackRTS<Operator>::apply(State& state) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack Relative
template <typename Operator>
class StackRelative : public Instruction2Byte
{
    using StackRelative::StackRelative;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int StackRelative<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// Stack Relative Indirect Indexed, Y
template <typename Operator>
class StackRelativeIndirectIndexedY : public Instruction2Byte
{
    using StackRelativeIndirectIndexedY::StackRelativeIndirectIndexedY;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int StackRelativeIndirectIndexedY<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

// n/a
template <typename Operator>
class na : public Instruction2Byte
{
    using na::na;
    int apply(State& state, uint8_t value) const override;
};

template <typename Operator>
int na<Operator>::apply(State& state, uint8_t value) const
{
    int data = 0;
    return Operator::operate(state, &data);
}

}
