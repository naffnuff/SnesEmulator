#pragma once

#include <vector>

#include "Common/Instruction.h"
#include "Common/MemoryLocation.h"

#include "WDC65816/CpuState.h"

class HdmaInstruction : public Instruction
{
private:
    struct Channel
    {
        Long hdmaControlAddress;
        Long registerAddressAddress;
        Long startAddressLowByteAddress;
        Long startAddressHighByteAddress;
        Long startAddressBankByteAddress;
        Long indirectAddressLowByteAddress;
        Long indirectAddressHighByteAddress;
        Long indirectAddressBankByteAddress;
        Long addressLowByteAddress;
        Long addressHighByteAddress;
        Long lineCounterAddress;
        bool doTransfer = false;
    };

public:
    HdmaInstruction(std::ostream& output, std::ostream& error, CPU::State& state)
        : output(output)
        , error(error)
        , memory(state.getMemory())
        , channels(8)
    {
        dmaEnabledAddress = 0x420b;
        hdmaEnabledAddress = 0x420c;
        for (int i = 0; i < channels.size(); ++i) {
            Long baseAddress = 0x4300 | i << 4;
            channels[i].hdmaControlAddress = baseAddress;
            channels[i].registerAddressAddress = baseAddress | 0x1;
            channels[i].startAddressLowByteAddress = baseAddress | 0x2;
            channels[i].startAddressHighByteAddress = baseAddress | 0x3;
            channels[i].startAddressBankByteAddress = baseAddress | 0x4;
            channels[i].indirectAddressLowByteAddress = baseAddress | 0x5;
            channels[i].indirectAddressHighByteAddress = baseAddress | 0x6;
            channels[i].indirectAddressBankByteAddress = baseAddress | 0x7;
            channels[i].addressLowByteAddress = baseAddress | 0x8;
            channels[i].addressHighByteAddress = baseAddress | 0x9;
            channels[i].lineCounterAddress = baseAddress | 0xa;
        }
    }

    HdmaInstruction(const HdmaInstruction&) = delete;
    HdmaInstruction& operator=(const HdmaInstruction&) = delete;

