#include "AudioSystem.h"

#include <iostream>
#include <chrono>

class AudioSystemRunner
{
public:
    AudioSystemRunner(AudioSystem& system)
        : system(system)
    {
    }

    void operator()()
    {
        try {
            uint64_t iteration = 0;
            //uint64_t masterCycle = 0;
            //uint64_t nextSpc = 0;
            system.output << "HELLO AUDIO MONKEY!" << std::endl;
            system.processor.startRenderer();
            std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
            using Frequency = std::ratio<1, 1024000>;
            using CycleCount = std::chrono::duration<uint64_t, Frequency>;
            CycleCount oneCycle(1);
            CycleCount masterCycle(0);
            CycleCount nextSpc(0);
            //double startTime = system.processor.renderer.getStreamTime();
            while (system.run) {
                if (masterCycle == nextSpc) {
                    Instruction* instruction = system.instructionDecoder.getNextInstruction(system.state);
                    system.context.nextInstruction = instruction;

                    //instruction->applyBreakpoints();

                    //system.context.addKnownAddress(system.state.getProgramAddress());

                    if (int cycles = instruction->execute()) {
                        nextSpc += CycleCount(cycles);
                        system.context.nextInstruction = system.instructionDecoder.getNextInstruction(system.state);
                    } else {
                        continue;
                    }
                }
                constexpr double speed = 1.024e6;
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                std::chrono::nanoseconds elapsedTime = now - startTime;
                CycleCount nextCycle = masterCycle + oneCycle;
                if (nextCycle <= elapsedTime)
                {
                    masterCycle = nextCycle;
                    system.registers.tick();
                }
                else {
                    //std::chrono::steady_clock::time_point nextCycleTime = startTime + 
                    std::this_thread::yield();
                    //std::this_thread::sleep_until(startTime + nextCycle);
                }
                ++iteration;
                static std::chrono::steady_clock::time_point lastTime = startTime;
                if (now - lastTime > std::chrono::seconds(1)) {
                    uint64_t masterCycleCount = std::chrono::duration_cast<CycleCount>(masterCycle).count();
                    system.output << "Audio cycles: " << masterCycleCount << " / " << iteration << " (" << (100.0 * masterCycleCount / iteration) << "%)" << std::endl;
                    lastTime = now;
                }
            }
            system.output << "BYE AUDIO MONKEY! " << std::endl;
        } catch (const std::exception& e) {
            system.error << "AudioSystem thread: Caught std::exception: " << e.what() << std::endl;
            std::getchar();
        }
    }

private:
    AudioSystem& system;
};

void AudioSystem::start()
{
    systemThread = std::thread(AudioSystemRunner(*this));
}