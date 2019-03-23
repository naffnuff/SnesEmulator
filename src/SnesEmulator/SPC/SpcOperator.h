#pragma once

#include "SpcState.h"

namespace SPC {

namespace Operator {

// ADC
// (X), (Y): (X) = (X)+(Y)+C    	[NV..H.ZC]
// A, #i: A = A+i+C    	[NV..H.ZC]
// A, (X): A = A+(X)+C    	[NV..H.ZC]
// A, [d]+Y: A = A+([d]+Y)+C    	[NV..H.ZC]
// A, [d+X]: A = A+([d+X])+C    	[NV..H.ZC]
// A, d: A = A+(d)+C    	[NV..H.ZC]
// A, d+X: A = A+(d+X)+C    	[NV..H.ZC]
// A, !a: A = A+(a)+C    	[NV..H.ZC]
// A, !a+X: A = A+(a+X)+C    	[NV..H.ZC]
// A, !a+Y: A = A+(a+Y)+C    	[NV..H.ZC]
// dd, ds: (dd) = (dd)+(d)+C    	[NV..H.ZC]
// d, #i: (d) = (d)+i+C    	[NV..H.ZC]
class ADC
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("ADC is not implemented");
        return 0;
    }

    static std::string toString() { return "ADC"; }
};

// ADDW
// YA, d: YA  = YA + (d), H on high byte    	[NV..H.ZC]
class ADDW
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("ADDW is not implemented");
        return 0;
    }

    static std::string toString() { return "ADDW"; }
};

// AND
// (X), (Y): (X) = (X) & (Y)    	[N.....Z.]
// A, #i: A = A & i    	[N.....Z.]
// A, (X): A = A & (X)    	[N.....Z.]
// A, [d]+Y: A = A & ([d]+Y)    	[N.....Z.]
// A, [d+X]: A = A & ([d+X])    	[N.....Z.]
// A, d: A = A & (d)    	[N.....Z.]
// A, d+X: A = A & (d+X)    	[N.....Z.]
// A, !a: A = A & (a)    	[N.....Z.]
// A, !a+X: A = A & (a+X)    	[N.....Z.]
// A, !a+Y: A = A & (a+Y)    	[N.....Z.]
// dd, ds: (dd) = (dd) & (ds)    	[N.....Z.]
// d, #i: (d) = (d) & i    	[N.....Z.]
class AND
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("AND is not implemented");
        return 0;
    }

    static std::string toString() { return "AND"; }
};

// AND1
// C, /m.b: C = C & ~(m.b)    	[.......C]
// C, m.b: C = C & (m.b)    	[.......C]
class AND1
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("AND1 is not implemented");
        return 0;
    }

    static std::string toString() { return "AND1"; }
};

// ASL
// A: Left shift A: high->C, 0->low    	[N.....ZC]
// d: Left shift (d) as above    	[N.....ZC]
// d+X: Left shift (d+X) as above    	[N.....ZC]
// !a: Left shift (a) as above    	[N.....ZC]
class ASL
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("ASL is not implemented");
        return 0;
    }

    static std::string toString() { return "ASL"; }
};

static int branchIf(bool condition, State& state, int8_t offset)
{
    int cycles = 0;
    if (condition) {
        cycles += 2;
        state.setProgramCounter(state.getProgramCounter(offset));
    }
    return cycles;
}

// BBC
// d.0, r: PC+=r  if d.0 == 0    	[........]
// d.1, r: PC+=r  if d.1 == 0    	[........]
// d.2, r: PC+=r  if d.2 == 0    	[........]
// d.3, r: PC+=r  if d.3 == 0    	[........]
// d.4, r: PC+=r  if d.4 == 0    	[........]
// d.5, r: PC+=r  if d.5 == 0    	[........]
// d.6, r: PC+=r  if d.6 == 0    	[........]
// d.7, r: PC+=r  if d.7 == 0    	[........]
class BBC
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("BBC is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BBC"; }
};

