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
        Long dmaControlAddress;
        Long registerAddressAddress;
        Long sourceAddressLowByteAddress;
        //Long sourceAddressHighByteAddress;
        //Long sourceBankAddress;
        Long dataSizeLowByteAddress;
        //Long dataSizeHighByteAddress;
        bool active = false;
    };

public:
    DmaInstruction(std::ostream& output, std::ostream& error, CPU::State& state)
        : output(output)
        , error(error)
        , memory(state.getMemory())
        , channels(8)
    {
        dmaEnabledAddress = 0x420b;
        for (int i = 0; i < channels.size(); ++i) {
            Long baseAddress = 0x4300 | i << 4;
            channels[i].dmaControlAddress = baseAddress;
            channels[i].registerAddressAddress = baseAddress | 1;
            channels[i].sourceAddressLowByteAddress = baseAddress | 2;
            //channels[i].sourceAddressHighByteAddress = baseAddress | 3;
            //channels[i].sourceBankAddress = baseAddress | 4;
            channels[i].dataSizeLowByteAddress = baseAddress | 5;
            //channels[i].dataSizeHighByteAddress = baseAddress | 6;
        }
    }

    DmaInstruction(const DmaInstruction&) = delete;
    DmaInstruction& operator=(const DmaInstruction&) = delete;

    std::string toString() const override
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by DMA)" << std::endl;
        ss << "DMA ";
        if (Byte enabled = memory.readByte(dmaEnabledAddress)) {
            for (int i = 0; i < 8; ++i) {
                if (enabled.getBit(i)) {
                    const Channel& channel = channels[i];
                    ss << "Channel " << i << ": ";
                    ss << memory.readLong(channel.sourceAddressLowByteAddress);
                    ss << " -> ";
                    ss << "21" << memory.readByte(channel.registerAddressAddress) << std::endl;
                    ss << "Bytes left: " << memory.readWord(channel.dataSizeLowByteAddress) << std::endl;
                    ss << "DMA control: " << memory.readByte(channel.dmaControlAddress) << std::endl;
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
        if (Byte dmaEnabledValue = memory.readByte(dmaEnabledAddress)) {
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

                    Long registerAddress = 0x2100 | memory.readByte(channel.registerAddressAddress);
                    Long sourceAddress = memory.readLong(channel.sourceAddressLowByteAddress);
                    Word dataSize = memory.readWord(channel.dataSizeLowByteAddress);

                    Byte dmaControl = memory.readByte(channel.dmaControlAddress);
                    bool direction = dmaControl.getBit(7);
                    int byteCount = 0;
                    Byte transferMode = dmaControl.getBits(0, 3);
                    if (transferMode == 0) {
                        transfer(sourceAddress, registerAddress, direction, false, byteCount);
                    }
                    else if (transferMode == 1) {
                        transfer(sourceAddress, registerAddress, direction, dataSize > 1, byteCount);
                    }
                    else {
                        error << "DMA control: " << dmaControl << std::endl;
                        throw OperatorNotYetImplementedException("DMA transfer mode not implemented");
                    }

                    bool fixedTransfer = dmaControl.getBit(3);
                    bool increment = dmaControl.getBit(4);
                    if (!fixedTransfer) {
                        memory.writeWord(sourceAddress + (increment ? -byteCount : byteCount), channel.sourceAddressLowByteAddress);
                    }
                    dataSize -= byteCount;
                    cycles += byteCount;

                    memory.writeWord(dataSize, channel.dataSizeLowByteAddress);

                    if (dataSize == 0) {
                        dmaEnabledValue.setBit(i, false);
                        memory.writeByte(dmaEnabledValue, dmaEnabledAddress);
                        channel.active = false;
                    }
                    return cycles;
                }
            }
        }
        return cycles;
    }

    void transfer(Long memoryAddress, Long registerAddress, bool direction, bool transferWord, int& byteCount)
    {
        Long sourceAddress;
        Long destinationAddress;
        if (direction) {
            sourceAddress = registerAddress;
            destinationAddress = memoryAddress;
        }
        else {
            sourceAddress = memoryAddress;
            destinationAddress = registerAddress;
        }

        if (transferWord) {
            memory.writeWord<CPU::State::MemoryType::Bank>(memory.readWord<CPU::State::MemoryType::Bank>(sourceAddress), destinationAddress);
            ++byteCount;
        }
        else {
            memory.writeByte(memory.readByte(sourceAddress), destinationAddress);
            ++byteCount;
        }
    }

    int size() const override
    {
        return blockedInstruction->size();
    }

    bool enabled()
    {
        if (memory.readByte(dmaEnabledAddress)) {
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
    CPU::State::MemoryType& memory;
    Long dmaEnabledAddress;
    std::vector<Channel> channels;

    std::ostream& output;
    std::ostream& error;

    int iteration = 0;
};