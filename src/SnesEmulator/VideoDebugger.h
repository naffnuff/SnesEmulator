#pragma once

#include "VideoProcessor.h"

//#define DEBUGOAM
//#define DEBUGBG
//#define DEBUGSPRITES
//#define DEBUGMODE7

namespace Video {

class OamViewer
{
public:
    static const int firstObjectIndex = 0;
    static const int spriteSize = 16;

#ifdef DEBUGOAM
    OamViewer(Video& video, int windowXPosition, int windowYPosition)
        : video(video)
        , renderer(windowXPosition, windowYPosition, 0x80, 0x100, 2.f, true, video.output)
    {
        thread = std::thread(std::ref(*this));
    }

    ~OamViewer()
    {
        running = false;
        thread.join();
    }

    void operator()()
    {
        renderer.title = "OAM viewer";
        renderer.initialize();
        while (running && renderer.isRunning()) {
            renderer.update();
        }
    }

    void update()
    {
        std::lock_guard lock(renderer.pixelBufferMutex);

        renderer.clearDisplay(0x7c1f);

        int rowOffset = 0;
        int columnOffset = 0;
        for (int i = firstObjectIndex; i < 128 && rowOffset < renderer.height && columnOffset < renderer.width; ++i) {
            Video::Object object = video.readObject(i);

            int objectSize = video.getObjectSize(object.sizeSelect);
            int objectTileSize = objectSize / 8;
            for (int tileRow = 0; tileRow < objectTileSize; ++tileRow) {
                for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                    int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                    Word tileAddress = video.nameBaseSelect + (tileIndex << 4);
                    if (object.nameTable) {
                        tileAddress += video.nameSelect;
                    }
                    for (int row = 0; row < 8; ++row, ++tileAddress) {
                        const int bpp = 4;
                        const int displayRow = rowOffset + tileRow * 8 + row;
                        const int displayColumnOffset = tileColumn * 8;
                        Byte firstLowByte(video.vram.lowTable[tileAddress]);
                        Byte firstHighByte(video.vram.highTable[tileAddress]);
                        Byte secondLowByte(video.vram.lowTable[tileAddress + 8]);
                        Byte secondHighByte(video.vram.highTable[tileAddress + 8]);
                        for (int column = 0; column < 8; ++column) {
                            Byte paletteIndex;
                            paletteIndex.setBit(0, firstLowByte.getBit(7 - column));
                            paletteIndex.setBit(1, firstHighByte.getBit(7 - column));
                            if (bpp >= 4) {
                                paletteIndex.setBit(2, secondLowByte.getBit(7 - column));
                                paletteIndex.setBit(3, secondHighByte.getBit(7 - column));
                            }
                            if (paletteIndex > 0) {
                                Word colorAddress = 0x80 + (1 << bpp) * object.palette + paletteIndex;
                                Word color = video.cgram.getWord(colorAddress);
                                if (object.horizontalFlip) {
                                    renderer.setPixel(displayRow, columnOffset + objectSize - 1 - displayColumnOffset - column, color);
                                } else {
                                    renderer.setPixel(displayRow, columnOffset + displayColumnOffset + column, color);
                                }
                            }
                        }
                    }
                }
            }
            columnOffset += spriteSize;
            if (columnOffset >= renderer.width) {
                columnOffset = 0;
                rowOffset += spriteSize;
            }
        }
    }

    std::thread thread;
    Renderer renderer;
    Video& video;
    bool running = true;
#else
    OamViewer(Processor&, int, int)
    {
    }
    void update()
    {
    }
#endif
};

class BackgroundViewer
{
public:
#ifdef DEBUGBG
    BackgroundViewer(Video& video, Layer backgroundLayer, int windowXPosition, int windowYPosition)
        : video(video)
        , backgroundLayer(backgroundLayer)
        , renderer(windowXPosition, windowYPosition, Video::rendererWidth * 2, Video::rendererWidth * 2, 1.f, true, video.output)
    {
        thread = std::thread(std::ref(*this));
    }

    ~BackgroundViewer()
    {
        running = false;
        thread.join();
    }

    void operator()()
    {
        renderer.title = std::string("Background ") + char('1' + backgroundLayer) + " viewer";
        renderer.initialize();
        while (running && renderer.isRunning()) {
            renderer.update();
        }
    }

