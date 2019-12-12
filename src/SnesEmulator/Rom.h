#pragma once

#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#include "Common/Types.h"
#include "WDC65816/CpuState.h"

class Rom
{
public:
    Rom(std::ostream& output)
        : output(output)
    {
    }

    Rom(const Rom&) = delete;
    Rom& operator=(const Rom&) = delete;

    void loadFromFile(const std::string& path)
    {
        output << "Reading " << path << std::endl;

        std::vector<char> rom;

        std::ifstream ifs(path, std::ios::binary | std::ios::ate);
        if (!ifs) {
            throw std::runtime_error("Could not read " + path);
        }
        std::ifstream::pos_type pos = ifs.tellg();

        output << "Reading " << pos << " bytes" << std::endl;

        rom.resize((size_t)pos);

        ifs.seekg(0, std::ios::beg);
        ifs.read(rom.data(), pos);

        data.resize(rom.size());
        std::transform(rom.begin(), rom.end(), data.begin(), [](char c) { return Byte(c); });

        if (!tryReadHeader(0x8000) && !tryReadHeader(0)) {
            throw std::runtime_error("Could not read header");
        }
    }

    void storeToMemory(CPU::State& state) const
    {
        bool romLoaded = false;

        int romIndex = 0;
        for (int bank = 0; bank < Byte::spaceSize; ++bank) {
            for (int address = 0x8000; address < Word::spaceSize; ++address) {
                Long longAddress(address, bank);
                state.createMemoryLocation<ReadOnlyMemory>(longAddress, data[romIndex++]);
                if (romIndex >= (int)data.size()) {
                    output << "ROM ends at " << longAddress << std::endl << std::endl;
                    romLoaded = true;
                    break;
                }
            }
            if (romLoaded) {
                break;
            }
        }

        if (!romLoaded) {
            throw std::runtime_error("ROM not fully loaded");
        }

        state.loadInterruptVectors();

        CPU::State::InterruptVectors& nativeVectors = state.getInterruptVectors(true);
        CPU::State::InterruptVectors& emulationVectors = state.getInterruptVectors(false);

        output
            << "Native Co-processor=" << nativeVectors.Coprocessor << std::endl
            << "Native Break=" << nativeVectors.Break << std::endl
            << "Native Abort=" << nativeVectors.Abort << std::endl
            << "Native NMI=" << nativeVectors.Nmi << std::endl
            << "Native Reset=" << nativeVectors.Reset << std::endl
            << "Native IRQ=" << nativeVectors.Irq << std::endl
            << std::endl
            << "Emulation Co-processor=" << emulationVectors.Coprocessor << std::endl
            << "Emulation Break=" << emulationVectors.Break << std::endl
            << "Emulation Abort=" << emulationVectors.Abort << std::endl
            << "Emulation NMI=" << emulationVectors.Nmi << std::endl
            << "Emulation Reset=" << emulationVectors.Reset << std::endl
            << "Emulation IRQ=" << emulationVectors.Irq << std::endl
            << std::endl;

        output << "Success reading header" << std::endl;

        output << std::endl;
    }

    bool isLowRom() const
    {
        return mapMode == 0x20 || mapMode == 0x30;
    }

private:
    bool tryReadHeader(Word offset)
    {
        output << "Trying to read ROM header assuming address offset " << offset << std::endl;

        if ((int)data.size() < 0x10000 - offset) {
            output << "Rom too small" << std::endl;
            return false;
        }

        output << "Maker code: " << data[0xFFD6 - offset] << std::endl;

        for (int i = 0; i < 21; ++i) {
            gameTitle.push_back(data[0xFFC0 + i - offset]);
        }

        mapMode = data[0xFFD5 - offset];

        cartridgeType = data[0xFFD6 - offset];

        romSize = 0x400 << data[0xFFD7 - offset];

        saveRamSize = 0x400 << data[0xFFD8 - offset];

        output
            << "Game Title=" << gameTitle << std::endl
            << "Map Mode=" << mapMode << std::endl
            << "Cartridge Type=" << cartridgeType << std::endl
            << "ROM Size=" << romSize << std::endl
            << "SaveRAM Size=" << saveRamSize << std::endl
            << std::endl;

        return true;
    }

private:
    std::vector<Byte> data;
    std::ostream& output;

public:
    std::string gameTitle;
    Byte mapMode;
    Byte cartridgeType;
    int romSize;
    int saveRamSize;
};