// BBS
// d.0, r: PC+=r  if d.0 == 1    	[........]
// d.1, r: PC+=r  if d.1 == 1    	[........]
// d.2, r: PC+=r  if d.2 == 1    	[........]
// d.3, r: PC+=r  if d.3 == 1    	[........]
// d.4, r: PC+=r  if d.4 == 1    	[........]
// d.5, r: PC+=r  if d.5 == 1    	[........]
// d.6, r: PC+=r  if d.6 == 1    	[........]
// d.7, r: PC+=r  if d.7 == 1    	[........]
class BBS
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("BBS is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BBS"; }
};

// BCC
// r: PC+=r  if C == 0    	[........]
class BCC
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BCC is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BCC"; }
};

// BCS
// r: PC+=r  if C == 1    	[........]
class BCS
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BCS is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BCS"; }
};

// BEQ
// r: PC+=r  if Z == 1    	[........]
class BEQ
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BEQ is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BEQ"; }
};

// BMI
// r: PC+=r  if N == 1    	[........]
class BMI
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BMI is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BMI"; }
};

// BNE
// r: PC+=r  if Z == 0    	[........]
class BNE
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        return branchIf(!state.getFlag(State::z), state, offset);
    }

    static std::string toString() { return "BNE"; }
};

// BPL
// r: PC+=r  if N == 0    	[........]
class BPL
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BPL is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BPL"; }
};

// BRA
// r: PC+=r    	[........]
class BRA
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BRA is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BRA"; }
};

// BRK
// : Push PC and Flags, PC = [$FFDE]    	[...1.0..]
class BRK
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("BRK is not implemented");
        return 0;
    }

    static std::string toString() { return "BRK"; }
};

// BVC
// r: PC+=r  if V == 0    	[........]
class BVC
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BVC is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BVC"; }
};

// BVS
// r: PC+=r  if V == 1    	[........]
class BVS
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, int8_t offset)
    {
        throw std::runtime_error("BVS is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "BVS"; }
};

// CALL
// !a: (SP--)=PCh, (SP--)=PCl, PC=a    	[........]
class CALL
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("CALL is not implemented");
        return 0;
    }

    static std::string toString() { return "CALL"; }
};

// CBNE
// d+X, r: CMP A, (d+X) then BNE    	[........]
// d, r: CMP A, (d) then BNE    	[........]
class CBNE
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("CBNE is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "CBNE"; }
};

// CLR1
// d.0: d.0 = 0    	[........]
// d.1: d.1 = 0    	[........]
// d.2: d.2 = 0    	[........]
// d.3: d.3 = 0    	[........]
// d.4: d.4 = 0    	[........]
// d.5: d.5 = 0    	[........]
// d.6: d.6 = 0    	[........]
// d.7: d.7 = 0    	[........]
class CLR1
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("CLR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "CLR1"; }
};

// CLRC
// : C = 0    	[.......0]
class CLRC
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("CLRC is not implemented");
        return 0;
    }

    static std::string toString() { return "CLRC"; }
};

// CLRP
// : P = 0    	[..0.....]
class CLRP
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("CLRP is not implemented");
        return 0;
    }

    static std::string toString() { return "CLRP"; }
};

// CLRV
// : V = 0, H = 0    	[.0..0...]
class CLRV
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("CLRV is not implemented");
        return 0;
    }

    static std::string toString() { return "CLRV"; }
};

// CMP
// (X), (Y): (X) - (Y)    	[N.....ZC]
// A, #i: A - i    	[N.....ZC]
// A, (X): A - (X)    	[N.....ZC]
// A, [d]+Y: A - ([d]+Y)    	[N.....ZC]
// A, [d+X]: A - ([d+X])    	[N.....ZC]
// A, d: A - (d)    	[N.....ZC]
// A, d+X: A - (d+X)    	[N.....ZC]
// A, !a: A - (a)    	[N.....ZC]
// A, !a+X: A - (a+X)    	[N.....ZC]
// A, !a+Y: A - (a+Y)    	[N.....ZC]
// X, #i: X - i    	[N.....ZC]
// X, d: X - (d)    	[N.....ZC]
// X, !a: X - (a)    	[N.....ZC]
// Y, #i: Y - i    	[N.....ZC]
// Y, d: Y - (d)    	[N.....ZC]
// Y, !a: Y - (a)    	[N.....ZC]
// dd, ds: (dd) - (ds)    	[N.....ZC]
// d, #i: (d) - i    	[N.....ZC]
class CMP
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        state.setFlag(State::c, leftOperand >= rightOperand);
        state.updateSignFlags(leftOperand - rightOperand);
        return 0;
    }

    static std::string toString() { return "CMP"; }
};

