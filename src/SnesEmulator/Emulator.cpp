#include "Emulator.h"

#include <fstream>
#include <iostream>

#include "CPU/CpuState.h"
#include "SPC/SpcState.h"

#include "CPU/CpuOpcodeMap.h"
#include "SPC/SpcOpcodeMap.h"

#ifdef _WIN32
#include <windows.h>
enum Color
{
    Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    DefaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
};
#endif

class Debugger
{
public:
    class Config
    {
    public:
        Config()
            : inspectedAddress(0)
        {

        }

        uint32_t inspectedAddress;
    };

    Debugger(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
        , watchMode(true)
        , stepMode(true)
    {
    }

    template<typename State>
    int executeNext(Instruction* instruction, const State& state, Config& config, uint64_t cycleCount, Color color)
    {
        if (stepMode) {
            printState(instruction, state, color);

            if (awaitCommand(config)) {
                int cycles = instruction->execute();
                if (stepMode) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
                    state.printRegisters(output) << std::endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
                }
                return cycles;
            }

        } else {
            /*if (cycleCount > 38000) {
                stepMode = true;
            }*/

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
    
    bool awaitCommand(Config& config)
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
            config.inspectedAddress += (1 << 8);
        } else if (command == "p") {
            watchMode = false;
            config.inspectedAddress -= (1 << 8);
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
                state.setFlags((Byte)value);
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
                Byte value = (Byte)stoi(command.substr(pos + 1), 0, 16);
                output << "Setting address " << std::setw(6) << std::setfill('0') << address <<
                    "=" << value << std::endl;
                //*state.getMemoryPointer(address) = value;
            } catch (std::exception& e) {
                error << "Not valid: " << command.substr(0, pos) << " or " << command.substr(pos + 1) << ": " << e.what() << std::endl;
            }
        } else {
            try {
                config.inspectedAddress = stoi(command, 0, 16);
                output << "Inspecting address " << std::setw(6) << std::setfill('0') << config.inspectedAddress << std::endl;
                watchMode = false;
            } catch (std::exception& e) {
                error << "Not a valid address: " << e.what() << std::endl;
            }
        }

        return false;
    }

    template<typename State>
    void printState(const Instruction* instruction, const State& state, Color color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        state.printRegisters(output) << std::endl;
        output << instruction->opcodeToString() << std::endl;
        output << state.readProgramByte() << ": ";
        output << instruction->toString() << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
    }

    void printMemory(const CPU::State& cpuState, uint32_t startCpuAddress, const SPC::State& spcState, uint32_t startSpcAddress)
    {
        size_t cpuMemorySize = cpuState.getMemorySize();
        size_t spcMemorySize = spcState.getMemorySize();

        output << "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f"
            << "             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        uint32_t cpuAddress = startCpuAddress - std::bitset<4>(startCpuAddress).to_ulong();
        uint32_t spcAddress = startSpcAddress - std::bitset<4>(startSpcAddress).to_ulong();


        for (int i = 0; i < 16; ++i) {
            if (cpuAddress < cpuMemorySize) {
                Byte bank = Byte(cpuAddress >> 16);
                uint16_t lowAddress = uint16_t(cpuAddress);
                lowAddress = lowAddress >> 4;
                output << bank << ':' << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  ";

                for (int j = 0; j < 16 && cpuAddress < cpuMemorySize; ++j) {
                    output << cpuState.getMemory(cpuAddress++) << ' ';
                }
            }

            output << "     ";

            if (spcAddress < spcMemorySize) {
                uint16_t lowAddress = spcAddress;
                lowAddress = lowAddress >> 4;
                output << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  ";

                for (int j = 0; j < 16 && spcAddress < spcMemorySize; ++j) {
                    output << spcState.getMemory(spcAddress++) << ' ';
                }
            }

            output << std::endl;
        }
    }

    bool watchMode;
    bool stepMode;
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

    Debugger::Config cpuConfig;
    Debugger::Config spcConfig;

    const bool resumeLast = true;

    if (resumeLast) {
        std::ifstream addressFile("address.txt");
        int programAddress = -1;
        addressFile >> std::hex >> programAddress;
        if (programAddress != -1) {
            output << "Read breakpoint: " << programAddress << std::endl;
            debugger.breakpoints.insert(programAddress);
        }
    }

    CPU::OpcodeMap cpuOpcodeMap(cpuState);
    SPC::OpcodeMap spcOpcodeMap(spcState);

    uint64_t cycleCount = 186;
    uint64_t nextCpu = 186;
    uint64_t nextSpc = 186;
    bool running = true;
    debugger.startTime = clock();
    
    while (running) {
        if (debugger.stepMode) {
            if ((cycleCount == nextCpu || cycleCount == nextSpc)) {
                output << std::dec << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::hex << std::endl;
                if (!debugger.breakpoints.empty()) {
                    output << "Breakpoints:";
                    for (int breakpoint : debugger.breakpoints) {
                        output << " " << breakpoint;
                    }
                    output << std::endl;
                }
            }
        }
        
        if (cycleCount == nextCpu) {
            if (debugger.stepMode) {
                if (debugger.watchMode) {
                    debugger.printMemory(cpuState, cpuState.getProgramAddress(), spcState, spcState.getProgramAddress());
                }
                else {
                    debugger.printMemory(cpuState, cpuConfig.inspectedAddress, spcState, spcConfig.inspectedAddress);
                }
            }

            Instruction* instruction = cpuOpcodeMap.getNextInstruction(cpuState);
            int cycles = 0;
            if (debugger.stepMode && resumeLast) {
                std::ofstream pcFile("address.txt");
                pcFile << std::hex << cpuState.getProgramAddress();
            }
            if (cycles = debugger.executeNext(instruction, cpuState, cpuConfig, cycleCount, Green)) {
                nextCpu += cycles * 8;
                for (int i = 0; i < 4; ++i) {
                    spcState.getMemory(0xf4 + i) = cpuState.getMemory(0x2140 + i);
                }
            }
            else {
                continue;
            }
        }

        if (cycleCount == nextSpc) {
            if (debugger.stepMode) {
                if (debugger.watchMode) {
                    debugger.printMemory(cpuState, cpuState.getProgramAddress(), spcState, spcState.getProgramAddress());
                }
                else {
                    debugger.printMemory(cpuState, cpuConfig.inspectedAddress, spcState, spcConfig.inspectedAddress);
                }
            }

            Instruction* instruction = spcOpcodeMap.getNextInstruction(spcState);
            int cycles = 0;
            if (cycles = debugger.executeNext(instruction, spcState, spcConfig, cycleCount, Blue)) {
                nextSpc += cycles * 16;
                for (int i = 0; i < 4; ++i) {
                    *cpuState.getMemoryPointer(0x2140 + i) = spcState.getMemory(0xf4 + i);
                }
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
