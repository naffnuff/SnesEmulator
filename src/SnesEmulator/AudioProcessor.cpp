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

Processor::FrequencyCounter::FrequencyTable Processor::FrequencyCounter::frequencyTable = Processor::FrequencyCounter::getFrequencyTable();

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
    timers[2].highPrecision = true;
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

int hoy = 0;

void Processor::outputNextSample(float& leftChannel, float& rightChannel)
{
    int32_t leftSampleSum = 0;
    int32_t rightSampleSum = 0;
    int16_t nextSample = 0;
    int i = 0;
    for (Audio::Processor::Voice& voice : voices)
	{
        ++i;


        try
        {
            //Audio::Processor::Voice& voice = voices[0];

            voice.calculateNextSample(nextSample);
            int16_t leftSample = voice.applyLeftVolume(nextSample);
            int16_t rightSample = voice.applyRightVolume(nextSample);
            leftSampleSum = Types::signedClamp<16, int32_t>(leftSampleSum + leftSample);
            rightSampleSum = Types::signedClamp<16, int32_t>(rightSampleSum + rightSample);
        }
        catch (const std::runtime_error&)
        {
            output.debug("Exception in voice ", i);
        }
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
}

int16_t Processor::Voice::applyLeftVolume(int16_t nextSample)
{
    return Types::signedClamp<16, int16_t>(nextSample * leftVolume >> 7);
}

int16_t Processor::Voice::applyRightVolume(int16_t nextSample)
{
    return Types::signedClamp<16, int16_t>(nextSample * rightVolume >> 7);
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
        std::cout << "Exception while reading header address, loopAddress=" << loopAddress << std::endl;
        throw e;
    }

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
            //sampleBuffer[bufferIndex++] = Types::clip<15, int16_t>(expandedSample); WTF?
            sampleBuffer[bufferIndex++] = Types::clip<16, int16_t>(expandedSample);
        }
    }
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
        }
    }
}

//  S1.Load VxSRCN register, if necessary.
template<>
void Processor::Voice::doStep<1>()
{
}

//  S2.Load the sample pointer(using previously loaded DIR and VxSRCN) if
//  necessary.
//  Load VxPITCHL register.
//  Load VxADSR1 register.
template<>
void Processor::Voice::doStep<2>()
{
}

//  S3.a.Load VxPITCHH register.
//  Apply pitch modulation if applicable.
void Processor::Voice::doStep3a()
{
}

//  b.Load the BRR header byte(every time), and the first of the two BRR
//  bytes that will be decoded.
void Processor::Voice::doStep3b()
{
}

//  c.If applicable, replace the current sample with the noise sample.
//  Apply the volume envelope.
//  - This is the value used for modulating the next voice's pitch, if
//  applicable.
//  Check FLG bit 7 (NOT previously loaded).
//  Check BRR header 'e' and 'l' bits to determine if the voice ends.
//  Handle KOFF and KON using previously loaded values.If KON, ENDX.x will
//  be cleared in step S7.
//  Load VxGAIN or VxADSR2 register depending on ADSR1.7.
//  Update the volume envelope, using previously loaded values.
void Processor::Voice::doStep3c()
{
}

template<>
void Processor::Voice::doStep<3>()
{
    doStep3a();
    doStep3b();
    doStep3c();
}

//  S4.Load and apply VxVOLL register.
//  If a new group of BRR samples is required, load the second BRR byte and
//  decode the group of 4 BRR samples.This is definitely not done when not
//  necessary.If necessary, adjust the BRR pointer to the next block, or
//  flag the loop address for loading next step S2 and set ENDX.x in step S7.
//  Note that this setting of ENDX.x will not override the clearing due to KON
//  in step S3c, if both occur during the same sample.
//  Increment interpolation sample position as specified by pitch values.
//  At any point from now until we next get to S3c, the next sample may be
//  calculated using the interpolation position and BRR buffer contents.
template<>
void Processor::Voice::doStep<4>()
{
}

//  S5.Load and apply VxVOLR register.
//  The new ENDX.x value is prepared, and can be overwritten.Reads will not
//  see it yet.
template<>
void Processor::Voice::doStep<5>()
{
}

//  S6.The new VxOUTX value is prepared, and can be overwritten.Reads will not
//  see it yet.
template<>
void Processor::Voice::doStep<6>()
{
}

//  S7.The new ENDX.x value may now be read.
//  The new VxENVX value is prepared, and can be overwritten.Reads will not
//  see it yet.
template<>
void Processor::Voice::doStep<7>()
{
}

//  S8.The new VxOUTX value may now be read.
template<>
void Processor::Voice::doStep<8>()
{
}

//  S9.The new VxENVX value may now be read.
template<>
void Processor::Voice::doStep<9>()
{
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
                timers[i].counter = (timers[i].counter + 1) % 0x10;
            }
        }
    }
}

