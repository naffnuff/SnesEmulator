#pragma once

#include <vector>

#include "System.h"
#include "MemoryLocation.h"

#include "SpcState.h"

namespace SPC {

class Audio
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
        : output(output)
        , error(error)
        , state(state)
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

    void printMemoryRegister(bool write, Byte value, Word address, const std::string& info)
    {
        System::setOutputColor(output, System::Blue, true);
        output << (write ? "Write " : "Read ") << value << " (" << std::bitset<8>(value) << ") @ " << address << " (" << info << "), " << std::endl;
        System::setOutputColor(output, System::DefaultColor, false);
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, std::function<void(Byte value)> callback = nullptr)
    {
        MemoryLocation* memory = state.getMemoryLocation(address);
        memory->setWriteOnly();
        memory->setValue(0);
        memory->onWrite = [this, address, callback, info, debug](Byte oldValue, Byte newValue) {
            if (debug) {
                printMemoryRegister(true, newValue, address, info);
            }
            if (callback) {
                callback(newValue);
            }
        };
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Byte& variable)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable = value; });
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Word& variable)
    {
        makeWriteRegister(address, info + " low byte", debug, [&variable](Byte value) { variable.setLowByte(value); });
        makeWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte value) { variable.setHighByte(value); });
    }

    void makeReadRegister(Word address, const std::string& info, bool debug, std::function<void(Byte& value)> callback = nullptr)
    {
        MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
        memory->setReadOnlyValue(0);
        memory->onRead = [this, address, callback, info, debug](Byte& value) {
            if (callback) {
                callback(value);
            }
            if (debug) {
                printMemoryRegister(false, value, address, info);
            }
        };
    };

    void makeReadRegister(Word address, const std::string& info, bool debug, const Word& variable)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); });
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); });
    }

    void makeReadRegister(Word address, const std::string& info, bool debug, const Long& variable)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); });
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); });
        makeReadRegister(address + 2, info + " bank byte", debug, [&variable](Byte& value) { value = variable.getBankByte(); });
    }

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, std::function<void(Byte& value)> readCallback = nullptr, std::function<void(Byte value)> writeCallback = nullptr)
    {
        MemoryLocation* memory = state.getMemoryLocation(address);
        memory->setReadWrite();
        memory->setValue(0);
        memory->onRead = [this, address, readCallback, info, debug](Byte& value) {
            if (readCallback) {
                readCallback(value);
            }
            if (debug) {
                printMemoryRegister(false, value, address, info);
            }
        };
        memory->onWrite = [this, address, writeCallback, info, debug](Byte oldValue, Byte newValue) {
            if (debug) {
                printMemoryRegister(true, newValue, address, info);
            }
            if (writeCallback) {
                writeCallback(newValue);
            }
        };
    };

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, Word& variable)
    {
        makeReadWriteRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, [&variable](Byte value) { variable.setLowByte(value); });
        makeReadWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, [&variable](Byte value) { variable.setHighByte(value); });
    }

    void initialize(std::array<MemoryLocation*, 4>& cpuToSpcPorts)
    {
        makeWriteRegister(0xf1, "I/0 and Timer Control", false,
            [this, cpuToSpcPorts](Byte byte) {
                for (int i = 0; i < 3; ++i) {
                    if (!timers[i].enabled && byte.getBit(i)) {
                        timers[i].tick = 0;
                        timers[i].counter = 0;
                    }
                    timers[i].enabled = byte.getBit(i);
                }
                if (byte.getBit(4)) {
                    cpuToSpcPorts[0]->setValue(0);
                    cpuToSpcPorts[1]->setValue(0);
                }
                if (byte.getBit(5)) {
                    cpuToSpcPorts[2]->setValue(0);
                    cpuToSpcPorts[3]->setValue(0);
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
            MemoryLocation* memory = state.getMemoryLocation(address);
            memory->setReadWrite();
            memory->setValue(0);
            std::function callback = [this, i](Byte& value) {
                if (bootRomDataEnabled) {
                    value = bootRomData[i];
                }
            };
            memory->onRead = callback;
            memory->onApply = callback;
        }
    }
    
    void reset()
    {
        bootRomDataEnabled = true;
        timers = {};
    }

    std::ostream& output;
    std::ostream& error;
    State& state;

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