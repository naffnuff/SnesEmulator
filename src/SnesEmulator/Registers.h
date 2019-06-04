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
        HdmaIndeirectAddressBankByte = 0x0007
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

    void makeWriteRegister(Word address, const std::string& info, bool debug = false, std::function<void(Byte value)> callback = nullptr)
    {
        MemoryLocation* memory = cpuState.getMemoryLocation(Long(address, 0));
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

    void makeReadRegister(Word address, const std::string& info, bool debug = false, std::function<void(Byte& value)> callback = nullptr)
    {
        MemoryLocation* memory = cpuState.getMemoryLocation(Long(address, 0));
        registerBus[address].setWriteOnly();
        memory->setMappings(&registerBus[address], nullptr, MemoryLocation::ReadOnly);
        memory->onRead =
            [this, address, callback, info, debug](Byte& value) {
            if (debug) {
                debugger.printMemoryRegister(false, value, address, info);
            }
            if (callback) {
                callback(value);
            }
        };
    };

    void initialize()
    {
        // Registers
        makeWriteRegister(0x2100, "Screen Display", false);
        makeWriteRegister(0x2101, "Object Size and Chr Address", true,
            [this](Byte value) {
                video.nameBaseSelect = value.getBits(0, 3);
                output << "video.nameBaseSelect: " << video.nameBaseSelect << std::endl;
                video.nameSelect = value.getBits(3, 2);
                video.objectSize = value.getBits(5, 3);
            }
        );

        makeWriteRegister(0x2102, "OAM Address low byte", false,
            [this](Byte value) {
                video.oam.address.setLowByte(value);
            });
        makeWriteRegister(0x2103, "OAM Address high bit and Obj Priority", false,
            [this](Byte value) {
                video.oam.address.setHighByte(value.getBit(0));
            });
        makeWriteRegister(0x2104, "OAM Data write", false,
            [this](Byte value) {
                video.oam.writeByte(value);
            }
        );

        makeWriteRegister(0x2105, "BG Mode and Character Size", true);
        makeWriteRegister(0x2106, "Screen Pixelation", true);
        makeWriteRegister(0x2107, "BG1 Tilemap Address and Size", true);
        makeWriteRegister(0x2108, "BG2 Tilemap Address and Size", true);
        makeWriteRegister(0x2109, "BG3 Tilemap Address and Size", true);
        makeWriteRegister(0x210a, "BG4 Tilemap Address and Size", true);
        makeWriteRegister(0x210b, "BG1 and 2 Chr Address", true);
        makeWriteRegister(0x210c, "BG3 and 4 Chr Address", true);
        makeWriteRegister(0x210d, "BG1 Horizontal Scroll / Mode 7 BG Horizontal Scroll", true);
        makeWriteRegister(0x210e, "BG1 Vertical Scroll / Mode 7 BG Vertical Scroll", true);
        makeWriteRegister(0x210f, "BG2 Horizontal Scroll", true);
        makeWriteRegister(0x2110, "BG2 Vertical Scroll", true);
        makeWriteRegister(0x2111, "BG3 Horizontal Scroll", true);
        makeWriteRegister(0x2112, "BG3 Vertical Scroll", true);
        makeWriteRegister(0x2113, "BG4 Horizontal Scroll", true);
        makeWriteRegister(0x2114, "BG4 Vertical Scroll", true);

        makeWriteRegister(0x2115, "Video Port Control", true);
        makeWriteRegister(0x2116, "VRAM Address low byte", false,
            [this](Byte value) {
                video.vram.address.setLowByte(value);
            }
        );
        makeWriteRegister(0x2117, "VRAM Address high byte", false,
            [this](Byte value) {
                video.vram.address.setHighByte(value);
            }
        );
        makeWriteRegister(0x2118, "VRAM Data Write low byte", false,
            [this](Byte value) {
                video.vram.writeByte(value, false, false);
            }
        );

        makeWriteRegister(0x2119, "VRAM Data Write high byte", false,
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

        makeWriteRegister(0x211a, "Mode 7 Settings", true);

        makeWriteRegister(0x211b, "Mode 7 Matrix A (also multiplicand for MPYx)", false,
            [this](Byte value) {
                m7Multiplicand = value << 8 | m7Buffer;
                m7Buffer = value;
            }
        );
        makeWriteRegister(0x211c, "Mode 7 Matrix B (also multiplier for MPYx)", false,
            [this](Byte value) {
                m7Buffer = value;

                int product = m7Multiplicand * int8_t(value);
                registerBus[0x2134].setValue(product);
                registerBus[0x2135].setValue(product >> 8);
                registerBus[0x2136].setValue(product >> 16);
            }
        );
        makeWriteRegister(0x211d, "Mode 7 Matrix C", true);
        makeWriteRegister(0x211e, "Mode 7 Matrix D", true);
        makeWriteRegister(0x211f, "Mode 7 Center X", true);
        makeWriteRegister(0x2120, "Mode 7 Center Y", true);

        makeWriteRegister(0x2121, "CGRAM Address", true,
            [this](Byte value) {
                video.cgram.address.setLowByte(value);
                video.cgram.address.setHighByte(0x00);
            }
        );
        makeWriteRegister(0x2122, "CGRAM Data Write", false,
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

        makeWriteRegister(0x2123, "Window Mask Settings for BG1 and BG2", true);
        makeWriteRegister(0x2124, "Window Mask Settings for BG3 and BG4", true);
        makeWriteRegister(0x2125, "Window Mask Settings for OBJ and Color Window", true);
        makeWriteRegister(0x2126, "Window 1 Left Position", true);
        makeWriteRegister(0x2127, "Window 1 Right Position", true);
        makeWriteRegister(0x2128, "Window 2 Left Position", true);
        makeWriteRegister(0x2129, "Window 2 Right Position", true);
        makeWriteRegister(0x212a, "Window mask logic for BGs", true);
        makeWriteRegister(0x212b, "Window mask logic for OBJs and Color Window", true);
        makeWriteRegister(0x212c, "Main Screen Designation", true);
        makeWriteRegister(0x212d, "Subscreen Designation", true);
        makeWriteRegister(0x212e, "Window Mask Designation for the Main Screen", true);
        makeWriteRegister(0x212f, "Window Mask Designation for the Subscreen", true);
        makeWriteRegister(0x2130, "Color Addition Select", true);
        makeWriteRegister(0x2131, "Color math designation", true);
        makeWriteRegister(0x2132, "Fixed Color Data", false,
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

        makeWriteRegister(0x2133, "Screen Mode/Video Select", true);

        // makeRegister(, true, "", true);
        // , [this](Byte value) {}

        makeReadRegister(0x2135, "Multiplication Result middle byte", false);
        makeReadRegister(0x2134, "Multiplication Result low byte", false);
        makeReadRegister(0x2136, "Multiplication Result high byte", false);
        
        //makeWriteRegister(0x4016, "NES-style Joypad Access Port 1", true);
        //makeWriteRegister(0x4017, "NES-style Joypad Access Port 2", true);
        makeReadRegister(0x4016, "NES-style Joypad Access Port 1", true);
        makeReadRegister(0x4017, "NES-style Joypad Access Port 2", true);
        
        makeWriteRegister(0x4200, "Interrupt Enable Flags", true);
        makeWriteRegister(0x4201, "Programmable I/O port (out-port)", true);
        makeWriteRegister(0x4202, "Multiplicand A", true);
        makeWriteRegister(0x4203, "Multiplicand B", true);
        
        makeWriteRegister(0x4204, "Dividend C low byte", false);
        makeWriteRegister(0x4205, "Dividend C high byte", false);
        makeWriteRegister(0x4206, "Divisor B", false,
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

        makeWriteRegister(0x4207, "H Timer low byte", true);
        makeWriteRegister(0x4208, "H Timer high byte", true);
        makeWriteRegister(0x4209, "V Timer low byte", true);
        makeWriteRegister(0x420a, "V Timer high byte", true);
        makeWriteRegister(0x420b, "DMA Enable", false);
        makeWriteRegister(0x420c, "HDMA Enable", true);
        makeWriteRegister(0x420d, "ROM Access Speed", true);

        makeReadRegister(0x4210, "NMI Flag and 5A22 Version", false,
            [this](Byte& value) {
                value = cpuState.isNmiActive() ? 0x82 : 0x02;
            });
        makeReadRegister(0x4211, "IRQ Flag", false,
            [this](Byte& value) {
                value = cpuState.isIrqActive() ? 0x80 : 0x00;
            });

        makeReadRegister(0x4212, "PPU Status", false,
            [this](Byte& value) {
                value.setBit(7, vBlank);
                value.setBit(6, hBlank);
            });

        makeReadRegister(0x4214, "Quotient of Divide Result low byte", false);
        makeReadRegister(0x4215, "Quotient of Divide Result high byte", false);
        makeReadRegister(0x4216, "Multiplication Product or Divide Remainder low byte", false);
        makeReadRegister(0x4217, "Multiplication Product or Divide Remainder high byte", false);

        makeReadRegister(0x4218, "Controller Port 1 Data1 Register low byte", false);
        makeReadRegister(0x4219, "Controller Port 1 Data1 Register high byte", false);
        makeReadRegister(0x421a, "Controller Port 2 Data1 Register low byte", false);
        makeReadRegister(0x421b, "Controller Port 2 Data1 Register high byte", false);

        for (int i = 0; i < 8; ++i) {
            std::stringstream ss;
            ss << i;
            makeWriteRegister(toDmaAddress(i, DmaControl), "DMA Control Channel " + ss.str());
            makeWriteRegister(toDmaAddress(i, DmaDestination), "DMA Destination Register Channel " + ss.str());
            makeWriteRegister(toDmaAddress(i, DmaSourceLowByte), "DMA Source Address low byte Channel " + ss.str());
            makeWriteRegister(toDmaAddress(i, DmaSourceHighByte), "DMA Source Address high byte Channel " + ss.str());
            makeWriteRegister(toDmaAddress(i, DmaSourceBankByte), "DMA Source Address bank byte Channel " + ss.str());
            makeWriteRegister(toDmaAddress(i, DmaSizeLowByte), "DMA Size/HDMA Indirect Address low byte Channel " + ss.str());
            makeWriteRegister(toDmaAddress(i, DmaSizeHighByte), "DMA Size/HDMA Indirect Address high byte Channel " + ss.str());
            makeWriteRegister(toDmaAddress(i, HdmaIndeirectAddressBankByte), "HDMA Indirect Address bank byte Channel " + ss.str());
        }
    }

    bool nmiEnabled() const
    {
        return registerBus[0x4200].getValue().getBit(7);
    }

    bool vCounterIrqEnabled() const
    {
        return registerBus[0x4200].getValue().getBit(5);
    }

    Word getVTimer() const
    {
        return registerBus[0x4209].getWordValue();
    }

    std::ostream& output;
    std::ostream& error;
    Debugger& debugger;
    std::vector<MemoryLocation> registerBus;
    CPU::State& cpuState;
    Video& video;

    bool vBlank = false;
    bool hBlank = false;

private:
    Byte m7Buffer = 0;
    int16_t m7Multiplicand = 0;
};