// CMPW
// YA, d: YA - (d)    	[N.....ZC]
class CMPW
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("CMPW is not implemented");
        return 0;
    }

    static std::string toString() { return "CMPW"; }
};

// DAA
// A: decimal adjust for addition    	[N.....ZC]
class DAA
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("DAA is not implemented");
        return 0;
    }

    static std::string toString() { return "DAA"; }
};

// DAS
// A: decimal adjust for subtraction    	[N.....ZC]
class DAS
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("DAS is not implemented");
        return 0;
    }

    static std::string toString() { return "DAS"; }
};

// DBNZ
// Y, r: Y-- then JNZ    	[........]
// d, r: (d)-- then JNZ    	[........]
class DBNZ
{
public:
    // �1: Add 1 cycle if branch is taken
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("DBNZ is not implemented");
        int cycles = 0;
        if (true /*branch taken*/) {
            cycles += 2;
            throw std::runtime_error("TODO01");
        }
        return cycles;
    }

    static std::string toString() { return "DBNZ"; }
};

// DEC
// A: A--    	[N.....Z.]
// X: X--    	[N.....Z.]
// Y: Y--    	[N.....Z.]
// d: (d)--    	[N.....Z.]
// d+X: (d+X)--    	[N.....Z.]
// !a: (a)--    	[N.....Z.]
class DEC
{
public:
    static int invoke(State& state, Byte& operand)
    {
        state.updateSignFlags(--operand);
        return 0;
    }

    static std::string toString() { return "DEC"; }
};

// DECW
// d: Word (d)--    	[N.....Z.]
class DECW
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("DECW is not implemented");
        return 0;
    }

    static std::string toString() { return "DECW"; }
};

// DI
// : I = 0    	[.....0..]
class DI
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("DI is not implemented");
        return 0;
    }

    static std::string toString() { return "DI"; }
};

// DIV
// YA, X: A=YA/X, Y=mod(YA,X)    	[NV..H.Z.]
class DIV
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("DIV is not implemented");
        return 0;
    }

    static std::string toString() { return "DIV"; }
};

// EI
// : I = 1    	[.....1..]
class EI
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("EI is not implemented");
        return 0;
    }

    static std::string toString() { return "EI"; }
};

// EOR
// (X), (Y): (X) = (X) EOR (Y)    	[N.....Z.]
// A, #i: A = A EOR i    	[N.....Z.]
// A, (X): A = A EOR (X)    	[N.....Z.]
// A, [d]+Y: A = A EOR ([d]+Y)    	[N.....Z.]
// A, [d+X]: A = A EOR ([d+X])    	[N.....Z.]
// A, d: A = A EOR (d)    	[N.....Z.]
// A, d+X: A = A EOR (d+X)    	[N.....Z.]
// A, !a: A = A EOR (a)    	[N.....Z.]
// A, !a+X: A = A EOR (a+X)    	[N.....Z.]
// A, !a+Y: A = A EOR (a+Y)    	[N.....Z.]
// dd, ds: (dd) = (dd) EOR (ds)    	[N.....Z.]
// d, #i: (d) = (d) EOR i    	[N.....Z.]
class EOR
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("EOR is not implemented");
        return 0;
    }

    static std::string toString() { return "EOR"; }
};

// EOR1
// C, m.b: C = C EOR (m.b)    	[.......C]
class EOR1
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("EOR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "EOR1"; }
};

// INC
// A: A++    	[N.....Z.]
// X: X++    	[N.....Z.]
// Y: Y++    	[N.....Z.]
// d: (d)++    	[N.....Z.]
// d+X: (d+X)++    	[N.....Z.]
// !a: (a)++    	[N.....Z.]
class INC
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("INC is not implemented");
        return 0;
    }

    static std::string toString() { return "INC"; }
};

