#pragma once

#include <vector>

#include "Common/Instruction.h"
#include "Common/MemoryLocation.h"

#include "WDC65816/CpuState.h"

class DmaInstruction : public Instruction
{
private:
    struct Channel
    {
        MemoryLocation dmaControl;
        MemoryLocation registerAddress;
        MemoryLocation sourceAddressLowByte;
        MemoryLocation sourceAddressHighByte;
        MemoryLocation sourceBank;
        MemoryLocation dataSizeLowByte;
        MemoryLocation dataSizeHighByte;
    };

public:
    DmaInstruction(std::ostream& output, std::ostream& error, CPU::State& state)
        : output(output)
        , error(error)
        , state(state)
        , channels(8)
    {
        dmaEnabled.setMappings(state.getMemoryLocation(0x420b));
        for (int i = 0; i < channels.size(); ++i) {
            Long baseAddress = 0x4300 | i << 4;
            channels[i].dmaControl.setMappings(state.getMemoryLocation(baseAddress), nullptr, MemoryLocation::ReadOnly);
            channels[i].registerAddress.setMappings(state.getMemoryLocation(baseAddress | 1), nullptr, MemoryLocation::ReadOnly);
            channels[i].sourceAddressLowByte.setMappings(state.getMemoryLocation(baseAddress | 2));
            channels[i].sourceAddressHighByte.setMappings(state.getMemoryLocation(baseAddress | 3));
            channels[i].sourceBank.setMappings(state.getMemoryLocation(baseAddress | 4), nullptr, MemoryLocation::ReadOnly);
            channels[i].dataSizeLowByte.setMappings(state.getMemoryLocation(baseAddress | 5));
            channels[i].dataSizeHighByte.setMappings(state.getMemoryLocation(baseAddress | 6));
        }
    }

    DmaInstruction(const DmaInstruction&) = delete;
    DmaInstruction& operator=(const DmaInstruction&) = delete;

    virtual std::string toString() const
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by DMA)" << std::endl;
        ss << "DMA ";
        if (Byte enabled = dmaEnabled.getValue()) {
            for (int i = 0; i < 7; ++i) {
                if (enabled.getBit(i)) {
                    Channel channel = channels[i];
                    ss << "Channel " << i << ": ";
                    ss << channel.sourceBank << channel.sourceAddressHighByte << channel.sourceAddressLowByte;
                    ss << " -> ";
                    ss << "21" << channel.registerAddress << std::endl;
                    ss << "Bytes left: " << channel.dataSizeHighByte << channel.dataSizeLowByte << std::endl;
                    ss << "DMA control: " << channel.dmaControl << std::endl;
                    break;
                }
            }
        }
        return ss.str();
    }

    virtual std::string opcodeToString() const
    {
        return blockedInstruction->opcodeToString();
    }

    virtual int execute()
    {
        int cycles = 0;
        if (Byte dmaEnabledValue = dmaEnabled.getValue()) {
            for (int i = 0; i < 7; ++i) {
                while (dmaEnabledValue.getBit(i)) {
                    Channel& channel = channels[i];

                    Long registerAddress = 0x2100 | channel.registerAddress.getValue();
                    Word sourceAddress = channel.sourceAddressLowByte.getWordValue();
                    Byte sourceBank = channel.sourceBank.getValue();
                    Word dataSize = channel.dataSizeLowByte.getWordValue();
                    MemoryLocation* memoryLocation = state.getMemoryLocation(Long(sourceAddress, sourceBank));
                    MemoryLocation* registerLocation = state.getMemoryLocation(registerAddress);

                    Byte dmaControl = channel.dmaControl.getValue();
                    Byte transferMode = dmaControl.getBits(0, 3);
                    bool fixedTransfer = dmaControl.getBit(3);
                    bool increment = dmaControl.getBit(4);
                    bool hdmaMode = dmaControl.getBit(6);
                    bool direction = dmaControl.getBit(7);
                    if (direction) {
                        throw OperatorNotYetImplementedException("DMA control direction not implemented");
                    }
                    int byteCount = 0;
                    if (transferMode == 0x0) {
                        Byte data = memoryLocation->getValue();
                        registerLocation->setValue(data);

                        byteCount = 1;
                    }
                    else if (transferMode == 0x1) {
                        Word data = memoryLocation->getWordValue();
                        registerLocation->setWordValue(data);

                        byteCount = 2;
                    }
                    else {
                        error << "DMA control: " << dmaControl << std::endl;
                        throw OperatorNotYetImplementedException("DMA control not implemented");
                    }

                    if (!fixedTransfer)
                    {
                        channel.sourceAddressLowByte.setWordValue(sourceAddress + (increment ? -byteCount : byteCount));
                    }
                    dataSize -= byteCount;
                    cycles += byteCount;

                    channel.dataSizeLowByte.setWordValue(dataSize);

                    if (dataSize == 0) {
                        dmaEnabledValue.setBit(i, false);
                        dmaEnabled.setValue(dmaEnabledValue);
                        return cycles;
                    }
                }
            }
        }
        return cycles;
    }

    virtual int size() const
    {
        return blockedInstruction->size();
    }

    bool enabled() const
    {
        return dmaEnabled.getValue();
    }

public:
    Instruction* blockedInstruction = nullptr;

private:
    CPU::State& state;
    MemoryLocation dmaEnabled;
    std::vector<Channel> channels;

    std::ostream& output;
    std::ostream& error;
};