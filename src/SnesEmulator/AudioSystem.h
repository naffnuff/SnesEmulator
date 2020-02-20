#pragma once

#include <iostream>
#include <array>

#include "Common/System.h"

#include "SPC700/SpcState.h"
#include "SPC700/SpcInstructionDecoder.h"

#include "Debugger.h"

#include "AudioRegisters.h"
#include "AudioProcessor.h"

class AudioSystem
{
public:
    AudioSystem(std::ostream& output, std::ostream& error, Debugger& debugger)
        : output(output)
        , error(error)
        , instructionDecoder(state)
        , registers(output, error, state)
        , processor(registers.processor)
        , debugger(debugger)
        , context("spc.txt", System::Magenta, debugger)
    {
    }

    ~AudioSystem()
    {
        run = false;
        systemThread.join();
    }

    AudioSystem(const AudioSystem&) = delete;
    AudioSystem& operator=(const AudioSystem&) = delete;

    Audio::Registers& getRegisters()
    {
        return registers;
    }

    const Audio::Processor& getProcessor() const
    {
        return processor;
    }

    void initialize(std::array<Byte, 4>& cpuToSpcBuffers, std::array<Byte, 4>& spcToCpuBuffers)
    {
        SPC::State::MemoryType& memory = state.getMemory();

        // I/O between the CPU and SPC700
        for (Word i = 0; i < 4; ++i) {
            memory.createLocation<ReadWriteRegister>(Word(0xf4 + i),
                [this, i, &cpuToSpcBuffers](Byte& value) {
                    value = cpuToSpcBuffers[i];
                },
                [this, i, &spcToCpuBuffers](Byte, Byte newValue) {
                    spcToCpuBuffers[i] = newValue;
                }
            );
        }

        registers.initialize(cpuToSpcBuffers);
        memory.finalize();

        debugger.loadBreakpoints(context, state);

        context.nextInstruction = instructionDecoder.getNextInstruction(state);
    }

    void tick()
    {
        if (debugger.isPaused()) {
            registers.tick();
        }
    }

    void reset()
    {
        registers.reset();
    }

    void start();

private:
    std::ostream& output;
    std::ostream& error;

    bool run = true;

public:
    SPC::State state;
    SPC::InstructionDecoder instructionDecoder;

private:
    Audio::Registers registers;
    Audio::Processor& processor;

    Debugger& debugger;

    std::thread systemThread;

public:
    Debugger::Context<SPC::State> context;

    bool pauseRequested = false;

    friend class AudioSystemRunner;
};
