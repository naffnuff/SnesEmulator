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

        void writeByte(Byte data, bool highTableSelect, int increment)
        {
            (highTableSelect ? highTable : lowTable)[address] = data;
            address += increment;
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
        bool sizeSelect = false;
        int x = 0;
        int y = 0;
        int tileIndex = 0;
        bool nameTable = false;
        int palette = 0;
        int priority = 0;
        bool horizontalFlip = false;
        bool verticalFlip = false;
    };

    class WriteTwiceRegister
    {
    public:
        void write(Byte byte)
        {
            if (highByteSelect) {
                value.setHighByte(byte);
            }
            else {
                value.setLowByte(byte);
            }
            highByteSelect = !highByteSelect;
        }
        Word value;
        bool highByteSelect = false;
    };

    struct Background
    {
        Word tilemapAddress;
        bool horizontalMirroring;
        bool verticalMirroring;
        Word characterAddress;
        WriteTwiceRegister horizontalScroll;
        WriteTwiceRegister verticalScroll;
        int bitsPerPixel;
    };

    enum Layer
    {
        BackgroundLayer1 = 0,
        BackgroundLayer2 = 1,
        BackgroundLayer3 = 2,
        BackgroundLayer4 = 3,
        ObjectLayer
    };

    struct LayerEntry
    {
        Layer layer;
        int priority;
    };

    static const int rendererWidth = 256;

    Video(std::ostream& output)
        : output(output)
        , vram(0x8000)
        , cgram(0x100)
        , oam(0x110)
        , renderer(rendererWidth, 224, 3.f, false, output)
        //, vramRenderer(0x200, 0x200, 2.f, true, output)
        //, cgramRenderer(16, 16, 16.f, true, output)
        //, oamRenderer(0x100, 0x100, 3.f, true, output)
        , backgrounds(4)
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
        switch (objectSizeIndex) {
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

    /*void drawDebugInfo()
    {
        oamRenderer.clearDisplay(0);

        int rowOffset = 0;
        int columnOffset = 0;
        for (int i = 0; i < 128 && rowOffset < oamRenderer.height && columnOffset < oamRenderer.width; ++i) {
            Object object = readObject(i);

            int objectSize = getObjectSize(object.sizeSelect);
            int objectTileSize = objectSize / 8;
            for (int tileRow = 0; tileRow < objectTileSize; ++tileRow) {
                for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                    int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                    Word tileAddress = nameBaseSelect + (tileIndex << 4);
                    if (object.nameTable) {
                        tileAddress += nameSelect;
                    }
                    for (int row = 0; row < 8; ++row, ++tileAddress) {
                        const int bpp = 4;
                        drawTileLine(oamRenderer, rowOffset + tileRow * 8 + row, columnOffset, tileColumn * 8, tileAddress, object.palette, true, objectSize, object.horizontalFlip, bpp);
                    }
                }
            }
            columnOffset += 64;
            if (columnOffset >= oamRenderer.width) {
                columnOffset = 0;
                rowOffset += 64;
            }
        }
    }*/

    void drawScanline(int vCounter)
    {
        //renderer.clearScanline(vCounter, cgram.readWord(0));
        //mode1e(vCounter);
        static const std::vector<LayerEntry> mode1e =
        {
            { BackgroundLayer3, 1 },
            { ObjectLayer, 3 },
            { BackgroundLayer1, 1 },
            { BackgroundLayer2, 1 },
            { ObjectLayer, 2 },
            { BackgroundLayer1, 0 },
            { BackgroundLayer2, 0 },
            { ObjectLayer, 1 },
            { ObjectLayer, 0 },
            { BackgroundLayer3, 0 }
        };
        backgrounds[BackgroundLayer1].bitsPerPixel = 4;
        backgrounds[BackgroundLayer2].bitsPerPixel = 4;
        backgrounds[BackgroundLayer3].bitsPerPixel = 2;
        drawLayers(mode1e, vCounter);
    }

    void drawLayers(const std::vector<LayerEntry>& layers, int displayRow)
    {
        Word backdropColor = cgram.readWord(0);
        Word fixedColor = clearRedIntensity | clearGreenIntensity << 5 | clearBlueIntensity << 10;

        std::array<std::array<std::array<int, rendererWidth>, 2>, 4> mainScreenBackgroundLayers;
        createBackgroundLayers(mainScreenBackgroundLayers, displayRow, mainScreenDesignation);
        std::array<std::array<int, rendererWidth>, 4> mainScreenObjectLayers;
        createObjectLayers(mainScreenObjectLayers, displayRow, mainScreenDesignation.getBit(4));

        std::array<std::array<std::array<int, rendererWidth>, 2>, 4> subscreenBackgroundLayers;
        createBackgroundLayers(subscreenBackgroundLayers, displayRow, subscreenDesignation);
        std::array<std::array<int, rendererWidth>, 4> subscreenObjectLayers;
        createObjectLayers(subscreenObjectLayers, displayRow, subscreenDesignation.getBit(4));

        for (int displayColumn = 0; displayColumn < renderer.width; ++displayColumn) {
            Word mainScreenPixel = calculatePixel(layers, mainScreenBackgroundLayers, mainScreenObjectLayers, mainScreenDesignation, displayRow, displayColumn, backdropColor);
            Word addendPixel;
            if (true) {
                addendPixel = calculatePixel(layers, subscreenBackgroundLayers, subscreenObjectLayers, subscreenDesignation, displayRow, displayColumn, fixedColor);
            }
            else {
                addendPixel = fixedColor;
            }
            Word sumPixel = mainScreenPixel;
            // add pixels
            renderer.setPixel(displayRow, displayColumn, sumPixel);
        }
    }

    Word calculatePixel(const std::vector<LayerEntry>& layers, std::array<std::array<std::array<int, rendererWidth>, 2>, 4>& backgroundLayers, std::array<std::array<int, rendererWidth>, 4>& objectLayers, Byte designation, int displayRow, int displayColumn, Word defaultPixel)
    {
        for (const LayerEntry& layer : layers) {
            if (designation.getBit(layer.layer)) {
                if (layer.layer == ObjectLayer) {
                    int result = objectLayers[layer.priority][displayColumn];
                    if (result != -1) {
                        return result;
                    }
                }
                else {
                    int result = backgroundLayers[layer.layer][layer.priority][displayColumn];
                    if (result != -1) {
                        return result;
                    }
                }
            }
        }
        return defaultPixel;
    }

    void createBackgroundLayers(std::array<std::array<std::array<int, rendererWidth>, 2>, 4>& backgroundLayers, int displayRow, Byte screenDesignation)
    {
        std::fill(backgroundLayers[0][0].begin(), backgroundLayers[3][1].end(), -1);
        for (int layerIndex = 0; layerIndex < 4; ++layerIndex) {
            if (screenDesignation.getBit(layerIndex)) {
                for (int priority = 0; priority < 2; ++priority) {
                    drawBackgroundLine(backgroundLayers[layerIndex][priority], backgrounds[layerIndex], displayRow, priority);
                }
            }
        }
    }

    void drawBackgroundLine(std::array<int, rendererWidth>& layer, Background& background, int displayRow, int priority)
    {
        const int tileSize = 8;
        for (int i = 0, tileRow = 0; tileRow < 32; ++tileRow) {
            int row = displayRow - tileRow * tileSize + background.verticalScroll.value;
            if (row >= 0 && row < tileSize) {
                for (int tileColumn = 0; tileColumn < 32; ++tileColumn) {
                    Word tileData = vram.readWord(background.tilemapAddress + (tileRow << 5) + tileColumn);
                    int tilePriority = tileData.getBits(13, 1);
                    if (priority == tilePriority) {
                        Word tileNumber = tileData.getBits(0, 10);
                        int palette = tileData.getBits(10, 3);
                        bool horizontalFlip = tileData.getBit(14);
                        bool verticalFlip = tileData.getBit(15);
                        Word tileAddress = background.characterAddress + (tileNumber * tileSize * background.bitsPerPixel / 2) + (verticalFlip ? tileSize - 1 - row : row);
                        drawTileLine(layer, tileColumn * tileSize + background.horizontalScroll.value, 0, tileAddress, std::pow(2, background.bitsPerPixel) * palette, tileSize, horizontalFlip, background.bitsPerPixel);
                    }
                }
            }
        }
    }

    void createObjectLayers(std::array<std::array<int, rendererWidth>, 4>& objectLayers, int displayRow, bool objectsVisible)
    {
        std::fill(objectLayers[0].begin(), objectLayers[3].end(), -1);
        if (objectsVisible) {
            for (int i = 0; i < 128; ++i) {
                Object object = readObject(i);
                drawObjectLine(objectLayers[object.priority], object, displayRow);
            }
        }
    }

    void drawObjectLine(std::array<int, rendererWidth>& layer, Object& object, int displayRow)
    {
        int objectSize = getObjectSize(object.sizeSelect);
        int row = displayRow - object.y;
        if (row >= 0 && row < objectSize) {
            int tileRow = 0;
            while (row >= 8) {
                ++tileRow;
                row -= 8;
            }
            int objectTileSize = objectSize / 8;
            for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                Word tileAddress = nameBaseSelect + (tileIndex << 4);
                if (object.nameTable) {
                    tileAddress += nameSelect;
                }
                tileAddress += row;
                const int bpp = 4;
                drawTileLine(layer, object.x, tileColumn * 8, tileAddress, 0x80 + std::pow(2, bpp) * object.palette, objectSize, object.horizontalFlip, bpp);
            }
        }
    }

    void drawTileLine(std::array<int, rendererWidth>& layer, int displayStartColumn, int displayColumnOffset, Word tileAddress, int paletteAddress, int objectSize, bool horizontalFlip, int bpp)
    {
        Byte firstLowByte(vram.lowTable[tileAddress]);
        Byte firstHighByte(vram.highTable[tileAddress]);
        Byte secondLowByte(vram.lowTable[tileAddress + 8]);
        Byte secondHighByte(vram.highTable[tileAddress + 8]);
        for (int column = 0; column < 8; ++column) {
            Byte paletteIndex;
            paletteIndex.setBit(0, firstLowByte.getBit(7 - column));
            paletteIndex.setBit(1, firstHighByte.getBit(7 - column));
            if (bpp >= 4) {
                paletteIndex.setBit(2, secondLowByte.getBit(7 - column));
                paletteIndex.setBit(3, secondHighByte.getBit(7 - column));
            }
            if (paletteIndex > 0) {
                Word colorAddress = paletteAddress + paletteIndex;
                int color = cgram.readWord(colorAddress);
                if (horizontalFlip) {
                    layer[displayStartColumn + objectSize - 1 - displayColumnOffset - column] = color;
                }
                else {
                    layer[displayStartColumn + displayColumnOffset + column] = color;
                }
            }
        }
    }

    /*bool getObjectPixel(const Object& object, int displayRow, int displayColumn, Word& result)
    {
        int objectSize = getObjectSize(object.sizeSelect);
        int row = displayRow - object.y;
        if (row >= 0 && row < objectSize) {
            int column = displayColumn - object.x;
            if (column >= 0 && column < objectSize) {
                int tileRow = 0;
                while (row >= 8) {
                    ++tileRow;
                    row -= 8;
                }
                int tileColumn = 0;
                while (column >= 8) {
                    ++tileColumn;
                    column -= 8;
                }
                int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                Word tileAddress = nameBaseSelect + (tileIndex << 4);
                if (object.nameTable) {
                    tileAddress += nameSelect;
                }
                tileAddress += row;
                const int bpp = 4;
                return getTilePixel(tileAddress, column, object.palette, true, objectSize, bpp, result);
            }
        }
        return false;
    }*/

    /*bool getBackgroundPixel(const Background& background, int displayRow, int displayColumn, int priority, int bitsPerPixel, Word& result)
    {
        static const int tileSize = 8;
        const int tileRow = displayRow / tileSize;
        const int tileColumn = displayColumn / tileSize;
        Word tileData = vram.readWord(background.tilemapAddress + (tileRow << 5) + tileColumn);
        int tilePriority = tileData.getBits(13, 1);
        if (priority == tilePriority) {
            Word tileNumber = tileData.getBits(0, 10);
            int palette = tileData.getBits(10, 3);
            bool horizontalFlip = tileData.getBit(14);
            bool verticalFlip = tileData.getBit(15);
            int row = displayRow % tileSize;
            if (verticalFlip) {
                row = tileSize - 1 - row;
            }
            int column = displayColumn % tileSize;
            if (horizontalFlip) {
                column = tileSize - 1 - column;
            }
            Word tileAddress = background.characterAddress + tileNumber * tileSize * bitsPerPixel / 2 + row;
            return getTilePixel(tileAddress, column, palette, false, tileSize, bitsPerPixel, result);
        }
    }

    bool getTilePixel(Word tileAddress, int column, int palette, bool spritePalette, int objectSize, int bpp, Word& result)
    {
        std::bitset<8> firstLowByte(vram.lowTable[tileAddress]);
        std::bitset<8> firstHighByte(vram.highTable[tileAddress]);
        std::bitset<8> secondLowByte(vram.lowTable[tileAddress + 8]);
        std::bitset<8> secondHighByte(vram.highTable[tileAddress + 8]);
        Byte paletteIndex;
        int firstLowBitValue = firstLowByte[7 - column] ? 1 : 0;
        int firstHighBitValue = firstHighByte[7 - column] ? 2 : 0;
        paletteIndex = firstLowBitValue | firstHighBitValue;
        if (bpp >= 4) {
            int secondLowBitValue = secondLowByte[7 - column] ? 4 : 0;
            int secondHighBitValue = secondHighByte[7 - column] ? 8 : 0;
            paletteIndex |= secondLowBitValue | secondHighBitValue;
        }
        if (paletteIndex > 0) {
            Word colorAddress = (spritePalette ? 0x80 : 0) + std::pow(2, bpp) * palette + paletteIndex;
            result = cgram.readWord(colorAddress);
            return true;
        }
        return false;
    }*/

    /*void mode1e(int displayRow)
    {
        if (mainScreenDesignation.getBit(2)) {
            drawBackgroundLine(backgrounds[2], displayRow, 2, 0);
        }
        if (mainScreenDesignation.getBit(4)) {
            for (int i = 0; i < 128; ++i) {
                Object object = readObject(i);
                if (object.priority == 0) {
                    drawObjectLine(object, displayRow);
                }
            }
            for (int i = 0; i < 128; ++i) {
                Object object = readObject(i);
                if (object.priority == 1) {
                    drawObjectLine(object, displayRow);
                }
            }
        }
        if (mainScreenDesignation.getBit(1)) {
            drawBackgroundLine(backgrounds[1], displayRow, 4, 0);
        }
        if (mainScreenDesignation.getBit(0)) {
            drawBackgroundLine(backgrounds[0], displayRow, 4, 0);
        }
        if (mainScreenDesignation.getBit(4)) {
            for (int i = 0; i < 128; ++i) {
                Object object = readObject(i);
                if (object.priority == 2) {
                    drawObjectLine(object, displayRow);
                }
            }
        }
        if (mainScreenDesignation.getBit(1)) {
            drawBackgroundLine(backgrounds[1], displayRow, 4, 1);
        }
        if (mainScreenDesignation.getBit(0)) {
            drawBackgroundLine(backgrounds[0], displayRow, 4, 1);
        }
        if (mainScreenDesignation.getBit(4)) {
            for (int i = 0; i < 128; ++i) {
                Object object = readObject(i);
                if (object.priority == 3) {
                    drawObjectLine(object, displayRow);
                }
            }
        }
        if (mainScreenDesignation.getBit(2)) {
            drawBackgroundLine(backgrounds[2], displayRow, 2, 1);
        }

    }

    void drawBackgroundLine(Background& background, int displayRow, int bpp, int priority)
    {
        const int tileSize = 8;
        for (int i = 0, tileRow = 0; tileRow < 32; ++tileRow) {
            int row = displayRow - tileRow * tileSize + background.verticalScroll.value;
            if (row >= 0 && row < tileSize) {
                for (int tileColumn = 0; tileColumn < 32; ++tileColumn) {
                    Word tileData = vram.readWord(background.tilemapAddress + (tileRow << 5) + tileColumn);
                    int tilePriority = tileData.getBits(13, 1);
                    if (priority == tilePriority) {
                        Word tileNumber = tileData.getBits(0, 10);
                        int palette = tileData.getBits(10, 3);
                        bool horizontalFlip = tileData.getBit(14);
                        bool verticalFlip = tileData.getBit(15);
                        Word tileAddress = background.characterAddress + (tileNumber * tileSize * bpp / 2) + (verticalFlip ? tileSize - 1 - row : row);
                        drawTileLine(renderer, displayRow, tileColumn * tileSize + background.horizontalScroll.value, 0, tileAddress, palette, false, tileSize, horizontalFlip, bpp);
                    }
                }
            }
        }
    }

    void drawObjectLine(Object& object, int displayRow)
    {
        int objectSize = getObjectSize(object.sizeSelect);
        int row = displayRow - object.y;
        if (row >= 0 && row < objectSize) {
            int tileRow = 0;
            while (row >= 8) {
                ++tileRow;
                row -= 8;
            }
            int objectTileSize = objectSize / 8;
            for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                Word tileAddress = nameBaseSelect + (tileIndex << 4);
                if (object.nameTable) {
                    tileAddress += nameSelect;
                }
                tileAddress += row;
                const int bpp = 4;
                drawTileLine(renderer, displayRow, object.x, tileColumn * 8, tileAddress, object.palette, true, objectSize, object.horizontalFlip, bpp);
            }
        }
    }*/

    /*void drawTileLine(Renderer& renderer, int displayRow, int displayStartColumn, int displayColumnOffset, Word tileAddress, int palette, bool spritePalette, int objectSize, bool horizontalFlip, int bpp)
    {
        std::bitset<8> firstLowByte(vram.lowTable[tileAddress]);
        std::bitset<8> firstHighByte(vram.highTable[tileAddress]);
        std::bitset<8> secondLowByte(vram.lowTable[tileAddress + 8]);
        std::bitset<8> secondHighByte(vram.highTable[tileAddress + 8]);
        for (int column = 0; column < 8; ++column) {
            Byte paletteIndex;
            int firstLowBitValue = firstLowByte[7 - column] ? 1 : 0;
            int firstHighBitValue = firstHighByte[7 - column] ? 2 : 0;
            paletteIndex = firstLowBitValue | firstHighBitValue;
            if (bpp >= 4) {
                int secondLowBitValue = secondLowByte[7 - column] ? 4 : 0;
                int secondHighBitValue = secondHighByte[7 - column] ? 8 : 0;
                paletteIndex |= secondLowBitValue | secondHighBitValue;
            }
            if (paletteIndex > 0) {
                Word colorAddress = (spritePalette ? 0x80 : 0) + std::pow(2, bpp) * palette + paletteIndex;
                Word color = cgram.readWord(colorAddress);
                if (horizontalFlip) {
                    renderer.setPixel(displayRow, displayStartColumn + objectSize - 1 - displayColumnOffset - column, color);
                }
                else {
                    renderer.setPixel(displayRow, displayStartColumn + displayColumnOffset + column, color);
                }
            }
        }
    }*/

    Object readObject(int index) const
    {
        Byte lowAddress = index * 2;
        Byte highAddress = index / 8;
        Byte highTableOffset = index % 8;
        Word firstWord(oam.lowTable[lowAddress], oam.highTable[lowAddress]);
        Word secondWord(oam.lowTable[lowAddress + 1], oam.highTable[lowAddress + 1]);
        Word thirdWord(oam.lowTable[0x100 | highAddress], oam.highTable[0x100 | highAddress]);
        Object result;
        result.sizeSelect = thirdWord.getBit(highTableOffset * 2 + 1);
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

    /*std::array<std::array<uint8_t, 8>, 8> readTile(int tileIndex, int bitsPerPixel)
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
    }*/

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

    Byte mainScreenDesignation;
    Byte subscreenDesignation;

    Byte objectSizeIndex;
    Word nameSelect;
    Word nameBaseSelect;

    std::vector<Background> backgrounds;
};