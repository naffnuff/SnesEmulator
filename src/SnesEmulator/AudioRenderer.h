#pragma once

#include <iostream>

#include <portaudio.h>

#include "Util.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

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
    static constexpr int voiceCount = 8;
    static constexpr int sampleRate = 32000;
    static constexpr int bufferSize = 1;
    static constexpr int tableSize = 50;

    Renderer(std::ostream& output, std::ostream& error)
        : output(output)
        , error(error)
    {
        output << "Initializing PortAudio version " << Pa_GetVersionInfo()->versionText << std::endl;
        Check(Pa_Initialize());
        initialized = true;

        PaStreamParameters outputParameters;
        outputParameters.device = Pa_GetDefaultOutputDevice();
        if (outputParameters.device == paNoDevice) {
            throw Exception("No output device found, device count=" + Util::toString(Pa_GetDeviceCount()));
        }
        outputParameters.channelCount = 2; // stereo
        outputParameters.sampleFormat = paFloat32;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;
        const PaDeviceInfo* info = Pa_GetDeviceInfo(outputParameters.device);

        output << "Host API " << Pa_GetHostApiInfo(info->hostApi)->name << std::endl;

        for (int i = 0; i < tableSize; i++) {
            sine[i] = (float)sin(((double)i / (double)tableSize) * M_PI * 2.0);
            output << sine[i] << ".";
        }

        Check(Pa_OpenStream(&stream, nullptr, &outputParameters, sampleRate, bufferSize, paClipOff, streamCallback, this));
        Check(Pa_StartStream(stream));
    }

    ~Renderer()
    {
        if (initialized) {
            Check(Pa_Terminate());
            initialized = false;
        }
    }

    static int streamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
    {
        Renderer& renderer = *(Renderer*)userData;
        float* out = (float*)output;

        std::vector<float> samples;
        for (Renderer::Data& data : renderer.data) {
            if (data.playing) {
                data.counter += data.pitch;
                int counter = int(data.counter + .5f);
                if (counter >= Renderer::tableSize) {
                    data.counter -= Renderer::tableSize;
                    counter = int(data.counter + .5f);
                }
                samples.push_back(renderer.sine[counter]);
            }
        }
        renderer.sample = 0.0f;
        for (float sample : samples) {
            renderer.sample += sample;
        }
        renderer.sample /= float(samples.size());

        out[0] = renderer.sample;
        out[1] = renderer.sample;

        static double previousTime = timeInfo->currentTime;
        static int count = 0;
        double currentTime = timeInfo->currentTime;
        count++;
        if (currentTime - previousTime >= 1.0) {
            renderer.output << "Rend: " << count << std::endl;

            count = 0;
            previousTime = currentTime;
        }
        return paContinue;
    }

private:
    void Check(PaError error) const
    {
        if (error != paNoError) {
            throw Exception(Pa_GetErrorText(error));
        }
    }

public:
    struct Data
    {
        bool playing = false;
        float counter = 0.0f;
        float pitch = 1.0f;
    };

    float sine[tableSize];

    std::array<Data, voiceCount> data;

    float sample = 0.0f;

private:
    std::ostream& output;
    std::ostream& error;

    bool initialized = false;

    PaStream* stream;
    //float counter = 0;

};

}
