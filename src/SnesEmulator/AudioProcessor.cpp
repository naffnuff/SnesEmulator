#include "AudioProcessor.h"

#include <iostream>

#include <portaudio.h>

#include "System.h"
#include "Util.h"

#define PROFILING_ENABLED false

#include "Profiler.h"

CREATE_PROFILER();

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace Audio
{

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

static constexpr Processor::SampleCycleTable createSampleCycleTable();

Processor::Processor(Output& output, Memory<Word>& spcMemory)
    : RegisterManager(output, "audio", dspMemory)
    , output(output, "audio")
    , spcMemory(spcMemory)
    , dspMemory(0x80, output)
{
    timers[2].highPrecision = true;

    Voice* previousVoice = nullptr;
    for (Voice& voice : voices)
    {
        voice.previousVoice = previousVoice;
        previousVoice = &voice;
    }

    leftOutputBuffer.resize(outputBufferSize, 0);
    rightOutputBuffer.resize(outputBufferSize, 0);

    sampleCycleTable = createSampleCycleTable();
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

    //for (int i = 0; i < tableSize; i++)
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

void Processor::outputNextSample(float& leftChannel, float& rightChannel)
{

    if (!dspOutputStarted)
    {
        dspOutputStarted = true;

        dspOutputCount = rightOutputCount;

        output.debug("Starting dsp output cycle ", rightOutputCount);
    }

    if (dspOutputCount <= rightOutputCount)
    {
        const size_t outputLag = leftOutputCount - dspOutputCount;

        const size_t oldOutputBufferSize = outputBufferSize;

        while (outputLag * 2 > outputBufferSize)
        {
            std::lock_guard outputBufferLock(outputBufferMutex);

            outputBufferSize <<= 1;
            leftOutputBuffer.resize(outputBufferSize);
            rightOutputBuffer.resize(outputBufferSize);

            for (int i = 0; i < oldOutputBufferSize; ++i)
            {
                leftOutputBuffer[i + oldOutputBufferSize] = leftOutputBuffer[i];
                rightOutputBuffer[i + oldOutputBufferSize] = rightOutputBuffer[i];
            }
        }

        if (oldOutputBufferSize != outputBufferSize)
        {
            output.debug("Iteration ", dspOutputCount, " New buffer size ", outputBufferSize);
        }

        maxOutputLag = std::max<size_t>(maxOutputLag, outputLag);

        const size_t outputIndex = dspOutputCount & (outputBufferSize - 1);

        leftChannel = leftOutputBuffer[outputIndex];
        rightChannel = rightOutputBuffer[outputIndex];

        ++dspOutputCount;

        if (lastDebugOutputCounter++ == 100000)
        {
            output.debug("Output count ", dspOutputCount);
            output.debug("Output index ", outputIndex);
            output.debug("Current ouput lag ", outputLag);
            output.debug("Max output lag ", maxOutputLag);
            output.debug("Buffer underrun counter ", outputBufferUnderrunCounter);
            lastDebugOutputCounter = 0;
        }
    }
    else
    {
        leftChannel = 0.0f;
        rightChannel = 0.0f;

        ++outputBufferUnderrunCounter;

    }

    /*leftSampleSum = 0;
    rightSampleSum = 0;
    int i = 0;
    for (Audio::Processor::Voice& voice : voices)
	{
        try
        {
            //Audio::Processor::Voice& voice = voices[0];

            voice.calculateNextSample();
            int16_t leftSample = voice.applyVolume(voice.leftVolume);
            int16_t rightSample = voice.applyVolume(voice.rightVolume);
            leftSampleSum = Types::signedClamp<16, int32_t>(leftSampleSum + leftSample);
            rightSampleSum = Types::signedClamp<16, int32_t>(rightSampleSum + rightSample);
        }
        catch (const std::runtime_error& e)
        {
            output.error("Exception in voice ", i);
            output.error(e.what());
        }

        ++i;
    }

    leftSampleSum = Types::signedClamp<16, int32_t>(leftSampleSum * mainVolumeLeft >> 7);
    rightSampleSum = Types::signedClamp<16, int32_t>(rightSampleSum * mainVolumeRight >> 7);
    leftChannel = float(leftSampleSum) / float(leftSampleSum < 0 ? 0x8000 : 0x7fff);
    rightChannel = float(rightSampleSum) / float(rightSampleSum < 0 ? 0x8000 : 0x7fff);*/
}

/*void Processor::Voice::calculateNextSample()
{
    if (keyOnInternal)
    {
        setupPhase = 5;
        keyOnInternal = false;
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
        else // 4, 3, 2
        {
            decodeNextBlock();
        }
        //calculateEnvelope();
        --setupPhase;
        nextSample = 0;
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
        nextSample = Types::signedClamp<16, int16_t>(int(nextSample) * int(envelope) >> 11);
    }
}*/

int16_t Processor::Voice::applyVolume(int8_t volume)
{
    return Types::signedClamp<16, int16_t>(nextSample * volume >> 7);
}

void Processor::Voice::readSampleAddress(bool loopAddress)
{
    Word finalSourceAddress = (processor.sourceDirectory << 8) | sourceNumber << 2;
    if (loopAddress)
    {
        finalSourceAddress += 2;
    }

    try
    {
        headerAddress = processor.spcMemory.readWord(finalSourceAddress);
    }
    catch (const std::runtime_error& e)
    {
        processor.output.error("Exception while reading header address, loopAddress=", loopAddress);
        throw e;
    }

    nextSampleAddress = headerAddress + 1;
}

void Processor::Voice::decodeSampleSource()
{
    for (size_t i = 0; i < 8; ++i)
    {
        sampleBuffer[i] = sampleBuffer[i + 4];
    }

    const Byte filter = header.getBits(2, 2);
    const Byte range = header.getBits(4, 4);
    size_t bufferIndex = 8;
    for (const Byte& byte : sampleSource)
    {
        for (int8_t sample : { byte.getBits(4, 4), byte.getBits(0, 4) })
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
            //sampleBuffer[bufferIndex++] = Types::clip<15, int16_t>(expandedSample); WTF?
            sampleBuffer[bufferIndex++] = Types::clip<16, int16_t>(expandedSample);
        }
    }

    nextSampleAddress += 2;
}

/*void Processor::Voice::decodeNextBlock()
{
    if (nextSampleAddress - headerAddress > 8)
    {
        if (header.getBit(0))
        { // end bit set
            if (!header.getBit(1))
            { // loop bit not set
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

    header = processor.spcMemory.readByte(headerAddress);

    sampleSource[0] = processor.spcMemory.readByte(nextSampleAddress);
    sampleSource[1] = processor.spcMemory.readByte(nextSampleAddress + 1);

    decodeSampleSource();
}*/

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
    else if (adsrStage == ADSRStage::Decay && frequencyCounter.tick())
    {
        if ((envelope >> 8) != sustainLevel)
        {
            envelope -= ((envelope - 1) >> 8) + 1;
        }
        if ((envelope >> 8) == sustainLevel)
        {
            setADSRStage(ADSRStage::Sustain);
        }
    }
    else if (adsrStage == ADSRStage::Sustain && frequencyCounter.tick())
    {
        if (envelope > 0)
        {
            envelope -= ((envelope - 1) >> 8) + 1;
        }
        if (envelope <= 0)
        {
            envelope = 0;
            setADSRStage(ADSRStage::Release);
        }
    }
    else if (adsrStage == ADSRStage::Release)
    {
        if (envelope > 0)
        {
            envelope -= 8;
        }
        if (envelope <= 0)
        {
            envelope = 0;
            setADSRStage(ADSRStage::Inactive);
            sampleStage = SampleStage::Inactive;
        }
    }
}

