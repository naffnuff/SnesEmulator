#pragma once

#include <stdexcept>
#include <iostream>
#include <array>
#include <vector>
#include <mutex>

#include "Types.h"

namespace Audio {

struct Exception : std::runtime_error
{
    Exception(const std::string& message)
        : std::runtime_error("Audio Exception: " + message)
    {
    }
};

class Renderer
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
                throw Exception(__FUNCTION__ ": Frequency index is out-of-bounds");
            }
            frequency = getTable()[index];
            if (frequency == 0) {
                std::cerr << __FUNCTION__ << ": Frequency is zero" << std::endl;
                throw Exception(__FUNCTION__ ": Frequency is zero");
            }
            counter = 0;
        }

        bool tick() noexcept
        {
            if (frequency == 0) {
                std::cerr << __FUNCTION__ << ": Frequency is zero" << std::endl;
            }
            if (counter >= frequency) {
                //std::cerr << __FUNCTION__ << ": Counter is beyond frequency: " << counter << " >= " << frequency << std::endl;
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
    class Voice
    {
    public:
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
        double counter = 0.0f;
        double pitch = 1.0f;
        Byte attackRate;
        Byte decayRate;
        Byte sustainRate;
        double sustainLevel;
        double envelope = 0.0;
        double output = 0.0;

        FrequencyCounter frequencyCounter;
        double outputBase = 0.0;
        double outputCoefficient = 0.0;

        void setEnvelopeStage(EnvelopeStage nextStage);
        void calculateEnvelope() noexcept;

    private:
        EnvelopeStage envelopeStage = Inactive;
    };

    static constexpr int tableSize = 50;
    static constexpr int voiceCount = 8;

    Renderer(std::ostream& output, std::ostream& error);
    ~Renderer();

    void initialize();
    void startStream();
    void checkStreamErrors();

private:
    bool checkStreamStatus(unsigned long flags);
    void outputSample(float& leftChannel, float& rightChannel);

    void printTimeInfo(double currentTime);

public:
    double sine[tableSize];

    std::array<Voice, voiceCount> voices;

    double mainVolumeLeft;
    double mainVolumeRight;

    std::ostream& output;
    std::ostream& error;

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
    friend struct StreamHandler;
};

}
