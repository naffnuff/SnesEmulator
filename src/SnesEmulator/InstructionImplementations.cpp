#include "InstructionImplementations.h"

// ADC Add With Carry [Flags affected: n,v,z,c]

// ADC (dp,X)
// Direct Page Indexed Indirect,X
int ADC_61::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// ADC sr,S
// Stack Relative
int ADC_63::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// ADC dp
// Direct Page
int ADC_65::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// ADC [dp]
// Direct Page Indirect Long
int ADC_67::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// ADC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int ADC_69::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// ADC addr
// Absolute
int ADC_6D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// ADC long
// Absolute Long
int ADC_6F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// ADC (dp),Y
// Direct Page Indirect Indexed, Y
int ADC_71::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO03 */ /* TODO04 */;
}

// ADC (dp)
// Direct Page Indirect
int ADC_72::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// ADC (sr,S),Y
// Stack Relative Indirect Indexed,Y
int ADC_73::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// ADC dp,X
// Direct Page Indexed,X
int ADC_75::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// ADC [dp],Y
// Direct Page Indirect Long Indexed, Y
int ADC_77::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// ADC addr,Y
// Absolute Indexed,Y
int ADC_79::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */ /* TODO04 */;
}

// ADC addr,X
// Absolute Indexed,X
int ADC_7D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */ /* TODO04 */;
}

// ADC long,X
// Absolute Long Indexed,X
int ADC_7F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// AND AND Accumulator With Memory [Flags affected: n,z]

// AND (dp,X)
// Direct Page Indexed Indirect,X
int AND_21::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// AND sr,S
// Stack Relative
int AND_23::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// AND dp
// Direct Page
int AND_25::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// AND [dp]
// Direct Page Indirect Long
int AND_27::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// AND #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int AND_29::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// AND addr
// Absolute
int AND_2D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// AND long
// Absolute Long
int AND_2F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// AND (dp),Y
// Direct Page Indirect Indexed, Y
int AND_31::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO03 */;
}

// AND (dp)
// Direct Page Indirect
int AND_32::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// AND (sr,S),Y
// Stack Relative Indirect Indexed,Y
int AND_33::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// AND dp,X
// Direct Page Indexed,X
int AND_35::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// AND [dp],Y
// Direct Page Indirect Long Indexed, Y
int AND_37::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// AND addr,Y
// Absolute Indexed,Y
int AND_39::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// AND addr,X
// Absolute Indexed,X
int AND_3D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// AND long,X
// Absolute Long Indexed,X
int AND_3F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]

// ASL dp
// Direct Page
int ASL_06::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ASL A
// Accumulator
int ASL_0A::calculateCycles(const State& state) const
{
    return 2;
}

// ASL addr
// Absolute
int ASL_0E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ASL dp,X
// Direct Page Indexed,X
int ASL_16::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ASL addr,X
// Absolute Indexed,X
int ASL_1E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    // 6: Subtract 1 cycle if 65C02 and no page boundary crossed
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */ /* TODO06 */;
}

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]

// BCC nearlabel
// Program Counter Relative
int BCC_90::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]

// BCS nearlabel
// Program Counter Relative
int BCS_B0::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// BEQ Branch if Equal [Flags affected: none]

// BEQ nearlabel
// Program Counter Relative
int BEQ_F0::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]

// BIT dp
// Direct Page
int BIT_24::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// BIT addr
// Absolute
int BIT_2C::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// BIT dp,X
// Direct Page Indexed,X
int BIT_34::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// BIT addr,X
// Absolute Indexed,X
int BIT_3C::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// BIT #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int BIT_89::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// BMI Branch if Minus [Flags affected: none]

// BMI nearlabel
// Program Counter Relative
int BMI_30::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// BNE Branch if Not Equal [Flags affected: none]

// BNE nearlabel
// Program Counter Relative
int BNE_D0::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// BPL Branch if Plus [Flags affected: none]

// BPL nearlabel
// Program Counter Relative
int BPL_10::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// BRA Branch Always [Flags affected: none]

// BRA nearlabel
// Program Counter Relative
int BRA_80::calculateCycles(const State& state) const
{
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 3 /* TODO08 */;
}

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]

// BRK
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
int BRK_00::calculateCycles(const State& state) const
{
    // 9: Add 1 cycle for 65816 native mode(e = 0)
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO09 */;
}

// BRL Branch Long Always [Flags affected: none]

// BRL label
// Program Counter Relative Long
int BRL_82::calculateCycles(const State& state) const
{
    return 4;
}

