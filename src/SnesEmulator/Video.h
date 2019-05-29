#pragma once

#include <vector>

#include "Common/Types.h"

#include "Renderer.h"

class Video
{
public:
    class Table
    {
    public:
        Table(Word size)
            : lowTable(size)
            , highTable(size)
        {
        }

        void setAddress(Word value)
        {
            address = value;
        }

        Word readWord(Word address) const
        {
            return Word(lowTable[address], highTable[address]);
        }

        void writeWord(Word data)
        {
            lowTable[address] = data.getLowByte();
            highTable[address] = data.getHighByte();
            ++address;
        }

        void writeByte(Byte data, bool highTableSelect, bool increment)
        {
            (highTableSelect ? highTable : lowTable)[address] = data;
            if (increment) {
                ++address;
            }
        }

        void writeByte(Byte data)
        {
            writeByte(data, highTableSelect, highTableSelect);
            highTableSelect = !highTableSelect;
        }

        std::vector<Byte> lowTable;
        std::vector<Byte> highTable;
        Word address = 0;
        bool highTableSelect = false;
    };

    struct Object
    {
        bool size = false;
        int x = 0;
        int y = 0;
        int tileIndex = 0;
        bool nameTable = false;
        int palette = 0;
        int priority = 0;
        bool horizontalFlip = false;
        bool verticalFlip = false;
    };

    Video(std::ostream& output)
        : output(output)
        , vram(0x8000)
        , cgram(0x100)
        , oam(0x110)
        , renderer(256, 224, 3.f, false, output)
        //, vramRenderer(0x200, 0x200, 1.f, true, output)
        //, cgramRenderer(16, 16, 16.f, true, output)
        //, oamRenderer(0x200, 0x100, 3.f, true, output)
    {
    }

    ~Video()
    {

    }

    Video(const Video&) = delete;
    Video& operator=(const Video&) = delete;

    void initialize(const std::string& gameTitle)
    {
        renderer.initialize(gameTitle);
    }

    int getObjectSize(bool sizeSelect) const
    {
        switch (objectSize) {
        case 0:
            return sizeSelect ? 16 : 8;
        case 1:
            return sizeSelect ? 32 : 8;
        case 2:
            return sizeSelect ? 64 : 8;
        case 3:
            return sizeSelect ? 32 : 16;
        case 4:
            return sizeSelect ? 64 : 16;
        case 5:
            return sizeSelect ? 64 : 32;
        default:
            throw std::logic_error("Object size not implemented.");
        }
    }

    void drawDebugInfo()
    {
        /*oamRenderer.clearDisplay(0);

        int rowOffset = 0;
        int columnOffset = 0;
        for (int i = 0; i < 128 && rowOffset < oamRenderer.height && columnOffset < oamRenderer.width; ++i) {
            Object object = readObject(i);

            int objectSize = getObjectSize(object.size);
            int objectTileSize = objectSize / 8;
            for (int tileRow = 0; tileRow < objectTileSize; ++tileRow) {
                for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                    int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                    Word tileAddress = (nameBaseSelect << 13) + (tileIndex << 4);
                    if (object.nameTable) {
                        tileAddress += (nameSelect + 1) << 12;
                    }
                    for (int row = 0; row < 8; ++row, ++tileAddress) {
                        drawRow(oamRenderer, rowOffset + tileRow * 8 + row, columnOffset, tileColumn * 8, tileAddress, object.palette, objectSize, object.horizontalFlip);
                    }
                }
            }
            columnOffset += 64;
            if (columnOffset >= oamRenderer.width) {
                columnOffset = 0;
                rowOffset += 64;
            }
        }*/
    }

