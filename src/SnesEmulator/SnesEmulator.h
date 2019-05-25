#pragma once

#include <ctime>
#include <set>

#include "Common/Instruction.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"

#include "WDC65816/CpuInstructionDecoder.h"
#include "SPC700/SpcInstructionDecoder.h"

#include "SnesRom.h"
#include "Debugger.h"
#include "SnesRenderer.h"
#include "VideoMemory.h"

class Emulator
{
public:
    Emulator(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
        , videoMemory(output)
        , vramRenderer(vramRendererWidth, vramRendererHeight, 2.f, true, output)
        , cgramRenderer(16, 16, 16.f, true, output)
        , debugger(output, input, error, cycleCount, running)
        , rom(output)
        , cpuInstructionDecoder(cpuState)
        , spcInstructionDecoder(spcState)
        , cpuContext("cpu.txt", Debugger::Green)
        , spcContext("spc.txt", Debugger::Magenta)
        , registers(0x6000)
    {
    }

    Emulator(Emulator&) = delete;
    Emulator& operator=(Emulator&) = delete;

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
    static const int vramRendererWidth = 0x200;
    static const int vramRendererHeight = 0x200;

    std::ostream& output;
    std::istream& input;
    std::ostream& error;

    Renderer vramRenderer;
    Renderer cgramRenderer;
    Debugger debugger;
    Rom rom;
    CPU::State cpuState;
    SPC::State spcState;
    CPU::InstructionDecoder cpuInstructionDecoder;
    SPC::InstructionDecoder spcInstructionDecoder;
    Debugger::Context cpuContext;
    Debugger::Context spcContext;

    std::vector<MemoryLocation> registers;
    VideoMemory videoMemory;

    bool running = true;
    uint64_t cycleCount = 186;

};

