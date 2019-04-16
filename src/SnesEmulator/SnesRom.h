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

    void loadToState(CPU::State& state)
    {
        bool romLoaded = false;

        int romIndex = 0;
        for (int bank = 0; bank < 1 << 8; ++bank) {
            for (int address = 0x8000; address < 1 << 16; ++address) {
                Long longAddress(address, bank);
                state.getMemoryLocation(longAddress)->setReadOnlyValue(data[romIndex++]);
                if (romIndex >= (int)data.size()) {
                    output << "ROM ends at " << longAddress << std::endl;
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

        state.setProgramAddress(Long(resetAddress, 0));

        output << "Success reading header" << std::endl;

        output << std::endl;
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

        romSize = 1024 * (int)std::pow(2, (int)data[0xFFD7 - offset]);

        ramSize = data[0xFFD8 - offset];

        resetAddress = Word(data[0xFFFC - offset], data[0xFFFD - offset]);

        output
            << "gameTitle=" << gameTitle << std::endl
            << "mapMode=" << mapMode << std::endl
            << "cartridgeType=" << cartridgeType << std::endl
            << "romSize=" << romSize << std::endl
            << "ramSize=" << ramSize << std::endl
            << "resetAddress=" << resetAddress
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
    Byte ramSize;
    Word resetAddress;
};