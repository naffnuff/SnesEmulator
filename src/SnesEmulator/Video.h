#pragma once

#include <vector>

#include "Common/Types.h"
#include "Common/Util.h"

#include "VideoModes.h"
#include "Renderer.h"

class Video
{
public:
    struct NotYetImplementedException : std::logic_error
    {
        NotYetImplementedException(const std::string& name)
            : std::logic_error("Video feature not yet implemented: " + name)
        {
        }
    };

    struct MemoryAccessException : std::logic_error
    {
        MemoryAccessException(const std::string& message)
            : std::logic_error("Bad video memory access: " + message)
        {
        }
    };

    struct RendererRunner
    {
        RendererRunner(Video& video, std::ostream& output)
            : video(video)
            , gameTitle(gameTitle)
        {

        }

        void operator()()
        {
            running = true;
            video.renderer.title = gameTitle;
            video.renderer.initialize(fullscreen, aspectRatioCorrection);
            while (running && video.renderer.isRunning()) {
                if (video.renderer.toggleFullscreenRequested) {
                    video.renderer.toggleFullscreenRequested = false;
                    fullscreen = !fullscreen;
                    video.renderer.setWindowProperties(fullscreen, aspectRatioCorrection);
                }
                video.renderer.update();
            }
            glfwTerminate();
        }

