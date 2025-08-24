#pragma once

#include "Types.h"
#include "System.h"
#include "Output.h"

template<typename Memory, Output::Color DebugColor>
class RegisterManager
{
    EXCEPTION(AccessException, ::AccessException)

public:
    typedef typename Memory::AddressType AddressType;

    RegisterManager(Output& output, const std::string& logName, Memory& memory)
        : output(output, logName)
        , memory(memory)
    {
    }

    virtual void printMemoryRegister(bool write, Byte value, AddressType address, const std::string& info)
    {
        if (supressOutput)
        {
            return;
        }
        output.log(Log::Level::Debug, DebugColor, value != 0, (write ? "Write " : "Read "), value, " (", std::bitset<8>(value), ") @", address, " (", info, "), ");
    }

    void makeWriteRegister(AddressType address, const std::string& info, bool debug, std::function<void(Byte)> callback = nullptr, bool openBus = false)
    {
        std::function<void(Byte, Byte)> onWrite = [this, address, callback, info, debug](Byte oldValue, Byte newValue)
            {
                if (debug && /*newValue && */oldValue != newValue)
                {
                    printMemoryRegister(true, newValue, address, info);
                }

                if (callback)
                {
                    callback(newValue);
                }
                else
                {
                    //throw NotYetImplementedException("Register ", address, ": ", info);
                }
            };
        if (openBus)
        {
            memory.template createLocation<OpenBusWriteRegister>(address, onWrite);
        }
        else
        {
            memory.template createLocation<WriteRegister>(address, onWrite);
        }
    }

    void makeWriteRegister(AddressType address, const std::string& info, bool debug, Byte& variable, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable = value; }, openBus);
    }

    void makeWriteRegister(AddressType address, const std::string& info, bool debug, int8_t& variable, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable = value; }, openBus);
    }

    /*void makeWriteRegister(AddressType address, const std::string& info, bool debug, std::bitset<8>& variable, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable = std::bitset<8>(value); }, openBus);
    }*/

    void makeWriteRegister(AddressType address, const std::string& info, bool debug, Word& variable, bool openBus = false)
    {
        makeWriteRegister(address, info + " low byte", debug, [&variable](Byte value) { variable.setLowByte(value); }, openBus);
        makeWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte value) { variable.setHighByte(value); }, openBus);
    }

    void makeWriteRegister(AddressType address, const std::string& info, bool debug, Long& variable, bool openBus = false)
    {
        makeWriteRegister(address, info + " low byte", debug, [&variable](Byte value) { variable.setLowByte(value); }, openBus);
        makeWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte value) { variable.setHighByte(value); }, openBus);
        makeWriteRegister(address + 2, info + " bank byte", debug, [&variable](Byte value) { variable.setBankByte(value); }, openBus);
    }

    void makeReadRegister(AddressType address, const std::string& info, bool debug, std::function<void(Byte&)> callback = nullptr, bool throwOnWrite = true)
    {
        memory.template createLocation<ReadRegister>(address,
            [this, address, callback, info, debug](Byte& value)
            {
                if (callback)
                {
                    callback(value);
                }
                else
                {
                    //throw NotYetImplementedException("Register ", address, ": ", info);
                }

                if (debug && value)
                {
                    printMemoryRegister(false, value, address, info);
                }
            },
            throwOnWrite
        );
    };

    void makeReadRegister(AddressType address, const std::string& info, bool debug, Byte& variable, bool throwOnWrite = true)
    {
        makeReadRegister(address, info, debug, [&variable](Byte& value) { value = variable; }, throwOnWrite);
    }

    void makeReadRegister(AddressType address, const std::string& info, bool debug, int8_t& variable, bool throwOnWrite = true)
    {
        makeReadRegister(address, info, debug, [&variable](Byte& value) { value = variable; }, throwOnWrite);
    }

    /*void makeReadRegister(AddressType address, const std::string& info, bool debug, std::bitset<8> & variable, bool throwOnWrite = true)
    {
        makeReadRegister(address, info, debug, [&variable](Byte& value) { value = uint8_t(variable.to_ulong()); }, throwOnWrite);
    }*/

    void makeReadRegister(AddressType address, const std::string& info, bool debug, const Word& variable, bool throwOnWrite = true)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, throwOnWrite);
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, throwOnWrite);
    }

    void makeReadRegister(AddressType address, const std::string& info, bool debug, const Long& variable, bool throwOnWrite = true)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, throwOnWrite);
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, throwOnWrite);
        makeReadRegister(address + 2, info + " bank byte", debug, [&variable](Byte& value) { value = variable.getBankByte(); }, throwOnWrite);
    }

    void makeReadWriteRegister(AddressType address, const std::string& info, bool debug, std::function<void(Byte&)> readCallback, std::function<void(Byte)> writeCallback)
    {
        memory.template createLocation<ReadWriteRegister>(address,
            [this, address, readCallback, info, debug](Byte& value)
            {
                if (readCallback)
                {
                    readCallback(value);
                }
                if (debug/* && value*/)
                {
                    printMemoryRegister(false, value, address, info);
                }
            },
            [this, address, writeCallback, info, debug](Byte oldValue, Byte newValue)
            {
                if (debug /*newValue && */ && oldValue != newValue)
                {
                    printMemoryRegister(true, newValue, address, info);
                }
                if (writeCallback)
                {
                    writeCallback(newValue);
                }
            }
        );
    };

    void makeReadWriteRegister(AddressType address, const std::string& info, bool debug, Byte& variable)
    {
        makeReadWriteRegister(address, info, debug, [&variable](Byte& value) { value = variable; }, [&variable](Byte value) { variable = value; });
    }

    void makeReadWriteRegister(AddressType address, const std::string& info, bool debug, int8_t& variable)
    {
        makeReadWriteRegister(address, info, debug, [&variable](Byte& value) { value = variable; }, [&variable](Byte value) { variable = value; });
    }

    /*void makeReadWriteRegister(AddressType address, const std::string& info, bool debug, std::bitset<8>& variable)
    {
        makeReadWriteRegister(address, info, debug, [&variable](Byte& value) { value = uint8_t(variable.to_ulong()); }, [&variable](Byte value) { variable = std::bitset<8>(value); });
    }*/

    void makeReadWriteRegister(AddressType address, const std::string& info, bool debug, Word& variable)
    {
        makeReadWriteRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, [&variable](Byte value) { variable.setLowByte(value); });
        makeReadWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, [&variable](Byte value) { variable.setHighByte(value); });
    }

    void makeReadWriteRegister(AddressType address, const std::string& info, bool debug, Long& variable)
    {
        makeReadWriteRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, [&variable](Byte value) { variable.setLowByte(value); });
        makeReadWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, [&variable](Byte value) { variable.setHighByte(value); });
        makeReadWriteRegister(address + 2, info + " bank byte", debug, [&variable](Byte& value) { value = variable.getBankByte(); }, [&variable](Byte value) { variable.setBankByte(value); });
    }

    void verifyRegister(AddressType address, Byte expectedValue)
    {
        struct OutputSupressor
        {
            OutputSupressor(bool& supressOutput)
                : supressOutput(supressOutput)
            {
                supressOutput = true;
            }
            ~OutputSupressor()
            {
                supressOutput = false;
            }
            bool& supressOutput;
        } outputSupressor(supressOutput);

        Byte readValue = memory.readByte(address);
        if (readValue != expectedValue)
        {
            throw AccessException("Verify memory failed @", address, ": ", "Expected value: ", expectedValue, ", ", "Read value: ", readValue);
        }
    }

    bool supressOutput = false;

private:
    Output output;

    Memory& memory;
};