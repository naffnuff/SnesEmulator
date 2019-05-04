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
    DmaInstruction(std::vector<MemoryLocation>& registers, std::vector<MemoryLocation>& memory, std::ostream& output)
        : registers(registers)
        , memory(memory)
        , dmaEnabledRead(registers[0x420b])
        , dmaEnabledWrite(memory[0x420b])
        , channels(8)
        , output(output)
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
        ss << "DMA ";
        if (Byte dmaEnabled = dmaEnabledRead.getValue()) {
            for (int i = 0; i < 7; ++i) {
                if (dmaEnabled.getBit(i)) {
                    Channel channel = channels[i];
                    Word sourceAddress = channel.sourceAddressRead->getWordValue();
                    Byte sourceBank = channel.sourceBank->getValue();
                    ss << sourceBank << ":" << sourceAddress;
                    ss << " -> ";
                    ss << Word(0x2100 | channel.registerAddress->getValue()) << std::endl;
                    ss << "Bytes left: " << channel.dataSizeRead->getWordValue() << std::endl;
                    ss << "Next word: " << memory[Long(sourceAddress, sourceBank)].getWordValue() << std::endl;
                    ss << "DMA control: " << channel.dmaControl->getValue() << std::endl;
                    ss << "Video port control: " << registers[0x2115].getValue() << std::endl;
                    Word vramAddress = registers[0x2116].getWordValue();
                    ss << "VRAM address " << vramAddress;
                    return ss.str();
                }
            }
        }
    }

    virtual std::string opcodeToString() const
    {
        return blockedInstruction->opcodeToString() + " (blocked by DMA)";
    }

    virtual int execute()
    {
        int cycles = 0;
        if (Byte dmaEnabled = dmaEnabledRead.getValue()) {
            for (int i = 0; i < 7; ++i) {
                if (dmaEnabled.getBit(i)) {
                    Channel& channel = channels[i];
                    Byte dmaControl = channel.dmaControl->getValue();
                    if (dmaControl == 0x01) {
                        Word registerAddress = 0x2100 | channel.registerAddress->getValue();
                        Word sourceAddress = channel.sourceAddressRead->getWordValue();
                        Byte sourceBank = channel.sourceBank->getValue();
                        Word dataSize = channel.dataSizeRead->getWordValue();
                        Word data = memory[Long(sourceAddress, sourceBank)].getWordValue();
                        memory[registerAddress].setWordValue(data);

                        cycles = 8 * 2;

                        channel.sourceAddressWrite->setWordValue(sourceAddress + 2);
                        channel.dataSizeWrite->setWordValue(dataSize - 2);

                        if (dataSize - 2 == 0) {
                            dmaEnabled.setBit(i, false);
                            dmaEnabledWrite.setValue(dmaEnabled);
                        }
                    } else {
                        throw std::logic_error("DMA control not implemented");
                    }
                    break;
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
};