        Video& video;
        bool running = false;
        std::string gameTitle;
        bool fullscreen = true;
        bool aspectRatioCorrection = true;
    };

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
                throw MemoryAccessException("Video::Table::getByte: Video-memory table out-of-bounds @ " + Util::toString(address) + ", size=" + Util::toString(size));
            }
            return table[address];
        }

        Word getWord(Word address) const
        {
            if (address >= size) {
                throw MemoryAccessException("Video::Table::getWord: Video-memory table out-of-bounds @ " + Util::toString(address) + ", size=" + Util::toString(size));
            }
            return Word(lowTable[address], highTable[address]);
        }

        Word readNextWord(int increment)
        {
            if (address >= size) {
                throw MemoryAccessException("Video::Table::readNextWord: Video-memory table out-of-bounds @ " + Util::toString(address) + ", size=" + Util::toString(size));
            }
            Word result = Word(lowTable[address], highTable[address]);
            address += increment;
            return result;
        }

        void writeWord(Word data)
        {
            if (address >= size) {
                throw MemoryAccessException("Video::Table::writeWord: Video-memory table out-of-bounds @ " + Util::toString(address) + ", size=" + Util::toString(size));
            }
            lowTable[address] = data.getLowByte();
            highTable[address] = data.getHighByte();
            ++address;
        }

        void writeByte(Byte data, bool highTableSelect, int increment)
        {
            std::vector<Byte>& table = highTableSelect ? highTable : lowTable;
            if (address >= size) {
                //throw MemoryAccessException("Video::Table::writeByte: Video-memory table out-of-bounds @ " + Util::toString(address) + ", size=" + Util::toString(size));
                table[address & 0x7fff] = 0;
            }
            else {
                table[address] = data;
            }
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

    struct ReadTwiceRegister
    {
        Byte read()
        {
            if (highByteSelect) {
                return value.getHighByte();
            }
            else {
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
            }
            else {
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

    Video(std::ostream& output)
        : output(output)
        , vram(0x8000)
        , cgram(0x100)
        , oam(0x110)
        , renderer(1000, 40, rendererWidth, rendererHeight, 3.f, true, output)
        , rendererRunner(*this, output)
        , backgrounds(4)
        , rendererLock(renderer.pixelBufferMutex)
        , rendererThread(std::ref(rendererRunner))
    {
    }

    ~Video()
    {
        rendererRunner.running = false;
        if (rendererLock.owns_lock()) {
            rendererLock.unlock();
        }
        rendererThread.join();
    }

    Video(const Video&) = delete;
    Video& operator=(const Video&) = delete;

    void initialize(const std::string& gameTitle)
    {
        rendererRunner.gameTitle = gameTitle;
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

    void drawScanline(int vCounter)
    {
        if (screenDisplay.getBit(7)) {
            renderer.clearScanline(vCounter - 1, 0);
            return;
        }
        if (characterSize.getBits(4, 4) != 0) {
            throw NotYetImplementedException("16x16 backgrounds");
        }

        if (backgroundMode == 1) {
            drawMode(mode1Extension ? mode1e : mode1, vCounter);
        }
        else if (backgroundMode == 7) {
            if (mode7HorizontalMirroring) {
                throw Video::NotYetImplementedException("Register 211a: Horizontal mirroring");
            }
            if (mode7VerticalMirroring) {
                throw Video::NotYetImplementedException("Register 211a: Vertical mirroring");
            }
            if (mode7EmptySpaceFill) {
                throw Video::NotYetImplementedException("Register 211a: Empty space fill");
            }
            if (directColorMode) {
                throw NotYetImplementedException("Direct color mode for 256-color BGs");
            }
            drawMode(mode7, vCounter, true);
        }
        else if (backgroundMode != 0) {
            output << "BG mode: " << backgroundMode << ", e: " << mode1Extension << std::endl;
            throw NotYetImplementedException("bg mode");
        }
    }

    void drawMode(const std::vector<ModeEntry>& modeEntries, int displayRow, bool mode7 = false)
    {
        Word backdropColor = cgram.getWord(0);
        Word fixedColor = clearColor;

        std::array<WindowSettings, 5> windowSettings;
        Byte windowMaskDesignations = mainScreenWindowMaskDesignation | subscreenWindowMaskDesignation;
        for (int i = 0; i < windowSettings.size(); ++i) {
            if (windowMaskDesignations.getBit(i)) {
                windowSettings[i].window1Enabled = windowMaskSettings.getBit(i * 4 + 1);
                windowSettings[i].window1Inverted = windowMaskSettings.getBit(i * 4);
                windowSettings[i].window2Enabled = windowMaskSettings.getBit(i * 4 + 3);
                windowSettings[i].window2Inverted = windowMaskSettings.getBit(i * 4 + 2);
                windowSettings[i].windowOperator = Byte(windowMaskLogic.getBits(i * 2, 2));
            }
        }

        ScanlineBuffers mainScreenBackgroundLayers;
        createLayers(mainScreenBackgroundLayers, modeEntries, displayRow, mainScreenDesignation, mainScreenWindowMaskDesignation, windowSettings, mode7);

        ScanlineBuffers subscreenBackgroundLayers;
        createLayers(subscreenBackgroundLayers, modeEntries, displayRow, subscreenDesignation, subscreenWindowMaskDesignation, windowSettings, mode7);

        int brightness = screenDisplay.getBits(0, 4);
        float brightnessFactor = float(brightness) / float(0xf);

        WindowSettings colorWindowSettings;
        colorWindowSettings.window1Enabled = windowMaskSettings.getBit(21);
        colorWindowSettings.window1Inverted = windowMaskSettings.getBit(20);
        colorWindowSettings.window2Enabled = windowMaskSettings.getBit(23);
        colorWindowSettings.window2Inverted = windowMaskSettings.getBit(22);
        colorWindowSettings.windowOperator = Byte(windowMaskLogic.getBits(10, 2));

        for (int displayColumn = 0; displayColumn < rendererWidth; ++displayColumn) {
            Byte addendPixelIndex;
            Word addendPixel = fixedColor;
            bool disableHalfMath = false;
            if (addSubscreen) {
                addendPixelIndex = calculateSubscreenPixel(modeEntries, subscreenBackgroundLayers, subscreenDesignation, displayRow, displayColumn);
                if (addendPixelIndex > 0) {
                    addendPixel = cgram.getWord(Word(addendPixelIndex));
                }
                else {
                    disableHalfMath = true;
                }
            }
            Word mainScreenPixel = calculateMainScreenPixel(modeEntries, mainScreenBackgroundLayers, mainScreenDesignation, displayRow, displayColumn, backdropColor, addendPixel, colorMathDesignation, colorWindowSettings, disableHalfMath);
            if (brightness != 0xf) {
                mainScreenPixel = factorColors(mainScreenPixel, brightnessFactor);
            }
            renderer.setPixel(displayRow - 1, displayColumn, mainScreenPixel);
        }
    }

    void createLayers(ScanlineBuffers& buffers, const std::vector<ModeEntry>& mode, int displayRow, Byte screenDesignation, Byte windowMaskDesignation, std::array<WindowSettings, 5> & windowSettings, bool mode7)
    {
        std::bitset<rendererWidth> backgroundsBufferMask;
        for (const ModeEntry& modeEntry : mode) {
            if (modeEntry.layer < BackgroundLayerCount && screenDesignation.getBit(modeEntry.layer)) {
                ScanlineBuffer& buffer = buffers.getBuffer(Layer(modeEntry.layer), modeEntry.priority);
                //buffer.data.fill(0);
                if (mode7) {
                    drawMode7Background(buffer, displayRow);
                }
                else {
                    drawBackground(buffer, backgrounds[modeEntry.layer], displayRow, modeEntry.priority, windowMaskDesignation.getBit(modeEntry.layer), windowSettings[modeEntry.layer], backgroundsBufferMask);
                }
            }
        }
        if (screenDesignation.getBit(ObjectLayer)) {
            for (int priority = 0; priority < 4; ++priority) {
                //buffers.getBuffer(ObjectLayer, priority).data.fill(0);
            }
            int firstObjectIndex = 0;
            if (objectPriority) {
                firstObjectIndex = oam.address * 2;
            }
            std::bitset<rendererWidth> objectsBufferMask;
            for (int i = firstObjectIndex; i < 128 + firstObjectIndex; ++i) {
                Object object = readObject(i % 128);
                drawObject(buffers.getBuffer(ObjectLayer, object.priority), object, displayRow, windowMaskDesignation.getBit(ObjectLayer), windowSettings[ObjectLayer], objectsBufferMask);
            }
        }
    }

    void drawMode7Background(ScanlineBuffer& buffer, int displayRow)
    {
        int vectorElement2 = displayRow + mode7VerticalScroll - mode7CenterY;
        for (int displayColumn = 0; displayColumn < rendererWidth; ++displayColumn) {
            int vectorElement1 = displayColumn + mode7HorizontalScroll - mode7CenterX;
            int fieldColumn = ((mode7MatrixA * vectorElement1))
                + ((mode7MatrixB * vectorElement2))
                + (mode7CenterX << 8);
            int fieldRow = ((mode7MatrixC * vectorElement1))
                + ((mode7MatrixD * vectorElement2))
                + (mode7CenterY << 8);
            fieldRow >>= 8;
            fieldColumn >>= 8;
            bool calculateTile = true;
            bool zeroPixel = false;
            if (fieldRow < 0 || fieldRow >= 1024 || fieldColumn < 0 || fieldColumn >= 1024) {
                fieldRow &= 1023;
                fieldColumn &= 1023;
                if (mode7PlayingFieldSize) {
                    if (mode7EmptySpaceFill) {
                        calculateTile = false;
                    }
                    else {
                        zeroPixel = true;
                    }
                }
            }
            if (zeroPixel) {
                buffer.data[displayColumn] = 0;
            }
            else {
                Byte tileData;
                if (calculateTile) {
                    Word tileRow = fieldRow >> 3;
                    Word tileColumn = fieldColumn >> 3;
                    Word tileDataAddress = (tileRow << 7) + tileColumn;
                    tileData = vram.getByte(tileDataAddress, false);
                }
                Word row = fieldRow & 7;
                Word column = fieldColumn & 7;
                Word pixelDataAddress = (tileData << 6) + (row << 3) + column;
                Byte pixelData = vram.getByte(pixelDataAddress, true);
                buffer.data[displayColumn] = pixelData;
            }
        }
    }

    void drawBackground(ScanlineBuffer& buffer, Background& background, int displayRow, int priority, bool windowEnabled, WindowSettings& windowSettings, std::bitset<rendererWidth>& bufferMask)
    {
        const int tileSize = 8;
        int backgroundHeight = tileSize * 32 * (background.verticalMirroring + 1);
        int backgroundWidth = tileSize * 32 * (background.horizontalMirroring + 1);
        displayRow += background.verticalScroll.value;
        int tileRow = displayRow % backgroundHeight / tileSize;
        bool screenRow = false;
        if (tileRow >= 32) {
            screenRow = background.verticalMirroring;
            tileRow %= 32;
        }
        int row = displayRow % tileSize;
        int columnOffset = background.horizontalScroll.value % tileSize;
        for (int displayColumn = -columnOffset; displayColumn < rendererWidth; displayColumn += tileSize) {
            int tileColumn = (displayColumn + columnOffset + background.horizontalScroll.value) % backgroundWidth / tileSize;
            bool screenColumn = false;
            if (tileColumn >= 32) {
                screenColumn = background.horizontalMirroring;
                tileColumn %= 32;
            }
            Word tileDataAddress = background.tilemapAddress + (tileRow << 5) + tileColumn;
            if (screenRow) {
                tileDataAddress += 0x800;
            }
            if (screenColumn) {
                tileDataAddress += 0x400;
            }
            Word tileData = vram.getWord(tileDataAddress);
            int tilePriority = tileData.getBits(13, 1);
            if (priority == tilePriority) {
                Word tileNumber = tileData.getBits(0, 10);
                int palette = tileData.getBits(10, 3);
                bool horizontalFlip = tileData.getBit(14);
                bool verticalFlip = tileData.getBit(15);
                Word tileAddress = background.characterAddress + (tileNumber * tileSize * background.bitsPerPixel / 2) + (verticalFlip ? tileSize - 1 - row : row);
                drawTile(buffer, displayColumn, 0, tileAddress, (1 << background.bitsPerPixel) * palette, tileSize, horizontalFlip, background.bitsPerPixel, windowEnabled, windowSettings, bufferMask);
            }
        }
    }

    Object readObject(int index) const
    {
        Word lowAddress = index * 2;
        Word highAddress = index / 8;
        Byte highTableOffset = index % 8;
        Word firstWord = oam.getWord(lowAddress);
        Word secondWord = oam.getWord(lowAddress + 1);
        Word thirdWord = oam.getWord(0x100 | highAddress);
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

    void drawObject(ScanlineBuffer& buffer, const Object& object, int displayRow, bool windowEnabled, WindowSettings& windowSettings, std::bitset<rendererWidth>& bufferMask)
    {
        int objectSize = getObjectSize(object.sizeSelect);
        int objectY = object.y;
        int distanceFromTop = rendererWidth - objectY;
        if (distanceFromTop >= 0 && distanceFromTop < objectSize) {
            objectY -= rendererWidth;
        }
        int row = displayRow - objectY - 1;
        if (row >= 0 && row < objectSize) {
            if (object.verticalFlip) {
                row = objectSize - 1 - row;
            }
            int tileRow = 0;
            while (row >= 8) {
                ++tileRow;
                row -= 8;
            }
            int objectTileSize = objectSize / 8;
            int objectX = object.x;
            if (objectX >= rendererWidth) {
                objectX -= rendererWidth * 2;
            }
            for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                Word tileAddress = nameBaseSelect + (tileIndex << 4);
                if (object.nameTable) {
                    tileAddress += nameSelect;
                }
                tileAddress += row;
                const int bitsPerPixel = 4;
                drawTile(buffer, objectX, tileColumn * 8, tileAddress, 0x80 + (1 << bitsPerPixel) * object.palette, objectSize, object.horizontalFlip, bitsPerPixel, windowEnabled, windowSettings, bufferMask);
            }
        }
    }

    void drawTile(ScanlineBuffer& buffer, int displayStartColumn, int displayColumnOffset, Word tileAddress, Byte paletteAddress, int objectSize, bool horizontalFlip, int bitsPerPixel, bool windowEnabled, WindowSettings& windowSettings, std::bitset<rendererWidth>& bufferMask)
    {
        for (int column = 0; column < 8; ++column) {
            int displayColumn;
            if (horizontalFlip) {
                displayColumn = displayStartColumn - displayColumnOffset + objectSize - 1 - column;
            }
            else {
                displayColumn = displayStartColumn + displayColumnOffset + column;
            }
            if (displayColumn < 0 || displayColumn >= rendererWidth) {
                continue;
            }
            if (buffer.data[displayColumn] > 0) {
                continue;
            }
            if (bufferMask[displayColumn]) {
                continue;
            }
            Byte paletteIndex;
            paletteIndex.setBit(0, vram.getByte(tileAddress, false).getBit(7 - column));
            paletteIndex.setBit(1, vram.getByte(tileAddress, true).getBit(7 - column));
            if (bitsPerPixel >= 4) {
                paletteIndex.setBit(2, vram.getByte(tileAddress + 8, false).getBit(7 - column));
                paletteIndex.setBit(3, vram.getByte(tileAddress + 8, true).getBit(7 - column));
            }
            if (paletteIndex > 0) {
                Byte colorAddress = paletteAddress + paletteIndex;
                //int color = cgram.readWord(colorAddress);
                bool masked = windowEnabled && insideWindow(displayColumn, windowSettings);
                if (masked) {
                    continue;
                }
                buffer.data[displayColumn] = colorAddress;
                bufferMask[displayColumn] = true;
            }
        }
    }

    Byte calculateSubscreenPixel(const std::vector<ModeEntry>& mode, ScanlineBuffers& buffers, Byte designation, int displayRow, int displayColumn)
    {
        for (const ModeEntry& modeEntry : mode) {
            if (designation.getBit(modeEntry.layer)) {
                Byte colorIndex = buffers.getBuffer(modeEntry.layer, modeEntry.priority).data[displayColumn];
                if (colorIndex > 0) {
                    return colorIndex;
                }
            }
        }
        return 0;
    }

    Word calculateMainScreenPixel(const std::vector<ModeEntry>& mode, ScanlineBuffers& buffers, Byte designation, int displayRow, int displayColumn, Word defaultPixel, Word addendPixel, Byte colorMathDesignation, WindowSettings& colorWindowSettings, bool disableHalfMath)
    {
        bool insideColorWindow = insideWindow(displayColumn, colorWindowSettings);
        bool clipColor = setColorBlack(insideColorWindow);
        bool clipMath = preventColorMath(insideColorWindow);
        bool subtract = colorMathDesignation.getBit(7);
        bool halfMath = !disableHalfMath && !clipColor && colorMathDesignation.getBit(6);

        for (const ModeEntry& modeEntry : mode) {
            if (designation.getBit(modeEntry.layer)) {
                Byte colorIndex = buffers.getBuffer(modeEntry.layer, modeEntry.priority).data[displayColumn];
                if (colorIndex > 0) {
                    Word color = cgram.getWord(Word(colorIndex));
                    if (modeEntry.layer == ObjectLayer && colorIndex > 0x80 && colorIndex < 0xc0) {
                        return color;
                    }
                    else {
                        return applyColorMath(color, modeEntry.layer, addendPixel, colorMathDesignation, clipColor, clipMath, subtract, halfMath);
                    }
                }
            }
        }
        return applyColorMath(defaultPixel, BackdropLayer, addendPixel, colorMathDesignation, clipColor, clipMath, subtract, halfMath);
    }

    bool insideWindow(int column, const WindowSettings& settings)
    {
        bool inside = false;
        if (!settings.window1Enabled && !settings.window2Enabled) {
            inside = false;
        }
        else if (settings.window1Enabled && settings.window2Enabled) {
            bool inside1 = column >= window1Left && column <= window1Right;
            bool inside2 = column >= window2Left && column <= window2Right;
            if (settings.window1Inverted) {
                inside1 = !inside1;
            }
            if (settings.window2Inverted) {
                inside2 = !inside2;
            }
            if (settings.windowOperator == 0) {
                inside = inside1 || inside2;
            }
            else {
                throw NotYetImplementedException("Window operator " + Util::toString(settings.windowOperator));
            }
        }
        else if (settings.window1Enabled) {
            inside = column >= window1Left && column <= window1Right;
            if (settings.window1Inverted) {
                inside = !inside;
            }
        }
        else if (settings.window2Enabled) {
            inside = column >= window2Left && column <= window2Right;
            if (settings.window2Inverted) {
                inside = !inside;
            }
        }
        return inside;
    }

    bool setColorBlack(bool insideColorWindow)
    {
        switch (clipColorToBlackMode)
        {
        case Never: return false;
        case OutsideColorWindowOnly: return !insideColorWindow;
        case InsideColorWindowOnly: return insideColorWindow;
        default: return true;
        }
    }

    bool preventColorMath(bool insideColorWindow)
    {
        switch (clipColorMathMode)
        {
        case Never: return false;
        case OutsideColorWindowOnly: return !insideColorWindow;
        case InsideColorWindowOnly: return insideColorWindow;
        default: return true;
        }
    }

    Word applyColorMath(Word inputPixel, Layer layer, Word addendPixel, Byte colorMathDesignation, bool clipColor, bool clipMath, bool subtract, bool halfMath)
    {
        Word result = inputPixel;
        if (colorMathDesignation.getBit(layer)) {
            if (clipColor) {
                result = 0;
            }
            if (!clipMath) {
                if (subtract) {
                    return subtractColors(Word(result), addendPixel, halfMath);
                }
                else {
                    return addColors(Word(result), addendPixel, halfMath);
                }
            }
        }
        return result;
    }

    static Word addColors(ColorComponents a, ColorComponents b, bool halfMath)
    {
        ColorComponents c;
        c.red = a.red + b.red;
        c.green = a.green + b.green;
        c.blue = a.blue + b.blue;
        if (halfMath) {
            c.red = c.red >> 1;
            c.green = c.green >> 1;
            c.blue = c.blue >> 1;
        }
        Byte maxColor = 0x1f;
        c.red = min(c.red, maxColor);
        c.green = min(c.green, maxColor);
        c.blue = min(c.blue, maxColor);
        return c;
    }

    static Word subtractColors(ColorComponents a, ColorComponents b, bool halfMath)
    {
        ColorComponents c;
        c.red = b.red < a.red ? a.red - b.red : 0;
        c.green = b.green < a.green ? a.green - b.green : 0;
        c.blue = b.blue < a.blue ? a.blue - b.blue : 0;
        if (halfMath) {
            throw NotYetImplementedException("Subtraction half math");
            c.red = c.red >> 1;
            c.green = c.green >> 1;
            c.blue = c.blue >> 1;
        }
        return c;
    }

    static Word factorColors(ColorComponents a, float b)
    {
        ColorComponents c;
        c.red = int(a.red * b);
        c.green = int(a.green * b);
        c.blue = int(a.blue * b);
        return c;
    }

    std::ostream& output;

    Table vram;
    Table cgram;
    Table oam;

    bool objectPriority = false;

    Renderer renderer;
    RendererRunner rendererRunner;
    std::thread rendererThread;

    Byte screenDisplay;

    ColorComponents clearColor;

    Byte backgroundMode;
    bool mode1Extension = false;
    Byte characterSize;

    Byte mainScreenDesignation;
    Byte subscreenDesignation;
    Byte mainScreenWindowMaskDesignation;
    Byte subscreenWindowMaskDesignation;
    Byte colorMathDesignation;

    ColorWindowMode clipColorToBlackMode = Never;
    ColorWindowMode clipColorMathMode = Never;
    bool addSubscreen = false;
    bool directColorMode = false;

    Byte objectSizeIndex;
    Word nameSelect;
    Word nameBaseSelect;

    std::vector<Background> backgrounds;

    Byte window1Left;
    Byte window1Right;
    Byte window2Left;
    Byte window2Right;

    Long windowMaskSettings;
    Word windowMaskLogic;

    bool mode7PlayingFieldSize = false;
    int16_t mode7HorizontalScroll = 0;
    int16_t mode7VerticalScroll = 0;
    int16_t mode7MatrixA = 0;
    int16_t mode7MatrixB = 0;
    int16_t mode7MatrixC = 0;
    int16_t mode7MatrixD = 0;
    int16_t mode7CenterX = 0;
    int16_t mode7CenterY = 0;
    bool mode7HorizontalMirroring = false;
    bool mode7VerticalMirroring = false;
    bool mode7EmptySpaceFill = false;

    std::unique_lock<std::mutex> rendererLock;
};