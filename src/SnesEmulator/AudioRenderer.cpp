#include "AudioRenderer.h"

#include <iostream>

#include <portaudio.h>

#include "Util.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace Audio {

static constexpr int sampleRate = 32000;
static constexpr int bufferSize = 1;

struct StreamHandler
{
    static int callback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
    {
        Audio::Renderer& renderer = *(Audio::Renderer*)userData;
        float* out = (float*)output;

        if (renderer.checkStreamStatus(statusFlags)) {
            renderer.outputSample(out[0], out[1]);
            renderer.printTimeInfo(timeInfo->currentTime);
            return paContinue;
        } else {
            renderer.output << "ABORTING AUDIO RENDERER!" << std::endl;
            return paAbort;
        }
    }
};

void check(PaError error)
{
    if (error != paNoError) {
        throw Audio::Exception(Pa_GetErrorText(error));
    }
}

Renderer::Renderer(std::ostream& output, std::ostream& error)
    : output(output)
    , error(error)
{
    size_t index = frequencyTable.size();
    frequencyTable[--index] = 1;
    frequencyTable[--index] = 2;
    for (int i = 0; i < 10; ++i) {
        frequencyTable[--index] = 3 << i;
        frequencyTable[--index] = 4 << i;
        frequencyTable[--index] = 5 << i;
    }
    frequencyTable[0] = 0;
    output << "Frequencies:" << std::endl;
    for (int frequency : frequencyTable) {
        output << frequency << std::endl;
    }
    output << "***" << std::endl;
}

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

    for (int i = 0; i < tableSize; i++) {
        sine[i] = (float)sin(((double)i / (double)tableSize) * M_PI * 2.0);
    }
}

void Renderer::startStream()
{
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

    check(Pa_OpenStream(&stream, nullptr, &outputParameters, sampleRate, bufferSize, paClipOff, StreamHandler::callback, this));
    check(Pa_StartStream(stream));
}

bool Renderer::checkStreamStatus(unsigned long statusFlags)
{
    if (false && statusFlags) {
        if (statusFlags & paInputUnderflow) {
            output << "paInputUnderflow" << std::endl;
            inputUnderflow = true;
        }
        if (statusFlags & paInputOverflow) {
            output << "paInputOverflow" << std::endl;
            inputOverflow = true;
        }
        if (statusFlags & paOutputUnderflow) {
            output << "paOutputUnderflow" << std::endl;
            outputUnderflow = true;
        }
        if (statusFlags & paOutputOverflow) {
            output << "paOutputOverflow" << std::endl;
            outputOverflow = true;
        }
        if (statusFlags & paPrimingOutput) {
            output << "paPrimingOutput" << std::endl;
            primingOutput = true;
        }
        output << std::endl << "STREAM CALLBACK FLAGS: " << statusFlags << std::endl;
        return false;
    } else {
        return true;
    }
}

void Renderer::outputSample(float& leftChannel, float& rightChannel)
{
    double leftSample = 0.0f;
    double rightSample = 0.0f;
    double sampleCount = 0.0f;
    for (Audio::Renderer::Data& data : data) {
        calculateEnvelope(data);
        if (data.envelopeStage != Inactive) {
            if (data.envelope == 0.0) {
                output << "WTF" << std::endl;
                output << data.envelope << std::endl;
            }
            data.counter += data.pitch;
            int counter = int(data.counter + .5f);
            if (counter >= Audio::Renderer::tableSize) {
                data.counter -= Audio::Renderer::tableSize;
                counter = int(data.counter + .5f);
            }
            leftSample += sine[counter] * data.envelope * data.leftVolume;
            rightSample += sine[counter] * data.envelope * data.rightVolume;
            ++sampleCount;
        }
    }
    leftSample /= sampleCount;
    rightSample /= sampleCount;

    leftChannel = float(leftSample * mainVolumeLeft);
    rightChannel = float(rightSample * mainVolumeRight);
}

void Renderer::calculateEnvelope(Data& data)
{
    if (data.envelopeStage == Attack) {
        if (data.envelope < 1.0) {
            constexpr double increment = 1.0 / 64.0;
            data.envelope += increment;
            if (data.envelope >= 1.0) {
                data.envelope = 1.0;
                data.envelopeStage = Sustain;
            }
        }
    } else if (data.envelopeStage == Decay) {
    } else if (data.envelopeStage == Sustain) {
    } else if (data.envelopeStage == Release) {
        if (data.envelope > 0.0) {
            constexpr double decrement = 1.0 / 256.0;
            data.envelope -= decrement;
        }
        if (data.envelope <= 0.0) {
            data.envelope = 0.0;
            data.envelopeStage = Inactive;
        }
    } else if (data.envelopeStage != Inactive) {
        throw Exception("Illegal envelope stage");
    }
}

void Renderer::printTimeInfo(double currentTime)
{
    if (previousTimeInfoTime == 0.0) {
        previousTimeInfoTime = currentTime;
    }
    timeInfoTickCounter++;
    if (currentTime - previousTimeInfoTime >= 10.0) {
        output << "Audio ticks: " << targetTickCounter << " / " << timeInfoTickCounter << "(" << (100.0 * targetTickCounter / timeInfoTickCounter) << "%)" << std::endl;
        targetTickCounter = 0;
        timeInfoTickCounter = 0;
        previousTimeInfoTime = currentTime;
    }
}

void Renderer::checkStreamErrors()
{
    if (streamError) {
        std::string message;
        if (inputUnderflow) {
            message = "Input underflow";
        } else if (inputOverflow) {
            message = "Input overflow";
        } else if (outputUnderflow) {
            message = "Output underflow";
        } else if (outputOverflow) {
            message = "Output overflow";
        } else if (primingOutput) {
            message = "Priming output";
        }
        output << message << std::endl;
        throw Exception(message);
    }
}

}
