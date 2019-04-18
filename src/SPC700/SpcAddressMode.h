#pragma once

#include "Exception.h"
#include "Instruction.h"
#include "SpcState.h"

namespace SPC {

typedef InstructionBase<State> Instruction1Byte;
typedef InstructionBase<State, Byte> Instruction2Byte;
typedef InstructionBase<State, Byte, Byte> Instruction3Byte;

namespace AddressMode {

// Absolute
// ASL !a:     	Left shift (a) as above    	[N.....ZC]
// DEC !a:     	(a)--    	[N.....Z.]
// INC !a:     	(a)++    	[N.....Z.]
// LSR !a:     	Right shift (a) as above    	[N.....ZC]
// ROL !a:     	Left shift (a) as above    	[N.....ZC]
// ROR !a:     	Right shift (a) as above    	[N.....ZC]
// TCLR1 !a:     	(a) = (a)&~A, ZN as for A-(a)    	[N.....Z.]
// TSET1 !a:     	(a) = (a)|A, ZN as for A-(a)    	[N.....Z.]
template <typename Operator>
class Absolute : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("Absolute");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

// CALL !a:     	(SP--)=PCh, (SP--)=PCl, PC=a    	[........]
// JMP !a:     	PC = a    	[........]
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
// JMP [!a+X]:     	PC = [a+X]    	[........]
template <typename Operator, State::Register RegisterIndex>
class AbsoluteIndexedIndirect : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        Word address(lowByte, highByte);
        address += Word(state.getRegisterValue<State::X>());
        return Operator::invoke(state, state.getMemoryWord(address));
    }

    std::string toString() const override
    {
        return Operator::toString() + " [$" + operandToString() + "+X]";
    }
};

// Absolute Indexed Register
// MOV !a+X, A:     	(a+X) = A      (read)    	[........]
// MOV !a+Y, A:     	(a+Y) = A      (read)    	[........]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class AbsoluteIndexedRegister : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        MemoryLocation* memory = state.getMemoryLocation(Word(Word(lowByte, highByte) + state.getRegisterValue<FirstRegister>()));
        return Operator::invoke(state, memory, state.getRegisterValue<SecondRegister>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + "+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();
    }
};

// Absolute Register
// MOV !a, A:     	(a) = A        (read)    	[........]
// MOV !a, X:     	(a) = X        (read)    	[........]
// MOV !a, Y:     	(a) = Y        (read)    	[........]
template <typename Operator, State::Register RegisterIndex>
class AbsoluteRegister : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, state.getMemoryLocation(lowByte, highByte), state.getRegisterValue<RegisterIndex>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + ", " + State::getRegisterName<RegisterIndex>();
    }
};

// Carry Memory Bit
// AND1 C, m.b:     	C = C & (m.b)    	[.......C]
// EOR1 C, m.b:     	C = C EOR (m.b)    	[.......C]
// MOV1 C, m.b:     	C = (m.b)    	[.......C]
// OR1 C, m.b:     	C = C | (m.b)    	[.......C]
template <typename Operator>
class CarryMemoryBit : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("CarryMemoryBit");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Carry Negated Memory Bit
// AND1 C, /m.b:     	C = C & ~(m.b)    	[.......C]
// OR1 C, /m.b:     	C = C | ~(m.b)    	[.......C]
template <typename Operator>
class CarryNegatedMemoryBit : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("CarryNegatedMemoryBit");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct
// ASL d:     	Left shift (d) as above    	[N.....ZC]
// DEC d:     	(d)--    	[N.....Z.]
// DECW d:     	Word (d)--    	[N.....Z.]
// INC d:     	(d)++    	[N.....Z.]
// INCW d:     	Word (d)++    	[N.....Z.]
// LSR d:     	Right shift (d) as above    	[N.....ZC]
// ROL d:     	Left shift (d) as above    	[N.....ZC]
// ROR d:     	Right shift (d) as above    	[N.....ZC]
// CLR1 d.0:     	d.0 = 0    	[........]
// CLR1 d.1:     	d.1 = 0    	[........]
// CLR1 d.2:     	d.2 = 0    	[........]
// CLR1 d.3:     	d.3 = 0    	[........]
// CLR1 d.4:     	d.4 = 0    	[........]
// CLR1 d.5:     	d.5 = 0    	[........]
// CLR1 d.6:     	d.6 = 0    	[........]
// CLR1 d.7:     	d.7 = 0    	[........]
// SET1 d.0:     	d.0 = 1    	[........]
// SET1 d.1:     	d.1 = 1    	[........]
// SET1 d.2:     	d.2 = 1    	[........]
// SET1 d.3:     	d.3 = 1    	[........]
// SET1 d.4:     	d.4 = 1    	[........]
// SET1 d.5:     	d.5 = 1    	[........]
// SET1 d.6:     	d.6 = 1    	[........]
// SET1 d.7:     	d.7 = 1    	[........]
template <typename Operator>
class Direct : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, state.getDirectMemoryLocation(lowByte));
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString();
    }
};

