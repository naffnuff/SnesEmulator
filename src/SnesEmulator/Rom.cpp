#include "Rom.h"

#include "Emulator.h"

void Rom::loadFromFile(const std::filesystem::path& path)
{
    output.debug("Reading ", path);

    std::vector<char> rom;

    std::ifstream ifs(path, std::ios::binary | std::ios::ate);
    if (!ifs)
    {
        throw std::runtime_error("Could not read " + path.string());
    }
    std::ifstream::pos_type pos = ifs.tellg();

    output.debug("Reading ", pos, " bytes");

    rom.resize((size_t)pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(rom.data(), pos);

    data.resize(rom.size());
    std::transform(rom.begin(), rom.end(), data.begin(), [](char c) { return Byte(c); });

    if (!tryReadHeader(0x8000) && !tryReadHeader(0))
    {
        throw std::runtime_error("Could not read header");
    }
}

void Rom::storeToMemory(CPU::State& state) const
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

void Rom::createMemoryMap(CPU::State::MemoryType& cpuMemory, Emulator& emulator) const
{
    // RAM
    for (Long address = 0x7e0000; address < 0x800000; ++address)
    {
        cpuMemory.createLocation<ReadWriteMemory>(address, Byte(0x55));
    }

    using Range = std::pair<int, int>;

    // RAM mirrors
    {
        std::vector<Range> mirrorBankRanges = { { 0x00, 0x40 }, { 0x80, 0xC0 } };
        for (const Range& mirrorBankRange : mirrorBankRanges)
        {
            for (Byte mirrorBank = Byte(mirrorBankRange.first); mirrorBank < mirrorBankRange.second; ++mirrorBank)
            {
                for (Word address = 0; address < 0x2000; ++address)
                {
                    cpuMemory.createMirror(Long(address, mirrorBank), Long(address, 0x7E));
                }
            }
        }
    }

    // I/O between the CPU and SPC700
    for (Word i = 0; i < 4; ++i)
    {
        cpuMemory.createLocation<ReadWriteRegister>(Long(0x2140 + i),
            [&emulator, i](Byte& value)
            {
                value = emulator.spcToCpuBuffers[i];
            },
            [&emulator, i](Byte, Byte newValue)
            {
                emulator.cpuToSpcBuffers[i] = newValue;
            }
        );
    }

    // Register mirrors
    {
        std::vector<Range> mirrorBankRanges = { { 0x01, 0x40 }, { 0x80, 0xC0 } };
        for (const Range& mirrorBankRange : mirrorBankRanges)
        {
            for (Byte mirrorBank = Byte(mirrorBankRange.first); mirrorBank < mirrorBankRange.second; ++mirrorBank)
            {
                for (Word address = 0x2000; address < 0x6000; ++address)
                {
                    cpuMemory.createMirror(Long(address, mirrorBank), Long(address, 0x00));
                }
            }
        }
    }

    if (romType == Rom::RomType::LoRom)
    {
        // Additional register mirrors
        for (int mirrorBank = 0xC0; mirrorBank < 0xFF; ++mirrorBank)
        {
            for (Word address = 0x2000; address < 0x6000; ++address)
            {
                cpuMemory.createMirror(Long(address, (Byte)mirrorBank), Long(address, 0x00));
            }
        }

        // ROM mirrors
        for (Byte mirrorBank = 0x0; mirrorBank < 0x7E; ++mirrorBank)
        {
            for (int localAddress = 0x8000; localAddress < Word::spaceSize; ++localAddress)
            {
                cpuMemory.createMirror(Long(Word(localAddress), mirrorBank), Long(Word(localAddress), mirrorBank + 0x80));
            }
        }
    }
    else if (romType == Rom::RomType::HiRom)
    {
        // ROM mirrors
        std::vector<Range> mirrorBankRanges = { { 0x00, 0x40 }, { 0x40, 0x7E }, { 0x80, 0xC0 } };
        for (const Range& mirrorBankRange : mirrorBankRanges)
        {
            for (Byte mirrorBank = Byte(mirrorBankRange.first), romBank = 0xC0; mirrorBank < mirrorBankRange.second; ++mirrorBank, ++romBank)
            {
                for (int localAddress = 0x8000; localAddress < Word::spaceSize; ++localAddress)
                {
                    cpuMemory.createMirror(Long(Word(localAddress), mirrorBank), Long(Word(localAddress), romBank));
                }
            }
        }
    }

    // Save RAM
    {
        if (saveRamSize > 0)
        {
            std::ifstream file(System::getRomLibraryPath() / (gameTitle + ".save"));
            file >> std::hex;

            std::vector<Range> bankRanges;
            Range addressRange;

            if (romType == Rom::RomType::LoRom)
            {
                bankRanges = { { 0x70, 0x7E } };
                addressRange = { 0x0, 0x8000 };
            }
            else if (romType == Rom::RomType::HiRom)
            {
                bankRanges = { { 0x30, 0x40 }, { 0xB0, 0xC0 } };
                addressRange = { 0x6000, 0x8000 };
            }

            Emulator::SaveRamSaver& saver = emulator.saveRamSaver;

            if (saveRamSize != saver.saveRam.size())
            {
                throw std::runtime_error("Save RAM mismatch");
            }

            const Long saveRamStartAddress(Word(addressRange.first), Byte(bankRanges.front().first));
            int localAddress = 0;
            bool createMirrors = false;

            for (const Range& bankRange : bankRanges)
            {
                for (Byte bank = Byte(bankRange.first); bank < bankRange.second; ++bank)
                {
                    for (Word address = Word(addressRange.first); address < addressRange.second; ++address, ++localAddress)
                    {
                        if (localAddress == saveRamSize)
                        {
                            localAddress = 0;
                            createMirrors = true;
                        }

                        Long longAddress(address, bank);
                        if (createMirrors)
                        {
                            Long saveRamAddress = saveRamStartAddress + localAddress;
                            cpuMemory.createMirror(longAddress, saveRamAddress);
                        }
                        else
                        {
                            Byte byte;
                            int inputValue;
                            if (file >> inputValue)
                            {
                                byte = Byte(inputValue);
                            }
                            saver.saveRam[localAddress] = byte;
                            cpuMemory.createLocation<ReadWriteRegister>(longAddress,
                                [&saver, localAddress](Byte& value)
                                {
                                    value = saver.saveRam[localAddress];
                                },
                                [&saver, localAddress](Byte oldValue, Byte newValue)
                                {
                                    if (oldValue != saver.saveRam[localAddress])
                                    {
                                        std::stringstream ss;
                                        ss << __FUNCTION__ << ": ";
                                        ss << "oldValue=" << oldValue << " != saveRamSaver.saveRam[address]=" << saver.saveRam[localAddress];
                                        ss << " @" << localAddress << std::endl;
                                        throw std::logic_error(ss.str());
                                    }
                                    if (newValue != saver.saveRam[localAddress])
                                    {
                                        saver.saveRam[localAddress] = newValue;
                                        std::scoped_lock<std::mutex> lock(saver.mutex);
                                        saver.saveRamModified = true;
                                    }
                                    saver.condition.notify_one();
                                },
                                byte);
                        }
                    }
                }
            }
        }
    } // Save RAM
}

void Rom::loadInterruptVectors(CPU::State& state) const
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

bool Rom::tryReadHeader(Word offset)
{
    output.debug("Trying to read ROM header assuming address offset ", offset);

    if ((int)data.size() < 0x10000 - offset)
    {
        output.debug("Rom too small");
        return false;
    }

    output.debug("Maker code: ", data[0xFFD6 - offset]);

    for (int i = 0; i < 21; ++i)
    {
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

bool Rom::isGameTitleCharacterValid(char c) const
{
    if (c != ' ' && c != '\'' && c != '-' && c != '_' && c != '(' && c != ')' && c != '%' && c != '+' && c != '.' && c != '!' && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9'))
    {
        output.debug("Invalid game-title character: ", c, " (", int(c), ")");
        return false;
    }
    return true;
}