// Gaussian table by libopenspc
// Take note of the 'int32' datatype. These 11-bit hex values are all
// positive and must be treated as signed.
static const int32_t gauss_coeffs[512] = {
0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
0x001, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001,
0x001, 0x001, 0x001, 0x002, 0x002, 0x002, 0x002, 0x002,
0x002, 0x002, 0x003, 0x003, 0x003, 0x003, 0x003, 0x004,
0x004, 0x004, 0x004, 0x004, 0x005, 0x005, 0x005, 0x005,
0x006, 0x006, 0x006, 0x006, 0x007, 0x007, 0x007, 0x008,
0x008, 0x008, 0x009, 0x009, 0x009, 0x00A, 0x00A, 0x00A,
0x00B, 0x00B, 0x00B, 0x00C, 0x00C, 0x00D, 0x00D, 0x00E,
0x00E, 0x00F, 0x00F, 0x00F, 0x010, 0x010, 0x011, 0x011,
0x012, 0x013, 0x013, 0x014, 0x014, 0x015, 0x015, 0x016,
0x017, 0x017, 0x018, 0x018, 0x019, 0x01A, 0x01B, 0x01B,
0x01C, 0x01D, 0x01D, 0x01E, 0x01F, 0x020, 0x020, 0x021,
0x022, 0x023, 0x024, 0x024, 0x025, 0x026, 0x027, 0x028,
0x029, 0x02A, 0x02B, 0x02C, 0x02D, 0x02E, 0x02F, 0x030,
0x031, 0x032, 0x033, 0x034, 0x035, 0x036, 0x037, 0x038,
0x03A, 0x03B, 0x03C, 0x03D, 0x03E, 0x040, 0x041, 0x042,
0x043, 0x045, 0x046, 0x047, 0x049, 0x04A, 0x04C, 0x04D,
0x04E, 0x050, 0x051, 0x053, 0x054, 0x056, 0x057, 0x059,
0x05A, 0x05C, 0x05E, 0x05F, 0x061, 0x063, 0x064, 0x066,
0x068, 0x06A, 0x06B, 0x06D, 0x06F, 0x071, 0x073, 0x075,
0x076, 0x078, 0x07A, 0x07C, 0x07E, 0x080, 0x082, 0x084,
0x086, 0x089, 0x08B, 0x08D, 0x08F, 0x091, 0x093, 0x096,
0x098, 0x09A, 0x09C, 0x09F, 0x0A1, 0x0A3, 0x0A6, 0x0A8,
0x0AB, 0x0AD, 0x0AF, 0x0B2, 0x0B4, 0x0B7, 0x0BA, 0x0BC,
0x0BF, 0x0C1, 0x0C4, 0x0C7, 0x0C9, 0x0CC, 0x0CF, 0x0D2,
0x0D4, 0x0D7, 0x0DA, 0x0DD, 0x0E0, 0x0E3, 0x0E6, 0x0E9,
0x0EC, 0x0EF, 0x0F2, 0x0F5, 0x0F8, 0x0FB, 0x0FE, 0x101,
0x104, 0x107, 0x10B, 0x10E, 0x111, 0x114, 0x118, 0x11B,
0x11E, 0x122, 0x125, 0x129, 0x12C, 0x130, 0x133, 0x137,
0x13A, 0x13E, 0x141, 0x145, 0x148, 0x14C, 0x150, 0x153,
0x157, 0x15B, 0x15F, 0x162, 0x166, 0x16A, 0x16E, 0x172,
0x176, 0x17A, 0x17D, 0x181, 0x185, 0x189, 0x18D, 0x191,
0x195, 0x19A, 0x19E, 0x1A2, 0x1A6, 0x1AA, 0x1AE, 0x1B2,
0x1B7, 0x1BB, 0x1BF, 0x1C3, 0x1C8, 0x1CC, 0x1D0, 0x1D5,
0x1D9, 0x1DD, 0x1E2, 0x1E6, 0x1EB, 0x1EF, 0x1F3, 0x1F8,
0x1FC, 0x201, 0x205, 0x20A, 0x20F, 0x213, 0x218, 0x21C,
0x221, 0x226, 0x22A, 0x22F, 0x233, 0x238, 0x23D, 0x241,
0x246, 0x24B, 0x250, 0x254, 0x259, 0x25E, 0x263, 0x267,
0x26C, 0x271, 0x276, 0x27B, 0x280, 0x284, 0x289, 0x28E,
0x293, 0x298, 0x29D, 0x2A2, 0x2A6, 0x2AB, 0x2B0, 0x2B5,
0x2BA, 0x2BF, 0x2C4, 0x2C9, 0x2CE, 0x2D3, 0x2D8, 0x2DC,
0x2E1, 0x2E6, 0x2EB, 0x2F0, 0x2F5, 0x2FA, 0x2FF, 0x304,
0x309, 0x30E, 0x313, 0x318, 0x31D, 0x322, 0x326, 0x32B,
0x330, 0x335, 0x33A, 0x33F, 0x344, 0x349, 0x34E, 0x353,
0x357, 0x35C, 0x361, 0x366, 0x36B, 0x370, 0x374, 0x379,
0x37E, 0x383, 0x388, 0x38C, 0x391, 0x396, 0x39B, 0x39F,
0x3A4, 0x3A9, 0x3AD, 0x3B2, 0x3B7, 0x3BB, 0x3C0, 0x3C5,
0x3C9, 0x3CE, 0x3D2, 0x3D7, 0x3DC, 0x3E0, 0x3E5, 0x3E9,
0x3ED, 0x3F2, 0x3F6, 0x3FB, 0x3FF, 0x403, 0x408, 0x40C,
0x410, 0x415, 0x419, 0x41D, 0x421, 0x425, 0x42A, 0x42E,
0x432, 0x436, 0x43A, 0x43E, 0x442, 0x446, 0x44A, 0x44E,
0x452, 0x455, 0x459, 0x45D, 0x461, 0x465, 0x468, 0x46C,
0x470, 0x473, 0x477, 0x47A, 0x47E, 0x481, 0x485, 0x488,
0x48C, 0x48F, 0x492, 0x496, 0x499, 0x49C, 0x49F, 0x4A2,
0x4A6, 0x4A9, 0x4AC, 0x4AF, 0x4B2, 0x4B5, 0x4B7, 0x4BA,
0x4BD, 0x4C0, 0x4C3, 0x4C5, 0x4C8, 0x4CB, 0x4CD, 0x4D0,
0x4D2, 0x4D5, 0x4D7, 0x4D9, 0x4DC, 0x4DE, 0x4E0, 0x4E3,
0x4E5, 0x4E7, 0x4E9, 0x4EB, 0x4ED, 0x4EF, 0x4F1, 0x4F3,
0x4F5, 0x4F6, 0x4F8, 0x4FA, 0x4FB, 0x4FD, 0x4FF, 0x500,
0x502, 0x503, 0x504, 0x506, 0x507, 0x508, 0x50A, 0x50B,
0x50C, 0x50D, 0x50E, 0x50F, 0x510, 0x511, 0x511, 0x512,
0x513, 0x514, 0x514, 0x515, 0x516, 0x516, 0x517, 0x517,
0x517, 0x518, 0x518, 0x518, 0x518, 0x518, 0x519, 0x519
};