// Direct Bit Program Counter Relative
// BBC d.0, r:     	PC+=r  if d.0 == 0    	[........]
// BBC d.1, r:     	PC+=r  if d.1 == 0    	[........]
// BBC d.2, r:     	PC+=r  if d.2 == 0    	[........]
// BBC d.3, r:     	PC+=r  if d.3 == 0    	[........]
// BBC d.4, r:     	PC+=r  if d.4 == 0    	[........]
// BBC d.5, r:     	PC+=r  if d.5 == 0    	[........]
// BBC d.6, r:     	PC+=r  if d.6 == 0    	[........]
// BBC d.7, r:     	PC+=r  if d.7 == 0    	[........]
// BBS d.0, r:     	PC+=r  if d.0 == 1    	[........]
// BBS d.1, r:     	PC+=r  if d.1 == 1    	[........]
// BBS d.2, r:     	PC+=r  if d.2 == 1    	[........]
// BBS d.3, r:     	PC+=r  if d.3 == 1    	[........]
// BBS d.4, r:     	PC+=r  if d.4 == 1    	[........]
// BBS d.5, r:     	PC+=r  if d.5 == 1    	[........]
// BBS d.6, r:     	PC+=r  if d.6 == 1    	[........]
// BBS d.7, r:     	PC+=r  if d.7 == 1    	[........]
template <typename Operator, int BitIndex>
class DirectBitProgramCounterRelative : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte directAddress, Byte offset) override
    {
        return Operator::invoke(state, state.getDirectMemoryByte(directAddress).getBit(BitIndex), offset);
    }

    std::string toString() const override
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.readProgramByte(1) << "." << BitIndex << ", $";
        ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.readProgramByte(2)));
        return ss.str();
    }
};

// Direct Direct
// ADC dd, ds:     	(dd) = (dd)+(d)+C    	[NV..H.ZC]
// AND dd, ds:     	(dd) = (dd) & (ds)    	[N.....Z.]
// CMP dd, ds:     	(dd) - (ds)    	[N.....ZC]
// EOR dd, ds:     	(dd) = (dd) EOR (ds)    	[N.....Z.]
// MOV dd, ds:     	(dd) = (ds)    (no read)    	[........]
// OR dd, ds:     	(dd) = (dd) | (ds)    	[N.....Z.]
// SBC dd, ds:     	(dd) = (dd)-(ds)-!C    	[NV..H.ZC]
template <typename Operator>
class DirectDirect : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("DirectDirect");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Immediate
// ADC d, #i:     	(d) = (d)+i+C    	[NV..H.ZC]
// AND d, #i:     	(d) = (d) & i    	[N.....Z.]
// CMP d, #i:     	(d) - i    	[N.....ZC]
// EOR d, #i:     	(d) = (d) EOR i    	[N.....Z.]
// MOV d, #i:     	(d) = i        (read)    	[........]
// OR d, #i:     	(d) = (d) | i    	[N.....Z.]
// SBC d, #i:     	(d) = (d)-i-!C    	[NV..H.ZC]
template <typename Operator>
class DirectImmediate : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, state.getDirectMemoryLocation(highByte), lowByte);
    }

    std::string toString() const override
    {
        std::string operand = operandToString();
        return Operator::toString() + " $" + operand.substr(0, 2) + ", #$" + operand.substr(2, 2);
    }
};

