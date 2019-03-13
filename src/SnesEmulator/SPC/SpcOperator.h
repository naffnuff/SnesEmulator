#pragma once

#include "SpcState.h"

namespace SPC {

namespace Operator {

// ADC
// (X), (Y): (X) = (X)+(Y)+C
// A, #i: A = A+i+C
// A, (X): A = A+(X)+C
// A, [d]+Y: A = A+([d]+Y)+C
// A, [d+X]: A = A+([d+X])+C
// A, d: A = A+(d)+C
// A, d+X: A = A+(d+X)+C
// A, !a: A = A+(a)+C
// A, !a+X: A = A+(a+X)+C
// A, !a+Y: A = A+(a+Y)+C
// dd, ds: (dd) = (dd)+(d)+C
// d, #i: (d) = (d)+i+C
class ADC
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("ADC is not implemented");
        return 0;
    }

    static std::string toString() { return "ADC"; }
};

// ADDW
// YA, d: YA  = YA + (d), H on high byte
class ADDW
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("ADDW is not implemented");
        return 0;
    }

    static std::string toString() { return "ADDW"; }
};

// AND
// (X), (Y): (X) = (X) & (Y)
// A, #i: A = A & i
// A, (X): A = A & (X)
// A, [d]+Y: A = A & ([d]+Y)
// A, [d+X]: A = A & ([d+X])
// A, d: A = A & (d)
// A, d+X: A = A & (d+X)
// A, !a: A = A & (a)
// A, !a+X: A = A & (a+X)
// A, !a+Y: A = A & (a+Y)
// dd, ds: (dd) = (dd) & (ds)
// d, #i: (d) = (d) & i
class AND
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("AND is not implemented");
        return 0;
    }

    static std::string toString() { return "AND"; }
};

// AND1
// C, /m.b: C = C & ~(m.b)
// C, m.b: C = C & (m.b)
class AND1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("AND1 is not implemented");
        return 0;
    }

    static std::string toString() { return "AND1"; }
};

// ASL
// A: Left shift A: high->C, 0->low
// d: Left shift (d) as above
// d+X: Left shift (d+X) as above
// !a: Left shift (a) as above
class ASL
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("ASL is not implemented");
        return 0;
    }

    static std::string toString() { return "ASL"; }
};

// BBC
// d.0, r: PC+=r  if d.0 == 0
// d.1, r: PC+=r  if d.1 == 0
// d.2, r: PC+=r  if d.2 == 0
// d.3, r: PC+=r  if d.3 == 0
// d.4, r: PC+=r  if d.4 == 0
// d.5, r: PC+=r  if d.5 == 0
// d.6, r: PC+=r  if d.6 == 0
// d.7, r: PC+=r  if d.7 == 0
class BBC
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BBC is not implemented");
        return 0;
    }

    static std::string toString() { return "BBC"; }
};

// BBS
// d.0, r: PC+=r  if d.0 == 1
// d.1, r: PC+=r  if d.1 == 1
// d.2, r: PC+=r  if d.2 == 1
// d.3, r: PC+=r  if d.3 == 1
// d.4, r: PC+=r  if d.4 == 1
// d.5, r: PC+=r  if d.5 == 1
// d.6, r: PC+=r  if d.6 == 1
// d.7, r: PC+=r  if d.7 == 1
class BBS
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BBS is not implemented");
        return 0;
    }

    static std::string toString() { return "BBS"; }
};

// BCC
// r: PC+=r  if C == 0
class BCC
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BCC is not implemented");
        return 0;
    }

    static std::string toString() { return "BCC"; }
};

// BCS
// r: PC+=r  if C == 1
class BCS
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BCS is not implemented");
        return 0;
    }

    static std::string toString() { return "BCS"; }
};

// BEQ
// r: PC+=r  if Z == 1
class BEQ
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BEQ is not implemented");
        return 0;
    }

    static std::string toString() { return "BEQ"; }
};

// BMI
// r: PC+=r  if N == 1
class BMI
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BMI is not implemented");
        return 0;
    }

    static std::string toString() { return "BMI"; }
};

// BNE
// r: PC+=r  if Z == 0
class BNE
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BNE is not implemented");
        return 0;
    }

    static std::string toString() { return "BNE"; }
};

