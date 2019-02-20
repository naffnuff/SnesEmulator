#include "Emulator.h"

#include <iostream>
#include <ctime>

Emulator::Emulator()
{
    state.loadRom("..\\..\\Legend of Zelda, The - A Link to the Past (U) [!].smc");
    //state.loadRom("..\\..\\Super Mario World (USA).sfc");
    //state.loadRom("..\\..\\Super Metroid (Japan, USA) (En,Ja).sfc");
    //state.loadRom("..\\..\\Super Metroid (JU) [!].smc");
    //state.loadRom("..\\..\\Megaman X (USA).sfc");
    //state.loadRom("..\\..\\SnesInitializationROM.smc");
    //state.loadRom("..\\..\\rom.smc");
    //state.loadRom("H:\\naffnuff\\wla\\rom.smc");
}

void Emulator::run()
{
    uint64_t cycleCount = 0;
    uint64_t instructionCount = 0;
    bool running = true;
    std::time_t startTime = clock();

    std::ostream& output = std::cout;
    
    while (running) {

        instructionCount++;

        output << std::hex << +state.readNextInstruction() << std::dec << ": ";

        Instruction* instruction = instructions.getInstruction(state.readNextInstruction());

        output << instruction->opcodeToString() << std::endl;
        output << instruction->toString(state) << std::endl;

        output << state << " -->" << std::endl;

        cycleCount += instruction->execute(state);

        output << state << std::endl;

        output << "instructionCount=" << instructionCount << ", cycleCount=" << cycleCount << std::endl;

        if (cycleCount > 1000000) {
            running = false;
        }

        std::getchar();
    }

    std::time_t endTime = clock();
    double elapsedSeconds = double(endTime - startTime) / CLOCKS_PER_SEC;

    output << "endTime=" << endTime << std::endl;
    output << "Time delta=" << elapsedSeconds << std::endl;

    output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
}

