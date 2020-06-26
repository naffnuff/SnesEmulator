#include "AudioRenderer.h"

#include <iostream>

#include <portaudio.h>

#include "System.h"
#include "Util.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace Audio {

static constexpr int sampleRate = 32000;
static constexpr int bufferSize = 1;

struct StreamHandler
{
    static void testAttack(Renderer& renderer, Byte tableIndex)
    {
        double time = 0.0;
        Renderer::FrequencyCounter counter;
        counter.changeFrequency((tableIndex << 1) + 0x1); // but not if tableIndex == 0xf
        int iteration = 0;
        double value = 0.0;
        while (value < 1.0) {
            time += 0.03125;
            if (counter.tick()) {
                ++iteration;
                value += 1.0 / 64.0;
            }
            if (value == 1.0)
            {
                renderer.output.info("tableIndex: ", tableIndex, ", Value: ", value, " after time: ", time);
            }
        }
    }

    static void testDecay(Renderer& renderer, Byte tableIndex)
    {
        double time = 0.0;
        Renderer::FrequencyCounter counter;
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
                //renderer.output << "Iteration: " << iteration << ", base: " << base << ", coef: " << coef << ", Value: " << value << " after time: " << (timeInfo->outputBufferDacTime - startTime) * 1000.0 << std::endl;
            }

            if (iteration == rate) {
                renderer.output.info("Iteration: ", iteration, ", Value: ", value, " after time: ", time);
            }
        }
    }

    static void testSustain(Renderer& renderer, Byte tableIndex)
    {
        double time = 0.0;
        Renderer::FrequencyCounter counter;
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
                //renderer.output << "Iteration: " << iteration << ", base: " << base << ", coef: " << coef << ", Value: " << value << " after time: " << (timeInfo->outputBufferDacTime - startTime) * 1000.0 << std::endl;
            }

            if (iteration == rate) {
                renderer.output.info("Iteration: ", iteration, ", Value: ", value, " after time: ", time);
            }
        }
    }

    static int callback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
    {
        Renderer& renderer = *(Renderer*)userData;
        try {
            float* out = (float*)output;

            for (int i = 0; i < 0x8; ++i) {
                //testAttack(renderer, i);
                //testDecay(renderer, i);
            }
            for (int i = 1; i < 0x20; ++i) {
                //testAttack(renderer, i);
                //testSustain(renderer, i);
            }
            //return paAbort;

            if (renderer.checkStreamStatus(statusFlags)) {
                renderer.outputSample(out[0], out[1]);
                renderer.printTimeInfo(timeInfo->currentTime);
                return paContinue;
            } else {
                renderer.output.error("ABORTING AUDIO RENDERER!");
                return paAbort;
            }
        } catch (const std::exception& e) {
            renderer.output.error("Caught std::exception in Audio Renderer: ", e.what());
            return paAbort;
        }
    }
};

void check(PaError error)
{
    if (error != paNoError) {
        throw RuntimeError(Pa_GetErrorText(error));
    }
}

Renderer::Renderer(Output& output)
    : output(output, "audio")
{
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
    output.debug("Initializing PortAudio version ", Pa_GetVersionInfo()->versionText);
    check(Pa_Initialize());
    initialized = true;

    for (int i = 0; i < tableSize; i++) {
        //sine[i] = sin(((double)i / (double)tableSize) * M_PI * 2.0);
        //double time = (double)i / (double)tableSize;
        //sine[i] = sampleSineWave(time, 0.01, 0.0) + sampleSquareWave(time, 1.0, 0.0) + sampleSawtoothWave(time, 0.5);
        //sine[i] = sampleSineWave(time, 0.01, 0.0) + sampleSineWave(time, 0.1, 0.0) + sampleSineWave(time, 0.5, 0.0);
        //sine[i] = sampleSquareWave(time, 0.01, 0.0) + sampleSineWave(time, 1.0, 0.0) + sampleSquareWave(time, 0.5, 0.0);
    }
}

void Renderer::startStream()
{
    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice) {
        throw RuntimeError("No output device found, device count=", Pa_GetDeviceCount());
    }
    outputParameters.channelCount = 2; // stereo
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    const PaDeviceInfo* info = Pa_GetDeviceInfo(outputParameters.device);

    output.debug("Host API ", Pa_GetHostApiInfo(info->hostApi)->name);

    check(Pa_OpenStream(&stream, nullptr, &outputParameters, sampleRate, bufferSize, paClipOff, StreamHandler::callback, this));
    check(Pa_StartStream(stream));
}

bool Renderer::checkStreamStatus(unsigned long statusFlags)
{
    if (false && statusFlags) {
        if (statusFlags & paInputUnderflow) {
            output.error("paInputUnderflow");
            inputUnderflow = true;
        }
        if (statusFlags & paInputOverflow) {
            output.error("paInputOverflow");
            inputOverflow = true;
        }
        if (statusFlags & paOutputUnderflow) {
            output.error("paOutputUnderflow");
            outputUnderflow = true;
        }
        if (statusFlags & paOutputOverflow) {
            output.error("paOutputOverflow");
            outputOverflow = true;
        }
        if (statusFlags & paPrimingOutput) {
            output.error("paPrimingOutput");
            primingOutput = true;
        }
        output.error("STREAM CALLBACK FLAGS: ", statusFlags);
        return false;
    } else {
        return true;
    }
}