// INCW
// d: Word (d)++    	[N.....Z.]
class INCW
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("INCW is not implemented");
        return 0;
    }

    static std::string toString() { return "INCW"; }
};

// JMP
// [!a+X]: PC = [a+X]    	[........]
// !a: PC = a    	[........]
class JMP
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("JMP is not implemented");
        return 0;
    }

    static std::string toString() { return "JMP"; }
};

// LSR
// A: Right shift A: 0->high, low->C    	[N.....ZC]
// d: Right shift (d) as above    	[N.....ZC]
// d+X: Right shift (d+X) as above    	[N.....ZC]
// !a: Right shift (a) as above    	[N.....ZC]
class LSR
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("LSR is not implemented");
        return 0;
    }

    static std::string toString() { return "LSR"; }
};

// MOV
// (X)+, A: (X++) = A      (no read)    	[........]
// (X), A: (X) = A        (read)    	[........]
// [d]+Y, A: ([d]+Y) = A    (read)    	[........]
// [d+X], A: ([d+X]) = A    (read)    	[........]
// SP, X: SP = X    	[........]
// dd, ds: (dd) = (ds)    (no read)    	[........]
// d+X, A: (d+X) = A      (read)    	[........]
// d+X, Y: (d+X) = Y      (read)    	[........]
// d+Y, X: (d+Y) = X      (read)    	[........]
// d, #i: (d) = i        (read)    	[........]
// d, A: (d) = A        (read)    	[........]
// d, X: (d) = X        (read)    	[........]
// d, Y: (d) = Y        (read)    	[........]
// !a+X, A: (a+X) = A      (read)    	[........]
// !a+Y, A: (a+Y) = A      (read)    	[........]
// !a, A: (a) = A        (read)    	[........]
// !a, X: (a) = X        (read)    	[........]
// !a, Y: (a) = Y        (read)    	[........]
class MOV
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        leftOperand = rightOperand;
        return 0;
    }

    static std::string toString() { return "MOV"; }
};

// MOV1
// C, m.b: C = (m.b)    	[.......C]
// m.b, C: (m.b) = C    	[........]
class MOV1
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("MOV1 is not implemented");
        return 0;
    }

    static std::string toString() { return "MOV1"; }
};

// MOVW
// YA, d: YA = word (d)    	[N.....Z.]
// d, YA: word (d) = YA  (read low only)    	[........]
class MOVW
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("MOVW is not implemented");
        return 0;
    }

    static std::string toString() { return "MOVW"; }
};

// MOV_SignedResult
// A, #i: A = i    	[N.....Z.]
// A, (X): A = (X)    	[N.....Z.]
// A, (X)+: A = (X++)    	[N.....Z.]
// A, [d]+Y: A = ([d]+Y)    	[N.....Z.]
// A, [d+X]: A = ([d+X])    	[N.....Z.]
// A, X: A = X    	[N.....Z.]
// A, Y: A = Y    	[N.....Z.]
// A, d: A = (d)    	[N.....Z.]
// A, d+X: A = (d+X)    	[N.....Z.]
// A, !a: A = (a)    	[N.....Z.]
// A, !a+X: A = (a+X)    	[N.....Z.]
// A, !a+Y: A = (a+Y)    	[N.....Z.]
// X, #i: X = i    	[N.....Z.]
// X, A: X = A    	[N.....Z.]
// X, SP: X = SP    	[N.....Z.]
// X, d: X = (d)    	[N.....Z.]
// X, d+Y: X = (d+Y)    	[N.....Z.]
// X, !a: X = (a)    	[N.....Z.]
// Y, #i: Y = i    	[N.....Z.]
// Y, A: Y = A    	[N.....Z.]
// Y, d: Y = (d)    	[N.....Z.]
// Y, d+X: Y = (d+X)    	[N.....Z.]
// Y, !a: Y = (a)    	[N.....Z.]
class MOV_SignedResult : public MOV
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        MOV::invoke(state, leftOperand, rightOperand);
        state.updateSignFlags(leftOperand);
        return 0;
    }
};

