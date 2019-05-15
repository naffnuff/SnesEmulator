#pragma once

#include <vector>

#include "Common/Types.h"

class VideoMemory
{
public:
    VideoMemory()
        : vramLowTable(0x8000)
        , vramHighTable(0x8000)
        , cgramLowTable(0x100)
        , cgramHighTable(0x100)
    {
    }

    VideoMemory(VideoMemory&) = delete;
    VideoMemory& operator=(VideoMemory&) = delete;

    Word readCgramWord(Byte address) const
    {
        return Word(cgramHighTable[address] << 8 | cgramLowTable[address]);
    }

    std::array<std::array<uint8_t, 8>, 8> readTile(int tileIndex, int bitsPerPixel)
    {
        static const int pixelsPerTile = 8 * 8;
        const int bitsPerTile = pixelsPerTile * bitsPerPixel;
        static const int bitsPerWord = 16;
        static const int tileWordCount = bitsPerTile / bitsPerWord;
        int tileAddress = tileIndex * tileWordCount;
        std::array<std::array<uint8_t, 8>, 8> result;
        for (int row = 0; row < 8; ++row) {
            std::bitset<8> firstLowByte(vramLowTable[tileAddress]);
            std::bitset<8> firstHighByte(vramHighTable[tileAddress]);
            std::bitset<8> secondLowByte(vramLowTable[tileAddress + tileWordCount / 2]);
            std::bitset<8> secondHighByte(vramHighTable[tileAddress + tileWordCount / 2]);
            for (int column = 0; column < 8; ++column) {
                Byte pixel;
                if (bitsPerPixel >= 2) {
                    int firstLowBitValue = firstLowByte[7 - column] ? 1 : 0;
                    int firstHighBitValue = firstHighByte[7 - column] ? 2 : 0;
                    pixel = firstLowBitValue + firstHighBitValue;
                }
                if (bitsPerPixel >= 4) {
                    int secondLowBitValue = secondLowByte[7 - column] ? 4 : 0;
                    int secondHighBitValue = secondHighByte[7 - column] ? 8 : 0;
                    pixel += secondLowBitValue + secondHighBitValue;
                }
                result[row][column] = pixel;
            }
            ++tileAddress;
        }
        return result;
    }

    std::vector<Byte> vramLowTable;
    std::vector<Byte> vramHighTable;
    std::vector<Byte> cgramLowTable;
    std::vector<Byte> cgramHighTable;

    bool cgramHighTableSelect = false;
};