#pragma once

#include <stdint.h>

#include "State.h"

#include "Instruction.h"

// ADC Add With Carry [Flags affected: n,v,z,c]

// ADC (dp,X)
// DP Indexed Indirect,X
class ADC_61 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC sr,S
// Stack Relative
class ADC_63 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC dp
// Direct Page
class ADC_65 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC [dp]
// DP Indirect Long
class ADC_67 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class ADC_69 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// ADC addr
// Absolute
class ADC_6D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ADC long
// Absolute Long
class ADC_6F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// ADC (dp),Y
// DP Indirect Indexed, Y
class ADC_71 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC (dp)
// DP Indirect
class ADC_72 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC (sr,S),Y
// SR Indirect Indexed,Y
class ADC_73 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC dp,X
// DP Indexed,X
class ADC_75 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC [dp],Y
// DP Indirect Long Indexed, Y
class ADC_77 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ADC addr,Y
// Absolute Indexed,Y
class ADC_79 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ADC addr,X
// Absolute Indexed,X
class ADC_7D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ADC long,X
// Absolute Long Indexed,X
class ADC_7F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// AND AND Accumulator With Memory [Flags affected: n,z]

// AND (dp,X)
// DP Indexed Indirect,X
class AND_21 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND sr,S
// Stack Relative
class AND_23 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND dp
// Direct Page
class AND_25 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND [dp]
// DP Indirect Long
class AND_27 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class AND_29 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// AND addr
// Absolute
class AND_2D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// AND long
// Absolute Long
class AND_2F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// AND (dp),Y
// DP Indirect Indexed, Y
class AND_31 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND (dp)
// DP Indirect
class AND_32 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND (sr,S),Y
// SR Indirect Indexed,Y
class AND_33 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND dp,X
// DP Indexed,X
class AND_35 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND [dp],Y
// DP Indirect Long Indexed, Y
class AND_37 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// AND addr,Y
// Absolute Indexed,Y
class AND_39 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// AND addr,X
// Absolute Indexed,X
class AND_3D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// AND long,X
// Absolute Long Indexed,X
class AND_3F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]

// ASL dp
// Direct Page
class ASL_06 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ASL A
// Accumulator
class ASL_0A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// ASL addr
// Absolute
class ASL_0E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ASL dp,X
// DP Indexed,X
class ASL_16 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ASL addr,X
// Absolute Indexed,X
class ASL_1E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]

// BCC nearlabel
// Program Counter Relative
class BCC_90 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]

// BCS nearlabel
// Program Counter Relative
class BCS_B0 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BEQ Branch if Equal [Flags affected: none]

// BEQ nearlabel
// Program Counter Relative
class BEQ_F0 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]

// BIT dp
// Direct Page
class BIT_24 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BIT addr
// Absolute
class BIT_2C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// BIT dp,X
// DP Indexed,X
class BIT_34 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BIT addr,X
// Absolute Indexed,X
class BIT_3C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// BIT #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class BIT_89 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// BMI Branch if Minus [Flags affected: none]

// BMI nearlabel
// Program Counter Relative
class BMI_30 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BNE Branch if Not Equal [Flags affected: none]

// BNE nearlabel
// Program Counter Relative
class BNE_D0 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BPL Branch if Plus [Flags affected: none]

// BPL nearlabel
// Program Counter Relative
class BPL_10 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BRA Branch Always [Flags affected: none]

// BRA nearlabel
// Program Counter Relative
class BRA_80 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]

// BRK
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class BRK_00 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BRL Branch Long Always [Flags affected: none]

// BRL label
// Program Counter Relative Long
class BRL_82 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// BVC Branch if Overflow Clear [Flags affected: none]

// BVC nearlabel
// Program Counter Relative
class BVC_50 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// BVS Branch if Overflow Set [Flags affected: none]

// BVS nearlabel
// Program Counter Relative
class BVS_70 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CLC Clear Carry [Flags affected: c]

