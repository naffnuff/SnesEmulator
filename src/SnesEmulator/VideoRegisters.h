#pragma once

#include <vector>

#include "Common/System.h"
#include "Common/Output.h"
#include "Common/Memory.h"
#include "Common/RegisterManager.h"

#include "VideoProcessor.h"
#include "VideoRenderer.h"

namespace Video
{

class Registers : public RegisterManager<CPU::State::MemoryType, Output::Color::Yellow>
{
public:
    enum class IrqMode
    {
        None = 0,
        HCounter = 1,
        VCounter = 2,
        HAndVCounter = 3
    };

    struct DmaChannel
    {
        Byte control;
        Byte destinationRegister;
        Long sourceAddress;
        Word dataSize;
        Word& indirectAddress = dataSize;
        Byte indirectAddressBankByte;
        Word tableAddress;
        Byte lineCounter;
        bool dmaActive = false;
        bool hdmaDoTransfer = false;
    };

    Registers(Output& output, CPU::State& state)
        : RegisterManager(output, "video", state.getMemory())
        , output(output, "video")
        , state(state)
        , memory(state.getMemory())
        , processor(output)
    {
    }

    Registers(const Registers&) = delete;
    Registers& operator=(const Registers&) = delete;

    void makeWriteTwiceRegister(Long address, const std::string& info, bool debug, WriteTwiceRegister& variable, bool openBus = false)
    {
        makeWriteRegister(address, info, debug, [&variable](Byte value) { variable.write(value); }, openBus);
    }

    void makeReadTwiceRegister(Long address, const std::string& info, bool debug, ReadTwiceRegister& variable)
    {
        makeReadRegister(address, info, debug, [&variable](Byte& value) { value = variable.read(); });
    }

