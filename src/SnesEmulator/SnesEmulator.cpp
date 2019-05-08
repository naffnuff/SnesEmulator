#include "SnesEmulator.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Common/Exception.h"

#include "DmaInstruction.h"

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error);

void Emulator::initialize()
{
    rom.loadFromFile("../../Legend of Zelda, The - A Link to the Past (U) [!].smc", cpuState);
    //rom.loadFromFile("../../Super Mario World (USA).sfc", cpuState);
    //rom.loadFromFile("../../Super Metroid (Japan, USA) (En,Ja).sfc", cpuState);
    //rom.loadFromFile("../../Super Metroid (JU) [!].smc", cpuState);
    //rom.loadFromFile("../../Megaman X (USA).sfc", cpuState);
    //rom.loadFromFile("../../SnesInitializationROM.smc", cpuState);
    //rom.loadFromFile("../../rom.smc", cpuState);
    //rom.loadFromFile("H:\\naffnuff\\wla\\rom.smc", cpuState);
    //rom.loadFromFile("C:\\cygwin64\\home\\rasmus.knutsson\\wla-dx\\wla\\myrom.smc", cpuState);

    renderer.initialize(rom.gameTitle);

    if (rom.isLowRom()) {
        // RAM
        for (Long address = 0x7E0000; address < 0x800000; address++) {
            cpuState.getMemoryLocation(address)->setReadWrite();
        }
        // RAM mirrors
        for (Byte bank = 0; bank < 0x40; ++bank) {
            for (Word address = 0; address < 0x2000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setMirror(cpuState.getMemoryLocation(Long(address, 0x7E)), MemoryLocation::ReadWrite);
            }
        }

        // Save RAM
        for (Byte bank = 0x70; bank < 0x71/*0x78*/; ++bank) {
            for (Word address = 0; address < 0x8000; ++address) {
                cpuState.getMemoryLocation(Long(address, bank))->setReadWrite();
                cpuState.getMemoryLocation(Long(address, bank))->setValue(0x00);
            }
        }

        auto setRegister = [this](Word address, bool cpuOutRegister, const std::string& info, std::function<void(MemoryLocation::Operation operation, Byte value)> callback = nullptr)
        {
            MemoryLocation* memory = cpuState.getMemoryLocation(Long(address, 0));
            if (cpuOutRegister) {
                memory->setWriteOnly();
                memory->setValue(0);
                registers[address].setMirror(memory, MemoryLocation::ReadOnly);
            } else {
                registers[address].setWriteOnly();
                memory->setMirror(&registers[address], MemoryLocation::ReadOnly);
            }
            memory->trap =
                [this, address, callback, info](MemoryLocation::Operation operation, Byte value) {
                //debugger.printMemoryRegister(operation, value, address, info);
                if (callback) {
                    callback(operation, value);
                }
            };
        };

        // Registers
        setRegister(0x2100, true, "Screen Display");
        setRegister(0x2102, true, "OAM Address low byte");
        setRegister(0x2103, true, "OAM Address high bit and Obj Priority");
        setRegister(0x2104, true, "Data for OAM write", [this](MemoryLocation::Operation operation, Byte value) {
            if (operation != MemoryLocation::Write) {
                throw std::logic_error("2104 can only be written by CPU");
            }
            Word oamAddress = registers[0x2102].getWordValue();
            //debugger.printMemoryRegister(operation, value, oamAddress, "Data for OAM write");
            });
        setRegister(0x2115, true, "Video Port Control");
        setRegister(0x2116, true, "VRAM Address low byte");
        setRegister(0x2117, true, "VRAM Address high byte");
        setRegister(0x2118, true, "VRAM Data Write low byte", [this](MemoryLocation::Operation operation, Byte value) {
            if (operation != MemoryLocation::Write) {
                throw std::logic_error("2118 can only be written by CPU");
            }
            Word vramAddress = registers[0x2116].getWordValue();
            videoMemory.setLowByte(vramAddress, value);
        });
        setRegister(0x2119, true, "VRAM Data Write high byte", [this](MemoryLocation::Operation operation, Byte value) {
            if (operation != MemoryLocation::Write) {
                throw std::logic_error("2119 can only be written by CPU");
            }
            Word vramAddress = registers[0x2116].getWordValue();
            videoMemory.setHighByte(vramAddress, value);

            const int bitsPerPixel = 4;
            static const int tilePixelCount = 8 * 8;
            int tileBitCount = tilePixelCount * bitsPerPixel;
            int tileWordCount = tileBitCount / 16;
            int tileIndex = vramAddress / tileWordCount;
            int tileWordOffset = vramAddress % tileWordCount;
            if (tileWordOffset == tileWordCount - 1) {
                std::array<std::array<uint8_t, 8>, 8> tile = videoMemory.readTile(tileIndex, bitsPerPixel);
                int tilesPerRow = vramRendererWidth / 8;
                int tileRow = tileIndex / tilesPerRow;
                int tileColumn = tileIndex % tilesPerRow;
                vramRenderer.setGrayscaleTile(tileRow * 8, tileColumn * 8, tile);
            }

            Byte videoPortControl = registers[0x2115].getValue();
            if (videoPortControl.getBit(7)) {
                cpuState.getMemoryLocation(0x2116)->setWordValue(vramAddress + 1);
            } else {
                error << "DMA: Video port control: " << videoPortControl << std::endl;
                throw std::logic_error("DMA: Video port control not implemented");
            }
        });
        setRegister(0x2121, true, "CGRAM Address");
        setRegister(0x2122, true, "CGRAM Data Write low byte", [this](MemoryLocation::Operation operation, Byte value) {
            if (operation != MemoryLocation::Write) {
                throw std::logic_error("2122 can only be written by CPU");
            }
            Byte cgramAddress = registers[0x2121].getValue();
            //debugger.printMemoryRegister(operation, value, Word(cgramAddress), "CGRAM Data Write");
            });
        setRegister(0x212e, true, "Window Mask Designation for the Main Screen");
        setRegister(0x212f, true, "Window Mask Designation for the Subscreen");

        setRegister(0x4016, true, "NES-style Joypad Access Port 1");

        setRegister(0x4200, true, "Interrupt Enable Flags");
        setRegister(0x420b, true, "DMA Enable");
        setRegister(0x420c, true, "HDMA Enable");
        setRegister(0x4210, false, "NMI Flag and 5A22 Version");

        setRegister(0x4218, false, "Controller Port 1 Data1 Register low byte");
        setRegister(0x4219, false, "Controller Port 1 Data1 Register high byte");

        // DMA channel 0
        setRegister(0x4300, true, "DMA Control Channel 0");
        setRegister(0x4301, true, "DMA Destination Register Channel 0");
        setRegister(0x4302, true, "DMA Source Address low byte Channel 0");
        setRegister(0x4303, true, "DMA Source Address high byte Channel 0");
        setRegister(0x4304, true, "DMA Source Address bank byte Channel 0");
        setRegister(0x4305, true, "DMA Size/HDMA Indirect Address low byte Channel 0");
        setRegister(0x4306, true, "DMA Size/HDMA Indirect Address high byte Channel 0");

        // DMA channel 1
        setRegister(0x4310, true, "DMA Control Channel 1");
        setRegister(0x4311, true, "DMA Destination Register Channel 1");
        setRegister(0x4312, true, "DMA Source Address low byte Channel 1");
        setRegister(0x4313, true, "DMA Source Address high byte Channel 1");
        setRegister(0x4314, true, "DMA Source Address bank byte Channel 1");
        setRegister(0x4315, true, "DMA Size/HDMA Indirect Address low byte Channel 1");
        setRegister(0x4316, true, "DMA Size/HDMA Indirect Address high byte Channel 1");

        // DMA channel 2
        setRegister(0x4320, true, "DMA Control Channel 2");
        setRegister(0x4321, true, "DMA Destination Register Channel 2");
        setRegister(0x4322, true, "DMA Source Address low byte Channel 2");
        setRegister(0x4323, true, "DMA Source Address high byte Channel 2");
        setRegister(0x4324, true, "DMA Source Address bank byte Channel 2");
        setRegister(0x4325, true, "DMA Size/HDMA Indirect Address low byte Channel 2");
        setRegister(0x4326, true, "DMA Size/HDMA Indirect Address high byte Channel 2");

        // DMA channel 3
        setRegister(0x4330, true, "DMA Control Channel 3");
        setRegister(0x4331, true, "DMA Destination Register Channel 3");
        setRegister(0x4332, true, "DMA Source Address low byte Channel 3");
        setRegister(0x4333, true, "DMA Source Address high byte Channel 3");
        setRegister(0x4334, true, "DMA Source Address bank byte Channel 3");
        setRegister(0x4335, true, "DMA Size/HDMA Indirect Address low byte Channel 3");
        setRegister(0x4336, true, "DMA Size/HDMA Indirect Address high byte Channel 3");

        // DMA channel 4
        setRegister(0x4340, true, "DMA Control Channel 4");
        setRegister(0x4341, true, "DMA Destination Register Channel 4");
        setRegister(0x4342, true, "DMA Source Address low byte Channel 4");
        setRegister(0x4343, true, "DMA Source Address high byte Channel 4");
        setRegister(0x4344, true, "DMA Source Address bank byte Channel 4");
        setRegister(0x4345, true, "DMA Size/HDMA Indirect Address low byte Channel 4");
        setRegister(0x4346, true, "DMA Size/HDMA Indirect Address high byte Channel 4");

        // I/O between the CPU and SPC700
        for (Word i = 0; i < 4; ++i) {
            MemoryLocation* cpuMemoryLocation = cpuState.getMemoryLocation(Long(0x2140 + i));
            MemoryLocation* spcMemoryLocation = spcState.getMemoryLocation(Word(0xf4 + i));
            cpuMemoryLocation->setMapping(spcMemoryLocation);
            spcMemoryLocation->setMapping(cpuMemoryLocation);
        }
    } else {
        throw std::runtime_error("Only the low-rom mempory map is supported for now");
    }

    for (Debugger::Context* context : { &cpuContext, &spcContext }) {
        std::ifstream contextFile(context->fileName);
        if (contextFile) {
            std::string breakpointString;
            while (std::getline(contextFile, breakpointString, ' ')) {
                Long breakpoint = std::stoi(breakpointString, 0, 16);
                output << "Read breakpoint: " << breakpoint << " from " << context->fileName << std::endl;
                context->breakpoints.insert(breakpoint);
            }
        }
    }

    cpuContext.nextInstruction = cpuInstructionDecoder.readNextInstruction(cpuState);
    spcContext.nextInstruction = spcInstructionDecoder.readNextInstruction(spcState);
}