// BVC Branch if Overflow Clear [Flags affected: none]

// BVC nearlabel
// Program Counter Relative
int BVC_50::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// BVS Branch if Overflow Set [Flags affected: none]

// BVS nearlabel
// Program Counter Relative
int BVS_70::calculateCycles(const State& state) const
{
    // 7: Add 1 cycle if branch is taken
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    return 2 /* TODO07 */ /* TODO08 */;
}

// CLC Clear Carry [Flags affected: c]

// CLC
// Implied
int CLC_18::calculateCycles(const State& state) const
{
    return 2;
}

// CLD Clear Decimal Mode Flag [Flags affected: d]

// CLD
// Implied
int CLD_D8::calculateCycles(const State& state) const
{
    return 2;
}

// CLI Clear Interrupt Disable Flag [Flags affected: i]

// CLI
// Implied
int CLI_58::calculateCycles(const State& state) const
{
    return 2;
}

// CLV Clear Overflow Flag [Flags affected: v]

// CLV
// Implied
int CLV_B8::calculateCycles(const State& state) const
{
    return 2;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]

// CMP (dp,X)
// Direct Page Indexed Indirect,X
int CMP_C1::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// CMP sr,S
// Stack Relative
int CMP_C3::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// CMP dp
// Direct Page
int CMP_C5::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// CMP [dp]
// Direct Page Indirect Long
int CMP_C7::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// CMP #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int CMP_C9::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// CMP addr
// Absolute
int CMP_CD::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// CMP long
// Absolute Long
int CMP_CF::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// CMP (dp),Y
// Direct Page Indirect Indexed, Y
int CMP_D1::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO03 */;
}

// CMP (dp)
// Direct Page Indirect
int CMP_D2::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// CMP (sr,S),Y
// Stack Relative Indirect Indexed,Y
int CMP_D3::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// CMP dp,X
// Direct Page Indexed,X
int CMP_D5::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// CMP [dp],Y
// Direct Page Indirect Long Indexed, Y
int CMP_D7::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// CMP addr,Y
// Absolute Indexed,Y
int CMP_D9::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// CMP addr,X
// Absolute Indexed,X
int CMP_DD::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// CMP long,X
// Absolute Long Indexed,X
int CMP_DF::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// COP Co-Processor Enable [Flags affected: d,i]

// COP const
// Stack/Interrupt
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
int COP_02::calculateCycles(const State& state) const
{
    // 9: Add 1 cycle for 65816 native mode(e = 0)
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO09 */;
}

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]

// CPX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
int CPX_E0::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 2 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// CPX dp
// Direct Page
int CPX_E4::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// CPX addr
// Absolute
int CPX_EC::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]

// CPY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
int CPY_C0::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 2 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// CPY dp
// Direct Page
int CPY_C4::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// CPY addr
// Absolute
int CPY_CC::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// DEC Decrement [Flags affected: n,z]

// DEC A
// Accumulator
int DEC_3A::calculateCycles(const State& state) const
{
    return 2;
}

// DEC dp
// Direct Page
int DEC_C6::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// DEC addr
// Absolute
int DEC_CE::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// DEC dp,X
// Direct Page Indexed,X
int DEC_D6::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// DEC addr,X
// Absolute Indexed,X
int DEC_DE::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    // 6: Subtract 1 cycle if 65C02 and no page boundary crossed
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */ /* TODO06 */;
}

// DEX Decrement Index Register X [Flags affected: n,z]

// DEX
// Implied
int DEX_CA::calculateCycles(const State& state) const
{
    return 2;
}

// DEY Decrement Index Register Y [Flags affected: n,z]

// DEY
// Implied
int DEY_88::calculateCycles(const State& state) const
{
    return 2;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]

// EOR (dp,X)
// Direct Page Indexed Indirect,X
int EOR_41::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// EOR sr,S
// Stack Relative
int EOR_43::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// EOR dp
// Direct Page
int EOR_45::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// EOR [dp]
// Direct Page Indirect Long
int EOR_47::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// EOR #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int EOR_49::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// EOR addr
// Absolute
int EOR_4D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// EOR long
// Absolute Long
int EOR_4F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// EOR (dp),Y
// Direct Page Indirect Indexed, Y
int EOR_51::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO03 */;
}

