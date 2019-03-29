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
    Blue = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
    Purple = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    DefaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};
#endif

class Debugger
{
public:
    class Config
    {
    public:
        Config(std::string fileName, Color debugColor, const Instruction* nextInstruction)
            : inspectedAddress(0)
            , fileName(fileName)
            , watchMode(true)
            , debugColor(debugColor)
            , nextInstruction(nextInstruction)
        {

        }

        Long inspectedAddress;
        std::set<Long> breakpoints;
        std::string fileName;
        bool watchMode;
        Color debugColor;
        const Instruction* nextInstruction;
    };

    Debugger(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
        , stepMode(true)
    {
    }

    template<typename State>
    int executeNext(Instruction* instruction, State& state, Config& config, uint64_t cycleCount)
    {
        try {
            if (stepMode) {
                printState(state, config);

                if (awaitCommand(config, state)) {
                    int cycles = instruction->execute();
                    if (stepMode) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), config.debugColor);
                        state.printRegisters(output) << std::endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
                    }
                    return cycles;
                }

            }
            else {
                for (Long i = state.getProgramAddress(); i < state.getProgramAddress() + instruction->size(); ++i) {
                    if (config.breakpoints.find(i) != config.breakpoints.end()) {
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
                else {
                    return instruction->execute();
                }
            }
        } catch (std::exception& e) {
            error << e.what() << std::endl;
            stepMode = true;
        }
        return 0;
    }

    template<typename State>
    bool awaitCommand(Config& config, State& state)
    {
        output << "Command (h for help): ";

        std::string command;
        std::getline(input, command);

        if (command.empty()) {
            output << "Step" << std::endl;
            return true;
        }
        else if (command == "h") {
            output << "[return]: step into next instruction" << std::endl
                << "n: inspect next memory page" << std::endl
                << "p: inspect previous memory page" << std::endl
                << "i: inspect operand address" << std::endl
                << "q: run program" << std::endl
                //<< "r: reset" << std::endl
                << "t: toggle breakpoint at current Program Counter address" << std::endl
                << "tt: toggle breakpoint at next Program Counter address" << std::endl
                << "t [hex]: toogle breakpoint at address [hex]" << std::endl
                << "clear: clear all breakpoints" << std::endl
                << "w: watch executing program memory" << std::endl
                << "[hex]: inspect memory page containing address [hex]" << std::endl
                << "[p|s|a|x|y|d|f]=[hex]: set register to [hex]" << std::endl
                << "[a]=[hex]: set address [a] to [hex]" << std::endl;
            std::getchar();
        }
        else if (command == "n") {
            config.watchMode = false;
            config.inspectedAddress += (1 << 8);
        }
        else if (command == "p") {
            config.watchMode = false;
            config.inspectedAddress -= (1 << 8);
        }
        else if (command == "q") {
            stepMode = false;
            output << "Run" << std::endl;
            startTime = clock();
            return true;
        }
        else if (command == "r") {
            output << "Reset not implemented" << std::endl;
        }
        else if (command == "i") {
            output << "Inspect not implemented" << std::endl;
        }
        else if (command == "clear") {
            config.breakpoints.clear();
            output << "Cleared config " << config.fileName << std::endl;
            std::ofstream file(config.fileName);
        }
        else if (command[0] == 't') {
            int breakpoint = state.getProgramAddress();
            std::string twoFirst = command.substr(0, 2);
            if (twoFirst == "tt") {
                breakpoint += config.nextInstruction->size();
            }
            else if (twoFirst == "t ") {
                try {
                    breakpoint = stoi(command.substr(2), 0, 16);
                } catch (std::exception& e) {
                    std::cerr << "Not a valid value: " << e.what() << std::endl;
                }
            }
            if (config.breakpoints.find(breakpoint) == config.breakpoints.end()) {
                config.breakpoints.insert(breakpoint);
                output << "Breakpoint inserted at address " << breakpoint << std::endl;
            }
            else {
                config.breakpoints.erase(breakpoint);
                output << "Breakpoint removed at address " << breakpoint << std::endl;
            }
            std::ofstream file(config.fileName);
            if (file) {
                for (Long breakpoint : config.breakpoints) {
                    file << breakpoint << " ";
                }
            }
        }
        else if (command == "w") {
            config.watchMode = !config.watchMode;
            output << "Watch mode " << (config.watchMode ? "on" : "off") << std::endl;
        }
        else if (command.size() > 1 && command[1] == '=') {
            try {
                Word value = (Word)stoi(command.substr(2), 0, 16);
                output << "Setting register " << command[0] << "=" << value << std::endl;
                state.setRegisterDebug(command[0], value);
            } catch (std::exception& e) {
                error << "Not a valid address: " << e.what() << std::endl;
            }
        }
        else if (command.find('=') != std::string::npos) {
            int pos = command.find('=');
            try {
                output << "Address: " << command.substr(0, pos) << ", value: " << command.substr(pos + 1) << std::endl;
                Long address = stoi(command.substr(0, pos), 0, 16);
                Byte value = (Byte)stoi(command.substr(pos + 1), 0, 16);
                output << "Setting address " << address <<
                    "=" << value << std::endl;
                *state.getMemoryPointer(address) = value;
            } catch (std::exception& e) {
                error << "Not valid: " << command.substr(0, pos) << " or " << command.substr(pos + 1) << ": " << e.what() << std::endl;
            }
        }
        else {
            try {
                config.inspectedAddress = stoi(command, 0, 16);
                output << "Inspecting address " << config.inspectedAddress << std::endl;
                config.watchMode = false;
            } catch (std::exception& e) {
                error << "Not a valid address: " << e.what() << std::endl;
            }
        }

        return false;
    }