void Emulator::run()
{
    std::thread vramRendererThread([this]()
        {
            vramRenderer.initialize("VRAM viewer");
            while (running) {
                vramRenderer.update();
            }
        });

    DmaInstruction dmaInstruction(registers, cpuState.accessMemory(), output, error);

    uint64_t nextCpu = cycleCount;
    uint64_t nextSpc = cycleCount;
    uint64_t cycleCountTarget = cycleCount;

    int hCounter = int(cycleCount);
    int vCounter = 0;
    bool vBlank = false;

    std::vector<Renderer::Pixel> scanline(256);

    bool irq = false;
    bool nmi = false;

    double runStartTime;
    bool stepMode = cpuContext.stepMode || spcContext.stepMode;
    if (!stepMode) {
        output << "Snip" << std::endl;
        debugger.startTime = clock();
        runStartTime = renderer.getTime();
    }

    try {
        uint64_t iteration = 0;
        while (running) {

            if (cycleCount == nextCpu) {

                if (nmi) {
                    nmi = false;
                    if (registers[0x4200].getValue().getBit(7)) {
                        cpuState.startNmi();
                        //cpuContext.stepMode = true;
                    }
                    nextCpu += 9 * 8; // TODO: check the correct cycles for interrupt
                }

                Instruction* instruction = cpuInstructionDecoder.readNextInstruction(cpuState);

                if (dmaInstruction.enabled()) { // DMA enabled
                    //cpuContext.stepMode = true;
                    dmaInstruction.blockedInstruction = instruction;
                    instruction = static_cast<Instruction*>(&dmaInstruction);
                }

                cpuContext.nextInstruction = instruction;

                if (cpuContext.stepMode) {
                    output << "Cycle count: " << cycleCount << ", Next cpu: " << nextCpu << ", Next spc: " << nextSpc << std::endl;
                    output << "V counter: " << vCounter << ", H counter: " << hCounter << ", V blank: " << vBlank << std::endl;
                    debugger.printBreakpoints(cpuContext, spcContext);
                    debugger.printMemory(cpuState, cpuContext, spcState, spcContext, videoMemory);
                }

                if (int cycles = executeNext(instruction, cpuState, debugger, cpuContext, spcState, spcContext, error)) {
                    nextCpu += cycles * 8;
                    cpuContext.nextInstruction = cpuInstructionDecoder.readNextInstruction(cpuState);
                } else {
                    continue;
                }
            }

            if (cycleCount == nextSpc) {
                Instruction* instruction = spcInstructionDecoder.readNextInstruction(spcState);
                spcContext.nextInstruction = instruction;

                if (spcContext.stepMode) {
                    output << "cycleCount=" << cycleCount << ", nextCpu=" << nextCpu << ", nextSpc=" << nextSpc << std::endl;
                    debugger.printBreakpoints(cpuContext, spcContext);
                    debugger.printMemory(cpuState, cpuContext, spcState, spcContext, videoMemory);
                }

                if (int cycles = executeNext(instruction, spcState, debugger, spcContext, cpuState, cpuContext, error)) {
                    nextSpc += cycles * 16;
                    spcContext.nextInstruction = spcInstructionDecoder.readNextInstruction(spcState);
                } else {
                    continue;
                }
            }

            bool increment = false;
            if (cpuContext.stepMode || spcContext.stepMode) { // step mode
                increment = true;
                stepMode = true;
            } else if (stepMode) { // run mode initiated
                stepMode = false;
                runStartTime = renderer.getTime();
            } else { // run mode continued
                if (iteration % 1000 == 0)
                {
                    double elapsedTime = renderer.getTime() - runStartTime;
                    static const double clockSpeedTarget = 1.89e9 / 88.0;
                    cycleCountTarget = uint64_t(elapsedTime * clockSpeedTarget);
                }

                if (cycleCountTarget > cycleCount)
                {
                    increment = true;
                }

                increment = true;

                static int incrementCount = 0;
                static int totalCount = 0;

                if (increment) {
                    ++incrementCount;
                }
                ++totalCount;

                /*static int nextPrintout = 5;
                double actualSpeed = double(cycleCount) / elapsedTime;
                if (nextPrintout == int(elapsedTime)) {
                    nextPrintout += 5;
                    output << "Renderer time: " << elapsedTime << std::endl;
                    output << "Elapsed cycles: " << elapsedCycles << std::endl;
                    output << "Actual cycles: " << cycleCount << std::endl;
                    output << "Clock speed: " << clockSpeed << std::endl;
                    output << "Actual speed: " << actualSpeed << std::endl;
                    output << "ratio: " << actualSpeed / clockSpeed << std::endl;
                    output << std::endl;
                    output << "increments: " << incrementCount << std::endl;
                    output << "total: " << totalCount << std::endl;
                    output << "ratio: " << double(incrementCount) / double(totalCount) << std::endl;
                    output << std::endl;
                    output << "V counter: " << vCounter << std::endl;
                    output << "H counter: " << hCounter << std::endl;
                    output << std::endl;
                }*/
            }

            static uint8_t color = 0;
            static bool ascending = true;
            if (increment) {
                ++cycleCount;
                ++hCounter;
                if (hCounter == 1360) {
                    hCounter = 0;
                    if (vCounter < 224) {
                        for (int i = 0; i < scanline.size(); ++i) {
                            //scanline[i] = { color, uint8_t(vCounter), uint8_t(i) };
                            renderer.setGrayscalePixel(vCounter, i, vCounter);
                        }
                        //renderer.setScanline(vCounter, scanline);
                    }
                    ++vCounter;
                    if (vCounter == 225) {
                        vBlank = true;
                        nmi = true;
                        registers[0x4210].setValue(0x82);
                        if (ascending) {
                            ++color;
                            if (color == 255) {
                                ascending = false;
                            }
                        } else {
                            --color;
                            if (color == 0) {
                                ascending = true;
                            }
                        }
                    } else if (vCounter == 262) {
                        vCounter = 0;
                        vBlank = false;
                        registers[0x4210].setValue(0x02);
                        renderer.update();
                        if (renderer.pause) {
                            renderer.pause = false;
                            cpuContext.stepMode = true;
                        }
                    }
                }
            }
            ++iteration;
        }
    } catch (const std::exception& e) {
        running = false;
        output << "Joining vramRendererThread" << std::endl;
        vramRendererThread.join();
        output << "Joined vramRendererThread" << std::endl;
        throw e;
    }
    output << "Joining vramRendererThread 2" << std::endl;
    vramRendererThread.join();
    output << "Joined vramRendererThread 2" << std::endl;
}

