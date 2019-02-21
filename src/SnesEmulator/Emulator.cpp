#include "Emulator.h"

#include <iostream>
#include <ctime>
#include <set>

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

    output << std::hex;

    uint32_t watchedAddress = 0;
    bool watchMode = false;
    bool stepMode = false;
    std::set<int> breakpoints;
    
    while (running) {

        instructionCount++;

        Instruction* instruction = instructions.getInstruction(state.readNextInstruction());

        if (state.readNextInstruction() == 0xFB) {
            //stepMode = true;
            //watchedAddress = state.getEffectiveProgramAddress();
            //state.printRegisters(output) << std::endl;
        }

        if (stepMode) {
            state.printMemoryPage(output, watchedAddress);
            output << instruction->opcodeToString() << std::endl;
            output << +state.readNextInstruction() << ": ";
            output << instruction->toString(state) << std::endl;
            state.printRegisters(output) << " -->";

            std::string command;
            std::getline(std::cin, command);
            output << "'" << command << "'" << std::endl;

            if (command.empty()) {
                cycleCount += instruction->execute(state);
                output << "instructionCount=" << instructionCount << ", cycleCount=" << cycleCount << std::endl;
            } else if (command == "n") {
                watchedAddress += (1 << 8);
            } else if (command == "p") {
                watchedAddress -= (1 << 8);
            } else if (command == "r") {
                stepMode = false;
                output << "Run mode" << std::endl;
            } else if (command.substr(0, 3) == "br ") {
                try {
                    int breakPoint = stoi(command.substr(3), 0, 16);
                    breakpoints.insert(breakPoint);
                    output << "Breakpoint " << breakPoint << " inserted" << std::endl;
                } catch (std::exception& e) {
                    std::cerr << "Not a valid address: " << e.what() << std::endl;
                }
            } else if (command == "w") {
                watchMode = !watchMode;
                output << "Watch mode " << (watchMode ? "on" : "off") << std::endl;
            } else {
                try {
                    stoi(command, &watchedAddress, 16);
                } catch (std::exception& e) {
                    std::cerr << "Not a valid address: " << e.what() << std::endl;
                }
            }
        } else {
            cycleCount += instruction->execute(state);
        }

        if (!stepMode) {
            uint32_t address = state.getEffectiveProgramAddress();
            stepMode = breakpoints.find(address) != breakpoints.end()
                || breakpoints.find(address - 1) != breakpoints.end()
                || breakpoints.find(address - 2) != breakpoints.end()
                || breakpoints.find(address - 3) != breakpoints.end();
        }

        if (watchMode) {
            watchedAddress = state.getEffectiveProgramAddress();
        }

        if (state.programCounter < 0x8000) {
            //output << "End of bank" << std::endl;
            //stepMode = true;
            if (state.programBank == 0xff) {
                //output << "End of program" << std::endl;
                break;
            } else {
                ++state.programBank;
                state.programCounter = 0x8000;
            }
        }
    }

    std::time_t endTime = clock();
    double elapsedSeconds = double(endTime - startTime) / CLOCKS_PER_SEC;

    output << "Time delta=" << elapsedSeconds << std::endl;

    output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
}

