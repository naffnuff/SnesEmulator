#pragma once

#include <vector>

#include "Common/Instruction.h"
#include "Common/Memory.h"

#include "WDC65816/CpuState.h"

#include "Registers.h"

class DmaInstruction : public Instruction
{
public:
    DmaInstruction(std::ostream& output, std::ostream& error, CPU::State& state, Registers& registers)
        : output(output)
        , error(error)
        , memory(state.getMemory())
        , registers(registers)
    {
    }

    DmaInstruction(const DmaInstruction&) = delete;
    DmaInstruction& operator=(const DmaInstruction&) = delete;

    std::string toString() const override
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by DMA)" << std::endl;
        ss << "Enabled: " << std::bitset<8>(registers.dmaEnabled) << std::endl;
        ss << "DMA ";
        if (registers.dmaEnabled) {
            for (int i = 0; i < 8; ++i) {
                if (registers.dmaEnabled.getBit(i)) {
                    const Registers::DmaChannel& channel = registers.dmaChannels[i];
                    ss << "Channel " << i << ": ";
                    ss << channel.sourceAddress;
                    ss << " -> ";
                    ss << "21" << channel.destinationRegister << std::endl;
                    ss << "Bytes left: " << channel.dataSize << std::endl;
                    ss << "DMA control: " << channel.control << std::endl;
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
        if (registers.dmaEnabled) {
            for (int i = 0; i < 8; ++i) {
                if (registers.dmaEnabled.getBit(i)) {
                    if (iteration++ == 0) {
                        cycles += 3;
                    }

                    Registers::DmaChannel& channel = registers.dmaChannels[i];
                    if (!channel.dmaActive) {
                        channel.dmaActive = true;
                        cycles += 1;
                    }

                    Long registerAddress = 0x2100 | channel.destinationRegister;

                    bool direction = channel.control.getBit(7);
                    int byteCount = 0;
                    Byte transferMode = channel.control.getBits(0, 3);
                    if (transferMode == 0) {
                        transfer(channel.sourceAddress, registerAddress, direction, false, byteCount);
                    }
                    else if (transferMode == 1) {
                        transfer(channel.sourceAddress, registerAddress, direction, channel.dataSize > 1, byteCount);
                    }
                    else {
                        error << "DMA control: " << channel.control << std::endl;
                        throw OperatorNotYetImplementedException("DMA transfer mode not implemented");
                    }

                    bool fixedTransfer = channel.control.getBit(3);
                    bool increment = channel.control.getBit(4);
                    if (!fixedTransfer) {
                        channel.sourceAddress += (increment ? -byteCount : byteCount);
                    }
                    channel.dataSize -= byteCount;
                    cycles += byteCount;

                    if (channel.dataSize == 0) {
                        registers.dmaEnabled.setBit(i, false);
                        channel.dmaActive = false;
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
            byteCount += 2;
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
        if (registers.dmaEnabled) {
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
    Registers& registers;

    std::ostream& output;
    std::ostream& error;

    int iteration = 0;
};