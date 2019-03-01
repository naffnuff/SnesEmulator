#include "Opcode.h"

namespace Opcode {

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
int ADC_61::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   mm....mm . ADC ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC sr,S
// Stack Relative
// 2<>
int ADC_63::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     mm....mm . ADC $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp
// Direct Page
// 2<>
int ADC_65::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       mm....mm . ADC $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp]
// Direct Page Indirect Long
// 2<>
int ADC_67::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     mm....mm . ADC [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int ADC_69::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       mm....mm . ADC #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr
// Absolute
// 3<>
int ADC_6D::calculateCycles(const State& state) const
{
    // 3   5-m         abs       mm....mm . ADC $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long
// Absolute Long
// 4<>
int ADC_6F::calculateCycles(const State& state) const
{
    // 4   6-m         long      mm....mm . ADC $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int ADC_71::calculateCycles(const State& state) const
{
    // 2   7-m+w-x+x*p (dir),Y   mm....mm . ADC ($10),Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (dp)
// Direct Page Indirect
// 2<>
int ADC_72::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     mm....mm . ADC ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int ADC_73::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y mm....mm . ADC ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC dp,X
// Direct Page Indexed, X
// 2<>
int ADC_75::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     mm....mm . ADC $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int ADC_77::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   mm....mm . ADC [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,Y
// Absolute Indexed, Y
// 3<>
int ADC_79::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,Y     mm....mm . ADC $9876,Y
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC addr,X
// Absolute Indexed, X
// 3<>
int ADC_7D::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     mm....mm . ADC $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 
    return cycles;
}

// ADC Add With Carry [Flags affected: n,v,z,c]
// ADC long,X
// Absolute Long Indexed, X
// 4<>
int ADC_7F::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    mm....mm . ADC $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
int AND_21::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   m.....m. . AND ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND sr,S
// Stack Relative
// 2<>
int AND_23::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     m.....m. . AND $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp
// Direct Page
// 2<>
int AND_25::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       m.....m. . AND $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp]
// Direct Page Indirect Long
// 2<>
int AND_27::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     m.....m. . AND [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int AND_29::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       m.....m. . AND #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr
// Absolute
// 3<>
int AND_2D::calculateCycles(const State& state) const
{
    // 3   5-m         abs       m.....m. . AND $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long
// Absolute Long
// 4<>
int AND_2F::calculateCycles(const State& state) const
{
    // 4   6-m         long      m.....m. . AND $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int AND_31::calculateCycles(const State& state) const
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . AND ($10),Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (dp)
// Direct Page Indirect
// 2<>
int AND_32::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     m.....m. . AND ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int AND_33::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y m.....m. . AND ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND dp,X
// Direct Page Indexed, X
// 2<>
int AND_35::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     m.....m. . AND $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int AND_37::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   m.....m. . AND [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,Y
// Absolute Indexed, Y
// 3<>
int AND_39::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . AND $9876,Y
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND addr,X
// Absolute Indexed, X
// 3<>
int AND_3D::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     m.....m. . AND $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// AND AND Accumulator With Memory [Flags affected: n,z]
// AND long,X
// Absolute Long Indexed, X
// 4<>
int AND_3F::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    m.....m. . AND $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp
// Direct Page
// 2<>
int ASL_06::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       m.....mm . ASL $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL A
// Accumulator
// 1<>
int ASL_0A::calculateCycles(const State& state) const
{
    // 1   2           acc       m.....mm . ASL
    int cycles = 2;
    return cycles;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr
// Absolute
// 3<>
int ASL_0E::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       m.....mm . ASL $9876
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL dp,X
// Direct Page Indexed, X
// 2<>
int ASL_16::calculateCycles(const State& state) const
{
    // 2   8-2*m+w     dir,X     m.....mm . ASL $10,X
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ASL Accumulator or Memory Shift Left [Flags affected: n,z,c]
// ASL addr,X
// Absolute Indexed, X
// 3<>
int ASL_1E::calculateCycles(const State& state) const
{
    // 3   9-2*m       abs,X     m.....mm . ASL $9876,X
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// BCC Branch if Carry Clear [Flags affected: none][Alias: BLT]
// BCC nearlabel
// Program Counter Relative
// 2<>
int BCC_90::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BCC LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BCS Branch if Carry Set [Flags affected: none][Alias: BGE]
// BCS nearlabel
// Program Counter Relative
// 2<>
int BCS_B0::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BCS LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BEQ Branch if Equal [Flags affected: none]
// BEQ nearlabel
// Program Counter Relative
// 2<>
int BEQ_F0::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BEQ LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp
// Direct Page
// 2<>
int BIT_24::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       mm....m. . BIT $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr
// Absolute
// 3<>
int BIT_2C::calculateCycles(const State& state) const
{
    // 3   5-m         abs       mm....m. . BIT $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT dp,X
// Direct Page Indexed, X
// 2<>
int BIT_34::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     mm....m. . BIT $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT addr,X
// Absolute Indexed, X
// 3<>
int BIT_3C::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     mm....m. . BIT $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// BIT Test Bits [Flags affected: z (immediate mode) n,v,z (non-immediate modes)]
// BIT #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int BIT_89::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       ......m. . BIT #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// BMI Branch if Minus [Flags affected: none]
// BMI nearlabel
// Program Counter Relative
// 2<>
int BMI_30::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BMI LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BNE Branch if Not Equal [Flags affected: none]
// BNE nearlabel
// Program Counter Relative
// 2<>
int BNE_D0::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BNE LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BPL Branch if Plus [Flags affected: none]
// BPL nearlabel
// Program Counter Relative
// 2<>
int BPL_10::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BPL LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BRA Branch Always [Flags affected: none]
// BRA nearlabel
// Program Counter Relative
// 2<>
int BRA_80::calculateCycles(const State& state) const
{
    // 2   3+e*p       rel8      ........ . BRA LABEL
    int cycles = 3;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BRK Break [Flags affected: b,i (6502) b,d,i (65C02/65816 Emulation) d,i (65816 Native)]
// BRK
// Stack/Interrupt
// 2<18>
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
int BRK_00::calculateCycles(const State& state) const
{
    // 1   8-e         imp       ....01.. . BRK
    int cycles = 7;
    // 9: Add 1 cycle for 65816 native mode (e=0)
    cycles += state.isEmulationMode() ? 0 : 1;
    return cycles;
}

// BRL Branch Long Always [Flags affected: none]
// BRL label
// Program Counter Relative Long
// 3<>
int BRL_82::calculateCycles(const State& state) const
{
    // 3   4           rel16     ........ . BRL LABEL
    int cycles = 4;
    return cycles;
}

// BVC Branch if Overflow Clear [Flags affected: none]
// BVC nearlabel
// Program Counter Relative
// 2<>
int BVC_50::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BVC LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// BVS Branch if Overflow Set [Flags affected: none]
// BVS nearlabel
// Program Counter Relative
// 2<>
int BVS_70::calculateCycles(const State& state) const
{
    // 2   2+t+t*e*p   rel8      ........ . BVS LABEL
    int cycles = 2;
    // 7: Add 1 cycle if branch is taken
    cycles += 0 /* TODO07 */;
    // 8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) 
    cycles += 0 /* TODO08 */;
    return cycles;
}

// CLC Clear Carry [Flags affected: c]
// CLC
// Implied
// 1<>
int CLC_18::calculateCycles(const State& state) const
{
    // 1   2           imp       .......0 . CLC
    int cycles = 2;
    return cycles;
}

// CLD Clear Decimal Mode Flag [Flags affected: d]
// CLD
// Implied
// 1<>
int CLD_D8::calculateCycles(const State& state) const
{
    // 1   2           imp       ....0... . CLD
    int cycles = 2;
    return cycles;
}

// CLI Clear Interrupt Disable Flag [Flags affected: i]
// CLI
// Implied
// 1<>
int CLI_58::calculateCycles(const State& state) const
{
    // 1   2           imp       .....0.. . CLI
    int cycles = 2;
    return cycles;
}

// CLV Clear Overflow Flag [Flags affected: v]
// CLV
// Implied
// 1<>
int CLV_B8::calculateCycles(const State& state) const
{
    // 1   2           imp       .0...... . CLV
    int cycles = 2;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp,X)
// Direct Page Indexed Indirect,X
// 2<>
int CMP_C1::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   m.....mm . CMP ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP sr,S
// Stack Relative
// 2<>
int CMP_C3::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     m.....mm . CMP $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp
// Direct Page
// 2<>
int CMP_C5::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       m.....mm . CMP $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp]
// Direct Page Indirect Long
// 2<>
int CMP_C7::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     m.....mm . CMP [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int CMP_C9::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       m.....mm . CMP #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr
// Absolute
// 3<>
int CMP_CD::calculateCycles(const State& state) const
{
    // 3   5-m         abs       m.....mm . CMP $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long
// Absolute Long
// 4<>
int CMP_CF::calculateCycles(const State& state) const
{
    // 4   6-m         long      m.....mm . CMP $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int CMP_D1::calculateCycles(const State& state) const
{
    // 2   7-m+w-x+x*p (dir),Y   m.....mm . CMP ($10),Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (dp)
// Direct Page Indirect
// 2<>
int CMP_D2::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     m.....mm . CMP ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int CMP_D3::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y m.....mm . CMP ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP dp,X
// Direct Page Indexed, X
// 2<>
int CMP_D5::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     m.....mm . CMP $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int CMP_D7::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   m.....mm . CMP [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,Y
// Absolute Indexed, Y
// 3<>
int CMP_D9::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,Y     m.....mm . CMP $9876,Y
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP addr,X
// Absolute Indexed, X
// 3<>
int CMP_DD::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     m.....mm . CMP $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// CMP Compare Accumulator With Memory [Flags affected: n,z,c]
// CMP long,X
// Absolute Long Indexed, X
// 4<>
int CMP_DF::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    m.....mm . CMP $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// COP Co-Processor Enable [Flags affected: d,i]
// COP const
// Stack/Interrupt
// 2<18>
// 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
int COP_02::calculateCycles(const State& state) const
{
    // 2   8-e         imm       ....01.. . COP #$12
    int cycles = 7;
    // 9: Add 1 cycle for 65816 native mode (e=0)
    cycles += state.isEmulationMode() ? 0 : 1;
    return cycles;
}

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX #const
// Immediate
// 2<19>
// 19: Add 1 byte if x=0 (16-bit index registers)
int CPX_E0::calculateCycles(const State& state) const
{
    // 3-x 3-x         imm       x.....xx . CPX #$54
    int cycles = 2;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX dp
// Direct Page
// 2<>
int CPX_E4::calculateCycles(const State& state) const
{
    // 2   4-x+w       dir       x.....xx . CPX $10
    int cycles = 3;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// CPX Compare Index Register X with Memory [Flags affected: n,z,c]
// CPX addr
// Absolute
// 3<>
int CPX_EC::calculateCycles(const State& state) const
{
    // 3   5-x         abs       x.....xx . CPX $9876
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY #const
// Immediate
// 2<19>
// 19: Add 1 byte if x=0 (16-bit index registers)
int CPY_C0::calculateCycles(const State& state) const
{
    // 3-x 3-x         imm       x.....xx . CPY #$54
    int cycles = 2;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY dp
// Direct Page
// 2<>
int CPY_C4::calculateCycles(const State& state) const
{
    // 2   4-x+w       dir       x.....xx . CPY $10
    int cycles = 3;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// CPY Compare Index Register Y with Memory [Flags affected: n,z,c]
// CPY addr
// Absolute
// 3<>
int CPY_CC::calculateCycles(const State& state) const
{
    // 3   5-x         abs       x.....xx . CPY $9876
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// DEC Decrement [Flags affected: n,z]
// DEC A
// Accumulator
// 1<>
int DEC_3A::calculateCycles(const State& state) const
{
    // 1   2           acc       m.....m. . DEC
    int cycles = 2;
    return cycles;
}

// DEC Decrement [Flags affected: n,z]
// DEC dp
// Direct Page
// 2<>
int DEC_C6::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       m.....m. . DEC $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// DEC Decrement [Flags affected: n,z]
// DEC addr
// Absolute
// 3<>
int DEC_CE::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       m.....m. . DEC $9876
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// DEC Decrement [Flags affected: n,z]
// DEC dp,X
// Direct Page Indexed, X
// 2<>
int DEC_D6::calculateCycles(const State& state) const
{
    // 2   8-2*m+w     dir,X     m.....m. . DEC $10,X
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// DEC Decrement [Flags affected: n,z]
// DEC addr,X
// Absolute Indexed, X
// 3<>
int DEC_DE::calculateCycles(const State& state) const
{
    // 3   9-2*m       abs,X     m.....m. . DEC $9876,X
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// DEX Decrement Index Register X [Flags affected: n,z]
// DEX
// Implied
// 1<>
int DEX_CA::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . DEX
    int cycles = 2;
    return cycles;
}

// DEY Decrement Index Register Y [Flags affected: n,z]
// DEY
// Implied
// 1<>
int DEY_88::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . DEY
    int cycles = 2;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp,X)
// Direct Page Indexed Indirect,X
// 2<>
int EOR_41::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   m.....m. . EOR ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR sr,S
// Stack Relative
// 2<>
int EOR_43::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     m.....m. . EOR $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp
// Direct Page
// 2<>
int EOR_45::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       m.....m. . EOR $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp]
// Direct Page Indirect Long
// 2<>
int EOR_47::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     m.....m. . EOR [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int EOR_49::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       m.....m. . EOR #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr
// Absolute
// 3<>
int EOR_4D::calculateCycles(const State& state) const
{
    // 3   5-m         abs       m.....m. . EOR $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long
// Absolute Long
// 4<>
int EOR_4F::calculateCycles(const State& state) const
{
    // 4   6-m         long      m.....m. . EOR $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int EOR_51::calculateCycles(const State& state) const
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . EOR ($10),Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (dp)
// Direct Page Indirect
// 2<>
int EOR_52::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     m.....m. . EOR ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int EOR_53::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y m.....m. . EOR ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR dp,X
// Direct Page Indexed, X
// 2<>
int EOR_55::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     m.....m. . EOR $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int EOR_57::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   m.....m. . EOR [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,Y
// Absolute Indexed, Y
// 3<>
int EOR_59::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . EOR $9876,Y
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR addr,X
// Absolute Indexed, X
// 3<>
int EOR_5D::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     m.....m. . EOR $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// EOR Exclusive-OR Accumulator with Memory [Flags affected: n,z]
// EOR long,X
// Absolute Long Indexed, X
// 4<>
int EOR_5F::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    m.....m. . EOR $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// INC Increment [Flags affected: n,z]
// INC A
// Accumulator
// 1<>
int INC_1A::calculateCycles(const State& state) const
{
    // 1   2           acc       m.....m. . INC
    int cycles = 2;
    return cycles;
}

// INC Increment [Flags affected: n,z]
// INC dp
// Direct Page
// 2<>
int INC_E6::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       m.....m. . INC $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// INC Increment [Flags affected: n,z]
// INC addr
// Absolute
// 3<>
int INC_EE::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       m.....m. . INC $9876
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// INC Increment [Flags affected: n,z]
// INC dp,X
// Direct Page Indexed, X
// 2<>
int INC_F6::calculateCycles(const State& state) const
{
    // 2   8-2*m+w     dir,X     m.....m. . INC $10,X
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// INC Increment [Flags affected: n,z]
// INC addr,X
// Absolute Indexed, X
// 3<>
int INC_FE::calculateCycles(const State& state) const
{
    // 3   9-2*m       abs,X     m.....m. . INC $9876,X
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// INX Increment Index Register X [Flags affected: n,z]
// INX
// Implied
// 1<>
int INX_E8::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . INX
    int cycles = 2;
    return cycles;
}

// INY Increment Index Register Y [Flags affected: n,z]
// INY
// Implied
// 1<>
int INY_C8::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . INY
    int cycles = 2;
    return cycles;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP addr
// Absolute
// 3<>
int JMP_4C::calculateCycles(const State& state) const
{
    // 3   3           abs       ........ . JMP $1234
    int cycles = 3;
    return cycles;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP long
// Absolute Long
// 4<>
int JMP_5C::calculateCycles(const State& state) const
{
    // 4   4           long      ........ . JMP $FEDCBA
    int cycles = 4;
    return cycles;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr)
// Absolute Indirect
// 3<>
int JMP_6C::calculateCycles(const State& state) const
{
    // 3   5           (abs)     ........ . JMP ($1234)
    int cycles = 5;
    // 
    // 
    return cycles;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP (addr,X)
// Absolute Indexed Indirect
// 3<>
int JMP_7C::calculateCycles(const State& state) const
{
    // 3   6           (abs,X)   ........ . JMP ($1234,X)
    int cycles = 6;
    return cycles;
}

// JMP Jump [Flags affected: none][Alias: JML for all Long addressing modes]
// JMP [addr]
// Absolute Indirect Long
// 3<>
int JMP_DC::calculateCycles(const State& state) const
{
    // 3   6           [abs]     ........ . JMP [$1234]
    int cycles = 6;
    return cycles;
}

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR addr
// Absolute
// 3<>
int JSR_20::calculateCycles(const State& state) const
{
    // 3   6           abs       ........ . JSR $1234
    int cycles = 6;
    return cycles;
}

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR long
// Absolute Long
// 4<>
int JSR_22::calculateCycles(const State& state) const
{
    // 4   8           long      ........ . JSL $123456
    int cycles = 8;
    return cycles;
}

// JSR Jump to Subroutine [Flags affected: none][Alias: JSL for Absolute Long]
// JSR (addr,X)
// Absolute Indexed Indirect
// 3<>
int JSR_FC::calculateCycles(const State& state) const
{
    // 3   8           (abs,X)   ........ . JSR ($1234,X)
    int cycles = 8;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
int LDA_A1::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   m.....m. . LDA ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA sr,S
// Stack Relative
// 2<>
int LDA_A3::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     m.....m. . LDA $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp
// Direct Page
// 2<>
int LDA_A5::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       m.....m. . LDA $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp]
// Direct Page Indirect Long
// 2<>
int LDA_A7::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     m.....m. . LDA [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int LDA_A9::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       m.....m. . LDA #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr
// Absolute
// 3<>
int LDA_AD::calculateCycles(const State& state) const
{
    // 3   5-m         abs       m.....m. . LDA $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long
// Absolute Long
// 4<>
int LDA_AF::calculateCycles(const State& state) const
{
    // 4   6-m         long      m.....m. . LDA $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int LDA_B1::calculateCycles(const State& state) const
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . LDA ($10),Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (dp)
// Direct Page Indirect
// 2<>
int LDA_B2::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     m.....m. . LDA ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int LDA_B3::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y m.....m. . LDA ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA dp,X
// Direct Page Indexed, X
// 2<>
int LDA_B5::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     m.....m. . LDA $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int LDA_B7::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   m.....m. . LDA [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,Y
// Absolute Indexed, Y
// 3<>
int LDA_B9::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . LDA $9876,Y
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA addr,X
// Absolute Indexed, X
// 3<>
int LDA_BD::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     m.....m. . LDA $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// LDA Load Accumulator from Memory [Flags affected: n,z]
// LDA long,X
// Absolute Long Indexed, X
// 4<>
int LDA_BF::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    m.....m. . LDA $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX #const
// Immediate
// 2<19>
// 19: Add 1 byte if x=0 (16-bit index registers)
int LDX_A2::calculateCycles(const State& state) const
{
    // 3-x 3-x         imm       x.....x. . LDX #$54
    int cycles = 2;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp
// Direct Page
// 2<>
int LDX_A6::calculateCycles(const State& state) const
{
    // 2   4-x+w       dir       x.....x. . LDX $10
    int cycles = 3;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr
// Absolute
// 3<>
int LDX_AE::calculateCycles(const State& state) const
{
    // 3   5-x         abs       x.....x. . LDX $9876
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX dp,Y
// Direct Page Indexed, Y
// 2<>
int LDX_B6::calculateCycles(const State& state) const
{
    // 2   5-x+w       dir,Y     x.....x. . LDX $10,Y
    int cycles = 4;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDX Load Index Register X from Memory [Flags affected: n,z]
// LDX addr,Y
// Absolute Indexed, Y
// 3<>
int LDX_BE::calculateCycles(const State& state) const
{
    // 3   6-2*x+x*p   abs,Y     x.....x. . LDX $9876,Y
    int cycles = 4;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY #const
// Immediate
// 2<19>
// 19: Add 1 byte if x=0 (16-bit index registers)
int LDY_A0::calculateCycles(const State& state) const
{
    // 3-x 3-x         imm       x.....x. . LDY #$54
    int cycles = 2;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp
// Direct Page
// 2<>
int LDY_A4::calculateCycles(const State& state) const
{
    // 2   4-x+w       dir       x.....x. . LDY $10
    int cycles = 3;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr
// Absolute
// 3<>
int LDY_AC::calculateCycles(const State& state) const
{
    // 3   5-x         abs       x.....x. . LDY $9876
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY dp,X
// Direct Page Indexed, X
// 2<>
int LDY_B4::calculateCycles(const State& state) const
{
    // 2   5-x+w       dir,X     x.....x. . LDY $10,X
    int cycles = 4;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LDY Load Index Register Y from Memory [Flags affected: n,z]
// LDY addr,X
// Absolute Indexed, X
// 3<>
int LDY_BC::calculateCycles(const State& state) const
{
    // 3   6-2*x+x*p   abs,X     x.....x. . LDY $9876,X
    int cycles = 4;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp
// Direct Page
// 2<>
int LSR_46::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       0.....m* . LSR $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR A
// Accumulator
// 1<>
int LSR_4A::calculateCycles(const State& state) const
{
    // 1   2           acc       0.....m* . LSR
    int cycles = 2;
    return cycles;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr
// Absolute
// 3<>
int LSR_4E::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       0.....m* . LSR $9876
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR dp,X
// Direct Page Indexed, X
// 2<>
int LSR_56::calculateCycles(const State& state) const
{
    // 2   8-2*m+w     dir,X     0.....m* . LSR $10,X
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// LSR Logical Shift Memory or Accumulator Right [Flags affected: n,z,c]
// LSR addr,X
// Absolute Indexed, X
// 3<>
int LSR_5E::calculateCycles(const State& state) const
{
    // 3   9-2*m       abs,X     0.....m* . LSR $9876,X
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// MVN Block Move Negative [Flags affected: none][Registers: X,Y,C]
// MVN srcbk,destbk
// Block Move
// 3<>
int MVN_54::calculateCycles(const State& state) const
{
    // 3   7           src,dest  ........ . MVN #$12,#$34
    int cycles = 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// MVP Block Move Positive [Flags affected: none][Registers: X,Y,C]
// MVP srcbk,destbk
// Block Move
// 3<>
int MVP_44::calculateCycles(const State& state) const
{
    // 3   7           src,dest  ........ . MVP #$12,#$34
    int cycles = 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// NOP No Operation [Flags affected: none]
// NOP
// Implied
// 1<>
int NOP_EA::calculateCycles(const State& state) const
{
    // 1   2           imp       ........ . NOP
    int cycles = 2;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
int ORA_01::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   m.....m. . ORA ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA sr,S
// Stack Relative
// 2<>
int ORA_03::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     m.....m. . ORA $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp
// Direct Page
// 2<>
int ORA_05::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       m.....m. . ORA $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp]
// Direct Page Indirect Long
// 2<>
int ORA_07::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     m.....m. . ORA [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int ORA_09::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       m.....m. . ORA #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr
// Absolute
// 3<>
int ORA_0D::calculateCycles(const State& state) const
{
    // 3   5-m         abs       m.....m. . ORA $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long
// Absolute Long
// 4<>
int ORA_0F::calculateCycles(const State& state) const
{
    // 4   6-m         long      m.....m. . ORA $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int ORA_11::calculateCycles(const State& state) const
{
    // 2   7-m+w-x+x*p (dir),Y   m.....m. . ORA ($10),Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (dp)
// Direct Page Indirect
// 2<>
int ORA_12::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     m.....m. . ORA ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int ORA_13::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y m.....m. . ORA ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA dp,X
// Direct Page Indexed, X
// 2<>
int ORA_15::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     m.....m. . ORA $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int ORA_17::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   m.....m. . ORA [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,Y
// Absolute Indexed, Y
// 3<>
int ORA_19::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,Y     m.....m. . ORA $9876,Y
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA addr,X
// Absolute Indexed, X
// 3<>
int ORA_1D::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     m.....m. . ORA $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// ORA OR Accumulator with Memory [Flags affected: n,z]
// ORA long,X
// Absolute Long Indexed, X
// 4<>
int ORA_1F::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    m.....m. . ORA $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// PEA Push Effective Absolute Address [Flags affected: none]
// PEA addr
// Stack (Absolute)
// 3<>
int PEA_F4::calculateCycles(const State& state) const
{
    // 3   5           imm       ........ . PEA #$1234
    int cycles = 5;
    return cycles;
}

// PEI Push Effective Indirect Address [Flags affected: none]
// PEI (dp)
// Stack (Direct Page Indirect)
// 2<>
int PEI_D4::calculateCycles(const State& state) const
{
    // 2   6+w         dir       ........ . PEI $12
    int cycles = 6;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// PER Push Effective Program Counter Relative Indirect Address [Flags affected: none]
// PER label
// Stack (Program Counter Relative Long)
// 3<>
int PER_62::calculateCycles(const State& state) const
{
    // 3   6           imm       ........ . PER LABEL
    int cycles = 6;
    return cycles;
}

// PHA Push Accumulator [Flags affected: none]
// PHA
// Stack (Push)
// 1<>
int PHA_48::calculateCycles(const State& state) const
{
    // 1   4-m         imp       ........ . PHA
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// PHB Push Data Bank Register [Flags affected: none]
// PHB
// Stack (Push)
// 1<>
int PHB_8B::calculateCycles(const State& state) const
{
    // 1   3           imp       ........ . PHB
    int cycles = 3;
    return cycles;
}

// PHD Push Direct Page Register [Flags affected: none]
// PHD
// Stack (Push)
// 1<>
int PHD_0B::calculateCycles(const State& state) const
{
    // 1   4           imp       ........ . PHD
    int cycles = 4;
    return cycles;
}

// PHK Push Program Bank Register [Flags affected: none]
// PHK
// Stack (Push)
// 1<>
int PHK_4B::calculateCycles(const State& state) const
{
    // 1   3           imp       ........ . PHK
    int cycles = 3;
    return cycles;
}

// PHP Push Processor Status Register [Flags affected: none]
// PHP
// Stack (Push)
// 1<>
int PHP_08::calculateCycles(const State& state) const
{
    // 1   3           imp       ........ . PHP
    int cycles = 3;
    return cycles;
}

// PHX Push Index Register X [Flags affected: none]
// PHX
// Stack (Push)
// 1<>
int PHX_DA::calculateCycles(const State& state) const
{
    // 1   4-x         imp       ........ . PHX
    int cycles = 3;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// PHY Push Index Register Y [Flags affected: none]
// PHY
// Stack (Push)
// 1<>
int PHY_5A::calculateCycles(const State& state) const
{
    // 1   4-x         imp       ........ . PHY
    int cycles = 3;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// PLA Pull Accumulator [Flags affected: n,z]
// PLA
// Stack (Pull)
// 1<>
int PLA_68::calculateCycles(const State& state) const
{
    // 1   5-m         imp       m.....m. . PLA
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// PLB Pull Data Bank Register [Flags affected: n,z]
// PLB
// Stack (Pull)
// 1<>
int PLB_AB::calculateCycles(const State& state) const
{
    // 1   4           imp       *.....*. . PLB
    int cycles = 4;
    return cycles;
}

// PLD Pull Direct Page Register [Flags affected: n,z]
// PLD
// Stack (Pull)
// 1<>
int PLD_2B::calculateCycles(const State& state) const
{
    // 1   5           imp       *.....*. . PLD
    int cycles = 5;
    return cycles;
}

// PLP Pull Processor Status Register [Flags affected: n,z]
// PLP
// Stack (Pull)
// 1<>
int PLP_28::calculateCycles(const State& state) const
{
    // 1   4           imp       ******** . PLP
    int cycles = 4;
    return cycles;
}

// PLX Pull Index Register X [Flags affected: n,z]
// PLX
// Stack (Pull)
// 1<>
int PLX_FA::calculateCycles(const State& state) const
{
    // 1   5-x         imp       x.....x. . PLX
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// PLY Pull Index Register Y [Flags affected: n,z]
// PLY
// Stack (Pull)
// 1<>
int PLY_7A::calculateCycles(const State& state) const
{
    // 1   5-x         imp       x.....x. . PLY
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// REP Reset Processor Status Bits [Flags affected: all except b per operand]
// REP #const
// Immediate
// 2<>
int REP_C2::calculateCycles(const State& state) const
{
    // 2   3           imm       ******** . REP #$12
    int cycles = 3;
    return cycles;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp
// Direct Page
// 2<>
int ROL_26::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       m.....mm . ROL $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL A
// Accumulator
// 1<>
int ROL_2A::calculateCycles(const State& state) const
{
    // 1   2           acc       m.....mm . ROL
    int cycles = 2;
    return cycles;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr
// Absolute
// 3<>
int ROL_2E::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       m.....mm . ROL $9876
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL dp,X
// Direct Page Indexed, X
// 2<>
int ROL_36::calculateCycles(const State& state) const
{
    // 2   8-2*m+w     dir,X     m.....mm . ROL $10,X
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ROL Rotate Memory or Accumulator Left [Flags affected: n,z,c]
// ROL addr,X
// Absolute Indexed, X
// 3<>
int ROL_3E::calculateCycles(const State& state) const
{
    // 3   9-2*m       abs,X     m.....mm . ROL $9876,X
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp
// Direct Page
// 2<>
int ROR_66::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       m.....m* . ROR $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR A
// Accumulator
// 1<>
int ROR_6A::calculateCycles(const State& state) const
{
    // 1   2           acc       m.....m* . ROR
    int cycles = 2;
    return cycles;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr
// Absolute
// 3<>
int ROR_6E::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       m.....m* . ROR $9876
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR dp,X
// Direct Page Indexed, X
// 2<>
int ROR_76::calculateCycles(const State& state) const
{
    // 2   8-2*m+w     dir,X     m.....m* . ROR $10,X
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// ROR Rotate Memory or Accumulator Right [Flags affected: n,z,c]
// ROR addr,X
// Absolute Indexed, X
// 3<>
int ROR_7E::calculateCycles(const State& state) const
{
    // 3   9-2*m       abs,X     m.....m* . ROR $9876,X
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// RTI Return from Interrupt [Flags affected: all except b]
// RTI
// Stack (RTI)
// 1<>
int RTI_40::calculateCycles(const State& state) const
{
    // 1   7-e         imp       ******** . RTI
    int cycles = 6;
    // 9: Add 1 cycle for 65816 native mode (e=0)
    cycles += state.isEmulationMode() ? 0 : 1;
    return cycles;
}

// RTL Return from Subroutine Long [Flags affected: none]
// RTL
// Stack (RTL)
// 1<>
int RTL_6B::calculateCycles(const State& state) const
{
    // 1   6           imp       ........ . RTL
    int cycles = 6;
    return cycles;
}

// RTS Return from Subroutine [Flags affected: none]
// RTS
// Stack (RTS)
// 1<>
int RTS_60::calculateCycles(const State& state) const
{
    // 1   6           imp       ........ . RTS
    int cycles = 6;
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
int SBC_E1::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   mm....mm . SBC ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC sr,S
// Stack Relative
// 2<>
int SBC_E3::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     mm....mm . SBC $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp
// Direct Page
// 2<>
int SBC_E5::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       mm....mm . SBC $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp]
// Direct Page Indirect Long
// 2<>
int SBC_E7::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     mm....mm . SBC [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC #const
// Immediate
// 2<17>
// 17: Add 1 byte if m=0 (16-bit memory/accumulator)
int SBC_E9::calculateCycles(const State& state) const
{
    // 3-m 3-m         imm       mm....mm . SBC #$54
    int cycles = 2;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr
// Absolute
// 3<>
int SBC_ED::calculateCycles(const State& state) const
{
    // 3   5-m         abs       mm....mm . SBC $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long
// Absolute Long
// 4<>
int SBC_EF::calculateCycles(const State& state) const
{
    // 4   6-m         long      mm....mm . SBC $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int SBC_F1::calculateCycles(const State& state) const
{
    // 2   7-m+w-x+x*p (dir),Y   mm....mm . SBC ($10),Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (dp)
// Direct Page Indirect
// 2<>
int SBC_F2::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     mm....mm . SBC ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int SBC_F3::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y mm....mm . SBC ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC dp,X
// Direct Page Indexed, X
// 2<>
int SBC_F5::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     mm....mm . SBC $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int SBC_F7::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   mm....mm . SBC [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,Y
// Absolute Indexed, Y
// 3<>
int SBC_F9::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,Y     mm....mm . SBC $9876,Y
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC addr,X
// Absolute Indexed, X
// 3<>
int SBC_FD::calculateCycles(const State& state) const
{
    // 3   6-m-x+x*p   abs,X     mm....mm . SBC $9876,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    // 
    return cycles;
}

// SBC Subtract with Borrow from Accumulator [Flags affected: n,v,z,c]
// SBC long,X
// Absolute Long Indexed, X
// 4<>
int SBC_FF::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    mm....mm . SBC $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 
    return cycles;
}

// SEC Set Carry Flag [Flags affected: c]
// SEC
// Implied
// 1<>
int SEC_38::calculateCycles(const State& state) const
{
    // 1   2           imp       .......1 . SEC
    int cycles = 2;
    return cycles;
}

// SED Set Decimal Flag [Flags affected: d]
// SED
// Implied
// 1<>
int SED_F8::calculateCycles(const State& state) const
{
    // 1   2           imp       ....1... . SED
    int cycles = 2;
    return cycles;
}

// SEI Set Interrupt Disable Flag [Flags affected: i]
// SEI
// Implied
// 1<>
int SEI_78::calculateCycles(const State& state) const
{
    // 1   2           imp       .....1.. . SEI
    int cycles = 2;
    return cycles;
}

// SEP Set Processor Status Bits [Flags affected: all except b per operand]
// SEP #const
// Immediate
// 2<>
int SEP_E2::calculateCycles(const State& state) const
{
    // 2   3           imm       ******** . SEP #$12
    int cycles = 3;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp,X)
// Direct Page Indexed Indirect, X
// 2<>
int STA_81::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir,X)   ........ . STA ($10,X)
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA sr,S
// Stack Relative
// 2<>
int STA_83::calculateCycles(const State& state) const
{
    // 2   5-m         stk,S     ........ . STA $32,S
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp
// Direct Page
// 2<>
int STA_85::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       ........ . STA $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp]
// Direct Page Indirect Long
// 2<>
int STA_87::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir]     ........ . STA [$10]
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr
// Absolute
// 3<>
int STA_8D::calculateCycles(const State& state) const
{
    // 3   5-m         abs       ........ . STA $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA long
// Absolute Long
// 4<>
int STA_8F::calculateCycles(const State& state) const
{
    // 4   6-m         long      ........ . STA $FEDBCA
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp),Y
// Direct Page Indirect Indexed, Y
// 2<>
int STA_91::calculateCycles(const State& state) const
{
    // 2   7-m+w       (dir),Y   ........ . STA ($10),Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA (dp)
// Direct Page Indirect
// 2<>
int STA_92::calculateCycles(const State& state) const
{
    // 2   6-m+w       (dir)     ........ . STA ($10)
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA (sr,S),Y
// Stack Relative Indirect Indexed, Y
// 2<>
int STA_93::calculateCycles(const State& state) const
{
    // 2   8-m         (stk,S),Y ........ . STA ($32,S),Y
    int cycles = 7;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA dp,X
// Direct Page Indexed, X
// 2<>
int STA_95::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     ........ . STA $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA [dp],Y
// Direct Page Indirect Long Indexed, Y
// 2<>
int STA_97::calculateCycles(const State& state) const
{
    // 2   7-m+w       [dir],Y   ........ . STA [$10],Y
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,Y
// Absolute Indexed, Y
// 3<>
int STA_99::calculateCycles(const State& state) const
{
    // 3   6-m         abs,Y     ........ . STA $9876,Y
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA addr,X
// Absolute Indexed, X
// 3<>
int STA_9D::calculateCycles(const State& state) const
{
    // 3   6-m         abs,X     ........ . STA $9876,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STA Store Accumulator to Memory [Flags affected: none]
// STA long,X
// Absolute Long Indexed, X
// 4<>
int STA_9F::calculateCycles(const State& state) const
{
    // 4   6-m         long,X    ........ . STA $FEDCBA,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STP Stop Processor [Flags affected: none]
// STP
// Implied
// 1<>
int STP_DB::calculateCycles(const State& state) const
{
    // 1   3           imp       ........ . STP
    int cycles = 3;
    // 14: Uses 3 cycles to shut the processor down; additional cycles are required by reset to restart it
    cycles += 0 /* TODO14 */;
    return cycles;
}

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp
// Direct Page
// 2<>
int STX_86::calculateCycles(const State& state) const
{
    // 2   4-x+w       dir       ........ . STX $10
    int cycles = 3;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// STX Store Index Register X to Memory [Flags affected: none]
// STX addr
// Absolute
// 3<>
int STX_8E::calculateCycles(const State& state) const
{
    // 3   5-x         abs       ........ . STX $9876
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// STX Store Index Register X to Memory [Flags affected: none]
// STX dp,Y
// Direct Page Indexed, Y
// 2<>
int STX_96::calculateCycles(const State& state) const
{
    // 2   5-x+w       dir,Y     ........ . STX $10,Y
    int cycles = 4;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp
// Direct Page
// 2<>
int STY_84::calculateCycles(const State& state) const
{
    // 2   4-x+w       dir       ........ . STY $10
    int cycles = 3;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// STY Store Index Register Y to Memory [Flags affected: none]
// STY addr
// Absolute
// 3<>
int STY_8C::calculateCycles(const State& state) const
{
    // 3   5-x         abs       ........ . STY $9876
    int cycles = 4;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// STY Store Index Register Y to Memory [Flags affected: none]
// STY dp,X
// Direct Page Indexed, X
// 2<>
int STY_94::calculateCycles(const State& state) const
{
    // 2   5-x+w       dir,X     ........ . STY $10,X
    int cycles = 4;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 10: Add 1 cycle if x=0 (16-bit index registers)
    cycles += state.getFlag(State::x) ? 0 : 1;
    return cycles;
}

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp
// Direct Page
// 2<>
int STZ_64::calculateCycles(const State& state) const
{
    // 2   4-m+w       dir       ........ . STZ $10
    int cycles = 3;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STZ Store Zero to Memory [Flags affected: none]
// STZ dp,X
// Direct Page Indexed, X
// 2<>
int STZ_74::calculateCycles(const State& state) const
{
    // 2   5-m+w       dir,X     ........ . STZ $10,X
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    return cycles;
}

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr
// Absolute
// 3<>
int STZ_9C::calculateCycles(const State& state) const
{
    // 3   5-m         abs       ........ . STZ $9876
    int cycles = 4;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// STZ Store Zero to Memory [Flags affected: none]
// STZ addr,X
// Absolute Indexed, X
// 3<>
int STZ_9E::calculateCycles(const State& state) const
{
    // 3   6-m         abs,X     ........ . STZ $9876,X
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// TAX Transfer Accumulator to Index Register X [Flags affected: n,z]
// TAX
// Implied
// 1<>
int TAX_AA::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . TAX
    int cycles = 2;
    return cycles;
}

// TAY Transfer Accumulator to Index Register Y [Flags affected: n,z]
// TAY
// Implied
// 1<>
int TAY_A8::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . TAY
    int cycles = 2;
    return cycles;
}

// TCD Transfer 16-bit Accumulator to Direct Page Register [Flags affected: n,z]
// TCD
// Implied
// 1<>
int TCD_5B::calculateCycles(const State& state) const
{
    // 1   2           imp       *.....*. . TCD
    int cycles = 2;
    return cycles;
}

// TCS Transfer 16-bit Accumulator to Stack Pointer [Flags affected: none]
// TCS
// Implied
// 1<>
int TCS_1B::calculateCycles(const State& state) const
{
    // 1   2           imp       ........ . TCS
    int cycles = 2;
    return cycles;
}

// TDC Transfer Direct Page Register to 16-bit Accumulator [Flags affected: n,z]
// TDC
// Implied
// 1<>
int TDC_7B::calculateCycles(const State& state) const
{
    // 1   2           imp       *.....*. . TDC
    int cycles = 2;
    return cycles;
}

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB dp
// Direct Page
// 2<>
int TRB_14::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       ......m. . TRB $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// TRB Test and Reset Memory Bits Against Accumulator [Flags affected: z]
// TRB addr
// Absolute
// 3<>
int TRB_1C::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       ......m. . TRB $9876
    int cycles = 6;
    // 3: Add 1 cycle if adding index crosses a page boundary
    cycles += 0 /* TODO03 */;
    return cycles;
}

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB dp
// Direct Page
// 2<>
int TSB_04::calculateCycles(const State& state) const
{
    // 2   7-2*m+w     dir       ......m. . TSB $10
    int cycles = 5;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 2: Add 1 cycle if low byte of Direct Page Register is non-zero
    cycles += (uint8_t)state.getDirectPage() ? 1 : 0;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// TSB Test and Set Memory Bits Against Accumulator [Flags affected: z]
// TSB addr
// Absolute
// 3<>
int TSB_0C::calculateCycles(const State& state) const
{
    // 3   8-2*m       abs       ......m. . TSB $9876
    int cycles = 6;
    // 1: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    // 5: Add 1 cycle if m=0 (16-bit memory/accumulator)
    cycles += state.getFlag(State::m) ? 0 : 1;
    return cycles;
}

// TSC Transfer Stack Pointer to 16-bit Accumulator [Flags affected: n,z]
// TSC
// Implied
// 1<>
int TSC_3B::calculateCycles(const State& state) const
{
    // 1   2           imp       *.....*. . TSC
    int cycles = 2;
    return cycles;
}

// TSX Transfer Stack Pointer to Index Register X [Flags affected: n,z]
// TSX
// Implied
// 1<>
int TSX_BA::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . TSX
    int cycles = 2;
    return cycles;
}

// TXA Transfer Index Register X to Accumulator [Flags affected: n,z]
// TXA
// Implied
// 1<>
int TXA_8A::calculateCycles(const State& state) const
{
    // 1   2           imp       m.....m. . TXA
    int cycles = 2;
    return cycles;
}

// TXS Transfer Index Register X to Stack Pointer [Flags affected: none]
// TXS
// Implied
// 1<>
int TXS_9A::calculateCycles(const State& state) const
{
    // 1   2           imp       ........ . TXS
    int cycles = 2;
    return cycles;
}

// TXY Transfer Index Register X to Index Register Y [Flags affected: n,z]
// TXY
// Implied
// 1<>
int TXY_9B::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . TXY
    int cycles = 2;
    return cycles;
}

// TYA Transfer Index Register Y to Accumulator [Flags affected: n,z]
// TYA
// Implied
// 1<>
int TYA_98::calculateCycles(const State& state) const
{
    // 1   2           imp       m.....m. . TYA
    int cycles = 2;
    return cycles;
}

// TYX Transfer Index Register Y to Index Register X [Flags affected: n,z]
// TYX
// Implied
// 1<>
int TYX_BB::calculateCycles(const State& state) const
{
    // 1   2           imp       x.....x. . TYX
    int cycles = 2;
    return cycles;
}

// WAI Wait for Interrupt [Flags affected: none]
// WAI
// Implied
// 1<>
int WAI_CB::calculateCycles(const State& state) const
{
    // 1   3           imp       ........ . WAI
    int cycles = 3;
    // 15: Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it
    cycles += 0 /* TODO15 */;
    return cycles;
}

// WDM Reserved for Future Expansion [Flags affected: none (subject to change)]
// WDM
// n/a
// 2<16>
// 16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths
int WDM_42::calculateCycles(const State& state) const
{
    // 2   2           imm       ........ . WDM
    int cycles = 0;
    // 16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths
    return cycles;
}

// XBA Exchange B and A 8-bit Accumulators [Flags affected: n,z]
// XBA
// Implied
// 1<>
int XBA_EB::calculateCycles(const State& state) const
{
    // 1   3           imp       *.....*. . XBA
    int cycles = 3;
    return cycles;
}

// XCE Exchange Carry and Emulation Flags [Flags affected: m,b/x,c,e]
// XCE
// Implied
// 1<>
int XCE_FB::calculateCycles(const State& state) const
{
    // 1   2           imp       .......* * XCE
    int cycles = 2;
    return cycles;
}

}