// MUL
// YA: YA = Y * A, NZ on Y only    	[N.....Z.]
class MUL
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("MUL is not implemented");
        return 0;
    }

    static std::string toString() { return "MUL"; }
};

// NOP
// : do nothing    	[........]
class NOP
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("NOP is not implemented");
        return 0;
    }

    static std::string toString() { return "NOP"; }
};

// NOT1
// m.b: m.b = ~m.b    	[........]
class NOT1
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("NOT1 is not implemented");
        return 0;
    }

    static std::string toString() { return "NOT1"; }
};

// NOTC
// : C = !C    	[.......C]
class NOTC
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("NOTC is not implemented");
        return 0;
    }

    static std::string toString() { return "NOTC"; }
};

// OR
// (X), (Y): (X) = (X) | (Y)    	[N.....Z.]
// A, #i: A = A | i    	[N.....Z.]
// A, (X): A = A | (X)    	[N.....Z.]
// A, [d]+Y: A = A | ([d]+Y)    	[N.....Z.]
// A, [d+X]: A = A | ([d+X])    	[N.....Z.]
// A, d: A = A | (d)    	[N.....Z.]
// A, d+X: A = A | (d+X)    	[N.....Z.]
// A, !a: A = A | (a)    	[N.....Z.]
// A, !a+X: A = A | (a+X)    	[N.....Z.]
// A, !a+Y: A = A | (a+Y)    	[N.....Z.]
// dd, ds: (dd) = (dd) | (ds)    	[N.....Z.]
// d, #i: (d) = (d) | i    	[N.....Z.]
class OR
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("OR is not implemented");
        return 0;
    }

    static std::string toString() { return "OR"; }
};

// OR1
// C, /m.b: C = C | ~(m.b)    	[.......C]
// C, m.b: C = C | (m.b)    	[.......C]
class OR1
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("OR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "OR1"; }
};

// PCALL
// u: CALL $FF00+u    	[........]
class PCALL
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("PCALL is not implemented");
        return 0;
    }

    static std::string toString() { return "PCALL"; }
};

// POP
// A: A = (++SP)    	[........]
// PSW: Flags = (++SP)    	[NVPBHIZC]
// X: X = (++SP)    	[........]
// Y: Y = (++SP)    	[........]
class POP
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("POP is not implemented");
        return 0;
    }

    static std::string toString() { return "POP"; }
};

// PUSH
// A: (SP--) = A    	[........]
// PSW: (SP--) = Flags    	[........]
// X: (SP--) = X    	[........]
// Y: (SP--) = Y    	[........]
class PUSH
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("PUSH is not implemented");
        return 0;
    }

    static std::string toString() { return "PUSH"; }
};

// RET
// : Pop PC    	[........]
class RET
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("RET is not implemented");
        return 0;
    }

    static std::string toString() { return "RET"; }
};

// RET1
// : Pop Flags, PC    	[NVPBHIZC]
class RET1
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("RET1 is not implemented");
        return 0;
    }

    static std::string toString() { return "RET1"; }
};

// ROL
// A: Left shift A: low=C, C=high    	[N.....ZC]
// d: Left shift (d) as above    	[N.....ZC]
// d+X: Left shift (d+X) as above    	[N.....ZC]
// !a: Left shift (a) as above    	[N.....ZC]
class ROL
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("ROL is not implemented");
        return 0;
    }

    static std::string toString() { return "ROL"; }
};

// ROR
// A: Right shift A: high=C, C=low    	[N.....ZC]
// d: Right shift (d) as above    	[N.....ZC]
// d+X: Right shift (d+X) as above    	[N.....ZC]
// !a: Right shift (a) as above    	[N.....ZC]
class ROR
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("ROR is not implemented");
        return 0;
    }

    static std::string toString() { return "ROR"; }
};