    std::string toString() const override
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by HDMA)" << std::endl;
        ss << "HDMA ";
        if (Byte enabled = memory.readByte(hdmaEnabledAddress)) {
            ss << "Enabled: " << std::bitset<8>(enabled) << std::endl;
            ss << "Active: " << active << std::endl;
            ss << "Initialization requested: " << initializationRequested << std::endl;
            ss << "Iteration: " << iteration << std::endl;
            for (int i = 0; i < 8; ++i) {
                if (enabled.getBit(i)) {
                    ss << "*" << std::endl;
                    const Channel& channel = channels[i];
                    ss << "Channel " << i << std::endl;
                    ss << "Start address: " << memory.readLong(channel.startAddressLowByteAddress) << std::endl;
                    ss << "Indirect address: " << memory.readLong(channel.indirectAddressLowByteAddress) << std::endl;
                    ss << "Address: " << memory.readWord(channel.addressLowByteAddress) << std::endl;
                    ss << "Register: 21" << memory.readByte(channel.registerAddressAddress) << std::endl;
                    ss << "Line counter: " << memory.readByte(channel.lineCounterAddress).getBits(0, 7) << std::endl;
                    ss << "Repeat: " << memory.readByte(channel.lineCounterAddress).getBit(7) << std::endl;
                    ss << "Do transfer: " << channel.doTransfer << std::endl;
                    ss << "HDMA control: " << memory.readByte(channel.hdmaControlAddress) << std::endl;
                }
            }
        }
        return ss.str();
    }

    std::string opcodeToString() const override
    {
        return blockedInstruction->opcodeToString();
    }

    int execute() override
    {
        int cycles = 0;
        if (const Byte hdmaEnabledValue = memory.readByte(hdmaEnabledAddress)) {
            Byte dmaEnabledValue = memory.readByte(dmaEnabledAddress);
            cycles += 2;
            for (int i = 0; i < 8; ++i) {
                if (hdmaEnabledValue.getBit(i)) {
                    ++iteration;

                    dmaEnabledValue.setBit(i, false);
                    cycles += 1;

                    Channel& channel = channels[i];

                    Byte hdmaControl = memory.readByte(channel.hdmaControlAddress);
                    bool direction = hdmaControl.getBit(7);
                    if (direction) {
                        error << "HDMA control: " << hdmaControl << std::endl;
                        throw OperatorNotYetImplementedException("HDMA direction not implemented");
                    }

                    bool indirectAddressingMode = hdmaControl.getBit(6);

                    if (initializationRequested) {
                        memory.writeWord(memory.readWord(channel.startAddressLowByteAddress), channel.addressLowByteAddress);
                        memory.writeByte(getNextByte(channel, false), channel.lineCounterAddress);
                        if (indirectAddressingMode) {
                            memory.writeByte(getNextByte(channel, false), channel.indirectAddressLowByteAddress);
                            memory.writeByte(getNextByte(channel, false), channel.indirectAddressLowByteAddress + 1);
                            cycles += 2;
                        }
                        channel.doTransfer = true;
                    }
                    else if (Byte lineCounter = memory.readByte(channel.lineCounterAddress))
                    {
                        //Byte lineCounter = channel.lineCounter.getValue();

                        Long registerAddress = 0x2100 | memory.readByte(channel.registerAddressAddress);

                        if (channel.doTransfer) {
                            Byte transferMode = hdmaControl.getBits(0, 3);
                            if (transferMode == 0) {
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress);
                                cycles += 1;
                            }
                            else if (transferMode == 1) {
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress);
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress + 1);
                                cycles += 2;
                            }
                            else if (transferMode == 2) {
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress);
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress);
                                cycles += 2;
                            }
                            else if (transferMode == 3) {
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress);
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress);
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress + 1);
                                memory.writeByte(getNextByte(channel, indirectAddressingMode), registerAddress + 1);
                                cycles += 4;
                            }
                            else {
                                error << "HDMA control: " << hdmaControl << std::endl;
                                error << "HDMA transfer mode: " << transferMode << std::endl;
                                throw OperatorNotYetImplementedException("HDMA transfer mode not implemented");
                            }
                        }
                        --lineCounter;
                        channel.doTransfer = lineCounter.getBit(7);
                        if (lineCounter.getBits(0, 7) == 0) {
                            lineCounter = getNextByte(channel, false);
                            if (indirectAddressingMode) {
                                Byte lowByte = getNextByte(channel, false);
                                memory.writeByte(getNextByte(channel, false), channel.indirectAddressLowByteAddress);
                                memory.writeByte(getNextByte(channel, false), channel.indirectAddressLowByteAddress + 1);
                                cycles += 2;
                            }
                            channel.doTransfer = true;
                        }
                        memory.writeByte(lineCounter, channel.lineCounterAddress);
                    }
                }
            }
            memory.writeByte(dmaEnabledValue, dmaEnabledAddress);
        }
        initializationRequested = false;
        active = false;
        return cycles;
    }

    Byte getNextByte(Channel& channel, bool indirect)
    {
        if (indirect) {
            Long address = memory.readLong(channel.indirectAddressLowByteAddress);
            memory.writeWord(address + 1, channel.indirectAddressLowByteAddress);
            return memory.readByte(address);
        }
        else {
            Word address = memory.readWord(channel.addressLowByteAddress);
            memory.writeWord(address + 1, channel.addressLowByteAddress);
            return memory.readByte(Long(address, memory.readByte(channel.startAddressBankByteAddress)));
        }
    }

    int size() const override
    {
        return blockedInstruction->size();
    }

    bool enabled() const
    {
        return memory.readByte(hdmaEnabledAddress);
    }

    void setActive(bool value, bool requestInitialization = false)
    {
        if (value && requestInitialization) {
            initializationRequested = true;
            iteration = -1;
        }
        active = value;
    }

    bool isActive() const
    {
        return active;
    }

public:
    Instruction* blockedInstruction = nullptr;
    Long hdmaEnabledAddress;

private:
    CPU::State::MemoryType& memory;
    bool active = false;
    bool initializationRequested = false;
    int iteration = -1;
    Long dmaEnabledAddress;
    std::vector<Channel> channels;

    std::ostream& output;
    std::ostream& error;
};