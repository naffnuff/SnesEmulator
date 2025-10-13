#pragma once

#include <vector>
#include <functional>

#include "SPC700/SpcState.h"

#include "Util.h"
#include "RegisterManager.h"
#include "System.h"
#include "Memory.h"

#include "AudioProcessor.h"

namespace Audio
{

class Registers : public RegisterManager<SPC::State::MemoryType, Output::Color::Blue>
{
public:
    Registers(Output& output, SPC::State& state)
        : RegisterManager(output, "audio", state.getMemory())
        , output(output, "audio")
        , memory(state.getMemory())
        , processor(output, state.getMemory())
    {
    }

    Registers(const Registers&) = delete;
    Registers& operator=(const Registers&) = delete;

    void initialize(std::array<Byte, 4>& cpuToSpcBuffers)
    {
        // SPC Registers
        makeWriteRegister(0xf1, "I/0 and Timer Control", false,
            [this, &cpuToSpcBuffers](Byte byte)
            {
                for (int i = 0; i < 3; ++i)
                {
                    if (!processor.timers[i].enabled && byte.getBit(i))
                    {
                        processor.timers[i].tick = 0;
                        processor.timers[i].counter = 0;
                    }
                    processor.timers[i].enabled = byte.getBit(i);
                }
                if (byte.getBit(4))
                {
                    cpuToSpcBuffers[0] = 0;
                    cpuToSpcBuffers[1] = 0;
                }
                if (byte.getBit(5))
                {
                    cpuToSpcBuffers[2] = 0;
                    cpuToSpcBuffers[3] = 0;
                }
                bootRomDataEnabled = byte.getBit(7);
            });
        makeWriteRegister(0xf2, "DSP Communication Address", false,
            [this](Byte value)
            {
                dspAddress = value;
            });
        makeReadWriteRegister(0xf3, "DSP Communication Data", false,
            [this](Byte& value)
            {
                value = processor.dspMemory.readByte(dspAddress & 0x7f);
            },
            [this](Byte value)
            {
                if (dspAddress < 0x80)
                {
                    processor.dspMemory.writeByte(value, dspAddress);
                    if (value > 0)
                    {
                        //pauseRequested = true;
                    }
                    //processor.verifyRegister(dspAddress, value);
                }
            });

        for (int i = 0; i < 3; ++i)
        {
            makeWriteRegister(Word(0xfa + i), std::string("Timer ") + char('1' + i) + " Scaling Target", true,
                [this, i](Byte value)
                {
                    processor.timers[i].target = value == 0 ? 0x100 : int(value);
                });
            makeReadRegister(Word(0xfd + i), std::string("Timer ") + char('1' + i) + " Output", false,
                [this, i](Byte& value)
                {
                    value = Byte(processor.timers[i].counter);
                    processor.timers[i].counter = 0;
                });
        }

        /*for (int i = 0; i < bootRomData.size(); ++i)
        {
            Word address(0xffc0 + i);
            memory.createLocation<BootRomLocation>(address, Byte(0xff), bootRomData[i], std::ref(bootRomDataEnabled));
        }*/

        // DSP Registers
        for (int i = 0; i < processor.voices.size(); ++i)
        {
            Byte voiceAddressStart(i << 4);
            std::string voiceName("Voice ");
            voiceName += char('0' + i);
            voiceName += " ";
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxVOLL>(i, voiceAddressStart, voiceName + "Left Volume", false);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxVOLR>(i, voiceAddressStart + 1, voiceName + "Right Volume", false);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxPITCHL>(i, voiceAddressStart + 2, voiceName + "Pitch low byte", false);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxPITCHH>(i, voiceAddressStart + 3, voiceName + "Pitch high byte", false);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxSRCN>(i, voiceAddressStart + 4, voiceName + "Source Number", false);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxADSR1>(i, voiceAddressStart + 5, voiceName + "ADSR low byte", false);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxADSR2>(i, voiceAddressStart + 6, voiceName + "ADSR high byte", false);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::VxGAIN>(i, voiceAddressStart + 7, voiceName + "Gain", false);
            //processor.makeReadRegister<Processor::Voice::Register::VxENV>(i, voiceAddressStart + 8, voiceName + "Envelope", false);
            //processor.makeReadRegister<Processor::Voice::Register::VxOUT>(i, voiceAddressStart + 9, voiceName + "Output", false);
        }
        processor.makeAudioWriteRegister<Processor::Register::MVOLL>(0x0c, "Main Volume Left", false);
        processor.makeAudioWriteRegister<Processor::Register::MVOLR>(0x1c, "Main Volume Right", false);
        processor.makeAudioWriteRegister<Processor::Register::EVOLL>(0x2c, "Echo Volume Left", false);
        processor.makeAudioWriteRegister<Processor::Register::EVOLR>(0x3c, "Echo Volume Right", false);
        processor.makeAudioWriteRegister<Processor::Register::KON>(0x4c, "Key On", true);
        processor.makeAudioWriteRegister<Processor::Register::KOFF>(0x5c, "Key Off", false);
        processor.makeAudioWriteRegister<Processor::Register::FLG>(0x6c, "Flags", false);
        processor.makeAudioWriteRegister<Processor::Register::ENDX>(0x7c, "Source End Block", true);
        processor.makeAudioWriteRegister<Processor::Register::EFB>(0x0d, "Echo Feedback", false);
        processor.makeAudioWriteRegister<Processor::Register::PMON>(0x2d, "Pitch Modulation", false);
        processor.makeAudioWriteRegister<Processor::Register::NON>(0x3d, "Noise On", false);
        processor.makeAudioWriteRegister<Processor::Register::EON>(0x4d, "Echo On", false);
        processor.makeAudioWriteRegister<Processor::Register::DIR>(0x5d, "Source Directory Offset", true);
        processor.makeAudioWriteRegister<Processor::Register::ESA>(0x6d, "Echo Region Offset", false);
        processor.makeAudioReadWriteRegister<Processor::Register::EDL>(0x7d, "Echo Delay", false);
        for (int i = 0; i < processor.voiceCount; ++i)
        {
            std::string coefficientName("Coefficient ");
            coefficientName += char('0' + i);
            processor.makeAudioVoiceWriteRegister<Processor::Voice::Register::FFCx>(i, Byte(i << 4 | 0x0f), coefficientName, false);
        }

        processor.dspMemory.finalize();

        processor.dspMemory.writeByte(0xe0, 0x6c);
        processor.dspMemory.writeByte(0xff, 0x7c);

        /*processor.dspMemory.writeByte(0x81, 0x00);
        processor.dspMemory.writeByte(0x7f, 0x01);
        processor.dspMemory.writeWord(0xffff, 0x02);
        processor.dspMemory.writeWord(0xaaaa, 0x05);
        processor.dspMemory.writeWord(0xaa, 0x07);*/

        output.debug("All audio registers created");
        processor.initialize();
    }