template<typename State, typename OtherState>
int executeNext(Instruction* instruction, State& state, Debugger& debugger, Debugger::Context& context, OtherState& otherState, Debugger::Context& otherContext, std::ostream& error)
{
    Long lastKnownProgramAddress = state.getProgramAddress();
    try {
        if (context.stepMode) {
            debugger.printState(state, context);

            if (debugger.awaitCommand(context, state, otherContext, otherState)) {
                int cycles = instruction->execute();
                if (context.stepMode) {
                    debugger.printRegisters(state, context);
                }
                return cycles;
            }
        }
        else {
            for (Long i = state.getProgramAddress(); i < state.getProgramAddress() + instruction->size(); ++i) {
                if (context.breakpoints.find(i) != context.breakpoints.end()) {
                    context.stepMode = true;
                    break;
                }
            }

            if (context.stepMode) {
                debugger.printClockSpeed();
            }
            else {
                return instruction->execute();
            }
        }
    } catch (OpcodeNotYetImplementedException& e) {
        error << e.what() << std::endl;
        context.stepMode = true;
    } catch (AddressModeNotYetImplementedException& e) {
        error << e.what() << std::endl;
        state.setProgramAddress(lastKnownProgramAddress);
        context.stepMode = true;
    } catch (OperatorNotYetImplementedException& e) {
        error << e.what() << std::endl;
        state.setProgramAddress(lastKnownProgramAddress);
        context.stepMode = true;
    } catch (MemoryLocation::AccessException& e) {
        error << e.what() << std::endl;
        state.setProgramAddress(lastKnownProgramAddress);
        context.stepMode = true;
    }
    return 0;
}
