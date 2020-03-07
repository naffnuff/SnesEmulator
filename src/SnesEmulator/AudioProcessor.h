#pragma once

#include "AudioRenderer.h"

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
        Byte sourceNumber;
        EnvelopeType envelopeType = Gain;
        GainMode gainMode;
        Byte gainLevel;

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
        , renderer(output, error)
    {

    }

    ~Processor()
    {
    }

    void initialize()
    {
        renderer.initialize();
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

    void tick()
    {
        ++dspCycle;
        ++renderer.targetTickCounter;
    }

    static constexpr int voiceCount = Renderer::voiceCount;

    uint64_t dspCycle = 0;

    Memory<Byte> dspMemory;

    std::array<Voice, voiceCount> voices;
    int8_t echoVolumeLeft;
    int8_t echoVolumeRight;
    std::bitset<voiceCount> keyOn;
    std::bitset<voiceCount> keyOff;
    bool reset = false;
    bool mute = false;
    bool echoOff = false;
    Byte noiseGeneratorClock;
    std::bitset<voiceCount> sourceEndBlock;    
    int8_t echoFeedback;
    std::bitset<voiceCount> pitchModulation;
    std::bitset<voiceCount> noiseOn;
    std::bitset<voiceCount> echoOn;
    Byte sourceDirectoryOffset;
    Byte echoRegionOffset;
    Byte echoDelay;
    std::array<Byte, voiceCount> coefficients;

    Renderer renderer;

private:
    std::ostream& output;
    std::ostream& error;
};

}
