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
    Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
    Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
    Purple = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    DefaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};
#endif

class Debugger
{
public:
    class Context
    {
    public:
        Context(std::string fileName, Color debugColor, const Instruction* nextInstruction)
            : inspectedAddress(0)
            , fileName(fileName)
            , watchMode(true)
            , stepMode(true)
            , debugColor(debugColor)
            , nextInstruction(nextInstruction)
        {

        }

        std::string fileName;
        Long inspectedAddress;
        bool watchMode;
        bool stepMode;
        Color debugColor;
        std::set<Long> breakpoints;
        const Instruction* nextInstruction;
    };

    Debugger(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
    {
    }

    template<typename State, typename OtherState>
    int executeNext(Instruction* instruction, State& state, Context& context, uint64_t cycleCount, OtherState& otherState, Context& otherContext)
    {
        try {
            if (context.stepMode) {
                printState(state, context);

                if (awaitCommand(context, state, otherContext, otherState)) {
                    int cycles = instruction->execute();
                    if (context.stepMode) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), context.debugColor);
                        state.printRegisters(output) << std::endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
                    }
                    return cycles;
                }

            }
            else {
                for (Long i = state.getProgramAddress(); i < state.getProgramAddress() + instruction->size(); ++i) {
                    if (context.breakpoints.find(i) != context.breakpoints.end()) {
                        context.stepMode = true;
                        break;
                    }
                }

                if (context.stepMode) {
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
            context.stepMode = true;
        }
        return 0;
    }