    void initialize()
    {
        // Registers
        makeWriteRegister(0x2100, "Screen Display", false, processor.screenDisplay);
        makeWriteRegister(0x2101, "Object Size and Chr Address", false,
            [this](Byte value)
            {
                processor.nameBaseSelect = value.getBits(0, 3) << 13;
                processor.nameSelect = (value.getBits(3, 2) + 1) << 12;
                processor.objectSizeIndex = value.getBits(5, 3);
            }
        );

        makeWriteRegister(0x2102, "OAM Address low byte", false,
            [this](Byte value)
            {
                oamStartAddress.setLowByte(value);
                processor.oam.currentAddress = oamStartAddress;
            });
        makeWriteRegister(0x2103, "OAM Address high bit and Obj Priority", false,
            [this](Byte value)
            {
                oamStartAddress.setHighByte(value.getBit(0));
                processor.oam.currentAddress = oamStartAddress;
                processor.objectPriority = value.getBit(7);
            });
        makeWriteRegister(0x2104, "OAM Data write", false,
            [this](Byte value)
            {
                processor.oam.writeByte(value);
            }
        );

        makeWriteRegister(0x2105, "BG Mode and Character Size", false,
            [this](Byte value)
            {
                processor.backgroundMode = value.getBits(0, 3);
                processor.mode1Extension = value.getBit(3);
                processor.characterSize = value.getBits(4, 4);
                if (processor.backgroundMode == 1)
                {
                    processor.backgrounds[size_t(Layer::Background1)].bitsPerPixel = 4;
                    processor.backgrounds[size_t(Layer::Background2)].bitsPerPixel = 4;
                    processor.backgrounds[size_t(Layer::Background3)].bitsPerPixel = 2;
                }
                else if (processor.backgroundMode == 7)
                {
                    processor.backgrounds[size_t(Layer::Background1)].bitsPerPixel = 8;
                }
            });

        makeWriteRegister(0x2106, "Screen Pixelation", true);

        for (int i = 0; i < 2; ++i)
        {
            std::string bgName = "BG";
            std::string bgName1 = bgName + char('1' + i * 2);
            std::string bgName2 = bgName + char('2' + i * 2);
            makeWriteRegister(0x210b + i, bgName1 + " and " + bgName2 + " Chr Address", false,
                [this, i](Byte value)
                {
                    processor.backgrounds[size_t(i) * 2].characterAddress = value.getBits(0, 4) << 12;
                    processor.backgrounds[size_t(i) * 2 + 1].characterAddress = value.getBits(4, 4) << 12;
                });
        }
        for (int i = 0; i < 4; ++i)
        {
            std::string bgName = "BG";
            bgName += char('1' + i);
            makeWriteRegister(0x2107 + i, bgName + " Tilemap Address and Size", false,
                [this, i](Byte value)
                {
                    processor.backgrounds[i].horizontalMirroring = value.getBit(0);
                    processor.backgrounds[i].verticalMirroring = value.getBit(1);
                    processor.backgrounds[i].tilemapAddress = value.getBits(2, 6) << 10;
                });
            if (i > 0)
            {
                makeWriteTwiceRegister(0x210d + i * 2, bgName + " Horizontal Scroll", false, processor.backgrounds[i].horizontalScroll, true);
                makeWriteTwiceRegister(0x210e + i * 2, bgName + " Vertical Scroll", false, processor.backgrounds[i].verticalScroll, true);
            }
        }

        makeWriteRegister(0x210d, "BG1 and Mode 7 Horizontal Scroll", false,
            [this](Byte value)
            {
                processor.backgrounds[size_t(Layer::Background1)].horizontalScroll.write(value);
                processor.mode7HorizontalScroll = to13Bit2sComplement(getMode7WordValue(value));
            });
        makeWriteRegister(0x210e, "BG1 and Mode 7 Vertical Scroll", false,
            [this](Byte value)
            {
                processor.backgrounds[size_t(Layer::Background1)].verticalScroll.write(value);
                processor.mode7VerticalScroll = to13Bit2sComplement(getMode7WordValue(value));
            });

        makeWriteRegister(0x2115, "Video Port Control", false,
            [this](Byte value)
            {
                videoPortControl = value;
                incrementVramOnHighByte = value.getBit(7);
            });

        makeWriteRegister(0x2116, "VRAM Address low byte", false,
            [this](Byte value)
            {
                processor.vram.currentAddress.setLowByte(value);
                //vramBuffer = processor.vram.readNextWord(0);
            });

        makeWriteRegister(0x2117, "VRAM Address high byte", false,
            [this](Byte value)
            {
                processor.vram.currentAddress.setHighByte(value & 0x7f);
                vramBuffer = processor.vram.readNextWord(0);
            });
        //makeWriteRegister(0x2116, "VRAM Address", false, processor.vram.address);

        makeWriteRegister(0x2118, "VRAM Data Write low byte", false,
            [this](Byte value)
            {
                writeToVram(value, false, !incrementVramOnHighByte);
            }
        );

        makeWriteRegister(0x2119, "VRAM Data Write high byte", false,
            [this](Byte value)
            {
                writeToVram(value, true, incrementVramOnHighByte);
            }
        );

        makeWriteRegister(0x211a, "Mode 7 Settings", true,
            [this](Byte value)
            {
                processor.mode7HorizontalMirroring = value.getBit(0);
                processor.mode7VerticalMirroring = value.getBit(1);
                processor.mode7EmptySpaceFill = value.getBit(6);
                processor.mode7PlayingFieldSize = value.getBit(7);
            });

        makeWriteRegister(0x211b, "Mode 7 Matrix A (also multiplicand for MPYx)", false,
            [this](Byte value)
            {
                mode7Multiplicand = getMode7WordValue(value);
                processor.mode7MatrixA = mode7Multiplicand;
            }
        );
        makeWriteRegister(0x211c, "Mode 7 Matrix B (also multiplier for MPYx)", false,
            [this](Byte value)
            {
                multiplicationResult = mode7Multiplicand * int8_t(value);
                processor.mode7MatrixB = getMode7WordValue(value);
            }
        );
        makeWriteRegister(0x211d, "Mode 7 Matrix C", false,
            [this](Byte value)
            {
                processor.mode7MatrixC = getMode7WordValue(value);
            });
        makeWriteRegister(0x211e, "Mode 7 Matrix D", false,
            [this](Byte value)
            {
                processor.mode7MatrixD = getMode7WordValue(value);
            });
        makeWriteRegister(0x211f, "Mode 7 Center X", false,
            [this](Byte value)
            {
                processor.mode7CenterX = to13Bit2sComplement(getMode7WordValue(value));
            });
        makeWriteRegister(0x2120, "Mode 7 Center Y", false,
            [this](Byte value)
            {
                processor.mode7CenterY = to13Bit2sComplement(getMode7WordValue(value));
            });

        makeWriteRegister(0x2121, "CGRAM Address", false,
            [this](Byte value)
            {
                processor.cgram.currentAddress.setLowByte(value);
                processor.cgram.currentAddress.setHighByte(0x00);
            }
        );
        makeWriteRegister(0x2122, "CGRAM Data Write", false,
            [this](Byte value)
            {
                Word cgramAddress = processor.cgram.currentAddress;

                processor.cgram.writeByte(value);

                /*if (cgramHighTable) {
                    int row = cgramAddress / 0x10;
                    int column = cgramAddress & 0xf;
                    processor.cgramRenderer.setPixel(row, column, processor.cgram.readWord(cgramAddress));
                }*/
            }
        );

        makeWriteRegister(0x2123, "Window Mask Settings", true, processor.windowMaskSettings);
        makeWriteRegister(0x2126, "Window 1 Left Position", false, processor.window1Left);
        makeWriteRegister(0x2127, "Window 1 Right Position", false, processor.window1Right);
        makeWriteRegister(0x2128, "Window 2 Left Position", false, processor.window2Left);
        makeWriteRegister(0x2129, "Window 2 Right Position", false, processor.window2Right);
        makeWriteRegister(0x212a, "Window Mask Logic", true, processor.windowMaskLogic);
        makeWriteRegister(0x212c, "Main Screen Designation", false, processor.mainScreenDesignation);
        makeWriteRegister(0x212d, "Subscreen Designation", false, processor.subscreenDesignation);
        makeWriteRegister(0x212e, "Window Mask Designation for the Main Screen", true, processor.mainScreenWindowMaskDesignation);
        makeWriteRegister(0x212f, "Window Mask Designation for the Subscreen", true, processor.subscreenWindowMaskDesignation);
        makeWriteRegister(0x2130, "Color Addition Select", false,
            [this](Byte value)
            {
                processor.directColorMode = value.getBit(0);
                processor.addSubscreen = value.getBit(1);
                processor.clipColorMathMode = ColorWindowMode(int(value.getBits(4, 2)));
                processor.clipColorToBlackMode = ColorWindowMode(int(value.getBits(6, 2)));
            });
        makeWriteRegister(0x2131, "Color Math Designation", false, processor.currentColorMathDesignation);
        makeWriteRegister(0x2132, "Fixed Color Data", false,
            [this](Byte value)
            {
                switch (value & 0xE0)
                {
                case 0x80:
                    processor.clearColor.blue = value & 0x1F;
                    break;
                case 0x40:
                    processor.clearColor.green = value & 0x1F;
                    break;
                case 0x20:
                    processor.clearColor.red = value & 0x1F;
                    break;
                default:
                    break;
                }
            }
        );

        makeWriteRegister(0x2133, "Screen Mode/Video Select", true,
            [this](Byte value)
            {
                if (value.getBit(0))
                {
                    throw NotYetImplementedException("Register 2133: Screen interlace");
                }
                if (value.getBit(1))
                {
                    throw NotYetImplementedException("Register 2133: Object interlace");
                }
                if (value.getBit(2))
                {
                    throw NotYetImplementedException("Register 2133: Overscan mode");
                }
                if (value.getBit(3))
                {
                    throw NotYetImplementedException("Register 2133: Pseudo-hires mode");
                }
                if (value.getBit(6))
                {
                    throw NotYetImplementedException("Register 2133: Mode 7 extra bg");
                }
                if (value.getBit(7))
                {
                    throw NotYetImplementedException("Register 2133: External sync");
                }
            });

        // makeRegister(, true, "", true);
        // , [this](Byte value) {}

        makeReadRegister(0x2134, "Multiplication Result", false, multiplicationResult);

        makeReadRegister(0x2137, "Software Latch for H/V Counter", false,
            [this](Byte)
            {
                if (programmableIOPort.getBit(7))
                {
                    horizontalScanlineLocation.value = Word(hCounter);
                    verticalScanlineLocation.value = Word(vCounter);
                    externalLatch = true;
                }
            });

        makeReadRegister(0x2138, "Data for OAM read", false);

        makeReadRegister(0x2139, "VRAM Data read low byte", false,
            [this](Byte& value)
            {
                value = readFromVram(false, !incrementVramOnHighByte);
            });
        makeReadRegister(0x213a, "VRAM Data read high byte", false,
            [this](Byte& value)
            {
                value = readFromVram(true, incrementVramOnHighByte);
            });

        makeReadTwiceRegister(0x213c, "Horizontal Scanline Location", false, horizontalScanlineLocation);
        makeReadTwiceRegister(0x213d, "Vertical Scanline Location", false, verticalScanlineLocation);
        makeReadRegister(0x213e, "PPU Status Flag and Version", false);
        makeReadRegister(0x213f, "PPU Status Flag and Version", false,
            [this](Byte& value)
            {
                value = 3;
                value.setBit(7, interlaceField);
                value.setBit(6, externalLatch);
                if (programmableIOPort.getBit(7))
                {
                    externalLatch = false;
                }
                horizontalScanlineLocation.highByteSelect = false;
                verticalScanlineLocation.highByteSelect = false;
            });

        makeWriteRegister(0x2180, "WRAM Data read/write", false,
            [this](Byte value)
            {
                memory.writeByte(value, wramAddress++);
            });
        makeWriteRegister(0x2181, "WRAM Address", false, wramAddress);

        makeReadWriteRegister(0x4016, "NES-style Joypad Access Port 1", false,
            [this](Byte& value)
            {
                //throw Video::NotYetImplementedException("Register 4016: Read");
                //printMemoryRegister(false, value, 0x4016, "NES-style Joypad Access Port 1");
            },
            [this](Byte value)
            {
                if (value > 0)
                {
                    throw NotYetImplementedException("Register 4016: Latch on");
                }
            });
        makeReadWriteRegister(0x4017, "NES-style Joypad Access Port 2", false,
            [this](Byte& value)
            {
                //throw Video::NotYetImplementedException("Register 4017: Read");
                //printMemoryRegister(false, value, 0x4017, "NES-style Joypad Access Port 2");
            },
            [this](Byte value)
            {
                if (value > 0)
                {
                    throw NotYetImplementedException("Register 4017: Latch on");
                }
            });

        makeWriteRegister(0x4200, "Interrupt Enable Flags", false,
            [this](Byte value)
            {
                autoJoypadReadEnabled = value.getBit(0);
                irqMode = IrqMode(int(value.getBits(4, 2)));
                nmiEnabled = value.getBit(7);
            });

        makeWriteRegister(0x4201, "Programmable I/O port (out-port)", true,
            [this](Byte value)
            {
                if (programmableIOPort.getBit(7) && !value.getBit(7))
                { // 1 -> 0
                    horizontalScanlineLocation.value = Word(hCounter);
                    verticalScanlineLocation.value = Word(vCounter);
                    externalLatch = true;
                }
                if (value.getBit(6))
                {
                    //throw Video::NotYetImplementedException("Register 4201: bit 6");
                }
                programmableIOPort = value;
            });
        makeWriteRegister(0x4202, "Multiplicand A", false, multiplicandA);
        makeWriteRegister(0x4203, "Multiplicand B", false,
            [this](Byte multiplicandB)
            {
                product = multiplicandA * multiplicandB;
            });

        makeWriteRegister(0x4204, "Dividend C", false, dividend);
        makeWriteRegister(0x4206, "Divisor B", false,
            [this](Byte divisor)
            {
                if (divisor == 0)
                {
                    quotient = 0xffff;
                    remainder = dividend;
                }
                else
                {
                    quotient = dividend / divisor;
                    remainder = dividend % divisor;
                }
            }
        );

        makeWriteRegister(0x4207, "H Timer", false, hTimer);
        makeWriteRegister(0x4209, "V Timer", false, vTimer);
        makeWriteRegister(0x420b, "DMA Enable", false, dmaEnabled);
        makeWriteRegister(0x420c, "HDMA Enable", false, hdmaEnabled);
        makeWriteRegister(0x420d, "ROM Access Speed", true);

        makeReadRegister(0x4210, "NMI Flag and 5A22 Version", false,
            [this](Byte& value)
            {
                value = state.isNmiActive() ? 0x82 : 0x02;
            });
        makeReadRegister(0x4211, "IRQ Flag", false,
            [this](Byte& value)
            {
                value = state.isIrqActive() ? 0x80 : 0x00;
            });

        makeReadRegister(0x4212, "PPU Status", false,
            [this](Byte& value)
            {
                value.setBit(7, vBlank);
                value.setBit(6, hBlank);
                value.setBit(0, autoJoypadReadEnabled && vCounter >= 225 && vCounter < 228);
            });

        makeReadRegister(0x4214, "Quotient of Divide Result", false, quotient);
        makeReadRegister(0x4216, "Multiplication Product or Divide Remainder", false, product, false);

        makeReadRegister(0x4218, "Controller Port 1 Data1 Register", false, controllerPort1Data1);
        makeReadRegister(0x421a, "Controller Port 2 Data1 Register low byte", false);
        makeReadRegister(0x421b, "Controller Port 2 Data1 Register high byte", false);

        for (int i = 0; i < dmaChannels.size(); ++i)
        {
            std::string channel = Util::toString(i);
            makeReadWriteRegister(toDmaAddress(i, 0x0), "DMA Control Channel " + channel, false, dmaChannels[i].control);
            makeReadWriteRegister(toDmaAddress(i, 0x1), "DMA Destination Register Channel " + channel, false, dmaChannels[i].destinationRegister);
            makeReadWriteRegister(toDmaAddress(i, 0x2), "DMA Source Address Channel " + channel, false, dmaChannels[i].sourceAddress);
            makeReadWriteRegister(toDmaAddress(i, 0x5), "DMA Size/HDMA Indirect Address Channel " + channel, false, dmaChannels[i].dataSize);
            makeReadWriteRegister(toDmaAddress(i, 0x7), "HDMA Indirect Address bank byte Channel " + channel, false, dmaChannels[i].indirectAddressBankByte);
            makeReadWriteRegister(toDmaAddress(i, 0x8), "HDMA Table Address Channel " + channel, false, dmaChannels[i].tableAddress);
            makeReadWriteRegister(toDmaAddress(i, 0xa), "HDMA Line Counter Channel " + channel, false, dmaChannels[i].lineCounter);
        }

        std::vector<std::pair<Long, Long>> invalidRanges = {
            { 0x2000, 0x2100 },
            { 0x2144, 0x2180 },
            { 0x2200, 0x4016 },
            { 0x4018, 0x4200 },
            { 0x4220, 0x4300 },
            { 0x437b, 0x8000 }
        };

        for (const std::pair<Long, Long>& range : invalidRanges)
        {
            for (Long address = range.first; address < range.second; ++address)
            {
                makeReadRegister(address, "Invalid register", true,
                    [this](Byte& value)
                    {
                        //pauseRequested = true;
                        value = memory.bus;
                    });
            }
        }

        /*std::vector<Word> invalidAddresses = {
            0x4000,
            0x7000,
            0x59f8,
            0x37f8,
            0x77f8,
            0x47e0,
            0x69d0,
            0x78a0,
            0x3810,
            0x47f0,
            0x4678,
            0x33b8,
            0x3a10,
            0x5b20,
            0x4bf0,
            0x41f8,
            0x27f8
        };

        for (Word startAddress : invalidAddresses) {
            for (Word address = startAddress; address < startAddress + 8; ++address) {
                makeReadRegister(address, "Invalid register", true,
                    [this](Byte& value) {
                        //pauseRequested = true;
                        value = state.getMemory().bus;
                    });
            }
        }*/
    }

