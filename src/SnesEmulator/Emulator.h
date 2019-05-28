#pragma once

#include <ctime>
#include <set>

#include "Common/Instruction.h"

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
        , registers(output, error, debugger, cpuState, video)
        , debugger(output, input, error, cycleCount, running)
        , rom(output)
        , cpuInstructionDecoder(cpuState)
        , spcInstructionDecoder(spcState)
        , cpuContext("cpu.txt", Debugger::Green)
        , spcContext("spc.txt", Debugger::Magenta)
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

