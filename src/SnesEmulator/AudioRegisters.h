#pragma once

#include <vector>
#include <functional>

#include "SPC700/SpcState.h"

#include "Util.h"
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
            processor.makeWriteRegister(voiceAddressStart + 4, voiceName + "Source Number", false,
                [this, i](Byte value) {
                    Word sourceAddress = (sourceDirectory << 8) + (value << 2);
                    decodeSource(sourceAddress);
                    processor.renderer.voices[i].sampleOffset = 0.0;
                    processor.renderer.voices[i].inLoop = false;
                    processor.renderer.voices[i].sourceAddress = sourceAddress;
                }
            );
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
        processor.makeWriteRegister(0x5d, "Source Directory Offset", true, sourceDirectory);
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

    void decodeSource(Word sourceAddress)
    {
        //output << "MAMASITA! " << sourceAddress << std::endl;
        Renderer::Sound& sound = processor.renderer.soundLibrary[sourceAddress];
        if (sound.start.empty() && sound.loop.empty()) {
            Word startAddress = spcMemory.readWord(sourceAddress);
            Word loopAddress = spcMemory.readWord(sourceAddress + 2);
            output << "startAddress=" << startAddress << ", loopAddress=" << loopAddress << std::endl;
            Word currentAddress = startAddress;
            bool end = false;
            bool loop = false;
            bool foundLoopStart = false;
            std::vector<double>& sampleOutput = sound.start;
            while (!end || loop) {
                if (currentAddress == loopAddress) {
                    output << "LOOPY MOTHERFUCKER!" << std::endl;
                    foundLoopStart = true;
                    sampleOutput = sound.loop;
                }
                decodeBlock(currentAddress, sampleOutput, end, loop);
            }
            /*if (loop) { // loop
                output << "LOOPING" << std::endl;
                if (loopAddress >= startAddress && loopAddress < currentAddress) {
                    if (foundLoopStart != loop) {
                        throw Exception("Da fuck!");
                    }
                    output << "Difference: " << (loopAddress - startAddress) << std::endl;
                    output << "Snufs: " << (double(loopAddress - startAddress) / 9.0) << std::endl;
                    output << "Snufs: " << (double(loopAddress - startAddress) / 9.0) * 16.0 << std::endl;
                    output << "size: " << sound.start.size() << std::endl;
                    int loopIndex = (loopAddress - startAddress) / 9 * 16;
                } else {
                    std::ostringstream ss;
                    ss << "Loop address is bananas: start=" << startAddress << ", loop=" << loopAddress << ", current=" << currentAddress;
                    throw Exception(ss.str());
                }
            } else {
                output << "NOT LOOPING!" << std::endl;
            }*/
        }
    }

    void decodeBlock(Word& currentAddress, std::vector<double>& sampleOutput, bool& end, bool& loop)
    {
        Byte header = spcMemory.readByte(currentAddress++);
        end = header.getBit(0);
        loop = header.getBit(1);
        Byte filter = header.getBits(2, 2);
        //output << "FUCKING FILTER: " << filter << std::endl;
        Byte range = header.getBits(4, 4);
        for (int i = 0; i < 8; ++i) {
            Byte sampleSource = spcMemory.readByte(currentAddress++);
            for (int8_t sample : { sampleSource.getBits(4, 4), sampleSource.getBits(0, 4) }) {
                if (sample >= 8) { // negative
                    sample |= 0xf0;
                }
                double doubleSample(int64_t(sample) << range);
                size_t size = sampleOutput.size();
                if (filter == 1) {
                    doubleSample += (size >= 1 ? sampleOutput[size - 1] * 15.0 / 16.0 : 0.0);
                } else if (filter == 2) {
                    doubleSample += (size >= 1 ? sampleOutput[size - 1] * 61.0 / 32.0 : 0.0) - (size >= 2 ? sampleOutput[size - 2] * 15.0 / 16.0 : 0.0);
                } else if (filter == 3) {
                    doubleSample += (size >= 1 ? sampleOutput[size - 1] * 115.0 / 64.0 : 0.0) - (size >=2 ? sampleOutput[size - 2] * 13.0 / 16.0 : 0.0);
                }
                sampleOutput.push_back(doubleSample);
            }
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
       0xcd, 0xef, 0xbd, 0xe8, 0x00, 0xc6, 0x1d, 0xd0, 0xfc, 0x8f, 0xaa, 0xf4, 0x8f, 0xbb, 0xf5, 0x78,
       0xcc, 0xf4, 0xd0, 0xfb, 0x2f, 0x19, 0xeb, 0xf4, 0xd0, 0xfc, 0x7e, 0xf4, 0xd0, 0x0b, 0xe4, 0xf5,
       0xcb, 0xf4, 0xd7, 0x00, 0xfc, 0xd0, 0xf3, 0xab, 0x01, 0x10, 0xef, 0x7e, 0xf4, 0x10, 0xeb, 0xba,
       0xf6, 0xda, 0x00, 0xba, 0xf4, 0xc4, 0xf4, 0xdd, 0x5d, 0xd0, 0xdb, 0x1f, 0x00, 0x00, 0xc0, 0xff,
    };

    struct VoiceData
    {
        Word pitch;
        Byte sourceNumber;
    };

    std::array<VoiceData, Processor::voiceCount> voiceData;

    Byte sourceDirectory;
};

}