//  S1.
template<>
void Processor::Voice::doStep<1>()
{
    //  1. Load VxSRCN register, if necessary.
    sourceNumber = registers[size_t(Register::VxSRCN)];
}

//  S2.
template<>
void Processor::Voice::doStep<2>()
{
    //  1. Load the sample pointer(using previously loaded DIR and VxSRCN) if
    //  necessary.
    if (sampleStage == SampleStage::AddressRead)
    {
        readSampleAddress(false);
        endOfSample = false;
        shouldLoop = false;
    }
    else
    {
        const bool endOfBlock = nextSampleAddress - headerAddress > 8;
        if (endOfBlock)
        {
            endOfSample = header.getBit(0);
            shouldLoop = header.getBit(1);

            if (endOfSample)
            {
                readSampleAddress(true);
            }
            else
            {
                headerAddress = nextSampleAddress;
                ++nextSampleAddress;
            }
        }
    }

    //  2. Load VxPITCHL register.
    pitch.setLowByte(registers[size_t(Register::VxPITCHL)]);

    //  3. Load VxADSR1 register.
    Byte adsr1 = registers[size_t(Register::VxADSR1)];
    attackRate = adsr1.getBits(0, 4);
    decayRate = adsr1.getBits(4, 3);
    if (adsr1.getBit(7))
    {
        envelopeType = Processor::Voice::EnvelopeType::ADSR;
    }
    else
    {
        envelopeType = Processor::Voice::EnvelopeType::Gain;
    }
}