    template<typename State, typename OtherState>
    bool awaitCommand(Context& context, State& state, Context& otherContext, OtherState& otherState)
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
                << "r: toggle run context" << std::endl
                << "rr: run all contexts" << std::endl
                //<< "r: reset" << std::endl
                << "t: toggle breakpoint at current Program Counter address" << std::endl
                << "tt: toggle breakpoint at next Program Counter address" << std::endl
                << "t [hex]: toogle breakpoint at address [hex]" << std::endl
                << "clear: clear all breakpoints" << std::endl
                << "w: watch executing program memory" << std::endl
                << "[hex]: inspect memory page containing address [hex]" << std::endl
                << "[p|s|a|x|y|d|f]=[hex]: set register to [hex]" << std::endl
                << "[a]=[hex]: set address [a] to [hex]" << std::endl
                << "s: switch context" << std::endl;
        }
        else if (command == "n") {
            context.watchMode = false;
            context.inspectedAddress += (1 << 8);
        }
        else if (command == "p") {
            context.watchMode = false;
            context.inspectedAddress -= (1 << 8);
        }
        else if (command[0] == 'r') {
            if (command == "rr") {
                context.stepMode = false;
                otherContext.stepMode = false;
            }
            else {
                context.stepMode = !context.stepMode;
                if (context.stepMode) {
                    output << "Step mode" << std::endl;
                }
                else {
                    output << "Run mode" << std::endl;
                }
            }
            if (!context.stepMode && !otherContext.stepMode) {
                output << "All running" << std::endl;
                startTime = clock();
            }
            return !context.stepMode;
        }
        else if (command == "i") {
            output << "Inspect not implemented" << std::endl;
        }
        else if (command == "clear") {
            context.breakpoints.clear();
            output << "Cleared context " << context.fileName << std::endl;
            std::ofstream file(context.fileName);
        }
        else if (command[0] == 't') {
            int breakpoint = state.getProgramAddress();
            std::string twoFirst = command.substr(0, 2);
            if (twoFirst == "tt") {
                breakpoint += context.nextInstruction->size();
            }
            else if (twoFirst == "t ") {
                try {
                    breakpoint = stoi(command.substr(2), 0, 16);
                } catch (std::exception& e) {
                    std::cerr << "Not a valid value: " << e.what() << std::endl;
                }
            }
            if (context.breakpoints.find(breakpoint) == context.breakpoints.end()) {
                context.breakpoints.insert(breakpoint);
                output << "Breakpoint inserted at address " << breakpoint << std::endl;
            }
            else {
                context.breakpoints.erase(breakpoint);
                output << "Breakpoint removed at address " << breakpoint << std::endl;
            }
            std::ofstream file(context.fileName);
            if (file) {
                for (Long breakpoint : context.breakpoints) {
                    file << breakpoint << " ";
                }
            }
        }
        else if (command == "w") {
            context.watchMode = !context.watchMode;
            output << "Watch mode " << (context.watchMode ? "on" : "off") << std::endl;
        }
        else if (command == "s") {
            output << "Switched contexts" << std::endl;
            printState(otherState, otherContext);
            return awaitCommand(otherContext, otherState, context, state);
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
                context.inspectedAddress = stoi(command, 0, 16);
                output << "Inspecting address " << context.inspectedAddress << std::endl;
                context.watchMode = false;
            } catch (std::exception& e) {
                error << "Not a valid address: " << e.what() << std::endl;
            }
        }

        return false;
    }

    template<typename State>
    void printState(const State& state, Context& context)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), context.stepMode ? context.debugColor : Red);
        state.printRegisters(output) << std::endl;
        output << context.nextInstruction->opcodeToString() << std::endl;
        output << state.readProgramByte() << ": ";
        output << context.nextInstruction->toString() << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
    }

    template<typename State>
    void setColor(const State& state, const Context& context, Long address)
    {
        bool breakpoint = context.breakpoints.find(address) != context.breakpoints.end();
        bool executing = address >= state.getProgramAddress() && address < state.getProgramAddress() + context.nextInstruction->size();
        Color color = DefaultColor;
        if (breakpoint && executing) {
            color = Blue;
        }
        else if (breakpoint) {
            color = Red;
        }
        else if (executing) {
            color = context.debugColor;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void printMemory(const CPU::State& cpuState, const Context& cpuContext, const SPC::State& spcState, const Context& spcContext)
    {
        Long startCpuAddress = cpuContext.watchMode ? cpuState.getProgramAddress() : cpuContext.inspectedAddress;
        Long startSpcAddress = spcContext.watchMode ? spcState.getProgramAddress() : spcContext.inspectedAddress;

        size_t cpuMemorySize = cpuState.getMemorySize();
        size_t spcMemorySize = spcState.getMemorySize();

        output << "           0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f"
            << "              0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        Long cpuAddress = startCpuAddress - std::bitset<8>(startCpuAddress).to_ulong();
        Long spcAddress = startSpcAddress - std::bitset<8>(startSpcAddress).to_ulong();


        for (int i = 0; i < 16; ++i) {
            if (cpuAddress < cpuMemorySize) {
                Byte bank = Byte(cpuAddress >> 16);
                Word lowAddress(cpuAddress);
                lowAddress = Word(lowAddress >> 4);
                output << bank << ':' << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && cpuAddress < cpuMemorySize; ++j) {
                    setColor(cpuState, cpuContext, cpuAddress);
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
                    setColor(spcState, spcContext, spcAddress);
                    output << spcState.getMemory(Word(spcAddress++)) << ' ';
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DefaultColor);
                }
            }

            output << std::endl;
        }
    }

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

    Debugger::Context cpuContext("cpu.txt", Green, cpuOpcodeMap.getNextInstruction(cpuState));
    Debugger::Context spcContext("spc.txt", Purple, spcOpcodeMap.getNextInstruction(spcState));

    const bool resumeLast = true;

    if (resumeLast) {
        for (Debugger::Context* context : { &cpuContext, &spcContext }) {
            std::ifstream contextFile(context->fileName);
            if (contextFile) {
                std::string breakpointString;
                while (std::getline(contextFile, breakpointString, ' ')) {
                    Long breakpoint = std::stoi(breakpointString, 0, 16);
                    output << "Read breakpoint: " << breakpoint << " from " << context->fileName << std::endl;
                    context->breakpoints.insert(breakpoint);
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
        if (cycleCount == nextCpu) {
            Instruction* instruction = cpuOpcodeMap.getNextInstruction(cpuState);

            if (cpuContext.stepMode) {
                output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                for (const Debugger::Context& context : { cpuContext, spcContext }) {
                    if (!context.breakpoints.empty()) {
                        output << "Breakpoints:";
                        for (Long breakpoint : context.breakpoints) {
                            output << " " << breakpoint;
                        }
                        output << std::endl;
                    }
                }
                debugger.printMemory(cpuState, cpuContext, spcState, spcContext);
            }

            if (int cycles = debugger.executeNext(instruction, cpuState, cpuContext, cycleCount, spcState, spcContext)) {
                nextCpu += cycles * 8;
                for (int i = 0; i < 4; ++i) {
                    spcState.getMemory(Byte(0xf4 + i)) = cpuState.getMemory(0x2140 + i);
                }
                cpuContext.nextInstruction = cpuOpcodeMap.getNextInstruction(cpuState);
            }
            else {
                continue;
            }
        }

        if (cycleCount == nextSpc) {
            Instruction* instruction = spcOpcodeMap.getNextInstruction(spcState);

            if (spcContext.stepMode) {
                output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                for (const Debugger::Context& context : { cpuContext, spcContext }) {
                    if (!context.breakpoints.empty()) {
                        output << "Breakpoints:";
                        for (Long breakpoint : context.breakpoints) {
                            output << " " << breakpoint;
                        }
                        output << std::endl;
                    }
                }
                debugger.printMemory(cpuState, cpuContext, spcState, spcContext);
            }

            if (int cycles = debugger.executeNext(instruction, spcState, spcContext, cycleCount, cpuState, cpuContext)) {
                nextSpc += cycles * 16;
                for (int i = 0; i < 4; ++i) {
                    *cpuState.getMemoryPointer(Long(0x2140 + i)) = spcState.getMemory(Byte(0xf4 + i));
                }
                spcContext.nextInstruction = spcOpcodeMap.getNextInstruction(spcState);
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
