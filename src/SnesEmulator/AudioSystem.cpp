#include "AudioSystem.h"

#include <iostream>

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
            uint64_t masterCycle = 0;
            uint64_t nextSpc = 0;
            system.output << "HELLO AUDIO MONKEY!" << std::endl;
            system.processor.startRenderer();
            double startTime = system.processor.renderer.getStreamTime();
            while (system.run) {
                if (masterCycle == nextSpc) {
                    Instruction* instruction = system.instructionDecoder.getNextInstruction(system.state);
                    system.context.nextInstruction = instruction;

                    //instruction->applyBreakpoints();

                    //system.context.addKnownAddress(system.state.getProgramAddress());

                    if (int cycles = instruction->execute()) {
                        nextSpc += uint64_t(cycles);
                        system.context.nextInstruction = system.instructionDecoder.getNextInstruction(system.state);
                    } else {
                        continue;
                    }
                }
                /*if (masterCycle >= system.processor.renderer.masterCycle) {
                    std::unique_lock<std::mutex> lock(system.processor.renderer.mutex);
                    system.processor.renderer.condition.wait(lock, [this, masterCycle]() { return masterCycle < system.processor.renderer.masterCycle; });
                }*/
                constexpr double speed = 1.024e6;
                double time = system.processor.renderer.getStreamTime() - startTime;
                /*static double lastTime = time;
                if (time - lastTime > 1.0) {
                    system.output << "Time: " << time << std::endl;
                    lastTime = time;
                }*/
                uint64_t targetMasterCycle = uint64_t(time * speed);
                if (masterCycle < targetMasterCycle)
                {
                    ++masterCycle;
                    system.registers.tick();
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