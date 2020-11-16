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
        currentAddress = value;
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
        if (currentAddress >= size) {
            throw AccessException("Processor::Table::readNextWord: Processor-memory table out-of-bounds @ ", currentAddress, ", size=", size);
        }
        Word result = Word(lowTable[currentAddress], highTable[currentAddress]);
        currentAddress += increment;
        return result;
    }

    void writeWord(Word data)
    {
        if (currentAddress >= size) {
            throw AccessException("Processor::Table::writeWord: Processor-memory table out-of-bounds @ ", currentAddress, ", size=", size);
        }
        lowTable[currentAddress] = data.getLowByte();
        highTable[currentAddress] = data.getHighByte();
        ++currentAddress;
    }

    void writeByte(Byte data, bool highTableSelect, int increment)
    {
        std::vector<Byte>& table = highTableSelect ? highTable : lowTable;
        if (currentAddress >= size) {
            //throw MemoryAccessException("Processor::Table::writeByte: Processor-memory table out-of-bounds @ " + Util::toString(address) + ", size=" + Util::toString(size));
            currentAddress &= size - 1;
        }
        /*if (address == 0x4800 && (highTableSelect && data == 0xff || !highTableSelect && data == 0xaa)) {
            throw MemoryAccessException("DAMN!");
        }*/
        table[currentAddress] = data;
        currentAddress += increment;
    }

    void writeByte(Byte data)
    {
        writeByte(data, currentHighTableSelect, currentHighTableSelect);
        currentHighTableSelect = !currentHighTableSelect;
    }

    const Word size = 0;
    Word currentAddress = 0;
    std::vector<Byte> lowTable;
    std::vector<Byte> highTable;
    bool currentHighTableSelect = false;
};

struct ReadTwiceRegister
{
    Byte read()
	{
		highByteSelect = !highByteSelect;
		if (highByteSelect)
		{
			return value.getLowByte();
		}
		else
		{
			return value.getHighByte();
        }
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

enum class Layer
{
    Background1 = 0,
    Background2 = 1,
    Background3 = 2,
    Background4 = 3,
    BackgroundCount = 4,
    Object = 4,
    Backdrop = 5
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
    bool horizontalMirroring = false;
    bool verticalMirroring = false;
    Word characterAddress;
    WriteTwiceRegister horizontalScroll;
    WriteTwiceRegister verticalScroll;
    int bitsPerPixel = 0;
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
        if (layer == Layer::Object) {
            return objectsBuffer.priorities[priority];
        } else {
            return backgroundBuffers[size_t(layer)].priorities[priority];
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

enum class ColorWindowMode
{
    Never,
    OutsideOnly,
    InsideOnly,
    Always
};

static const std::vector<ModeEntry> mode1 =
{
    { Layer::Object, 3 },
    { Layer::Background1, 1 },
    { Layer::Background2, 1 },
    { Layer::Object, 2 },
    { Layer::Background1, 0 },
    { Layer::Background2, 0 },
    { Layer::Object, 1 },
    { Layer::Background3, 1 },
    { Layer::Object, 0 },
    { Layer::Background3, 0 }
};

static const std::vector<ModeEntry> mode1e =
{
    { Layer::Background3, 1 },
    { Layer::Object, 3 },
    { Layer::Background1, 1 },
    { Layer::Background2, 1 },
    { Layer::Object, 2 },
    { Layer::Background1, 0 },
    { Layer::Background2, 0 },
    { Layer::Object, 1 },
    { Layer::Object, 0 },
    { Layer::Background3, 0 }
};

static const std::vector<ModeEntry> mode7 =
{
    { Layer::Object, 3 },
    { Layer::Object, 2 },
    { Layer::Object, 1 },
    { Layer::Background1, 0 },
    { Layer::Object, 0 }
};

}