// CLC
// Implied
class CLC_18 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// CLD Clear Decimal Mode Flag [Flags affected: d]

// CLD
// Implied
class CLD_D8 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// CLI Clear Interrupt Disable Flag [Flags affected: i]

// CLI
// Implied
class CLI_58 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// CLV Clear Overflow Flag [Flags affected: v]

// CLV
// Implied
class CLV_B8 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]

// CMP (dp,X)
// DP Indexed Indirect,X
class CMP_C1 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP sr,S
// Stack Relative
class CMP_C3 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP dp
// Direct Page
class CMP_C5 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP [dp]
// DP Indirect Long
class CMP_C7 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class CMP_C9 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// CMP addr
// Absolute
class CMP_CD : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// CMP long
// Absolute Long
class CMP_CF : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// CMP (dp),Y
// DP Indirect Indexed, Y
class CMP_D1 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP (dp)
// DP Indirect
class CMP_D2 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP (sr,S),Y
// SR Indirect Indexed,Y
class CMP_D3 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP dp,X
// DP Indexed,X
class CMP_D5 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP [dp],Y
// DP Indirect Long Indexed, Y
class CMP_D7 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CMP addr,Y
// Absolute Indexed,Y
class CMP_D9 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// CMP addr,X
// Absolute Indexed,X
class CMP_DD : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// CMP long,X
// Absolute Long Indexed,X
class CMP_DF : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// COP Co-Processor Enable [Flags affected: d,i]

// COP const
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
class COP_02 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]

// CPX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class CPX_E0 : public InstructionFlagSize<State::x> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// CPX dp
// Direct Page
class CPX_E4 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CPX addr
// Absolute
class CPX_EC : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]

// CPY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class CPY_C0 : public InstructionFlagSize<State::x> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// CPY dp
// Direct Page
class CPY_C4 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// CPY addr
// Absolute
class CPY_CC : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// DEC Decrement [Flags affected: n,z]

// DEC A
// Accumulator
class DEC_3A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// DEC dp
// Direct Page
class DEC_C6 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// DEC addr
// Absolute
class DEC_CE : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// DEC dp,X
// DP Indexed,X
class DEC_D6 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// DEC addr,X
// Absolute Indexed,X
class DEC_DE : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// DEX Decrement Index Register X [Flags affected: n,z]

// DEX
// Implied
class DEX_CA : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// DEY Decrement Index Register Y [Flags affected: n,z]

// DEY
// Implied
class DEY_88 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]

// EOR (dp,X)
// DP Indexed Indirect,X
class EOR_41 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR sr,S
// Stack Relative
class EOR_43 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR dp
// Direct Page
class EOR_45 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR [dp]
// DP Indirect Long
class EOR_47 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class EOR_49 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// EOR addr
// Absolute
class EOR_4D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// EOR long
// Absolute Long
class EOR_4F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// EOR (dp),Y
// DP Indirect Indexed, Y
class EOR_51 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR (dp)
// DP Indirect
class EOR_52 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR (sr,S),Y
// SR Indirect Indexed,Y
class EOR_53 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR dp,X
// DP Indexed,X
class EOR_55 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR [dp],Y
// DP Indirect Long Indexed, Y
class EOR_57 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// EOR addr,Y
// Absolute Indexed,Y
class EOR_59 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// EOR addr,X
// Absolute Indexed,X
class EOR_5D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// EOR long,X
// Absolute Long Indexed,X
class EOR_5F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// INC Increment [Flags affected: n,z]

// INC A
// Accumulator
class INC_1A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// INC dp
// Direct Page
class INC_E6 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// INC addr
// Absolute
class INC_EE : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// INC dp,X
// DP Indexed,X
class INC_F6 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// INC addr,X
// Absolute Indexed,X
class INC_FE : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// INX Increment Index Register X [Flags affected: n,z]

// INX
// Implied
class INX_E8 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// INY Increment Index Register Y [Flags affected: n,z]

// INY
// Implied
class INY_C8 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]

