#pragma once

#include <vector>

#include "Common/Types.h"

class VideoMemory
{
public:
    VideoMemory()
        : vram(0x8000)
    {
    }

    VideoMemory(VideoMemory&) = delete;
    VideoMemory& operator=(VideoMemory&) = delete;

    void setWord(Word address, Word word)
    {
        vram[address] = word;
    }

    Word getWord(Word wordAddress) const
    {
        return vram[wordAddress];
    }

    size_t getVramSize() const
    {
        return vram.size();
    }

    void setLowByte(Word address, Byte lowByte)
    {
        vram[address].setLowByte(lowByte);
    }

    void setHighByte(Word address, Byte lowByte)
    {
        vram[address].setHighByte(lowByte);
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
            std::bitset<8> firstLowByte(vram[tileAddress].getLowByte());
            std::bitset<8> firstHighByte(vram[tileAddress].getHighByte());
            std::bitset<8> secondLowByte(vram[tileAddress + tileWordCount / 2].getLowByte());
            std::bitset<8> secondHighByte(vram[tileAddress + tileWordCount / 2].getHighByte());
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

private:
    std::vector<Word> vram;
};