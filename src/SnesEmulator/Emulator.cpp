#include "Emulator.h"

#include <iostream>

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
    
    while (running) {

        instructionCount++;

        Instruction* instruction = instructions.getInstruction(state.readNextInstruction());

        //instruction->printNextExecution(std::cout, state) << std::endl;

        cycleCount += instruction->execute(state);

        //std::cout << "instructionCount=" << instructionCount << ", cycleCount=" << cycleCount << std::endl;

        if (cycleCount > 10000000) {
            running = false;
        }

        //std::getchar();
    }
}