//  S3a.
void Processor::Voice::doStep3a()
{
    //  1. Load VxPITCHH register.
    pitch.setHighByte(registers[size_t(Register::VxPITCHH)].getBits(0, 6));

    //  2. Apply pitch modulation if applicable.
    if (pitchModulation)
    {
        throw NotYetImplementedException("Pitch modulation is not yet implemented in voice step 3a");
    }
}

//  S3b.
void Processor::Voice::doStep3b()
{
    if (sampleStage > SampleStage::Inactive)
    {
        //  1. Load the BRR header byte (every time)
        header = processor.spcMemory.readByte(headerAddress);

        //  2. Read the first of the two BRR bytes that will be decoded.
        sampleSource[0] = processor.spcMemory.readByte(nextSampleAddress);
    }
}

//  S3c.
void Processor::Voice::doStep3c()
{
    //  1. If applicable, replace the current sample with the noise sample.
    // TODO

    //  2. Apply the volume envelope.
    //  - This is the value used for modulating the next voice's pitch, if
    //  applicable.
    nextSample = Types::signedClamp<16, int16_t>(int(nextSample) * int(envelope) >> 11);

    //  3. Check FLG bit 7 (NOT previously loaded).
    processor.reset = processor.registers[size_t(Processor::Register::FLG)].getBit(7);
    if (processor.reset)
    {
        // TODO
    }

    if (sampleStage > SampleStage::Inactive)
    {
        //  4. Check BRR header 'e' and 'l' bits to determine if the voice ends.
        if (endOfSample && !shouldLoop)
        { // loop bit not set
            // TODO is this really immediate?
            envelope = 0;
            adsrStage = ADSRStage::Inactive;
        }
    }

    //  5. Handle KOFF and KON using previously loaded values. If KON, ENDX.x will
    //  be cleared in step S7.
    // TODO - ENDX.x
    if (keyOnInternal)
    {
        envelope = 0;
        adsrStage = ADSRStage::Inactive;
        sampleStage = SampleStage::Reset;
    }
    if (keyOff)
    {
        sampleStage = SampleStage::Playing;
        setADSRStage(ADSRStage::Release);
    }

    //  6. Load VxGAIN or VxADSR2 register depending on ADSR1.7.
    if (envelopeType == Processor::Voice::EnvelopeType::ADSR)
    {
        Byte adsr2 = registers[size_t(Register::VxADSR2)];
        sustainRate = adsr2.getBits(0, 5);
        sustainLevel = adsr2.getBits(5, 3);
    }
    else // envelopeType == Processor::Voice::EnvelopeType::GAIN
    {
        Byte gain = registers[size_t(Register::VxGAIN)];
        if (gain.getBit(7))
        {
            gainMode = Processor::Voice::GainMode(uint8_t(gain.getBits(5, 2)));
            gainLevel = gain.getBits(0, 5);
        }
        else
        {
            gainMode = Processor::Voice::GainMode::Direct;
            gainLevel = gain.getBits(0, 7);
        }
    }

    if (sampleStage == SampleStage::PreparePlay)
    {
        setADSRStage(ADSRStage::Attack);
    }

    //  7. Update the volume envelope, using previously loaded values.
    calculateEnvelope();

}

