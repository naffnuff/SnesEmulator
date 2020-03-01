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
public:
    enum EnvelopeStage
    {
        Inactive,
        Attack,
        Decay,
        Sustain,
        Release,
    };

    struct Data
    {
        double leftVolume = 0.0f;
        double rightVolume = 0.0f;
        double counter = 0.0f;
        double pitch = 1.0f;
        EnvelopeStage envelopeStage = Inactive;
        double envelope = 0.0;
        int frequencyOffset = 0;
        int frequencyTarget = 0;
        double output = 0.0;
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
    void calculateEnvelope(Data& data);

    void printTimeInfo(double currentTime);

public:
    std::array<int, 32> frequencyTable;

    double sine[tableSize];

    std::array<Data, voiceCount> data;

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