//    0. Voice steps : V0:S5  V1 : S2
//    Tick the SPC700 Stage 1 timers, always for T2 and every 4 samples for
//    T0 and T1.
template<>
void Processor::onSampleCycle<0>()
{
    voices[0].doStep<5>();
    voices[1].doStep<2>();

    tickTimers(spcCycle % 128 == 0);

    ++dspCycle;
    ++targetTickCounter;
}

//    1. Voice steps : V0:S6  V1 : S3
template<>
void Processor::onSampleCycle<1>()
{
    voices[0].doStep<6>();
    voices[1].doStep<3>();
}

//    2. Voice steps : V0:S7  V1 : S4         V3 : S1
template<>
void Processor::onSampleCycle<2>()
{
    voices[0].doStep<7>();
    voices[1].doStep<4>();
    voices[3].doStep<1>();
}

//    3. Voice steps : V0:S8  V1 : S5  V2 : S2
template<>
void Processor::onSampleCycle<3>()
{
    voices[0].doStep<8>();
    voices[1].doStep<5>();
    voices[2].doStep<2>();
}

//    4. Voice steps : V0:S9  V1 : S6  V2 : S3
template<>
void Processor::onSampleCycle<4>()
{
    voices[0].doStep<9>();
    voices[1].doStep<6>();
    voices[2].doStep<3>();
}

//    5. Voice steps : V1:S7  V2 : S4         V4 : S1
template<>
void Processor::onSampleCycle<5>()
{
    voices[1].doStep<7>();
    voices[2].doStep<4>();
    voices[4].doStep<1>();
}

//    6. Voice steps : V1:S8  V2 : S5  V3 : S2
template<>
void Processor::onSampleCycle<6>()
{
    voices[1].doStep<8>();
    voices[2].doStep<5>();
    voices[3].doStep<2>();
}

//    7. Voice steps : V1:S9  V2 : S6  V3 : S3
template<>
void Processor::onSampleCycle<7>()
{
    voices[1].doStep<9>();
    voices[2].doStep<6>();
    voices[3].doStep<3>();
}

//    8. Voice steps : V2:S7  V3 : S4         V5 : S1
template<>
void Processor::onSampleCycle<8>()
{
    voices[2].doStep<7>();
    voices[3].doStep<4>();
    voices[5].doStep<1>();
}

//    9. Voice steps : V2:S8  V3 : S5  V4 : S2
template<>
void Processor::onSampleCycle<9>()
{
    voices[2].doStep<8>();
    voices[3].doStep<5>();
    voices[4].doStep<2>();
}

//    10. Voice steps : V2:S9  V3 : S6  V4 : S3
template<>
void Processor::onSampleCycle<10>()
{
    voices[2].doStep<9>();
    voices[3].doStep<6>();
    voices[4].doStep<3>();
}

//    11. Voice steps : V3:S7  V4 : S4         V6 : S1
template<>
void Processor::onSampleCycle<11>()
{
    voices[3].doStep<7>();
    voices[4].doStep<4>();
    voices[6].doStep<1>();
}

//    12. Voice steps : V3:S8  V4 : S5  V5 : S2
template<>
void Processor::onSampleCycle<12>()
{
    voices[3].doStep<8>();
    voices[4].doStep<5>();
    voices[5].doStep<2>();
}

//    13. Voice steps : V3:S9  V4 : S6  V5 : S3
template<>
void Processor::onSampleCycle<13>()
{
    voices[3].doStep<9>();
    voices[4].doStep<6>();
    voices[5].doStep<3>();
}

//    14. Voice steps : V4:S7  V5 : S4         V7 : S1
template<>
void Processor::onSampleCycle<14>()
{
    voices[4].doStep<7>();
    voices[5].doStep<4>();
    voices[7].doStep<1>();
}

//    15. Voice steps : V4:S8  V5 : S5  V6 : S2
template<>
void Processor::onSampleCycle<15>()
{
    voices[4].doStep<8>();
    voices[5].doStep<5>();
    voices[6].doStep<2>();
}

//    16. Voice steps : V4:S9  V5 : S6  V6 : S3
//    Tick the SPC700 Stage 1 timer for T2.
template<>
void Processor::onSampleCycle<16>()
{
    voices[4].doStep<9>();
    voices[5].doStep<6>();
    voices[6].doStep<3>();

    tickTimers(false);
}

//    17. Voice steps : V0:S1                              V5 : S7  V6 : S4
template<>
void Processor::onSampleCycle<17>()
{
    voices[0].doStep<1>();
    voices[5].doStep<7>();
    voices[6].doStep<4>();
}

//    18. Voice steps : V5:S8  V6 : S5  V7 : S2
template<>
void Processor::onSampleCycle<18>()
{
    voices[5].doStep<8>();
    voices[6].doStep<5>();
    voices[7].doStep<2>();
}

//    19. Voice steps : V5:S9  V6 : S6  V7 : S3
template<>
void Processor::onSampleCycle<19>()
{
    voices[5].doStep<9>();
    voices[6].doStep<6>();
    voices[7].doStep<3>();
}

//    20. Voice steps : V1:S1                              V6 : S7  V7 : S4
template<>
void Processor::onSampleCycle<20>()
{
    voices[1].doStep<1>();
    voices[6].doStep<7>();
    voices[7].doStep<4>();
}

