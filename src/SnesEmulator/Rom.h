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
    enum class RomType
    {
        Uninitialized,
        LoRom,
        HiRom,
        Sa1Rom,
        Sdd1Rom,
        ExHiRom
    };

public:
    Rom(Output& output)
        : output(output, "rom")
    {
    }

    Rom() = delete;

    Rom(const Rom&) = delete;
    Rom& operator=(const Rom&) = delete;

    void loadFromFile(const std::filesystem::path& path)
    {
        output.debug("Reading ", path);

        std::vector<char> rom;

        std::ifstream ifs(path, std::ios::binary | std::ios::ate);
        if (!ifs) {
            throw std::runtime_error("Could not read " + path.string());
        }
        std::ifstream::pos_type pos = ifs.tellg();

        output.debug("Reading ", pos, " bytes");

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

        int startBank = 0;
        int startAddress = 0;

        if (romType == RomType::LoRom)
        {
            startBank = 0x80;
            startAddress = 0x8000;
        }
        else if (romType == RomType::HiRom)
        {
            startBank = 0xC0;
            startAddress = 0x0;
        }
        else
        {
            throw std::runtime_error("Only the LoROM and HiROM memory maps are supported for now");
        }

        int romIndex = 0;
        for (int bank = startBank; bank < Byte::spaceSize; ++bank)
        {
            for (int address = startAddress; address < Word::spaceSize; ++address)
            {
                Long longAddress = Long(Word(address), Byte(bank));
                state.createMemoryLocation<ReadOnlyMemory>(longAddress, data[romIndex++]);
                if (romIndex >= (int)data.size())
                {
                    output.debug("ROM ends at ", longAddress);
                    romLoaded = true;
                    break;
                }
            }
            if (romLoaded)
            {
                break;
            }
        }

        if (!romLoaded)
        {
            throw std::runtime_error("ROM not fully loaded");
        }
    }

    void loadInterruptVectors(CPU::State& state) const
    {
        state.loadInterruptVectors();

        CPU::State::InterruptVectors& nativeVectors = state.getInterruptVectors(true);
        CPU::State::InterruptVectors& emulationVectors = state.getInterruptVectors(false);

        output.debug("Native Co-processor=", nativeVectors.Coprocessor);
        output.debug("Native Break=", nativeVectors.Break);
        output.debug("Native Abort=", nativeVectors.Abort);
        output.debug("Native NMI=", nativeVectors.Nmi);
        output.debug("Native Reset=", nativeVectors.Reset);
        output.debug("Native IRQ=", nativeVectors.Irq);
        output.debug();
        output.debug("Emulation Co-processor=", emulationVectors.Coprocessor);
        output.debug("Emulation Break=", emulationVectors.Break);
        output.debug("Emulation Abort=", emulationVectors.Abort);
        output.debug("Emulation NMI=", emulationVectors.Nmi);
        output.debug("Emulation Reset=", emulationVectors.Reset);
        output.debug("Emulation IRQ=", emulationVectors.Irq);
        output.debug();

        output.debug("Success reading header");

        output.debug();
    }

private:
    bool tryReadHeader(Word offset)
    {
        output.debug("Trying to read ROM header assuming address offset ", offset);

        if ((int)data.size() < 0x10000 - offset) {
            output.debug("Rom too small");
            return false;
        }

        output.debug("Maker code: ", data[0xFFD6 - offset]);

        for (int i = 0; i < 21; ++i) {
            const char c = data[0xFFC0 + size_t(i) - size_t(offset)];
            if (!isGameTitleCharacterValid(c))
            {
                gameTitle.clear();
                return false;
            }
            gameTitle.push_back(c);
        }

        mapMode = data[0xFFD5 - offset];

        cartridgeType = data[0xFFD6 - offset];

        romSize = 0x400 << data[0xFFD7 - offset];

        saveRamSize = 0x400 << data[0xFFD8 - offset];

        output.info(gameTitle);
        output.debug("Map Mode=", mapMode);
        output.debug("Cartridge Type=", cartridgeType);
        output.debug("ROM Size=", romSize);
        output.debug("SaveRAM Size=", saveRamSize);
        output.debug();

        if (mapMode == 0x20 || mapMode == 0x30)
        {
            romType = RomType::LoRom;
            if (offset != 0x8000)
            {
                throw std::runtime_error("LoROM header location mismatch");
            }
        }
        else if (mapMode == 0x21 || mapMode == 0x31)
        {
            romType = RomType::HiRom;
            if (offset != 0x0)
            {
                throw std::runtime_error("LoROM header location mismatch");
            }
        }

        return true;
    }

    bool isGameTitleCharacterValid(char c) const
    {
        if (c != ' ' && c != '\'' && c != '-' && c != '_' && c != '(' && c != ')' && c != '%' && c != '+' && c != '.' && c != '!' && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9'))
        {
            output.debug("Invalid game-title character: ", c, " (", int(c), ")");
            return false;
        }
        return true;
    }

private:
    std::vector<Byte> data;
    Output output;

public:
    std::string gameTitle;
    Byte mapMode;
    Byte cartridgeType;
    int romSize = 0;
    int saveRamSize = 0;
    RomType romType = RomType::Uninitialized;
};