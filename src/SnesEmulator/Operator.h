#pragma once

#include "State.h"

namespace Operator {

class ADC
{
public:
    static int operate(State& state, int* address);
};

class AND
{
public:
    static int operate(State& state, int* address);
};

class ASL
{
public:
    static int operate(State& state, int* address);
};

class BCC
{
public:
    static int operate(State& state, int* address);
};

class BCS
{
public:
    static int operate(State& state, int* address);
};

class BEQ
{
public:
    static int operate(State& state, int* address);
};

class BIT
{
public:
    static int operate(State& state, int* address);
};

class BMI
{
public:
    static int operate(State& state, int* address);
};

class BNE
{
public:
    static int operate(State& state, int* address);
};

class BPL
{
public:
    static int operate(State& state, int* address);
};

class BRA
{
public:
    static int operate(State& state, int* address);
};

class BRK
{
public:
    static int operate(State& state, int* address);
};

class BRL
{
public:
    static int operate(State& state, int* address);
};

class BVC
{
public:
    static int operate(State& state, int* address);
};

class BVS
{
public:
    static int operate(State& state, int* address);
};

class CLC
{
public:
    static int operate(State& state, int* address);
};

class CLD
{
public:
    static int operate(State& state, int* address);
};

class CLI
{
public:
    static int operate(State& state, int* address);
};

class CLV
{
public:
    static int operate(State& state, int* address);
};

class CMP
{
public:
    static int operate(State& state, int* address);
};

class COP
{
public:
    static int operate(State& state, int* address);
};

class CPX
{
public:
    static int operate(State& state, int* address);
};

class CPY
{
public:
    static int operate(State& state, int* address);
};

class DEC
{
public:
    static int operate(State& state, int* address);
};

class DEX
{
public:
    static int operate(State& state, int* address);
};

class DEY
{
public:
    static int operate(State& state, int* address);
};

class EOR
{
public:
    static int operate(State& state, int* address);
};

class INC
{
public:
    static int operate(State& state, int* address);
};

class INX
{
public:
    static int operate(State& state, int* address);
};

class INY
{
public:
    static int operate(State& state, int* address);
};

class JMP
{
public:
    static int operate(State& state, int* address);
};

class JSR
{
public:
    static int operate(State& state, int* address);
};

class LDA
{
public:
    static int operate(State& state, int* address);
};

class LDX
{
public:
    static int operate(State& state, int* address);
};

class LDY
{
public:
    static int operate(State& state, int* address);
};

class LSR
{
public:
    static int operate(State& state, int* address);
};

class MVN
{
public:
    static int operate(State& state, int* address);
};

class NOP
{
public:
    static int operate(State& state, int* address);
};

class ORA
{
public:
    static int operate(State& state, int* address);
};

class PEA
{
public:
    static int operate(State& state, int* address);
};

class PEI
{
public:
    static int operate(State& state, int* address);
};

class PER
{
public:
    static int operate(State& state, int* address);
};

class PHA
{
public:
    static int operate(State& state, int* address);
};

class PHB
{
public:
    static int operate(State& state, int* address);
};

class PHD
{
public:
    static int operate(State& state, int* address);
};

class PHK
{
public:
    static int operate(State& state, int* address);
};

class PHP
{
public:
    static int operate(State& state, int* address);
};

class PHX
{
public:
    static int operate(State& state, int* address);
};

class PHY
{
public:
    static int operate(State& state, int* address);
};

class PLA
{
public:
    static int operate(State& state, int* address);
};

class PLB
{
public:
    static int operate(State& state, int* address);
};

class PLD
{
public:
    static int operate(State& state, int* address);
};

class PLP
{
public:
    static int operate(State& state, int* address);
};

class PLX
{
public:
    static int operate(State& state, int* address);
};

class PLY
{
public:
    static int operate(State& state, int* address);
};

class REP
{
public:
    static int operate(State& state, int* address);
};

class ROL
{
public:
    static int operate(State& state, int* address);
};

class ROR
{
public:
    static int operate(State& state, int* address);
};

class RTI
{
public:
    static int operate(State& state, int* address);
};

class RTL
{
public:
    static int operate(State& state, int* address);
};

class RTS
{
public:
    static int operate(State& state, int* address);
};

class SBC
{
public:
    static int operate(State& state, int* address);
};

class SEC
{
public:
    static int operate(State& state, int* address);
};

class SED
{
public:
    static int operate(State& state, int* address);
};

class SEI
{
public:
    static int operate(State& state, int* address);
};

class SEP
{
public:
    static int operate(State& state, int* address);
};

class STA
{
public:
    static int operate(State& state, int* address);
};

class STP
{
public:
    static int operate(State& state, int* address);
};

class STX
{
public:
    static int operate(State& state, int* address);
};

class STY
{
public:
    static int operate(State& state, int* address);
};

class STZ
{
public:
    static int operate(State& state, int* address);
};

class TAX
{
public:
    static int operate(State& state, int* address);
};

class TAY
{
public:
    static int operate(State& state, int* address);
};

class TCD
{
public:
    static int operate(State& state, int* address);
};

class TCS
{
public:
    static int operate(State& state, int* address);
};

class TDC
{
public:
    static int operate(State& state, int* address);
};

class TRB
{
public:
    static int operate(State& state, int* address);
};

class TSB
{
public:
    static int operate(State& state, int* address);
};

class TSC
{
public:
    static int operate(State& state, int* address);
};

class TSX
{
public:
    static int operate(State& state, int* address);
};

class TXA
{
public:
    static int operate(State& state, int* address);
};

class TXS
{
public:
    static int operate(State& state, int* address);
};

class TXY
{
public:
    static int operate(State& state, int* address);
};

class TYA
{
public:
    static int operate(State& state, int* address);
};

class TYX
{
public:
    static int operate(State& state, int* address);
};

class WAI
{
public:
    static int operate(State& state, int* address);
};

class WDM
{
public:
    static int operate(State& state, int* address);
};

class XBA
{
public:
    static int operate(State& state, int* address);
};

class XCE
{
public:
    static int operate(State& state, int* address);
};

}