template<>
void Processor::Voice::doStep<3>()
{
    doStep3a();
    doStep3b();
    doStep3c();
}

//  S4.
template<>
void Processor::Voice::doStep<4>()
{
    //  1. Load and apply VxVOLL register.
    leftVolume = registers[size_t(Register::VxVOLL)];

    //  2. If a new group of BRR samples is required, load the second BRR byte and
    //  decode the group of 4 BRR samples. This is definitely not done when not
    //  necessary. If necessary, adjust the BRR pointer to the next block, or
    //  flag the loop address for loading next step S2 and set ENDX.x in step S7.
    //  Note that this setting of ENDX.x will not override the clearing due to KON
    //  in step S3c, if both occur during the same sample.
    if (sampleStage == SampleStage::FirstBRRGroup || sampleStage == SampleStage::SecondBRRGroup || sampleStage == SampleStage::ThirdBRRGroup)
    {
        sampleSource[1] = processor.spcMemory.readByte(nextSampleAddress + 1);
        decodeSampleSource();
    }
    // TODO

    //  3. Increment interpolation sample position as specified by pitch values.
    //  At any point from now until we next get to S3c, the next sample may be
    //  calculated using the interpolation position and BRR buffer contents.
    if (sampleStage == SampleStage::Playing)
    {
        interpolationIndex += pitch;
        if (interpolationIndex > 0x7fff)
        {
            interpolationIndex = 0x7fff;
        }
        if (interpolationIndex >= 0x4000)
        {
            sampleSource[1] = processor.spcMemory.readByte(nextSampleAddress + 1);
            decodeSampleSource();

            interpolationIndex -= 0x4000;
        }
        nextSample = sampleBuffer[interpolationIndex >> 12];
        nextSample = Types::signedClamp<16, int16_t>(int(nextSample) * int(envelope) >> 11);

        int16_t leftSample = applyVolume(leftVolume);
        processor.leftSampleSum += leftSample;
    }
    else if(sampleStage != SampleStage::Inactive)
    {
        sampleStage = SampleStage(int(sampleStage) + 1);
    }

}

//  S5.
template<>
void Processor::Voice::doStep<5>()
{
    //  1. Load and apply VxVOLR register.
    rightVolume = registers[size_t(Register::VxVOLR)];
    if (sampleStage == SampleStage::Playing)
    {
        int16_t rightSample = applyVolume(rightVolume);
        processor.leftSampleSum += rightSample;
    }

    //  2. The new ENDX.x value is prepared, and can be overwritten. Reads will not
    //  see it yet.
    // TODO

}

//  S6.
template<>
void Processor::Voice::doStep<6>()
{
    //  1. The new VxOUTX value is prepared, and can be overwritten. Reads will not
    //  see it yet.
    // TODO

}

//  S7.
template<>
void Processor::Voice::doStep<7>()
{
    //  1. The new ENDX.x value may now be read.
    // TODO

    //  2. The new VxENVX value is prepared, and can be overwritten.Reads will not
    //  see it yet.
    // TODO

}

//  S8.
template<>
void Processor::Voice::doStep<8>()
{
    //  1. The new VxOUTX value may now be read.
    // TODO

}

//  S9.
template<>
void Processor::Voice::doStep<9>()
{
    //  1. The new VxENVX value may now be read.
    // TODO


}

void Processor::tickTimers(bool tickAllTimers)
{
    for (int i = 0; i < 3; ++i)
    {
        if (timers[i].enabled && (timers[i].highPrecision || tickAllTimers))
        {
            ++timers[i].tick;
            if (timers[i].tick == timers[i].target)
            {
                timers[i].tick = 0;
                timers[i].counter = (timers[i].counter + 1) & 0xf;
            }
        }
    }
}

//  0.
template<>
void Processor::onSampleCycle<0>()
{
    //  1. Voice steps : V0:S5  V1 : S2
    //doSteps({ 0, 5 }, { 1, 2 });
    voices[0].doStep<5>();
    voices[1].doStep<2>();

    //  2. Tick the SPC700 Stage 1 timers, always for T2 and every 4 samples for
    //  T0 and T1.
    tickTimers((sampleCount & 3) == 0);

    ++dspCycle;
    ++targetTickCounter;
}

//  1.
template<>
void Processor::onSampleCycle<1>()
{
    //  1. Voice steps : V0:S6  V1 : S3
    voices[0].doStep<6>();
    voices[1].doStep<3>();
}

//  2.
template<>
void Processor::onSampleCycle<2>()
{
    //  1. Voice steps : V0:S7  V1 : S4         V3 : S1
    voices[0].doStep<7>();
    voices[1].doStep<4>();
    voices[3].doStep<1>();
}