// EOR (dp)
// Direct Page Indirect
int EOR_52::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// EOR (sr,S),Y
// Stack Relative Indirect Indexed,Y
int EOR_53::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// EOR dp,X
// Direct Page Indexed,X
int EOR_55::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// EOR [dp],Y
// Direct Page Indirect Long Indexed, Y
int EOR_57::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// EOR addr,Y
// Absolute Indexed,Y
int EOR_59::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// EOR addr,X
// Absolute Indexed,X
int EOR_5D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// EOR long,X
// Absolute Long Indexed,X
int EOR_5F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// INC Increment [Flags affected: n,z]

// INC A
// Accumulator
int INC_1A::calculateCycles(const State& state) const
{
    return 2;
}

// INC dp
// Direct Page
int INC_E6::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// INC addr
// Absolute
int INC_EE::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// INC dp,X
// Direct Page Indexed,X
int INC_F6::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// INC addr,X
// Absolute Indexed,X
int INC_FE::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    // 6: Subtract 1 cycle if 65C02 and no page boundary crossed
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */ /* TODO06 */;
}

// INX Increment Index Register X [Flags affected: n,z]

// INX
// Implied
int INX_E8::calculateCycles(const State& state) const
{
    return 2;
}

// INY Increment Index Register Y [Flags affected: n,z]

// INY
// Implied
int INY_C8::calculateCycles(const State& state) const
{
    return 2;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]

// JMP addr
// Absolute
int JMP_4C::calculateCycles(const State& state) const
{
    return 3;
}

// JMP long
// Absolute Long
int JMP_5C::calculateCycles(const State& state) const
{
    return 4;
}

// JMP (addr)
// Absolute Indirect
int JMP_6C::calculateCycles(const State& state) const
{
    // 11: Add 1 cycle if 65C02
    // 12: 6502: Yields incorrect results if low byte of operand is $FF(i.e., operand is $xxFF)
    return 5 /* TODO11 */ /* TODO12 */;
}

// JMP (addr,X)
// Absolute Indexed Indirect
int JMP_7C::calculateCycles(const State& state) const
{
    return 6;
}

// JMP [addr]
// Absolute Indirect Long
int JMP_DC::calculateCycles(const State& state) const
{
    return 6;
}

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]

// JSR addr
// Absolute
int JSR_20::calculateCycles(const State& state) const
{
    return 6;
}

// JSR long
// Absolute Long
int JSR_22::calculateCycles(const State& state) const
{
    return 8;
}

// JSR (addr,X)
// Absolute Indexed Indirect
int JSR_FC::calculateCycles(const State& state) const
{
    return 8;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]

// LDA (dp,X)
// Direct Page Indexed Indirect,X
int LDA_A1::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// LDA sr,S
// Stack Relative
int LDA_A3::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// LDA dp
// Direct Page
int LDA_A5::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// LDA [dp]
// Direct Page Indirect Long
int LDA_A7::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// LDA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int LDA_A9::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// LDA addr
// Absolute
int LDA_AD::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// LDA long
// Absolute Long
int LDA_AF::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// LDA (dp),Y
// Direct Page Indirect Indexed, Y
int LDA_B1::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO03 */;
}

// LDA (dp)
// Direct Page Indirect
int LDA_B2::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// LDA (sr,S),Y
// Stack Relative Indirect Indexed,Y
int LDA_B3::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// LDA dp,X
// Direct Page Indexed,X
int LDA_B5::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// LDA [dp],Y
// Direct Page Indirect Long Indexed, Y
int LDA_B7::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// LDA addr,Y
// Absolute Indexed,Y
int LDA_B9::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// LDA addr,X
// Absolute Indexed,X
int LDA_BD::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// LDA long,X
// Absolute Long Indexed,X
int LDA_BF::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]

// LDX #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
int LDX_A2::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 2 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDX dp
// Direct Page
int LDX_A6::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDX addr
// Absolute
int LDX_AE::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDX dp,Y
// Direct Page Indexed,Y
int LDX_B6::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDX addr,Y
// Absolute Indexed,Y
int LDX_BE::calculateCycles(const State& state) const
{
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 /* TODO03 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]

// LDY #const
// Immediate
// 19: Add 1 byte if x = 0 (16 - bit index registers)
int LDY_A0::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 2 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDY dp
// Direct Page
int LDY_A4::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDY addr
// Absolute
int LDY_AC::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDY dp,X
// Direct Page Indexed,X
int LDY_B4::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LDY addr,X
// Absolute Indexed,X
int LDY_BC::calculateCycles(const State& state) const
{
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 /* TODO03 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]

// LSR dp
// Direct Page
int LSR_46::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// LSR A
// Accumulator
int LSR_4A::calculateCycles(const State& state) const
{
    return 2;
}

// LSR addr
// Absolute
int LSR_4E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// LSR dp,X
// Direct Page Indexed,X
int LSR_56::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// LSR addr,X
// Absolute Indexed,X
int LSR_5E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    // 6: Subtract 1 cycle if 65C02 and no page boundary crossed
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */ /* TODO06 */;
}

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]