    void update()
    {
        std::lock_guard lock(renderer.pixelBufferMutex);

        if (backgroundLayer == BackgroundLayer1 && video.backgroundMode == 7) {
            renderer.clearDisplay(0x3ff);
            return;
        } else {
            renderer.clearDisplay(0);
        }

        Video::Background& background = video.backgrounds[backgroundLayer];

        const int tileSize = 8;
        for (int screenRow = 0; screenRow < background.verticalMirroring + 1; ++screenRow) {
            for (int screenColumn = 0; screenColumn < background.horizontalMirroring + 1; ++screenColumn) {
                for (int tileRow = 0; tileRow < 32; ++tileRow) {
                    for (int tileColumn = 0; tileColumn < 32; ++tileColumn) {
                        Word tileDataAddress = background.tilemapAddress + (tileRow << 5) + tileColumn;
                        if (screenRow) {
                            if (background.horizontalMirroring) {
                                tileDataAddress += 0x800;
                            } else {
                                tileDataAddress += 0x400;
                            }
                        }
                        if (screenColumn) {
                            tileDataAddress += 0x400;
                        }
                        Word tileData = video.vram.getWord(tileDataAddress);
                        int tilePriority = tileData.getBits(13, 1);
                        Word tileNumber = tileData.getBits(0, 10);
                        int palette = tileData.getBits(10, 3);
                        bool horizontalFlip = tileData.getBit(14);
                        bool verticalFlip = tileData.getBit(15);
                        Word tileAddress = background.characterAddress + (tileNumber * tileSize * background.bitsPerPixel / 2);
                        int paletteAddress = (1 << background.bitsPerPixel) * palette;
                        for (int row = 0; row < 8; ++row) {
                            Byte firstLowByte(video.vram.lowTable[tileAddress + row]);
                            Byte firstHighByte(video.vram.highTable[tileAddress + row]);
                            Byte secondLowByte(video.vram.lowTable[tileAddress + row + 8]);
                            Byte secondHighByte(video.vram.highTable[tileAddress + row + 8]);
                            int displayRow = tileRow * tileSize + screenRow * Video::rendererWidth + (verticalFlip ? tileSize - 1 - row : row);
                            for (int column = 0; column < 8; ++column) {
                                Byte paletteIndex;
                                paletteIndex.setBit(0, firstLowByte.getBit(7 - column));
                                paletteIndex.setBit(1, firstHighByte.getBit(7 - column));
                                if (background.bitsPerPixel >= 4) {
                                    paletteIndex.setBit(2, secondLowByte.getBit(7 - column));
                                    paletteIndex.setBit(3, secondHighByte.getBit(7 - column));
                                }
                                Word color = 0x5555;
                                int displayColumn = tileColumn * tileSize + screenColumn * Video::rendererWidth + (horizontalFlip ? tileSize - 1 - column : column);
                                if (paletteIndex > 0) {
                                    Word colorAddress = paletteAddress + paletteIndex;
                                    color = video.cgram.getWord(colorAddress);
                                }
                                if (tilePriority) {
                                    color = Video::addColors(color, Word(0x1084), false);//0x2108));
                                }
                                renderer.setPixel(displayRow, displayColumn, color);
                            }
                        }
                    }
                }
            }
        }
    }

    std::thread thread;
    Renderer renderer;
    Video& video;
    bool running = true;
    Layer backgroundLayer;
#else
    BackgroundViewer(Processor&, Layer, int, int)
    {
    }
    void update()
    {
    }
#endif
};

class SpriteLayerViewer
{
public:
#ifdef DEBUGSPRITES
    SpriteLayerViewer(Video& video, int priority, int windowXPosition, int windowYPosition)
        : video(video)
        , priority(priority)
        , renderer(windowXPosition, windowYPosition, Video::rendererWidth, Video::rendererHeight, 1.f, true, video.output)
    {
        thread = std::thread(std::ref(*this));
    }

    ~SpriteLayerViewer()
    {
        running = false;
        thread.join();
    }

    void operator()()
    {
        renderer.title = std::string("Sprites prio ") + char('1' + priority) + " viewer";
        renderer.initialize();
        while (running && renderer.isRunning()) {
            renderer.update();
        }
    }

