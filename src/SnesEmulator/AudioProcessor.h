#pragma once

#include "OpenALFramework/Framework.h"

namespace Audio {

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
        Byte gainValue;
        Byte envelope;
        int8_t output;
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
        static uint64_t lastAudioCycle = 0;
        System::setOutputColor(output, value ? System::Cyan : System::Magenta, true);
        output << (write ? "Write " : "Read ") << value << " (" << std::bitset<8>(value) << ") @" << address << " (" << info << "), cycle " << audioCycle << " (+" << (audioCycle - lastAudioCycle) << ")" << std::endl;
        System::setOutputColor(output, System::DefaultColor, false);
        lastAudioCycle = audioCycle;
    }

    void playSound()
    {
        alSourcePlay(uiSource);
    }

    std::array<Voice, 8> voices;
    std::array<Byte, 8> coefficients;
    
    Memory<Byte> dspMemory;

    uint64_t audioCycle = 0;

    int8_t mainVolumeLeft;
    int8_t mainVolumeRight;
    int8_t echoVolumeLeft;
    int8_t echoVolumeRight;
    std::bitset<8> echoOn;
    bool reset = false;
    bool mute = false;
    bool echoOff = false;
    Byte noiseGeneratorClock;
    int8_t echoFeedback;
    Byte echoRegionOffset;
    Byte echoDelay;


private:
    std::ostream& output;
    std::ostream& error;

    ALuint      uiBuffer;
    ALuint      uiSource;
    ALint       iState;
};

}
