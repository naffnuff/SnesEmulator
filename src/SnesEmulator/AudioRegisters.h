#pragma once

#include <vector>
#include <functional>

#include "SPC700/SpcState.h"

#include "RegisterManager.h"
#include "System.h"
#include "Memory.h"

#include "AudioProcessor.h"

namespace Audio {

class Registers : public RegisterManager<SPC::State::MemoryType, System::Blue>
{
public:
    class Timer
    {
    public:
        bool highPrecision = false;
        bool enabled = false;
        int tick = 0;
        int target = 256;
        int counter = 0;
    };

    Registers(std::ostream& output, std::ostream& error, SPC::State& state)
        : RegisterManager(output, error, state.getMemory())
        , output(output)
        , error(error)
        , spcMemory(state.getMemory())
        , processor(output, error)
    {
        timers[2].highPrecision = true;
    }

    Registers(const Registers&) = delete;
    Registers& operator=(const Registers&) = delete;

    void tick()
    {
        ++spcCycle;
        if (spcCycle % 16 == 0) {
            if (spcCycle % 32 == 0) {
                processor.tick();
            }
            for (int i = 0; i < 3; ++i) {
                if (timers[i].enabled && (timers[i].highPrecision || spcCycle % 128 == 0)) {
                    ++timers[i].tick;
                    if (timers[i].tick == timers[i].target) {
                        timers[i].tick = 0;
                        timers[i].counter = (timers[i].counter + 1) % 0x10;
                    }
                }
            }
        }
    }

