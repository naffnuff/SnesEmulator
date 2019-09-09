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

    void makeWriteRegister(Word address, const std::string& info, bool debug, Long& variable)
    {
        makeWriteRegister(address, info + " low byte", debug, [&variable](Byte value) { variable.setLowByte(value); });
        makeWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte value) { variable.setHighByte(value); });
        makeWriteRegister(address + 2, info + " bank byte", debug, [&variable](Byte value) { variable.setBankByte(value); });
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
            if (callback) {
                callback(value);
            }
            if (debug && value) {
                printMemoryRegister(false, value, address, info);
            }
        };
    };

    void makeReadRegister(Word address, const std::string& info, bool debug, const Word& variable)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); });
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); });
    }

    void makeReadRegister(Word address, const std::string& info, bool debug, const Long& variable)
    {
        makeReadRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); });
        makeReadRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); });
        makeReadRegister(address + 2, info + " bank byte", debug, [&variable](Byte& value) { value = variable.getBankByte(); });
    }

    void makeReadRegister(Word address, const std::string& info, bool debug, Video::ReadTwiceRegister& variable)
    {
        makeReadRegister(address, info, debug, [&variable](Byte& value) { value = variable.read(); });
    }

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, std::function<void(Byte& value)> readCallback = nullptr, std::function<void(Byte value)> writeCallback = nullptr)
    {
        MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
        memory->setReadWrite();
        memory->setValue(0);
        memory->onRead =
            [this, address, readCallback, info, debug](Byte& value) {
            if (readCallback) {
                readCallback(value);
            }
            if (debug && value) {
                printMemoryRegister(false, value, address, info);
            }
        };
        memory->onWrite =
            [this, address, writeCallback, info, debug](Byte oldValue, Byte newValue) {
            if (debug && newValue && oldValue != newValue) {
                printMemoryRegister(true, newValue, address, info);
            }
            if (writeCallback) {
                writeCallback(newValue);
            }
        };
    };

    void makeReadWriteRegister(Word address, const std::string& info, bool debug, Word& variable)
    {
        makeReadWriteRegister(address, info + " low byte", debug, [&variable](Byte& value) { value = variable.getLowByte(); }, [&variable](Byte value) { variable.setLowByte(value); });
        makeReadWriteRegister(address + 1, info + " high byte", debug, [&variable](Byte& value) { value = variable.getHighByte(); }, [&variable](Byte value) { variable.setHighByte(value); });
    }

    void initialize()
    {
        // Registers
        makeWriteRegister(0x2100, "Screen Display", false, video.screenDisplay);
        makeWriteRegister(0x2101, "Object Size and Chr Address", false,
            [this](Byte value) {
                video.nameBaseSelect = value.getBits(0, 3) << 13;
                video.nameSelect = (value.getBits(3, 2) + 1) << 12;
                video.objectSizeIndex = value.getBits(5, 3);
            }
        );

        makeWriteRegister(0x2102, "OAM Address low byte", false,
            [this](Byte value) {
                oamStartAddress.setLowByte(value);
                video.oam.address = oamStartAddress;
            });
        makeWriteRegister(0x2103, "OAM Address high bit and Obj Priority", false,
            [this](Byte value) {
                oamStartAddress.setHighByte(value.getBit(0));
                video.oam.address = oamStartAddress;
                video.objectPriority = value.getBit(7);
            });
        makeWriteRegister(0x2104, "OAM Data write", false,
            [this](Byte value) {
                video.oam.writeByte(value);
            }
        );

        makeWriteRegister(0x2105, "BG Mode and Character Size", false,
            [this](Byte value) {
                video.backgroundMode = value.getBits(0, 3);
                video.mode1Extension = value.getBit(3);
                video.characterSize = value.getBits(4, 4);
                if (video.backgroundMode == 1) {
                    video.backgrounds[BackgroundLayer1].bitsPerPixel = 4;
                    video.backgrounds[BackgroundLayer2].bitsPerPixel = 4;
                    video.backgrounds[BackgroundLayer3].bitsPerPixel = 2;
                }
                else if (video.backgroundMode == 7) {
                    video.backgrounds[BackgroundLayer1].bitsPerPixel = 8;
                }
            });

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
            makeWriteRegister(0x2107 + i, bgName + " Tilemap Address and Size", false,
                [this, i](Byte value) {
                    video.backgrounds[i].horizontalMirroring = value.getBit(0);
                    video.backgrounds[i].verticalMirroring = value.getBit(1);
                    video.backgrounds[i].tilemapAddress = value.getBits(2, 6) << 10;
                });
            if (i > 0) {
                makeWriteRegister(0x210d + i * 2, bgName + " Horizontal Scroll", false, video.backgrounds[i].horizontalScroll);
                makeWriteRegister(0x210e + i * 2, bgName + " Vertical Scroll", false, video.backgrounds[i].verticalScroll);
            }
        }

        makeWriteRegister(0x210d, "BG1 and Mode 7 Horizontal Scroll", false,
            [this](Byte value) {
                video.backgrounds[BackgroundLayer1].horizontalScroll.write(value);
                video.mode7HorizontalScroll = to13Bit2sComplement(getMode7WordValue(value));
            });
        makeWriteRegister(0x210e, "BG1 and Mode 7 Vertical Scroll", false,
            [this](Byte value) {
                video.backgrounds[BackgroundLayer1].verticalScroll.write(value);
                video.mode7VerticalScroll = to13Bit2sComplement(getMode7WordValue(value));
            });

        makeWriteRegister(0x2115, "Video Port Control", false,
            [this](Byte value) {
                videoPortControl = value;
                incrementVramOnHighByte = value.getBit(7);
            });

        /*makeWriteRegister(0x2116, "VRAM Address low byte", false, 
            [this](Byte value) {
                video.vram.address.setLowByte(value);
            });

        makeWriteRegister(0x2117, "VRAM Address high byte", false,
            [this](Byte value) {
                video.vram.address.setHighByte(value & 0x7f);
            });*/
        makeWriteRegister(0x2116, "VRAM Address", false, video.vram.address);

        makeWriteRegister(0x2118, "VRAM Data Write low byte", false,
            [this](Byte value) {
                writeToVram(value, false, !incrementVramOnHighByte);
            }
        );

        makeWriteRegister(0x2119, "VRAM Data Write high byte", false,
            [this](Byte value) {
                writeToVram(value, true, incrementVramOnHighByte);
            }
        );

        makeWriteRegister(0x211a, "Mode 7 Settings", true,
            [this](Byte value) {
                video.mode7HorizontalMirroring = value.getBit(0);
                video.mode7VerticalMirroring = value.getBit(1);
                video.mode7EmptySpaceFill = value.getBit(6);
                video.mode7PlayingFieldSize = value.getBit(7);
            });

        makeWriteRegister(0x211b, "Mode 7 Matrix A (also multiplicand for MPYx)", false,
            [this](Byte value) {
                mode7Multiplicand = getMode7WordValue(value);
                video.mode7MatrixA = mode7Multiplicand;
            }
        );
        makeWriteRegister(0x211c, "Mode 7 Matrix B (also multiplier for MPYx)", false,
            [this](Byte value) {
                multiplicationResult = mode7Multiplicand * int8_t(value);
                video.mode7MatrixB = getMode7WordValue(value);
            }
        );
        makeWriteRegister(0x211d, "Mode 7 Matrix C", false,
            [this](Byte value) {
                video.mode7MatrixC = getMode7WordValue(value);
            });
        makeWriteRegister(0x211e, "Mode 7 Matrix D", false,
            [this](Byte value) {
                video.mode7MatrixD = getMode7WordValue(value);
            });
        makeWriteRegister(0x211f, "Mode 7 Center X", false,
            [this](Byte value) {
                video.mode7CenterX = to13Bit2sComplement(getMode7WordValue(value));
            });
        makeWriteRegister(0x2120, "Mode 7 Center Y", false,
            [this](Byte value) {
                video.mode7CenterY = to13Bit2sComplement(getMode7WordValue(value));
            });

        makeWriteRegister(0x2121, "CGRAM Address", false,
            [this](Byte value) {
                video.cgram.address.setLowByte(value);
                video.cgram.address.setHighByte(0x00);
            }
        );
        makeWriteRegister(0x2122, "CGRAM Data Write", false,
            [this](Byte value) {
                Word cgramAddress = video.cgram.address;

                video.cgram.writeByte(value);

                /*if (cgramHighTable) {
                    int row = cgramAddress / 0x10;
                    int column = cgramAddress % 0x10;
                    video.cgramRenderer.setPixel(row, column, video.cgram.readWord(cgramAddress));
                }*/
            }
        );

        makeWriteRegister(0x2123, "Window Mask Settings", true, video.windowMaskSettings);
        makeWriteRegister(0x2126, "Window 1 Left Position", false, video.window1Left);
        makeWriteRegister(0x2127, "Window 1 Right Position", false, video.window1Right);
        makeWriteRegister(0x2128, "Window 2 Left Position", false, video.window2Left);
        makeWriteRegister(0x2129, "Window 2 Right Position", false, video.window2Right);
        makeWriteRegister(0x212a, "Window Mask Logic", true, video.windowMaskLogic);
        makeWriteRegister(0x212c, "Main Screen Designation", false, video.mainScreenDesignation);
        makeWriteRegister(0x212d, "Subscreen Designation", false, video.subscreenDesignation);
        makeWriteRegister(0x212e, "Window Mask Designation for the Main Screen", true, video.mainScreenWindowMaskDesignation);
        makeWriteRegister(0x212f, "Window Mask Designation for the Subscreen", true, video.subscreenWindowMaskDesignation);
        makeWriteRegister(0x2130, "Color Addition Select", false,
            [this](Byte value) {
                video.directColorMode = value.getBit(0);
                video.addSubscreen = value.getBit(1);
                video.clipColorMathMode = Video::ColorWindowMode(int(value.getBits(4, 2)));
                video.clipColorToBlackMode = Video::ColorWindowMode(int(value.getBits(6, 2)));
            });
        makeWriteRegister(0x2131, "Color Math Designation", false, video.colorMathDesignation);
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

        makeWriteRegister(0x2133, "Screen Mode/Video Select", true,
            [this](Byte value) {
                if (value.getBit(0)) {
                    throw Video::NotYetImplementedException("Register 2133: Screen interlace");
                }
                if (value.getBit(1)) {
                    throw Video::NotYetImplementedException("Register 2133: Object interlace");
                }
                if (value.getBit(2)) {
                    throw Video::NotYetImplementedException("Register 2133: Overscan mode");
                }
                if (value.getBit(3)) {
                    throw Video::NotYetImplementedException("Register 2133: Pseudo-hires mode");
                }
                if (value.getBit(6)) {
                    throw Video::NotYetImplementedException("Register 2133: Mode 7 extra bg");
                }
                if (value.getBit(7)) {
                    throw Video::NotYetImplementedException("Register 2133: External sync");
                }
            });

        // makeRegister(, true, "", true);
        // , [this](Byte value) {}

        makeReadRegister(0x2134, "Multiplication Result", false, multiplicationResult);

        makeReadRegister(0x2137, "Software Latch for H/V Counter", true,
            [this](Byte) {
                if (programmableIOPort.getBit(7)) {
                    horizontalScanlineLocation.value = hCounter;
                    verticalScanlineLocation.value = vCounter;
                    externalLatch = true;
                }
            });

        makeReadRegister(0x2138, "Data for OAM read", true);

        makeReadRegister(0x2139, "VRAM Data read low byte", false,
            [this](Byte& value) {
                value = readFromVram(false, !incrementVramOnHighByte);
            });
        makeReadRegister(0x213a, "VRAM Data read high byte", false,
            [this](Byte& value) {
                value = readFromVram(true, incrementVramOnHighByte);
            });

        makeReadRegister(0x213c, "Horizontal Scanline Location", false, horizontalScanlineLocation);
        makeReadRegister(0x213d, "Vertical Scanline Location", false, verticalScanlineLocation);
        makeReadRegister(0x213e, "PPU Status Flag and Version", false);
        makeReadRegister(0x213f, "PPU Status Flag and Version", false,
            [this](Byte& byte) {
                byte = 3;
                byte.setBit(7, interlaceField);
                byte.setBit(6, externalLatch);
                if (programmableIOPort.getBit(7)) {
                    externalLatch = false;
                }
                horizontalScanlineLocation.highByteSelect = false;
                verticalScanlineLocation.highByteSelect = false;
            });

        makeWriteRegister(0x2181, "WRAM Address", false, wramAddress);

        makeReadWriteRegister(0x4016, "NES-style Joypad Access Port 1", false,
            [this](Byte& value) {
                //printMemoryRegister(false, value, 0x4016, "NES-style Joypad Access Port 1");
            },
            [this](Byte value) {
                if (value > 0) {
                    throw Video::NotYetImplementedException("Register 4016: Latch on");
                }
            });
        makeReadWriteRegister(0x4017, "NES-style Joypad Access Port 2", false,
            [this](Byte& value) {
                //printMemoryRegister(false, value, 0x4017, "NES-style Joypad Access Port 2");
            },
            [this](Byte value) {
                if (value > 0) {
                    throw Video::NotYetImplementedException("Register 4017: Latch on");
                }
            });

        makeWriteRegister(0x4200, "Interrupt Enable Flags", false,
            [this](Byte value) {
                autoJoypadReadEnabled = value.getBit(0);
                irqMode = IrqMode(int(value.getBits(4, 2)));
                nmiEnabled = value.getBit(7);
            });

        makeWriteRegister(0x4201, "Programmable I/O port (out-port)", true,
            [this](Byte value) {
                if (programmableIOPort.getBit(7) && !value.getBit(7)) { // 1 -> 0
                    horizontalScanlineLocation.value = hCounter;
                    verticalScanlineLocation.value = vCounter;
                    externalLatch = true;
                }
                if (value.getBit(6)) {
                    //throw Video::NotYetImplementedException("Register 4201: bit 6");
                }
                programmableIOPort = value;
            });
        makeWriteRegister(0x4202, "Multiplicand A", false, multiplicandA);
        makeWriteRegister(0x4203, "Multiplicand B", false,
            [this](Byte multiplicandB) {
                product = multiplicandA * multiplicandB;
            });

        makeWriteRegister(0x4204, "Dividend C", false, dividend);
        makeWriteRegister(0x4206, "Divisor B", false,
            [this](Byte divisor) {
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

        makeWriteRegister(0x4207, "H Timer", false, hTimer);
        makeWriteRegister(0x4209, "V Timer", false, vTimer);
        makeWriteRegister(0x420b, "DMA Enable", false);
        makeWriteRegister(0x420c, "HDMA Enable", false,
            [this](Byte value) {
                /*std::stringstream ss;
                ss << "HDMA Enable " << "vCounter=" << vCounter << ", hCounter=" << hCounter << std::endl;
                printMemoryRegister(true, value, 0x420c, ss.str());*/
            });
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
                value.setBit(0, autoJoypadReadEnabled && vCounter >= 225 && vCounter < 228);
            });

        makeReadRegister(0x4214, "Quotient of Divide Result", false, quotient);
        makeReadWriteRegister(0x4216, "Multiplication Product or Divide Remainder", false, product);

        makeReadRegister(0x4218, "Controller Port 1 Data1 Register", false, controllerPort1Data1);
        makeReadRegister(0x421a, "Controller Port 2 Data1 Register low byte", false);
        makeReadRegister(0x421b, "Controller Port 2 Data1 Register high byte", false);

        for (int i = 0; i < 8; ++i) {
            std::string channel = Util::toString(i);
            makeReadWriteRegister(toDmaAddress(i, 0x0), "DMA Control Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x1), "DMA Destination Register Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x2), "DMA Source Address low byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x3), "DMA Source Address high byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x4), "DMA Source Address bank byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x5), "DMA Size/HDMA Indirect Address low byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x6), "DMA Size/HDMA Indirect Address high byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x7), "HDMA Indirect Address bank byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x8), "HDMA Table Address low byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0x9), "HDMA Table Address high byte Channel " + channel, false);
            makeReadWriteRegister(toDmaAddress(i, 0xa), "HDMA Line Counter Channel " + channel, false);
        }

        for (int address = 0x2000; address < 0x2100; ++address) {
            MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
            memory->setReadOnlyValue(0x0f);
        }

        for (int address = 0x2144; address < 0x2180; ++address) {
            MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
            memory->setReadOnlyValue(0x0f);
        }

        for (int address = 0x2200; address < 0x4200; ++address) {
            if (address != 0x4016 && address != 0x4017) {
                MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
                memory->setReadOnlyValue(0x0f);
            }
        }

        for (int address = 0x4220; address < 0x4300; ++address) {
            MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
            memory->setReadOnlyValue(0x0f);
        }

        for (int address = 0x437b; address < 0x8000; ++address) {
            MemoryLocation* memory = state.getMemoryLocation(Long(address, 0));
            memory->setReadOnlyValue(0x0f);
        }
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
        for (int i = 13; i < Word::bitCount(); ++i) {
            value.setBit(i, isNegative);
        }
        //if (result != value) {
            //output << "to13Bit2sComplement: " << value << " (" << std::bitset<16>(value) << ", " << int16_t(value) << ") -> " << result << " (" << std::bitset<16>(result) << ", " << int16_t(result) << ")" << std::endl;
        //}
        return value;
    }

    void readControllers()
    {
        if (autoJoypadReadEnabled) {
            controllerPort1Data1.setBit(4, video.renderer.buttonR);
            controllerPort1Data1.setBit(5, video.renderer.buttonL);
            controllerPort1Data1.setBit(6, video.renderer.buttonX);
            controllerPort1Data1.setBit(7, video.renderer.buttonA);
            controllerPort1Data1.setBit(8, video.renderer.buttonRight);
            controllerPort1Data1.setBit(9, video.renderer.buttonLeft);
            controllerPort1Data1.setBit(10, video.renderer.buttonDown);
            controllerPort1Data1.setBit(11, video.renderer.buttonUp);
            controllerPort1Data1.setBit(12, video.renderer.buttonStart);
            controllerPort1Data1.setBit(13, video.renderer.buttonSelect);
            controllerPort1Data1.setBit(14, video.renderer.buttonY);
            controllerPort1Data1.setBit(15, video.renderer.buttonB);
        }
    }

    void writeToVram(Byte value, bool highByte, bool increment)
    {
        if (videoPortControl.getBits(2, 2) != 0) {
            throw Video::NotYetImplementedException("Video port control address mapping");
        }
        if (increment) {
            video.vram.writeByte(value, highByte, getVramIncrement());
        }
        else {
            video.vram.writeByte(value, highByte, 0);
        }
    }

    Byte readFromVram(bool highByte, bool increment)
    {
        if (videoPortControl.getBits(2, 2) != 0) {
            throw Video::NotYetImplementedException("Video port control address mapping");
        }
        Byte result;
        if (highByte) {
            result = vramBuffer.getHighByte();
        }
        else {
            result = vramBuffer.getLowByte();
        }
        if (increment) {
            vramBuffer = video.vram.readNextWord(getVramIncrement());
        }
        return result;
    }

    int getVramIncrement()
    {
        if (videoPortControl.getBits(0, 2) == 2) {
            throw Video::NotYetImplementedException("Video port control: unsure of increment 2");
        }
        int increment = 1;
        if (videoPortControl.getBit(1)) {
            increment = 128;
        }
        else if (videoPortControl.getBit(0)) {
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

        video.vram.address = 0;
    }

    std::ostream& output;
    std::ostream& error;
    CPU::State& state;
    Video& video;

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
    enum IrqMode
    {
        NoIrq = 0,
        HCounterIrq = 1,
        VCounterIrq = 2,
        HAndVCounterIrq = 3
    };
    IrqMode irqMode;
    bool autoJoypadReadEnabled = false;
    Word hTimer;
    Word vTimer;
    Byte programmableIOPort = 0xff;
    bool externalLatch = false;
    Video::ReadTwiceRegister horizontalScanlineLocation;
    Video::ReadTwiceRegister verticalScanlineLocation;
    Byte ppuStatusFlagAndVersion;
    const Word mysteriousRegister;
};
