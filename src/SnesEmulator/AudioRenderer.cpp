#include "AudioRenderer.h"

#include <iostream>

#include <portaudio.h>

#include "Util.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace {

static constexpr int sampleRate = 32000;
static constexpr int bufferSize = 1;

int streamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    Audio::Renderer& renderer = *(Audio::Renderer*)userData;
    float* out = (float*)output;

    if (statusFlags) {
        if (statusFlags & paInputUnderflow) {
            renderer.output << "paInputUnderflow" << std::endl;
            renderer.inputUnderflow = true;
        }
        if (statusFlags & paInputOverflow) {
            renderer.output << "paInputOverflow" << std::endl;
            renderer.inputOverflow = true;
        }
        if (statusFlags & paOutputUnderflow) {
            renderer.output << "paOutputUnderflow" << std::endl;
            renderer.outputUnderflow = true;
        }
        if (statusFlags & paOutputOverflow) {
            renderer.output << "paOutputOverflow" << std::endl;
            renderer.outputOverflow = true;
        }
        if (statusFlags & paPrimingOutput) {
            renderer.output << "paPrimingOutput" << std::endl;
            renderer.primingOutput = true;
        }
        renderer.output << std::endl << "STREAM CALLBACK FLAGS: " << statusFlags << std::endl;
    }

    float sample = 0.0f;
    float sampleCount = 0.0f;
    for (Audio::Renderer::Data& data : renderer.data) {
        if (data.playing) {
            data.counter += data.pitch;
            int counter = int(data.counter + .5f);
            if (counter >= Audio::Renderer::tableSize) {
                data.counter -= Audio::Renderer::tableSize;
                counter = int(data.counter + .5f);
            }
            sample += renderer.sine[counter];
            ++sampleCount;
        }
    }
    sample /= float(sampleCount);

    out[0] = sample;
    out[1] = sample;

    static double previousTime = timeInfo->currentTime;
    static int count = 0;
    double currentTime = timeInfo->currentTime;
    count++;
    if (currentTime - previousTime >= 1.0) {
        renderer.output << "Proc: " << renderer.counter << std::endl;
        renderer.output << "Rend: " << count << std::endl;
        renderer.counter = 0;
        count = 0;
        previousTime = currentTime;
    }

    if (statusFlags) {
        renderer.output << "ABORTING AUDIO!" << std::endl;
        //return paContinue;
        return paAbort;
    } else {
        //renderer.output << "CONTINUING AS FUCK!" << std::endl;
        return paContinue;
    }
}

void check(PaError error)
{
    if (error != paNoError) {
        throw Audio::Exception(Pa_GetErrorText(error));
    }
}

}

namespace Audio {

Renderer::~Renderer()
{
    if (initialized) {
        check(Pa_Terminate());
        initialized = false;
    }
}

void Renderer::initialize()
{
    output << "Initializing PortAudio version " << Pa_GetVersionInfo()->versionText << std::endl;
    check(Pa_Initialize());
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

    PaStream* stream;
    check(Pa_OpenStream(&stream, nullptr, &outputParameters, sampleRate, bufferSize, paClipOff, streamCallback, this));
    check(Pa_StartStream(stream));
}

void Renderer::tick()
{
    if (inputUnderflow) {
        output << "inputUnderflow" << std::endl;
        throw Exception("Input underflow");
    } else if (inputOverflow) {
        output << "inputOverflow" << std::endl;
        throw Exception("Input overflow");
    } else if (outputUnderflow) {
        output << "outputUnderflow" << std::endl;
        throw Exception("Output underflow");
    } else if (outputOverflow) {
        output << "outputOverflow" << std::endl;
        throw Exception("Output overflow");
    } else if (primingOutput) {
        output << "primingOutput" << std::endl;
        throw Exception("Priming output");
    }
    ++counter;
}

}
