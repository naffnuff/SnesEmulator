#pragma once

#include <stdexcept>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <bitset>
#include <mutex>

#include "Exception.h"
#include "Types.h"
#include "Output.h"
#include "Memory.h"
#include "RegisterManager.h"

namespace Audio {

EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)
EXCEPTION(RuntimeError, ::RuntimeError)

class Processor : public RegisterManager<Memory<Byte>, Output::Cyan>
{
private:
    class FrequencyCounter
    {
    private:
        static constexpr int tableSize = 32;
        using Table = std::array<int, tableSize>;

        static constexpr Table getTable()
        {
            Table table = { 0 };
            size_t index = table.size();
            table[--index] = 1;
            table[--index] = 2;
            for (int i = 0; i < 10; ++i) {
                table[--index] = 3 << i;
                table[--index] = 4 << i;
                table[--index] = 5 << i;
            }
            table[0] = 0;
            return table;
        }

    public:
        FrequencyCounter()
        {
            /*std::cout << "Frequencies:" << std::endl;
            for (int frequency : getTable()) {
                std::cout << frequency << std::endl;
            }
            std::cout << "***" << std::endl;*/
        }

        void changeFrequency(int index)
        {
            if (index < 0 || index >= tableSize) {
                throw RuntimeError(__FUNCTION__ ": Frequency index is out-of-bounds");
            }
            frequency = getTable()[index];
            if (frequency == 0) {
                throw RuntimeError(__FUNCTION__ ": Frequency is zero");
            }
            counter = 0;
        }

        bool tick()
        {
            if (frequency == 0) {
                throw RuntimeError(__FUNCTION__ ": Frequency is zero");
            }
            if (counter >= frequency) {
                throw RuntimeError(__FUNCTION__ ": Counter is beyond frequency: counter: ", counter, ", frequency: ", frequency);
            }
            if (++counter == frequency) {
                counter = 0;
                return true;
            } else {
                return false;
            }
        }
    private:
        int frequency = 0;
        int counter = 0;
    };

public:
    struct Sound
    {
        Sound() = default;

        Sound(const Sound&) = delete;
        Sound& operator=(const Sound&) = delete;

        std::vector<double> start;
        std::vector<double> loop;
    };
    using SoundLibraryKey = std::pair<Word, Word>;
    using SoundLibrary = std::map<SoundLibraryKey, Sound>;

    class Voice
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

        enum EnvelopeStage
        {
            Inactive,
            Attack,
            Decay,
            Sustain,
            Release,
        };

        double leftVolume = 0.0f;
        double rightVolume = 0.0f;
        double pitch = 0.0f;
        Byte attackRate;
        Byte decayRate;
        Byte sustainRate;
        double sustainLevel;
        double envelope = 0.0;
        double output = 0.0;

        FrequencyCounter frequencyCounter;
        double outputBase = 0.0;
        double outputCoefficient = 0.0;
        bool inLoop = false;
        double bufferOffset = 0.0f;
        Word startAddress;
        Word loopAddress;

        EnvelopeType envelopeType = Gain;
        GainMode gainMode;
        Byte gainLevel;

        std::string envelopeTypeToString() const
        {
            switch (envelopeType) {
            case Audio::Processor::Voice::Gain:
                return "Gain";
            case Audio::Processor::Voice::ADSR:
                return "ADSR";
            default:
                return "";
            }
        }

        std::string gainModeToString() const
        {
            switch (gainMode) {
            case Audio::Processor::Voice::Direct:
                return "Direct";
            case Audio::Processor::Voice::LinearIncrease:
                return "Increase (Linear)";
            case Audio::Processor::Voice::BentLineIncrease:
                return "Increase (Bent Line)";
            case Audio::Processor::Voice::LinearDecrease:
                return "Decrease (Linear)";
            case Audio::Processor::Voice::ExponentialDecrease:
                return "Decrease (Exponential)";
            default:
                return "";
            }
        }

        void setEnvelopeStage(EnvelopeStage nextStage);
        void calculateEnvelope();
        double sample(SoundLibrary& sounds);

    private:
        EnvelopeStage envelopeStage = Inactive;
    };

    static constexpr int tableSize = 50;
    static constexpr int voiceCount = 8;

    Processor(Output& output);

    Processor(const Processor&) = delete;
    Processor& operator=(const Processor&) = delete;

    ~Processor();

    void initialize();
    void startStream();
    void checkStreamErrors();

    void printMemoryRegister(bool write, Byte value, AddressType address, const std::string& info) override
    {
        if (supressOutput)
        {
            return;
        }
        static uint64_t lastDspCycle = 0;
        output.log(Log::Level::Debug, Output::Cyan, value != 0, (write ? "Write " : "Read "), value, " (", std::bitset<8>(value), ") @", address, " (", info, "), cycle ", dspCycle, " (+", (dspCycle - lastDspCycle), ")");
        lastDspCycle = dspCycle;
    }

    void tick()
    {
        ++dspCycle;
        ++targetTickCounter;
    }

private:
    bool checkStreamStatus(unsigned long flags);
    void outputSample(float& leftChannel, float& rightChannel);

    void printTimeInfo(double currentTime);

public:
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
    int8_t echoFeedback = 0;
    std::bitset<voiceCount> pitchModulation;
    std::bitset<voiceCount> noiseOn;
    std::bitset<voiceCount> echoOn;
    Byte echoRegionOffset;
    Byte echoDelay;
    std::array<Byte, voiceCount> coefficients;

    SoundLibrary soundLibrary;

    double mainVolumeLeft;
    double mainVolumeRight;

    void* stream;

    bool initialized = false;

    int targetTickCounter = 0;

    bool streamError = false;
    bool inputUnderflow = false;
    bool inputOverflow = false;
    bool outputUnderflow = false;
    bool outputOverflow = false;
    bool primingOutput = false;

    double previousTimeInfoTime = 0.0;
    int timeInfoTickCounter = 0;

private:
    Output output;

    friend struct StreamHandler;
};

}