// Direct Indexed
// ASL d+X:     	Left shift (d+X) as above    	[N.....ZC]
// DEC d+X:     	(d+X)--    	[N.....Z.]
// INC d+X:     	(d+X)++    	[N.....Z.]
// LSR d+X:     	Right shift (d+X) as above    	[N.....ZC]
// ROL d+X:     	Left shift (d+X) as above    	[N.....ZC]
// ROR d+X:     	Right shift (d+X) as above    	[N.....ZC]
template <typename Operator, State::Register RegisterIndex>
class DirectIndexed : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("DirectIndexed");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed Indirect Register
// MOV [d+X], A:     	([d+X]) = A    (read)    	[........]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class DirectIndexedIndirectRegister : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("DirectIndexedIndirectRegister");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed Program Counter Relative
// CBNE d+X, r:     	CMP A, (d+X) then BNE    	[........]
template <typename Operator, State::Register RegisterIndex>
class DirectIndexedProgramCounterRelative : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("DirectIndexedProgramCounterRelative");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indexed Register
// MOV d+X, A:     	(d+X) = A      (read)    	[........]
// MOV d+X, Y:     	(d+X) = Y      (read)    	[........]
// MOV d+Y, X:     	(d+Y) = X      (read)    	[........]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class DirectIndexedRegister : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("DirectIndexedRegister");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Direct Indirect Indexed Register
// MOV [d]+Y, A:     	([d]+Y) = A    (read)    	[........]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class DirectIndirectIndexedRegister : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        Word address = state.getDirectMemoryWord(lowByte) + state.getRegisterValue<FirstRegister>();
        MemoryLocation* memory = state.getMemoryLocation(address);
        return Operator::invoke(state, memory, state.getRegisterValue<SecondRegister>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " [$" + operandToString() + "]+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();
    }
};

// Direct Program Counter Relative
// CBNE d, r:     	CMP A, (d) then BNE    	[........]
// DBNZ d, r:     	(d)-- then JNZ    	[........]
template <typename Operator>
class DirectProgramCounterRelative : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("DirectProgramCounterRelative");
        return Operator::invoke(state, state.getDirectMemoryLocation(lowByte), highByte);
    }

    std::string toString() const override
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.readProgramByte(1) << ", $";
        ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.readProgramByte(2)));
        return ss.str();
    }
};

// Direct Register
// MOV d, A:     	(d) = A        (read)    	[........]
// MOV d, X:     	(d) = X        (read)    	[........]
// MOV d, Y:     	(d) = Y        (read)    	[........]
template <typename Operator, State::Register RegisterIndex>
class DirectRegister : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, state.getDirectMemoryLocation(lowByte), state.getRegisterValue<RegisterIndex>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + ", " + State::getRegisterName<RegisterIndex>();
    }
};

// Direct Y Accumulator
// MOVW d, YA:     	word (d) = YA  (read low only)    	[........]
template <typename Operator>
class DirectYAccumulator : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, state.getDirectMemoryLocation(lowByte), state.getYAccumulator());
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + ", YA";
    }
};

// Implied
// BRK :     	Push PC and Flags, PC = [$FFDE]    	[...1.0..]
// CLRC :     	C = 0    	[.......0]
// CLRP :     	P = 0    	[..0.....]
// CLRV :     	V = 0, H = 0    	[.0..0...]
// DI :     	I = 0    	[.....0..]
// EI :     	I = 1    	[.....1..]
// NOP :     	do nothing    	[........]
// NOTC :     	C = !C    	[.......C]
// RET :     	Pop PC    	[........]
// RET1 :     	Pop Flags, PC    	[NVPBHIZC]
// SETC :     	C = 1    	[.......1]
// SETP :     	P = 1    	[..1.....]
// SLEEP :     	Halts the processor    	[........]
// STOP :     	Halts the processor    	[........]
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

