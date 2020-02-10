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
    class NotYetImplementedException : public std::logic_error
    {
    public:
        NotYetImplementedException(const std::string& name)
            : std::logic_error("Registers feature not yet implemented: " + name)
        {
        }
    };

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
        ++processor.audioCycle;
        if (processor.audioCycle % 16 == 0) {
            if (processor.audioCycle % 32 == 0) {
                
            }
            for (int i = 0; i < 3; ++i) {
                if (timers[i].enabled && (timers[i].highPrecision || processor.audioCycle % 128 == 0)) {
                    ++timers[i].tick;
                    if (timers[i].tick == timers[i].target) {
                        timers[i].tick = 0;
                        timers[i].counter = (timers[i].counter + 1) % 0x10;
                    }
                }
            }
        }
    }

    void initialize(Memory<Long>& cpuMemory)
    {
        makeWriteRegister(0xf1, "I/0 and Timer Control", false,
            [this, &cpuMemory](Byte byte) {
                for (int i = 0; i < 3; ++i) {
                    if (!timers[i].enabled && byte.getBit(i)) {
                        timers[i].tick = 0;
                        timers[i].counter = 0;
                    }
                    timers[i].enabled = byte.getBit(i);
                }
                if (byte.getBit(4)) {
                    cpuMemory.writeWord(0, 0x2140);
                }
                if (byte.getBit(5)) {
                    cpuMemory.writeWord(0, 0x2142);
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
                    processor.verifyRegister(dspAddress, value);
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
            processor.makeReadWriteRegister(voiceAddressStart, voiceName + "Left Volume", true, processor.voices[i].leftVolume);
            processor.makeReadWriteRegister(voiceAddressStart + 1, voiceName + "Right Volume", true, processor.voices[i].rightVolume);
            processor.makeReadWriteRegister(voiceAddressStart + 2, voiceName + "Pitch low byte", true,
                [this, i](Byte& value) {
                    value = processor.voices[i].pitch.getLowByte();
                },
                [this, i](Byte value) {
                    processor.voices[i].pitch.setLowByte(value);
                }
            );
            processor.makeReadWriteRegister(voiceAddressStart + 3, voiceName + "Pitch high byte", true,
                [this, i](Byte& value) {
                    value = processor.voices[i].pitch.getHighByte();
                },
                [this, i](Byte value) {
                    processor.voices[i].pitch.setHighByte(value.getBits(0, 6));
                }
            );
            processor.makeReadWriteRegister(voiceAddressStart + 4, voiceName + "Source Number", true, processor.voices[i].sourceNumber);
            processor.makeReadWriteRegister(voiceAddressStart + 5, voiceName + "ADSR low byte", true,
                [this, i](Byte& value) {
                    value = processor.voices[i].attackRate | processor.voices[i].decayRate << 4 | processor.voices[i].envelopeType << 7;
                },
                [this, i](Byte value) {
                    processor.voices[i].attackRate = value.getBits(0, 4);
                    processor.voices[i].decayRate = value.getBits(4, 3);
                    if (value.getBit(7)) {
                        processor.voices[i].envelopeType = Processor::ADSR;
                    } else {
                        processor.voices[i].envelopeType = Processor::Gain;
                    }
                }
            );
            processor.makeReadWriteRegister(voiceAddressStart + 6, voiceName + "ADSR high byte", true,
                [this, i](Byte& value) {
                    value = processor.voices[i].sustainRate | processor.voices[i].sustainLevel << 5;
                },
                [this, i](Byte value) {
                    processor.voices[i].sustainRate = value.getBits(0, 5);
                    processor.voices[i].sustainLevel = value.getBits(5, 3);
                }
            );
            processor.makeReadWriteRegister(voiceAddressStart + 7, voiceName + "Gain", true,
                [this, i](Byte& value) {
                    if (processor.voices[i].gainMode == Processor::Direct) {
                        return processor.voices[i].gainValue;
                    } else {
                        return Byte(processor.voices[i].gainMode << 5 | 1 << 7);
                    }
                },
                [this, i](Byte value) {
                    if (value.getBit(7)) {
                        processor.voices[i].gainMode = Processor::GainMode(uint8_t(value.getBits(5, 2)));
                    } else {
                        processor.voices[i].gainMode = Processor::Direct;
                        processor.voices[i].gainValue = value.getBits(0, 7);
                    }
                }
            );
            processor.makeReadWriteRegister(voiceAddressStart + 8, voiceName + "Envelope", true, processor.voices[i].envelope);
            processor.makeReadWriteRegister(voiceAddressStart + 9, voiceName + "Output", true, processor.voices[i].output);
        }
        processor.makeReadWriteRegister(0x0c, "Main Volume Left", true, processor.mainVolumeLeft);
        processor.makeReadWriteRegister(0x1c, "Main Volume Right", true, processor.mainVolumeRight);
        processor.makeReadWriteRegister(0x2c, "Echo Volume Left", true, processor.echoVolumeLeft);
        processor.makeReadWriteRegister(0x3c, "Echo Volume Right", true, processor.echoVolumeRight);
        processor.makeReadWriteRegister(0x4c, "Key On", true,
            [this](Byte& value) {
            },
            [this](Byte value) {
            }
        );
        processor.makeReadWriteRegister(0x5c, "Key Off", true,
            [this](Byte& value) {
            },
            [this](Byte value) {
            }
        );
        processor.makeReadWriteRegister(0x6c, "Flags", true,
            [this](Byte& value) {
                value = processor.reset << 7 | processor.mute << 6 | processor.echoOff << 5 | processor.noiseGeneratorClock;
            },
            [this](Byte value) {
                processor.reset = value.getBit(7);
                processor.mute = value.getBit(6);
                processor.echoOff = value.getBit(5);
                processor.noiseGeneratorClock = value.getBits(0, 5);
            }
        );
        processor.makeReadWriteRegister(0x7c, "Source End Block", true,
            [this](Byte& value) {
            },
            [this](Byte value) {
            }
        );
        processor.makeReadWriteRegister(0x0d, "Echo Feedback", true, processor.echoFeedback);
        processor.makeReadWriteRegister(0x2d, "Pitch Modulation", true,
            [this](Byte& value) {
            },
            [this](Byte value) {
            }
        );
        processor.makeReadWriteRegister(0x3d, "Noice On", true,
            [this](Byte& value) {
            },
            [this](Byte value) {
            }
        );
        processor.makeReadWriteRegister(0x4d, "Echo On", true, processor.echoOn);
        processor.makeReadWriteRegister(0x5d, "Source Directory Offset", true,
            [this](Byte& value) {
            },
            [this](Byte value) {
            }
        );
        processor.makeReadWriteRegister(0x6d, "Echo Region Offset", true, processor.echoRegionOffset);
        processor.makeReadWriteRegister(0x7d, "Echo Delay", true,
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
            processor.makeReadWriteRegister(i << 4 | 0x0f, coefficientName, true, processor.coefficients[i]);
        }

        processor.dspMemory.finalize();

        processor.dspMemory.writeByte(0xe0, 0x6c);
        processor.dspMemory.writeByte(0xff, 0x7c);
    }
    
    void reset()
    {
        bootRomDataEnabled = true;
        timers = {};
    }

    std::ostream& output;
    std::ostream& error;

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
};

}
