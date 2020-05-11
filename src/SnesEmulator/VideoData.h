#pragma once

#include <vector>

namespace Video {

EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)
EXCEPTION(AccessException, ::AccessException)

struct Table
{
    Table(Word size)
        : size(size)
        , lowTable(size)
        , highTable(size)
    {
    }

    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;

    void setAddress(Word value)
    {
        address = value;
    }

    Byte getByte(Word address, bool highTableSelect) const
    {
        const std::vector<Byte>& table = highTableSelect ? highTable : lowTable;
        if (address >= size) {
            throw AccessException("Processor::Table::getByte: Processor-memory table out-of-bounds @ ", address, ", size=", size);
        }
        return table[address];
    }

    Word getWord(Word address) const
    {
        if (address >= size) {
            throw AccessException("Processor::Table::getWord: Processor-memory table out-of-bounds @ ", address, ", size=", size);
        }
        return Word(lowTable[address], highTable[address]);
    }

    Word readNextWord(int increment)
    {
        if (address >= size) {
            throw AccessException("Processor::Table::readNextWord: Processor-memory table out-of-bounds @ ", address, ", size=", size);
        }
        Word result = Word(lowTable[address], highTable[address]);
        address += increment;
        return result;
    }

    void writeWord(Word data)
    {
        if (address >= size) {
            throw AccessException("Processor::Table::writeWord: Processor-memory table out-of-bounds @ ", address, ", size=", size);
        }
        lowTable[address] = data.getLowByte();
        highTable[address] = data.getHighByte();
        ++address;
    }

    void writeByte(Byte data, bool highTableSelect, int increment)
    {
        std::vector<Byte>& table = highTableSelect ? highTable : lowTable;
        if (address >= size) {
            //throw MemoryAccessException("Processor::Table::writeByte: Processor-memory table out-of-bounds @ " + Util::toString(address) + ", size=" + Util::toString(size));
            address &= size - 1;
        }
        /*if (address == 0x4800 && (highTableSelect && data == 0xff || !highTableSelect && data == 0xaa)) {
            throw MemoryAccessException("DAMN!");
        }*/
        table[address] = data;
        address += increment;
    }

    void writeByte(Byte data)
    {
        writeByte(data, highTableSelect, highTableSelect);
        highTableSelect = !highTableSelect;
    }

    const Word size = 0;
    Word address = 0;
    std::vector<Byte> lowTable;
    std::vector<Byte> highTable;
    bool highTableSelect = false;
};

struct ReadTwiceRegister
{
    Byte read()
    {
        if (highByteSelect) {
            return value.getHighByte();
        } else {
            return value.getLowByte();
        }
        highByteSelect = !highByteSelect;
    }
    Word value;
    bool highByteSelect = false;
};

struct WriteTwiceRegister
{
    void write(Byte byte)
    {
        if (highByteSelect) {
            value.setHighByte(byte);
        } else {
            value.setLowByte(byte);
        }
        highByteSelect = !highByteSelect;
    }
    Word value;
    bool highByteSelect = false;
};

enum Layer
{
    BackgroundLayer1 = 0,
    BackgroundLayer2 = 1,
    BackgroundLayer3 = 2,
    BackgroundLayer4 = 3,
    BackgroundLayerCount = 4,
    ObjectLayer = 4,
    BackdropLayer = 5
};

struct ModeEntry
{
    Layer layer;
    int priority;
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

static const int rendererWidth = 256;
static const int rendererHeight = 224;

struct ScanlineBuffer
{
    std::array<Byte, rendererWidth> data;
};

struct ScanlineBuffers
{
    struct BackgroundBuffer
    {
        std::array<ScanlineBuffer, 2> priorities;
    };
    struct ObjectsBuffer
    {
        std::array<ScanlineBuffer, 4> priorities;
    };

    ScanlineBuffer& getBuffer(Layer layer, int priority)
    {
        if (layer == ObjectLayer) {
            return objectsBuffer.priorities[priority];
        } else {
            return backgroundBuffers[layer].priorities[priority];
        }
    }

    std::array<BackgroundBuffer, 4> backgroundBuffers;
    ObjectsBuffer objectsBuffer;
};

struct ColorComponents
{
    ColorComponents()
    {
    }

    ColorComponents(Word color)
    {
        red = color & 0x1f;
        green = color >> 5 & 0x1f;
        blue = color >> 10 & 0x1f;
    }

    operator Word() const
    {
        return blue << 10 | green << 5 | red;
    }

    Byte red;
    Byte green;
    Byte blue;
};

struct WindowSettings
{
    bool window1Enabled = false;
    bool window1Inverted = false;
    bool window2Enabled = false;
    bool window2Inverted = false;
    Byte windowOperator;
};

enum ColorWindowMode
{
    Never,
    OutsideColorWindowOnly,
    InsideColorWindowOnly,
    Always
};

static const std::vector<ModeEntry> mode1 =
{
    { ObjectLayer, 3 },
    { BackgroundLayer1, 1 },
    { BackgroundLayer2, 1 },
    { ObjectLayer, 2 },
    { BackgroundLayer1, 0 },
    { BackgroundLayer2, 0 },
    { ObjectLayer, 1 },
    { BackgroundLayer3, 1 },
    { ObjectLayer, 0 },
    { BackgroundLayer3, 0 }
};

static const std::vector<ModeEntry> mode1e =
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

static const std::vector<ModeEntry> mode7 =
{
    { ObjectLayer, 3 },
    { ObjectLayer, 2 },
    { ObjectLayer, 1 },
    { BackgroundLayer1, 0 },
    { ObjectLayer, 0 }
};

}