    void initialize(std::array<Byte, 4>& cpuToSpcBuffers)
    {
        makeWriteRegister(0xf1, "I/0 and Timer Control", false,
            [this, &cpuToSpcBuffers](Byte byte) {
                for (int i = 0; i < 3; ++i) {
                    if (!timers[i].enabled && byte.getBit(i)) {
                        timers[i].tick = 0;
                        timers[i].counter = 0;
                    }
                    timers[i].enabled = byte.getBit(i);
                }
                if (byte.getBit(4)) {
                    cpuToSpcBuffers[0] = 0;
                    cpuToSpcBuffers[1] = 0;
                }
                if (byte.getBit(5)) {
                    cpuToSpcBuffers[2] = 0;
                    cpuToSpcBuffers[3] = 0;
                }
                bootRomDataEnabled = byte.getBit(7);
            });
        makeWriteRegister(0xf2, "DSP Communication Address", false,
            [this](Byte value) {
                dspAddress = value;
            });
        makeReadWriteRegister(0xf3, "DSP Communication Data", false,
            [this](Byte& value) {
                value = processor.dspMemory.readByte(dspAddress & 0x7f);
            },
            [this](Byte value) {
                if (dspAddress < 0x80) {
                    processor.dspMemory.writeByte(value, dspAddress);
                    if (value > 0) {
                        //pauseRequested = true;
                    }
                    //processor.verifyRegister(dspAddress, value);
                }
            });

        for (int i = 0; i < 3; ++i) {
            makeWriteRegister(0xfa + i, std::string("Timer ") + char('1' + i) + " Scaling Target", true,
                [this, i](Byte value) {
                    timers[i].target = value == 0 ? 0x100 : int(value);
                });
            makeReadRegister(0xfd + i, std::string("Timer ") + char('1' + i) + " Output", false,
                [this, i](Byte& value) {
                    value = timers[i].counter;
                    timers[i].counter = 0;
                });
        }

        for (int i = 0; i < bootRomData.size(); ++i) {
            Word address = 0xffc0 + i;
            spcMemory.createLocation<BootRomLocation>(address, 0xff, bootRomData[i], std::ref(bootRomDataEnabled));
        }

        for (int i = 0; i < processor.voices.size(); ++i) {
            Byte voiceAddressStart = i << 4;
            std::string voiceName("Voice ");
            voiceName += '0' + i;
            voiceName += " ";
            processor.makeWriteRegister(voiceAddressStart, voiceName + "Left Volume", false,
                [this, i](Byte value) {
                    processor.renderer.voices[i].leftVolume = toFactor(value);
                }
            );
            processor.makeWriteRegister(voiceAddressStart + 1, voiceName + "Right Volume", false,
                [this, i](Byte value) {
                    processor.renderer.voices[i].rightVolume = toFactor(value);
                }
            );
            processor.makeWriteRegister(voiceAddressStart + 2, voiceName + "Pitch low byte", false,
                /*[this, i](Byte& value) {
                    value = processor.voices[i].pitch.getLowByte();
                },*/
                [this, i](Byte value) {
                    voiceData[i].pitch.setLowByte(value);
                    calculatePitch(i);
                }
            );
            processor.makeWriteRegister(voiceAddressStart + 3, voiceName + "Pitch high byte", false,
                /*[this, i](Byte& value) {
                    value = processor.voices[i].pitch.getHighByte();
                },*/
                [this, i](Byte value) {
                    //processor.voices[i].pitch.setHighByte(value.getBits(0, 6));
                    voiceData[i].pitch.setHighByte(value);
                    calculatePitch(i);
                }
            );
            processor.makeWriteRegister(voiceAddressStart + 4, voiceName + "Source Number", false, processor.voices[i].sourceNumber);
            processor.makeWriteRegister(voiceAddressStart + 5, voiceName + "ADSR low byte", false,
                /*[this, i](Byte& value) {
                    value = processor.voices[i].attackRate | processor.voices[i].decayRate << 4 | processor.voices[i].envelopeType << 7;
                },*/
                [this, i](Byte value) {
                    processor.renderer.voices[i].attackRate = value.getBits(0, 4);
                    processor.renderer.voices[i].decayRate = value.getBits(4, 3);
                    if (value.getBit(7)) {
                        processor.voices[i].envelopeType = Processor::ADSR;
                    } else {
                        processor.voices[i].envelopeType = Processor::Gain;
                        throw NotYetImplementedException("Gain mode not supported");
                    }
                }
            );
            processor.makeWriteRegister(voiceAddressStart + 6, voiceName + "ADSR high byte", false,
                /*[this, i](Byte& value) {
                    value = processor.voices[i].sustainRate | processor.voices[i].sustainLevel << 5;
                },*/
                [this, i](Byte value) {
                    processor.renderer.voices[i].sustainRate = value.getBits(0, 5);
                    processor.renderer.voices[i].sustainLevel = double(value.getBits(5, 3) + 1.0) / 8.0;
                }
            );
            processor.makeWriteRegister(voiceAddressStart + 7, voiceName + "Gain", false,
                /*[this, i](Byte& value) {
                    if (processor.voices[i].gainMode == Processor::Direct) {
                        value = processor.voices[i].gainLevel;
                    } else {
                        value = Byte(processor.voices[i].gainLevel | processor.voices[i].gainMode << 5 | 1 << 7);
                    }
                },*/
                [this, i](Byte value) {
                    if (value.getBit(7)) {
                        processor.voices[i].gainMode = Processor::GainMode(uint8_t(value.getBits(5, 2)));
                        processor.voices[i].gainLevel = value.getBits(0, 5);
                    } else {
                        processor.voices[i].gainMode = Processor::Direct;
                        processor.voices[i].gainLevel = value.getBits(0, 7);
                    }
                }
            );
            //processor.makeReadRegister(voiceAddressStart + 8, voiceName + "Envelope", false, processor.renderer.data[i].envelope);
            //processor.makeReadRegister(voiceAddressStart + 9, voiceName + "Output", false, processor.renderer.data[i].output);
        }
        processor.makeWriteRegister(0x0c, "Main Volume Left", false,
            [this](Byte value) {
                processor.renderer.mainVolumeLeft = toFactor(value);
            }
        );
        processor.makeWriteRegister(0x1c, "Main Volume Right", false,
            [this](Byte value) {
                processor.renderer.mainVolumeRight = toFactor(value);
            }
        );
        processor.makeWriteRegister(0x2c, "Echo Volume Left", false, processor.echoVolumeLeft);
        processor.makeWriteRegister(0x3c, "Echo Volume Right", false, processor.echoVolumeRight);
        processor.makeWriteRegister(0x4c, "Key On", false,
            [this](Byte value) {
                std::bitset<8> newValue(value);
                for (int i = 0; i < 8; ++i) {
                    if (newValue[i] && !processor.keyOn[i]) {
                        processor.renderer.voices[i].setEnvelopeStage(Renderer::Voice::Attack);
                        //pauseRequested = true;
                    }
                }
                processor.keyOn = newValue;
                if (value) {
                }
            }
        );
        processor.makeWriteRegister(0x5c, "Key Off", false,
            [this](Byte value) {
                std::bitset<8> newValue(value);
                for (int i = 0; i < 8; ++i) {
                    if (newValue[i] && !processor.keyOff[i]) {
                        processor.renderer.voices[i].setEnvelopeStage(Renderer::Voice::Release);
                    }
                }
                processor.keyOff = newValue;
                if (value) {
                    //pauseRequested = true;
                }
            });
        processor.makeWriteRegister(0x6c, "Flags", false,
            /*[this](Byte& value) {
                value = processor.reset << 7 | processor.mute << 6 | processor.echoOff << 5 | processor.noiseGeneratorClock;
            },*/
            [this](Byte value) {
                processor.reset = value.getBit(7);
                processor.mute = value.getBit(6);
                processor.echoOff = value.getBit(5);
                processor.noiseGeneratorClock = value.getBits(0, 5);
            }
        );
        processor.makeWriteRegister(0x7c, "Source End Block", true,
            /*[this](Byte& value) {
            },*/
            [this](Byte value) {
            }
        );
        processor.makeWriteRegister(0x0d, "Echo Feedback", false, processor.echoFeedback);
        processor.makeWriteRegister(0x2d, "Pitch Modulation", false, processor.pitchModulation);
        processor.makeWriteRegister(0x3d, "Noise On", false, processor.noiseOn);
        processor.makeWriteRegister(0x4d, "Echo On", false, processor.echoOn);
        processor.makeWriteRegister(0x5d, "Source Directory Offset", true, processor.sourceDirectoryOffset);
        processor.makeWriteRegister(0x6d, "Echo Region Offset", false, processor.echoRegionOffset);
        processor.makeReadWriteRegister(0x7d, "Echo Delay", false,
            [this](Byte& value) {
                value = processor.echoDelay;
            },
            [this](Byte value) {
                processor.echoDelay = value.getBits(0, 4);
            }
        );
        for (int i = 0; i < processor.coefficients.size(); ++i) {
            std::string coefficientName("Coefficient ");
            coefficientName += '0' + i;
            processor.makeWriteRegister(i << 4 | 0x0f, coefficientName, false, processor.coefficients[i]);
        }

        processor.dspMemory.finalize();

        processor.dspMemory.writeByte(0xe0, 0x6c);
        processor.dspMemory.writeByte(0xff, 0x7c);
        
        /*processor.dspMemory.writeByte(0x81, 0x00);
        processor.dspMemory.writeByte(0x7f, 0x01);
        processor.dspMemory.writeWord(0xffff, 0x02);
        processor.dspMemory.writeWord(0xaaaa, 0x05);
        processor.dspMemory.writeWord(0xaa, 0x07);*/

        output << "BLUFFIS!" << std::endl;
        processor.initialize();
    }
    