//    21. Voice steps : V0:S2                                     V6 : S8  V7 : S5
template<>
void Processor::onSampleCycle<21>()
{
    voices[0].doStep<2>();
    voices[6].doStep<8>();
    voices[7].doStep<5>();
}

//    22. Voice steps : V0:S3a                                    V6 : S9  V7 : S6
//    Apply ESA using the previously loaded value along with the previously
//    calculated echo offset to calculate new echo pointer.
//    Load left channel sample from the echo buffer.
//    Load FFC0.
template<>
void Processor::onSampleCycle<22>()
{
    voices[0].doStep3a();
    voices[6].doStep<9>();
    voices[7].doStep<6>();

    //    Apply ESA using the previously loaded value along with the previously
    //    calculated echo offset to calculate new echo pointer.
    //    Load left channel sample from the echo buffer.
    //    Load FFC0.
}

//    23. Voice steps : V7:S7
//    Load right channel sample from the echo buffer.
//    Load FFC1 and FFC2.
template<>
void Processor::onSampleCycle<23>()
{
    voices[7].doStep<7>();

    //    Load right channel sample from the echo buffer.
    //    Load FFC1 and FFC2.
}

//    24. Voice steps : V7:S8
//    Load FFC3, FFC4, and FFC5.
template<>
void Processor::onSampleCycle<24>()
{
    voices[7].doStep<8>();

    //    Load FFC3, FFC4, and FFC5.
}

//    25. Voice steps : V0:S3b                                           V7 : S9
//    Load FFC6 and FFC7.
template<>
void Processor::onSampleCycle<25>()
{
    voices[0].doStep3b();
    voices[7].doStep<9>();

    //    Load FFC6 and FFC7.
}

//    26. Load and apply MVOLL.
//    Load and apply EVOLL.
//    Output the left sample to the DAC.
//    Load and apply EFB.
template<>
void Processor::onSampleCycle<26>()
{
    //    26. Load and apply MVOLL.
    //    Load and apply EVOLL.
    //    Output the left sample to the DAC.
    //    Load and apply EFB.
}

//    27. Load and apply MVOLR.
//    Load and apply EVOLR.
//    Output the right sample to the DAC.
//    Load PMON
template<>
void Processor::onSampleCycle<27>()
{
    //    27. Load and apply MVOLR.
    //    Load and apply EVOLR.
    //    Output the right sample to the DAC.
    //    Load PMON
}

//    28. Load NON, EON, and DIR.
//    Load FLG bit 5 (ECENx) for application to the left channel.
template<>
void Processor::onSampleCycle<28>()
{
    //    28. Load NON, EON, and DIR.
    //    Load FLG bit 5 (ECENx) for application to the left channel.
}

//    29. Update global counter.
//    Write left channel sample to the echo buffer, if allowed by ECENx.
//    Load EDL - if the current echo offset is 0, apply EDL.
//    Load ESA for future use.
//    Load FLG bit 5 (ECENx)again for application to the right channel.
//    ** Clear internal KON bits for any channels keyed on in the previous 2 samples.
template<>
void Processor::onSampleCycle<29>()
{
    //    29. Update global counter.
    //    Write left channel sample to the echo buffer, if allowed by ECENx.
    //    Load EDL - if the current echo offset is 0, apply EDL.
    //    Load ESA for future use.
    //    Load FLG bit 5 (ECENx)again for application to the right channel.
    //    ** Clear internal KON bits for any channels keyed on in the previous 2 samples.
}

//    30. Voice steps : V0:S3c
//    Write right channel sample to the echo buffer, if allowed by ECENx.
//    Increment the echo offset, and set to 0 if it exceeds the buffer length.
//    Load FLG bits 0 - 4 and update noise sample if necessary.
//    ** Load KOFF and internal KON.
template<>
void Processor::onSampleCycle<30>()
{
    voices[0].doStep3c();
    //    Write right channel sample to the echo buffer, if allowed by ECENx.
    //    Increment the echo offset, and set to 0 if it exceeds the buffer length.
    //    Load FLG bits 0 - 4 and update noise sample if necessary.
    //    ** Load KOFF and internal KON.
}

//    31. Voice steps : V0:S4         V2 : S1
template<>
void Processor::onSampleCycle<31>()
{
    voices[0].doStep<4>();
    voices[2].doStep<1>();
}

template<int... Indices>
static constexpr Processor::SampleCycleTable makeSampleCycleTable(std::integer_sequence<int, Indices...>)
{
    return { ([](Processor& processor) { processor.onSampleCycle<Indices>(); })... };
}

static constexpr Processor::SampleCycleTable getSampleCycleTable()
{
    return makeSampleCycleTable(std::make_integer_sequence<int, 32>{});
}

Processor::SampleCycleTable Processor::sampleCycleTable = getSampleCycleTable();

void Processor::tick()
{
    int sampleCycle = spcCycle % 32;
    sampleCycleTable[sampleCycle](*this);
    ++spcCycle;
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