void Renderer::outputSample(float& leftChannel, float& rightChannel)
{
    double leftSample = 0.0f;
    double rightSample = 0.0f;
    //double sampleCount = 0.0f;
    for (Audio::Renderer::Voice& voice : voices) {
        voice.calculateEnvelope();
        if (voice.envelope > 0.0) {
            double sample = voice.sample(soundLibrary);
            leftSample += sample * voice.envelope * voice.leftVolume;
            rightSample += sample * voice.envelope * voice.rightVolume;
            //leftSample += sine[counter] * voice.envelope * voice.leftVolume;
            //rightSample += sine[counter] * voice.envelope * voice.rightVolume;
            //++sampleCount;
        }
    }
    //leftSample /= sampleCount;
    //rightSample /= sampleCount;

    leftChannel = float(leftSample * mainVolumeLeft);
    rightChannel = float(rightSample * mainVolumeRight);
}

void Renderer::Voice::setEnvelopeStage(EnvelopeStage nextStage)
{
    if (nextStage == Attack) {
        inLoop = false;
        bufferOffset = 0.0;
        if (attackRate == 0xf) {
            envelope = 1.0;
        } else {
            frequencyCounter.changeFrequency((attackRate << 1) + 0x1);
        }
    } else if (nextStage == Decay || nextStage == Sustain && sustainRate > 0) {
        double targetLevel = 0.0;
        if (nextStage == Decay) {
            targetLevel = sustainLevel;
            frequencyCounter.changeFrequency((decayRate << 1) + 0x10);
        } else {
            frequencyCounter.changeFrequency(sustainRate);
        }
        constexpr double targetOvershoot = 0.0001;
        constexpr double stageLength = 588.0;
        outputCoefficient = exp(-::log((1.0 + targetOvershoot) / targetOvershoot) / stageLength);
        outputBase = (targetLevel - targetOvershoot) * (1.0 - outputCoefficient);
    }
    envelopeStage = nextStage;
}

void Renderer::Voice::calculateEnvelope()
{
    if (envelopeStage == Attack) {
        if (attackRate == 0xf) {
            envelope = 1.0;
        }
        else if (envelope < 1.0 && frequencyCounter.tick()) {
            envelope += 1.0 / 64.0;
        }
        if (envelope >= 1.0) {
            envelope = 1.0;
            setEnvelopeStage(Decay);
        }
    } else if (envelopeStage == Decay || envelopeStage == Sustain && sustainRate > 0) {
        double targetLevel = envelopeStage == Decay ? sustainLevel : 0.0;
        if (envelope > targetLevel && frequencyCounter.tick()) {
            output = outputBase + output * outputCoefficient;
        }
        if (envelope <= targetLevel) {
            envelope = targetLevel;
            setEnvelopeStage(EnvelopeStage(envelopeStage + 1));
        }
    } else if (envelopeStage == Release) {
        if (envelope > 0.0) {
            envelope -= 1.0 / 256.0;
        }
        if (envelope <= 0.0) {
            envelope = 0.0;
            setEnvelopeStage(Inactive);
        }
    }
}

double Renderer::Voice::sample(SoundLibrary& library)
{
    const Sound& sound = library[SoundLibraryKey(startAddress, loopAddress)];
    if (inLoop && sound.loop.empty()) {
        return 0.0;
    }
    bufferOffset += pitch;
    int roundedBufferOffset = int(bufferOffset + .5f);
    size_t bufferSize = inLoop ? sound.loop.size() : sound.start.size();
    int iterations = 0;
    while (roundedBufferOffset >= bufferSize) {
        if (++iterations > 2) {
            throw RuntimeError("Too many iterations when playing ", startAddress, ":", loopAddress, ", roundedBufferOffset: ", roundedBufferOffset, ", bufferSize: ", bufferSize, ", inLoop: ", inLoop);
        }
        bufferOffset -= double(bufferSize);
        roundedBufferOffset = int(bufferOffset + .5f);
        if (roundedBufferOffset < 0) {
            throw RuntimeError("roundedBufferOffset==", roundedBufferOffset);
        }
        inLoop = true;
        if (sound.loop.empty()) {
            return 0.0;
        }
        bufferSize = sound.loop.size();
    }
    return (inLoop ? sound.loop : sound.start)[roundedBufferOffset];
}

void Renderer::printTimeInfo(double currentTime)
{
    if (previousTimeInfoTime == 0.0) {
        previousTimeInfoTime = currentTime;
    }
    timeInfoTickCounter++;
    if (currentTime - previousTimeInfoTime >= 10.0) {
        output.debug("Audio ticks: ", targetTickCounter, " / ", timeInfoTickCounter, "(", 100.0 * targetTickCounter / timeInfoTickCounter, "%)");
        targetTickCounter = 0;
        timeInfoTickCounter = 0;
        previousTimeInfoTime = currentTime;
    }
}

void Renderer::checkStreamErrors()
{
    if (streamError) {
        if (inputUnderflow) {
            throw RuntimeError("Input underflow");
        } else if (inputOverflow) {
            throw RuntimeError("Input overflow");
        } else if (outputUnderflow) {
            throw RuntimeError("Output underflow");
        } else if (outputOverflow) {
            throw RuntimeError("Output overflow");
        } else if (primingOutput) {
            throw RuntimeError("Priming output");
        }
    }
}

}
