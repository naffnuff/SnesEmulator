#pragma once

#include <iostream>
#include <algorithm>

#include "Common/System.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"
#include "SPC700/Audio.h"

#include "Video.h"
#include "VideoDebugger.h"
#include "Registers.h"

struct Breakpoint
{
    Long address;
    uint64_t applicationCount = 0;
    int argumentValue = -1;

    bool operator<(const Breakpoint& breakpoint) const
    {
        return address < breakpoint.address;
    }
};

inline std::ostream& operator<<(std::ostream& o, const Breakpoint& b)
{
    o << "@" << b.address;
    if (b.applicationCount > 0) {
        o << "#" << b.applicationCount;
    }
    if (b.argumentValue >= 0) {
        o << ":" << Byte(b.argumentValue);
    }
    return o;
}

class Debugger
{
public:
    class Context
    {
    public:
        Context(std::string fileName, System::Color debugColor, Debugger& debugger)
            : fileName(fileName)
            , debugColor(debugColor)
            , debugger(debugger)
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

        Long getPreviousAddress(Long currentAddress) const
        {
            for (Byte i = lastKnownAddressIndex; i != Byte(lastKnownAddressIndex - 0xff); --i) {
                if (knownAddresses[i] != currentAddress) {
                    return knownAddresses[i];
                }
            }
            return currentAddress;
        }

        void printAddressHistory(std::ostream& output)
        {
            output << "Address history:" << std::endl;
            for (Byte i = lastKnownAddressIndex; i != Byte(lastKnownAddressIndex - 10); --i) {
                output << knownAddresses[i] << std::endl;
            }
        }

        void setPaused(bool paused)
        {
            stepMode = paused;
            if (paused) {
                if (debugger.registers.video.rendererLock.owns_lock()) {
                    debugger.registers.video.rendererLock.unlock();
                    unlockedMutex = true;
                }
                if (debugger.registers.video.rendererRunner.fullscreen) {
                    debugger.registers.video.renderer.toggleFullscreenRequested = true;
                }
                debugger.registers.video.renderer.focusWindow(false);
                System::focusConsoleWindow();
            }
            else {
                if (unlockedMutex) {
                    debugger.registers.video.rendererLock.lock();
                    unlockedMutex = false;
                }
                debugger.registers.video.renderer.focusWindow(true);
            }
        }

        bool isPaused() const
        {
            return stepMode;
        }

        std::array<Long, 0x100> knownAddresses;
        Byte lastKnownAddressIndex = 0;

        Debugger& debugger;
        std::string fileName;
        Long inspectedAddress = 0;
        bool watchMode = true;
        System::Color debugColor;
        std::set<Breakpoint> breakpoints;
        const Instruction* nextInstruction;
    private:
        bool stepMode = false;
        bool unlockedMutex = false;
    };

