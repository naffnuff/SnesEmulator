#pragma once

#include "AudioProcessor.h"

namespace Audio {

class Test
{

private:
    static void testAttack(Processor& processor, Byte tableIndex)
    {
        double time = 0.0;
        Processor::FrequencyCounter counter;
        counter.changeFrequency((tableIndex << 1) + 0x1); // but not if tableIndex == 0xf
        int iteration = 0;
        double value = 0.0;
        while (value < 1.0) {
            time += 0.03125;
            if (counter.tick()) {
                ++iteration;
                value += 1.0 / 64.0;
            }
            if (value == 1.0) {
                processor.output.info("tableIndex: ", tableIndex, ", Value: ", value, " after time: ", time);
            }
        }
    }

    static void testDecay(Processor& processor, Byte tableIndex)
    {
        double time = 0.0;
        Processor::FrequencyCounter counter;
        counter.changeFrequency((tableIndex << 1) + 0x10);
        int iteration = 0;
        double value = 1.0;
        double targetLevel = 7.0 / 8.0;
        double targetRatio = 0.0001;
        double rate = 588.0;
        double coef = exp(-log((1.0 + targetRatio) / targetRatio) / rate);
        double base = (targetLevel - targetRatio) * (1.0 - coef);
        while (iteration < rate) {
            time += 0.03125;
            if (counter.tick()) {
                ++iteration;
                value = base + value * coef;
                //processor.output << "Iteration: " << iteration << ", base: " << base << ", coef: " << coef << ", Value: " << value << " after time: " << (timeInfo->outputBufferDacTime - startTime) * 1000.0 << std::endl;
            }

            if (iteration == rate) {
                processor.output.info("Iteration: ", iteration, ", Value: ", value, " after time: ", time);
            }
        }
    }

    static void testSustain(Processor& processor, Byte tableIndex)
    {
        double time = 0.0;
        Processor::FrequencyCounter counter;
        counter.changeFrequency(tableIndex);
        int iteration = 0;
        double value = 7.0 / 8.0;
        double targetLevel = 0.0;
        double targetRatio = 0.0001;
        double rate = 588.0;
        double coef = exp(-log((1.0 + targetRatio) / targetRatio) / rate);
        double base = (targetLevel - targetRatio) * (1.0 - coef);
        while (iteration < rate) {
            time += 0.03125;
            if (counter.tick()) {
                ++iteration;
                value = base + value * coef;
                //processor.output << "Iteration: " << iteration << ", base: " << base << ", coef: " << coef << ", Value: " << value << " after time: " << (timeInfo->outputBufferDacTime - startTime) * 1000.0 << std::endl;
            }

            if (iteration == rate) {
                processor.output.info("Iteration: ", iteration, ", Value: ", value, " after time: ", time);
            }
        }
    }

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
};

}