    void reset()
    {
        bootRomDataEnabled = true;
        processor.resetTimers();
    }

    Output output;

    SPC::State::MemoryType& memory;

    Processor processor;

    bool pauseRequested = false;

    Byte dspAddress;

    bool bootRomDataEnabled = true;

    std::array<Byte, 64> bootRomData = {
// cd: MOV X, #$ef
// MOV X, #i
// X = i    	[N.....Z.]
// Register Immediate (2-Byte)
        0xcd, 0xef,

// bd: MOV SP, X
// MOV SP, X
// SP = X    	[........]
// Register Register (1-Byte)
        0xbd,

// e8: MOV A, #$00
// MOV A, #i
// A = i    	[N.....Z.]
// Register Immediate (2-Byte)
        0xe8, 0x00,

// c6: MOV(X), A
// MOV (X), A
// (X) = A        (read)    	[........]
// Register Indirect Register (1-Byte)
        0xc6,

// 1d: DEC X
// DEC X
// X--    	[N.....Z.]
// Register (1-Byte)
        0x1d,

// d0: BNE $ffc5
// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
        0xd0, 0xfc,

// 8f: MOV $f4, #$aa
// MOV d, #i
// (d) = i        (read)    	[........]
// Direct Immediate (3-Byte)
        0x8f, 0xaa, 0xf4,

// 8f: MOV $f5, #$bb
// MOV d, #i
// (d) = i        (read)    	[........]
// Direct Immediate (3-Byte)
        0x8f, 0xbb, 0xf5,

// 78: CMP $f4, #$cc
// CMP d, #i
// (d) - i    	[N.....ZC]
// Direct Immediate (3-Byte)
        0x78, 0xcc, 0xf4,

// d0: BNE $ffcf
// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
        0xd0, 0xfb,

// 2f: BRA $ffef
// BRA r
// PC+=r    	[........]
// Program Counter Relative (2-Byte)
        0x2f, 0x19,

// eb: MOV Y, $f4
// MOV Y, d
// Y = (d)    	[N.....Z.]
// Register Direct (2-Byte)
        0xeb, 0xf4,

// d0: BNE $ffd6
// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
        0xd0, 0xfc,

// 7e: CMP Y, $f4
// CMP Y, d
// Y - (d)    	[N.....ZC]
// Register Direct (2-Byte)
        0x7e, 0xf4,

// d0: BNE $ffe9
// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
        0xd0, 0x0b,

// e4: MOV A, $f5
// MOV A, d
// A = (d)    	[N.....Z.]
// Register Direct (2-Byte)
        0xe4, 0xf5,

// cb: MOV $f4, Y
// MOV d, Y
// (d) = Y        (read)    	[........]
// Direct Register (2-Byte)
        0xcb, 0xf4,

// d7: MOV [$00]+Y, A
// MOV [d]+Y, A
// ([d]+Y) = A    (read)    	[........]
// Direct Indirect Indexed Register (2-Byte)
        0xd7, 0x00,

// fc: INC Y
// INC Y
// Y++    	[N.....Z.]
// Register (1-Byte)
        0xfc,

// d0: BNE $ffda
// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
        0xd0, 0xf3,

// ab: INC $01
// INC d
// (d)++    	[N.....Z.]
// Direct (2-Byte)
        0xab, 0x01,

// 10: BPL $ffda
// BPL r
// PC+=r  if N == 0    	[........]
// Program Counter Relative (2-Byte)
        0x10, 0xef,

// 7e: CMP Y, $f4
// CMP Y, d
// Y - (d)    	[N.....ZC]
// Register Direct (2-Byte)
        0x7e, 0xf4,

// 10: BPL $ffda
// BPL r
// PC+=r  if N == 0    	[........]
// Program Counter Relative (2-Byte)
        0x10, 0xeb,

// ba: MOVW YA, $f6
// MOVW YA, d
// YA = word (d)    	[N.....Z.]
// Y Accumulator Direct (2-Byte)
        0xba, 0xf6,

// da: MOVW $00, YA
// MOVW d, YA
// word (d) = YA  (read low only)    	[........]
// Direct Y Accumulator (2-Byte)
        0xda, 0x00,

// ba: MOVW YA, $f4
// MOVW YA, d
// YA = word (d)    	[N.....Z.]
// Y Accumulator Direct (2-Byte)
        0xba, 0xf4,

// c4: MOV $f4, A
// MOV d, A
// (d) = A        (read)    	[........]
// Direct Register (2-Byte)
        0xc4, 0xf4,

// dd: MOV A, Y
// MOV A, Y
// A = Y    	[N.....Z.]
// Register Register (1-Byte)
        0xdd,

// 5d: MOV X, A
// MOV X, A
// X = A    	[N.....Z.]
// Register Register (1-Byte)
        0x5d,

// d0: BNE $ffd6
// BNE r
// PC+=r  if Z == 0    	[........]
// Program Counter Relative (2-Byte)
        0xd0, 0xdb,

// 1f: JMP [$0000+X]
// JMP [!a+X]
// PC = [a+X]    	[........]
// Absolute Indexed Indirect (3-Byte)
        0x1f, 0x00, 0x00,

// unreachable gibberish
        0xc0, 0xff
    };

    int libraryByteCount = 0;
};

}
