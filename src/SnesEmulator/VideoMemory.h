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
        static const int tilePixelCount = 8 * 8;
        int tileBitCount = tilePixelCount * bitsPerPixel;
        int tileWordCount = tileBitCount / 16;
        int tileAddress = tileIndex * tileWordCount;
        std::array<std::array<uint8_t, 8>, 8> result;
        std::bitset<16> word(vram[tileAddress]);
        int tileAddressOffset = 0;
        int bitIndex = 0;
        int bitExpansion = 8 / bitsPerPixel;
        int wordBitIndex = 0;
        for (int row = 0; row < 8; ++row) {
            for (int column = 0; column < 8; ++column) {
                std::bitset<8> pixel;
                for (int i = 0; i < bitsPerPixel; ++i) {
                    for (int j = 0; j < bitExpansion; ++j) {
                        pixel[i * bitExpansion + j] = word[wordBitIndex + i];
                    }
                }
                wordBitIndex += 4;
                if (wordBitIndex == 16) {
                    ++tileAddressOffset;
                    word = std::bitset<16>(vram[tileAddress + tileAddressOffset]);
                    wordBitIndex = 0;
                }
                result[row][column] = uint8_t(pixel.to_ulong());
            }
        }
        return result;
    }

private:
    std::vector<Word> vram;
};