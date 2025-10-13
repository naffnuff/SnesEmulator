#include "AudioSystem.h"

#include <iostream>
#include <chrono>

#define PROFILING_ENABLED false

#include "Profiler.h"

CREATE_PROFILER();

class AudioSystemRunner
{
public:
    AudioSystemRunner(AudioSystem& system)
        : system(system)
    {
    }

    void operator()()
    {
        try
        {
            uint64_t iteration = 0;
            //uint64_t masterCycle = 0;
            //uint64_t nextSpc = 0;
            system.output.debug("HELLO AUDIO SYSTEM!");
            system.now = std::chrono::steady_clock::now();
            std::chrono::steady_clock::time_point startTime = system.now;
            constexpr AudioSystem::CycleCount oneCycle(1);
            AudioSystem::CycleCount masterCycle(0);
            //double startTime = system.processor.renderer.getStreamTime();
            while (system.run)
            {
                system.processor.checkStreamErrors();

                if (system.threaded && system.booted)
                {
                    if (system.nextSpc == AudioSystem::CycleCount(0))
                    {
                        system.nextSpc = masterCycle;
                    }

                    if (masterCycle == system.nextSpc)
                    {
                        Instruction<SPC::State>* instruction = system.instructionDecoder.getNextInstruction(system.state);
                        system.context.nextInstruction = instruction;

                        instruction->applyBreakpoints(system.state);

                        system.context.addKnownAddress(system.state.getProgramAddress());

                        if (system.debugger.isPaused())
                        {
                            break;
                        }


                        int cycles = 0;
                        {
                            PROFILE_SCOPE("Execute SPC Instruction (threaded)");
                            cycles = instruction->execute(system.state);
                        }
                        if (cycles)
                        {
                            system.nextSpc += AudioSystem::CycleCount(cycles);
                            system.context.nextInstruction = system.instructionDecoder.getNextInstruction(system.state);
                        }
                        else
                        {
                            continue;
                        }

                        if (system.debugger.isPaused())
                        {
                            break;
                        }

                        if (system.registers.pauseRequested)
                        {
                            break;
                        }
                    }
                }

                system.now = std::chrono::steady_clock::now();
                system.elapsedTime = system.now - startTime;
                AudioSystem::CycleCount nextCycle = masterCycle + oneCycle;
                if (nextCycle <= system.elapsedTime)
                {
                    masterCycle = nextCycle;
                    if (system.booted)
                    {
                        system.processor.tick();
                    }
                }
                else
                {
                    //std::chrono::steady_clock::time_point nextCycleTime = startTime + 
                    std::this_thread::yield();
                    //std::this_thread::sleep_until(startTime + nextCycle);
                }
                ++iteration;
                static std::chrono::steady_clock::time_point lastTime = startTime;
                if (system.now - lastTime > std::chrono::seconds(10))
                {
                    system.output.debug("Audio cycles: ", masterCycle.count(), " / ", iteration, " (", (100.0 * masterCycle.count() / iteration), "%)");
                    lastTime = system.now;
                }
            }
            system.output.debug("BYE AUDIO MONKEY! ");
        }
        catch (const ::NotYetImplementedException& e)
        {
            system.output.error("AudioSystem thread: ", e.what());
            system.context.printAddressHistory(system.output);
            //std::getchar();
        }
        catch (const ::RuntimeError& e)
        {
            system.output.error("AudioSystem thread: ", e.what());
            system.context.printAddressHistory(system.output);
            //std::getchar();
        }
        catch (const ::AccessException& e)
        {
            system.output.error("AudioSystem thread: ", e.what());
            system.context.printAddressHistory(system.output);
            //std::getchar();
        }
        system.elapsedTime = std::chrono::nanoseconds(0);
        system.pauseRequested = true;
        system.threaded = false;
    }

private:
    AudioSystem& system;
};

class BootLoaderRunner
{
public:
    BootLoaderRunner(AudioSystem& system)
        : system(system)
    {
    }

