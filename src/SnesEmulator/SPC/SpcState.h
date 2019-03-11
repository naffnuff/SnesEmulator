#pragma once


#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>

#include "../IState.h"
#include "../Util.h"

namespace SPC {

class State : public IState
{
public:
    State()
        : programCounter(0xFFC0)
        , memory(1 << 16, 0x55)
    {
        memory[0xFFC0] = 0xCD;
        memory[0xFFC1] = 0xEF;
    }

    State(State&) = delete;
    State& operator=(State&) = delete;

    std::ostream& printMemoryPage(std::ostream& output, uint32_t startAddress) const override
    {
        output << "          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        uint32_t address = startAddress - std::bitset<4>(startAddress).to_ulong();
        for (int i = 0; i < 16 && address < memory.size(); ++i) {
            uint8_t bank = uint8_t(address >> 16);
            uint16_t lowAddress = uint16_t(address);
            lowAddress = lowAddress >> 4;
            output << std::setw(2) << std::setfill('0') << +bank << ':' << std::setw(3) << std::setfill('0') << lowAddress << "x  ";

            for (int j = 0; j < 16 && address < memory.size(); ++j) {
                output << std::setw(2) << std::setfill('0') << +memory[address++] << ' ';
            }

            output << std::endl;
        }
        return output;
    }

    std::ostream& printRegisters(std::ostream& output) const override
    {
        return output;
    }

    uint32_t getProgramAddress(int offset = 0) const override
    {
        return programCounter + offset;
    }

    uint16_t getProgramCounter(int offset = 0) const override
    {
        return programCounter + offset;
    }

    uint8_t readProgramByte(int offset = 0) const override
    {
        return memory[getProgramAddress(offset)];
    }
    
    void incrementProgramCounter(uint16_t increment)
    {
        programCounter += increment;
    }

private:
    uint16_t programCounter;

    std::vector<uint8_t> memory;
};

}