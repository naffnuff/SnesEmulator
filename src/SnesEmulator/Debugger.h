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
    if (b.applicationCount > 0)
    {
        o << "#" << b.applicationCount;
    }
    if (b.argumentValue >= 0)
    {
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
            color = Output::Color::Default;
        }

        void visit(const ReadOnlyMemory& location) override
        {
            color = location.getApplicationCount() > 0 ? Output::Color::Cyan : Output::Color::Blue;
        }

        void visit(const ReadWriteMemory& location) override
        {
            color = location.getApplicationCount() > 0 ? Output::Color::Cyan : Output::Color::Red;
        }

        void visit(const ReadRegister&) override
        {
            color = Output::Color::Magenta;
        }

        void visit(const WriteRegister&) override
        {
            color = Output::Color::Green;
        }

        void visit(const ReadWriteRegister&) override
        {
            color = Output::Color::Yellow;
        }

        void visit(const BootRomLocation& location) override
        {
            if (location.getApplicationCount() > 0)
            {
                color = Output::Color::Cyan;
            }
            else if (location.bootRomDataEnabled)
            {
                color = Output::Color::Blue;
            }
            else
            {
                color = Output::Color::Red;
            }
        }

        Output::Color color = Output::Color::Default;
    };

public:
    class ContextBase
    {
    public:
        ContextBase(std::string fileName, Output::Color debugColor, Debugger& debugger)
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

        Debugger& debugger;
        std::string fileName;
        Long inspectedAddress = 0;
        bool watchMode = true;
        Output::Color debugColor;
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
            for (Byte i = lastKnownAddressIndex; i != Byte(lastKnownAddressIndex - 0xff); --i)
            {
                if (knownAddresses[i] != currentAddress)
                {
                    return knownAddresses[i];
                }
            }
            return currentAddress;
        }

        void printAddressHistory(Output& output)
        {
            Output::Lock lock(output);
            output.printLine(lock, "Address history:");
            for (Byte i = lastKnownAddressIndex; i != Byte(lastKnownAddressIndex - 10); --i)
            {
                output.print(lock, "@", knownAddresses[i], " ");
            }
            output.printLine(lock);
        }

        bool isStepMode() const
        {
            return stepMode;
        }

    public:
        const Instruction<State>* nextInstruction = nullptr;

    private:
        bool stepMode = false;
        Byte lastKnownAddressIndex = 0;
        std::array<AddressType, 0x100> knownAddresses;
        std::set<Breakpoint<State>> breakpoints;

        friend class Debugger;
    };

    Debugger(Output& output, Video::Registers& videoRegisters, Audio::Registers& audioRegisters, bool& running)
        : output(output, "debugger")
        , videoRegisters(videoRegisters)
        , videoProcessor(videoRegisters.processor)
        , audioRegisters(audioRegisters)
        , audioProcessor(audioRegisters.processor)
        , running(running)
    {
    }

    Debugger(const Debugger&) = delete;
    Debugger& operator=(const Debugger&) = delete;

    template<typename State>
    void loadBreakpoints(Context<State>& context, State& state)
    {
        std::ifstream contextFile(context.fileName);
        if (contextFile)
        {
            std::string breakpointString;
            while (std::getline(contextFile, breakpointString, ' '))
            {
                int applicationCountIndex = int(breakpointString.find('#'));
                int argumentValueIndex = int(breakpointString.find(':'));
                Breakpoint<State> breakpoint;
                int index = std::min(applicationCountIndex, argumentValueIndex) - 1;
                breakpoint.address = typename State::AddressType(std::stoi(breakpointString.substr(1, index), 0, 16));
                if (applicationCountIndex >= 0)
                {
                    breakpoint.applicationCount = std::stoull(breakpointString.substr(size_t(applicationCountIndex) + 1));
                }
                if (argumentValueIndex >= 0)
                {
                    breakpoint.argumentValue = std::stoi(breakpointString.substr(size_t(argumentValueIndex) + 1), 0, 16);
                }
                output.debug("Read breakpoint: ", breakpoint, " from ", context.fileName);
                MemoryAccess access = state.getMemoryAccess(typename State::AddressType(breakpoint.address));
                toggleBreakpoint(context, state, access, breakpoint);
            }
        }
    }

    template<typename State>
    void toggleBreakpoint(Context<State>& context, State& state, LocationAccess& access, const Breakpoint<State>& breakpoint)
    {
        if (access.hasBreakpoint())
        {
            if (access.setBreakpoint(nullptr))
            {
                context.breakpoints.erase(breakpoint);
                output.debug("Breakpoint removed at address ", breakpoint.address);
            }
            else
            {
                output.error("Breakpoint not allowed at address ", breakpoint.address);
            }
        }
        else
        {
            bool success = access.setBreakpoint([this, &context, &state, breakpoint](Location::Operation operation, Byte value, uint64_t applicationCount)
                {
                    bool printInstruction = false;
                    Output::Lock lock(output);
                    if (operation == Location::Operation::Apply && (breakpoint.applicationCount == 0 || breakpoint.applicationCount == applicationCount))
                    {
                        output.printLine(lock, "Apply: Breakpoint hit ", breakpoint, "#", applicationCount);
                        pause(context);
                    }
                    else if (operation == Location::Operation::Read && (breakpoint.argumentValue == -1 || breakpoint.argumentValue == value))
                    {
                        output.print(lock, "Read: Breakpoint hit @ ", breakpoint, ":", value);
                        pause(context);
                        printInstruction = true;
                    }
                    else if (operation == Location::Operation::Write && (breakpoint.argumentValue == -1 || breakpoint.argumentValue == value))
                    {
                        output.print(lock, "Write: Breakpoint hit ", breakpoint, ":", value);
                        pause(context);
                        printInstruction = true;
                    }
                    if (printInstruction)
                    {
                        typename State::AddressType programAddress = state.getProgramAddress();
                        state.setProgramAddress(context.getLastKnownAddress());
                        output.print(lock, " while executing ");
                        {
                            Output::ColorScope colorScope(lock, output, context.stepMode ? context.debugColor : Output::Color::Red, true);
                            output.print(lock, context.nextInstruction->toString(state));
                        }
                        output.printLine(lock, " @", context.getLastKnownAddress());
                        state.setProgramAddress(programAddress);
                    }
                });
            if (success)
            {
                context.breakpoints.insert(breakpoint);
                output.debug("Breakpoint inserted: ", breakpoint);
            }
            else
            {
                output.error("Breakpoint not allowed at address ", breakpoint.address);
            }
        }
    }

    template<typename State, typename OtherState>
    bool awaitCommand(Context<State>& context, State& state, Context<OtherState>& otherContext, OtherState& otherState)
    {
        output.print(Output::Lock(output), "Command (h for help): ");

        std::string command;
        std::getline(std::cin, command);

        if (command.empty())
        {
            output.info("Step");
            return true;
        }
        else if (command == "h")
        {
            Output::Lock lock(output);
            output.printLine(lock, "Commands:");
            output.printLine(lock, "[return]: step into next instruction");
            output.printLine(lock, "n: inspect next memory page");
            output.printLine(lock, "p: inspect previous memory page");
            output.printLine(lock, "i: inspect operand address");
            output.printLine(lock, "r: toggle run context");
            output.printLine(lock, "rr: run all contexts");
            output.printLine(lock, "q: soft reset");
            output.printLine(lock, "qr: soft reset and run");
            output.printLine(lock, "qq: hard reset");
            output.printLine(lock, "t: toggle breakpoint at current Program Counter address");
            output.printLine(lock, "tt: toggle breakpoint at next Program Counter address");
            output.printLine(lock, "ttt: toggle breakpoint at last executed Program Counter address");
            output.printLine(lock, "t [hex]: toogle breakpoint at address [hex]");
            output.printLine(lock, "clear: clear all breakpoints");
            output.printLine(lock, "w: watch executing program memory");
            output.printLine(lock, "[hex]: inspect memory page containing address [hex]");
            output.printLine(lock, "v [hex]: inspect videoProcessor memory containing address [hex]");
            output.printLine(lock, "[p|s|a|x|y|d|f]=[hex]: set register to [hex]");
            output.printLine(lock, "[a]=[hex]: set address [a] to [hex]");
            output.printLine(lock, "s: switch contexts");
        }
        else if (command == "n")
        {
            context.watchMode = false;
            context.inspectedAddress += (1 << 8);
        }
        else if (command == "p")
        {
            context.watchMode = false;
            context.inspectedAddress -= (1 << 8);
        }
        else if (command[0] == 'r')
        {
            if (command == "rr")
            {
                unpause(context, otherContext);
            }
            else
            {
                context.stepMode = !context.stepMode;
                if (context.stepMode)
                {
                    output.info("Step mode");
                }
                else if (!otherContext.stepMode)
                {
                    output.info("Run mode");
                    unpause(context, otherContext);
                }
            }
            if (!paused)
            {
                output.info("All running");
                startTime = clock();
            }
            return !context.stepMode;
        }
        else if (command == "i")
        {
            output.info("Inspect not implemented");
        }
        else if (command == "q")
        {
            output.info("Soft reset");
            state.reset();
            otherState.reset();
            videoRegisters.reset();
            audioRegisters.reset();
        }
        else if (command == "qr")
        {
            output.info("Soft reset and run");
            state.reset();
            otherState.reset();
            videoRegisters.reset();
            audioRegisters.reset();
            unpause(context, otherContext);
            startTime = clock();
        }
        else if (command == "qq")
        {
            output.info("Hard reset");
            running = false;
        }
        else if (command == "clear")
        {
            for (const Breakpoint<State>& breakpoint : context.breakpoints)
            {
                state.getMemoryAccess(breakpoint.address).setBreakpoint(nullptr);
            }
            context.breakpoints.clear();
            output.info("Cleared context ", context.fileName);
            std::ofstream file(context.fileName);
        }
        else if (command[0] == 't')
        {
            Breakpoint<State> breakpoint;
            breakpoint.address = state.getProgramAddress();
            if (command.substr(0, 3) == "ttt")
            {
                breakpoint.address = context.getPreviousAddress(breakpoint.address);
                breakpoint.applicationCount = state.getMemory().getApplicationCount(breakpoint.address);
            }
            else if (command.substr(0, 2) == "tt")
            {
                breakpoint.address += context.nextInstruction->size();
                breakpoint.applicationCount = state.getMemory().getApplicationCount(breakpoint.address);
            }
            else if (command.substr(0, 2) == "t ")
            {
                try
                {
                    breakpoint.address = typename State::AddressType(stoi(command.substr(2), 0, 16));
                }
                catch (const std::exception& e)
                {
                    output.error("Not a valid value: ", e.what());
                }
            }
            MemoryAccess access = state.getMemoryAccess(breakpoint.address);
            toggleBreakpoint(context, state, access, breakpoint);
            std::ofstream file(context.fileName);
            if (file)
            {
                for (const Breakpoint<State>& b : context.breakpoints)
                {
                    file << b << ' ';
                }
            }
        }
        else if (command[0] == 'v')
        {
            try
            {
                inspectedVideoMemory = Word(stoi(command.substr(2), 0, 16));
            }
            catch (const std::exception& e)
            {
                output.error("Not a valid value: ", e.what());
            }
        }
        else if (command == "w")
        {
            context.watchMode = !context.watchMode;
            output.info("Watch mode ", (context.watchMode ? "on" : "off"));
        }
        else if (command == "s")
        {
            output.info("Switched contexts");
            printState(otherState, otherContext);
            return awaitCommand(otherContext, otherState, context, state);
        }
        else if (command.size() > 1 && command[1] == '=')
        {
            try
            {
                Word value = (Word)stoi(command.substr(2), 0, 16);
                output.info("Setting register ", command[0], "=", value);
                state.setRegisterDebug(command[0], value);
            }
            catch (const std::exception& e)
            {
                output.error("Not a valid address: ", e.what());
            }
        }
        else if (command.find('=') != std::string::npos)
        {
            size_t pos = command.find('=');
            try
            {
                output.info("Address: ", command.substr(0, pos), ", value: ", command.substr(pos + 1));
                typename State::AddressType address(stoi(command.substr(0, pos), 0, 16));
                Byte value = (Byte)stoi(command.substr(pos + 1), 0, 16);
                output.info("Setting address ", address, "=", value);
                state.getMemory().writeByte(value, address);
            }
            catch (const std::exception& e)
            {
                output.error("Not valid: ", command.substr(0, pos), " or ", command.substr(pos + 1), ": ", e.what());
            }
        }
        else
        {
            try
            {
                context.inspectedAddress = stoi(command, 0, 16);
                output.info("Inspecting address ", context.inspectedAddress);
                context.watchMode = false;
            }
            catch (const std::exception& e)
            {
                output.error("Not a valid address: ", e.what());
            }
        }

        return false;
    }

    template<typename State>
    void printRegisters(const State& state, Context<State>& context)
    {
        Output::Lock lock(output);
        Output::ColorScope colorScope(lock, output, context.debugColor, true);
        state.printRegisters(output, lock);
        output.printLine(lock);
    }

    template<typename State>
    void printState(State& state, Context<State>& context)
    {
        Output::Lock lock(output);
        Output::ColorScope colorScope(lock, output, paused ? context.debugColor : Output::Color::Red, true);
        state.printRegisters(output, lock);
        output.printLine(lock);
        output.printLine(lock, context.nextInstruction->opcodeToString());
        output.print(lock, state.inspectProgramByte(), ": ");
        output.print(lock, context.nextInstruction->toString(state));
        output.printLine(lock, " #", state.getMemory().getApplicationCount(state.getProgramAddress()));
    }

    template<typename State>
    void setColor(const State& state, const Context<State>& context, typename State::AddressType address, const ConstLocationAccess& access, Output::Color& color, bool& bright)
    {
        color = Output::Color::Default;
        bright = false;
        bool executing = address >= state.getProgramAddress() && address < state.getProgramAddress() + context.nextInstruction->size();
        if (access.hasBreakpoint() && executing)
        {
            color = Output::Color::Cyan;
            bright = true;
        }
        else if (access.hasBreakpoint())
        {
            color = Output::Color::Red;
            bright = true;
        }
        else if (executing)
        {
            color = context.debugColor;
            bright = true;
        }
        else
        {
            OutputColorVisitor colorVisitor;
            access.accept(colorVisitor);
            color = colorVisitor.color;
        }
    }

    void printMemory(CPU::State& cpuState, const Context<CPU::State>& cpuContext, const SPC::State& spcState, const Context<SPC::State>& spcContext)
    {
        //System::setOutputColor(output, System::DefaultColor, false);
        //int oamAddress = inspectedVideoMemory & 0xFF80;
        //int oamAuxAddress = oamAddress / 8;
        //int oamAuxOffset = oamAddress & 7;
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

        Output::Lock lock(output);

        output.printLine(lock, "OAM start address: ", videoRegisters.oamStartAddress);
        output.printLine(lock, "OAM current address: ", videoProcessor.oam.currentAddress);
        output.printLine(lock, "Video port control: ", videoRegisters.videoPortControl);
        //output << "VRAM start address: " << videoRegisters.vramStartAddress << std::endl;
        output.printLine(lock, "VRAM current address: ", videoProcessor.vram.currentAddress);
        output.printLine(lock, "CPU bus: ", cpuState.getMemory().bus);

        audioProcessor.printDebuggerInfo(output, lock);

        output.printLine(lock);
        output.printLine(lock);

        output.printLine(lock, "          0     1     2     3     4     5     6     7");
        output.print(lock, "          8     9     a     b     c     d     e     f");
        output.printLine(lock, "                0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
        int lastVramLowAddress = -1;
        int longVramAddress = inspectedVideoMemory & 0xFF80;
        Byte dspAddress = 0;
        for (int i = 0; i < 16; ++i)
        {
            if (longVramAddress < videoProcessor.vram.size)
            {
                Word vramAddress(longVramAddress);
                uint16_t lowAddress = vramAddress;
                lowAddress = lowAddress >> 4;
                if (lastVramLowAddress != lowAddress)
                {
                    output.print(lock, "   ", std::hex, std::right, std::setw(3), std::setfill('0'), lowAddress, "x  ", std::dec);
                }
                else
                {
                    output.print(lock, "         ");
                }
                lastVramLowAddress = lowAddress;

                for (int j = 0; j < 8 && vramAddress < videoProcessor.vram.size; ++j)
                {
                    output.print(lock, videoProcessor.vram.getByte(vramAddress, false), ' ', videoProcessor.vram.getByte(vramAddress, true), ' ');
                    ++vramAddress;
                }
            }

            output.print(lock, "     ");

            if (dspAddress < audioProcessor.dspMemory.size())
            {
                uint16_t lowAddress(dspAddress);
                lowAddress = lowAddress >> 4;
                output.print(lock, std::hex, std::right, std::setw(3), std::setfill('0'), lowAddress, "x  ", std::dec);

                for (int j = 0; j < 16 && dspAddress < audioProcessor.dspMemory.size(); ++j)
                {
                    ConstMemoryAccess access(audioProcessor.dspMemory, dspAddress);
                    OutputColorVisitor colorVisitor;
                    access.accept(colorVisitor);
                    Output::ColorScope outputColor(lock, output, colorVisitor.color, false);
                    output.print(lock, access, ' ');
                    ++dspAddress;
                }
            }

            output.printLine(lock);
        }
        output.print(lock);

        Long startCpuAddress = cpuContext.watchMode ? cpuState.getProgramAddress() : cpuContext.inspectedAddress;
        Long startSpcAddress = spcContext.watchMode ? spcState.getProgramAddress() : spcContext.inspectedAddress;

        size_t cpuMemorySize = cpuState.getMemorySize();
        size_t spcMemorySize = spcState.getMemorySize();

        output.printLine(lock, "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f",
            "             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
        Long cpuAddress(startCpuAddress & 0xFFFF00);
        Word spcAddress(startSpcAddress & 0xFFFF00);

        for (int i = 0; i < 16; ++i)
        {
            if (cpuAddress < cpuMemorySize)
            {
                Byte bank = Byte(cpuAddress >> 16);
                uint16_t lowAddress = uint16_t(cpuAddress);
                lowAddress = lowAddress >> 4;
                output.print(lock, bank, ':', std::hex, std::right, std::setw(3), std::setfill('0'), lowAddress, "x  ", std::dec);

                for (int j = 0; j < 16 && cpuAddress < cpuMemorySize; ++j)
                {
                    ConstMemoryAccess access = cpuState.getConstMemoryAccess(cpuAddress);
                    Output::Color color = Output::Color::Default;
                    bool bright = false;
                    setColor(cpuState, cpuContext, cpuAddress, access, color, bright);
                    Output::ColorScope outputColor(lock, output, color, bright);
                    output.print(lock, access, ' ');
                    ++cpuAddress;
                }
            }

            output.print(lock, "     ");

            if (spcAddress < spcMemorySize)
            {
                uint16_t lowAddress(spcAddress);
                lowAddress = lowAddress >> 4;
                output.print(lock, std::hex, std::right, std::setw(3), std::setfill('0'), lowAddress, "x  ", std::dec);

                for (int j = 0; j < 16 && spcAddress < spcMemorySize; ++j)
                {
                    ConstMemoryAccess access = spcState.getConstMemoryAccess(spcAddress);
                    Output::Color color;
                    bool bright = false;
                    setColor(spcState, spcContext, spcAddress, access, color, bright);
                    Output::ColorScope outputColor(lock, output, color, bright);
                    if (spcAddress >= 0xffc0 && audioRegisters.bootRomDataEnabled)
                    {
                        output.print(lock, audioRegisters.bootRomData[spcAddress - 0xffc0], ' ');
                    }
                    else
                    {
                        output.print(lock, access, ' ');
                    }
                    ++spcAddress;
                }
            }

            output.printLine(lock);
        }
    }

    void printBreakpoints(const Context<CPU::State>& cpuContext, const Context<SPC::State>& spcContext)
    {
        printBreakpoints(cpuContext);
        printBreakpoints(spcContext);
    }

    template<typename State>
    void printBreakpoints(const Context<State>& context)
    {
        if (!context.breakpoints.empty())
        {
            Output::Lock lock(output);
            output.print(lock, "Breakpoints:");
            for (const Breakpoint<State>& breakpoint : context.breakpoints)
            {
                output.print(lock, " ", breakpoint);
            }
            output.printLine(lock);
        }
    }

    template<typename State>
    void pause(Context<State>& context)
    {
        context.stepMode = true;
        if (paused)
        {
            return;
        }
        paused = true;
        if (videoProcessor.tryUnlockRenderer())
        {
            rendererUnlocked = true;
        }
        if (videoProcessor.rendererRunner.fullscreen)
        {
            videoProcessor.renderer.toggleFullscreenRequested = true;
        }
        videoProcessor.renderer.focusWindow(false);
        System::focusConsoleWindow();
    }

    template<typename State, typename OtherState>
    void unpause(Context<State>& context, Context<OtherState>& otherContext)
    {
        if (!paused)
        {
            return;
        }
        paused = false;
        context.stepMode = false;
        otherContext.stepMode = false;
        if (rendererUnlocked)
        {
            videoProcessor.lockRenderer();
            rendererUnlocked = false;
        }
        videoProcessor.renderer.focusWindow(true);
    }

    bool isPaused() const
    {
        return paused;
    }

    std::time_t startTime = 0LL;

private:
    Output output;

    Video::Registers& videoRegisters;
    Video::Processor& videoProcessor;

    Audio::Registers& audioRegisters;
    const Audio::Processor& audioProcessor;
    
    bool& running;
    Word inspectedVideoMemory = 0x0;
    bool paused = false;
    bool rendererUnlocked = false;
};
