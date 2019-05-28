#pragma once

#include <vector>

#include "Common/MemoryLocation.h"

#include "Video.h"
#include "Debugger.h"
#include "Renderer.h"

class Registers
{
public:
    enum Register
    {
        M7A = 0x211b,
        M7B = 0x211c,

        MPYL = 0x2134,
        MPYM = 0x2135,
        MPYH = 0x2136,

        NMITIMEN = 0x4200,

        DmaBase = 0x4300
    };

    enum DmaFunction
    {
        DmaControl = 0x0000,
        DmaDestination = 0x0001,
        DmaSourceLowByte = 0x0002,
        DmaSourceHighByte = 0x0003,
        DmaSourceBankByte = 0x0004,
        DmaSizeLowByte = 0x0005,
        DmaSizeHighByte = 0x0006,
    };

    static int toDmaAddress(int channel, DmaFunction function)
    {
        return DmaBase | channel << 4 | function;
    }

    Registers(std::ostream& output, std::ostream& error, Debugger& debugger, CPU::State& cpuState, Video& video)
        : output(output)
        , error(error)
        , debugger(debugger)
        , cpuState(cpuState)
        , registerBus(0x6000)
        , video(video)
    {
    }

    Registers(const Registers&) = delete;
    Registers& operator=(const Registers&) = delete;

    void makeRegister(Word address, bool cpuOutRegister, const std::string& info, bool debug = false, std::function<void(Byte value)> callback = nullptr)
    {
        std::cout << "Memory size: " << cpuState.accessMemory().size() << std::endl;
        MemoryLocation* memory = cpuState.getMemoryLocation(Long(address, 0));
        if (cpuOutRegister) {
            memory->setWriteOnly();
            memory->setValue(0);
            registerBus[address].setMappings(memory, nullptr, MemoryLocation::ReadOnly);
            memory->onWrite =
                [this, address, callback, info, debug](Byte oldValue, Byte newValue) {
                if (debug && newValue && oldValue != newValue) {
                    debugger.printMemoryRegister(true, newValue, address, info);
                }
                if (callback) {
                    callback(newValue);
                }
            };
        }
        else {
            registerBus[address].setWriteOnly();
            memory->setMappings(&registerBus[address], nullptr, MemoryLocation::ReadOnly);
            memory->onRead =
                [this, address, callback, info, debug](Byte value) {
                if (debug && value) {
                    debugger.printMemoryRegister(false, value, address, info);
                }
                if (callback) {
                    callback(value);
                }
            };
        }
    };