// SBC
// (X), (Y): (X) = (X)-(Y)-!C    	[NV..H.ZC]
// A, #i: A = A-i-!C    	[NV..H.ZC]
// A, (X): A = A-(X)-!C    	[NV..H.ZC]
// A, [d]+Y: A = A-([d]+Y)-!C    	[NV..H.ZC]
// A, [d+X]: A = A-([d+X])-!C    	[NV..H.ZC]
// A, d: A = A-(d)-!C    	[NV..H.ZC]
// A, d+X: A = A-(d+X)-!C    	[NV..H.ZC]
// A, !a: A = A-(a)-!C    	[NV..H.ZC]
// A, !a+X: A = A-(a+X)-!C    	[NV..H.ZC]
// A, !a+Y: A = A-(a+Y)-!C    	[NV..H.ZC]
// dd, ds: (dd) = (dd)-(ds)-!C    	[NV..H.ZC]
// d, #i: (d) = (d)-i-!C    	[NV..H.ZC]
class SBC
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("SBC is not implemented");
        return 0;
    }

    static std::string toString() { return "SBC"; }
};

// SET1
// d.0: d.0 = 1    	[........]
// d.1: d.1 = 1    	[........]
// d.2: d.2 = 1    	[........]
// d.3: d.3 = 1    	[........]
// d.4: d.4 = 1    	[........]
// d.5: d.5 = 1    	[........]
// d.6: d.6 = 1    	[........]
// d.7: d.7 = 1    	[........]
class SET1
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("SET1 is not implemented");
        return 0;
    }

    static std::string toString() { return "SET1"; }
};

// SETC
// : C = 1    	[.......1]
class SETC
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("SETC is not implemented");
        return 0;
    }

    static std::string toString() { return "SETC"; }
};

// SETP
// : P = 1    	[..1.....]
class SETP
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("SETP is not implemented");
        return 0;
    }

    static std::string toString() { return "SETP"; }
};

// SLEEP
// : Halts the processor    	[........]
class SLEEP
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("SLEEP is not implemented");
        return 0;
    }

    static std::string toString() { return "SLEEP"; }
};

// STOP
// : Halts the processor    	[........]
class STOP
{
public:
    static int invoke(State& state)
    {
        throw std::runtime_error("STOP is not implemented");
        return 0;
    }

    static std::string toString() { return "STOP"; }
};

// SUBW
// YA, d: YA  = YA - (d), H on high byte    	[NV..H.ZC]
class SUBW
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("SUBW is not implemented");
        return 0;
    }

    static std::string toString() { return "SUBW"; }
};

// TCALL
// 0: CALL [$FFDE]    	[........]
// 1: CALL [$FFDC]    	[........]
// 2: CALL [$FFDA]    	[........]
// 3: CALL [$FFD8]    	[........]
// 4: CALL [$FFD6]    	[........]
// 5: CALL [$FFD4]    	[........]
// 6: CALL [$FFD2]    	[........]
// 7: CALL [$FFD0]    	[........]
// 8: CALL [$FFCE]    	[........]
// 9: CALL [$FFCC]    	[........]
// 10: CALL [$FFCA]    	[........]
// 11: CALL [$FFC8]    	[........]
// 12: CALL [$FFC6]    	[........]
// 13: CALL [$FFC4]    	[........]
// 14: CALL [$FFC2]    	[........]
// 15: CALL [$FFC0]    	[........]
class TCALL
{
public:
    static int invoke(State& state, Byte& leftOperand, const Byte& rightOperand)
    {
        throw std::runtime_error("TCALL is not implemented");
        return 0;
    }

    static std::string toString() { return "TCALL"; }
};

// TCLR1
// !a: (a) = (a)&~A, ZN as for A-(a)    	[N.....Z.]
class TCLR1
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("TCLR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "TCLR1"; }
};

// TSET1
// !a: (a) = (a)|A, ZN as for A-(a)    	[N.....Z.]
class TSET1
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("TSET1 is not implemented");
        return 0;
    }

    static std::string toString() { return "TSET1"; }
};

// XCN
// A: A = (A>>4) | (A<<4)    	[N.....Z.]
class XCN
{
public:
    static int invoke(State& state, Byte& operand)
    {
        throw std::runtime_error("XCN is not implemented");
        return 0;
    }

    static std::string toString() { return "XCN"; }
};

}

}