// Indirect Indirect
// ADC (X), (Y):     	(X) = (X)+(Y)+C    	[NV..H.ZC]
// AND (X), (Y):     	(X) = (X) & (Y)    	[N.....Z.]
// CMP (X), (Y):     	(X) - (Y)    	[N.....ZC]
// EOR (X), (Y):     	(X) = (X) EOR (Y)    	[N.....Z.]
// OR (X), (Y):     	(X) = (X) | (Y)    	[N.....Z.]
// SBC (X), (Y):     	(X) = (X)-(Y)-!C    	[NV..H.ZC]
template <typename Operator>
class IndirectIndirect : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        throw AddressModeNotYetImplementedException("IndirectIndirect");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Memory Bit
// NOT1 m.b:     	m.b = ~m.b    	[........]
template <typename Operator>
class MemoryBit : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("MemoryBit");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Memory Bit Carry
// MOV1 m.b, C:     	(m.b) = C    	[........]
template <typename Operator>
class MemoryBitCarry : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        throw AddressModeNotYetImplementedException("MemoryBitCarry");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Program Counter Relative
// BCC r:     	PC+=r  if C == 0    	[........]
// BCS r:     	PC+=r  if C == 1    	[........]
// BEQ r:     	PC+=r  if Z == 1    	[........]
// BMI r:     	PC+=r  if N == 1    	[........]
// BNE r:     	PC+=r  if Z == 0    	[........]
// BPL r:     	PC+=r  if N == 0    	[........]
// BVC r:     	PC+=r  if V == 0    	[........]
// BVS r:     	PC+=r  if V == 1    	[........]
// BRA r:     	PC+=r    	[........]
template <typename Operator>
class ProgramCounterRelative : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, lowByte);
    }

    std::string toString() const override
    {
        std::ostringstream ss;
        ss << Operator::toString() + " $";
        ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.readProgramByte(1)));
        return ss.str();
    }
};

// Register
// ASL A:     	Left shift A: high->C, 0->low    	[N.....ZC]
// DAA A:     	decimal adjust for addition    	[N.....ZC]
// DAS A:     	decimal adjust for subtraction    	[N.....ZC]
// DEC A:     	A--    	[N.....Z.]
// DEC X:     	X--    	[N.....Z.]
// DEC Y:     	Y--    	[N.....Z.]
// INC A:     	A++    	[N.....Z.]
// INC X:     	X++    	[N.....Z.]
// INC Y:     	Y++    	[N.....Z.]
// LSR A:     	Right shift A: 0->high, low->C    	[N.....ZC]
// POP A:     	A = (++SP)    	[........]
// POP PSW:     	Flags = (++SP)    	[NVPBHIZC]
// POP X:     	X = (++SP)    	[........]
// POP Y:     	Y = (++SP)    	[........]
// PUSH A:     	(SP--) = A    	[........]
// PUSH PSW:     	(SP--) = Flags    	[........]
// PUSH X:     	(SP--) = X    	[........]
// PUSH Y:     	(SP--) = Y    	[........]
// ROL A:     	Left shift A: low=C, C=high    	[N.....ZC]
// ROR A:     	Right shift A: high=C, C=low    	[N.....ZC]
// XCN A:     	A = (A>>4) | (A<<4)    	[N.....Z.]
template <typename Operator, State::Register RegisterIndex>
class Register : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        return Operator::invoke(state, state.getRegister<RegisterIndex>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " " + State::getRegisterName<RegisterIndex>();
    }
};

// Register Absolute
// ADC A, !a:     	A = A+(a)+C    	[NV..H.ZC]
// AND A, !a:     	A = A & (a)    	[N.....Z.]
// CMP A, !a:     	A - (a)    	[N.....ZC]
// CMP X, !a:     	X - (a)    	[N.....ZC]
// CMP Y, !a:     	Y - (a)    	[N.....ZC]
// EOR A, !a:     	A = A EOR (a)    	[N.....Z.]
// MOV A, !a:     	A = (a)    	[N.....Z.]
// MOV X, !a:     	X = (a)    	[N.....Z.]
// MOV Y, !a:     	Y = (a)    	[N.....Z.]
// OR A, !a:     	A = A | (a)    	[N.....Z.]
// SBC A, !a:     	A = A-(a)-!C    	[NV..H.ZC]
template <typename Operator, State::Register RegisterIndex>
class RegisterAbsolute : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        return Operator::invoke(state, state.getRegister<RegisterIndex>(), state.getMemoryByte(lowByte, highByte));
    }

    std::string toString() const override
    {
        return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $" + operandToString();
    }
};

