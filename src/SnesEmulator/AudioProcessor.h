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

class Processor : public RegisterManager<Memory<Byte>, Output::Color::Cyan>
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
            for (int i = 0; i < 10; ++i)
            {
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
            int i = 0;
            for (int entry : getTable())
            {
                std::cout << entry << "\t";

                if (++i % 3 == 0)
                {
                    std::cout << std::endl;
                }
            }
            std::cout << "***" << std::endl;*/
        }

        void changeFrequency(int index)
        {
            if (index < 0 || index >= tableSize)
            {
                throw RuntimeError(__FUNCTION__ ": Frequency index is out-of-bounds");
            }
            frequency = frequencyTable[index];
            counter = 0;
        }

        bool tick()
        {
            if (frequency == 0)
            {
                return false;
            }
            if (counter >= frequency)
            {
                throw RuntimeError(__FUNCTION__ ": Counter is beyond frequency: counter: ", counter, ", frequency: ", frequency);
            }
            if (++counter == frequency)
            {
                counter = 0;
                return true;
            }
            else
            {
                return false;
            }
        }
	private:
		static Table frequencyTable;

        int frequency = 0;
        int counter = 0;
    };

public:
    class Voice
    {
    public:
        enum class EnvelopeType
        {
            Gain = 0,
            ADSR = 1
        };

        enum class GainMode
        {
            Direct = 4,
            LinearIncrease = 2,
            BentLineIncrease = 3,
            LinearDecrease = 0,
            ExponentialDecrease = 1
        };

        enum class ADSRStage
        {
            Inactive,
            Attack,
            Decay,
            Sustain,
            Release,
        };

        Voice(Processor& processor)
            : processor(processor)
        {
        }

        Word headerAddress;
        Word nextSampleAddress;

        std::array<int16_t, 12> sampleBuffer = { 0 };

        int8_t leftVolume = 0;
        int8_t rightVolume = 0;

        Word pitch;

        Byte attackRate;
        Byte decayRate;
        Byte sustainRate;
        Byte sustainLevel;

        Byte sourceNumber;

        int envelope;
        Word output;

        int setupPhase = 0;
        bool keyOnIsSet = false;

        bool keyOn = false;
        bool keyOff = false;
        bool sourceEndBlock = false;
        bool pitchModulation = false;
        bool noiseOn = false;
        bool echoOn = false;
        Byte coefficient;

        uint16_t interpolationIndex = 0;

        FrequencyCounter frequencyCounter;

        EnvelopeType envelopeType = EnvelopeType::Gain;
        GainMode gainMode = GainMode::Direct;
        Byte gainLevel;

        std::string envelopeTypeToString() const
        {
            switch (envelopeType)
            {
            case EnvelopeType::Gain:
                return "Gain";
            case EnvelopeType::ADSR:
                return "ADSR";
            default:
                return "";
            }
        }

        std::string adsrStageToString() const
        {
            switch (adsrStage)
            {
            case ADSRStage::Inactive:
                return "Inactive";
                break;
            case ADSRStage::Attack:
                return "Attack";
                break;
            case ADSRStage::Decay:
                return "Decay";
                break;
            case ADSRStage::Sustain:
                return "Sustain";
                break;
            case ADSRStage::Release:
                return "Release";
                break;
            default:
                return "";
                break;
            }
        }

        std::string gainModeToString() const
        {
            switch (gainMode)
            {
            case GainMode::Direct:
                return "Direct";
            case GainMode::LinearIncrease:
                return "Increase (Linear)";
            case GainMode::BentLineIncrease:
                return "Increase (Bent Line)";
            case GainMode::LinearDecrease:
                return "Decrease (Linear)";
            case GainMode::ExponentialDecrease:
                return "Decrease (Exponential)";
            default:
                return "";
            }
        }

        void calculateNextSample(int16_t& nextSample);
        void setADSRStage(ADSRStage nextStage);
        void calculateEnvelope();
        void readSampleAddress(bool loopAddress);
        void decodeNextBlock();

    private:
        Processor& processor;
        ADSRStage adsrStage = ADSRStage::Inactive;
    };

    static constexpr int tableSize = 50;
    static constexpr int voiceCount = 8;

    Processor(Output& output, Memory<Word>& spcMemory);

    Processor(const Processor&) = delete;
    Processor& operator=(const Processor&) = delete;

    ~Processor();

    template<bool Voice::*DataMember>
    void setVoiceBits(Byte value)
    {
        for (int i = 0; i < voiceCount; ++i)
        {
            voices[i].*DataMember = value.getBit(i);
        }
    }

    template<bool Voice::*DataMember>
    Byte getVoiceBits() const
    {
        Byte result;
        for (int i = 0; i < voiceCount; ++i)
        {
            result.setBit(i, voices[i].*DataMember);
        }
        return result;
    }

    template<bool Voice::*DataMember>
    void makeVoiceBitWriteRegister(AddressType address, const std::string& info, bool debug, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, [this](Byte value) { setVoiceBits<DataMember>(value); }, openBus);
    }

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
        output.log(Log::Level::Debug, Output::Color::Cyan, value != 0, (write ? "Write " : "Read "), value, " (", std::bitset<8>(value), ") @", address, " (", info, "), cycle ", dspCycle, " (+", (dspCycle - lastDspCycle), ")");
        lastDspCycle = dspCycle;
    }

    void tick();

private:
    bool checkStreamStatus(unsigned long flags);
    void outputNextSample(float& leftChannel, float& rightChannel);

    void printTimeInfo(double currentTime);

public:
    uint64_t dspCycle = 0;

    Memory<Word>& spcMemory;
    Memory<Byte> dspMemory;

    std::array<Voice, voiceCount> voices = { *this, *this, *this, *this, *this, *this, *this, *this };
    int8_t mainVolumeLeft;
    int8_t mainVolumeRight;
    int8_t echoVolumeLeft;
    int8_t echoVolumeRight;
    bool reset = false;
    bool mute = false;
    bool echoOff = false;
    bool end = false;
    Byte noiseGeneratorClock;
    int8_t echoFeedback = 0;
    Byte sourceDirectory;
    Byte echoRegionOffset;
    Byte echoDelay;

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
