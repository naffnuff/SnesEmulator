#pragma once

#include <stdexcept>
#include <iostream>
#include <array>
#include <vector>
#include <map>
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

        bool tick()
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
    struct Sound
    {
        Sound() = default;

        Sound(const Sound&) = delete;
        Sound& operator=(const Sound&) = delete;

        std::vector<double> start;
        std::vector<double> loop;
    };
    using SoundLibrary = std::map<uint32_t, Sound>;

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
        bool inLoop = false;
        double bufferOffset = 0.0f;
        uint32_t sourceAddress;

        void setEnvelopeStage(EnvelopeStage nextStage);
        void calculateEnvelope();
        double sample(SoundLibrary& sounds);

    private:
        EnvelopeStage envelopeStage = Inactive;
    };

    static constexpr int tableSize = 50;
    static constexpr int voiceCount = 8;

    Renderer(std::ostream& output, std::ostream& error);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void initialize();
    void startStream();
    void checkStreamErrors();

private:
    bool checkStreamStatus(unsigned long flags);
    void outputSample(float& leftChannel, float& rightChannel);

    void printTimeInfo(double currentTime);

    static constexpr double level = 0.33;
    static constexpr double double_Pi = 3.14159265358979323846264338327950288;

    /*
 * Generate sine wave
 */
    double sampleSineWave(double t, double frequency, double phase)
    {
        return level * sin(2.0 * double_Pi * frequency * t + phase);
    };

    /*
     * Generate square wave
     * This can be generated using 2 variants
     * First is to calculate values by periods
     * Second is to use sine wave and apply sign function to it
     */
    double sampleSquareWave(double t, double frequency, double phase)
    {
        //return level * sampleByTime(t);
        return level * sampleBySinSign(t, frequency, phase);
    };

    double sampleByTime(double t, double frequency, double phase)
    {
        double fullPeriodTime = 1.0 / frequency;
        double halfPeriodTime = fullPeriodTime / 2.0;
        double localTime = fmod(t, fullPeriodTime);

        if (localTime < halfPeriodTime) return 1.0;
        else return -1.0;
    }

    double sampleBySinSign(double t, double frequency, double phase)
    {
        return sign(sin(2 * double_Pi * frequency * t + phase));
    }

    int sign(double value)
    {
        return (value >= 0.0) ? 1 : -1;
    }

    /*
     * Generate triangle wave
     */
    double sampleTriangleWave(double t, double frequency)
    {
        double res = 0.0;
        double fullPeriodTime = 1.0 / frequency;
        double localTime = fmod(t, fullPeriodTime);

        double value = localTime / fullPeriodTime;

        if (value < 0.25) {
            res = value * 4;
        } else if (value < 0.75) {
            res = 2.0 - (value * 4.0);
        } else {
            res = value * 4 - 4.0;
        }

        return level * res;
    };

    /*
     * Generate sawtooth wave
     */
    double sampleSawtoothWave(double t, double frequency)
    {
        double fullPeriodTime = 1.0 / frequency;
        double localTime = fmod(t, fullPeriodTime);

        return level * ((localTime / fullPeriodTime) * 2 - 1.0);
    };

public:
    //double sine[tableSize];

    SoundLibrary soundLibrary;

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
