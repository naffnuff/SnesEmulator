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
#include "Renderer.h"
#include "Video.h"
#include "Registers.h"

class Emulator
{
public:
    Emulator(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
        , video(output)
        , cpuState()
        , spcState()
        , debugger(output, input, error, registers, cycleCount, running)
        , registers(output, error, cpuState, video)
        , rom(output)
        , cpuInstructionDecoder(cpuState)
        , spcInstructionDecoder(spcState)
        , cpuContext("cpu.txt", System::Green)
        , spcContext("spc.txt", System::Magenta)
    {
    }

    Emulator(const Emulator&) = delete;
    Emulator& operator=(const Emulator&) = delete;

    void initialize();
    void run();

    std::string getRomTitle() const
    {
        return rom.gameTitle;
    }

    void pause()
    {
        cpuContext.stepMode = true;
    }

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;

    Debugger debugger;
    Rom rom;
    CPU::State cpuState;
    SPC::State spcState;
    CPU::InstructionDecoder cpuInstructionDecoder;
    SPC::InstructionDecoder spcInstructionDecoder;
    Debugger::Context cpuContext;
    Debugger::Context spcContext;

    Video video;
    Registers registers;

    bool running = true;
    uint64_t cycleCount = 186;

};

