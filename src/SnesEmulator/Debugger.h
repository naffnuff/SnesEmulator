#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

#include "Common/System.h"

#include "WDC65816/CpuState.h"
#include "SPC700/SpcState.h"

#include "Instruction.h"

#include "VideoProcessor.h"
#include "VideoRegisters.h"
#include "VideoDebugger.h"

#include "AudioRegisters.h"

template<typename State>
struct Breakpoint
{
    typename State::AddressType address;
    uint64_t applicationCount = 0;
    int argumentValue = -1;

    bool operator<(const Breakpoint& breakpoint) const
    {
        return address < breakpoint.address;
    }
};

template<typename State>
inline std::ostream& operator<<(std::ostream& o, const Breakpoint<State>& b)
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
private:
    class OutputColorVisitor : public LocationVisitor
    {
    public:
        void visit(const InvalidLocation&) override
        {
            color = System::DefaultColor;
        }

        void visit(const ReadOnlyMemory& location) override
        {
            color = location.getApplicationCount() > 0 ? System::Cyan : System::Blue;
        }

        void visit(const ReadWriteMemory& location) override
        {
            color = location.getApplicationCount() > 0 ? System::Cyan : System::Red;
        }

        void visit(const ReadRegister&) override
        {
            color = System::Magenta;
        }

        void visit(const WriteRegister&) override
        {
            color = System::Green;
        }

        void visit(const ReadWriteRegister&) override
        {
            color = System::Yellow;
        }

        void visit(const BootRomLocation& location) override
        {
            if (location.getApplicationCount() > 0) {
                color = System::Cyan;
            } else if (location.bootRomDataEnabled) {
                color = System::Blue;
            } else {
                color = System::Red;
            }
        }

        System::Color color = System::DefaultColor;
    };

