#pragma once

#include <ctime>
#include <set>

#include "Common/Instruction.h"
#include "Common/System.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"

#include "WDC65816/CpuInstructionDecoder.h"
#include "SPC700/SpcInstructionDecoder.h"

#include "Rom.h"
#include "Debugger.h"

#include "VideoRenderer.h"
#include "VideoProcessor.h"
#include "VideoRegisters.h"

#include "AudioProcessor.h"

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
        , spcState()
        , cpuInstructionDecoder(cpuState)
        , spcInstructionDecoder(spcState)
        , videoRegisters(output, error, cpuState)
        , videoProcessor(videoRegisters.processor)
        , audioRegisters(output, error, spcState)
        , audioProcessor(audioRegisters.processor)
        , debugger(output, input, error, videoRegisters, audioRegisters, masterCycle, running)
        , cpuContext("cpu.txt", System::Green, debugger)
        , spcContext("spc.txt", System::Magenta, debugger)
        , saveRamSaver(*this)
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

    void pause()
    {
        cpuContext.setPaused(true);
    }

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;

    const Rom& rom;
    CPU::State cpuState;
    SPC::State spcState;
    CPU::InstructionDecoder cpuInstructionDecoder;
    SPC::InstructionDecoder spcInstructionDecoder;

    Video::Registers videoRegisters;
    Audio::Registers audioRegisters;

    Video::Processor& videoProcessor;
    Audio::Processor& audioProcessor;


    Debugger debugger;

    Debugger::Context<CPU::State> cpuContext;
    Debugger::Context<SPC::State> spcContext;

    SaveRamSaver saveRamSaver;
    std::thread saveRamSaverThread;

    bool running = true;
    uint64_t masterCycle = 186;

    std::array<Byte, 4> cpuToSpcBuffers;
    std::array<Byte, 4> spcToCpuBuffers;
};

