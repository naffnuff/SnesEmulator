#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"

#include "Video.h"

class Debugger
{
public:
#ifdef _WIN32
    enum Color
    {
        Red = FOREGROUND_RED,
        Green = FOREGROUND_GREEN,
        Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
        Blue = FOREGROUND_BLUE,
        Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
        Cyan = FOREGROUND_BLUE | FOREGROUND_GREEN,
        DefaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    };
    void setOutputColor(Color color, bool bright)
    {
        int effectiveColor = color;
        if (bright) {
            effectiveColor |= FOREGROUND_INTENSITY;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), effectiveColor);
    }
#else
    enum Color
    {
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        Cyan = 36,
        DefaultColor = 0
    };
    void setOutputColor(Color color, bool bright)
    {
        output << "\33[" << color;
        if (bright) {
            output << ";" << 1;
        }
        output << "m";
    }
#endif

    class Context
    {
    public:
        Context(std::string fileName, Color debugColor)
            : fileName(fileName)
            , debugColor(debugColor)
        {
        }
        
        Context(const Context&) = delete;
        Context& operator=(const Context&) = delete;

        void addKnownAddress(Long address)
        {
            knownAddresses[++lastKnownAddressIndex] = address;
        }

        Long getLastKnownAddress() const
        {
            return knownAddresses[lastKnownAddressIndex];
        }

        void printAddressHistory(std::ostream& output)
        {
            output << "Address history:" << std::endl;
            for (Byte i = lastKnownAddressIndex; i != Byte(lastKnownAddressIndex - 10); --i) {
                output << knownAddresses[i] << std::endl;
            }
        }

        std::array<Long, 0x100> knownAddresses;
        Byte lastKnownAddressIndex = 0;

        std::string fileName;
        Long inspectedAddress = 0;
        bool watchMode = true;
        bool stepMode = false;
        Color debugColor;
        std::set<Long> breakpoints;
        const Instruction* nextInstruction;
    };

    Debugger(std::ostream& output, std::istream& input, std::ostream& error, uint64_t& cycleCount, bool& running)
        : output(output)
        , input(input)
        , error(error)
        , cycleCount(cycleCount)
        , running(running)
    {
    }

    Debugger(const Debugger&) = delete;
    Debugger& operator=(const Debugger&) = delete;

    template<typename State>
    void loadBreakpoints(Context& context, State& state)
    {
        std::ifstream contextFile(context.fileName);
        if (contextFile) {
            std::string breakpointString;
            while (std::getline(contextFile, breakpointString, ' ')) {
                Long breakpoint = std::stoi(breakpointString, 0, 16);
                output << "Read breakpoint: " << breakpoint << " from " << context.fileName << std::endl;
                toggleBreakpoint(context, state, breakpoint);
            }
        }
    }

    template<typename State>
    void toggleBreakpoint(Context& context, State& state, Long breakpoint)
    {
        MemoryLocation* memory = state.getMemoryLocation(breakpoint);
        if (memory->breakpoint == nullptr) {
            memory->breakpoint = [this, &context, breakpoint]() {
                context.stepMode = true;
                setOutputColor(Red, true);
                output << "Breakpoint hit @ " << breakpoint << std::endl;
                setOutputColor(DefaultColor, false);
            };
            context.breakpoints.insert(breakpoint);
            output << "Breakpoint inserted at address " << breakpoint << std::endl;
        }
        else {
            memory->breakpoint = nullptr;
            context.breakpoints.erase(breakpoint);
            output << "Breakpoint removed at address " << breakpoint << std::endl;
        }
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
        } else if (command == "h") {
            output
                << "Commands:"
                << "[return]: step into next instruction" << std::endl
                << "n: inspect next memory page" << std::endl
                << "p: inspect previous memory page" << std::endl
                << "i: inspect operand address" << std::endl
                << "r: toggle run context" << std::endl
                << "rr: run all contexts" << std::endl
                << "q: reset" << std::endl
                << "t: toggle breakpoint at current Program Counter address" << std::endl
                << "tt: toggle breakpoint at next Program Counter address" << std::endl
                << "t [hex]: toogle breakpoint at address [hex]" << std::endl
                << "clear: clear all breakpoints" << std::endl
                << "w: watch executing program memory" << std::endl
                << "[hex]: inspect memory page containing address [hex]" << std::endl
                << "v [hex]: inspect video memory containing address [hex]" << std::endl
                << "[p|s|a|x|y|d|f]=[hex]: set register to [hex]" << std::endl
                << "[a]=[hex]: set address [a] to [hex]" << std::endl
                << "s: switch contexts" << std::endl;
        } else if (command == "n") {
            context.watchMode = false;
            context.inspectedAddress += (1 << 8);
        } else if (command == "p") {
            context.watchMode = false;
            context.inspectedAddress -= (1 << 8);
        } else if (command[0] == 'r') {
            if (command == "rr") {
                context.stepMode = false;
                otherContext.stepMode = false;
            } else {
                context.stepMode = !context.stepMode;
                if (context.stepMode) {
                    output << "Step mode" << std::endl;
                } else {
                    output << "Run mode" << std::endl;
                }
            }
            if (!context.stepMode && !otherContext.stepMode) {
                output << "All running" << std::endl;
                output << "Snip" << std::endl;
                startTime = clock();
            }
            return !context.stepMode;
        } else if (command == "i") {
            output << "Inspect not implemented" << std::endl;
        } else if (command == "q") {
            output << "Reset" << std::endl;
            running = false;
        } else if (command == "clear") {
            for (Long address : context.breakpoints) {
                state.getMemoryLocation(address)->breakpoint = nullptr;
            }
            context.breakpoints.clear();
            output << "Cleared context " << context.fileName << std::endl;
            std::ofstream file(context.fileName);
        } else if (command[0] == 't') {
            Long breakpoint = state.getProgramAddress();
            std::string twoFirst = command.substr(0, 2);
            if (twoFirst == "tt") {
                breakpoint += context.nextInstruction->size();
            } else if (twoFirst == "t ") {
                try {
                    breakpoint = stoi(command.substr(2), 0, 16);
                } catch (std::exception& e) {
                    std::cerr << "Not a valid value: " << e.what() << std::endl;
                }
            }
            toggleBreakpoint(context, state, breakpoint);
            std::ofstream file(context.fileName);
            if (file) {
                for (Long breakpoint : context.breakpoints) {
                    file << breakpoint << " ";
                }
            }
        }
        else if (command[0] == 'v') {
            try {
                inspectedVideoMemory = stoi(command.substr(2), 0, 16);
            } catch (std::exception& e) {
                std::cerr << "Not a valid value: " << e.what() << std::endl;
            }
        }
        else if (command == "w") {
            context.watchMode = !context.watchMode;
            output << "Watch mode " << (context.watchMode ? "on" : "off") << std::endl;
        } else if (command == "s") {
            output << "Switched contexts" << std::endl;
            printState(otherState, otherContext);
            return awaitCommand(otherContext, otherState, context, state);
        } else if (command.size() > 1 && command[1] == '=') {
            try {
                Word value = (Word)stoi(command.substr(2), 0, 16);
                output << "Setting register " << command[0] << "=" << value << std::endl;
                state.setRegisterDebug(command[0], value);
            } catch (std::exception& e) {
                error << "Not a valid address: " << e.what() << std::endl;
            }
        } else if (command.find('=') != std::string::npos) {
            size_t pos = command.find('=');
            try {
                output << "Address: " << command.substr(0, pos) << ", value: " << command.substr(pos + 1) << std::endl;
                Long address = stoi(command.substr(0, pos), 0, 16);
                Byte value = (Byte)stoi(command.substr(pos + 1), 0, 16);
                output << "Setting address " << address <<
                    "=" << value << std::endl;
                state.getMemoryLocation(address)->setValue(value);
            } catch (std::exception& e) {
                error << "Not valid: " << command.substr(0, pos) << " or " << command.substr(pos + 1) << ": " << e.what() << std::endl;
            }
        } else {
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
    void printRegisters(const State& state, Context& context)
    {
        setOutputColor(context.debugColor, true);
        state.printRegisters(output) << std::endl;
        setOutputColor(DefaultColor, false);
    }

    template<typename State>
    void printState(const State& state, Context& context)
    {
        setOutputColor(context.stepMode ? context.debugColor : Red, true);
        state.printRegisters(output) << std::endl;
        output << context.nextInstruction->opcodeToString() << std::endl;
        output << state.readProgramByte() << ": ";
        output << context.nextInstruction->toString() << std::endl;
        setOutputColor(DefaultColor, false);
    }

    template<typename State>
    void setColor(const State& state, const Context& context, Long address, const MemoryLocation& memory)
    {
        Color color = DefaultColor;
        bool bright = false;
        if (memory.getApplicationCount() > 0) {
            color = Cyan;
        }
        else if (memory.isMirror()) {
            color = Yellow;
        }
        //else if (memory.getType() == MemoryLocation::Mapped) {
        //    color = Green;
        //}
        else if (memory.getType() == MemoryLocation::ReadOnly) {
            color = Blue;
            //bright = true;
        }
        else if (memory.getType() == MemoryLocation::ReadWrite) {
            color = Red;
        }
        else if (memory.getType() == MemoryLocation::WriteOnly) {
            color = Magenta;
        }
        bool executing = address >= state.getProgramAddress() && address < state.getProgramAddress() + context.nextInstruction->size();
        if (memory.breakpoint && executing) {
            color = Cyan;
            bright = true;
        } else if (memory.breakpoint) {
            color = Red;
            bright = true;
        } else if (executing) {
            color = context.debugColor;
            bright = true;
        }
        if (color != DefaultColor) {
            setOutputColor(color, bright);
        }
    }

    void printMemory(const CPU::State& cpuState, const Context& cpuContext, const SPC::State& spcState, const Context& spcContext, Video& video)
    {
        setOutputColor(DefaultColor, false);
        int oamAddress = inspectedVideoMemory & 0xFF80;
        int oamAuxAddress = oamAddress / 8;
        int oamAuxOffset = oamAddress % 8;
        for (int i = 0; i < 32; ++i) {
            Video::Object object = video.readObject(i);
            output << "size: " << video.getObjectSize(object.size);
            output << ", x: " << object.x;
            output << ", y: " << object.y;
            output << ", tile: " << object.tileIndex;
            output << ", name: " << object.nameTable;
            output << ", palette: " << object.palette;
            output << ", priority: " << object.priority;
            output << ", horizontalFlip: " << object.horizontalFlip;
            output << ", verticalFlip: " << object.verticalFlip;
            output << std::endl;
        }

        Long startCpuAddress = cpuContext.watchMode ? cpuState.getProgramAddress() : cpuContext.inspectedAddress;
        Long startSpcAddress = spcContext.watchMode ? spcState.getProgramAddress() : spcContext.inspectedAddress;

        size_t cpuMemorySize = cpuState.getMemorySize();
        size_t spcMemorySize = spcState.getMemorySize();

        output << "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f"
            << "             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        Long cpuAddress = startCpuAddress & 0xFFFF00;
        Long spcAddress = startSpcAddress & 0xFFFF00;


        for (int i = 0; i < 16; ++i) {
            if (cpuAddress < cpuMemorySize) {
                Byte bank = Byte(cpuAddress >> 16);
                uint16_t lowAddress(cpuAddress);
                lowAddress = lowAddress >> 4;
                output << bank << ':' << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && cpuAddress < cpuMemorySize; ++j) {
                    const MemoryLocation& memory = cpuState.getMemory(cpuAddress);
                    setColor(cpuState, cpuContext, cpuAddress++, memory);
                    output << memory << ' ';
                    setOutputColor(DefaultColor, false);
                }
            }

            output << "     ";

            if (spcAddress < spcMemorySize) {
                uint16_t lowAddress(spcAddress);
                lowAddress = lowAddress >> 4;
                output << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && spcAddress < spcMemorySize; ++j) {
                    const MemoryLocation& memory = spcState.getMemory(spcAddress);
                    setColor(spcState, spcContext, spcAddress++, memory);
                    output << memory << ' ';
                    setOutputColor(DefaultColor, false);
                }
            }

            output << std::endl;
        }
    }

    void printBreakpoints(const Context& cpuContext, const Context& spcContext) const
    {
        /*for (const Debugger::Context* context : { &cpuContext, &spcContext }) {
            if (!context->breakpoints.empty()) {
                output << "Breakpoints:";
                for (Long breakpoint : context->breakpoints) {
                    output << " " << breakpoint;
                }
                output << std::endl;
            }
        }*/
    }

    void printClockSpeed() const
    {
        std::time_t endTime = clock();
        output << "Snap" << std::endl;
        double elapsedSeconds = double(endTime - startTime) / CLOCKS_PER_SEC;
        output << "Time delta=" << elapsedSeconds << std::endl;
        output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
    }

    void printMemoryRegister(bool write, Byte value, Word address, const std::string& info)
    {
        setOutputColor(Debugger::Yellow, true);
        output << (write ? "Write " : "Read ") << value << " (" << std::bitset<8>(value) << ") @ " << address << " (" << info << "), " << cycleCount << std::endl;
        setOutputColor(Debugger::DefaultColor, false);
    }

    std::time_t startTime;

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;
    uint64_t& cycleCount;
    bool& running;
    Word inspectedVideoMemory = 0x0;

};
