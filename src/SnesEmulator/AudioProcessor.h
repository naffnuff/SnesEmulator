#pragma once

#include "OpenALFramework/Framework.h"

namespace Audio {

struct NotYetImplementedException : std::logic_error
{
    NotYetImplementedException(const std::string& name)
        : std::logic_error("Audio feature not yet implemented: " + name)
    {
    }
};

class Processor : public RegisterManager<Memory<Byte>, System::Cyan>
{
public:
    enum EnvelopeType
    {
        Gain = 0,
        ADSR = 1
    };

    enum GainMode
    {
        Direct = 4,
        LinearIncrease = 2,
        BentLineIncrease = 3,
        LinearDecrease = 0,
        ExponentialDecrease = 1
    };

    struct Voice
    {
        int8_t leftVolume;
        int8_t rightVolume;
        Word pitch;
        Byte sourceNumber;
        EnvelopeType envelopeType = Gain;
        Byte attackRate;
        Byte decayRate;
        Byte sustainRate;
        Byte sustainLevel;
        GainMode gainMode;
        Byte gainLevel;
        Byte envelope;
        int8_t output;

        std::string envelopeTypeToString() const
        {
            switch (envelopeType) {
            case Audio::Processor::Gain:
                return "Gain";
            case Audio::Processor::ADSR:
                return "ADSR";
            default:
                return "";
            }
        }

        std::string gainModeToString() const
        {
            switch (gainMode) {
            case Audio::Processor::Direct:
                return "Direct";
            case Audio::Processor::LinearIncrease:
                return "Increase (Linear)";
            case Audio::Processor::BentLineIncrease:
                return "Increase (Bent Line)";
            case Audio::Processor::LinearDecrease:
                return "Decrease (Linear)";
            case Audio::Processor::ExponentialDecrease:
                return "Decrease (Exponential)";
            default:
                return "";
            }
        }
    };

    Processor(std::ostream& output, std::ostream& error)
        : RegisterManager(output, error, dspMemory)
        , output(output)
        , error(error)
        , dspMemory(0x80)
    {
        // Initialize Framework
        ALFWInit();

        ALFWprintf("PlayStatic Test Application\n");

        if (!ALFWInitOpenAL()) {
            ALFWprintf("Failed to initialize OpenAL\n");
            ALFWShutdown();
        }

        // Generate an AL Buffer
        alGenBuffers(1, &uiBuffer);

        // Load Wave file into OpenAL Buffer
        if (!ALFWLoadWaveToBuffer("wave2.wav", uiBuffer)) {
            ALFWprintf("Failed to load wave2.wav\n");
        }

        // Generate a Source to playback the Buffer
        alGenSources(1, &uiSource);

        alSourcef(uiSource, AL_PITCH, 1);

        // Attach Source to Buffer
        alSourcei(uiSource, AL_BUFFER, uiBuffer);
    }

    ~Processor()
    {
        // Clean up by deleting Source(s) and Buffer(s)
        alSourceStop(uiSource);
        alDeleteSources(1, &uiSource);
        alDeleteBuffers(1, &uiBuffer);

        ALFWShutdownOpenAL();

        ALFWShutdown();
    }

    void printMemoryRegister(bool write, Byte value, AddressType address, const std::string& info) override
    {
        if (supressOutput)
        {
            return;
        }
        static uint64_t lastDspCycle = 0;
        System::ScopedOutputColor outputColor(output, System::Cyan, value != 0);
        output << (write ? "Write " : "Read ") << value << " (" << std::bitset<8>(value) << ") @" << address << " (" << info << "), cycle " << dspCycle << " (+" << (dspCycle - lastDspCycle) << ")" << std::endl;
        lastDspCycle = dspCycle;
    }

    void playSound()
    {
        alSourcePlay(uiSource);
    }

    uint64_t dspCycle = 0;

    Memory<Byte> dspMemory;

    std::array<Voice, 8> voices;
    int8_t mainVolumeLeft;
    int8_t mainVolumeRight;
    int8_t echoVolumeLeft;
    int8_t echoVolumeRight;
    std::bitset<8> keyOn;
    std::bitset<8> keyOff;
    bool reset = false;
    bool mute = false;
    bool echoOff = false;
    Byte noiseGeneratorClock;
    std::bitset<8> sourceEndBlock;    
    int8_t echoFeedback;
    std::bitset<8> pitchModulation;
    std::bitset<8> noiseOn;
    std::bitset<8> echoOn;
    Byte sourceDirectoryOffset;
    Byte echoRegionOffset;
    Byte echoDelay;
    std::array<Byte, 8> coefficients;

private:
    std::ostream& output;
    std::ostream& error;

    ALuint      uiBuffer;
    ALuint      uiSource;
    ALint       iState;
};

}
