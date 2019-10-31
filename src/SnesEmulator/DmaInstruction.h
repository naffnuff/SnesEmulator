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
        Channel()
            : dmaControl(0, [](const MemoryLocation*) { return "DmaInstruction: DMA Control"; })
            , registerAddress(0, [](const MemoryLocation*) { return "DmaInstruction: Register Address"; })
            , sourceAddressLowByte(0, [](const MemoryLocation*) { return "DmaInstruction: Source Address low byte"; })
            , sourceAddressHighByte(0, [](const MemoryLocation*) { return "DmaInstruction: Source Address high byte"; })
            , sourceBank(0, [](const MemoryLocation*) { return "DmaInstruction: Source Bank"; })
            , dataSizeLowByte(0, [](const MemoryLocation*) { return "DmaInstruction: Data Size low byte"; })
            , dataSizeHighByte(0, [](const MemoryLocation*) { return "DmaInstruction: Data Size high byte"; })
        {
        }

        MemoryLocation dmaControl;
        MemoryLocation registerAddress;
        MemoryLocation sourceAddressLowByte;
        MemoryLocation sourceAddressHighByte;
        MemoryLocation sourceBank;
        MemoryLocation dataSizeLowByte;
        MemoryLocation dataSizeHighByte;
        bool active = false;
    };

public:
    DmaInstruction(std::ostream& output, std::ostream& error, CPU::State& state)
        : output(output)
        , error(error)
        , state(state)
        , channels(8)
        , dmaEnabled(0, [](const MemoryLocation*) { return "DmaInstruction: DMA Enabled"; })
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

    std::string toString() const override
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by DMA)" << std::endl;
        ss << "DMA ";
        if (Byte enabled = dmaEnabled.getValue()) {
            for (int i = 0; i < 8; ++i) {
                if (enabled.getBit(i)) {
                    const Channel& channel = channels[i];
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
        ss << "Iteration: " << iteration << std::endl;
        return ss.str();
    }

    std::string opcodeToString() const override
    {
        return blockedInstruction->opcodeToString();
    }

    int execute() override
    {
        int cycles = 0;
        if (Byte dmaEnabledValue = dmaEnabled.getValue()) {
            for (int i = 0; i < 8; ++i) {
                if (dmaEnabledValue.getBit(i)) {
                    if (iteration++ == 0) {
                        cycles += 3;
                    }

                    Channel& channel = channels[i];
                    if (!channel.active) {
                        channel.active = true;
                        cycles += 1;
                    }

                    Long registerAddress = 0x2100 | channel.registerAddress.getValue();
                    Word sourceAddress = channel.sourceAddressLowByte.getWordValue();
                    Byte sourceBank = channel.sourceBank.getValue();
                    Word dataSize = channel.dataSizeLowByte.getWordValue();
                    MemoryLocation* sourceLocation = state.getMemoryLocation(Long(sourceAddress, sourceBank));
                    MemoryLocation* registerLocation = state.getMemoryLocation(registerAddress);

                    Byte dmaControl = channel.dmaControl.getValue();
                    bool direction = dmaControl.getBit(7);
                    int byteCount = 0;
                    Byte transferMode = dmaControl.getBits(0, 3);
                    if (transferMode == 0) {
                        transferByte(sourceLocation, registerLocation, direction, byteCount);
                    }
                    else if (transferMode == 1) {
                        transferByte(sourceLocation, registerLocation, direction, byteCount);
                        if (dataSize > 1) {
                            transferByte(sourceLocation->nextInBank, registerLocation->nextInMemory, direction, byteCount);
                        }
                    }
                    else {
                        error << "DMA control: " << dmaControl << std::endl;
                        throw OperatorNotYetImplementedException("DMA transfer mode not implemented");
                    }

                    bool fixedTransfer = dmaControl.getBit(3);
                    bool increment = dmaControl.getBit(4);
                    if (!fixedTransfer) {
                        channel.sourceAddressLowByte.setWordValue(sourceAddress + (increment ? -byteCount : byteCount));
                    }
                    dataSize -= byteCount;
                    cycles += byteCount;

                    channel.dataSizeLowByte.setWordValue(dataSize);

                    if (dataSize == 0) {
                        dmaEnabledValue.setBit(i, false);
                        dmaEnabled.setValue(dmaEnabledValue);
                        channel.active = false;
                    }
                    return cycles;
                }
            }
        }
        return cycles;
    }

    static void transferByte(MemoryLocation* sourceLocation, MemoryLocation* registerLocation, bool direction, int& byteCount)
    {
        if (direction) {
            sourceLocation->setValue(registerLocation->getValue());
        }
        else {
            registerLocation->setValue(sourceLocation->getValue());
        }
        ++byteCount;
    }

    int size() const override
    {
        return blockedInstruction->size();
    }

    bool enabled()
    {
        if (dmaEnabled.getValue()) {
            return true;
        }
        else {
            iteration = 0;
            return false;
        }
    }

public:
    Instruction* blockedInstruction = nullptr;

private:
    CPU::State& state;
    MemoryLocation dmaEnabled;
    std::vector<Channel> channels;

    std::ostream& output;
    std::ostream& error;

    int iteration = 0;
};