// BPL
// r: PC+=r  if N == 0
class BPL
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BPL is not implemented");
        return 0;
    }

    static std::string toString() { return "BPL"; }
};

// BRA
// r: PC+=r
class BRA
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BRA is not implemented");
        return 0;
    }

    static std::string toString() { return "BRA"; }
};

// BRK
// : Push PC and Flags, PC = [$FFDE]
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
// r: PC+=r  if V == 0
class BVC
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BVC is not implemented");
        return 0;
    }

    static std::string toString() { return "BVC"; }
};

// BVS
// r: PC+=r  if V == 1
class BVS
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("BVS is not implemented");
        return 0;
    }

    static std::string toString() { return "BVS"; }
};

// CALL
// !a: (SP--)=PCh, (SP--)=PCl, PC=a
class CALL
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("CALL is not implemented");
        return 0;
    }

    static std::string toString() { return "CALL"; }
};

// CBNE
// d+X, r: CMP A, (d+X) then BNE
// d, r: CMP A, (d) then BNE
class CBNE
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("CBNE is not implemented");
        return 0;
    }

    static std::string toString() { return "CBNE"; }
};

// CLR1
// d.0: d.0 = 0
// d.1: d.1 = 0
// d.2: d.2 = 0
// d.3: d.3 = 0
// d.4: d.4 = 0
// d.5: d.5 = 0
// d.6: d.6 = 0
// d.7: d.7 = 0
class CLR1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("CLR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "CLR1"; }
};

// CLRC
// : C = 0
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
// : P = 0
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
// : V = 0, H = 0
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
// (X), (Y): (X) - (Y)
// A, #i: A - i
// A, (X): A - (X)
// A, [d]+Y: A - ([d]+Y)
// A, [d+X]: A - ([d+X])
// A, d: A - (d)
// A, d+X: A - (d+X)
// A, !a: A - (a)
// A, !a+X: A - (a+X)
// A, !a+Y: A - (a+Y)
// X, #i: X - i
// X, d: X - (d)
// X, !a: X - (a)
// Y, #i: Y - i
// Y, d: Y - (d)
// Y, !a: Y - (a)
// dd, ds: (dd) - (ds)
// d, #i: (d) - i
class CMP
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("CMP is not implemented");
        return 0;
    }

    static std::string toString() { return "CMP"; }
};

// CMPW
// YA, d: YA - (d)
class CMPW
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("CMPW is not implemented");
        return 0;
    }

    static std::string toString() { return "CMPW"; }
};

// DAA
// A: decimal adjust for addition
class DAA
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("DAA is not implemented");
        return 0;
    }

    static std::string toString() { return "DAA"; }
};

// DAS
// A: decimal adjust for subtraction
class DAS
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("DAS is not implemented");
        return 0;
    }

    static std::string toString() { return "DAS"; }
};

// DBNZ
// Y, r: Y-- then JNZ
// d, r: (d)-- then JNZ
class DBNZ
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("DBNZ is not implemented");
        return 0;
    }

    static std::string toString() { return "DBNZ"; }
};

// DEC
// A: A--
// X: X--
// Y: Y--
// d: (d)--
// d+X: (d+X)--
// !a: (a)--
class DEC
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("DEC is not implemented");
        return 0;
    }

    static std::string toString() { return "DEC"; }
};

// DECW
// d: Word (d)--
class DECW
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("DECW is not implemented");
        return 0;
    }

    static std::string toString() { return "DECW"; }
};

// DI
// : I = 0
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
// YA, X: A=YA/X, Y=mod(YA,X)
class DIV
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("DIV is not implemented");
        return 0;
    }

    static std::string toString() { return "DIV"; }
};

// EI
// : I = 1
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
// (X), (Y): (X) = (X) EOR (Y)
// A, #i: A = A EOR i
// A, (X): A = A EOR (X)
// A, [d]+Y: A = A EOR ([d]+Y)
// A, [d+X]: A = A EOR ([d+X])
// A, d: A = A EOR (d)
// A, d+X: A = A EOR (d+X)
// A, !a: A = A EOR (a)
// A, !a+X: A = A EOR (a+X)
// A, !a+Y: A = A EOR (a+Y)
// dd, ds: (dd) = (dd) EOR (ds)
// d, #i: (d) = (d) EOR i
class EOR
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("EOR is not implemented");
        return 0;
    }

    static std::string toString() { return "EOR"; }
};

