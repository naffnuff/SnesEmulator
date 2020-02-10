#pragma once

#include <vector>

#include "Common/Instruction.h"
#include "Common/Memory.h"

#include "WDC65816/CpuState.h"

class HdmaInstruction : public Instruction
{
public:
    HdmaInstruction(std::ostream& output, std::ostream& error, CPU::State& state, Video::Registers& registers)
        : output(output)
        , error(error)
        , memory(state.getMemory())
        , registers(registers)
    {
    }

    HdmaInstruction(const HdmaInstruction&) = delete;
    HdmaInstruction& operator=(const HdmaInstruction&) = delete;

    std::string toString() const override
    {
        std::stringstream ss;
        ss << blockedInstruction->toString() << " (blocked by HDMA)" << std::endl;
        ss << "HDMA ";
        if (registers.hdmaEnabled) {
            ss << "Enabled: " << std::bitset<8>(registers.hdmaEnabled) << std::endl;
            ss << "Active: " << active << std::endl;
            ss << "Initialization requested: " << initializationRequested << std::endl;
            ss << "Iteration: " << iteration << std::endl;
            for (int i = 0; i < 8; ++i) {
                if (registers.hdmaEnabled.getBit(i)) {
                    ss << "*" << std::endl;
                    const Video::Registers::DmaChannel& channel = registers.dmaChannels[i];
                    ss << "Channel " << i << std::endl;
                    ss << "Start address: " << channel.sourceAddress << std::endl;
                    ss << "Indirect address: " << Long(channel.indirectAddress, channel.indirectAddressBankByte) << std::endl;
                    ss << "Address: " << channel.tableAddress << std::endl;
                    ss << "Register: 21" << channel.destinationRegister << std::endl;
                    ss << "Line counter: " << channel.lineCounter.getBits(0, 7) << std::endl;
                    ss << "Repeat: " << channel.lineCounter.getBit(7) << std::endl;
                    ss << "Do transfer: " << channel.hdmaDoTransfer << std::endl;
                    ss << "HDMA control: " << channel.control << std::endl;
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
        if (registers.hdmaEnabled) {
            cycles += 2;
            for (int i = 0; i < 8; ++i) {
                if (registers.hdmaEnabled.getBit(i)) {
                    ++iteration;

                    registers.dmaEnabled.setBit(i, false);
                    cycles += 1;

                    Video::Registers::DmaChannel& channel = registers.dmaChannels[i];

                    bool direction = channel.control.getBit(7);
                    if (direction) {
                        error << "HDMA control: " << channel.control << std::endl;
                        throw OperatorNotYetImplementedException("HDMA direction not implemented");
                    }

                    bool indirectAddressingMode = channel.control.getBit(6);

                    if (initializationRequested) {
                        channel.tableAddress = Word(channel.sourceAddress);
                        channel.lineCounter = getNextByte(channel, false);
                        if (indirectAddressingMode) {
                            Byte lowByte = getNextByte(channel, false);
                            channel.indirectAddress = Word(lowByte, getNextByte(channel, false));
                            cycles += 2;
                        }
                        channel.hdmaDoTransfer = true;
                    }
                    else if (channel.lineCounter)
                    {
                        //Byte lineCounter = channel.lineCounter.getValue();

                        Long registerAddress = 0x2100 | channel.destinationRegister;

                        if (channel.hdmaDoTransfer) {
                            Byte transferMode = channel.control.getBits(0, 3);
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
                                error << "HDMA control: " << channel.control << std::endl;
                                error << "HDMA transfer mode: " << transferMode << std::endl;
                                throw OperatorNotYetImplementedException("HDMA transfer mode not implemented");
                            }
                        }
                        --channel.lineCounter;
                        channel.hdmaDoTransfer = channel.lineCounter.getBit(7);
                        if (channel.lineCounter.getBits(0, 7) == 0) {
                            channel.lineCounter = getNextByte(channel, false);
                            if (indirectAddressingMode) {
                                Byte lowByte = getNextByte(channel, false);
                                channel.indirectAddress = Word(lowByte, getNextByte(channel, false));
                                cycles += 2;
                            }
                            channel.hdmaDoTransfer = true;
                        }
                    }
                }
            }
        }
        initializationRequested = false;
        active = false;
        return cycles;
    }

    Byte getNextByte(Video::Registers::DmaChannel& channel, bool indirect)
    {
        if (indirect) {
            Long address(channel.indirectAddress, channel.indirectAddressBankByte);
            ++channel.indirectAddress;
            return memory.readByte(address);
        }
        else {
            Long address(channel.tableAddress, channel.sourceAddress.getBankByte());
            ++channel.tableAddress;
            return memory.readByte(address);
        }
    }

    int size() const override
    {
        return blockedInstruction->size();
    }

    bool enabled() const
    {
        return registers.hdmaEnabled;
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

    void applyBreakpoints() const override
    {
    }

public:
    Instruction* blockedInstruction = nullptr;

private:
    CPU::State::MemoryType& memory;
    Video::Registers& registers;
    bool active = false;
    bool initializationRequested = false;
    int iteration = -1;

    std::ostream& output;
    std::ostream& error;
};