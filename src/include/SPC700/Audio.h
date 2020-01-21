#pragma once

#include <vector>
#include <functional>

#include "RegisterManager.h"
#include "System.h"
#include "Memory.h"

#include "SpcState.h"

namespace SPC {

class Audio : public RegisterManager<State, System::Blue>
{
public:
    class NotYetImplementedException : public std::logic_error
    {
    public:
        NotYetImplementedException(const std::string& name)
            : std::logic_error("Audio feature not yet implemented: " + name)
        {
        }
    };

    class Timer
    {
    public:
        bool highPrecision = false;
        bool enabled = false;
        int tick = 0;
        int target = 256;
        int counter = 0;
    };

    Audio(std::ostream& output, std::ostream& error, State& state)
        : RegisterManager(output, error, state)
        , output(output)
        , error(error)
        , dspMemory(0x100)
    {
        timers[2].highPrecision = true;
    }

    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    void tick()
    {
        ++audioCycle;
        if (audioCycle % 16 == 0) {
            for (int i = 0; i < 3; ++i) {
                if (timers[i].enabled && (timers[i].highPrecision || audioCycle % 128 == 0)) {
                    ++timers[i].tick;
                    if (timers[i].tick == timers[i].target) {
                        timers[i].tick = 0;
                        timers[i].counter = (timers[i].counter + 1) % 0x10;
                    }
                }
            }
        }
    }

    void initialize(Memory<Long>& cpuMemory)
    {
        makeWriteRegister(0xf1, "I/0 and Timer Control", false,
            [this, &cpuMemory](Byte byte) {
                for (int i = 0; i < 3; ++i) {
                    if (!timers[i].enabled && byte.getBit(i)) {
                        timers[i].tick = 0;
                        timers[i].counter = 0;
                    }
                    timers[i].enabled = byte.getBit(i);
                }
                if (byte.getBit(4)) {
                    cpuMemory.writeWord(0, 0x2140);
                }
                if (byte.getBit(5)) {
                    cpuMemory.writeWord(0, 0x2142);
                }
                bootRomDataEnabled = byte.getBit(7);
            });
        makeWriteRegister(0xf2, "DSP Communication Address", false,
            [this](Byte value) {
                dspAddress = value;
            });
        makeReadWriteRegister(0xf3, "DSP Communication Data", false,
            [this](Byte& value) {
                value = dspMemory[dspAddress & 0x7f];
            },
            [this](Byte value) {
                if (dspAddress < 0x80) {
                    dspMemory[dspAddress] = value;
                }
            });

        for (int i = 0; i < 3; ++i) {
            makeWriteRegister(0xfa + i, std::string("Timer ") + char('1' + i) + " Scaling Target", true,
                [this, i](Byte value) {
                    timers[i].target = value == 0 ? 0x100 : int(value);
                });
            makeReadRegister(0xfd + i, std::string("Timer ") + char('1' + i) + " Output", false,
                [this, i](Byte& value) {
                    value = timers[i].counter;
                    timers[i].counter = 0;
                });
        }

        for (int i = 0; i < bootRomData.size(); ++i) {
            Word address = 0xffc0 + i;
            state.createMemoryLocation<BootRomLocation>(address, 0xff, bootRomData[i], bootRomDataEnabled);
        }
    }
    
    void reset()
    {
        bootRomDataEnabled = true;
        timers = {};
    }

    std::ostream& output;
    std::ostream& error;

    uint64_t audioCycle = 0;

    std::array<Timer, 3> timers;

    Byte dspAddress;
    std::vector<Byte> dspMemory;

    bool bootRomDataEnabled = true;

    std::array<Byte, 64> bootRomData = {
       0xCD, 0xEF, 0xBD, 0xE8, 0x00, 0xC6, 0x1D, 0xD0, 0xFC, 0x8F, 0xAA, 0xF4, 0x8F, 0xBB, 0xF5, 0x78,
       0xCC, 0xF4, 0xD0, 0xFB, 0x2F, 0x19, 0xEB, 0xF4, 0xD0, 0xFC, 0x7E, 0xF4, 0xD0, 0x0B, 0xE4, 0xF5,
       0xCB, 0xF4, 0xD7, 0x00, 0xFC, 0xD0, 0xF3, 0xAB, 0x01, 0x10, 0xEF, 0x7E, 0xF4, 0x10, 0xEB, 0xBA,
       0xF6, 0xDA, 0x00, 0xBA, 0xF4, 0xC4, 0xF4, 0xDD, 0x5D, 0xD0, 0xDB, 0x1F, 0x00, 0x00, 0xC0, 0xFF,
    };
};

}