// EOR1
// C, m.b: C = C EOR (m.b)
class EOR1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("EOR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "EOR1"; }
};

// INC
// A: A++
// X: X++
// Y: Y++
// d: (d)++
// d+X: (d+X)++
// !a: (a)++
class INC
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("INC is not implemented");
        return 0;
    }

    static std::string toString() { return "INC"; }
};

// INCW
// d: Word (d)++
class INCW
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("INCW is not implemented");
        return 0;
    }

    static std::string toString() { return "INCW"; }
};

// JMP
// [!a+X]: PC = [a+X]
// !a: PC = a
class JMP
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("JMP is not implemented");
        return 0;
    }

    static std::string toString() { return "JMP"; }
};

// LSR
// A: Right shift A: 0->high, low->C
// d: Right shift (d) as above
// d+X: Right shift (d+X) as above
// !a: Right shift (a) as above
class LSR
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("LSR is not implemented");
        return 0;
    }

    static std::string toString() { return "LSR"; }
};

// MOV
// (X)+, A: (X++) = A      (no read)
// (X), A: (X) = A        (read)
// [d]+Y, A: ([d]+Y) = A    (read)
// [d+X], A: ([d+X]) = A    (read)
// A, #i: A = i
// A, (X): A = (X)
// A, (X)+: A = (X++)
// A, [d]+Y: A = ([d]+Y)
// A, [d+X]: A = ([d+X])
// A, X: A = X
// A, Y: A = Y
// A, d: A = (d)
// A, d+X: A = (d+X)
// A, !a: A = (a)
// A, !a+X: A = (a+X)
// A, !a+Y: A = (a+Y)
// SP, X: SP = X
// X, #i: X = i
// X, A: X = A
// X, SP: X = SP
// X, d: X = (d)
// X, d+Y: X = (d+Y)
// X, !a: X = (a)
// Y, #i: Y = i
// Y, A: Y = A
// Y, d: Y = (d)
// Y, d+X: Y = (d+X)
// Y, !a: Y = (a)
// dd, ds: (dd) = (ds)    (no read)
// d+X, A: (d+X) = A      (read)
// d+X, Y: (d+X) = Y      (read)
// d+Y, X: (d+Y) = X      (read)
// d, #i: (d) = i        (read)
// d, A: (d) = A        (read)
// d, X: (d) = X        (read)
// d, Y: (d) = Y        (read)
// !a+X, A: (a+X) = A      (read)
// !a+Y, A: (a+Y) = A      (read)
// !a, A: (a) = A        (read)
// !a, X: (a) = X        (read)
// !a, Y: (a) = Y        (read)
class MOV
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("MOV is not implemented");
        return 0;
    }

    static std::string toString() { return "MOV"; }
};

// MOV1
// C, m.b: C = (m.b)
// m.b, C: (m.b) = C
class MOV1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("MOV1 is not implemented");
        return 0;
    }

    static std::string toString() { return "MOV1"; }
};

// MOVW
// YA, d: YA = word (d)
// d, YA: word (d) = YA  (read low only)
class MOVW
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("MOVW is not implemented");
        return 0;
    }

    static std::string toString() { return "MOVW"; }
};

// MUL
// YA: YA = Y * A, NZ on Y only
class MUL
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("MUL is not implemented");
        return 0;
    }

    static std::string toString() { return "MUL"; }
};

// NOP
// : do nothing
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
// m.b: m.b = ~m.b
class NOT1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("NOT1 is not implemented");
        return 0;
    }

    static std::string toString() { return "NOT1"; }
};

// NOTC
// : C = !C
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
// (X), (Y): (X) = (X) | (Y)
// A, #i: A = A | i
// A, (X): A = A | (X)
// A, [d]+Y: A = A | ([d]+Y)
// A, [d+X]: A = A | ([d+X])
// A, d: A = A | (d)
// A, d+X: A = A | (d+X)
// A, !a: A = A | (a)
// A, !a+X: A = A | (a+X)
// A, !a+Y: A = A | (a+Y)
// dd, ds: (dd) = (dd) | (ds)
// d, #i: (d) = (d) | i
class OR
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("OR is not implemented");
        return 0;
    }

    static std::string toString() { return "OR"; }
};

