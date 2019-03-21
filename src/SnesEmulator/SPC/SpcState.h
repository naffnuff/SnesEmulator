#pragma once


#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <iomanip>

#include "../IState.h"
#include "../Util.h"

namespace SPC {

class State : public IState
{
public:
    enum Register
    {
        A,
        X,
        Y,
        SP,
        PSW,
        RegisterCount
    };

    State()
        : programCounter(0xFFC0)
        , memory(1 << 16, 0x55)
    {
        std::array<uint8_t, 64> bootRomData = {
           0xCD, 0xEF, 0xBD, 0xE8, 0x00, 0xC6, 0x1D, 0xD0, 0xFC, 0x8F, 0xAA, 0xF4, 0x8F, 0xBB, 0xF5, 0x78,
           0xCC, 0xF4, 0xD0, 0xFB, 0x2F, 0x19, 0xEB, 0xF4, 0xD0, 0xFC, 0x7E, 0xF4, 0xD0, 0x0B, 0xE4, 0xF5,
           0xCB, 0xF4, 0xD7, 0x00, 0xFC, 0xD0, 0xF3, 0xAB, 0x01, 0x10, 0xEF, 0x7E, 0xF4, 0x10, 0xEB, 0xBA,
           0xF6, 0xDA, 0x00, 0xBA, 0xF4, 0xC4, 0xF4, 0xDD, 0x5D, 0xD0, 0xDB, 0x1F, 0x00, 0x00, 0xC0, 0xFF,
        };

        for (size_t i = 0; i < bootRomData.size(); ++i) {
            memory[programCounter + i] = bootRomData[i];
        }
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

    template<Register RegisterIndex>
    uint8_t& getRegister()
    {
        return registers[RegisterIndex];
    }

private:
    uint16_t programCounter;

    std::vector<uint8_t> memory;
    std::array<uint8_t, RegisterCount> registers;
};

}