    Debugger(std::ostream& output, std::istream& input, std::ostream& error, Registers& registers, SPC::Audio& audio, uint64_t& cycleCount, bool& running)
        : output(output)
        , input(input)
        , error(error)
        , registers(registers)
        , audio(audio)
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
                int applicationCountIndex = int(breakpointString.find('#'));
                int argumentValueIndex = int(breakpointString.find(':'));
                Breakpoint breakpoint;
                int index = min(applicationCountIndex, argumentValueIndex) - 1;
                breakpoint.address = std::stoul(breakpointString.substr(1, index), 0, 16);
                if (applicationCountIndex >= 0) {
                    breakpoint.applicationCount = std::stoull(breakpointString.substr(applicationCountIndex + 1));
                }
                if (argumentValueIndex >= 0) {
                    breakpoint.argumentValue = std::stoi(breakpointString.substr(argumentValueIndex + 1), 0, 16);
                }
                output << "Read breakpoint: " << breakpoint << " from " << context.fileName << std::endl;
                MemoryLocation* memory = state.getMemoryLocation(breakpoint.address);
                toggleBreakpoint(context, memory, breakpoint);
            }
        }
    }

    void toggleBreakpoint(Context& context, MemoryLocation* memory, const Breakpoint& breakpoint)
    {
        if (memory->hasBreakpoint()) {
            memory->setBreakpoint(nullptr);
            context.breakpoints.erase(breakpoint);
            output << "Breakpoint removed at address " << breakpoint.address << std::endl;
        }
        else {
            memory->setBreakpoint([this, &context, breakpoint](MemoryLocation::Operation operation, Byte value, uint64_t applicationCount) {
                if (operation == MemoryLocation::Apply && (breakpoint.applicationCount == 0 || breakpoint.applicationCount == applicationCount)) {
                    //output << "Frame: " << registers.frame << ", V counter: " << registers.vCounter << ", H counter: " << registers.hCounter << ", V blank: " << registers.vBlank << ", H blank: " << registers.hBlank << std::endl;
                    context.setPaused(true);
                    output << "Apply: Breakpoint hit " << breakpoint << std::endl;
                }
                /*else if (operation == MemoryLocation::Read) {
                    if (!context.stepMode) {
                        state.setProgramAddress(context.getLastKnownAddress());
                    }
                    context.stepMode = true;
                    output << "Read: Breakpoint hit @ " << breakpoint << std::endl;
                }*/
                else if (operation == MemoryLocation::Write && (breakpoint.argumentValue == -1 || breakpoint.argumentValue == value)) {
                    context.setPaused(true);
                    output << "Write: Breakpoint hit " << breakpoint << ":" << value << std::endl;
                    //output << value << std::endl;
                }
            });
            context.breakpoints.insert(breakpoint);
            output << "Breakpoint inserted: " << breakpoint << std::endl;
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
        }
        else if (command == "h") {
            output
                << "Commands:"
                << "[return]: step into next instruction" << std::endl
                << "n: inspect next memory page" << std::endl
                << "p: inspect previous memory page" << std::endl
                << "i: inspect operand address" << std::endl
                << "r: toggle run context" << std::endl
                << "rr: run all contexts" << std::endl
                << "q: soft reset" << std::endl
                << "qr: soft reset and run" << std::endl
                << "qq: hard reset" << std::endl
                << "t: toggle breakpoint at current Program Counter address" << std::endl
                << "tt: toggle breakpoint at next Program Counter address" << std::endl
                << "ttt: toggle breakpoint at last executed Program Counter address" << std::endl
                << "t [hex]: toogle breakpoint at address [hex]" << std::endl
                << "clear: clear all breakpoints" << std::endl
                << "w: watch executing program memory" << std::endl
                << "[hex]: inspect memory page containing address [hex]" << std::endl
                << "v [hex]: inspect video memory containing address [hex]" << std::endl
                << "[p|s|a|x|y|d|f]=[hex]: set register to [hex]" << std::endl
                << "[a]=[hex]: set address [a] to [hex]" << std::endl
                << "s: switch contexts" << std::endl;
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
                context.setPaused(false);
                otherContext.setPaused(false);
            }
            else {
                context.setPaused(!context.isPaused());
                if (context.isPaused()) {
                    output << "Step mode" << std::endl;
                }
                else {
                    output << "Run mode" << std::endl;
                }
            }
            if (!context.isPaused() && !otherContext.isPaused()) {
                output << "All running" << std::endl;
                output << "Snip" << std::endl;
                startTime = clock();
            }
            return !context.isPaused();
        }
        else if (command == "i") {
            output << "Inspect not implemented" << std::endl;
        }
        else if (command == "q") {
            output << "Soft reset" << std::endl;
            state.reset();
            otherState.reset();
            registers.reset();
            audio.reset();
        }
        else if (command == "qr") {
            output << "Soft reset and run" << std::endl;
            state.reset();
            otherState.reset();
            registers.reset();
            audio.reset();
            context.setPaused(false);
            otherContext.setPaused(false);
            startTime = clock();
        }
        else if (command == "qq") {
            output << "Hard reset" << std::endl;
            running = false;
        }
        else if (command == "clear") {
            for (const Breakpoint& breakpoint : context.breakpoints) {
                state.getMemoryLocation(breakpoint.address)->setBreakpoint(nullptr);
            }
            context.breakpoints.clear();
            output << "Cleared context " << context.fileName << std::endl;
            std::ofstream file(context.fileName);
        }
        else if (command[0] == 't') {
            Breakpoint breakpoint;
            breakpoint.address = state.getProgramAddress();
            MemoryLocation* memory = state.getMemoryLocation(breakpoint.address);
            if (command.substr(0, 3) == "ttt") {
                breakpoint.address = context.getPreviousAddress(breakpoint.address);
                memory = state.getMemoryLocation(breakpoint.address);
                breakpoint.applicationCount = memory->getApplicationCount();
            }
            else if (command.substr(0, 2) == "tt") {
                breakpoint.address += context.nextInstruction->size();
                memory = state.getMemoryLocation(breakpoint.address);
                breakpoint.applicationCount = memory->getApplicationCount();
            }
            else if (command.substr(0, 2) == "t ") {
                try {
                    breakpoint.address = stoi(command.substr(2), 0, 16);
                    memory = state.getMemoryLocation(breakpoint.address);
                } catch (std::exception& e) {
                    std::cerr << "Not a valid value: " << e.what() << std::endl;
                }
            }
            toggleBreakpoint(context, memory, breakpoint);
            std::ofstream file(context.fileName);
            if (file) {
                for (const Breakpoint& breakpoint : context.breakpoints) {
                    file << breakpoint << ' ';
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
    void printRegisters(const State& state, Context& context)
    {
        System::setOutputColor(output, context.debugColor, true);
        state.printRegisters(output) << std::endl;
        System::setOutputColor(output, System::DefaultColor, false);
    }

    template<typename State>
    void printState(const State& state, Context& context)
    {
        System::setOutputColor(output, context.isPaused() ? context.debugColor : System::Red, true);
        state.printRegisters(output) << std::endl;
        output << context.nextInstruction->opcodeToString() << std::endl;
        output << state.readProgramByte() << ": ";
        output << context.nextInstruction->toString();
        output << " #" << state.getMemory(state.getProgramAddress()).getApplicationCount() << std::endl;
        System::setOutputColor(output, System::DefaultColor, false);
    }

    template<typename State>
    void setColor(const State& state, const Context& context, Long address, const MemoryLocation& memory)
    {
        System::Color color = System::DefaultColor;
        bool bright = false;
        if (memory.getApplicationCount() > 0) {
            color = System::Cyan;
        }
        else if (memory.isMirror()) {
            color = System::Yellow;
        }
        //else if (memory.getType() == MemoryLocation::Mapped) {
        //    color = Green;
        //}
        else if (memory.getType() == MemoryLocation::ReadOnly) {
            color = System::Blue;
            //bright = true;
        }
        else if (memory.getType() == MemoryLocation::ReadWrite) {
            color = System::Red;
        }
        else if (memory.getType() == MemoryLocation::WriteOnly) {
            color = System::Magenta;
        }
        bool executing = address >= state.getProgramAddress() && address < state.getProgramAddress() + context.nextInstruction->size();
        if (memory.hasBreakpoint() && executing) {
            color = System::Cyan;
            bright = true;
        } else if (memory.hasBreakpoint()) {
            color = System::Red;
            bright = true;
        } else if (executing) {
            color = context.debugColor;
            bright = true;
        }
        if (color != System::DefaultColor) {
            System::setOutputColor(output, color, bright);
        }
    }

    void printMemory(const CPU::State& cpuState, const Context& cpuContext, const SPC::State& spcState, const Context& spcContext, Video& video)
    {
        System::setOutputColor(output, System::DefaultColor, false);
        int oamAddress = inspectedVideoMemory & 0xFF80;
        int oamAuxAddress = oamAddress / 8;
        int oamAuxOffset = oamAddress % 8;
        /*for (int i = OamViewer::firstObjectIndex; i < OamViewer::firstObjectIndex + 32; ++i) {
            Video::Object object = video.readObject(i);
            output << i << ": ";
            output << " size: " << video.getObjectSize(object.sizeSelect);
            output << ", x: " << object.x;
            output << ", y: " << object.y;
            output << ", tile: " << Byte(object.tileIndex);
            output << ", name: " << object.nameTable;
            output << ", palette: " << object.palette;
            output << ", priority: " << object.priority;
            output << ", horizontalFlip: " << object.horizontalFlip;
            output << ", verticalFlip: " << object.verticalFlip;
            output << std::endl;
        }*/

        output << "OAM start address: " << registers.oamStartAddress << std::endl;
        output << "OAM current address: " << registers.video.oam.address << std::endl;
        output << "Video port control: " << registers.videoPortControl << std::endl;
        //output << "VRAM start address: " << registers.vramStartAddress << std::endl;
        output << "VRAM current address: " << registers.video.vram.address << std::endl;
        output << "maxApplicationCount: " << MemoryLocation::maxApplicationCount << std::endl;

        output << "          0     1     2     3     4     5     6     7" << std::endl
            << "          8     9     a     b     c     d     e     f"
            << "                0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        int lastVramLowAddress = -1;
        int vramAddress = inspectedVideoMemory & 0xFF80;
        int dspAddress = 0;
        for (int i = 0; i < 16; ++i) {
            if (vramAddress < video.vram.size) {
                uint16_t lowAddress(vramAddress);
                lowAddress = lowAddress >> 4;
                if (lastVramLowAddress != lowAddress) {
                    output << "   " << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;
                }
                else {
                    output << "         ";
                }
                lastVramLowAddress = lowAddress;

                for (int j = 0; j < 8 && vramAddress < video.vram.size; ++j) {
                    output << video.vram.getByte(vramAddress, false) << ' ' << video.vram.getByte(vramAddress, true) << ' ';
                    ++vramAddress;
                }
            }

            output << "     ";

            if (dspAddress < audio.dspMemory.size()) {
                uint16_t lowAddress(dspAddress);
                lowAddress = lowAddress >> 4;
                output << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && dspAddress < audio.dspMemory.size(); ++j) {
                    Byte memory = audio.dspMemory[dspAddress++];
                    //setColor(spcState, spcContext, dspAddress++, memory);
                    output << memory << ' ';
                    //System::setOutputColor(output, System::DefaultColor, false);
                }
            }

            output << std::endl;
        }
        output << std::endl;

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
                    System::setOutputColor(output, System::DefaultColor, false);
                }
            }

            output << "     ";

            if (spcAddress < spcMemorySize) {
                uint16_t lowAddress(spcAddress);
                lowAddress = lowAddress >> 4;
                output << std::hex << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && spcAddress < spcMemorySize; ++j) {
                    const MemoryLocation& memory = spcState.getMemory(spcAddress);
                    setColor(spcState, spcContext, spcAddress, memory);
                    if (spcAddress >= 0xffc0 && audio.bootRomDataEnabled) {
                        output << audio.bootRomData[spcAddress - 0xffc0] << ' ';
                    }
                    else {
                        output << memory << ' ';
                    }
                    ++spcAddress;
                    System::setOutputColor(output, System::DefaultColor, false);
                }
            }

            output << std::endl;
        }
    }

    void printBreakpoints(const Context& cpuContext, const Context& spcContext) const
    {
        for (const Debugger::Context* context : { &cpuContext, &spcContext }) {
            if (!context->breakpoints.empty()) {
                output << "Breakpoints:";
                for (const Breakpoint& breakpoint : context->breakpoints) {
                    output << " " << breakpoint ;
                }
                output << std::endl;
            }
        }
    }

    void printClockSpeed() const
    {
        std::time_t endTime = clock();
        output << "Snap" << std::endl;
        double elapsedSeconds = double(endTime - startTime) / CLOCKS_PER_SEC;
        output << "Time delta=" << elapsedSeconds << std::endl;
        output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
    }

    std::time_t startTime;

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;
    Registers& registers;
    SPC::Audio& audio;
    uint64_t& cycleCount;
    bool& running;
    Word inspectedVideoMemory = 0x0;

};
