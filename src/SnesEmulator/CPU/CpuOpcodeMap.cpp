#include "CpuOpcodeMap.h"

#include "CpuOpcode.h"

namespace CPU {

Instruction* OpcodeMap::getNextInstruction(State& state) const
{
    Byte opcode = state.applyProgramByte();
    if (state.is16Bit(State::m) && instructions16BitM[opcode]) {
        return instructions16BitM[opcode].get();
    } else if (state.is16Bit(State::x) && instructions16BitX[opcode]) {
        return instructions16BitX[opcode].get();
    } else {
        return instructions[opcode].get();
    }
}

OpcodeMap::OpcodeMap(State& state)
{
    instructions[0x61] = std::make_unique<Opcode::ADC_61>(state);
    instructions[0x63] = std::make_unique<Opcode::ADC_63>(state);
    instructions[0x65] = std::make_unique<Opcode::ADC_65>(state);
    instructions[0x67] = std::make_unique<Opcode::ADC_67>(state);
    instructions[0x69] = std::make_unique<Opcode::ADC_69>(state);
    instructions16BitM[0x69] = std::make_unique<Opcode::ADC_69_16Bit>(state);
    instructions[0x6D] = std::make_unique<Opcode::ADC_6D>(state);
    instructions[0x6F] = std::make_unique<Opcode::ADC_6F>(state);
    instructions[0x71] = std::make_unique<Opcode::ADC_71>(state);
    instructions[0x72] = std::make_unique<Opcode::ADC_72>(state);
    instructions[0x73] = std::make_unique<Opcode::ADC_73>(state);
    instructions[0x75] = std::make_unique<Opcode::ADC_75>(state);
    instructions[0x77] = std::make_unique<Opcode::ADC_77>(state);
    instructions[0x79] = std::make_unique<Opcode::ADC_79>(state);
    instructions[0x7D] = std::make_unique<Opcode::ADC_7D>(state);
    instructions[0x7F] = std::make_unique<Opcode::ADC_7F>(state);
    instructions[0x21] = std::make_unique<Opcode::AND_21>(state);
    instructions[0x23] = std::make_unique<Opcode::AND_23>(state);
    instructions[0x25] = std::make_unique<Opcode::AND_25>(state);
    instructions[0x27] = std::make_unique<Opcode::AND_27>(state);
    instructions[0x29] = std::make_unique<Opcode::AND_29>(state);
    instructions16BitM[0x29] = std::make_unique<Opcode::AND_29_16Bit>(state);
    instructions[0x2D] = std::make_unique<Opcode::AND_2D>(state);
    instructions[0x2F] = std::make_unique<Opcode::AND_2F>(state);
    instructions[0x31] = std::make_unique<Opcode::AND_31>(state);
    instructions[0x32] = std::make_unique<Opcode::AND_32>(state);
    instructions[0x33] = std::make_unique<Opcode::AND_33>(state);
    instructions[0x35] = std::make_unique<Opcode::AND_35>(state);
    instructions[0x37] = std::make_unique<Opcode::AND_37>(state);
    instructions[0x39] = std::make_unique<Opcode::AND_39>(state);
    instructions[0x3D] = std::make_unique<Opcode::AND_3D>(state);
    instructions[0x3F] = std::make_unique<Opcode::AND_3F>(state);
    instructions[0x06] = std::make_unique<Opcode::ASL_06>(state);
    instructions[0x0A] = std::make_unique<Opcode::ASL_0A>(state);
    instructions[0x0E] = std::make_unique<Opcode::ASL_0E>(state);
    instructions[0x16] = std::make_unique<Opcode::ASL_16>(state);
    instructions[0x1E] = std::make_unique<Opcode::ASL_1E>(state);
    instructions[0x90] = std::make_unique<Opcode::BCC_90>(state);
    instructions[0xB0] = std::make_unique<Opcode::BCS_B0>(state);
    instructions[0xF0] = std::make_unique<Opcode::BEQ_F0>(state);
    instructions[0x24] = std::make_unique<Opcode::BIT_24>(state);
    instructions[0x2C] = std::make_unique<Opcode::BIT_2C>(state);
    instructions[0x34] = std::make_unique<Opcode::BIT_34>(state);
    instructions[0x3C] = std::make_unique<Opcode::BIT_3C>(state);
    instructions[0x89] = std::make_unique<Opcode::BIT_89>(state);
    instructions16BitM[0x89] = std::make_unique<Opcode::BIT_89_16Bit>(state);
    instructions[0x30] = std::make_unique<Opcode::BMI_30>(state);
    instructions[0xD0] = std::make_unique<Opcode::BNE_D0>(state);
    instructions[0x10] = std::make_unique<Opcode::BPL_10>(state);
    instructions[0x80] = std::make_unique<Opcode::BRA_80>(state);
    instructions[0x00] = std::make_unique<Opcode::BRK_00>(state);
    instructions[0x82] = std::make_unique<Opcode::BRL_82>(state);
    instructions[0x50] = std::make_unique<Opcode::BVC_50>(state);
    instructions[0x70] = std::make_unique<Opcode::BVS_70>(state);
    instructions[0x18] = std::make_unique<Opcode::CLC_18>(state);
    instructions[0xD8] = std::make_unique<Opcode::CLD_D8>(state);
    instructions[0x58] = std::make_unique<Opcode::CLI_58>(state);
    instructions[0xB8] = std::make_unique<Opcode::CLV_B8>(state);
    instructions[0xC1] = std::make_unique<Opcode::CMP_C1>(state);
    instructions[0xC3] = std::make_unique<Opcode::CMP_C3>(state);
    instructions[0xC5] = std::make_unique<Opcode::CMP_C5>(state);
    instructions[0xC7] = std::make_unique<Opcode::CMP_C7>(state);
    instructions[0xC9] = std::make_unique<Opcode::CMP_C9>(state);
    instructions16BitM[0xC9] = std::make_unique<Opcode::CMP_C9_16Bit>(state);
    instructions[0xCD] = std::make_unique<Opcode::CMP_CD>(state);
    instructions[0xCF] = std::make_unique<Opcode::CMP_CF>(state);
    instructions[0xD1] = std::make_unique<Opcode::CMP_D1>(state);
    instructions[0xD2] = std::make_unique<Opcode::CMP_D2>(state);
    instructions[0xD3] = std::make_unique<Opcode::CMP_D3>(state);
    instructions[0xD5] = std::make_unique<Opcode::CMP_D5>(state);
    instructions[0xD7] = std::make_unique<Opcode::CMP_D7>(state);
    instructions[0xD9] = std::make_unique<Opcode::CMP_D9>(state);
    instructions[0xDD] = std::make_unique<Opcode::CMP_DD>(state);
    instructions[0xDF] = std::make_unique<Opcode::CMP_DF>(state);
    instructions[0x02] = std::make_unique<Opcode::COP_02>(state);
    instructions[0xE0] = std::make_unique<Opcode::CPX_E0>(state);
    instructions16BitX[0xE0] = std::make_unique<Opcode::CPX_E0_16Bit>(state);
    instructions[0xE4] = std::make_unique<Opcode::CPX_E4>(state);
    instructions[0xEC] = std::make_unique<Opcode::CPX_EC>(state);
    instructions[0xC0] = std::make_unique<Opcode::CPY_C0>(state);
    instructions16BitX[0xC0] = std::make_unique<Opcode::CPY_C0_16Bit>(state);
    instructions[0xC4] = std::make_unique<Opcode::CPY_C4>(state);
    instructions[0xCC] = std::make_unique<Opcode::CPY_CC>(state);
    instructions[0x3A] = std::make_unique<Opcode::DEC_3A>(state);
    instructions[0xC6] = std::make_unique<Opcode::DEC_C6>(state);
    instructions[0xCE] = std::make_unique<Opcode::DEC_CE>(state);
    instructions[0xD6] = std::make_unique<Opcode::DEC_D6>(state);
    instructions[0xDE] = std::make_unique<Opcode::DEC_DE>(state);
    instructions[0xCA] = std::make_unique<Opcode::DEX_CA>(state);
    instructions[0x88] = std::make_unique<Opcode::DEY_88>(state);
    instructions[0x41] = std::make_unique<Opcode::EOR_41>(state);
    instructions[0x43] = std::make_unique<Opcode::EOR_43>(state);
    instructions[0x45] = std::make_unique<Opcode::EOR_45>(state);
    instructions[0x47] = std::make_unique<Opcode::EOR_47>(state);
    instructions[0x49] = std::make_unique<Opcode::EOR_49>(state);
    instructions16BitM[0x49] = std::make_unique<Opcode::EOR_49_16Bit>(state);
    instructions[0x4D] = std::make_unique<Opcode::EOR_4D>(state);
    instructions[0x4F] = std::make_unique<Opcode::EOR_4F>(state);
    instructions[0x51] = std::make_unique<Opcode::EOR_51>(state);
    instructions[0x52] = std::make_unique<Opcode::EOR_52>(state);
    instructions[0x53] = std::make_unique<Opcode::EOR_53>(state);
    instructions[0x55] = std::make_unique<Opcode::EOR_55>(state);
    instructions[0x57] = std::make_unique<Opcode::EOR_57>(state);
    instructions[0x59] = std::make_unique<Opcode::EOR_59>(state);
    instructions[0x5D] = std::make_unique<Opcode::EOR_5D>(state);
    instructions[0x5F] = std::make_unique<Opcode::EOR_5F>(state);
    instructions[0x1A] = std::make_unique<Opcode::INC_1A>(state);
    instructions[0xE6] = std::make_unique<Opcode::INC_E6>(state);
    instructions[0xEE] = std::make_unique<Opcode::INC_EE>(state);
    instructions[0xF6] = std::make_unique<Opcode::INC_F6>(state);
    instructions[0xFE] = std::make_unique<Opcode::INC_FE>(state);
    instructions[0xE8] = std::make_unique<Opcode::INX_E8>(state);
    instructions[0xC8] = std::make_unique<Opcode::INY_C8>(state);
    instructions[0x4C] = std::make_unique<Opcode::JMP_4C>(state);
    instructions[0x5C] = std::make_unique<Opcode::JMP_5C>(state);
    instructions[0x6C] = std::make_unique<Opcode::JMP_6C>(state);
    instructions[0x7C] = std::make_unique<Opcode::JMP_7C>(state);
    instructions[0xDC] = std::make_unique<Opcode::JMP_DC>(state);
    instructions[0x20] = std::make_unique<Opcode::JSR_20>(state);
    instructions[0x22] = std::make_unique<Opcode::JSR_22>(state);
    instructions[0xFC] = std::make_unique<Opcode::JSR_FC>(state);
    instructions[0xA1] = std::make_unique<Opcode::LDA_A1>(state);
    instructions[0xA3] = std::make_unique<Opcode::LDA_A3>(state);
    instructions[0xA5] = std::make_unique<Opcode::LDA_A5>(state);
    instructions[0xA7] = std::make_unique<Opcode::LDA_A7>(state);
    instructions[0xA9] = std::make_unique<Opcode::LDA_A9>(state);
    instructions16BitM[0xA9] = std::make_unique<Opcode::LDA_A9_16Bit>(state);
    instructions[0xAD] = std::make_unique<Opcode::LDA_AD>(state);
    instructions[0xAF] = std::make_unique<Opcode::LDA_AF>(state);
    instructions[0xB1] = std::make_unique<Opcode::LDA_B1>(state);
    instructions[0xB2] = std::make_unique<Opcode::LDA_B2>(state);
    instructions[0xB3] = std::make_unique<Opcode::LDA_B3>(state);
    instructions[0xB5] = std::make_unique<Opcode::LDA_B5>(state);
    instructions[0xB7] = std::make_unique<Opcode::LDA_B7>(state);
    instructions[0xB9] = std::make_unique<Opcode::LDA_B9>(state);
    instructions[0xBD] = std::make_unique<Opcode::LDA_BD>(state);
    instructions[0xBF] = std::make_unique<Opcode::LDA_BF>(state);
    instructions[0xA2] = std::make_unique<Opcode::LDX_A2>(state);
    instructions16BitX[0xA2] = std::make_unique<Opcode::LDX_A2_16Bit>(state);
    instructions[0xA6] = std::make_unique<Opcode::LDX_A6>(state);
    instructions[0xAE] = std::make_unique<Opcode::LDX_AE>(state);
    instructions[0xB6] = std::make_unique<Opcode::LDX_B6>(state);
    instructions[0xBE] = std::make_unique<Opcode::LDX_BE>(state);
    instructions[0xA0] = std::make_unique<Opcode::LDY_A0>(state);
    instructions16BitX[0xA0] = std::make_unique<Opcode::LDY_A0_16Bit>(state);
    instructions[0xA4] = std::make_unique<Opcode::LDY_A4>(state);
    instructions[0xAC] = std::make_unique<Opcode::LDY_AC>(state);
    instructions[0xB4] = std::make_unique<Opcode::LDY_B4>(state);
    instructions[0xBC] = std::make_unique<Opcode::LDY_BC>(state);
    instructions[0x46] = std::make_unique<Opcode::LSR_46>(state);
    instructions[0x4A] = std::make_unique<Opcode::LSR_4A>(state);
    instructions[0x4E] = std::make_unique<Opcode::LSR_4E>(state);
    instructions[0x56] = std::make_unique<Opcode::LSR_56>(state);
    instructions[0x5E] = std::make_unique<Opcode::LSR_5E>(state);
    instructions[0x54] = std::make_unique<Opcode::MVN_54>(state);
    instructions[0x44] = std::make_unique<Opcode::MVP_44>(state);
    instructions[0xEA] = std::make_unique<Opcode::NOP_EA>(state);
    instructions[0x01] = std::make_unique<Opcode::ORA_01>(state);
    instructions[0x03] = std::make_unique<Opcode::ORA_03>(state);
    instructions[0x05] = std::make_unique<Opcode::ORA_05>(state);
    instructions[0x07] = std::make_unique<Opcode::ORA_07>(state);
    instructions[0x09] = std::make_unique<Opcode::ORA_09>(state);
    instructions16BitM[0x09] = std::make_unique<Opcode::ORA_09_16Bit>(state);
    instructions[0x0D] = std::make_unique<Opcode::ORA_0D>(state);
    instructions[0x0F] = std::make_unique<Opcode::ORA_0F>(state);
    instructions[0x11] = std::make_unique<Opcode::ORA_11>(state);
    instructions[0x12] = std::make_unique<Opcode::ORA_12>(state);
    instructions[0x13] = std::make_unique<Opcode::ORA_13>(state);
    instructions[0x15] = std::make_unique<Opcode::ORA_15>(state);
    instructions[0x17] = std::make_unique<Opcode::ORA_17>(state);
    instructions[0x19] = std::make_unique<Opcode::ORA_19>(state);
    instructions[0x1D] = std::make_unique<Opcode::ORA_1D>(state);
    instructions[0x1F] = std::make_unique<Opcode::ORA_1F>(state);
    instructions[0xF4] = std::make_unique<Opcode::PEA_F4>(state);
    instructions[0xD4] = std::make_unique<Opcode::PEI_D4>(state);
    instructions[0x62] = std::make_unique<Opcode::PER_62>(state);
    instructions[0x48] = std::make_unique<Opcode::PHA_48>(state);
    instructions[0x8B] = std::make_unique<Opcode::PHB_8B>(state);
    instructions[0x0B] = std::make_unique<Opcode::PHD_0B>(state);
    instructions[0x4B] = std::make_unique<Opcode::PHK_4B>(state);
    instructions[0x08] = std::make_unique<Opcode::PHP_08>(state);
    instructions[0xDA] = std::make_unique<Opcode::PHX_DA>(state);
    instructions[0x5A] = std::make_unique<Opcode::PHY_5A>(state);
    instructions[0x68] = std::make_unique<Opcode::PLA_68>(state);
    instructions[0xAB] = std::make_unique<Opcode::PLB_AB>(state);
    instructions[0x2B] = std::make_unique<Opcode::PLD_2B>(state);
    instructions[0x28] = std::make_unique<Opcode::PLP_28>(state);
    instructions[0xFA] = std::make_unique<Opcode::PLX_FA>(state);
    instructions[0x7A] = std::make_unique<Opcode::PLY_7A>(state);
    instructions[0xC2] = std::make_unique<Opcode::REP_C2>(state);
    instructions[0x26] = std::make_unique<Opcode::ROL_26>(state);
    instructions[0x2A] = std::make_unique<Opcode::ROL_2A>(state);
    instructions[0x2E] = std::make_unique<Opcode::ROL_2E>(state);
    instructions[0x36] = std::make_unique<Opcode::ROL_36>(state);
    instructions[0x3E] = std::make_unique<Opcode::ROL_3E>(state);
    instructions[0x66] = std::make_unique<Opcode::ROR_66>(state);
    instructions[0x6A] = std::make_unique<Opcode::ROR_6A>(state);
    instructions[0x6E] = std::make_unique<Opcode::ROR_6E>(state);
    instructions[0x76] = std::make_unique<Opcode::ROR_76>(state);
    instructions[0x7E] = std::make_unique<Opcode::ROR_7E>(state);
    instructions[0x40] = std::make_unique<Opcode::RTI_40>(state);
    instructions[0x6B] = std::make_unique<Opcode::RTL_6B>(state);
    instructions[0x60] = std::make_unique<Opcode::RTS_60>(state);
    instructions[0xE1] = std::make_unique<Opcode::SBC_E1>(state);
    instructions[0xE3] = std::make_unique<Opcode::SBC_E3>(state);
    instructions[0xE5] = std::make_unique<Opcode::SBC_E5>(state);
    instructions[0xE7] = std::make_unique<Opcode::SBC_E7>(state);
    instructions[0xE9] = std::make_unique<Opcode::SBC_E9>(state);
    instructions16BitM[0xE9] = std::make_unique<Opcode::SBC_E9_16Bit>(state);
    instructions[0xED] = std::make_unique<Opcode::SBC_ED>(state);
    instructions[0xEF] = std::make_unique<Opcode::SBC_EF>(state);
    instructions[0xF1] = std::make_unique<Opcode::SBC_F1>(state);
    instructions[0xF2] = std::make_unique<Opcode::SBC_F2>(state);
    instructions[0xF3] = std::make_unique<Opcode::SBC_F3>(state);
    instructions[0xF5] = std::make_unique<Opcode::SBC_F5>(state);
    instructions[0xF7] = std::make_unique<Opcode::SBC_F7>(state);
    instructions[0xF9] = std::make_unique<Opcode::SBC_F9>(state);
    instructions[0xFD] = std::make_unique<Opcode::SBC_FD>(state);
    instructions[0xFF] = std::make_unique<Opcode::SBC_FF>(state);
    instructions[0x38] = std::make_unique<Opcode::SEC_38>(state);
    instructions[0xF8] = std::make_unique<Opcode::SED_F8>(state);
    instructions[0x78] = std::make_unique<Opcode::SEI_78>(state);
    instructions[0xE2] = std::make_unique<Opcode::SEP_E2>(state);
    instructions[0x81] = std::make_unique<Opcode::STA_81>(state);
    instructions[0x83] = std::make_unique<Opcode::STA_83>(state);
    instructions[0x85] = std::make_unique<Opcode::STA_85>(state);
    instructions[0x87] = std::make_unique<Opcode::STA_87>(state);
    instructions[0x8D] = std::make_unique<Opcode::STA_8D>(state);
    instructions[0x8F] = std::make_unique<Opcode::STA_8F>(state);
    instructions[0x91] = std::make_unique<Opcode::STA_91>(state);
    instructions[0x92] = std::make_unique<Opcode::STA_92>(state);
    instructions[0x93] = std::make_unique<Opcode::STA_93>(state);
    instructions[0x95] = std::make_unique<Opcode::STA_95>(state);
    instructions[0x97] = std::make_unique<Opcode::STA_97>(state);
    instructions[0x99] = std::make_unique<Opcode::STA_99>(state);
    instructions[0x9D] = std::make_unique<Opcode::STA_9D>(state);
    instructions[0x9F] = std::make_unique<Opcode::STA_9F>(state);
    instructions[0xDB] = std::make_unique<Opcode::STP_DB>(state);
    instructions[0x86] = std::make_unique<Opcode::STX_86>(state);
    instructions[0x8E] = std::make_unique<Opcode::STX_8E>(state);
    instructions[0x96] = std::make_unique<Opcode::STX_96>(state);
    instructions[0x84] = std::make_unique<Opcode::STY_84>(state);
    instructions[0x8C] = std::make_unique<Opcode::STY_8C>(state);
    instructions[0x94] = std::make_unique<Opcode::STY_94>(state);
    instructions[0x64] = std::make_unique<Opcode::STZ_64>(state);
    instructions[0x74] = std::make_unique<Opcode::STZ_74>(state);
    instructions[0x9C] = std::make_unique<Opcode::STZ_9C>(state);
    instructions[0x9E] = std::make_unique<Opcode::STZ_9E>(state);
    instructions[0xAA] = std::make_unique<Opcode::TAX_AA>(state);
    instructions[0xA8] = std::make_unique<Opcode::TAY_A8>(state);
    instructions[0x5B] = std::make_unique<Opcode::TCD_5B>(state);
    instructions[0x1B] = std::make_unique<Opcode::TCS_1B>(state);
    instructions[0x7B] = std::make_unique<Opcode::TDC_7B>(state);
    instructions[0x14] = std::make_unique<Opcode::TRB_14>(state);
    instructions[0x1C] = std::make_unique<Opcode::TRB_1C>(state);
    instructions[0x04] = std::make_unique<Opcode::TSB_04>(state);
    instructions[0x0C] = std::make_unique<Opcode::TSB_0C>(state);
    instructions[0x3B] = std::make_unique<Opcode::TSC_3B>(state);
    instructions[0xBA] = std::make_unique<Opcode::TSX_BA>(state);
    instructions[0x8A] = std::make_unique<Opcode::TXA_8A>(state);
    instructions[0x9A] = std::make_unique<Opcode::TXS_9A>(state);
    instructions[0x9B] = std::make_unique<Opcode::TXY_9B>(state);
    instructions[0x98] = std::make_unique<Opcode::TYA_98>(state);
    instructions[0xBB] = std::make_unique<Opcode::TYX_BB>(state);
    instructions[0xCB] = std::make_unique<Opcode::WAI_CB>(state);
    instructions[0x42] = std::make_unique<Opcode::WDM_42>(state);
    instructions[0xEB] = std::make_unique<Opcode::XBA_EB>(state);
    instructions[0xFB] = std::make_unique<Opcode::XCE_FB>(state);
}

}