// JMP addr
// Absolute
class JMP_4C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// JMP long
// Absolute Long
class JMP_5C : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// JMP (addr)
// Absolute Indirect
class JMP_6C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// JMP (addr,X)
// Absolute Indexed Indirect
class JMP_7C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// JMP [addr]
// Absolute Indirect Long
class JMP_DC : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]

// JSR addr
// Absolute
class JSR_20 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// JSR long
// Absolute Long
class JSR_22 : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// JSR (addr,X))
// Absolute Indexed Indirect
class JSR_FC : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDA Load Accumulator from Memory [Flags affected: n,z]

// LDA (dp,X)
// DP Indexed Indirect,X
class LDA_A1 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA sr,S
// Stack Relative
class LDA_A3 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA dp
// Direct Page
class LDA_A5 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA [dp]
// DP Indirect Long
class LDA_A7 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class LDA_A9 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDA addr
// Absolute
class LDA_AD : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDA long
// Absolute Long
class LDA_AF : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// LDA (dp),Y
// DP Indirect Indexed, Y
class LDA_B1 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA (dp)
// DP Indirect
class LDA_B2 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA (sr,S),Y
// SR Indirect Indexed,Y
class LDA_B3 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA dp,X
// DP Indexed,X
class LDA_B5 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA [dp],Y
// DP Indirect Long Indexed, Y
class LDA_B7 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDA addr,Y
// Absolute Indexed,Y
class LDA_B9 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDA addr,X
// Absolute Indexed,X
class LDA_BD : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDA long,X
// Absolute Long Indexed,X
class LDA_BF : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// LDX Load Index Register X from Memory [Flags affected: n,z]

// LDX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class LDX_A2 : public InstructionFlagSize<State::x> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDX dp
// Direct Page
class LDX_A6 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDX addr
// Absolute
class LDX_AE : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDX dp,Y
// DP Indexed,Y
class LDX_B6 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDX addr,Y
// Absolute Indexed,Y
class LDX_BE : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDY Load Index Register Y from Memory [Flags affected: n,z]

// LDY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
class LDY_A0 : public InstructionFlagSize<State::x> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDY dp
// Direct Page
class LDY_A4 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDY addr
// Absolute
class LDY_AC : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LDY dp,X
// DP Indexed,X
class LDY_B4 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LDY addr,X
// Absolute Indexed,X
class LDY_BC : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]

// LSR dp
// Direct Page
class LSR_46 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LSR A
// Accumulator
class LSR_4A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// LSR addr
// Absolute
class LSR_4E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// LSR dp,X
// DP Indexed,X
class LSR_56 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// LSR addr,X
// Absolute Indexed,X
class LSR_5E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]

// MVN srcbk,destbk
// Block Move
class MVN_54 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]

// MVN srcbk,destbk
// Block Move
class MVN_44 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// NOP No Operation [Flags affected: none]

// NOP
// Implied
class NOP_EA : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// ORA OR Accumulator with Memory [Flags affected: n,z]

// ORA (dp,X)
// DP Indexed Indirect,X
class ORA_01 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA sr,S
// Stack Relative
class ORA_03 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA dp
// Direct Page
class ORA_05 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA [dp]
// DP Indirect Long
class ORA_07 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class ORA_09 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// ORA addr
// Absolute
class ORA_0D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ORA long
// Absolute Long
class ORA_0F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// ORA (dp),Y
// DP Indirect Indexed, Y
class ORA_11 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA (dp)
// DP Indirect
class ORA_12 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA (sr,S),Y
// SR Indirect Indexed,Y
class ORA_13 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA dp,X
// DP Indexed,X
class ORA_15 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA [dp],Y
// DP Indirect Long Indexed, Y
class ORA_17 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ORA addr,Y
// Absolute Indexed,Y
class ORA_19 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ORA addr,X
// Absolute Indexed,X
class ORA_1D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ORA long,X
// Absolute Long Indexed,X
class ORA_1F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// PEA Push Effective Absolute Address [Flags affected: none]