// MVN srcbk,destbk
// Block Move
int MVN_54::calculateCycles(const State& state) const
{
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 1 /* TODO03 */;
}

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]

// MVN srcbk,destbk
// Block Move
int MVN_44::calculateCycles(const State& state) const
{
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 1 /* TODO03 */;
}

// NOP No Operation [Flags affected: none]

// NOP
// Implied
int NOP_EA::calculateCycles(const State& state) const
{
    return 2;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]

// ORA (dp,X)
// Direct Page Indexed Indirect,X
int ORA_01::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// ORA sr,S
// Stack Relative
int ORA_03::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// ORA dp
// Direct Page
int ORA_05::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// ORA [dp]
// Direct Page Indirect Long
int ORA_07::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// ORA #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int ORA_09::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// ORA addr
// Absolute
int ORA_0D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// ORA long
// Absolute Long
int ORA_0F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// ORA (dp),Y
// Direct Page Indirect Indexed, Y
int ORA_11::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO03 */;
}

// ORA (dp)
// Direct Page Indirect
int ORA_12::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// ORA (sr,S),Y
// Stack Relative Indirect Indexed,Y
int ORA_13::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// ORA dp,X
// Direct Page Indexed,X
int ORA_15::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// ORA [dp],Y
// Direct Page Indirect Long Indexed, Y
int ORA_17::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// ORA addr,Y
// Absolute Indexed,Y
int ORA_19::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// ORA addr,X
// Absolute Indexed,X
int ORA_1D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */;
}

// ORA long,X
// Absolute Long Indexed,X
int ORA_1F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// PEA Push Effective Absolute Address [Flags affected: none]

// PEA addr
// Stack (Absolute)
int PEA_F4::calculateCycles(const State& state) const
{
    return 5;
}

// PEI Push Effective Indirect Address [Flags affected: none]

// PEI (dp)
// Stack (Direct Page Indirect)
int PEI_D4::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 /* TODO02 */;
}

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]

// PER label
// Stack (Program Counter Relative Long)
int PER_62::calculateCycles(const State& state) const
{
    return 6;
}

// PHA Push Accumulator [Flags affected: none]

// PHA
// Stack (Push)
int PHA_48::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// PHB Push Data Bank Register [Flags affected: none]

// PHB
// Stack (Push)
int PHB_8B::calculateCycles(const State& state) const
{
    return 3;
}

// PHD Push Direct Page Register [Flags affected: none]

// PHD
// Stack (Push)
int PHD_0B::calculateCycles(const State& state) const
{
    return 4;
}

// PHK Push Program Bank Register [Flags affected: none]

// PHK
// Stack (Push)
int PHK_4B::calculateCycles(const State& state) const
{
    return 3;
}

// PHP Push Processor Status Register [Flags affected: none]

// PHP
// Stack (Push)
int PHP_08::calculateCycles(const State& state) const
{
    return 3;
}

// PHX Push Index Register X [Flags affected: none]

// PHX
// Stack (Push)
int PHX_DA::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// PHY Push Index Register Y [Flags affected: none]

// PHY
// Stack (Push)
int PHY_5A::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// PLA Pull Accumulator [Flags affected: n,z]

// PLA
// Stack (Pull)
int PLA_68::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// PLB Pull Data Bank Register [Flags affected: n,z]

// PLB
// Stack (Pull)
int PLB_AB::calculateCycles(const State& state) const
{
    return 4;
}

// PLD Pull Direct Page Register [Flags affected: n,z]

// PLD
// Stack (Pull)
int PLD_2B::calculateCycles(const State& state) const
{
    return 5;
}

// PLP Pull Processor Status Register [Flags affected: n,z]

// PLP
// Stack (Pull)
int PLP_28::calculateCycles(const State& state) const
{
    return 4;
}

// PLX Pull Index Register X [Flags affected: n,z]

// PLX
// Stack (Pull)
int PLX_FA::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// PLY Pull Index Register Y [Flags affected: n,z]