    void update()
    {
        std::lock_guard lock(renderer.pixelBufferMutex);
        renderer.clearDisplay(0x7c1f);
        int firstObjectIndex = 0;
        if (video.objectPriority) {
            firstObjectIndex = video.oam.address * 2;
        }
        for (int i = 127; i >= 0; --i) {
            Video::Object object = video.readObject((i + firstObjectIndex) % 128);
            if (object.priority != priority) {
                continue;
            }
            const int bitsPerPixel = 4;
            int paletteAddress = 0x80 + (1 << bitsPerPixel) * object.palette;
            int objectSize = video.getObjectSize(object.sizeSelect);
            int objectY = object.y;
            int distanceFromTop = Video::rendererWidth - objectY;
            if (distanceFromTop >= 0 && distanceFromTop < objectSize) {
                objectY -= Video::rendererWidth;
            }
            int objectTileSize = objectSize / 8;
            int objectX = object.x;
            if (objectX >= Video::rendererWidth) {
                objectX -= Video::rendererWidth * 2;
            }
            for (int tileRow = 0; tileRow < objectTileSize; ++tileRow) {
                for (int tileColumn = 0; tileColumn < objectTileSize; ++tileColumn) {
                    int tileIndex = object.tileIndex + tileRow * 0x10 + tileColumn;
                    for (int row = 0; row < 8; ++row) {
                        Word tileAddress = video.nameBaseSelect + (tileIndex << 4);
                        if (object.nameTable) {
                            tileAddress += video.nameSelect;
                        }
                        tileAddress += row;

                        for (int column = 0; column < 8; ++column) {
                            Byte paletteIndex;
                            paletteIndex.setBit(0, video.vram.lowTable[tileAddress].getBit(7 - column));
                            paletteIndex.setBit(1, video.vram.highTable[tileAddress].getBit(7 - column));
                            if (bitsPerPixel >= 4) {
                                paletteIndex.setBit(2, video.vram.lowTable[tileAddress + 8].getBit(7 - column));
                                paletteIndex.setBit(3, video.vram.highTable[tileAddress + 8].getBit(7 - column));
                            }
                            int displayRow = 0;
                            if (object.verticalFlip) {
                                displayRow = object.y + objectSize - 1 - (tileRow * 8 + row);
                            } else {
                                displayRow = object.y + tileRow * 8 + row;
                            }
                            if (displayRow < 0 || displayRow >= Video::rendererHeight) {
                                continue;
                            }
                            int displayColumn = 0;
                            if (object.horizontalFlip) {
                                displayColumn = object.x + objectSize - 1 - (tileColumn * 8 + column);
                            } else {
                                displayColumn = object.x + tileColumn * 8 + column;
                            }
                            if (displayColumn < 0 || displayColumn >= Video::rendererWidth) {
                                continue;
                            }
                            if (paletteIndex > 0) {
                                Word colorAddress = paletteAddress + paletteIndex;
                                int color = video.cgram.getWord(colorAddress);
                                renderer.setPixel(displayRow, displayColumn, color);
                            }
                        }
                    }
                }
            }
        }
    }

    std::thread thread;
    Renderer renderer;
    Video& video;
    bool running = true;
    int priority = 0;
#else
    SpriteLayerViewer(Processor&, int, int, int)
    {
    }
    void update()
    {
    }
#endif
};

class Mode7Viewer
{
public:
#ifdef DEBUGMODE7
    Mode7Viewer(Video& video, int windowXPosition, int windowYPosition)
        : video(video)
        , renderer(windowXPosition, windowYPosition, 1024, 1024, 1.f, true, video.output)
    {
        thread = std::thread(std::ref(*this));
    }

    ~Mode7Viewer()
    {
        running = false;
        thread.join();
    }

    void operator()()
    {
        renderer.title = "Mode 7 viewer";
        renderer.initialize();
        while (running && renderer.isRunning()) {
            renderer.update();
        }
    }

    void update()
    {
        std::lock_guard lock(renderer.pixelBufferMutex);
        renderer.clearDisplay(0);
        int tileDataAddress = 0;
        int i = 0;
        for (int tileRow = 0; tileRow < 128; ++tileRow) {
            for (int tileColumn = 0; tileColumn < 128; ++tileColumn) {
                Byte tileData = video.vram.lowTable[tileDataAddress];
                for (int row = 0; row < 8; ++row) {
                    for (int column = 0; column < 8; ++column) {
                        int pixelDataAddress = tileData * 8 * 8 + row * 8 + column;
                        Byte pixelData = video.vram.highTable[pixelDataAddress];
                        Word pixel = video.cgram.getWord(Word(pixelData));
                        renderer.setPixel(tileRow * 8 + row, tileColumn * 8 + column, pixel);
                    }
                }
                ++tileDataAddress;
            }
        }
    }

    std::thread thread;
    Renderer renderer;
    Video& video;
    bool running = true;
#else
    Mode7Viewer(Processor&, int, int)
    {
    }
    void update()
    {
    }
#endif
};

}
