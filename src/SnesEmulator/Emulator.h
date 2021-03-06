#pragma once

#include <ctime>
#include <set>

#include "Common/Instruction.h"
#include "Common/System.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"
#include "SPC700/Audio.h"

#include "WDC65816/CpuInstructionDecoder.h"
#include "SPC700/SpcInstructionDecoder.h"

#include "Rom.h"
#include "Debugger.h"
#include "Renderer.h"
#include "Video.h"
#include "Registers.h"

class Emulator
{
private:
    struct SaveRamSaver {
        SaveRamSaver(Emulator& emulator)
            : saveRam(emulator.rom.romSize)
            , rom(emulator.rom)
        {
        }

        void operator()()
        {
            running = true;
            while (running) {
                bool save = false;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    condition.wait(lock, [this]() { return saveRamModified || !running; });
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

        bool running = false;
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
        , video(output)
        , rom(rom)
        , cpuState()
        , spcState()
        , registers(output, error, cpuState, video)
        , audio(output, error, spcState)
        , debugger(output, input, error, registers, audio, masterCycle, running)
        , cpuInstructionDecoder(cpuState)
        , spcInstructionDecoder(spcState)
        , cpuContext("cpu.txt", System::Green, debugger)
        , spcContext("spc.txt", System::Magenta, debugger)
        , saveRamSaver(*this)
    {
    }

    Emulator(const Emulator&) = delete;
    Emulator& operator=(const Emulator&) = delete;

    ~Emulator()
    {
        if (saveRamSaver.running) {
            saveRamSaver.running = false;
            saveRamSaver.condition.notify_one();
            saveRamSaverThread.join();
        }
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

    Debugger debugger;
    const Rom& rom;
    CPU::State cpuState;
    SPC::State spcState;
    CPU::InstructionDecoder cpuInstructionDecoder;
    SPC::InstructionDecoder spcInstructionDecoder;
    Debugger::Context cpuContext;
    Debugger::Context spcContext;

    Video video;
    Registers registers;
    SPC::Audio audio;

    bool running = true;
    uint64_t masterCycle = 186;

    SaveRamSaver saveRamSaver;
    std::thread saveRamSaverThread;

    std::array<Byte, 4> cpuToSpcBuffers;
    std::array<Byte, 4> spcToCpuBuffers;
};