// OR1
// C, /m.b: C = C | ~(m.b)
// C, m.b: C = C | (m.b)
class OR1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("OR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "OR1"; }
};

// PCALL
// u: CALL $FF00+u
class PCALL
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("PCALL is not implemented");
        return 0;
    }

    static std::string toString() { return "PCALL"; }
};

// POP
// A: A = (++SP)
// PSW: Flags = (++SP)
// X: X = (++SP)
// Y: Y = (++SP)
class POP
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("POP is not implemented");
        return 0;
    }

    static std::string toString() { return "POP"; }
};

// PUSH
// A: (SP--) = A
// PSW: (SP--) = Flags
// X: (SP--) = X
// Y: (SP--) = Y
class PUSH
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("PUSH is not implemented");
        return 0;
    }

    static std::string toString() { return "PUSH"; }
};

// RET
// : Pop PC
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
// : Pop Flags, PC
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
// A: Left shift A: low=C, C=high
// d: Left shift (d) as above
// d+X: Left shift (d+X) as above
// !a: Left shift (a) as above
class ROL
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("ROL is not implemented");
        return 0;
    }

    static std::string toString() { return "ROL"; }
};

// ROR
// A: Right shift A: high=C, C=low
// d: Right shift (d) as above
// d+X: Right shift (d+X) as above
// !a: Right shift (a) as above
class ROR
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("ROR is not implemented");
        return 0;
    }

    static std::string toString() { return "ROR"; }
};

// SBC
// (X), (Y): (X) = (X)-(Y)-!C
// A, #i: A = A-i-!C
// A, (X): A = A-(X)-!C
// A, [d]+Y: A = A-([d]+Y)-!C
// A, [d+X]: A = A-([d+X])-!C
// A, d: A = A-(d)-!C
// A, d+X: A = A-(d+X)-!C
// A, !a: A = A-(a)-!C
// A, !a+X: A = A-(a+X)-!C
// A, !a+Y: A = A-(a+Y)-!C
// dd, ds: (dd) = (dd)-(ds)-!C
// d, #i: (d) = (d)-i-!C
class SBC
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("SBC is not implemented");
        return 0;
    }

    static std::string toString() { return "SBC"; }
};

// SET1
// d.0: d.0 = 1
// d.1: d.1 = 1
// d.2: d.2 = 1
// d.3: d.3 = 1
// d.4: d.4 = 1
// d.5: d.5 = 1
// d.6: d.6 = 1
// d.7: d.7 = 1
class SET1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("SET1 is not implemented");
        return 0;
    }

    static std::string toString() { return "SET1"; }
};

// SETC
// : C = 1
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
// : P = 1
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
// : Halts the processor
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
// : Halts the processor
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
// YA, d: YA  = YA - (d), H on high byte
class SUBW
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("SUBW is not implemented");
        return 0;
    }

    static std::string toString() { return "SUBW"; }
};

// TCALL
// 0: CALL [$FFDE]
// 1: CALL [$FFDC]
// 2: CALL [$FFDA]
// 3: CALL [$FFD8]
// 4: CALL [$FFD6]
// 5: CALL [$FFD4]
// 6: CALL [$FFD2]
// 7: CALL [$FFD0]
// 8: CALL [$FFCE]
// 9: CALL [$FFCC]
// 10: CALL [$FFCA]
// 11: CALL [$FFC8]
// 12: CALL [$FFC6]
// 13: CALL [$FFC4]
// 14: CALL [$FFC2]
// 15: CALL [$FFC0]
class TCALL
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("TCALL is not implemented");
        return 0;
    }

    static std::string toString() { return "TCALL"; }
};

// TCLR1
// !a: (a) = (a)&~A, ZN as for A-(a)
class TCLR1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("TCLR1 is not implemented");
        return 0;
    }

    static std::string toString() { return "TCLR1"; }
};

// TSET1
// !a: (a) = (a)|A, ZN as for A-(a)
class TSET1
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("TSET1 is not implemented");
        return 0;
    }

    static std::string toString() { return "TSET1"; }
};

// XCN
// A: A = (A>>4) | (A<<4)
class XCN
{
public:
    static int invoke(State& state, uint8_t* data)
    {
        throw std::runtime_error("XCN is not implemented");
        return 0;
    }

    static std::string toString() { return "XCN"; }
};

}

}