// Register Absolute Indexed
// ADC A, !a+X:     	A = A+(a+X)+C    	[NV..H.ZC]
// ADC A, !a+Y:     	A = A+(a+Y)+C    	[NV..H.ZC]
// AND A, !a+X:     	A = A & (a+X)    	[N.....Z.]
// AND A, !a+Y:     	A = A & (a+Y)    	[N.....Z.]
// CMP A, !a+X:     	A - (a+X)    	[N.....ZC]
// CMP A, !a+Y:     	A - (a+Y)    	[N.....ZC]
// EOR A, !a+X:     	A = A EOR (a+X)    	[N.....Z.]
// EOR A, !a+Y:     	A = A EOR (a+Y)    	[N.....Z.]
// MOV A, !a+X:     	A = (a+X)    	[N.....Z.]
// MOV A, !a+Y:     	A = (a+Y)    	[N.....Z.]
// OR A, !a+X:     	A = A | (a+X)    	[N.....Z.]
// OR A, !a+Y:     	A = A | (a+Y)    	[N.....Z.]
// SBC A, !a+X:     	A = A-(a+X)-!C    	[NV..H.ZC]
// SBC A, !a+Y:     	A = A-(a+Y)-!C    	[NV..H.ZC]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterAbsoluteIndexed : public Instruction3Byte
{
    using Instruction3Byte::InstructionBase;

    int invokeOperator(Byte lowByte, Byte highByte) override
    {
        Word address(lowByte, highByte);
        address += Word(state.getRegisterValue<SecondRegister>());
        return Operator::invoke(state, state.getRegister<FirstRegister>(), state.getMemoryByte(address));
    }

    std::string toString() const override
    {
        return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", $" + operandToString() + "+" + State::getRegisterName<SecondRegister>();
    }
};

// Register Direct
// ADC A, d:     	A = A+(d)+C    	[NV..H.ZC]
// AND A, d:     	A = A & (d)    	[N.....Z.]
// CMP A, d:     	A - (d)    	[N.....ZC]
// CMP X, d:     	X - (d)    	[N.....ZC]
// CMP Y, d:     	Y - (d)    	[N.....ZC]
// EOR A, d:     	A = A EOR (d)    	[N.....Z.]
// MOV A, d:     	A = (d)    	[N.....Z.]
// MOV X, d:     	X = (d)    	[N.....Z.]
// MOV Y, d:     	Y = (d)    	[N.....Z.]
// OR A, d:     	A = A | (d)    	[N.....Z.]
// SBC A, d:     	A = A-(d)-!C    	[NV..H.ZC]
template <typename Operator, State::Register RegisterIndex>
class RegisterDirect : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, state.getRegister<RegisterIndex>(), state.getDirectMemoryByte(lowByte));
    }

    std::string toString() const override
    {
        return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $" + operandToString();
    }
};