//  3.
template<>
void Processor::onSampleCycle<3>()
{
    //  1. Voice steps : V0:S8  V1 : S5  V2 : S2
    voices[0].doStep<8>();
    voices[1].doStep<5>();
    voices[2].doStep<2>();
}

//  4.
template<>
void Processor::onSampleCycle<4>()
{
    //  1. Voice steps : V0:S9  V1 : S6  V2 : S3
    voices[0].doStep<9>();
    voices[1].doStep<6>();
    voices[2].doStep<3>();
}

//  5.
template<>
void Processor::onSampleCycle<5>()
{
    //  1. Voice steps : V1:S7  V2 : S4         V4 : S1
    voices[1].doStep<7>();
    voices[2].doStep<4>();
    voices[4].doStep<1>();
}

//  6.
template<>
void Processor::onSampleCycle<6>()
{
    //  1. Voice steps : V1:S8  V2 : S5  V3 : S2
    voices[1].doStep<8>();
    voices[2].doStep<5>();
    voices[3].doStep<2>();
}

//  7.
template<>
void Processor::onSampleCycle<7>()
{
    //  1. Voice steps : V1:S9  V2 : S6  V3 : S3
    voices[1].doStep<9>();
    voices[2].doStep<6>();
    voices[3].doStep<3>();
}

//  8.
template<>
void Processor::onSampleCycle<8>()
{
    //  1. Voice steps : V2:S7  V3 : S4         V5 : S1
    voices[2].doStep<7>();
    voices[3].doStep<4>();
    voices[5].doStep<1>();
}

//  9.
template<>
void Processor::onSampleCycle<9>()
{
    //  1. Voice steps : V2:S8  V3 : S5  V4 : S2
    voices[2].doStep<8>();
    voices[3].doStep<5>();
    voices[4].doStep<2>();
}

//  10.
template<>
void Processor::onSampleCycle<10>()
{
    //  1. Voice steps : V2:S9  V3 : S6  V4 : S3
    voices[2].doStep<9>();
    voices[3].doStep<6>();
    voices[4].doStep<3>();
}

//  11.
template<>
void Processor::onSampleCycle<11>()
{
    //  1. Voice steps : V3:S7  V4 : S4         V6 : S1
    voices[3].doStep<7>();
    voices[4].doStep<4>();
    voices[6].doStep<1>();
}

//  12.
template<>
void Processor::onSampleCycle<12>()
{
    //  1. Voice steps : V3:S8  V4 : S5  V5 : S2
    voices[3].doStep<8>();
    voices[4].doStep<5>();
    voices[5].doStep<2>();
}

//  13.
template<>
void Processor::onSampleCycle<13>()
{
    //  1. Voice steps : V3:S9  V4 : S6  V5 : S3
    voices[3].doStep<9>();
    voices[4].doStep<6>();
    voices[5].doStep<3>();
}

//  14.
template<>
void Processor::onSampleCycle<14>()
{
    //  1. Voice steps : V4:S7  V5 : S4         V7 : S1
    voices[4].doStep<7>();
    voices[5].doStep<4>();
    voices[7].doStep<1>();
}

//  15.
template<>
void Processor::onSampleCycle<15>()
{
    //  1. Voice steps : V4:S8  V5 : S5  V6 : S2
    voices[4].doStep<8>();
    voices[5].doStep<5>();
    voices[6].doStep<2>();
}

//  16.
template<>
void Processor::onSampleCycle<16>()
{
    //  1. Voice steps : V4:S9  V5 : S6  V6 : S3
    voices[4].doStep<9>();
    voices[5].doStep<6>();
    voices[6].doStep<3>();

    //  2. Tick the SPC700 Stage 1 timer for T2.
    tickTimers(false);
}

//  17.
template<>
void Processor::onSampleCycle<17>()
{
    //  1. Voice steps : V0:S1                              V5 : S7  V6 : S4
    voices[0].doStep<1>();
    voices[5].doStep<7>();
    voices[6].doStep<4>();
}

//  18.
template<>
void Processor::onSampleCycle<18>()
{
    //  1. Voice steps : V5:S8  V6 : S5  V7 : S2
    voices[5].doStep<8>();
    voices[6].doStep<5>();
    voices[7].doStep<2>();
}

//  19.
template<>
void Processor::onSampleCycle<19>()
{
    //  1. Voice steps : V5:S9  V6 : S6  V7 : S3
    voices[5].doStep<9>();
    voices[6].doStep<6>();
    voices[7].doStep<3>();
}

//  20.
template<>
void Processor::onSampleCycle<20>()
{
    //  1. Voice steps : V1:S1                              V6 : S7  V7 : S4
    voices[1].doStep<1>();
    voices[6].doStep<7>();
    voices[7].doStep<4>();
}

//  21.
template<>
void Processor::onSampleCycle<21>()
{
    //  1. Voice steps : V0:S2                                     V6 : S8  V7 : S5
    voices[0].doStep<2>();
    voices[6].doStep<8>();
    voices[7].doStep<5>();
}