// PEA addr
// Stack (Absolute)
class PEA_F4 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// PEI Push Effective Indirect Address [Flags affected: none]

// PEI (dp)
// Stack (DP Indirect)
class PEI_D4 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// PER Push Effective PC Relative Indirect Address [Flags affected: none]

// PER label
// Stack (PC Relative Long)
class PER_62 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// PHA Push Accumulator [Flags affected: none]

// PHA
// Stack (Push)
class PHA_48 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PHB Push Data Bank Register [Flags affected: none]

// PHB
// Stack (Push)
class PHB_8B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PHD Push Direct Page Register [Flags affected: none]

// PHD
// Stack (Push)
class PHD_0B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PHK Push Program Bank Register [Flags affected: none]

// PHK
// Stack (Push)
class PHK_4B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PHP Push Processor Status Register [Flags affected: none]

// PHP
// Stack (Push)
class PHP_08 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PHX Push Index Register X [Flags affected: none]

// PHX
// Stack (Push)
class PHX_DA : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PHY Push Index Register Y [Flags affected: none]

// PHY
// Stack (Push)
class PHY_5A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PLA Pull Accumulator [Flags affected: n,z]

// PLA
// Stack (Pull)
class PLA_68 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PLB Pull Data Bank Register [Flags affected: n,z]

// PLB
// Stack (Pull)
class PLB_AB : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PLD Pull Direct Page Register [Flags affected: n,z]

// PLD
// Stack (Pull)
class PLD_2B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PLP Pull Processor Status Register [Flags affected: n,z]

// PLP
// Stack (Pull)
class PLP_28 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PLX Pull Index Register X [Flags affected: n,z]

// PLX
// Stack (Pull)
class PLX_FA : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// PLY Pull Index Register Y [Flags affected: n,z]

// PLY
// Stack (Pull)
class PLY_7A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// REP Reset Processor Status Bits [Flags affected: all except b per operand]

// REP #const
// Immediate
class REP_C2 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]

// ROL dp
// Direct Page
class ROL_26 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ROL A
// Accumulator
class ROL_2A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// ROL addr
// Absolute
class ROL_2E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ROL dp,X
// DP Indexed,X
class ROL_36 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ROL addr,X
// Absolute Indexed,X
class ROL_3E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]

// ROR dp
// Direct Page
class ROR_66 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ROR A
// Accumulator
class ROR_6A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// ROR addr
// Absolute
class ROR_6E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// ROR dp,X
// DP Indexed,X
class ROR_76 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// ROR addr,X
// Absolute Indexed,X
class ROR_7E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// RTI Return from Interrupt [Flags affected: all except b]

// RTI
// Stack (RTI)
class RTI_40 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// RTL Return from Subroutine Long [Flags affected: none]

// RTL
// Stack (RTL)
class RTL_6B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// RTS Return from Subroutine [Flags affected: none]

// RTS
// Stack (RTS)
class RTS_60 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]

// SBC (dp,X)
// DP Indexed Indirect,X
class SBC_E1 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC sr,S
// Stack Relative
class SBC_E3 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC dp
// Direct Page
class SBC_E5 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC [dp]
// DP Indirect Long
class SBC_E7 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
class SBC_E9 : public InstructionFlagSize<State::m> {
    using InstructionFlagSize::InstructionFlagSize;
public:
    int apply(State& state, uint16_t value) const override;
};

// SBC addr
// Absolute
class SBC_ED : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// SBC long
// Absolute Long
class SBC_EF : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// SBC (dp),Y
// DP Indirect Indexed, Y
class SBC_F1 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC (dp)
// DP Indirect
class SBC_F2 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC (sr,S),Y
// SR Indirect Indexed,Y
class SBC_F3 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC dp,X
// DP Indexed,X
class SBC_F5 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC [dp],Y
// DP Indirect Long Indexed, Y
class SBC_F7 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// SBC addr,Y
// Absolute Indexed,Y
class SBC_F9 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// SBC addr,X
// Absolute Indexed,X
class SBC_FD : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// SBC long,X
// Absolute Long Indexed,X
class SBC_FF : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// SEC Set Carry Flag [Flags affected: c]