// PLY
// Stack (Pull)
int PLY_7A::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// REP Reset Processor Status Bits [Flags affected: all except b per operand]

// REP #const
// Immediate
int REP_C2::calculateCycles(const State& state) const
{
    return 3;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]

// ROL dp
// Direct Page
int ROL_26::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ROL A
// Accumulator
int ROL_2A::calculateCycles(const State& state) const
{
    return 2;
}

// ROL addr
// Absolute
int ROL_2E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ROL dp,X
// Direct Page Indexed,X
int ROL_36::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ROL addr,X
// Absolute Indexed,X
int ROL_3E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    // 6: Subtract 1 cycle if 65C02 and no page boundary crossed
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */ /* TODO06 */;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]

// ROR dp
// Direct Page
int ROR_66::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ROR A
// Accumulator
int ROR_6A::calculateCycles(const State& state) const
{
    return 2;
}

// ROR addr
// Absolute
int ROR_6E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ROR dp,X
// Direct Page Indexed,X
int ROR_76::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// ROR addr,X
// Absolute Indexed,X
int ROR_7E::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    // 6: Subtract 1 cycle if 65C02 and no page boundary crossed
    return 7 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */ /* TODO06 */;
}

// RTI Return from Interrupt [Flags affected: all except b]

// RTI
// Stack (RTI)
int RTI_40::calculateCycles(const State& state) const
{
    // 9: Add 1 cycle for 65816 native mode(e = 0)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO09 */;
}

// RTL Return from Subroutine Long [Flags affected: none]

// RTL
// Stack (RTL)
int RTL_6B::calculateCycles(const State& state) const
{
    return 6;
}

// RTS Return from Subroutine [Flags affected: none]

// RTS
// Stack (RTS)
int RTS_60::calculateCycles(const State& state) const
{
    return 6;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]

// SBC (dp,X)
// Direct Page Indexed Indirect,X
int SBC_E1::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// SBC sr,S
// Stack Relative
int SBC_E3::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// SBC dp
// Direct Page
int SBC_E5::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// SBC [dp]
// Direct Page Indirect Long
int SBC_E7::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// SBC #const
// Immediate
// 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
int SBC_E9::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 2 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// SBC addr
// Absolute
int SBC_ED::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// SBC long
// Absolute Long
int SBC_EF::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// SBC (dp),Y
// Direct Page Indirect Indexed, Y
int SBC_F1::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO03 */ /* TODO04 */;
}

// SBC (dp)
// Direct Page Indirect
int SBC_F2::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// SBC (sr,S),Y
// Stack Relative Indirect Indexed,Y
int SBC_F3::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// SBC dp,X
// Direct Page Indexed,X
int SBC_F5::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// SBC [dp],Y
// Direct Page Indirect Long Indexed, Y
int SBC_F7::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */ /* TODO04 */;
}

// SBC addr,Y
// Absolute Indexed,Y
int SBC_F9::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */ /* TODO04 */;
}

// SBC addr,X
// Absolute Indexed,X
int SBC_FD::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 3: Add 1 cycle if adding index crosses a page boundary
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO03 */ /* TODO04 */;
}

// SBC long,X
// Absolute Long Indexed,X
int SBC_FF::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO04 */;
}

// SEC Set Carry Flag [Flags affected: c]

// SEC
// Implied
int SEC_38::calculateCycles(const State& state) const
{
    return 2;
}

// SED Set Decimal Flag [Flags affected: d]

// SED
// Implied
int SED_F8::calculateCycles(const State& state) const
{
    return 2;
}

// SEI Set Interrupt Disable Flag [Flags affected: i]

// SEI
// Implied
int SEI_78::calculateCycles(const State& state) const
{
    return 2;
}

// SEP Set Processor Status Bits [Flags affected: all except b per operand]

// SEP #const
// Immediate
int SEP_E2::calculateCycles(const State& state) const
{
    return 3;
}

// STA Store Accumulator to Memory [Flags affected: none]

// STA (dp,X)
// Direct Page Indexed Indirect,X
int STA_81::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STA sr,S
// Stack Relative
int STA_83::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STA dp
// Direct Page
int STA_85::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STA [dp]
// Direct Page Indirect Long
int STA_87::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STA addr
// Absolute
int STA_8D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STA long
// Absolute Long
int STA_8F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STA (dp),Y
// Direct Page Indirect Indexed, Y
int STA_91::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STA (dp)
// Direct Page Indirect
int STA_92::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STA (sr,S),Y
// Stack Relative Indirect Indexed,Y
int STA_93::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 7 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STA dp,X
// Direct Page Indexed,X
int STA_95::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STA [dp],Y
// Direct Page Indirect Long Indexed, Y
int STA_97::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 6 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STA addr,Y
// Absolute Indexed,Y
int STA_99::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STA addr,X
// Absolute Indexed,X
int STA_9D::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STA long,X
// Absolute Long Indexed,X
int STA_9F::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STP Stop Processor [Flags affected: none]

