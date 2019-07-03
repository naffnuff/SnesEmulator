#pragma once

#include <vector>

#include "Common/System.h"
#include "Common/MemoryLocation.h"

#include "Video.h"
#include "Debugger.h"
#include "Renderer.h"

class Registers
{
public:

    static int toDmaAddress(int channel, int function)
    {
        return 0x4300 | channel << 4 | function;
    }

    Registers(std::ostream& output, std::ostream& error, CPU::State& state, Video& video)
        : output(output)
        , error(error)
        , state(state)
        , video(video)
    {
    }

    Registers(const Registers&) = delete;
    Registers& operator=(const Registers&) = delete;

    void printMemoryRegister(bool write, Byte value, Word address, const std::string& info)
    {
        System::setOutputColor(output, System::Yellow, true);
        output << (write ? "Write " : "Read ") << value << " (" << std::bitset<8>(value) << ") @ " << address << " (" << info << "), " << std::endl;
        System::setOutputColor(output, System::DefaultColor, false);
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, std::function<void(Byte value)> callback = nullptr)
    {
        MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
        memory->setWriteOnly();
        memory->setValue(0);
        memory->onWrite =
            [this, address, callback, info, debug](Byte oldValue, Byte newValue) {
            if (debug && newValue && oldValue != newValue) {
                printMemoryRegister(true, newValue, address, info);
            }
            if (callback) {
                callback(newValue);
            }
        };
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Byte& variable)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable = value; });
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Word& variable)
    {
        makeWriteRegister(address, info + " low byte", debug, [&variable](Byte value) { variable.setLowByte(value); });
        makeWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte value) { variable.setHighByte(value); });
    }

    void makeWriteRegister(Word address, const std::string& info, bool debug, Video::WriteTwiceRegister& variable)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable.write(value); });
    }

    void makeReadRegister(Word address, const std::string& info, bool debug, std::function<void(Byte& value)> callback = nullptr)
    {
        MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
        memory->setReadOnlyValue(0);
        memory->onRead =
            [this, address, callback, info, debug](Byte& value) {
            if (debug) {
                printMemoryRegister(false, value, address, info);
            }
            if (callback) {
                callback(value);
            }
        };
    };

    void makeReadRegister(Word address, const std::string& info, bool debug, Word& variable)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); });
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); });
    }

    void makeReadRegister(Word address, const std::string& info, bool debug, Long& variable)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); });
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); });
        makeReadRegister(address + 2, info + " bank byte", debug, [&variable](Byte& value) { value = variable.getBankByte(); });
    }

    void initialize()
    {
        // Registers
        makeWriteRegister(0x2100, "Screen Display", false);
        makeWriteRegister(0x2101, "Object Size and Chr Address", false,
            [this](Byte value) {
                video.nameBaseSelect = value.getBits(0, 3) << 13;
                video.nameSelect = (value.getBits(3, 2) + 1) << 12;
                video.objectSizeIndex = value.getBits(5, 3);
            }
        );

        makeWriteRegister(0x2102, "OAM Address low byte", false,
            [this](Byte value) {
                video.oam.address.setLowByte(value);
            });
        makeWriteRegister(0x2103, "OAM Address high bit and Obj Priority", false,
            [this](Byte value) {
                video.oam.address.setHighByte(value.getBit(0));
                if (value.getBit(7)) {
                    error << "OAM Address high bit and Obj Priority: " << value << std::endl;
                    throw MemoryLocation::AccessException("Priority bit set");
                }
            });
        makeWriteRegister(0x2104, "OAM Data write", false,
            [this](Byte value) {
                video.oam.writeByte(value);
            }
        );

        makeWriteRegister(0x2105, "BG Mode and Character Size", true, video.backgroundModeAndCharacterSize);
        makeWriteRegister(0x2106, "Screen Pixelation", true);
        for (int i = 0; i < 2; ++i) {
            std::string bgName = "BG";
            std::string bgName1 = bgName + char('1' + i * 2);
            std::string bgName2 = bgName + char('2' + i * 2);
            makeWriteRegister(0x210b + i, bgName1 + " and " + bgName2 + " Chr Address", false,
                [this, i](Byte value) {
                    video.backgrounds[i * 2].characterAddress = value.getBits(0, 4) << 12;
                    video.backgrounds[i * 2 + 1].characterAddress = value.getBits(4, 4) << 12;
                });
        }
        for (int i = 0; i < 4; ++i) {
            std::string bgName = "BG";
            bgName += '1' + i;
            makeWriteRegister(0x2107 + i, bgName + " Tilemap Address and Size", true,
                [this, i](Byte value) {
                    video.backgrounds[i].horizontalMirroring = value.getBit(0);
                    video.backgrounds[i].verticalMirroring = value.getBit(1);
                    video.backgrounds[i].tilemapAddress = value.getBits(2, 6) << 10;
                });
            makeWriteRegister(0x210d + i * 2, bgName + " Horizontal Scroll", false, video.backgrounds[i].horizontalScroll);
            makeWriteRegister(0x210e + i * 2, bgName + " Vertical Scroll", false, video.backgrounds[i].verticalScroll);
        }

        makeWriteRegister(0x2115, "Video Port Control", true, videoPortControl);

        makeWriteRegister(0x2116, "VRAM Address", false, video.vram.address);
        makeWriteRegister(0x2118, "VRAM Data Write low byte", false, vramDataWriteLowByte);

        makeWriteRegister(0x2119, "VRAM Data Write high byte", false,
            [this](Byte value) {
                if (!videoPortControl.getBit(7)) {
                    error << "DMA: Video port control: " << videoPortControl << std::endl;
                    throw MemoryLocation::AccessException("DMA: Video port control not implemented");
                }

                Word vramAddress = video.vram.address;

                int increment = 1;
                if (videoPortControl.getBit(1)) {
                    increment = 128;
                }
                else if (videoPortControl.getBit(0)) {
                    increment = 32;
                }
                video.vram.writeByte(vramDataWriteLowByte, false, 0);
                video.vram.writeByte(value, true, increment);

                /*static const int bitsPerPixel = 4;
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
                }*/
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
                m7MultiplicationResult = m7Multiplicand * int8_t(value);
            }
        );
        makeWriteRegister(0x211d, "Mode 7 Matrix C", true);
        makeWriteRegister(0x211e, "Mode 7 Matrix D", true);
        makeWriteRegister(0x211f, "Mode 7 Center X", false);
        makeWriteRegister(0x2120, "Mode 7 Center Y", false);

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

                /*if (cgramHighTable) {
                    int row = cgramAddress / 0x10;
                    int column = cgramAddress % 0x10;
                    video.cgramRenderer.setPixel(row, column, video.cgram.readWord(cgramAddress));
                }*/
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
        makeWriteRegister(0x212c, "Main Screen Designation", true, video.mainScreenDesignation);
        makeWriteRegister(0x212d, "Subscreen Designation", true, video.subscreenDesignation);
        makeWriteRegister(0x212e, "Window Mask Designation for the Main Screen", true);
        makeWriteRegister(0x212f, "Window Mask Designation for the Subscreen", true);
        makeWriteRegister(0x2130, "Color Addition Select", true, video.colorAdditionSelect);
        makeWriteRegister(0x2131, "Color Math Designation", true, video.colorMathDesignation);
        makeWriteRegister(0x2132, "Fixed Color Data", false,
            [this](Byte value) {
                switch (value & 0xE0) {
                case 0x80:
                    video.clearColor.blue = value & 0x1F;
                    break;
                case 0x40:
                    video.clearColor.green = value & 0x1F;
                    break;
                case 0x20:
                    video.clearColor.red = value & 0x1F;
                    break;
                default:
                    break;
                }
            }
        );

        makeWriteRegister(0x2133, "Screen Mode/Video Select", true);

        // makeRegister(, true, "", true);
        // , [this](Byte value) {}

        makeReadRegister(0x2134, "Multiplication Result", false, m7MultiplicationResult);
        
        //makeWriteRegister(0x4016, "NES-style Joypad Access Port 1", true);
        //makeWriteRegister(0x4017, "NES-style Joypad Access Port 2", true);
        //makeReadRegister(0x4016, "NES-style Joypad Access Port 1", true);
        //makeReadRegister(0x4017, "NES-style Joypad Access Port 2", true);
        state.getMemoryLocation(Long(0x4016, 0))->setReadWrite();
        state.getMemoryLocation(Long(0x4017, 0))->setReadWrite();
        
        makeWriteRegister(0x4200, "Interrupt Enable Flags", true, interruptEnableFlags);
        makeWriteRegister(0x4201, "Programmable I/O port (out-port)", true);
        makeWriteRegister(0x4202, "Multiplicand A", false, multiplicandA);
        makeWriteRegister(0x4203, "Multiplicand B", false,
            [this](Byte multiplicandB) {
                product = multiplicandA * multiplicandB;
            });
        
        makeWriteRegister(0x4204, "Dividend C", false, dividend);
        makeWriteRegister(0x4206, "Divisor B", false,
            [this](Byte value) {
                Byte divisor = value;
                if (divisor == 0) {
                    quotient = 0xffff;
                    remainder = dividend;
                }
                else {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
        );

        makeWriteRegister(0x4207, "H Timer low byte", true);
        makeWriteRegister(0x4208, "H Timer high byte", true);
        makeWriteRegister(0x4209, "V Timer", false, vTimer);
        makeWriteRegister(0x420b, "DMA Enable", false);
        makeWriteRegister(0x420c, "HDMA Enable", false);
        makeWriteRegister(0x420d, "ROM Access Speed", true);

        makeReadRegister(0x4210, "NMI Flag and 5A22 Version", false,
            [this](Byte& value) {
                value = state.isNmiActive() ? 0x82 : 0x02;
            });
        makeReadRegister(0x4211, "IRQ Flag", false,
            [this](Byte& value) {
                value = state.isIrqActive() ? 0x80 : 0x00;
            });

        makeReadRegister(0x4212, "PPU Status", false,
            [this](Byte& value) {
                value.setBit(7, vBlank);
                value.setBit(6, hBlank);
            });

        makeReadRegister(0x4214, "Quotient of Divide Result", false, quotient);
        makeReadRegister(0x4216, "Multiplication Product or Divide Remainder", false, product);

        makeReadRegister(0x4218, "Controller Port 1 Data1 Register low byte", false);
        makeReadRegister(0x4219, "Controller Port 1 Data1 Register high byte", false);
        makeReadRegister(0x421a, "Controller Port 2 Data1 Register low byte", false);
        makeReadRegister(0x421b, "Controller Port 2 Data1 Register high byte", false);

        for (int i = 0; i < 8; ++i) {
            std::stringstream ss;
            ss << i;
            makeWriteRegister(toDmaAddress(i, 0), "DMA Control Channel " + ss.str(), false);
            makeWriteRegister(toDmaAddress(i, 1), "DMA Destination Register Channel " + ss.str(), false);
            makeWriteRegister(toDmaAddress(i, 2), "DMA Source Address low byte Channel " + ss.str(), false);
            makeWriteRegister(toDmaAddress(i, 3), "DMA Source Address high byte Channel " + ss.str(), false);
            makeWriteRegister(toDmaAddress(i, 4), "DMA Source Address bank byte Channel " + ss.str(), false);
            makeWriteRegister(toDmaAddress(i, 5), "DMA Size/HDMA Indirect Address low byte Channel " + ss.str(), false);
            makeWriteRegister(toDmaAddress(i, 6), "DMA Size/HDMA Indirect Address high byte Channel " + ss.str(), false);
            makeWriteRegister(toDmaAddress(i, 7), "HDMA Indirect Address bank byte Channel " + ss.str(), false);
        }
    }

    bool nmiEnabled() const
    {
        return interruptEnableFlags.getBit(7);
    }

    bool vCounterIrqEnabled() const
    {
        return interruptEnableFlags.getBit(5);
    }

    Word getVTimer() const
    {
        return vTimer;
    }

    void reset()
    {
        vBlank = false;
        hBlank = false;

        m7Buffer = 0;
        m7Multiplicand = 0;
    }

    std::ostream& output;
    std::ostream& error;
    CPU::State& state;
    Video& video;

    bool vBlank = false;
    bool hBlank = false;

private:
    Byte videoPortControl;
    Byte vramDataWriteLowByte;
    Byte m7Buffer;
    int16_t m7Multiplicand = 0;
    Long m7MultiplicationResult;
    Byte multiplicandA;
    Word dividend;
    Word quotient;
    Word product;
    Word& remainder = product;
    Byte interruptEnableFlags;
    Word vTimer;
};