    void initialize()
    {
        // Registers
        makeRegister(0x2100, true, "Screen Display", false);
        makeRegister(0x2101, true, "Object Size and Chr Address", true,
            [this](Byte value) {
                video.nameBaseSelect = value.getBits(0, 3);
                output << "video.nameBaseSelect: " << video.nameBaseSelect << std::endl;
                video.nameSelect = value.getBits(3, 2);
                video.objectSize = value.getBits(5, 3);
            }
        );

        makeRegister(0x2102, true, "OAM Address low byte", false,
            [this](Byte value) {
                video.oam.address.setLowByte(value);
            });
        makeRegister(0x2103, true, "OAM Address high bit and Obj Priority", false,
            [this](Byte value) {
                video.oam.address.setHighByte(value.getBit(0));
            });
        makeRegister(0x2104, true, "OAM Data write", false,
            [this](Byte value) {
                video.oam.writeByte(value);
            }
        );

        makeRegister(0x2105, true, "BG Mode and Character Size", true);
        makeRegister(0x2106, true, "Screen Pixelation", true);
        makeRegister(0x2107, true, "BG1 Tilemap Address and Size", true);
        makeRegister(0x2108, true, "BG2 Tilemap Address and Size", true);
        makeRegister(0x2109, true, "BG3 Tilemap Address and Size", true);
        makeRegister(0x210b, true, "BG1 and 2 Chr Address", true);
        makeRegister(0x210c, true, "BG3 and 4 Chr Address", true);
        makeRegister(0x210d, true, "BG1 Horizontal Scroll / Mode 7 BG Horizontal Scroll", true);
        makeRegister(0x210e, true, "BG1 Vertical Scroll / Mode 7 BG Vertical Scroll", true);
        makeRegister(0x210f, true, "BG2 Horizontal Scroll", true);
        makeRegister(0x2110, true, "BG2 Vertical Scroll", true);
        makeRegister(0x2111, true, "BG3 Horizontal Scroll", true);
        makeRegister(0x2112, true, "BG3 Vertical Scroll", true);

        makeRegister(0x2115, true, "Video Port Control", true);
        makeRegister(0x2116, true, "VRAM Address low byte", false,
            [this](Byte value) {
                video.vram.address.setLowByte(value);
            }
        );
        makeRegister(0x2117, true, "VRAM Address high byte", false,
            [this](Byte value) {
                video.vram.address.setHighByte(value);
            }
        );
        makeRegister(0x2118, true, "VRAM Data Write low byte", false,
            [this](Byte value) {
                video.vram.writeByte(value, false, false);
            }
        );

        makeRegister(0x2119, true, "VRAM Data Write high byte", false,
            [this](Byte value) {
                Byte videoPortControl = registerBus[0x2115].getValue();
                if (!videoPortControl.getBit(7)) {
                    error << "DMA: Video port control: " << videoPortControl << std::endl;
                    throw std::logic_error("DMA: Video port control not implemented");
                }

                Word vramAddress = video.vram.address;

                video.vram.writeByte(value, true, true);

                static const int bitsPerPixel = 4;
                static const int pixelPerTile = 8 * 8;
                static const int bitPerTile = pixelPerTile * bitsPerPixel;
                static const int bitsPerWord = 16;
                static const int wordPerTile = bitPerTile / bitsPerWord;
                const int tileIndex = vramAddress / wordPerTile;
                const int tileWordOffset = vramAddress % wordPerTile;
                if (tileWordOffset == wordPerTile - 1) {
                    const std::array<std::array<uint8_t, 8>, 8> tile = video.readTile(tileIndex, bitsPerPixel);
                    static const int tilesPerRow = video.vramRenderer.width / 8;
                    const int rowIndex = tileIndex / tilesPerRow;
                    const int columnIndex = tileIndex % tilesPerRow;
                    video.vramRenderer.setGrayscaleTile(rowIndex * 8, columnIndex * 8, tile, bitsPerPixel);
                }
            }
        );

        makeRegister(M7A, true, "Mode 7 Matrix A (also multiplicand for MPYx)", false,
            [this](Byte value) {
                m7Multiplicand = value << 8 | m7Buffer;
                m7Buffer = value;
            }
        );
        makeRegister(M7B, true, "Mode 7 Matrix B (also multiplier for MPYx)", false,
            [this](Byte value) {
                m7Buffer = value;

                int product = m7Multiplicand * int8_t(value);
                registerBus[MPYL].setValue(product);
                registerBus[MPYM].setValue(product >> 8);
                registerBus[MPYH].setValue(product >> 16);
            }
        );

        makeRegister(0x2121, true, "CGRAM Address", true,
            [this](Byte value) {
                video.cgram.address.setLowByte(value);
                video.cgram.address.setHighByte(0x00);
            }
        );
        makeRegister(0x2122, true, "CGRAM Data Write", false,
            [this](Byte value) {
                Word cgramAddress = video.cgram.address;
                bool cgramHighTable = video.cgram.highTableSelect;

                video.cgram.writeByte(value);

                if (cgramHighTable) {
                    int row = cgramAddress / 0x10;
                    int column = cgramAddress % 0x10;
                    video.cgramRenderer.setPixel(row, column, video.cgram.readWord(cgramAddress));
                }
            }
        );

        makeRegister(0x2123, true, "Window Mask Settings for BG1 and BG2", true);
        makeRegister(0x2124, true, "Window Mask Settings for BG3 and BG4", true);
        makeRegister(0x2125, true, "Window Mask Settings for OBJ and Color Window", true);
        makeRegister(0x212c, true, "Main Screen Designation", true);
        makeRegister(0x212d, true, "Subscreen Designation", true);
        makeRegister(0x212e, true, "Window Mask Designation for the Main Screen", true);
        makeRegister(0x212f, true, "Window Mask Designation for the Subscreen", true);
        makeRegister(0x2130, true, "Color Addition Select", true);
        makeRegister(0x2131, true, "Color math designation", true);
        makeRegister(0x2132, true, "Fixed Color Data", false,
            [this](Byte value) {
                switch (value & 0xE0) {
                case 0x80:
                    video.clearBlueIntensity = value & 0x1F;
                    break;
                case 0x40:
                    video.clearGreenIntensity = value & 0x1F;
                    break;
                case 0x20:
                    video.clearRedIntensity = value & 0x1F;
                    break;
                default:
                    break;
                }
            }
        );

        makeRegister(0x2133, true, "Screen Mode/Video Select", true);

        // makeRegister(, true, "", true);
        // , [this](Byte value) {}

        makeRegister(MPYL, false, "Multiplication Result low byte", false);
        makeRegister(MPYM, false, "Multiplication Result middle byte", false);
        makeRegister(MPYH, false, "Multiplication Result high byte", false);

        makeRegister(0x4016, true, "NES-style Joypad Access Port 1", true);

        makeRegister(NMITIMEN, true, "Interrupt Enable Flags", true);

        makeRegister(0x4204, true, "Dividend C low byte", false);
        makeRegister(0x4205, true, "Dividend C high byte", false);
        makeRegister(0x4206, true, "Divisor B", false,
            [this](Byte value) {
                Word dividend = registerBus[0x4204].getWordValue();
                Byte divisor = value;
                Word quotient;
                Word remainder;
                if (divisor == 0) {
                    quotient = 0xffff;
                    remainder = dividend;
                }
                else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
                registerBus[0x4214].setWordValue(quotient);
                registerBus[0x4216].setWordValue(remainder);
            }
        );

        makeRegister(0x4209, true, "V Timer low byte", true);
        makeRegister(0x420a, true, "V Timer high byte", true);
        makeRegister(0x420b, true, "DMA Enable", false);
        makeRegister(0x420c, true, "HDMA Enable", true);
        makeRegister(0x4210, false, "NMI Flag and 5A22 Version", false);

        makeRegister(0x4214, false, "Quotient of Divide Result low byte", false);
        makeRegister(0x4215, false, "Quotient of Divide Result high byte", false);
        makeRegister(0x4216, false, "Multiplication Product or Divide Remainder low byte", false);
        makeRegister(0x4217, false, "Multiplication Product or Divide Remainder high byte", false);

        makeRegister(0x4218, false, "Controller Port 1 Data1 Register low byte", true);
        makeRegister(0x4219, false, "Controller Port 1 Data1 Register high byte", true);

        for (int i = 0; i < 8; ++i) {
            std::stringstream ss;
            ss << i;
            makeRegister(toDmaAddress(i, DmaControl), true, "DMA Control Channel " + ss.str());
            makeRegister(toDmaAddress(i, DmaDestination), true, "DMA Destination Register Channel " + ss.str());
            makeRegister(toDmaAddress(i, DmaSourceLowByte), true, "DMA Source Address low byte Channel " + ss.str());
            makeRegister(toDmaAddress(i, DmaSourceHighByte), true, "DMA Source Address high byte Channel " + ss.str());
            makeRegister(toDmaAddress(i, DmaSourceBankByte), true, "DMA Source Address bank byte Channel " + ss.str());
            makeRegister(toDmaAddress(i, DmaSizeLowByte), true, "DMA Size/HDMA Indirect Address low byte Channel " + ss.str());
            makeRegister(toDmaAddress(i, DmaSizeHighByte), true, "DMA Size/HDMA Indirect Address high byte Channel " + ss.str());
        }
    }

    bool nmiEnabled() const
    {
        return registerBus[NMITIMEN].getValue().getBit(7);
    }

    void setNmiActive(bool value)
    {
        registerBus[0x4210].setValue(value ? 0x82 : 0x02);
    }

    std::ostream& output;
    std::ostream& error;
    Debugger& debugger;
    std::vector<MemoryLocation> registerBus;
    CPU::State& cpuState;
    Video& video;

private:
    Byte m7Buffer = 0;
    int16_t m7Multiplicand = 0;
};
