#include "AudioProcessor.h"

#include <iostream>

#include <portaudio.h>

#include "System.h"
#include "Util.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace Audio
{
Processor::FrequencyCounter::Table Processor::FrequencyCounter::frequencyTable = Processor::FrequencyCounter::getTable();

static constexpr int sampleRate = 32000;
static constexpr int bufferSize = 1;

struct StreamHandler
{
    static int callback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
    {
        Processor& processor = *(Processor*)userData;
        try
        {
            float* out = (float*)output;

            /*
            for (int i = 0; i < 0x8; ++i) {
                //testAttack(processor, i);
                //testDecay(processor, i);
            }
            for (int i = 1; i < 0x20; ++i) {
                //testAttack(processor, i);
                //testSustain(processor, i);
            }
            //return paAbort;
            */

            if (processor.checkStreamStatus(statusFlags))
            {
                processor.outputNextSample(out[0], out[1]);
                processor.printTimeInfo(timeInfo->currentTime);
                return paContinue;
            }
            else
            {
                processor.output.error("ABORTING AUDIO PROCESSOR!");
                return paAbort;
            }
        }
        catch (const AccessException& e)
        {
            processor.output.debug("Caught AccessException in Audio processor: ", e.what());
            return paContinue;
        }
        catch (const std::exception& e)
        {
            processor.output.error("Caught std::exception in Audio processor: ", e.what());
            return paAbort;
        }
    }
};

void check(PaError error)
{
    if (error != paNoError)
    {
        throw RuntimeError(Pa_GetErrorText(error));
    }
}

Processor::Processor(Output& output, Memory<Word>& spcMemory)
    : RegisterManager(output, "audio", dspMemory)
    , output(output, "audio")
    , spcMemory(spcMemory)
    , dspMemory(0x80)
{
}

Processor::~Processor()
{
    if (initialized)
    {
        check(Pa_Terminate());
        initialized = false;
    }
}

void Processor::initialize()
{
    //output.debug("Initializing PortAudio version ", Pa_GetVersionInfo()->versionText);
    check(Pa_Initialize());
    initialized = true;

    for (int i = 0; i < tableSize; i++)
    {
        //sine[i] = sin(((double)i / (double)tableSize) * M_PI * 2.0);
        //double time = (double)i / (double)tableSize;
        //sine[i] = sampleSineWave(time, 0.01, 0.0) + sampleSquareWave(time, 1.0, 0.0) + sampleSawtoothWave(time, 0.5);
        //sine[i] = sampleSineWave(time, 0.01, 0.0) + sampleSineWave(time, 0.1, 0.0) + sampleSineWave(time, 0.5, 0.0);
        //sine[i] = sampleSquareWave(time, 0.01, 0.0) + sampleSineWave(time, 1.0, 0.0) + sampleSquareWave(time, 0.5, 0.0);
    }
}

void Processor::startStream()
{
    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice)
    {
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

bool Processor::checkStreamStatus(unsigned long statusFlags)
{
    if (statusFlags)
    {
        if (statusFlags & paInputUnderflow)
        {
            output.error("paInputUnderflow");
            inputUnderflow = true;
        }
        if (statusFlags & paInputOverflow)
        {
            output.error("paInputOverflow");
            inputOverflow = true;
        }
        if (statusFlags & paOutputUnderflow)
        {
            output.error("paOutputUnderflow");
            outputUnderflow = true;
        }
        if (statusFlags & paOutputOverflow)
        {
            output.error("paOutputOverflow");
            outputOverflow = true;
        }
        if (statusFlags & paPrimingOutput)
        {
            output.error("paPrimingOutput");
            primingOutput = true;
        }
        output.error("STREAM CALLBACK FLAGS: ", statusFlags);
        return false;
    }
    else
    {
        return true;
    }
}

void Processor::tick()
{
    for (Audio::Processor::Voice& voice : voices)
	{
		if (((sourceDirectory << 8) | (voice.sourceNumber << 2)) != ((sourceDirectory << 8) + (voice.sourceNumber << 2)))
		{
			throw RuntimeError("Source address is wonky!");
		}
        voice.sourceAddress = (sourceDirectory << 8) + (voice.sourceNumber << 2);
    }

	++dspCycle;
	++targetTickCounter;
}

void Processor::outputNextSample(float& leftChannel, float& rightChannel)
{
    int32_t leftSampleSum = 0;
    int32_t rightSampleSum = 0;
    int16_t nextSample = 0;
    for (Audio::Processor::Voice& voice : voices)
	{
		//Audio::Processor::Voice& voice = voices[7];

        voice.calculateNextSample(nextSample);
        int16_t leftSample = Types::signedClamp<16, int16_t>(nextSample * voice.leftVolume >> 7);
        int16_t rightSample = Types::signedClamp<16, int16_t>(nextSample * voice.rightVolume >> 7);
        leftSampleSum = Types::signedClamp<16, int32_t>(leftSampleSum + leftSample);
        rightSampleSum = Types::signedClamp<16, int32_t>(rightSampleSum + rightSample);
    }
    leftSampleSum = Types::signedClamp<16, int32_t>(leftSampleSum * mainVolumeLeft >> 7);
    rightSampleSum = Types::signedClamp<16, int32_t>(rightSampleSum * mainVolumeRight >> 7);
    leftChannel = float(leftSampleSum) / float(leftSampleSum < 0 ? 0x8000 : 0x7fff);
    rightChannel = float(rightSampleSum) / float(rightSampleSum < 0 ? 0x8000 : 0x7fff);
}

void Processor::Voice::calculateNextSample(int16_t& nextSample)
{
    if (keyOnIsSet)
    {
        setupPhase = 5;
        keyOnIsSet = false;
    }
    if (keyOff)
    {
        setupPhase = 0;
        setADSRStage(ADSRStage::Release);
    }
    if (setupPhase > 0)
    {
        if (setupPhase == 5)
        {
            envelope = 0;
            adsrStage = ADSRStage::Inactive;
            readSampleAddress(false);
        }
        else if (setupPhase == 1)
        {
            setADSRStage(ADSRStage::Attack);
        }
        else
        {
            decodeNextBlock();
        }
        --setupPhase;
    }
    else
    {
        interpolationIndex += pitch;
        if (interpolationIndex > 0x7fff)
        {
            interpolationIndex = 0x7fff;
        }
        if (interpolationIndex >= 0x4000)
        {
            decodeNextBlock();
            interpolationIndex -= 0x4000;
        }
        nextSample = sampleBuffer[interpolationIndex >> 12];
        calculateEnvelope();
        if (envelope == 0)
        {
            nextSample = 0;
        }
        //nextSample = Types::signedClamp<16>(nextSample * envelope >> 11);
    }
}

void Processor::Voice::readSampleAddress(bool loopAddress)
{
    Word finalSourceAddress = sourceAddress;
    if (loopAddress)
    {
        finalSourceAddress += 2;
    }
    headerAddress = processor.spcMemory.readWord(finalSourceAddress);
    nextSampleAddress = headerAddress + 1;
}

void Processor::Voice::decodeNextBlock()
{
    for (size_t i = 0; i < 8; ++i)
    {
        sampleBuffer[i] = sampleBuffer[i + 4];
    }
    const Byte header = processor.spcMemory.readByte(headerAddress);
    const Byte filter = header.getBits(2, 2);
    const Byte range = header.getBits(4, 4);
    size_t bufferIndex = 8;
    for (int i = 0; i < 2; ++i)
    {
        const Byte sampleSource = processor.spcMemory.readByte(nextSampleAddress++);
        for (int8_t sample : { sampleSource.getBits(4, 4), sampleSource.getBits(0, 4) })
        {
            bool isNegative = false;
            if (sample >= 8)
            {
                isNegative = true;
                sample |= 0xf0;
            }
            int expandedSample = 0;
            if (range <= 12)
            {
                expandedSample = int16_t(int16_t(sample) << range) >> 1;
            }
            else if (isNegative)
            {
                expandedSample = 0xf800;
            }
            const int16_t lastSample = sampleBuffer[bufferIndex - 1];
            const int16_t secondLastSample = sampleBuffer[bufferIndex - 2];
            if (filter == 1)
            {
                expandedSample += lastSample + (-lastSample >> 4);
            }
            else if (filter == 2)
            {
                expandedSample += (lastSample << 1) + ((-((lastSample << 1) + lastSample)) >> 5) - secondLastSample + (secondLastSample >> 4);
            }
            else if (filter == 3)
            {
                expandedSample += (lastSample << 1) + ((-(lastSample + (lastSample << 2) + (lastSample << 3))) >> 6) - secondLastSample + (((secondLastSample << 1) + secondLastSample) >> 4);
            }
            expandedSample = Types::signedClamp<16, int>(expandedSample);
            sampleBuffer[bufferIndex++] = Types::clip<15, int16_t>(expandedSample);
        }
    }
    if (nextSampleAddress - headerAddress > 8)
    {
        if (header.getBit(0))
        { // end bit, really means "loop"
            if (!header.getBit(1))
            { // loop bit, really means "don't end"
                envelope = 0;
                adsrStage = ADSRStage::Inactive;
            }
            readSampleAddress(true);
        }
        else
        {
            headerAddress = nextSampleAddress;
            ++nextSampleAddress;
        }
    }
}

void Processor::Voice::setADSRStage(ADSRStage nextStage)
{
    if (nextStage == ADSRStage::Attack)
    {
        if (attackRate != 0xf)
        {
            frequencyCounter.changeFrequency((attackRate << 1) + 0x1);
        }
    }
    else if (nextStage == ADSRStage::Decay)
    {
        frequencyCounter.changeFrequency((decayRate << 1) + 0x10);
    }
    else if (nextStage == ADSRStage::Sustain)
    {
        frequencyCounter.changeFrequency(sustainRate);
    }
    adsrStage = nextStage;
}

void Processor::Voice::calculateEnvelope()
{
    if (adsrStage == ADSRStage::Attack)
    {
        if (attackRate == 0xf)
        {
            envelope += 1024;
        }
        else if (envelope < 0x7ff && frequencyCounter.tick())
        {
            envelope += 32;
        }
        if (envelope > 0x7ff)
        {
            envelope = 0x7ff;
            setADSRStage(ADSRStage::Decay);
        }
    }
    else if ((adsrStage == ADSRStage::Decay || adsrStage == ADSRStage::Sustain) && frequencyCounter.tick())
    {
        const int16_t targetLevel = adsrStage == ADSRStage::Decay ? (sustainLevel << 8 & 0xff) : 0;
        if (envelope > targetLevel)
        {
            envelope -= ((envelope - 1) >> 8) + 1;
        }
        if (envelope <= targetLevel)
        {
            setADSRStage(ADSRStage(int(adsrStage) + 1));
        }
    }
    if (adsrStage == ADSRStage::Release)
    {
        if (envelope > 0)
        {
            envelope -= 8;
        }
        if (envelope <= 0)
        {
            envelope = 0;
            setADSRStage(ADSRStage::Inactive);
        }
    }
}

void Processor::printTimeInfo(double currentTime)
{
    if (previousTimeInfoTime == 0.0)
    {
        previousTimeInfoTime = currentTime;
    }
    timeInfoTickCounter++;
    if (currentTime - previousTimeInfoTime >= 10.0)
    {
        output.debug("Audio ticks: ", targetTickCounter, " / ", timeInfoTickCounter, "(", 100.0 * targetTickCounter / timeInfoTickCounter, "%)");
        targetTickCounter = 0;
        timeInfoTickCounter = 0;
        previousTimeInfoTime = currentTime;
    }
}

void Processor::checkStreamErrors()
{
    if (streamError)
    {
        if (inputUnderflow)
        {
            throw RuntimeError("Input underflow");
        }
        else if (inputOverflow)
        {
            throw RuntimeError("Input overflow");
        }
        else if (outputUnderflow)
        {
            throw RuntimeError("Output underflow");
        }
        else if (outputOverflow)
        {
            throw RuntimeError("Output overflow");
        }
        else if (primingOutput)
        {
            throw RuntimeError("Priming output");
        }
    }
}

}