// Register Direct Indexed
// ADC A, d+X:     	A = A+(d+X)+C    	[NV..H.ZC]
// AND A, d+X:     	A = A & (d+X)    	[N.....Z.]
// CMP A, d+X:     	A - (d+X)    	[N.....ZC]
// EOR A, d+X:     	A = A EOR (d+X)    	[N.....Z.]
// MOV A, d+X:     	A = (d+X)    	[N.....Z.]
// MOV X, d+Y:     	X = (d+Y)    	[N.....Z.]
// MOV Y, d+X:     	Y = (d+X)    	[N.....Z.]
// OR A, d+X:     	A = A | (d+X)    	[N.....Z.]
// SBC A, d+X:     	A = A-(d+X)-!C    	[NV..H.ZC]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterDirectIndexed : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("RegisterDirectIndexed");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Register Direct Indexed Indirect
// ADC A, [d+X]:     	A = A+([d+X])+C    	[NV..H.ZC]
// AND A, [d+X]:     	A = A & ([d+X])    	[N.....Z.]
// CMP A, [d+X]:     	A - ([d+X])    	[N.....ZC]
// EOR A, [d+X]:     	A = A EOR ([d+X])    	[N.....Z.]
// MOV A, [d+X]:     	A = ([d+X])    	[N.....Z.]
// OR A, [d+X]:     	A = A | ([d+X])    	[N.....Z.]
// SBC A, [d+X]:     	A = A-([d+X])-!C    	[NV..H.ZC]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterDirectIndexedIndirect : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("RegisterDirectIndexedIndirect");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Register Direct Indirect Indexed
// ADC A, [d]+Y:     	A = A+([d]+Y)+C    	[NV..H.ZC]
// AND A, [d]+Y:     	A = A & ([d]+Y)    	[N.....Z.]
// CMP A, [d]+Y:     	A - ([d]+Y)    	[N.....ZC]
// EOR A, [d]+Y:     	A = A EOR ([d]+Y)    	[N.....Z.]
// MOV A, [d]+Y:     	A = ([d]+Y)    	[N.....Z.]
// OR A, [d]+Y:     	A = A | ([d]+Y)    	[N.....Z.]
// SBC A, [d]+Y:     	A = A-([d]+Y)-!C    	[NV..H.ZC]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterDirectIndirectIndexed : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("RegisterDirectIndirectIndexed");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Register Immediate
// ADC A, #i:     	A = A+i+C    	[NV..H.ZC]
// AND A, #i:     	A = A & i    	[N.....Z.]
// CMP A, #i:     	A - i    	[N.....ZC]
// CMP X, #i:     	X - i    	[N.....ZC]
// CMP Y, #i:     	Y - i    	[N.....ZC]
// EOR A, #i:     	A = A EOR i    	[N.....Z.]
// MOV A, #i:     	A = i    	[N.....Z.]
// MOV X, #i:     	X = i    	[N.....Z.]
// MOV Y, #i:     	Y = i    	[N.....Z.]
// OR A, #i:     	A = A | i    	[N.....Z.]
// SBC A, #i:     	A = A-i-!C    	[NV..H.ZC]
template <typename Operator, State::Register RegisterIndex>
class RegisterImmediate : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, state.getRegister<RegisterIndex>(), lowByte);
    }

    std::string toString() const override
    {
        return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", #$" + operandToString();
    }
};

// Register Indirect Increment Register
// MOV (X)+, A:     	(X++) = A      (no read)    	[........]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterIndirectIncrementRegister : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        MemoryLocation* firstRegister = state.getRegister<FirstRegister>();
        MemoryLocation* data = state.getDirectMemoryLocation(firstRegister->get()++);
        return Operator::invoke(state, data, state.getRegisterValue<SecondRegister>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " (" + State::getRegisterName<FirstRegister>() + ")+, " + State::getRegisterName<SecondRegister>();
    }
};

// Register Indirect Register
// MOV (X), A:     	(X) = A        (read)    	[........]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterIndirectRegister : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        MemoryLocation* memory = state.getDirectMemoryLocation(state.getRegisterValue<FirstRegister>());
        return Operator::invoke(state, memory, state.getRegisterValue<SecondRegister>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " (" + State::getRegisterName<FirstRegister>() + "), " + State::getRegisterName<SecondRegister>();
    }
};

// Register Program Counter Relative
// DBNZ Y, r:     	Y-- then JNZ    	[........]
template <typename Operator, State::Register RegisterIndex>
class RegisterProgramCounterRelative : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, state.getRegister<RegisterIndex>(), lowByte);
    }

    std::string toString() const override
    {
        std::ostringstream ss;
        ss << Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $";
        ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.readProgramByte(1)));
        return ss.str();
    }
};

// Register Register
// MOV A, X:     	A = X    	[N.....Z.]
// MOV A, Y:     	A = Y    	[N.....Z.]
// MOV SP, X:     	SP = X    	[........]
// MOV X, A:     	X = A    	[N.....Z.]
// MOV X, SP:     	X = SP    	[N.....Z.]
// MOV Y, A:     	Y = A    	[N.....Z.]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterRegister : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        return Operator::invoke(state, state.getRegister<FirstRegister>(), state.getRegisterValue<SecondRegister>());
    }

    std::string toString() const override
    {
        return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();
    }
};

