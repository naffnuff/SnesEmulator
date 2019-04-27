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

    bool isLowRom() const
    {
        return mapMode == 0x20;
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

        //romSize = 1024 * (int)std::pow(2, (int)data[0xFFD7 - offset]);
        romSize = 0x400 << data[0xFFD7 - offset];

        //sRamSize = 0x400 << data[0xFFD8 - offset];
        sRamSize = 1024 * (int)std::pow(2, (int)data[0xFFD8 - offset]);

        nativeCoprocessorVector = Word(data[0xFFE4 - offset], data[0xFFE5 - offset]);
        nativeBreakVector = Word(data[0xFFE6 - offset], data[0xFFE7 - offset]);
        nativeAbortVector = Word(data[0xFFE8 - offset], data[0xFFE9 - offset]);
        nativeNmiVector = Word(data[0xFFEA - offset], data[0xFFEB - offset]);
        nativeResetVector = Word(data[0xFFEC - offset], data[0xFFED - offset]);
        nativeIrqVector = Word(data[0xFFEE - offset], data[0xFFEF - offset]);

        emulationCoprocessorVector = Word(data[0xFFF4 - offset], data[0xFFF5 - offset]);
        emulationBreakVector = Word(data[0xFFF6 - offset], data[0xFFF7 - offset]);
        emulationAbortVector = Word(data[0xFFF8 - offset], data[0xFFF9 - offset]);
        emulationNmiVector = Word(data[0xFFFA - offset], data[0xFFFB - offset]);
        emulationResetVector = Word(data[0xFFFC - offset], data[0xFFFD - offset]);
        emulationIrqVector = Word(data[0xFFFE - offset], data[0xFFFF - offset]);

        resetAddress = emulationResetVector;

        output
            << "Game Title=" << gameTitle << std::endl
            << "Map Mode=" << mapMode << std::endl
            << "Cartridge Type=" << cartridgeType << std::endl
            << "ROM Size=" << romSize << std::endl
            << "SRAM Size=" << sRamSize << std::endl
            << "Native co-processor=" << nativeCoprocessorVector << std::endl
            << "Native Break=" << nativeBreakVector << std::endl
            << "Native Abort=" << nativeAbortVector << std::endl
            << "Native NMI=" << nativeNmiVector << std::endl
            << "Native Reset=" << nativeResetVector << std::endl
            << "Native IRQ=" << nativeIrqVector << std::endl
            << "Emulation Co-processor=" << emulationCoprocessorVector << std::endl
            << "Emulation Break=" << emulationBreakVector << std::endl
            << "Emulation Abort=" << emulationAbortVector << std::endl
            << "Emulation NMI=" << emulationNmiVector << std::endl
            << "Emulation Reset=" << emulationResetVector << std::endl
            << "Emulation IRQ=" << emulationIrqVector << std::endl;

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
    int sRamSize;
    Word resetAddress;

    Word nativeCoprocessorVector;
    Word nativeBreakVector;
    Word nativeAbortVector;
    Word nativeNmiVector;
    Word nativeResetVector;
    Word nativeIrqVector;

    Word emulationCoprocessorVector;
    Word emulationBreakVector;
    Word emulationAbortVector;
    Word emulationNmiVector;
    Word emulationResetVector;
    Word emulationIrqVector;
};