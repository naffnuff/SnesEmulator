#pragma once

#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#include "Common/Types.h"
#include "WDC65816/CpuState.h"

class Emulator;

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

    void loadFromFile(const std::filesystem::path& path);
    void storeToMemory(CPU::State& state) const;
    void createMemoryMap(CPU::State::MemoryType& cpuMemory, Emulator& emulator) const;
    void loadInterruptVectors(CPU::State& state) const;

private:
    bool tryReadHeader(Word offset);
    bool isGameTitleCharacterValid(char c) const;

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