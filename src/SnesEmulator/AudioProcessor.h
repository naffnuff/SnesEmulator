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
    class Timer
    {
    public:
        bool highPrecision = false;
        bool enabled = false;
        int tick = 0;
        int target = 256;
        int counter = 0;
    };

    class FrequencyCounter
    {
    private:
        static constexpr int frequencyTableSize = 32;
        using FrequencyTable = std::array<int, frequencyTableSize>;

        static constexpr FrequencyTable getFrequencyTable()
        {
            FrequencyTable table = { 0 };
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
            if (index < 0 || index >= frequencyTableSize)
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
		static FrequencyTable frequencyTable;

        int frequency = 0;
        int counter = 0;
    };

public:
    class Voice
    {
    public:
        enum class Register
        {
            VxVOLL, // processor.voices[i].leftVolume
            VxVOLR, // processor.voices[i].rightVolume
            VxPITCHL,
            VxPITCHH,
            VxSRCN,
            VxADSR1,
            VxADSR2,
            VxGAIN,
            VxENV, // processor.renderer.data[i].envelope
            VxOUT, // processor.renderer.data[i].output
            FFCx, // processor.voices[i].coefficient
            Count
        };

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

        enum class SampleStage
        {
            Inactive = -1,
            /* #0 = After the final pre-KON sample is prepared, the envelope is set to 0 and
                    enters the Attack state, and is not updated for the next several
                    samples. The interpolation index is reset to 0, and is not updated for
                    the next several samples. The final pre-KON BRR decode also occurs here
                    (which can matter if the first block of the new BRR data uses a
                    non-Direct filter).*/
            Reset = 0,
            /* #1 = The first '0x0000' sample. At step S2, the start address is read. No BRR
                    decoding or header checks, envelope updating, or interpolation index
                    updating is performed.*/
            AddressRead = 1,
            /* #2 = At step S4, first BRR group is decoded. No envelope or interpolation
                    index updating.*/
            FirstBRRGroup = 2,
            /* #3 = At step S4, second BRR group is decoded. No envelope or interpolation
                    index updating.*/
            SecondBRRGroup = 3,
            /* #4 = At step S4, third BRR group is decoded. No envelope or interpolation
                    index updating.*/
            ThirdBRRGroup = 4,
            /* #5 = Envelope updating begins. The sample output is still '0x0000', because of
                    the order in which voice operations are performed. The interpolation
                    position is still 0.*/
            PrepareOutput = 5,
            /* #6 = Finally, we see the first data sample. The first interpolation position
                    update is done during step S4.*/
            Output = 6
        };

        Voice(Processor& processor)
            : processor(processor)
        {
        }

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

        void calculateNextSample();
        int16_t applyVolume(int8_t volume);
        void setADSRStage(ADSRStage nextStage);
        void calculateEnvelope();
        void readSampleAddress(bool loopAddress);
        void decodeSampleSource();
        void decodeNextBlock();

        void doStep3a();
        void doStep3b();
        void doStep3c();

        template<int N>
        void doStep() = delete;

    public:
        std::array<Byte, size_t(Register::Count)> registers;

        Voice* previousVoice = nullptr;

    private:
        Processor& processor;

        ADSRStage adsrStage = ADSRStage::Inactive;

        Word sourceAddress;

        Word headerAddress;
        Word nextSampleAddress;

        Byte header;
        bool endOfSample = false;
        bool shouldLoop = false;

        std::array<Byte, 2> sampleSource = { 0 };

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
        int16_t nextSample = 0;
        Word output;

        int setupPhase = -1; // remove
        SampleStage sampleStage = SampleStage::Inactive;

        //bool keyOnIsSet = false;

        bool keyOn = false;
        bool keyOnInternal = false;
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

        friend class Processor;
    };

    enum class Register
    {
        MVOLL, // processor.mainVolumeLeft
        MVOLR, // processor.mainVolumeRight
        EVOLL, // processor.echoVolumeLeft
        EVOLR, // processor.echoVolumeRight
        KON, //
                /*std::bitset<8> bitSet(value);
                for (int i = 0; i < 8; ++i)
                {
                    processor.voices[i].keyOn = bitSet[i];
                    if (bitSet[i])
                    {
                        processor.voices[i].keyOnIsSet = true;
                    }
                }*/
        KOFF, // makeVoiceBitWriteRegister<&Processor::Voice::keyOff>
        FLG, //
                /*processor.reset = value.getBit(7);
                processor.mute = value.getBit(6);
                processor.echoOff = value.getBit(5);
                processor.noiseGeneratorClock = value.getBits(0, 5);*/
        ENDX, //
                /*for (Processor::Voice& voice : processor.voices)
                {
                    voice.sourceEndBlock = false;
                }*/
        EFB, // processor.echoFeedback
        PMON, // makeVoiceBitWriteRegister<&Processor::Voice::pitchModulation>
        NON, // makeVoiceBitWriteRegister<&Processor::Voice::noiseOn>
        EON, // makeVoiceBitWriteRegister<&Processor::Voice::echoOn>
        DIR, // processor.sourceDirectory
        ESA, // processor.echoRegionOffset
        EDL, //[this](Byte& value)
            /*{
                value = processor.echoDelay;
            },
            [this](Byte value)
            {
                processor.echoDelay = value.getBits(0, 4);
            }*/
        Count
    };

    using SampleCycleTable = std::array<void(*)(Processor&), 32>;

    static SampleCycleTable sampleCycleTable;

    //static constexpr int tableSize = 50;
    static constexpr int voiceCount = 8;

    Processor(Output& output, Memory<Word>& spcMemory);

    Processor(const Processor&) = delete;
    Processor& operator=(const Processor&) = delete;

    ~Processor();

    template<Register R>
    void makeAudioWriteRegister(AddressType address, const std::string& info, bool debug, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, registers[size_t(R)], openBus);
    }

    template<Register R>
    void makeAudioReadWriteRegister(AddressType address, const std::string& info, bool debug)
    {
        makeReadWriteRegister(address, info, debug, registers[size_t(R)]);
    }

    template<Voice::Register R>
    void makeAudioVoiceWriteRegister(int voiceIndex, AddressType address, const std::string& info, bool debug, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, voices[voiceIndex].registers[size_t(R)], openBus);
    }

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
        output.log(Log::Level::Debug, Output::Color::Cyan, value != 0, (write ? "Write " : "Read "), value, " (", std::bitset<8>(value), ") @", address, " (", info, "), cycle ", dspCycle, " (+", (dspCycle - lastDspCycle), ")", " (sampleCount=", sampleCount, ")", " (sampleCycle=", sampleCycle, ")");
        lastDspCycle = dspCycle;
    }

    void tickTimers(bool tickAllTimers);

    template<int N>
    void onSampleCycle() = delete;

    void tick();

    void resetTimers()
    {
        timers = {};
    }

    void printDebuggerInfo(Output& output, Output::Lock& lock) const;

private:
    bool checkStreamStatus(unsigned long flags);
    void outputNextSample(float& leftChannel, float& rightChannel);

    void printTimeInfo(double currentTime);

public:
    std::array<Voice, voiceCount> voices = { *this, *this, *this, *this, *this, *this, *this, *this };

    std::array<Timer, 3> timers;

    Memory<Byte> dspMemory;

    std::array<Byte, size_t(Register::Count)> registers;

    int sampleCycle = 0;
    uint64_t sampleCount = 0;

    int32_t leftSampleSum = 0;
    int32_t rightSampleSum = 0;

private:
    Output output;

    friend struct StreamHandler;

    //uint64_t spcCycle = 0;

    uint64_t dspCycle = 0;

    Memory<Word>& spcMemory;

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

    //float leftOutput = 0;
    //float rightOutput = 0;

    std::vector<float> leftOutputBuffer;
    std::vector<float> rightOutputBuffer;

    size_t nextOuputIndex = 0;

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
};

}