    static int toDmaAddress(int channel, int function)
    {
        return 0x4300 | channel << 4 | function;
    }

    Word getMode7WordValue(Byte value)
    {
        Word result = value << 8 | mode7Buffer;
        mode7Buffer = value;
        return result;
    }

    int16_t to13Bit2sComplement(Word value)
    {
        bool isNegative = value.getBit(12);
        for (int i = 13; i < Word::bitCount; ++i)
        {
            value.setBit(i, isNegative);
        }
        //if (result != value) {
            //output << "to13Bit2sComplement: " << value << " (" << std::bitset<16>(value) << ", " << int16_t(value) << ") -> " << result << " (" << std::bitset<16>(result) << ", " << int16_t(result) << ")" << std::endl;
        //}
        return value;
    }

    void readControllers()
    {
        if (autoJoypadReadEnabled)
        {
            controllerPort1Data1.setBit(4, processor.renderer.buttonR);
            controllerPort1Data1.setBit(5, processor.renderer.buttonL);
            controllerPort1Data1.setBit(6, processor.renderer.buttonX);
            controllerPort1Data1.setBit(7, processor.renderer.buttonA);
            controllerPort1Data1.setBit(8, processor.renderer.buttonRight);
            controllerPort1Data1.setBit(9, processor.renderer.buttonLeft);
            controllerPort1Data1.setBit(10, processor.renderer.buttonDown);
            controllerPort1Data1.setBit(11, processor.renderer.buttonUp);
            controllerPort1Data1.setBit(12, processor.renderer.buttonStart);
            controllerPort1Data1.setBit(13, processor.renderer.buttonSelect);
            controllerPort1Data1.setBit(14, processor.renderer.buttonY);
            controllerPort1Data1.setBit(15, processor.renderer.buttonB);
        }
    }