    void operator()()
    {
        try
        {
            SPC::State& state = system.state;
            Byte a, x, y, comp, oOne;
            Word ya;
            bool isPositive = false;
    // ffc0: cd: MOV X, #$ef
            x = 0xef;
    // ffc2: bd: MOV SP, X
            state.writeRegister<SPC::State::Register::SP>(x);

    // ffc3: e8: MOV A, #$00
            a = 0;

            for (; x > 0; --x)
            {
    // ffc5: c6: MOV(X), A
                state.writeDirectMemoryByte(a, x);
    // ffc6: 1d: DEC X
    // ffc7: d0: BNE $ffc5
            }

    // ffc9: 8f: MOV $f4, #$aa
            state.writeDirectMemoryByte(0xaa, 0xf4);
    // ffcc: 8f: MOV $f5, #$bb
            state.writeDirectMemoryByte(0xbb, 0xf5);
    // ffcf: 78: CMP $f4, #$cc
    // ffd2: d0: BNE $ffcf
            while (state.readDirectMemoryByte(0xf4) != 0xcc);
    // ffd2: 2f: BRA $ffef
            // jump to ffef
            goto ffef;


            // label ffd6
        ffd6:
    // ffd6: eb: MOV Y, $f4
    // ffd8: d0: BNE $ffd6
            while (y = state.readDirectMemoryByte(0xf4) != 0);


            // label ffda
        ffda:
    // ffda: 7e: CMP Y, $f4
            comp = y - state.readDirectMemoryByte(0xf4);
            isPositive = !comp.isNegative();
    // ffdc: d0: BNE $ffe9
            if (comp != 0)
            {
                // jump to ffe9
                goto ffe9;
            }
    // ffde: e4: MOV A, $f5
            a = state.readDirectMemoryByte(0xf5);
    // ffe0: cb: MOV $f4, Y
            state.writeDirectMemoryByte(y, 0xf4);
    // ffe2: d7: MOV [$00]+Y, A
            state.writeMemoryByte(a, state.readDirectMemoryWord(0x00) + y);
    // ffe4: fc: INC Y
            ++y;
    // ffe5: d0: BNE $ffda
            if (y != 0)
            {
                // jump to ffda
                goto ffda;
            }
    // ffe7: ab: INC $01
            oOne = state.readDirectMemoryByte(0x01) + 1;
            state.writeDirectMemoryByte(oOne, 0x01);
            isPositive = !oOne.isNegative();


            // label ffe9
        ffe9:
    // ffe9: 10: BPL $ffda
            if (isPositive)
            {
                // jump to ffda
                goto ffda;
            }

    // ffeb: 7e: CMP Y, $f4
    // ffed: 10: BPL $ffda
            if (!Byte(y - state.readDirectMemoryByte(0xf4)).isNegative())
            {
                // jump to ffda
                goto ffda;
            }


            // label ffef
        ffef:
    // ffef: ba: MOVW YA, $f6
            ya = state.readDirectMemoryWord(0xf6);
    // fff1: da: MOVW $00, YA
            state.writeDirectMemoryWord(ya, 0x00);
    // fff3: ba: MOVW YA, $f4
            ya = state.readDirectMemoryWord(0xf4);
    // fff5: c4: MOV $f4, A
            state.writeDirectMemoryByte(ya.getLowByte(), 0xf4);
    // fff7: dd: MOV A, Y
            ya.setLowByte(ya.getHighByte());
    // fff8: 5d: MOV X, A
            x = ya.getHighByte();
    // fff9: d0: BNE $ffd6
            if (x != 0)
            {
                // jump to ffd6
                goto ffd6;
            }


    // fffb: 1f: JMP [$0000+X]
            state.setProgramCounter(state.readMemoryWord(Word(0x00, x)));


            // post state: S = 01ef, Z = 1
            state.setFlag(SPC::State::Flag::z, true);
        }
        catch (const ::NotYetImplementedException& e)
        {
            system.output.error("AudioBootLoader thread: ", e.what());
            //std::getchar();
        }
        catch (const ::RuntimeError& e)
        {
            system.output.error("AudioBootLoader thread: ", e.what());
            //std::getchar();
        }
        catch (const ::AccessException& e)
        {
            system.output.error("AudioBootLoader thread: ", e.what());
            //std::getchar();
        }
        system.booted = true;
    }

private:
    AudioSystem& system;
};

void AudioSystem::start()
{
    //threaded = false;
    //booted = true;
    bootLoaderThread = std::thread(BootLoaderRunner(*this));
    processor.startStream();
    if (threaded)
    {
        systemThread = std::thread(AudioSystemRunner(*this));
        systemThreadStarted = true;
    }
}