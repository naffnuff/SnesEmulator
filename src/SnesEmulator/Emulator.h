#pragma once

#include <ctime>
#include <set>

#include "Common/Instruction.h"
#include "Common/System.h"

#include "WDC65816/CpuState.h"

#include "WDC65816/CpuInstructionDecoder.h"

#include "Rom.h"
#include "Debugger.h"

#include "VideoRenderer.h"
#include "VideoProcessor.h"
#include "VideoRegisters.h"

#include "AudioSystem.h"

class Emulator
{
private:
    struct SaveRamSaver {
        SaveRamSaver(Emulator& emulator)
            : saveRam(emulator.rom.romSize)
            , rom(emulator.rom)
        {
        }

        ~SaveRamSaver()
        {
        }

        void operator()()
        {
            while (run) {
                bool save = false;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    condition.wait(lock, [this]() { return saveRamModified || !run; });
                    save = saveRamModified;
                    saveRamModified = false;
                }
                if (save) {
                    std::ofstream file(rom.gameTitle + ".save");
                    for (int address = 0; address < rom.saveRamSize; ++address) {
                        file << saveRam[address] << ' ';
                    }
                    std::cout << "*";
                }
            }
        }

        bool run = true;
        bool saveRamModified = false;
        std::mutex mutex;
        std::condition_variable condition;
        const Rom& rom;
        std::vector<Byte> saveRam;
    };

public:
    Emulator(std::ostream& output, std::istream& input, std::ostream& error, const Rom& rom)
        : output(output)
        , input(input)
        , error(error)
        , rom(rom)
        , cpuState()
        , cpuInstructionDecoder(cpuState)
        , videoRegisters(output, error, cpuState)
        , videoProcessor(videoRegisters.processor)
        , audioSystem(output, error, debugger)
        , debugger(output, input, error, videoRegisters, audioSystem.getRegisters(), running)
        , cpuContext("cpu.txt", System::Green, debugger)
        , saveRamSaver(*this)
        , masterCycle(0)
    {
    }

    Emulator(const Emulator&) = delete;
    Emulator& operator=(const Emulator&) = delete;

    ~Emulator()
    {
        saveRamSaver.run = false;
        saveRamSaver.condition.notify_one();
        saveRamSaverThread.join();
    }

    void initialize();
    void run();

    std::string getRomTitle() const
    {
        return rom.gameTitle;
    }

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;

    const Rom& rom;

    CPU::State cpuState;
    CPU::InstructionDecoder cpuInstructionDecoder;

    Video::Registers videoRegisters;
    Video::Processor& videoProcessor;

    AudioSystem audioSystem;

    Debugger debugger;

    Debugger::Context<CPU::State> cpuContext;

    SaveRamSaver saveRamSaver;
    std::thread saveRamSaverThread;

    bool running = true;

    using Frequency = std::ratio<88, 1890000000>;
    using CycleCount = std::chrono::duration<uint64_t, Frequency>;
    CycleCount masterCycle;

    std::array<Byte, 4> cpuToSpcBuffers;
    std::array<Byte, 4> spcToCpuBuffers;
};

