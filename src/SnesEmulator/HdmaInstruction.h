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
        MemoryLocation hdmaControl;
        MemoryLocation registerAddress;
        MemoryLocation startAddressLowByte;
        MemoryLocation startAddressHighByte;
        MemoryLocation startAddressBankByte;
        MemoryLocation indirectAddressLowByte;
        MemoryLocation indirectAddressHighByte;
        MemoryLocation indirectAddressBankByte;
        MemoryLocation addressLowByte;
        MemoryLocation addressHighByte;
        MemoryLocation lineCounter;
        bool doTransfer = false;
    };

public:
    HdmaInstruction(std::ostream& output, std::ostream& error, CPU::State& state)
        : output(output)
        , error(error)
        , state(state)
        , channels(8)
    {
        dmaEnabled.setMappings(state.getMemoryLocation(0x420b));
        hdmaEnabled.setMappings(state.getMemoryLocation(0x420c));
        for (int i = 0; i < channels.size(); ++i) {
            Long baseAddress = 0x4300 | i << 4;
            channels[i].hdmaControl.setMappings(state.getMemoryLocation(baseAddress), nullptr, MemoryLocation::ReadOnly);
            channels[i].registerAddress.setMappings(state.getMemoryLocation(baseAddress | 0x1), nullptr, MemoryLocation::ReadOnly);
            channels[i].startAddressLowByte.setMappings(state.getMemoryLocation(baseAddress | 0x2), nullptr, MemoryLocation::ReadOnly);
            channels[i].startAddressHighByte.setMappings(state.getMemoryLocation(baseAddress | 0x3), nullptr, MemoryLocation::ReadOnly);
            channels[i].startAddressBankByte.setMappings(state.getMemoryLocation(baseAddress | 0x4), nullptr, MemoryLocation::ReadOnly);
            channels[i].indirectAddressLowByte.setMappings(state.getMemoryLocation(baseAddress | 0x5));
            channels[i].indirectAddressHighByte.setMappings(state.getMemoryLocation(baseAddress | 0x6));
            channels[i].indirectAddressBankByte.setMappings(state.getMemoryLocation(baseAddress | 0x7));
            channels[i].addressLowByte.setMappings(state.getMemoryLocation(baseAddress | 0x8));
            channels[i].addressHighByte.setMappings(state.getMemoryLocation(baseAddress | 0x9));
            channels[i].lineCounter.setMappings(state.getMemoryLocation(baseAddress | 0xa));
        }
    }

    HdmaInstruction(const HdmaInstruction&) = delete;
    HdmaInstruction& operator=(const HdmaInstruction&) = delete;

    std::string toString() const override
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by HDMA)" << std::endl;
        ss << "HDMA ";
        if (Byte enabled = hdmaEnabled.getValue()) {
            ss << "Enabled: " << enabled << std::endl;
            ss << "Active: " << active << std::endl;
            ss << "Initialize: " << initialize << std::endl;
            for (int i = 0; i < 8; ++i) {
                if (enabled.getBit(i)) {
                    const Channel& channel = channels[i];
                    ss << "Channel " << i << std::endl;
                    ss << "Start address: " << channel.startAddressBankByte << channel.startAddressHighByte << channel.startAddressLowByte << std::endl;
                    ss << "Indirect address: " << channel.indirectAddressBankByte << channel.indirectAddressHighByte << channel.indirectAddressLowByte << std::endl;
                    ss << "Address: " << channel.addressHighByte << channel.addressLowByte << std::endl;
                    ss << "Register: 21" << channel.registerAddress << std::endl;
                    ss << "Line counter: " << channel.lineCounter.getValue().getBits(0, 7) << std::endl;
                    ss << "Repeat: " << channel.lineCounter.getValue().getBit(7) << std::endl;
                    ss << "Do transfer: " << channel.doTransfer << std::endl;
                    ss << "HDMA control: " << channel.hdmaControl << std::endl;
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
        if (const Byte hdmaEnabledValue = hdmaEnabled.getValue()) {
            Byte dmaEnabledValue = dmaEnabled.getValue();
            cycles += 2;
            for (int i = 0; i < 8; ++i) {
                if (hdmaEnabledValue.getBit(i)) {
                    dmaEnabledValue.setBit(i, false);
                    cycles += 1;

                    Channel& channel = channels[i];

                    Byte hdmaControl = channel.hdmaControl.getValue();
                    bool direction = hdmaControl.getBit(7);
                    if (direction) {
                        error << "DMA control: " << hdmaControl << std::endl;
                        throw OperatorNotYetImplementedException("HDMA direction not implemented");
                    }

                    bool indirectAddressingMode = hdmaControl.getBit(6);

                    if (initialize) {
                        channel.addressLowByte.setWordValue(channel.startAddressLowByte.getWordValue());
                        channel.lineCounter.setValue(getNextByte(channel, false));
                        if (indirectAddressingMode) {
                            Byte lowByte = getNextByte(channel, false);
                            channel.indirectAddressLowByte.setWordValue(Word(lowByte, getNextByte(channel, false)));
                            cycles += 2;
                        }
                        channel.doTransfer = true;
                    }
                    else if (Byte lineCounter = channel.lineCounter.getValue())
                    {
                        //Byte lineCounter = channel.lineCounter.getValue();

                        Long registerAddress = 0x2100 | channel.registerAddress.getValue();
                        MemoryLocation* registerLocation = state.getMemoryLocation(registerAddress);

                        if (channel.doTransfer) {
                            Byte transferMode = hdmaControl.getBits(0, 3);
                            /*if (transferMode == 0) {
                                registerLocation->setValue(getNextByte(channel, indirectAddressingMode));
                                cycles += 1;
                            }
                            else */if (transferMode == 1) {
                                Byte lowByte = getNextByte(channel, indirectAddressingMode);
                                registerLocation->setWordValue(Word(lowByte, getNextByte(channel, indirectAddressingMode)));
                                cycles += 2;
                            }
                            else {
                                error << "DMA control: " << hdmaControl << std::endl;
                                throw OperatorNotYetImplementedException("DMA transfer mode not implemented");
                            }
                        }
                        --lineCounter;
                        channel.doTransfer = lineCounter.getBit(7);
                        if (lineCounter.getBits(0, 7) == 0) {
                            lineCounter = getNextByte(channel, false);
                            if (indirectAddressingMode) {
                                Byte lowByte = getNextByte(channel, false);
                                channel.indirectAddressLowByte.setWordValue(Word(lowByte, getNextByte(channel, false)));
                                cycles += 2;
                            }
                            channel.doTransfer = true;
                        }
                        channel.lineCounter.setValue(lineCounter);
                    }
                }
            }
            dmaEnabled.setValue(dmaEnabledValue);
        }
        initialize = false;
        active = false;
        return cycles;
    }

    Byte getNextByte(Channel& channel, bool indirect)
    {
        if (indirect) {
            Word address = channel.indirectAddressLowByte.getWordValue();
            channel.indirectAddressLowByte.setWordValue(address + 1);
            return state.getMemoryByte(Long(address, channel.indirectAddressBankByte.getValue()));
        }
        else {
            Word address = channel.addressLowByte.getWordValue();
            channel.addressLowByte.setWordValue(address + 1);
            return state.getMemoryByte(Long(address, channel.startAddressBankByte.getValue()));
        }
    }

    int size() const override
    {
        return blockedInstruction->size();
    }

    bool enabled() const
    {
        return hdmaEnabled.getValue();
    }

public:
    Instruction* blockedInstruction = nullptr;
    bool active = false;
    bool initialize = false;

private:
    CPU::State& state;
    MemoryLocation dmaEnabled;
    MemoryLocation hdmaEnabled;
    std::vector<Channel> channels;

    std::ostream& output;
    std::ostream& error;
};