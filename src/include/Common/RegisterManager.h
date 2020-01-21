#pragma once

#include "Types.h"
#include "System.h"

template<typename State, System::Color DebugColor>
class RegisterManager
{
public:
    typedef typename State::AddressType AddressType;

    RegisterManager(std::ostream& output, std::ostream& error, State& state)
        : output(output)
        , error(error)
        , state(state)
    {
    }

    void printMemoryRegister(bool write, Byte value, Word address, const std::string& info)
    {
        System::setOutputColor(output, DebugColor, true);
        output << (write ? "Write " : "Read ") << value << " (" << std::bitset<8>(value) << ") @ " << address << " (" << info << "), " << std::endl;
        System::setOutputColor(output, System::DefaultColor, false);
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, std::function<void(Byte)> callback = nullptr, bool openBus = false)
    {
        std::function<void(Byte, Byte)> onWrite = [this, address, callback, info, debug](Byte oldValue, Byte newValue) {
            if (debug && newValue && oldValue != newValue) {
                printMemoryRegister(true, newValue, address, info);
            }
            if (callback) {
                callback(newValue);
            }
        };
        if (openBus) {
            state.createMemoryLocation<OpenBusWriteRegister>(AddressType(address), onWrite);
        } else {
            state.createMemoryLocation<WriteRegister>(AddressType(address), onWrite);
        }
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Byte& variable, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable = value; }, openBus);
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Word& variable, bool openBus = false)
    {
        makeWriteRegister(address, info + " low byte", debug, [&variable](Byte value) { variable.setLowByte(value); }, openBus);
        makeWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte value) { variable.setHighByte(value); }, openBus);
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Long& variable, bool openBus = false)
    {
        makeWriteRegister(address, info + " low byte", debug, [&variable](Byte value) { variable.setLowByte(value); }, openBus);
        makeWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte value) { variable.setHighByte(value); }, openBus);
        makeWriteRegister(address + 2, info + " bank byte", debug, [&variable](Byte value) { variable.setBankByte(value); }, openBus);
    }

    void makeReadRegister(Word address, const std::string& info, bool debug, std::function<void(Byte&)> callback = nullptr)
    {
        state.createMemoryLocation<ReadRegister>(AddressType(address),
            [this, address, callback, info, debug](Byte& value) {
                if (callback) {
                    callback(value);
                }
                if (debug && value) {
                    printMemoryRegister(false, value, address, info);
                }
            }
        );
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

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, std::function<void(Byte&)> readCallback, std::function<void(Byte)> writeCallback)
    {
        state.createMemoryLocation<ReadWriteRegister>(AddressType(address),
            [this, address, readCallback, info, debug](Byte& value) {
                if (readCallback) {
                    readCallback(value);
                }
                if (debug && value) {
                    printMemoryRegister(false, value, address, info);
                }
            },
            [this, address, writeCallback, info, debug](Byte oldValue, Byte newValue) {
                if (debug && newValue && oldValue != newValue) {
                    printMemoryRegister(true, newValue, address, info);
                }
                if (writeCallback) {
                    writeCallback(newValue);
                }
            }
            );
    };

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, Byte& variable)
    {
        makeReadWriteRegister(address, info, debug, [&variable](Byte& value) { value = variable; }, [&variable](Byte value) { variable = value; });
    }

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, Word& variable)
    {
        makeReadWriteRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, [&variable](Byte value) { variable.setLowByte(value); });
        makeReadWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, [&variable](Byte value) { variable.setHighByte(value); });
    }

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, Long& variable)
    {
        makeReadWriteRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, [&variable](Byte value) { variable.setLowByte(value); });
        makeReadWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, [&variable](Byte value) { variable.setHighByte(value); });
        makeReadWriteRegister(address + 2, info + " bank byte", debug, [&variable](Byte& value) { value = variable.getBankByte(); }, [&variable](Byte value) { variable.setBankByte(value); });
    }

private:
    std::ostream& output;
    std::ostream& error;

protected:
    State& state;
};