//  22.
template<>
void Processor::onSampleCycle<22>()
{
    //  1. Voice steps : V0:S3a                                    V6 : S9  V7 : S6
    voices[0].doStep3a();
    voices[6].doStep<9>();
    voices[7].doStep<6>();

    //  2. Apply ESA using the previously loaded value along with the previously
    //  calculated echo offset to calculate new echo pointer.
    // TODO
    
    //  3. Load left channel sample from the echo buffer.
    // TODO
    
    //  4. Load FFC0.
    // TODO
    
}

//  23.
template<>
void Processor::onSampleCycle<23>()
{
    //  1. Voice steps : V7:S7
    voices[7].doStep<7>();

    //  2. Load right channel sample from the echo buffer.
    // TODO
    
    //  3. Load FFC1 and FFC2.
    // TODO
    
}

//  24.
template<>
void Processor::onSampleCycle<24>()
{
    //  1. Voice steps : V7:S8
    voices[7].doStep<8>();

    //  2. Load FFC3, FFC4, and FFC5.
    // TODO
}

//  25.
template<>
void Processor::onSampleCycle<25>()
{
    //  1. Voice steps : V0:S3b                                           V7 : S9
    voices[0].doStep3b();
    voices[7].doStep<9>();

    //  2. Load FFC6 and FFC7.
    // TODO
}

float applyMainVolume(int32_t& sample, int32_t mainVolume)
{
    sample = Types::signedClamp<16, int32_t>(sample * mainVolume >> 7);
    float output = float(sample) / float(sample < 0 ? 0x8000 : 0x7fff);
    sample = 0;
    return output;
}

//  26.
template<>
void Processor::onSampleCycle<26>()
{
    //  1. Load and apply MVOLL.
    mainVolumeLeft = registers[size_t(Register::MVOLL)];

    //  2. Load and apply EVOLL.
    echoVolumeLeft = registers[size_t(Register::EVOLL)];
    // TODO

    //  3. Output the left sample to the DAC.
    const float leftOutput = applyMainVolume(leftSampleSum, mainVolumeLeft);
    {
        std::lock_guard outputBufferLock(outputBufferMutex);

        const size_t outputIndex = leftOutputCount & (outputBufferSize - 1);
        leftOutputBuffer[outputIndex] = leftOutput;
        ++leftOutputCount;
    }

    //  4. Load and apply EFB.
    // TODO
    
}

//  27.
template<>
void Processor::onSampleCycle<27>()
{
    //  1. Load and apply MVOLR.
    mainVolumeRight = registers[size_t(Register::MVOLR)];

    //  2. Load and apply EVOLR.
    echoVolumeRight = registers[size_t(Register::EVOLR)];
    // TODO

    //  3. Output the right sample to the DAC.
    const float rightOutput = applyMainVolume(rightSampleSum, mainVolumeRight);
    {
        std::lock_guard outputBufferLock(outputBufferMutex);

        const size_t outputIndex = rightOutputCount & (outputBufferSize - 1);
        rightOutputBuffer[outputIndex] = rightOutput;
        ++rightOutputCount;
    }

    //  4. Load PMON
    setVoiceBits<&Processor::Voice::pitchModulation>(registers[size_t(Register::PMON)]);
}

//  28.
template<>
void Processor::onSampleCycle<28>()
{
    //  1. Load NON, EON, and DIR.
    sourceDirectory = registers[size_t(Register::DIR)];
    // TODO

    //  2. Load FLG bit 5 (ECENx) for application to the left channel.
    // TODO
}

//  29.
template<>
void Processor::onSampleCycle<29>()
{
    //  1. Update global counter.
    // TODO

    //  2. Write left channel sample to the echo buffer, if allowed by ECENx.
    // TODO

    //  3. Load EDL - if the current echo offset is 0, apply EDL.
    // TODO

    //  4. Load ESA for future use.
    // TODO

    //  5. Load FLG bit 5 (ECENx)again for application to the right channel.
    // TODO

    if ((sampleCount & 1) == 1)
    {
        //  6. ** Clear internal KON bits for any channels keyed on in the previous 2 samples.
        setVoiceBits<&Voice::keyOnInternal>(0);
    }
}

//  30.
template<>
void Processor::onSampleCycle<30>()
{
    if ((sampleCount & 1) == 1)
    {
        //  5. ** Load KOFF and internal KON.
        // Note: this presumably has to be done before voice step 3c, despite anomie's ordering
        Byte externalKeyOn = registers[size_t(Register::KON)];
        for (int i = 0; i < voices.size(); ++i)
        {
            bool oldKeyOn = voices[i].keyOn;
            voices[i].keyOn = externalKeyOn.getBit(i);
            if (voices[i].keyOn && !oldKeyOn)
            {
                voices[i].keyOnInternal = true;
            }
        }

        setVoiceBits<&Voice::keyOff>(registers[size_t(Register::KOFF)]);
    }

    //  1. Voice steps : V0:S3c
    voices[0].doStep3c();

    //  2. Write right channel sample to the echo buffer, if allowed by ECENx.
    // TODO

    //  3. Increment the echo offset, and set to 0 if it exceeds the buffer length.
    // TODO

    //  4. Load FLG bits 0 - 4 and update noise sample if necessary.
    // TODO

    leftSampleSum = 0;
    rightSampleSum = 0;
}