    void writeToVram(Byte value, bool highByte, bool increment)
    {
        if (videoPortControl.getBits(2, 2) != 0)
        {
            throw NotYetImplementedException("Video port control address mapping");
        }
        if (increment)
        {
            processor.vram.writeByte(value, highByte, getVramIncrement());
        }
        else
        {
            processor.vram.writeByte(value, highByte, 0);
        }
    }

    Byte readFromVram(bool highByte, bool increment)
    {
        if (videoPortControl.getBits(2, 2) != 0)
        {
            throw NotYetImplementedException("Video port control address mapping");
        }
        Byte result;
        if (highByte)
        {
            result = vramBuffer.getHighByte();
        }
        else
        {
            result = vramBuffer.getLowByte();
        }
        if (increment)
        {
            vramBuffer = processor.vram.readNextWord(getVramIncrement());
        }
        return result;
    }

    int getVramIncrement()
    {
        if (videoPortControl.getBits(0, 2) == 2)
        {
            throw NotYetImplementedException("Video port control: unsure of increment 2");
        }
        int increment = 1;
        if (videoPortControl.getBit(1))
        {
            increment = 128;
        }
        else if (videoPortControl.getBit(0))
        {
            increment = 32;
        }
        return increment;
    }

    void reset()
    {
        vBlank = false;
        hBlank = false;

        mode7Buffer = 0;
        mode7Multiplicand = 0;

        processor.vram.currentAddress = 0;
    }

    Output output;

    CPU::State& state;
    CPU::State::MemoryType& memory;

    Processor processor;

    bool pauseRequested = false;

    int vCounter = 0;
    int hCounter = 0;
    int frame = 0;
    bool interlaceField = false;

    bool vBlank = false;
    bool hBlank = false;

    Word oamStartAddress;

    Word vramBuffer;

    Long wramAddress;

    Word controllerPort1Data1;

    Byte videoPortControl;
    bool incrementVramOnHighByte = false;
    Byte mode7Buffer;
    int16_t mode7Multiplicand = 0;
    Long multiplicationResult;
    Byte multiplicandA;
    Word dividend;
    Word quotient;
    Word product;
    Word& remainder = product;
    bool nmiEnabled = false;

    IrqMode irqMode = IrqMode::None;
    bool autoJoypadReadEnabled = false;
    Word hTimer;
    Word vTimer;
    Byte programmableIOPort = 0xff;
    bool externalLatch = false;
    ReadTwiceRegister horizontalScanlineLocation;
    ReadTwiceRegister verticalScanlineLocation;
    Byte ppuStatusFlagAndVersion;

    Byte dmaEnabled;
    Byte hdmaEnabled;

    std::array<DmaChannel, 8> dmaChannels;
};

}