public:
    class ContextBase
    {
    public:
        ContextBase(std::string fileName, System::Color debugColor, Debugger& debugger)
            : fileName(fileName)
            , debugColor(debugColor)
            , debugger(debugger)
        {
        }

        ContextBase() = delete;
        ContextBase(const ContextBase&) = delete;
        ContextBase& operator=(const ContextBase&) = delete;

        virtual ~ContextBase()
        {
        }

        void setPaused(bool paused)
        {
            if (paused == stepMode) {
                return;
            }
            stepMode = paused;
            if (paused) {
                if (debugger.videoProcessor.rendererLock.owns_lock()) {
                    debugger.videoProcessor.rendererLock.unlock();
                    unlockedMutex = true;
                }
                if (debugger.videoProcessor.rendererRunner.fullscreen) {
                    debugger.videoProcessor.renderer.toggleFullscreenRequested = true;
                }
                debugger.videoProcessor.renderer.focusWindow(false);
                System::focusConsoleWindow();
            }
            else {
                if (unlockedMutex) {
                    debugger.videoProcessor.rendererLock.lock();
                    unlockedMutex = false;
                }
                debugger.videoProcessor.renderer.focusWindow(true);
            }
        }

        bool isPaused() const
        {
            return stepMode;
        }

        Debugger& debugger;
        std::string fileName;
        Long inspectedAddress = 0;
        bool watchMode = true;
        System::Color debugColor;
        const Instruction* nextInstruction;
    private:
        bool stepMode = false;
        bool unlockedMutex = false;
    };

    template<typename State>
    class Context : public ContextBase
    {
    public:
        using ContextBase::ContextBase;

        typedef typename State::AddressType AddressType;

        ~Context() override
        {
        }

        void addKnownAddress(AddressType address)
        {
            knownAddresses[++lastKnownAddressIndex] = address;
        }

        AddressType getLastKnownAddress() const
        {
            return knownAddresses[lastKnownAddressIndex];
        }

        AddressType getPreviousAddress(AddressType currentAddress) const
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

        Byte lastKnownAddressIndex = 0;
        std::array<AddressType, 0x100> knownAddresses;
        std::set<Breakpoint<State>> breakpoints;
    };

    Debugger(std::ostream& output, std::istream& input, std::ostream& error, Video::Registers& videoRegisters, Audio::Registers& audioRegisters, uint64_t& cycleCount, bool& running)
        : output(output)
        , input(input)
        , error(error)
        , videoRegisters(videoRegisters)
        , videoProcessor(videoRegisters.processor)
        , audioRegisters(audioRegisters)
        , audioProcessor(audioRegisters.processor)
        , cycleCount(cycleCount)
        , running(running)
    {
    }

    Debugger(const Debugger&) = delete;
    Debugger& operator=(const Debugger&) = delete;

    template<typename State>
    void loadBreakpoints(Context<State>& context, State& state)
    {
        std::ifstream contextFile(context.fileName);
        if (contextFile) {
            std::string breakpointString;
            while (std::getline(contextFile, breakpointString, ' ')) {
                int applicationCountIndex = int(breakpointString.find('#'));
                int argumentValueIndex = int(breakpointString.find(':'));
                Breakpoint<State> breakpoint;
                int index = min(applicationCountIndex, argumentValueIndex) - 1;
                breakpoint.address = typename State::AddressType(std::stoi(breakpointString.substr(1, index), 0, 16));
                if (applicationCountIndex >= 0) {
                    breakpoint.applicationCount = std::stoull(breakpointString.substr(applicationCountIndex + 1));
                }
                if (argumentValueIndex >= 0) {
                    breakpoint.argumentValue = std::stoi(breakpointString.substr(argumentValueIndex + 1), 0, 16);
                }
                output << "Read breakpoint: " << breakpoint << " from " << context.fileName << std::endl;
                MemoryAccess access = state.getMemoryAccess(typename State::AddressType(breakpoint.address));
                toggleBreakpoint(context, state, access, breakpoint);
            }
        }
    }

    template<typename State>
    void toggleBreakpoint(Context<State>& context, State& state, LocationAccess& access, const Breakpoint<State>& breakpoint)
    {
        if (access.hasBreakpoint()) {
            if (access.setBreakpoint(nullptr)) {
                context.breakpoints.erase(breakpoint);
                output << "Breakpoint removed at address " << breakpoint.address << std::endl;
            }
            else {
                output << "Breakpoint not allowed at address " << breakpoint.address << std::endl;
            }
        } else {
            bool success = access.setBreakpoint([this, &context, &state, breakpoint](Location::Operation operation, Byte value, uint64_t applicationCount) {
                bool printInstruction = false;
                if (operation == Location::Apply && (breakpoint.applicationCount == 0 || breakpoint.applicationCount == applicationCount)) {
                    output << "Apply: Breakpoint hit " << breakpoint << "#" << applicationCount << std::endl;
                    context.setPaused(true);
                } else if (operation == Location::Read && (breakpoint.argumentValue == -1 || breakpoint.argumentValue == value)) {
                    output << "Read: Breakpoint hit @ " << breakpoint << ":" << value;
                    context.setPaused(true);
                    printInstruction = true;
                }
                else if (operation == Location::Write && (breakpoint.argumentValue == -1 || breakpoint.argumentValue == value)) {
                    output << "Write: Breakpoint hit " << breakpoint << ":" << value;
                    context.setPaused(true);
                    printInstruction = true;
                }
                if (printInstruction) {
                    typename State::AddressType programAddress = state.getProgramAddress();
                    state.setProgramAddress(context.getLastKnownAddress());
                    output << " while executing ";
                    {
                        System::ScopedOutputColor outputColor(output, context.isPaused() ? context.debugColor : System::Red, true);
                        output << context.nextInstruction->toString();
                    }
                    output << " @" << context.getLastKnownAddress() << std::endl;
                    state.setProgramAddress(programAddress);
                }
            });
            if (success) {
                context.breakpoints.insert(breakpoint);
                output << "Breakpoint inserted: " << breakpoint << std::endl;
            } else {
                    output << "Breakpoint not allowed at address " << breakpoint.address << std::endl;
                }
        }
    }

    template<typename State, typename OtherState>
    bool awaitCommand(Context<State>& context, State& state, Context<OtherState>& otherContext, OtherState& otherState)
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
                << "v [hex]: inspect videoProcessor memory containing address [hex]" << std::endl
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
            videoRegisters.reset();
            audioRegisters.reset();
        }
        else if (command == "qr") {
            output << "Soft reset and run" << std::endl;
            state.reset();
            otherState.reset();
            videoRegisters.reset();
            audioRegisters.reset();
            context.setPaused(false);
            otherContext.setPaused(false);
            startTime = clock();
        }
        else if (command == "qq") {
            output << "Hard reset" << std::endl;
            running = false;
        }
        else if (command == "clear") {
            for (const Breakpoint<State>& breakpoint : context.breakpoints) {
                state.getMemoryAccess(breakpoint.address).setBreakpoint(nullptr);
            }
            context.breakpoints.clear();
            output << "Cleared context " << context.fileName << std::endl;
            std::ofstream file(context.fileName);
        }
        else if (command[0] == 't') {
            Breakpoint<State> breakpoint;
            breakpoint.address = state.getProgramAddress();
            if (command.substr(0, 3) == "ttt") {
                breakpoint.address = context.getPreviousAddress(breakpoint.address);
                breakpoint.applicationCount = state.getMemory().getApplicationCount(breakpoint.address);
            }
            else if (command.substr(0, 2) == "tt") {
                breakpoint.address += context.nextInstruction->size();
                breakpoint.applicationCount = state.getMemory().getApplicationCount(breakpoint.address);
            }
            else if (command.substr(0, 2) == "t ") {
                try {
                    breakpoint.address = stoi(command.substr(2), 0, 16);
                } catch (std::exception& e) {
                    std::cerr << "Not a valid value: " << e.what() << std::endl;
                }
            }
            MemoryAccess access = state.getMemoryAccess(breakpoint.address);
            toggleBreakpoint(context, state, access, breakpoint);
            std::ofstream file(context.fileName);
            if (file) {
                for (const Breakpoint<State>& breakpoint : context.breakpoints) {
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
                typename State::AddressType address = stoi(command.substr(0, pos), 0, 16);
                Byte value = (Byte)stoi(command.substr(pos + 1), 0, 16);
                output << "Setting address " << address <<
                    "=" << value << std::endl;
                state.getMemory().writeByte(value, address);
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
    void printRegisters(const State& state, Context<State>& context)
    {
        System::ScopedOutputColor outputColor(output, context.debugColor, true);
        state.printRegisters(output) << std::endl;
    }

    template<typename State>
    void printState(State& state, Context<State>& context)
    {
        System::ScopedOutputColor outputColor(output, context.isPaused() ? context.debugColor : System::Red, true);
        state.printRegisters(output) << std::endl;
        output << context.nextInstruction->opcodeToString() << std::endl;
        output << state.inspectProgramByte() << ": ";
        output << context.nextInstruction->toString();
        output << " #" << state.getMemory().getApplicationCount(state.getProgramAddress()) << std::endl;
    }

    template<typename State>
    void setColor(const State& state, const Context<State>& context, typename State::AddressType address, const LocationAccess& access, System::ScopedOutputColor& outputColor)
    {
        System::Color color = System::DefaultColor;
        bool bright = false;
        bool executing = address >= state.getProgramAddress() && address < state.getProgramAddress() + context.nextInstruction->size();
        if (access.hasBreakpoint() && executing) {
            color = System::Cyan;
            bright = true;
        } else if (access.hasBreakpoint()) {
            color = System::Red;
            bright = true;
        } else if (executing) {
            color = context.debugColor;
            bright = true;
        } else {
            OutputColorVisitor colorVisitor;
            access.accept(colorVisitor);
            color = colorVisitor.color;
        }
        if (color != System::DefaultColor) {
            outputColor.set(color, bright);
        }
    }

    void printMemory(CPU::State& cpuState, const Context<CPU::State>& cpuContext, SPC::State& spcState, const Context<SPC::State>& spcContext, Video::Processor& videoProcessor)
    {
        //System::setOutputColor(output, System::DefaultColor, false);
        int oamAddress = inspectedVideoMemory & 0xFF80;
        int oamAuxAddress = oamAddress / 8;
        int oamAuxOffset = oamAddress % 8;
        /*for (int i = OamViewer::firstObjectIndex; i < OamViewer::firstObjectIndex + 32; ++i) {
            Video::Object object = videoProcessor.readObject(i);
            output << i << ": ";
            output << " size: " << videoProcessor.getObjectSize(object.sizeSelect);
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

        output << "OAM start address: " << videoRegisters.oamStartAddress << std::endl;
        output << "OAM current address: " << videoProcessor.oam.address << std::endl;
        output << "Video port control: " << videoRegisters.videoPortControl << std::endl;
        //output << "VRAM start address: " << videoRegisters.vramStartAddress << std::endl;
        output << "VRAM current address: " << videoProcessor.vram.address << std::endl;
        output << "CPU bus: " << cpuState.getMemory().bus << std::endl;

        output << "   Vol L Vol R Pitch Src      AR DR SR SL  Gain Mode               Lvl Env Out" << std::endl;
        for (int i = 0; i < audioProcessor.voices.size(); ++i) {
            const Audio::Processor::Voice& voice = audioProcessor.voices[i];
            output << i << ": " << std::left << std::setfill(' ') << std::setw(4) << +voice.leftVolume
                << "  " << std::setw(4) << +voice.rightVolume
                << "  " << voice.pitch
                << "  " << voice.sourceNumber
                << "  " << voice.envelopeTypeToString()
                << " " << voice.attackRate
                << " " << voice.decayRate
                << " " << voice.sustainRate
                << " " << voice.sustainLevel
                << "  " << std::left << std::setfill(' ') << std::setw(22) << voice.gainModeToString()
                << "  " << voice.gainLevel
                << "  " << voice.envelope
                << "  " << +voice.output
                << std::endl;
        }
        output << "Main Vol    Echo Vol    Key On    Key Off   R M E Gen Src End   Echo FB   Pitch Mod Noise On  Echo On   Dir ER  Delay" << std::endl;
        output << std::left << std::setfill(' ') << std::setw(4) << +audioProcessor.mainVolumeLeft
            << "  " << std::setw(4) << +audioProcessor.mainVolumeRight
            << "  " << std::setw(4) << +audioProcessor.echoVolumeLeft
            << "  " << std::setw(4) << +audioProcessor.echoVolumeRight
            << "  " << audioProcessor.keyOn
            << "  " << audioProcessor.keyOff
            << "  " << audioProcessor.reset
            << " " << audioProcessor.mute
            << " " << audioProcessor.echoOff
            << " " << audioProcessor.noiseGeneratorClock
            << "  " << audioProcessor.sourceEndBlock
            << "  " << std::setw(8) << +audioProcessor.echoFeedback
            << "  " << audioProcessor.pitchModulation
            << "  " << audioProcessor.noiseOn
            << "  " << audioProcessor.echoOn
            << "  " << audioProcessor.sourceDirectoryOffset
            << "  " << audioProcessor.echoRegionOffset
            << "  " << audioProcessor.echoDelay
            << std::endl;
        output << "Filter coefficients:";
        for (int i = 0; i < audioProcessor.coefficients.size(); ++i) {
            output << "  " << audioProcessor.coefficients[i];
        }

        output << std::endl << std::endl;

        output << "          0     1     2     3     4     5     6     7" << std::endl
            << "          8     9     a     b     c     d     e     f"
            << "                0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        int lastVramLowAddress = -1;
        int vramAddress = inspectedVideoMemory & 0xFF80;
        Byte dspAddress = 0;
        for (int i = 0; i < 16; ++i) {
            if (vramAddress < videoProcessor.vram.size) {
                uint16_t lowAddress(vramAddress);
                lowAddress = lowAddress >> 4;
                if (lastVramLowAddress != lowAddress) {
                    output << "   " << std::hex << std::right << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;
                }
                else {
                    output << "         ";
                }
                lastVramLowAddress = lowAddress;

                for (int j = 0; j < 8 && vramAddress < videoProcessor.vram.size; ++j) {
                    output << videoProcessor.vram.getByte(vramAddress, false) << ' ' << videoProcessor.vram.getByte(vramAddress, true) << ' ';
                    ++vramAddress;
                }
            }

            output << "     ";

            if (dspAddress < audioProcessor.dspMemory.size()) {
                uint16_t lowAddress(dspAddress);
                lowAddress = lowAddress >> 4;
                output << std::hex << std::right << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && dspAddress < audioProcessor.dspMemory.size(); ++j) {
                    MemoryAccess access(audioProcessor.dspMemory, dspAddress);
                    OutputColorVisitor colorVisitor;
                    access.accept(colorVisitor);
                    System::ScopedOutputColor outputColor(output, colorVisitor.color, false);
                    output << access << ' ';
                    ++dspAddress;
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
        Word spcAddress = startSpcAddress & 0xFFFF00;

        for (int i = 0; i < 16; ++i) {
            if (cpuAddress < cpuMemorySize) {
                Byte bank = Byte(cpuAddress >> 16);
                uint16_t lowAddress(cpuAddress);
                lowAddress = lowAddress >> 4;
                output << bank << ':' << std::hex << std::right << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && cpuAddress < cpuMemorySize; ++j) {
                    MemoryAccess access = cpuState.getMemoryAccess(cpuAddress);
                    System::ScopedOutputColor outputColor(output);
                    setColor(cpuState, cpuContext, cpuAddress, access, outputColor);
                    output << access << ' ';
                    ++cpuAddress;
                }
            }

            output << "     ";

            if (spcAddress < spcMemorySize) {
                uint16_t lowAddress(spcAddress);
                lowAddress = lowAddress >> 4;
                output << std::hex << std::right << std::setw(3) << std::setfill('0') << lowAddress << "x  " << std::dec;

                for (int j = 0; j < 16 && spcAddress < spcMemorySize; ++j) {
                    MemoryAccess access = spcState.getMemoryAccess(spcAddress);
                    System::ScopedOutputColor outputColor(output);
                    setColor(spcState, spcContext, spcAddress, access, outputColor);
                    if (spcAddress >= 0xffc0 && audioRegisters.bootRomDataEnabled) {
                        output << audioRegisters.bootRomData[spcAddress - 0xffc0] << ' ';
                    }
                    else {
                        output << access << ' ';
                    }
                    ++spcAddress;
                }
            }

            output << std::endl;
        }
    }

    void printBreakpoints(const Context<CPU::State>& cpuContext, const Context<SPC::State>& spcContext) const
    {
        printBreakpoints(cpuContext);
        printBreakpoints(spcContext);
    }

    template<typename State>
    void printBreakpoints(const Context<State>& context) const
    {
        if (!context.breakpoints.empty()) {
            output << "Breakpoints:";
            for (const Breakpoint<State>& breakpoint : context.breakpoints) {
                output << " " << breakpoint;
            }
            output << std::endl;
        }
    }

    void printClockSpeed() const
    {
        std::time_t endTime = clock();
        double elapsedSeconds = double(endTime - startTime) / CLOCKS_PER_SEC;
        output << "Time delta=" << elapsedSeconds << std::endl;
        output << "Speed is " << cycleCount / 1000000.0 / elapsedSeconds << " MHz (kind of)" << std::endl;
    }

    std::time_t startTime;

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;
    Video::Registers& videoRegisters;
    Video::Processor& videoProcessor;
    Audio::Registers& audioRegisters;
    Audio::Processor& audioProcessor;
    uint64_t& cycleCount;
    bool& running;
    Word inspectedVideoMemory = 0x0;

};