// STP
// Implied
int STP_DB::calculateCycles(const State& state) const
{
    // 14: Uses 3 cycles to shut the processor down : additional cycles are required by reset to restart it
    return 3 /* TODO14 */;
}

// STX Store Index Register X to Memory [Flags affected: none]

// STX dp
// Direct Page
int STX_86::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// STX addr
// Absolute
int STX_8E::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// STX dp,Y
// Direct Page Indexed,Y
int STX_96::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// STY Store Index Register Y to Memory [Flags affected: none]

// STY dp
// Direct Page
int STY_84::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 3 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// STY addr
// Absolute
int STY_8C::calculateCycles(const State& state) const
{
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// STY dp,X
// Direct Page Indexed,X
int STY_94::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 10: Add 1 cycle if x = 0 (16 - bit index registers)
    return 4 /* TODO02 */ + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */;
}

// STZ Store Zero to Memory [Flags affected: none]

// STZ dp
// Direct Page
int STZ_64::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 3 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STZ dp,X
// Direct Page Indexed,X
int STZ_74::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/ /* TODO02 */;
}

// STZ addr
// Absolute
int STZ_9C::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 4 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// STZ addr,X
// Absolute Indexed,X
int STZ_9E::calculateCycles(const State& state) const
{
    // 1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    return 5 + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/;
}

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]

// TAX
// Implied
int TAX_AA::calculateCycles(const State& state) const
{
    return 2;
}

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]

// TAY
// Implied
int TAY_A8::calculateCycles(const State& state) const
{
    return 2;
}

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]

// TCD
// Implied
int TCD_5B::calculateCycles(const State& state) const
{
    return 2;
}

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]

// TCS
// Implied
int TCS_1B::calculateCycles(const State& state) const
{
    return 2;
}

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]

// TDC
// Implied
int TDC_7B::calculateCycles(const State& state) const
{
    return 2;
}

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]

// TRB dp
// Direct Page
int TRB_14::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// TRB addr
// Absolute
int TRB_1C::calculateCycles(const State& state) const
{
    // 3: Add 1 cycle if adding index crosses a page boundary
    return 6 /* TODO03 */;
}

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]

// TSB dp
// Direct Page
int TSB_04::calculateCycles(const State& state) const
{
    // 2: Add 1 cycle if low byte of Direct Page Register is non - zero
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 5 /* TODO02 */ + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// TSB addr
// Absolute
int TSB_0C::calculateCycles(const State& state) const
{
    // 5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)
    return 6 + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */;
}

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]

// TSC
// Implied
int TSC_3B::calculateCycles(const State& state) const
{
    return 2;
}

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]

// TSX
// Implied
int TSX_BA::calculateCycles(const State& state) const
{
    return 2;
}

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]

// TXA
// Implied
int TXA_8A::calculateCycles(const State& state) const
{
    return 2;
}

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]

// TXS
// Implied
int TXS_9A::calculateCycles(const State& state) const
{
    return 2;
}

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]

// TXY
// Implied
int TXY_9B::calculateCycles(const State& state) const
{
    return 2;
}

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]

// TYA
// Implied
int TYA_98::calculateCycles(const State& state) const
{
    return 2;
}

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]

// TYX
// Implied
int TYX_BB::calculateCycles(const State& state) const
{
    return 2;
}

// WAI Wait for Interrupt [Flags affected: none]

// WAI
// Implied
int WAI_CB::calculateCycles(const State& state) const
{
    // 15: Uses 3 cycles to shut the processor down : additional cycles are required by interrupt to restart it
    return 3 /* TODO15 */;
}

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]

// WDM
// n/a
// 16: Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths
int WDM_42::calculateCycles(const State& state) const
{
    // 16: Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths
    return 0 /* TODO16 */;
}

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]

// XBA
// Implied
int XBA_EB::calculateCycles(const State& state) const
{
    return 3;
}

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]

// XCE
// Implied
int XCE_FB::calculateCycles(const State& state) const
{
    return 2;
}

