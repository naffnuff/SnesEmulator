#include "Emulator.h"

#include <fstream>
#include <iostream>

#include "CPU/CpuState.h"
#include "SPC/SpcState.h"

#include "CPU/CpuOpcodeMap.h"
#include "SPC/SpcOpcodeMap.h"

class Debugger
{
public:
    Debugger(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
    {
    }

    template<typename State>
    int executeNext(Instruction* instruction, const State& state, uint64_t cycleCount)
    {
        if (stepMode) {
            /*if (resumeLast) {
            std::ofstream pcFile("address.txt");
            pcFile << std::hex << state.getProgramAddress();
            }*/

            printState(instruction, state);

            if (awaitCommand()) {
                return instruction->execute();
            }

        } else {

            for (uint32_t i = state.getProgramAddress(); i < state.getProgramAddress() + instruction->size(); ++i) {
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
            } else {
                return instruction->execute();
            }
        }
        return 0;
    }
    
    bool awaitCommand()
    {
        output << "Command (h for help): ";

        std::string command;
        std::getline(input, command);

        if (command.empty()) {
            output << "Step" << std::endl;
            return true;
        } else if (command == "h") {
            output << "[return]: step into next instruction" << std::endl
                << "n: inspect next memory page" << std::endl
                << "p: inspect previous memory page" << std::endl
                << "r: run program" << std::endl
                << "br [hex]: toogle breakpoint at address [hex]" << std::endl
                << "w: watch executing program memory" << std::endl
                << "[hex]: inspect memory page containing address [hex]" << std::endl
                << "[p|s|a|x|y|d|f]=[hex]: set register to [hex]" << std::endl
                << "[a]=[hex]: set address [a] to [hex]" << std::endl;
            std::getchar();
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
            return true;
        } else if (command.substr(0, 3) == "br ") {
            try {
                int breakpoint = stoi(command.substr(3), 0, 16);
                if (breakpoints.find(breakpoint) == breakpoints.end()) {
                    breakpoints.insert(breakpoint);
                    output << "Breakpoint inserted at address " << breakpoint << std::endl;
                } else {
                    breakpoints.erase(breakpoint);
                    output << "Breakpoint removed at address " << breakpoint << std::endl;
                }
            } catch (std::exception& e) {
                std::cerr << "Not a valid value: " << e.what() << std::endl;
            }
        } else if (command == "w") {
            watchMode = !watchMode;
            output << "Watch mode " << (watchMode ? "on" : "off") << std::endl;
        } else if (command.size() > 1 && command[1] == '=') {
            try {
                uint16_t value = (uint16_t)stoi(command.substr(2), 0, 16);
                output << "Setting register " << command[0] << "=" << std::setw(6) << std::setfill('0') << value << std::endl;
                /*switch (command[0]) {
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
                case 'f':
                state.setFlags((uint8_t)value);
                break;
                default:
                error << "Unknown register " << command[0] << std::endl;
                break;
                }*/
            } catch (std::exception& e) {
                error << "Not a valid address: " << e.what() << std::endl;
            }
        } else if (command.find('=') != std::string::npos) {
            int pos = command.find('=');
            try {
                output << "Address: " << command.substr(0, pos) << ", value: " << command.substr(pos + 1) << std::endl;
                uint32_t address = stoi(command.substr(0, pos), 0, 16);
                uint8_t value = (uint8_t)stoi(command.substr(pos + 1), 0, 16);
                output << "Setting address " << std::setw(6) << std::setfill('0') << address <<
                    "=" << std::setw(2) << std::setfill('0') << +value << std::endl;
                //*state.getMemoryPointer(address) = value;
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

        return false;
    }

    template<typename State>
    void printState(const Instruction* instruction, const State& state)
    {
        if (watchMode) {
            inspectedAddress = state.getProgramAddress();
        }
        if (!breakpoints.empty()) {
            output << "Breakpoints:";
            for (int breakpoint : breakpoints) {
                output << " " << breakpoint;
            }
            output << std::endl;
        }
        state.printMemoryPage(output, inspectedAddress);
        state.printRegisters(output) << std::endl;
        output << instruction->opcodeToString() << std::endl;
        output << std::setw(2) << std::setfill('0') << +state.readProgramByte() << ": ";
        output << instruction->toString() << std::endl;
    }

    uint32_t inspectedAddress = 0;
    bool watchMode = true;
    bool stepMode = true;
    std::set<uint32_t> breakpoints;
    std::time_t startTime;

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;
};

void Emulator::run()
{
    CPU::State cpuState;

    cpuState.loadRom("..\\..\\Legend of Zelda, The - A Link to the Past (U) [!].smc", output);
    //state.loadRom("..\\..\\Super Mario World (USA).sfc");
    //state.loadRom("..\\..\\Super Metroid (Japan, USA) (En,Ja).sfc");
    //state.loadRom("..\\..\\Super Metroid (JU) [!].smc");
    //state.loadRom("..\\..\\Megaman X (USA).sfc");
    //state.loadRom("..\\..\\SnesInitializationROM.smc");
    //state.loadRom("..\\..\\rom.smc");
    //state.loadRom("H:\\naffnuff\\wla\\rom.smc");
    //state.loadRom("C:\\cygwin64\\home\\rasmus.knutsson\\wla-dx\\wla\\myrom.smc");
    
    SPC::State spcState;

    Debugger debugger(output, input, error);

    const bool resumeLast = false;

    if (resumeLast) {
        std::ifstream addressFile("address.txt");
        int programAddress = -1;
        addressFile >> std::hex >> programAddress;
        output << "Read breakpoint: " << programAddress << std::endl;
        debugger.breakpoints.insert(programAddress);
    }

    CPU::OpcodeMap cpuOpcodeMap(cpuState);
    SPC::OpcodeMap spcOpcodeMap(spcState);

    uint64_t cycleCount = 0;
    uint64_t nextCpu = 0;
    uint64_t nextSpc = 0;
    bool running = true;
    debugger.startTime = clock();
    
    while (running) {
        output << std::dec << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::hex << std::endl;
        
        if (cycleCount == nextCpu) {
            Instruction* instruction = cpuOpcodeMap.getNextInstruction(cpuState);
            int cycles = 0;
            if (cycles = debugger.executeNext(instruction, cpuState, cycleCount)) {
                nextCpu += cycles;
                cpuState.printRegisters(output) << std::endl;
            }
            else {
                continue;
            }
        }

        if (cycleCount == nextSpc) {
            Instruction* instruction = spcOpcodeMap.getNextInstruction(spcState);
            int cycles = 0;
            if (cycles = debugger.executeNext(instruction, spcState, cycleCount)) {
                nextSpc += cycles;
                spcState.printRegisters(output) << std::endl;
            }
            else {
                continue;
            }
        }

        ++cycleCount;
    }

    std::time_t endTime = clock();
    double elapsedSeconds = double(endTime - debugger.startTime) / CLOCKS_PER_SEC;
    output << "Time delta=" << elapsedSeconds << std::endl;
    output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
}