    void reset()
    {
        bootRomDataEnabled = true;
        timers = {};
    }

    void calculatePitch(int voice)
    {
        processor.renderer.voices[voice].pitch = float(voiceData[voice].pitch) / float(1 << 12);
    }

    double toFactor(Byte value)
    {
        if (value.isNegative()) {
            return double(value) / 128.0;
        } else {
            return double(value) / 127.0;
        }
    }

    std::ostream& output;
    std::ostream& error;

    uint64_t spcCycle = 0;

    SPC::State::MemoryType& spcMemory;

    Processor processor;

    bool pauseRequested = false;

    std::array<Timer, 3> timers;

    Byte dspAddress;

    bool bootRomDataEnabled = true;

    std::array<Byte, 64> bootRomData = {
       0xCD, 0xEF, 0xBD, 0xE8, 0x00, 0xC6, 0x1D, 0xD0, 0xFC, 0x8F, 0xAA, 0xF4, 0x8F, 0xBB, 0xF5, 0x78,
       0xCC, 0xF4, 0xD0, 0xFB, 0x2F, 0x19, 0xEB, 0xF4, 0xD0, 0xFC, 0x7E, 0xF4, 0xD0, 0x0B, 0xE4, 0xF5,
       0xCB, 0xF4, 0xD7, 0x00, 0xFC, 0xD0, 0xF3, 0xAB, 0x01, 0x10, 0xEF, 0x7E, 0xF4, 0x10, 0xEB, 0xBA,
       0xF6, 0xDA, 0x00, 0xBA, 0xF4, 0xC4, 0xF4, 0xDD, 0x5D, 0xD0, 0xDB, 0x1F, 0x00, 0x00, 0xC0, 0xFF,
    };

    struct VoiceData
    {
        Word pitch;
    };

    std::array<VoiceData, Processor::voiceCount> voiceData;
};

}