    void drawScanline(int vCounter)
    {
        for (int i = 0; i < 128; ++i) {
            Object object = readObject(i);

            int objectSize = getObjectSize(object.size);
            int row = vCounter - object.y;
            if (row >= 0 && row < objectSize) {
                int tileRow = 0;
                while (row >= 8) {
                    ++tileRow;
                    row -= 8;
                }
                int objectTileSize = objectSize / 8;
                for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                    int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                    Word tileAddress = (nameBaseSelect << 13) + (tileIndex << 4);
                    if (object.nameTable) {
                        tileAddress += (nameSelect + 1) << 12;
                    }
                    tileAddress += row;
                    drawRow(renderer, vCounter, object.x, tileColumn * 8, tileAddress, object.palette, objectSize, object.horizontalFlip);
                }
            }
        }
    }

    void drawRow(Renderer& renderer, int displayRow, int displayStartColumn, int displayColumnOffset, Word tileAddress, int palette, int objectSize, bool horizontalFlip)
    {
        std::bitset<8> firstLowByte(vram.lowTable[tileAddress]);
        std::bitset<8> firstHighByte(vram.highTable[tileAddress]);
        std::bitset<8> secondLowByte(vram.lowTable[tileAddress + 8]);
        std::bitset<8> secondHighByte(vram.highTable[tileAddress + 8]);
        for (int column = 0; column < 8; ++column) {
            Byte paletteIndex;
            int firstLowBitValue = firstLowByte[7 - column] ? 1 : 0;
            int firstHighBitValue = firstHighByte[7 - column] ? 2 : 0;
            paletteIndex = firstLowBitValue + firstHighBitValue;
            int secondLowBitValue = secondLowByte[7 - column] ? 4 : 0;
            int secondHighBitValue = secondHighByte[7 - column] ? 8 : 0;
            paletteIndex += secondLowBitValue + secondHighBitValue;
            if (paletteIndex > 0) {
                Byte colorAddress = 0x80 + 0x10 * palette + paletteIndex;
                Word color(cgram.lowTable[colorAddress], cgram.highTable[colorAddress]);
                if (horizontalFlip) {
                    renderer.setPixel(displayRow, displayStartColumn + objectSize - 1 - displayColumnOffset - column, color);
                }
                else {
                    renderer.setPixel(displayRow, displayStartColumn + displayColumnOffset + column, color);
                }
            }
        }
    }

    Object readObject(int index) const
    {
        Byte lowAddress = index * 2;
        Byte highAddress = index / 8;
        Byte highTableOffset = index % 8;
        Word firstWord(oam.lowTable[lowAddress], oam.highTable[lowAddress]);
        Word secondWord(oam.lowTable[lowAddress + 1], oam.highTable[lowAddress + 1]);
        Word thirdWord(oam.lowTable[0x100 | highAddress], oam.highTable[0x100 | highAddress]);
        Object result;
        result.size = thirdWord.getBit(highTableOffset * 2 + 1);
        result.x = thirdWord.getBit(highTableOffset * 2) << 8 | firstWord.getLowByte();
        result.y = firstWord.getHighByte();
        result.tileIndex = secondWord.getLowByte();
        result.nameTable = secondWord.getHighByte().getBit(0);
        result.palette = secondWord.getHighByte().getBits(1, 3);
        result.priority = secondWord.getHighByte().getBits(4, 2);
        result.horizontalFlip = secondWord.getHighByte().getBit(6);
        result.verticalFlip = secondWord.getHighByte().getBit(7);
        return result;
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
            std::bitset<8> firstLowByte(vram.lowTable[tileAddress]);
            std::bitset<8> firstHighByte(vram.highTable[tileAddress]);
            std::bitset<8> secondLowByte(vram.lowTable[tileAddress + tileWordCount / 2]);
            std::bitset<8> secondHighByte(vram.highTable[tileAddress + tileWordCount / 2]);
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
                result[row][column] = pixel * 85;
            }
            ++tileAddress;
        }
        return result;
    }

    void clearDisplay()
    {
        renderer.clearDisplay(clearRedIntensity | clearGreenIntensity << 5 | clearBlueIntensity << 10);
    }

    std::ostream& output;

    Table vram;
    Table cgram;
    Table oam;

    Renderer renderer;
    //Renderer vramRenderer;
    //Renderer cgramRenderer;
    //Renderer oamRenderer;

    uint8_t clearBlueIntensity = 0;
    uint8_t clearGreenIntensity = 0;
    uint8_t clearRedIntensity = 0;

    Byte objectSize;
    Byte nameSelect;
    Byte nameBaseSelect;
};