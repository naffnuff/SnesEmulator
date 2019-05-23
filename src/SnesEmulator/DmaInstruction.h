#pragma once

#include <vector>

#include "Common/Instruction.h"
#include "Common/MemoryLocation.h"

class DmaInstruction : public Instruction
{
private:
    struct Channel
    {
        MemoryLocation* dmaControl = nullptr;
        MemoryLocation* registerAddress = nullptr;
        MemoryLocation* sourceAddressRead = nullptr;
        MemoryLocation* sourceAddressWrite = nullptr;
        MemoryLocation* sourceBank = nullptr;
        MemoryLocation* dataSizeRead = nullptr;
        MemoryLocation* dataSizeWrite = nullptr;
    };

public:
    DmaInstruction(std::vector<MemoryLocation>& registers, std::vector<MemoryLocation>& memory, std::ostream& output, std::ostream& error)
        : registers(registers)
        , memory(memory)
        , dmaEnabledRead(registers[0x420b])
        , dmaEnabledWrite(memory[0x420b])
        , channels(8)
        , output(output)
        , error(error)
    {
        for (int i = 0; i < channels.size(); ++i) {
            Word baseAddress = 0x4300 | i << 4;
            channels[i].dmaControl = &registers[baseAddress];
            channels[i].registerAddress = &registers[baseAddress | 0x0001];
            channels[i].sourceAddressRead = &registers[baseAddress | 0x0002];
            channels[i].sourceAddressWrite = &memory[baseAddress | 0x0002];
            channels[i].sourceBank = &registers[baseAddress | 0x0004];
            channels[i].dataSizeRead = &registers[baseAddress | 0x0005];
            channels[i].dataSizeWrite = &memory[baseAddress | 0x0005];
        }
    }

    DmaInstruction(DmaInstruction&) = delete;
    DmaInstruction& operator=(DmaInstruction&) = delete;

    virtual std::string toString() const
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by DMA)" << std::endl;
        ss << "DMA ";
        if (Byte dmaEnabled = dmaEnabledRead.getValue()) {
            for (int i = 0; i < 7; ++i) {
                if (dmaEnabled.getBit(i)) {
                    Channel channel = channels[i];
                    Word sourceAddress = channel.sourceAddressRead->getWordValue();
                    Byte sourceBank = channel.sourceBank->getValue();
                    MemoryLocation& memoryLocation = memory[Long(sourceAddress, sourceBank)];
                    ss << "Channel " << i << ": ";
                    ss << sourceBank << sourceAddress;
                    ss << " -> ";
                    ss << Word(0x2100 | channel.registerAddress->getValue()) << std::endl;
                    ss << "Bytes left: " << channel.dataSizeRead->getWordValue() << std::endl;
                    ss << "DMA control: " << channel.dmaControl->getValue() << std::endl;
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
        if (Byte dmaEnabled = dmaEnabledRead.getValue()) {
            for (int i = 0; i < 7; ++i) {
                while (dmaEnabled.getBit(i)) {
                    Channel& channel = channels[i];

                    Word registerAddress = 0x2100 | channel.registerAddress->getValue();
                    Word sourceAddress = channel.sourceAddressRead->getWordValue();
                    Byte sourceBank = channel.sourceBank->getValue();
                    Word dataSize = channel.dataSizeRead->getWordValue();
                    MemoryLocation& memoryLocation = memory[Long(sourceAddress, sourceBank)];

                    Byte dmaControl = channel.dmaControl->getValue();
                    Byte transferMode = dmaControl.getBits(0, 3);
                    bool fixedTransfer = dmaControl.getBit(3);
                    bool increment = dmaControl.getBit(4);
                    bool hdmaMode = dmaControl.getBit(6);
                    bool direction = dmaControl.getBit(7);
                    if (direction) {
                        throw OpcodeNotYetImplementedException("DMA control direction not implemented");
                    }
                    int byteCount = 0;
                    if (transferMode == 0x0) {
                        Byte data = memoryLocation.getValue();
                        memory[registerAddress].setValue(data);

                        byteCount = 1;
                    }
                    else if (transferMode == 0x1) {
                        Word data = memoryLocation.getWordValue();
                        memory[registerAddress].setWordValue(data);

                        byteCount = 2;
                    }
                    else {
                        error << "DMA control: " << dmaControl << std::endl;
                        throw OpcodeNotYetImplementedException("DMA control not implemented");
                    }

                    if (!fixedTransfer)
                    {
                        channel.sourceAddressWrite->setWordValue(sourceAddress + (increment ? -byteCount : byteCount));
                    }
                    dataSize -= byteCount;
                    cycles += byteCount;

                    channel.dataSizeWrite->setWordValue(dataSize);

                    if (dataSize == 0) {
                        dmaEnabled.setBit(i, false);
                        dmaEnabledWrite.setValue(dmaEnabled);
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
        return dmaEnabledRead.getValue();
    }

public:
    Instruction* blockedInstruction = nullptr;

private:
    std::vector<MemoryLocation>& registers;
    std::vector<MemoryLocation>& memory;

    MemoryLocation& dmaEnabledRead;
    MemoryLocation& dmaEnabledWrite;
    std::vector<Channel> channels;

    std::ostream& output;
    std::ostream& error;
};