//  31.
template<>
void Processor::onSampleCycle<31>()
{
    //  1. Voice steps : V0:S4         V2 : S1
    voices[0].doStep<4>();
    voices[2].doStep<1>();
}

template<int... Indices>
static constexpr Processor::SampleCycleTable defineSampleCycles(std::integer_sequence<int, Indices...>)
{
    return { ([](Processor& processor) { processor.onSampleCycle<Indices>(); })... };
}

static constexpr Processor::SampleCycleTable createSampleCycleTable()
{
    return defineSampleCycles(std::make_integer_sequence<int, 32>{});
}

void Processor::tick()
{
    PROFILE_SCOPE("Audio-Processor Tick");

    try
    {
        sampleCycleTable[sampleCycle](*this);
    }
    catch (const std::exception& e)
    {
        output.error("Exception in sample cycle ", sampleCycle);
        output.error(e.what());
        throw RuntimeError();
    }


    if (++sampleCycle == 32)
    {
        sampleCycle = 0;
        ++sampleCount;
    }

    /*if ((spcCycle & 15) == 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (timers[i].enabled && (timers[i].highPrecision || (spcCycle & 127) == 0))
            {
                ++timers[i].tick;
                if (timers[i].tick == timers[i].target)
                {
                    timers[i].tick = 0;
                    timers[i].counter = (timers[i].counter + 1) & 0xf;
                }
            }
        }
    }
	++spcCycle;*/
}

void Processor::printTimeInfo(double currentTime)
{
    if (previousTimeInfoTime == 0.0)
    {
        previousTimeInfoTime = currentTime;
    }
    timeInfoTickCounter++;
    double elapsedTime = currentTime - previousTimeInfoTime;
    if (elapsedTime >= 10.0)
    {
        output.debug("Audio ticks: ", targetTickCounter / elapsedTime, " / ", timeInfoTickCounter / elapsedTime, "(", 100.0 * targetTickCounter / timeInfoTickCounter, "%)");
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

void Processor::printDebuggerInfo(Output& out, Output::Lock& lock) const
{
    out.printLine(lock, "Main Vol    Echo Vol    Key On    Key Off   R M E Gen Src End   Echo FB   Pitch Mod Noise On  Echo On   Dir ER  Delay");
    out.printLine(lock, std::left, std::setfill(' '), std::setw(4), +mainVolumeLeft,
        "  ", std::setw(4), +mainVolumeRight,
        "  ", std::setw(4), +echoVolumeLeft,
        "  ", std::setw(4), +echoVolumeRight,
        "  ", getVoiceBits<&Voice::keyOn>(),
        "  ", getVoiceBits<&Voice::keyOff>(),
        "  ", reset,
        " ", mute,
        " ", echoOff,
        " ", noiseGeneratorClock,
        "  ", getVoiceBits<&Voice::sourceEndBlock>(),
        "  ", std::setw(8), +echoFeedback,
        "  ", getVoiceBits<&Voice::pitchModulation>(),
        "  ", getVoiceBits<&Voice::noiseOn>(),
        "  ", getVoiceBits<&Voice::echoOn>(),
        "  ", sourceDirectory,
        "  ", echoRegionOffset,
        "  ", echoDelay);


    out.print(lock, "Filter coefficients:");
    for (int i = 0; i < voiceCount; ++i)
    {
        out.print(lock, "  ", voices[i].coefficient);
    }
    out.printLine(lock);

    out.printLine(lock, "   Vol L       Vol R       Pitch       Src  Type AR DR SR SL     Gain Mode               Lvl Envelope    Output");
    for (int i = 0; i < voices.size(); ++i)
    {
        const Voice& voice = voices[i];
        out.printLine(lock, i, ": ",
            std::left, std::setfill(' '), std::setw(10), +voice.leftVolume,
            "  ", std::setw(10), +voice.rightVolume,
            "  ", std::left, std::setfill(' '), std::setw(10), voice.pitch, "",
            "  ", voice.sourceNumber,
            "   ", voice.envelopeTypeToString(),
            " ", voice.attackRate,
            " ", voice.decayRate,
            " ", voice.sustainRate,
            " ", std::left, std::setfill(' '), std::setw(5), voice.sustainLevel,
            "  ", std::left, std::setfill(' '), std::setw(22), voice.gainModeToString(),
            "  ", voice.gainLevel,
            "  ", std::left, std::setfill(' '), std::setw(10), voice.envelope,
            "  ", std::left, std::setfill(' '), std::setw(10), voice.output);
    }
}

}