// Register Register Indirect
// ADC A, (X):     	A = A+(X)+C    	[NV..H.ZC]
// AND A, (X):     	A = A & (X)    	[N.....Z.]
// CMP A, (X):     	A - (X)    	[N.....ZC]
// EOR A, (X):     	A = A EOR (X)    	[N.....Z.]
// MOV A, (X):     	A = (X)    	[N.....Z.]
// OR A, (X):     	A = A | (X)    	[N.....Z.]
// SBC A, (X):     	A = A-(X)-!C    	[NV..H.ZC]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterRegisterIndirect : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        MemoryLocation* memory = state.getDirectMemoryLocation(state.getRegisterValue<SecondRegister>());
        return Operator::invoke(state, state.getRegister<FirstRegister>(), memory->getValue());
    }

    std::string toString() const override
    {
        return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", (" + State::getRegisterName<SecondRegister>() + ")";
    }
};

// Register Register Indirect Increment
// MOV A, (X)+:     	A = (X++)    	[N.....Z.]
template <typename Operator, State::Register FirstRegister, State::Register SecondRegister>
class RegisterRegisterIndirectIncrement : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        throw AddressModeNotYetImplementedException("RegisterRegisterIndirectIncrement");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Table
// TCALL 0:     	CALL [$FFDE]    	[........]
// TCALL 1:     	CALL [$FFDC]    	[........]
// TCALL 2:     	CALL [$FFDA]    	[........]
// TCALL 3:     	CALL [$FFD8]    	[........]
// TCALL 4:     	CALL [$FFD6]    	[........]
// TCALL 5:     	CALL [$FFD4]    	[........]
// TCALL 6:     	CALL [$FFD2]    	[........]
// TCALL 7:     	CALL [$FFD0]    	[........]
// TCALL 8:     	CALL [$FFCE]    	[........]
// TCALL 9:     	CALL [$FFCC]    	[........]
// TCALL 10:     	CALL [$FFCA]    	[........]
// TCALL 11:     	CALL [$FFC8]    	[........]
// TCALL 12:     	CALL [$FFC6]    	[........]
// TCALL 13:     	CALL [$FFC4]    	[........]
// TCALL 14:     	CALL [$FFC2]    	[........]
// TCALL 15:     	CALL [$FFC0]    	[........]
template <typename Operator, uint8_t Index>
class Table : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        throw AddressModeNotYetImplementedException("Table");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// U Page
// PCALL u:     	CALL $FF00+u    	[........]
template <typename Operator>
class UPage : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        throw AddressModeNotYetImplementedException("UPage");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " $" + operandToString() + " TODO";
    }
};

// Y Accumulator
// MUL YA:     	YA = Y * A, NZ on Y only    	[N.....Z.]
template <typename Operator>
class YAccumulator : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        throw AddressModeNotYetImplementedException("YAccumulator");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

// Y Accumulator Direct
// ADDW YA, d:     	YA  = YA + (d), H on high byte    	[NV..H.ZC]
// CMPW YA, d:     	YA - (d)    	[N.....ZC]
// MOVW YA, d:     	YA = word (d)    	[N.....Z.]
// SUBW YA, d:     	YA  = YA - (d), H on high byte    	[NV..H.ZC]
template <typename Operator>
class YAccumulatorDirect : public Instruction2Byte
{
    using Instruction2Byte::InstructionBase;

    int invokeOperator(Byte lowByte) override
    {
        return Operator::invoke(state, state.getRegister<State::A>(), state.getDirectMemoryWord(lowByte));
    }

    std::string toString() const override
    {
        return Operator::toString() + " YA, $" + operandToString();
    }
};

// Y Accumulator Index
// DIV YA, X:     	A=YA/X, Y=mod(YA,X)    	[NV..H.Z.]
template <typename Operator, State::Register RegisterIndex>
class YAccumulatorIndex : public Instruction1Byte
{
    using Instruction1Byte::InstructionBase;

    int invokeOperator() override
    {
        throw AddressModeNotYetImplementedException("YAccumulatorIndex");
        MemoryLocation* data = nullptr;
        return Operator::invoke(state, data, 0);
    }

    std::string toString() const override
    {
        return Operator::toString() + " TODO";
    }
};

}

}

