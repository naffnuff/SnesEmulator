#include "CpuState.h"

#include <fstream>
#include <string>
#include <functional>
#include <bitset>

namespace CPU {

void State::loadRom(const std::string& path, std::ostream& output)
{
    output << "Reading " << path << std::endl;
    {
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

        if (!tryReadHeader(0x8000, rom, output) && !tryReadHeader(0, rom, output)) {
            throw std::runtime_error("Could not read header");
        }

        bool romLoaded = false;

        int romIndex = 0;
        for (int bank = 0; bank < 1 << 8; ++bank) {
            for (int address = 0x8000; address < (1 << 16); ++address) {
                Byte byte(rom[romIndex++]);
                memory[bank << 16 | address] = byte;
                if (romIndex >= (int)rom.size()) {
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
    }

    programCounter = resetAddress;

    output << "Success reading header" << std::endl;

    output << std::endl;
}

bool State::tryReadHeader(int offset, std::vector<char> rom, std::ostream& output)
{
    output << "Trying to read header assuming ROM address offset " << offset << std::endl;

    if ((int)rom.size() < 0x10000 - offset) {
        output << "Rom too small" << std::endl;
        return false;
    }

    std::string gameTitle;
    for (int i = 0; i < 21; ++i) {
        gameTitle.push_back((Byte)rom[0xFFC0 + i - offset]);
    }

    std::bitset<8> mapMode((Byte)rom[0xFFD5 - offset]);

    int romSize = 1024 * (int)std::pow(2, (int)rom[0xFFD7 - offset]);

    resetAddress = (Byte)rom[0xFFFC - offset];
    resetAddress += (Byte)rom[0xFFFD - offset] << 8;

    output << "gameTitle=" << gameTitle << std::endl
        << "mapMode=" << mapMode << std::endl
        << "romSize=" << romSize << std::endl
        << "resetAddress=" << resetAddress
        << std::endl;

    return true;
}

}