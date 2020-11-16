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
            system.output.debug("HELLO AUDIO SYSTEM!");
            system.now = std::chrono::steady_clock::now();
            std::chrono::steady_clock::time_point startTime = system.now;
            AudioSystem::CycleCount oneCycle(1);
            AudioSystem::CycleCount masterCycle(0);
            //double startTime = system.processor.renderer.getStreamTime();
            while (system.run) {
                system.processor.checkStreamErrors();

                if (masterCycle == system.nextSpc) {
                    Instruction* instruction = system.instructionDecoder.getNextInstruction(system.state);
                    system.context.nextInstruction = instruction;

                    instruction->applyBreakpoints();

                    system.context.addKnownAddress(system.state.getProgramAddress());

                    if (system.debugger.isPaused()) {
                        break;
                    }

                    if (int cycles = instruction->execute()) {
                        system.nextSpc += AudioSystem::CycleCount(cycles);
                        system.context.nextInstruction = system.instructionDecoder.getNextInstruction(system.state);
                    } else {
                        continue;
                    }

                    if (system.debugger.isPaused()) {
                        break;
                    }

                    if (system.registers.pauseRequested) {
                        break;
                    }
                }

                system.now = std::chrono::steady_clock::now();
                system.elapsedTime = system.now - startTime;
                AudioSystem::CycleCount nextCycle = masterCycle + oneCycle;
                if (nextCycle <= system.elapsedTime)
                {
                    masterCycle = nextCycle;
                    system.registers.tick();
                }
                else
                {
                    //std::chrono::steady_clock::time_point nextCycleTime = startTime + 
                    std::this_thread::yield();
                    //std::this_thread::sleep_until(startTime + nextCycle);
                }
                ++iteration;
                static std::chrono::steady_clock::time_point lastTime = startTime;
                if (system.now - lastTime > std::chrono::seconds(10)) {
                    system.output.debug("Audio cycles: ", masterCycle.count(), " / ", iteration, " (", (100.0 * masterCycle.count() / iteration), "%)");
                    lastTime = system.now;
                }
            }
            system.output.debug("BYE AUDIO MONKEY! ");
        } catch (const ::NotYetImplementedException& e) {
            system.output.error("AudioSystem thread: ", e.what());
            system.context.printAddressHistory(system.output);
            //std::getchar();
        } catch (const ::RuntimeError& e) {
            system.output.error("AudioSystem thread: ", e.what());
            system.context.printAddressHistory(system.output);
            //std::getchar();
        } catch (const ::AccessException& e) {
            system.output.error("AudioSystem thread: ", e.what());
            system.context.printAddressHistory(system.output);
            //std::getchar();
        }
        system.elapsedTime = std::chrono::nanoseconds(0);
        system.pauseRequested = true;
        system.threaded = false;
    }

private:
    AudioSystem& system;
};

void AudioSystem::start()
{
    processor.startStream();
    if (threaded) {
        systemThread = std::thread(AudioSystemRunner(*this));
        systemThreadStarted = true;
    }
}