// SEC
// Implied
class SEC_38 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// SED Set Decimal Flag [Flags affected: d]

// SED
// Implied
class SED_F8 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// SEI Set Interrupt Disable Flag [Flags affected: i]

// SEI
// Implied
class SEI_78 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// SEP Set Processor Status Bits [Flags affected: all except b per operand]

// SEP
// Immediate
class SEP_E2 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA Store Accumulator to Memory [Flags affected: none]

// STA (dp,X)
// DP Indexed Indirect,X
class STA_81 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA sr,S
// Stack Relative
class STA_83 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA dp
// Direct Page
class STA_85 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA [dp]
// DP Indirect Long
class STA_87 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA addr
// Absolute
class STA_8D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// STA long
// Absolute Long
class STA_8F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// STA (dp),Y
// DP Indirect Indexed, Y
class STA_91 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA (dp)
// DP Indirect
class STA_92 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA (sr,S),Y
// SR Indirect Indexed,Y
class STA_93 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA dpX
// DP Indexed,X
class STA_95 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA [dp],Y
// DP Indirect Long Indexed, Y
class STA_97 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STA addr,Y
// Absolute Indexed,Y
class STA_99 : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// STA addr,X
// Absolute Indexed,X
class STA_9D : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// STA long,X
// Absolute Long Indexed,X
class STA_9F : public Instruction4Byte {
    using Instruction4Byte::Instruction4Byte;
public:
    int apply(State& state, uint32_t value) const override;
};

// STP Stop Processor [Flags affected: none]

// STP
// Implied
class STP_DB : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// STX Store Index Register X to Memory [Flags affected: none]

// STX dp
// Direct Page
class STX_86 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STX addr
// Absolute
class STX_8E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// STX dp,Y
// DP Indexed,Y
class STX_96 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STY Store Index Register Y to Memory [Flags affected: none]

// STY dp
// Direct Page
class STY_84 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STY addr
// Absolute
class STY_8C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// STY dp,X
// DP Indexed,X
class STY_94 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STZ Store Zero to Memory [Flags affected: none]

// STZ dp
// Direct Page
class STZ_64 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STZ dp,X
// DP Indexed,X
class STZ_74 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// STZ addr
// Absolute
class STZ_9C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// STZ addr,X
// Absolute Indexed,X
class STZ_9E : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]

// TAX
// Implied
class TAX_AA : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]

// TAY
// Implied
class TAY_A8 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]

// TCD
// Implied
class TCD_5B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]

// TCS
// Implied
class TCS_1B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]

// TDC
// Implied
class TDC_7B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]

// TRB dp
// Direct Page
class TRB_14 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// TRB addr
// Absolute
class TRB_1C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]

// TSB dp
// Direct Page
class TSB_04 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// TSB addr
// Absolute
class TSB_0C : public Instruction3Byte {
    using Instruction3Byte::Instruction3Byte;
public:
    int apply(State& state, uint16_t value) const override;
};

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]

// TSC
// Implied
class TSC_3B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]

// TSX
// Implied
class TSX_BA : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]

// TXA
// Implied
class TXA_8A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]

// TXS
// Implied
class TXS_9A : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]

// TXY
// Implied
class TXY_9B : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]

// TYA
// Implied
class TYA_98 : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]

// TYX
// Implied
class TYX_BB : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// WAI Wait for Interrupt [Flags affected: none]

// WAI
// Implied
class WAI_CB : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]

// WDM
// n/a
// 16: Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths
class WDM_42 : public Instruction2Byte {
    using Instruction2Byte::Instruction2Byte;
public:
    int apply(State& state, uint8_t value) const override;
};

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]

// XBA
// Implied
class XBA_EB : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]

// XCE
// Implied
class XCE_FB : public Instruction1Byte {
    using Instruction1Byte::Instruction1Byte;
public:
    int apply(State& state) const override;
};

