#include "InstructionMap.h"

#include <stdint.h>

#include "InstructionImplementations.h"
#include "State.h"

Instruction* InstructionMap::getInstruction(uint8_t code) const
{
    return instructions[code].get();
}

InstructionMap::InstructionMap()
{
    instructions[0x61] = std::make_unique<ADC_61>("ADC (dp,X)", "DP Indexed Indirect,X");
    instructions[0x63] = std::make_unique<ADC_63>("ADC sr,S", "Stack Relative");
    instructions[0x65] = std::make_unique<ADC_65>("ADC dp", "Direct Page");
    instructions[0x67] = std::make_unique<ADC_67>("ADC [dp]", "DP Indirect Long");
    instructions[0x69] = std::make_unique<ADC_69>("ADC #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0x6D] = std::make_unique<ADC_6D>("ADC addr", "Absolute");
    instructions[0x6F] = std::make_unique<ADC_6F>("ADC long", "Absolute Long");
    instructions[0x71] = std::make_unique<ADC_71>("ADC (dp),Y", "DP Indirect Indexed, Y");
    instructions[0x72] = std::make_unique<ADC_72>("ADC (dp)", "DP Indirect");
    instructions[0x73] = std::make_unique<ADC_73>("ADC (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0x75] = std::make_unique<ADC_75>("ADC dp,X", "DP Indexed,X");
    instructions[0x77] = std::make_unique<ADC_77>("ADC [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0x79] = std::make_unique<ADC_79>("ADC addr,Y", "Absolute Indexed,Y");
    instructions[0x7D] = std::make_unique<ADC_7D>("ADC addr,X", "Absolute Indexed,X");
    instructions[0x7F] = std::make_unique<ADC_7F>("ADC long,X", "Absolute Long Indexed,X");
    instructions[0x21] = std::make_unique<AND_21>("AND (dp,X)", "DP Indexed Indirect,X");
    instructions[0x23] = std::make_unique<AND_23>("AND sr,S", "Stack Relative");
    instructions[0x25] = std::make_unique<AND_25>("AND dp", "Direct Page");
    instructions[0x27] = std::make_unique<AND_27>("AND [dp]", "DP Indirect Long");
    instructions[0x29] = std::make_unique<AND_29>("AND #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0x2D] = std::make_unique<AND_2D>("AND addr", "Absolute");
    instructions[0x2F] = std::make_unique<AND_2F>("AND long", "Absolute Long");
    instructions[0x31] = std::make_unique<AND_31>("AND (dp),Y", "DP Indirect Indexed, Y");
    instructions[0x32] = std::make_unique<AND_32>("AND (dp)", "DP Indirect");
    instructions[0x33] = std::make_unique<AND_33>("AND (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0x35] = std::make_unique<AND_35>("AND dp,X", "DP Indexed,X");
    instructions[0x37] = std::make_unique<AND_37>("AND [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0x39] = std::make_unique<AND_39>("AND addr,Y", "Absolute Indexed,Y");
    instructions[0x3D] = std::make_unique<AND_3D>("AND addr,X", "Absolute Indexed,X");
    instructions[0x3F] = std::make_unique<AND_3F>("AND long,X", "Absolute Long Indexed,X");
    instructions[0x06] = std::make_unique<ASL_06>("ASL dp", "Direct Page");
    instructions[0x0A] = std::make_unique<ASL_0A>("ASL A", "Accumulator");
    instructions[0x0E] = std::make_unique<ASL_0E>("ASL addr", "Absolute");
    instructions[0x16] = std::make_unique<ASL_16>("ASL dp,X", "DP Indexed,X");
    instructions[0x1E] = std::make_unique<ASL_1E>("ASL addr,X", "Absolute Indexed,X");
    instructions[0x90] = std::make_unique<BCC_90>("BCC nearlabel", "Program Counter Relative");
    instructions[0xB0] = std::make_unique<BCS_B0>("BCS nearlabel", "Program Counter Relative");
    instructions[0xF0] = std::make_unique<BEQ_F0>("BEQ nearlabel", "Program Counter Relative");
    instructions[0x24] = std::make_unique<BIT_24>("BIT dp", "Direct Page");
    instructions[0x2C] = std::make_unique<BIT_2C>("BIT addr", "Absolute");
    instructions[0x34] = std::make_unique<BIT_34>("BIT dp,X", "DP Indexed,X");
    instructions[0x3C] = std::make_unique<BIT_3C>("BIT addr,X", "Absolute Indexed,X");
    instructions[0x89] = std::make_unique<BIT_89>("BIT #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0x30] = std::make_unique<BMI_30>("BMI nearlabel", "Program Counter Relative");
    instructions[0xD0] = std::make_unique<BNE_D0>("BNE nearlabel", "Program Counter Relative");
    instructions[0x10] = std::make_unique<BPL_10>("BPL nearlabel", "Program Counter Relative");
    instructions[0x80] = std::make_unique<BRA_80>("BRA nearlabel", "Program Counter Relative");
    instructions[0x00] = std::make_unique<BRK_00>("BRK", "Stack/Interrupt"); // 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
    instructions[0x82] = std::make_unique<BRL_82>("BRL label", "Program Counter Relative Long");
    instructions[0x50] = std::make_unique<BVC_50>("BVC nearlabel", "Program Counter Relative");
    instructions[0x70] = std::make_unique<BVS_70>("BVS nearlabel", "Program Counter Relative");
    instructions[0x18] = std::make_unique<CLC_18>("CLC", "Implied");
    instructions[0xD8] = std::make_unique<CLD_D8>("CLD", "Implied");
    instructions[0x58] = std::make_unique<CLI_58>("CLI", "Implied");
    instructions[0xB8] = std::make_unique<CLV_B8>("CLV", "Implied");
    instructions[0xC1] = std::make_unique<CMP_C1>("CMP (dp,X)", "DP Indexed Indirect,X");
    instructions[0xC3] = std::make_unique<CMP_C3>("CMP sr,S", "Stack Relative");
    instructions[0xC5] = std::make_unique<CMP_C5>("CMP dp", "Direct Page");
    instructions[0xC7] = std::make_unique<CMP_C7>("CMP [dp]", "DP Indirect Long");
    instructions[0xC9] = std::make_unique<CMP_C9>("CMP #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0xCD] = std::make_unique<CMP_CD>("CMP addr", "Absolute");
    instructions[0xCF] = std::make_unique<CMP_CF>("CMP long", "Absolute Long");
    instructions[0xD1] = std::make_unique<CMP_D1>("CMP (dp),Y", "DP Indirect Indexed, Y");
    instructions[0xD2] = std::make_unique<CMP_D2>("CMP (dp)", "DP Indirect");
    instructions[0xD3] = std::make_unique<CMP_D3>("CMP (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0xD5] = std::make_unique<CMP_D5>("CMP dp,X", "DP Indexed,X");
    instructions[0xD7] = std::make_unique<CMP_D7>("CMP [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0xD9] = std::make_unique<CMP_D9>("CMP addr,Y", "Absolute Indexed,Y");
    instructions[0xDD] = std::make_unique<CMP_DD>("CMP addr,X", "Absolute Indexed,X");
    instructions[0xDF] = std::make_unique<CMP_DF>("CMP long,X", "Absolute Long Indexed,X");
    instructions[0x02] = std::make_unique<COP_02>("COP const", "Stack/Interrupt"); // 18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte
    instructions[0xE0] = std::make_unique<CPX_E0>("CPX #const", "Immediate"); // 19: Add 1 byte if x = 0 (16 - bit index registers)
    instructions[0xE4] = std::make_unique<CPX_E4>("CPX dp", "Direct Page");
    instructions[0xEC] = std::make_unique<CPX_EC>("CPX addr", "Absolute");
    instructions[0xC0] = std::make_unique<CPY_C0>("CPY #const", "Immediate"); // 19: Add 1 byte if x = 0 (16 - bit index registers)
    instructions[0xC4] = std::make_unique<CPY_C4>("CPY dp", "Direct Page");
    instructions[0xCC] = std::make_unique<CPY_CC>("CPY addr", "Absolute");
    instructions[0x3A] = std::make_unique<DEC_3A>("DEC A", "Accumulator");
    instructions[0xC6] = std::make_unique<DEC_C6>("DEC dp", "Direct Page");
    instructions[0xCE] = std::make_unique<DEC_CE>("DEC addr", "Absolute");
    instructions[0xD6] = std::make_unique<DEC_D6>("DEC dp,X", "DP Indexed,X");
    instructions[0xDE] = std::make_unique<DEC_DE>("DEC addr,X", "Absolute Indexed,X");
    instructions[0xCA] = std::make_unique<DEX_CA>("DEX", "Implied");
    instructions[0x88] = std::make_unique<DEY_88>("DEY", "Implied");
    instructions[0x41] = std::make_unique<EOR_41>("EOR (dp,X)", "DP Indexed Indirect,X");
    instructions[0x43] = std::make_unique<EOR_43>("EOR sr,S", "Stack Relative");
    instructions[0x45] = std::make_unique<EOR_45>("EOR dp", "Direct Page");
    instructions[0x47] = std::make_unique<EOR_47>("EOR [dp]", "DP Indirect Long");
    instructions[0x49] = std::make_unique<EOR_49>("EOR #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0x4D] = std::make_unique<EOR_4D>("EOR addr", "Absolute");
    instructions[0x4F] = std::make_unique<EOR_4F>("EOR long", "Absolute Long");
    instructions[0x51] = std::make_unique<EOR_51>("EOR (dp),Y", "DP Indirect Indexed, Y");
    instructions[0x52] = std::make_unique<EOR_52>("EOR (dp)", "DP Indirect");
    instructions[0x53] = std::make_unique<EOR_53>("EOR (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0x55] = std::make_unique<EOR_55>("EOR dp,X", "DP Indexed,X");
    instructions[0x57] = std::make_unique<EOR_57>("EOR [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0x59] = std::make_unique<EOR_59>("EOR addr,Y", "Absolute Indexed,Y");
    instructions[0x5D] = std::make_unique<EOR_5D>("EOR addr,X", "Absolute Indexed,X");
    instructions[0x5F] = std::make_unique<EOR_5F>("EOR long,X", "Absolute Long Indexed,X");
    instructions[0x1A] = std::make_unique<INC_1A>("INC A", "Accumulator");
    instructions[0xE6] = std::make_unique<INC_E6>("INC dp", "Direct Page");
    instructions[0xEE] = std::make_unique<INC_EE>("INC addr", "Absolute");
    instructions[0xF6] = std::make_unique<INC_F6>("INC dp,X", "DP Indexed,X");
    instructions[0xFE] = std::make_unique<INC_FE>("INC addr,X", "Absolute Indexed,X");
    instructions[0xE8] = std::make_unique<INX_E8>("INX", "Implied");
    instructions[0xC8] = std::make_unique<INY_C8>("INY", "Implied");
    instructions[0x4C] = std::make_unique<JMP_4C>("JMP addr", "Absolute");
    instructions[0x5C] = std::make_unique<JMP_5C>("JMP long", "Absolute Long");
    instructions[0x6C] = std::make_unique<JMP_6C>("JMP (addr)", "Absolute Indirect");
    instructions[0x7C] = std::make_unique<JMP_7C>("JMP (addr,X)", "Absolute Indexed Indirect");
    instructions[0xDC] = std::make_unique<JMP_DC>("JMP [addr]", "Absolute Indirect Long");
    instructions[0x20] = std::make_unique<JSR_20>("JSR addr", "Absolute");
    instructions[0x22] = std::make_unique<JSR_22>("JSR long", "Absolute Long");
    instructions[0xFC] = std::make_unique<JSR_FC>("JSR (addr,X))", "Absolute Indexed Indirect");
    instructions[0xA1] = std::make_unique<LDA_A1>("LDA (dp,X)", "DP Indexed Indirect,X");
    instructions[0xA3] = std::make_unique<LDA_A3>("LDA sr,S", "Stack Relative");
    instructions[0xA5] = std::make_unique<LDA_A5>("LDA dp", "Direct Page");
    instructions[0xA7] = std::make_unique<LDA_A7>("LDA [dp]", "DP Indirect Long");
    instructions[0xA9] = std::make_unique<LDA_A9>("LDA #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0xAD] = std::make_unique<LDA_AD>("LDA addr", "Absolute");
    instructions[0xAF] = std::make_unique<LDA_AF>("LDA long", "Absolute Long");
    instructions[0xB1] = std::make_unique<LDA_B1>("LDA (dp),Y", "DP Indirect Indexed, Y");
    instructions[0xB2] = std::make_unique<LDA_B2>("LDA (dp)", "DP Indirect");
    instructions[0xB3] = std::make_unique<LDA_B3>("LDA (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0xB5] = std::make_unique<LDA_B5>("LDA dp,X", "DP Indexed,X");
    instructions[0xB7] = std::make_unique<LDA_B7>("LDA [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0xB9] = std::make_unique<LDA_B9>("LDA addr,Y", "Absolute Indexed,Y");
    instructions[0xBD] = std::make_unique<LDA_BD>("LDA addr,X", "Absolute Indexed,X");
    instructions[0xBF] = std::make_unique<LDA_BF>("LDA long,X", "Absolute Long Indexed,X");
    instructions[0xA2] = std::make_unique<LDX_A2>("LDX #const", "Immediate"); // 19: Add 1 byte if x = 0 (16 - bit index registers)
    instructions[0xA6] = std::make_unique<LDX_A6>("LDX dp", "Direct Page");
    instructions[0xAE] = std::make_unique<LDX_AE>("LDX addr", "Absolute");
    instructions[0xB6] = std::make_unique<LDX_B6>("LDX dp,Y", "DP Indexed,Y");
    instructions[0xBE] = std::make_unique<LDX_BE>("LDX addr,Y", "Absolute Indexed,Y");
    instructions[0xA0] = std::make_unique<LDY_A0>("LDY #const", "Immediate"); // 19: Add 1 byte if x = 0 (16 - bit index registers)
    instructions[0xA4] = std::make_unique<LDY_A4>("LDY dp", "Direct Page");
    instructions[0xAC] = std::make_unique<LDY_AC>("LDY addr", "Absolute");
    instructions[0xB4] = std::make_unique<LDY_B4>("LDY dp,X", "DP Indexed,X");
    instructions[0xBC] = std::make_unique<LDY_BC>("LDY addr,X", "Absolute Indexed,X");
    instructions[0x46] = std::make_unique<LSR_46>("LSR dp", "Direct Page");
    instructions[0x4A] = std::make_unique<LSR_4A>("LSR A", "Accumulator");
    instructions[0x4E] = std::make_unique<LSR_4E>("LSR addr", "Absolute");
    instructions[0x56] = std::make_unique<LSR_56>("LSR dp,X", "DP Indexed,X");
    instructions[0x5E] = std::make_unique<LSR_5E>("LSR addr,X", "Absolute Indexed,X");
    instructions[0x54] = std::make_unique<MVN_54>("MVN srcbk,destbk", "Block Move");
    instructions[0x44] = std::make_unique<MVN_44>("MVN srcbk,destbk", "Block Move");
    instructions[0xEA] = std::make_unique<NOP_EA>("NOP", "Implied");
    instructions[0x01] = std::make_unique<ORA_01>("ORA (dp,X)", "DP Indexed Indirect,X");
    instructions[0x03] = std::make_unique<ORA_03>("ORA sr,S", "Stack Relative");
    instructions[0x05] = std::make_unique<ORA_05>("ORA dp", "Direct Page");
    instructions[0x07] = std::make_unique<ORA_07>("ORA [dp]", "DP Indirect Long");
    instructions[0x09] = std::make_unique<ORA_09>("ORA #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0x0D] = std::make_unique<ORA_0D>("ORA addr", "Absolute");
    instructions[0x0F] = std::make_unique<ORA_0F>("ORA long", "Absolute Long");
    instructions[0x11] = std::make_unique<ORA_11>("ORA (dp),Y", "DP Indirect Indexed, Y");
    instructions[0x12] = std::make_unique<ORA_12>("ORA (dp)", "DP Indirect");
    instructions[0x13] = std::make_unique<ORA_13>("ORA (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0x15] = std::make_unique<ORA_15>("ORA dp,X", "DP Indexed,X");
    instructions[0x17] = std::make_unique<ORA_17>("ORA [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0x19] = std::make_unique<ORA_19>("ORA addr,Y", "Absolute Indexed,Y");
    instructions[0x1D] = std::make_unique<ORA_1D>("ORA addr,X", "Absolute Indexed,X");
    instructions[0x1F] = std::make_unique<ORA_1F>("ORA long,X", "Absolute Long Indexed,X");
    instructions[0xF4] = std::make_unique<PEA_F4>("PEA addr", "Stack (Absolute)");
    instructions[0xD4] = std::make_unique<PEI_D4>("PEI (dp)", "Stack (DP Indirect)");
    instructions[0x62] = std::make_unique<PER_62>("PER label", "Stack (PC Relative Long)");
    instructions[0x48] = std::make_unique<PHA_48>("PHA", "Stack (Push)");
    instructions[0x8B] = std::make_unique<PHB_8B>("PHB", "Stack (Push)");
    instructions[0x0B] = std::make_unique<PHD_0B>("PHD", "Stack (Push)");
    instructions[0x4B] = std::make_unique<PHK_4B>("PHK", "Stack (Push)");
    instructions[0x08] = std::make_unique<PHP_08>("PHP", "Stack (Push)");
    instructions[0xDA] = std::make_unique<PHX_DA>("PHX", "Stack (Push)");
    instructions[0x5A] = std::make_unique<PHY_5A>("PHY", "Stack (Push)");
    instructions[0x68] = std::make_unique<PLA_68>("PLA", "Stack (Pull)");
    instructions[0xAB] = std::make_unique<PLB_AB>("PLB", "Stack (Pull)");
    instructions[0x2B] = std::make_unique<PLD_2B>("PLD", "Stack (Pull)");
    instructions[0x28] = std::make_unique<PLP_28>("PLP", "Stack (Pull)");
    instructions[0xFA] = std::make_unique<PLX_FA>("PLX", "Stack (Pull)");
    instructions[0x7A] = std::make_unique<PLY_7A>("PLY", "Stack (Pull)");
    instructions[0xC2] = std::make_unique<REP_C2>("REP #const", "Immediate");
    instructions[0x26] = std::make_unique<ROL_26>("ROL dp", "Direct Page");
    instructions[0x2A] = std::make_unique<ROL_2A>("ROL A", "Accumulator");
    instructions[0x2E] = std::make_unique<ROL_2E>("ROL addr", "Absolute");
    instructions[0x36] = std::make_unique<ROL_36>("ROL dp,X", "DP Indexed,X");
    instructions[0x3E] = std::make_unique<ROL_3E>("ROL addr,X", "Absolute Indexed,X");
    instructions[0x66] = std::make_unique<ROR_66>("ROR dp", "Direct Page");
    instructions[0x6A] = std::make_unique<ROR_6A>("ROR A", "Accumulator");
    instructions[0x6E] = std::make_unique<ROR_6E>("ROR addr", "Absolute");
    instructions[0x76] = std::make_unique<ROR_76>("ROR dp,X", "DP Indexed,X");
    instructions[0x7E] = std::make_unique<ROR_7E>("ROR addr,X", "Absolute Indexed,X");
    instructions[0x40] = std::make_unique<RTI_40>("RTI", "Stack (RTI)");
    instructions[0x6B] = std::make_unique<RTL_6B>("RTL", "Stack (RTL)");
    instructions[0x60] = std::make_unique<RTS_60>("RTS", "Stack (RTS)");
    instructions[0xE1] = std::make_unique<SBC_E1>("SBC (dp,X)", "DP Indexed Indirect,X");
    instructions[0xE3] = std::make_unique<SBC_E3>("SBC sr,S", "Stack Relative");
    instructions[0xE5] = std::make_unique<SBC_E5>("SBC dp", "Direct Page");
    instructions[0xE7] = std::make_unique<SBC_E7>("SBC [dp]", "DP Indirect Long");
    instructions[0xE9] = std::make_unique<SBC_E9>("SBC #const", "Immediate"); // 17: Add 1 byte if m = 0 (16 - bit memory / accumulator)
    instructions[0xED] = std::make_unique<SBC_ED>("SBC addr", "Absolute");
    instructions[0xEF] = std::make_unique<SBC_EF>("SBC long", "Absolute Long");
    instructions[0xF1] = std::make_unique<SBC_F1>("SBC (dp),Y", "DP Indirect Indexed, Y");
    instructions[0xF2] = std::make_unique<SBC_F2>("SBC (dp)", "DP Indirect");
    instructions[0xF3] = std::make_unique<SBC_F3>("SBC (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0xF5] = std::make_unique<SBC_F5>("SBC dp,X", "DP Indexed,X");
    instructions[0xF7] = std::make_unique<SBC_F7>("SBC [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0xF9] = std::make_unique<SBC_F9>("SBC addr,Y", "Absolute Indexed,Y");
    instructions[0xFD] = std::make_unique<SBC_FD>("SBC addr,X", "Absolute Indexed,X");
    instructions[0xFF] = std::make_unique<SBC_FF>("SBC long,X", "Absolute Long Indexed,X");
    instructions[0x38] = std::make_unique<SEC_38>("SEC", "Implied");
    instructions[0xF8] = std::make_unique<SED_F8>("SED", "Implied");
    instructions[0x78] = std::make_unique<SEI_78>("SEI", "Implied");
    instructions[0xE2] = std::make_unique<SEP_E2>("SEP", "Immediate");
    instructions[0x81] = std::make_unique<STA_81>("STA (dp,X)", "DP Indexed Indirect,X");
    instructions[0x83] = std::make_unique<STA_83>("STA sr,S", "Stack Relative");
    instructions[0x85] = std::make_unique<STA_85>("STA dp", "Direct Page");
    instructions[0x87] = std::make_unique<STA_87>("STA [dp]", "DP Indirect Long");
    instructions[0x8D] = std::make_unique<STA_8D>("STA addr", "Absolute");
    instructions[0x8F] = std::make_unique<STA_8F>("STA long", "Absolute Long");
    instructions[0x91] = std::make_unique<STA_91>("STA (dp),Y", "DP Indirect Indexed, Y");
    instructions[0x92] = std::make_unique<STA_92>("STA (dp)", "DP Indirect");
    instructions[0x93] = std::make_unique<STA_93>("STA (sr,S),Y", "SR Indirect Indexed,Y");
    instructions[0x95] = std::make_unique<STA_95>("STA dpX", "DP Indexed,X");
    instructions[0x97] = std::make_unique<STA_97>("STA [dp],Y", "DP Indirect Long Indexed, Y");
    instructions[0x99] = std::make_unique<STA_99>("STA addr,Y", "Absolute Indexed,Y");
    instructions[0x9D] = std::make_unique<STA_9D>("STA addr,X", "Absolute Indexed,X");
    instructions[0x9F] = std::make_unique<STA_9F>("STA long,X", "Absolute Long Indexed,X");
    instructions[0xDB] = std::make_unique<STP_DB>("STP", "Implied");
    instructions[0x86] = std::make_unique<STX_86>("STX dp", "Direct Page");
    instructions[0x8E] = std::make_unique<STX_8E>("STX addr", "Absolute");
    instructions[0x96] = std::make_unique<STX_96>("STX dp,Y", "DP Indexed,Y");
    instructions[0x84] = std::make_unique<STY_84>("STY dp", "Direct Page");
    instructions[0x8C] = std::make_unique<STY_8C>("STY addr", "Absolute");
    instructions[0x94] = std::make_unique<STY_94>("STY dp,X", "DP Indexed,X");
    instructions[0x64] = std::make_unique<STZ_64>("STZ dp", "Direct Page");
    instructions[0x74] = std::make_unique<STZ_74>("STZ dp,X", "DP Indexed,X");
    instructions[0x9C] = std::make_unique<STZ_9C>("STZ addr", "Absolute");
    instructions[0x9E] = std::make_unique<STZ_9E>("STZ addr,X", "Absolute Indexed,X");
    instructions[0xAA] = std::make_unique<TAX_AA>("TAX", "Implied");
    instructions[0xA8] = std::make_unique<TAY_A8>("TAY", "Implied");
    instructions[0x5B] = std::make_unique<TCD_5B>("TCD", "Implied");
    instructions[0x1B] = std::make_unique<TCS_1B>("TCS", "Implied");
    instructions[0x7B] = std::make_unique<TDC_7B>("TDC", "Implied");
    instructions[0x14] = std::make_unique<TRB_14>("TRB dp", "Direct Page");
    instructions[0x1C] = std::make_unique<TRB_1C>("TRB addr", "Absolute");
    instructions[0x04] = std::make_unique<TSB_04>("TSB dp", "Direct Page");
    instructions[0x0C] = std::make_unique<TSB_0C>("TSB addr", "Absolute");
    instructions[0x3B] = std::make_unique<TSC_3B>("TSC", "Implied");
    instructions[0xBA] = std::make_unique<TSX_BA>("TSX", "Implied");
    instructions[0x8A] = std::make_unique<TXA_8A>("TXA", "Implied");
    instructions[0x9A] = std::make_unique<TXS_9A>("TXS", "Implied");
    instructions[0x9B] = std::make_unique<TXY_9B>("TXY", "Implied");
    instructions[0x98] = std::make_unique<TYA_98>("TYA", "Implied");
    instructions[0xBB] = std::make_unique<TYX_BB>("TYX", "Implied");
    instructions[0xCB] = std::make_unique<WAI_CB>("WAI", "Implied");
    instructions[0x42] = std::make_unique<WDM_42>("WDM", "n/a"); // 16: Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths
    instructions[0xEB] = std::make_unique<XBA_EB>("XBA", "Implied");
    instructions[0xFB] = std::make_unique<XCE_FB>("XCE", "Implied");
}
