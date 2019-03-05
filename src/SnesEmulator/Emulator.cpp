#include "Emulator.h"

#include <iostream>
#include <ctime>
#include <set>

void Emulator::run(std::ostream& output, std::istream& input, std::ostream& error)
{
    state.loadRom("..\\..\\Legend of Zelda, The - A Link to the Past (U) [!].smc", output);
    //state.loadRom("..\\..\\Super Mario World (USA).sfc");
    //state.loadRom("..\\..\\Super Metroid (Japan, USA) (En,Ja).sfc");
    //state.loadRom("..\\..\\Super Metroid (JU) [!].smc");
    //state.loadRom("..\\..\\Megaman X (USA).sfc");
    //state.loadRom("..\\..\\SnesInitializationROM.smc");
    //state.loadRom("..\\..\\rom.smc");
    //state.loadRom("H:\\naffnuff\\wla\\rom.smc");
    //state.loadRom("C:\\cygwin64\\home\\rasmus.knutsson\\wla-dx\\wla\\myrom.smc");

    uint64_t cycleCount = 0;
    uint64_t instructionCount = 0;
    bool running = true;
    std::time_t startTime = clock();

    uint32_t inspectedAddress = 0;
    bool showMemory = true;
    bool showRegisters = true;
    bool watchMode = false;
    bool stepMode = true;
    std::set<int> breakpoints;
    
    while (running) {

        instructionCount++;

        Instruction* instruction = instructions.getInstruction(state.readProgramByte());

        if (stepMode) {
            if (watchMode) {
                inspectedAddress = state.getProgramAddress();
            }

            output << std::dec << "instructionCount=" << instructionCount << ", cycleCount=" << cycleCount << std::hex << std::endl;
            if (!breakpoints.empty()) {
                output << "Breakpoints:";
                for (int breakpoint : breakpoints) {
                    output << " " << breakpoint;
                }
                output << std::endl;
            }
            if (showMemory) {
                state.printMemoryPage(output, inspectedAddress);
            }
            if (showRegisters) {
                state.printRegisters(output) << std::endl;
            }
            output << instruction->opcodeToString() << std::endl;
            output << std::setw(2) << std::setfill('0') << +state.readProgramByte() << ": ";
            output << instruction->toString(state) << std::endl;

            output << "Command (h for help): ";

            std::string command;
            std::getline(input, command);

            if (command.empty()) {
                cycleCount += instruction->execute(state);
                output << "Step" << std::endl;
            } else if (command == "h") {
                output << "[return]: step into next instruction" << std::endl
                    << "s: toggle show register state" << std::endl
                    << "m: toggle show memory" << std::endl
                    << "n: inspect next memory page" << std::endl
                    << "p: inspect previous memory page" << std::endl
                    << "r: run program" << std::endl
                    << "br [hex]: toogle breakpoint at address [hex]" << std::endl
                    << "w: watch executing program memory" << std::endl
                    << "[hex]: inspect memory page containing address [hex]" << std::endl
                    << "[p|s|a|x|y|d]=[hex]: set register to [hex]" << std::endl
                    << "[a]=[hex]: set address [a] to [hex]" << std::endl;
                std::getchar();
            } else if (command == "s") {
                showRegisters = !showRegisters;
            } else if (command == "m") {
                showMemory = !showMemory;
            } else if (command == "n") {
                watchMode = false;
                inspectedAddress += (1 << 8);
            } else if (command == "p") {
                watchMode = false;
                inspectedAddress -= (1 << 8);
            } else if (command == "r") {
                stepMode = false;
                output << "Run" << std::endl;
                startTime = clock();
            } else if (command.substr(0, 3) == "br ") {
                try {
                    int breakPoint = stoi(command.substr(3), 0, 16);
                    if (breakpoints.find(breakPoint) == breakpoints.end()) {
                        breakpoints.insert(breakPoint);
                        output << "Breakpoint inserted at address " << breakPoint << std::endl;
                    } else {
                        breakpoints.erase(breakPoint);
                        output << "Breakpoint removed at address " << breakPoint << std::endl;
                    }
                } catch (std::exception& e) {
                    std::cerr << "Not a valid value: " << e.what() << std::endl;
                }
            } else if (command == "w") {
                watchMode = !watchMode;
                output << "Watch mode " << (watchMode ? "on" : "off") << std::endl;
            } else if (command.size() > 1 && command[1] == '=') {
                try {
                    uint16_t value = stoi(command.substr(2), 0, 16);
                    output << "Setting register " << command[0] << "=" << std::setw(6) << std::setfill('0') << value << std::endl;
                    switch (command[0]) {
                    case 'p':
                        state.setProgramCounter(value);
                        break;
                    case 's':
                        state.setStackPointer(value);
                        break;
                    case 'a':
                        state.setAccumulatorC(value);
                        break;
                    case 'x':
                        state.setXIndexRegister(value);
                        break;
                    case 'y':
                        state.setYIndexRegister(value);
                        break;
                    case 'd':
                        state.setDirectPageRegister(value);
                        break;
                    default:
                        error << "Unknown register " << command[0] << std::endl;
                        break;
                    }
                } catch (std::exception& e) {
                    error << "Not a valid address: " << e.what() << std::endl;
                }
            } else if (command.find('=') != std::string::npos) {
                int pos = command.find('=');
                try {
                    output << "Address: " << command.substr(0, pos) << ", value: " << command.substr(pos + 1) << std::endl;
                    uint32_t address = stoi(command.substr(0, pos), 0, 16);
                    uint8_t value = stoi(command.substr(pos + 1), 0, 16);
                    output << "Setting address " << std::setw(6) << std::setfill('0') << address <<
                        "=" << std::setw(2) << std::setfill('0') << +value << std::endl;
                    *state.getMemoryPointer(address, address >> 8, address >> 16) = value;
                } catch (std::exception& e) {
                    error << "Not valid: " << command.substr(0, pos) << " or " << command.substr(pos + 1) << ": " << e.what() << std::endl;
                }
            } else {
                try {
                    inspectedAddress = stoi(command, 0, 16);
                    output << "Inspecting address " << std::setw(6) << std::setfill('0') << inspectedAddress << std::endl;
                    watchMode = false;
                } catch (std::exception& e) {
                    error << "Not a valid address: " << e.what() << std::endl;
                }
            }
        }

        if (!stepMode) {
            uint32_t previousAddress = state.getProgramAddress();

            cycleCount += instruction->execute(state);

            uint32_t address = state.getProgramAddress();

            for (uint32_t i = address; i > previousAddress; --i) {
                if (breakpoints.find(i) != breakpoints.end()) {
                    stepMode = true;
                    break;
                }
            }

            if (stepMode) {
                std::time_t endTime = clock();
                double elapsedSeconds = double(endTime - startTime) / CLOCKS_PER_SEC;
                output << "Time delta=" << elapsedSeconds << std::endl;
                output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
            }
        }

        /*if (state.programCounter < 0x8000) {
            //output << "End of bank" << std::endl;
            //stepMode = true;
            if (state.programBank == 0xff) {
                //output << "End of program" << std::endl;
                break;
            } else {
                ++state.programBank;
                state.programCounter = 0x8000;
            }
        }*/
    }

    std::time_t endTime = clock();
    double elapsedSeconds = double(endTime - startTime) / CLOCKS_PER_SEC;
    output << "Time delta=" << elapsedSeconds << std::endl;
    output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
}