    template<typename State>
    void printState(const State& state, Config& config)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), config.debugColor);
        state.printRegisters(output) << std::endl;
        output << config.nextInstruction->opcodeToString() << std::endl;
        output << state.readProgramByte() << ": ";
        output << config.nextInstruction->toString() << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
    }

    template<typename State>
    void setColor(const State& state, const Config& config, Long address)
    {
        bool breakpoint = config.breakpoints.find(address) != config.breakpoints.end();
        bool executing = address >= state.getProgramAddress() && address < state.getProgramAddress() + config.nextInstruction->size();
        Color color = DefaultColor;
        if (breakpoint && executing) {
            color = Purple;
        }
        else if (breakpoint) {
            color = Red;
        }
        else if (executing) {
            color = config.debugColor;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void printMemory(const CPU::State& cpuState, const Config& cpuConfig, const SPC::State& spcState, const Config& spcConfig)
    {
        Long startCpuAddress = cpuConfig.watchMode ? cpuState.getProgramAddress() : cpuConfig.inspectedAddress;
        Long startSpcAddress = spcConfig.watchMode ? spcState.getProgramAddress() : spcConfig.inspectedAddress;

        size_t cpuMemorySize = cpuState.getMemorySize();
        size_t spcMemorySize = spcState.getMemorySize();

        output << "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f"
            << "             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        Long cpuAddress = startCpuAddress - std::bitset<4>(startCpuAddress).to_ulong();
        Long spcAddress = startSpcAddress - std::bitset<4>(startSpcAddress).to_ulong();


        for (int i = 0; i < 16; ++i) {
            if (cpuAddress < cpuMemorySize) {
                Byte bank = Byte(cpuAddress >> 16);
                Word lowAddress(cpuAddress);
                lowAddress = Word(lowAddress >> 4);
                output << bank << ':' << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && cpuAddress < cpuMemorySize; ++j) {
                    setColor(cpuState, cpuConfig, cpuAddress);
                    output << cpuState.getMemory(cpuAddress++) << ' ';
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
                }
            }

            output << "     ";

            if (spcAddress < spcMemorySize) {
                Word lowAddress(spcAddress);
                lowAddress = Word(lowAddress >> 4);
                output << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  ";

                for (int j = 0; j < 16 && spcAddress < spcMemorySize; ++j) {
                    setColor(spcState, spcConfig, spcAddress);
                    output << spcState.getMemory(Word(spcAddress++)) << ' ';
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
                }
            }

            output << std::endl;
        }
    }

    bool stepMode;
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

    CPU::OpcodeMap cpuOpcodeMap(cpuState);
    SPC::OpcodeMap spcOpcodeMap(spcState);

    Debugger debugger(output, input, error);

    Debugger::Config cpuConfig("cpu.txt", Green, cpuOpcodeMap.getNextInstruction(cpuState));
    Debugger::Config spcConfig("spc.txt", Blue, spcOpcodeMap.getNextInstruction(spcState));

    const bool resumeLast = true;

    if (resumeLast) {
        for (Debugger::Config* config : { &cpuConfig, &spcConfig }) {
            std::ifstream configFile(config->fileName);
            if (configFile) {
                std::string breakpointString;
                while (std::getline(configFile, breakpointString, ' ')) {
                    Long breakpoint = std::stoi(breakpointString, 0, 16);
                    output << "Read breakpoint: " << breakpoint << " from " << config->fileName << std::endl;
                    config->breakpoints.insert(breakpoint);
                }
            }
        }
    }

    uint64_t cycleCount = 186;
    uint64_t nextCpu = 186;
    uint64_t nextSpc = 186;
    bool running = true;
    debugger.startTime = clock();

    while (running) {
        if (debugger.stepMode) {
            if ((cycleCount == nextCpu || cycleCount == nextSpc)) {
                output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                for (const Debugger::Config& config : { cpuConfig, spcConfig }) {
                    if (!config.breakpoints.empty()) {
                        output << "Breakpoints:";
                        for (Long breakpoint : config.breakpoints) {
                            output << " " << breakpoint;
                        }
                        output << std::endl;
                    }
                }
            }
        }

        if (cycleCount == nextCpu) {
            Instruction* instruction = cpuOpcodeMap.getNextInstruction(cpuState);

            if (debugger.stepMode) {
                debugger.printMemory(cpuState, cpuConfig, spcState, spcConfig);
            }

            if (int cycles = debugger.executeNext(instruction, cpuState, cpuConfig, cycleCount)) {
                nextCpu += cycles * 8;
                for (int i = 0; i < 4; ++i) {
                    spcState.getMemory(Byte(0xf4 + i)) = cpuState.getMemory(0x2140 + i);
                }
                cpuConfig.nextInstruction = cpuOpcodeMap.getNextInstruction(cpuState);
            }
            else {
                continue;
            }
        }

        if (cycleCount == nextSpc) {
            Instruction* instruction = spcOpcodeMap.getNextInstruction(spcState);

            if (debugger.stepMode) {
                debugger.printMemory(cpuState, cpuConfig, spcState, spcConfig);
            }

            if (int cycles = debugger.executeNext(instruction, spcState, spcConfig, cycleCount)) {
                nextSpc += cycles * 16;
                for (int i = 0; i < 4; ++i) {
                    *cpuState.getMemoryPointer(Long(0x2140 + i)) = spcState.getMemory(Byte(0xf4 + i));
                }
                spcConfig.nextInstruction = spcOpcodeMap.getNextInstruction(spcState);
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
