/*
All documentation in the comments of this file is from:

=============================================================================
 Anomie's Register Doc
 $Revision: 1157 $
 $Date: 2007-07-12 16:39:41 -0400 (Thu, 12 Jul 2007) $
 <anomie@users.sourceforge.net>
=============================================================================
*/

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

    Registers(Output& output, CPU::State& state, const std::string& gameTitle)
        : RegisterManager(output, "video", state.getMemory())
        , output(output, "video")
        , state(state)
        , memory(state.getMemory())
        , processor(output, gameTitle)
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
        /*
            REGISTERS
            =========

            Addr rw?fvha Name
                    bits

                    Explanation

            "Addr" is the address this register is mapped into the SNES memory space.
            "Name" is the official and unofficial name of the register
            "bits" is either 8 or 16 characters explicating the bitfields in this register.

            The flags are:
            rw?fvha
            ||||||+--> '+' if it can be read/written at any time, '-' otherwise
            |||||+---> '+' if it can be read/written during H-Blank
            ||||+----> '+' if it can be read/written during V-Blank
            |||+-----> '+' if it can be read/written during force-blank
            ||+------> Read/Write style: 'b'     => byte
            ||                           'h'/'l' => read/write high/low byte of a word
            ||                           'w'     => word read/write twice low then high
            |+-------> 'w' if the register is writable for an effect
            +--------> 'r' if the register is readable for a value or effect (i.e. not
                        open bus).

            To find the entry for a particular register, search for the register number
            (i.e. '2100') at the very beginning of the line. Note that the DMA registers
            are combined, so e.g. to find $4300, $4310, $4320, $4330, $4340, $4350, $4360,
            or $4370 you'd search for '43x0'.

            For most registers (and most undefined bits of readable registers), the
            returned value is Open Bus, that is the last value read over the main bus from
            the ROM (typically part of the opcode arguments or the indirect base address).

            Registers matching $21x4-6 or $21x8-A (where x is 0-2) return the last value
            read from any of the PPU1 registers $2134-6, $2138-A, or $213E. This is known
            as PPU1 Open Bus. Similarly, PPU2 Open Bus involves reading registers $213B-D
            or $213F (NOT $21xB-D though).

            Note that it may be possible to write registers anytime even if marked '-', but
            until we have proof '-' is a better guess.

            --------
        */

        // Registers

        /*
            2100  wb++++ INIDISP - Screen Display
                    x---bbbb

                    x    = Force blank on when set.
                    bbbb = Screen brightness, F=max, 0="off".

                    Note that force blank CAN be disabled mid-scanline. However, this can
                    result in glitched graphics on that scanline, as the internal rendering
                    buffers will not have been updated during force blank. Current theory
                    is that BGs will be glitched for a few tiles (depending on how far in
                    advance the PPU operates), and OBJ will be glitched for the entire
                    scanline.

                    Also, writing this register on the first line of V-Blank (225 or 240,
                    depending on overscan) when force blank is currently active causes the
                    OAM Address Reset to occur.
        */
        makeWriteRegister(0x2100, "Screen Display", false, processor.screenDisplay);

        /*
            2101  wb++?- OBSEL - Object Size and Chr Address
                    sssnnbbb

                    sss  = Object size:
                        000 =  8x8  and 16x16 sprites
                        001 =  8x8  and 32x32 sprites
                        010 =  8x8  and 64x64 sprites
                        011 = 16x16 and 32x32 sprites
                        100 = 16x16 and 64x64 sprites
                        101 = 32x32 and 64x64 sprites
                        110 = 16x32 and 32x64 sprites ('undocumented')
                        111 = 16x32 and 32x32 sprites ('undocumented')

                    nn   = Name Select
                    bbb  = Name Base Select (Addr>>14)
                        See the section "SPRITES" below for details.
        */
        makeWriteRegister(0x2101, "Object Size and Chr Address", false,
            [this](Byte value)
            {
                processor.nameBaseSelect = value.getBits(0, 3) << 13;
                processor.nameSelect = (value.getBits(3, 2) + 1) << 12;
                processor.objectSizeIndex = value.getBits(5, 3);
            }
        );

        /*
            2102  wl++?- OAMADDL - OAM Address low byte
            2103  wh++?- OAMADDH - OAM Address high bit and Obj Priority
                    p------b aaaaaaaa

                    p    = Obj Priority activation bit
                        When this bit is set, an Obj other than Sprite 0 may be given
                        priority. See the section "SPRITES" below for details.

                    b aaaaaaaa = OAM address
                        This can be thought of in two ways, depending on your conception of
                        OAM. If you consider OAM as a 544-byte table, baaaaaaaa is the word
                        address into that table. If you consider OAM to be a 512-byte table
                        and a 32-byte table, b is the table selector and aaaaaaaa is the
                        word address in the table. See the section "SPRITES" below for
                        details.

                    The internal OAM address is invalidated when scanlines are being
                    rendered. This invalidation is deterministic, but we do not know how
                    it is determined. Thus, the last value written to these registers is
                    reloaded into the internal OAM address at the beginning of V-Blank if
                    that occurs outside of a force-blank period. This is known as 'OAM
                    reset'. 'OAM reset' also occurs on certain writes to $2100.

                    Writing to either $2102 or $2103 resets the entire internal OAM Address
                    to the values last written to this register. E.g., if you set $104 to
                    this register, write 4 bytes, then write $1 to $2103, the internal OAM
                    address will point to word 4, not word 6.
        */
        makeWriteRegister(0x2102, "OAM Address low byte", false,
            [this](Byte value)
            {
                oamStartAddress.setLowByte(value);
                processor.oam.currentAddress = oamStartAddress;
            }
        );
        makeWriteRegister(0x2103, "OAM Address high bit and Obj Priority", false,
            [this](Byte value)
            {
                oamStartAddress.setHighByte(value.getBit(0));
                processor.oam.currentAddress = oamStartAddress;
                processor.objectPriority = value.getBit(7);
            }
        );

        /*
            2104  wb++-- OAMDATA - Data for OAM write
                    dddddddd

                    Note that OAM writes are done in an odd manner, in particular
                    the low table of OAM is not affected until the high byte of a
                    word is written (however, the high table is affected
                    immediately). Thus, if you set the address, then alternate writes and
                    reads, OAM will never be affected until you reach the high table!

                    Similarly, if you set the address to 0, then write 1, 2, read, then
                    write 3, OAM will end up as "01 02 01 03", rather than "01 02 xx 03" as
                    you might expect.

                    Technically, this register CAN be written during H-blank (and probably
                    mid-scanline as well). However, due to OAM address invalidation the
                    actual OAM byte written will probably not be what you expect. Note that
                    writing during force-blank will only work as expected if that
                    force-blank was begun during V-Blank, or (probably) if $2102/3 have
                    been reset during that force-blank period.

                    See the section "SPRITES" below for details.
        */
        makeWriteRegister(0x2104, "OAM Data write", false,
            [this](Byte value)
            {
                processor.oam.writeByte(value);
            }
        );

        /*
            2105  wb+++- BGMODE - BG Mode and Character Size
                    DCBAemmm

                    A/B/C/D = BG character size for BG1/BG2/BG3/BG4
                        If the bit is set, then the BG is made of 16x16 tiles. Otherwise,
                        8x8 tiles are used. However, note that Modes 5 and 6 always use
                        16-pixel wide tiles, and Mode 7 always uses 8x8 tiles. See the
                        section "BACKGROUNDS" below for details.

                    mmm  = BG Mode
                    e    = Mode 1 BG3 priority bit
                        Mode     BG depth  OPT  Priorities
                                 1 2 3 4        Front -> Back
                        -=-------=-=-=-=----=---============---
                         0       2 2 2 2    n    3AB2ab1CD0cd
                         1       4 4 2      n    3AB2ab1C 0c
                                    * if e set: C3AB2ab1  0c
                         2       4 4        y    3A 2B 1a 0b
                         3       8 4        n    3A 2B 1a 0b
                         4       8 2        y    3A 2B 1a 0b
                         5       4 2        n    3A 2B 1a 0b
                         6       4          y    3A 2  1a 0
                         7       8          n    3  2  1a 0
                         7+EXTBG 8 7        n    3  2B 1a 0b

                        "OPT" means "Offset-per-tile mode". For the priorities, numbers
                        mean sprites with that priority. Letters correspond to BGs (A=1,
                        B=2, etc), with upper/lower case indicating tile priority 1/0. See
                        the section "BACKGROUNDS" below for details.

                        Mode 7's EXTBG mode allows you to enable BG2, which uses the same
                        tilemap and character data as BG1 but interprets bit 7 of the pixel
                        data as a priority bit. BG2 also has some oddness to do with some
                        of the per-BG registers below. See the Mode 7 section under
                        BACKGROUNDS for details.
        */
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
            }
        );

        /*
            2106  wb+++- MOSAIC - Screen Pixelation
                    xxxxDCBA

                    A/B/C/D = Affect BG1/BG2/BG3/BG4

                    xxxx = pixel size, 0=1x1, F=16x16
                        The mosaic filter goes over the BG and covers each x-by-x square
                        with the upper-left pixel of that square, with the top of the first
                        row of squares on the 'starting scanline'. If this register is set
                        during the frame, the 'starting scanline' is the current scanline,
                        otherwise it is the first visible scanline of the frame. I.e. if
                        even scanlines are completely red and odd scanlines are completely
                        blue, setting the xxxx=1 mid-frame will make the rest of the screen
                        either completely red or completely blue depending on whether you
                        set xxxx on an even or an odd scanline.

                        XXX: It seems that writing the same value to this register does not
                        reset the 'starting scanline', but which changes do reset it?

                        Note that mosaic is applied after scrolling, but before any clip
                        windows, color windows, or math. So the XxX block can be partially
                        clipped, and it can be mathed as normal with a non-mosaiced BG. But
                        scrolling can't make it partially one color and partially another.

                        Modes 5-6 should 'double' the expansion factor to expand
                        half-pixels. This actually makes xxxx=0 have a visible effect,
                        since the even half-pixels (usually on the subscreen) hide the odd
                        half-pixels. The same thing happens vertically with interlace mode.

                        Mode 7, of course, is weird. BG1 mosaics about like normal, as long
                        as you remember that the Mode 7 transformations have no effect on
                        the XxX blocks. BG2 uses bit A to control 'vertical mosaic' and bit
                        B to control 'horizontal mosaic', so you could be expanding over
                        1xX, Xx1, or XxX blocks. This can get really interesting as BG1
                        still uses bit A as normal, so you could have the BG1 pixels
                        expanded XxX with high-priority BG2 pixels expanded 1xX on top of
                        them.

                    See the section "BACKGROUNDS" below for details.
        */
        makeWriteRegister(0x2106, "Screen Pixelation", true,
            [this](Byte value)
            {
                // TODO, not implemented yet
            }
        );

        /*
            2107  wb++?- BG1SC - BG1 Tilemap Address and Size
            2108  wb++?- BG2SC - BG2 Tilemap Address and Size
            2109  wb++?- BG3SC - BG3 Tilemap Address and Size
            210a  wb++?- BG4SC - BG4 Tilemap Address and Size
                    aaaaaayx

                    aaaaaa = Tilemap address in VRAM (Addr>>10)
                    x    = Tilemap horizontal mirroring
                    y    = Tilemap veritcal mirroring
                        All tilemaps are 32x32 tiles. If x and y are both unset, there is
                        one tilemap at Addr. If x is set, a second tilemap follows the
                        first that should be considered "to the right of" the first. If y
                        is set, a second tilemap follows the first that should be
                        considered "below" the first. If both are set, then a second
                        follows "to the right", then a third "below", and a fourth "below
                        and to the right".

                    See the section "BACKGROUNDS" below for more details.
        */
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
                }
            );
            if (i > 0)
            {
                makeWriteTwiceRegister(0x210d + i * 2, bgName + " Horizontal Scroll", false, processor.backgrounds[i].horizontalScroll, true);
                makeWriteTwiceRegister(0x210e + i * 2, bgName + " Vertical Scroll", false, processor.backgrounds[i].verticalScroll, true);
            }
        }

        /*
            210b  wb++?- BG12NBA - BG1 and 2 Chr Address
            210c  wb++?- BG34NBA - BG3 and 4 Chr Address
                    bbbbaaaa

                    aaaa = Base address for BG1/3 (Addr>>13)
                    bbbb = Base address for BG2/4 (Addr>>13)
                        See the section "BACKGROUNDS" below for details.
        */
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
                }
            );
        }

        /*
            210d  ww+++- BG1HOFS - BG1 Horizontal Scroll
                  ww+++- M7HOFS  - Mode 7 BG Horizontal Scroll
            210e  ww+++- BG1VOFS - BG1 Vertical Scroll
                  ww+++- M7VOFS  - Mode 7 BG Vertical Scroll
                    ------xx xxxxxxxx
                    ---mmmmm mmmmmmmm

                    x = The BG offset, 10 bits.
                    m = The Mode 7 BG offset, 13 bits two's-complement signed.

                    These are actually two registers in one (or would that be "4 registers
                    in 2"?). Anyway, writing $210d will write both BG1HOFS which works
                    exactly like the rest of the BGnxOFS registers below ($210f-$2114), and
                    M7HOFS which works with the M7* registers ($211b-$2120) instead.

                    Modes 0-6 use BG1xOFS and ignore M7xOFS, while Mode 7 uses M7xOFS and
                    ignores BG1HOFS. See the appropriate sections below for details, and
                    note the different formulas for BG1HOFS versus M7HOFS.
        */
        makeWriteRegister(0x210d, "BG1 and Mode 7 Horizontal Scroll", false,
            [this](Byte value)
            {
                processor.backgrounds[size_t(Layer::Background1)].horizontalScroll.write(value);
                processor.mode7HorizontalScroll = to13Bit2sComplement(getMode7WordValue(value));
            }
        );
        makeWriteRegister(0x210e, "BG1 and Mode 7 Vertical Scroll", false,
            [this](Byte value)
            {
                processor.backgrounds[size_t(Layer::Background1)].verticalScroll.write(value);
                processor.mode7VerticalScroll = to13Bit2sComplement(getMode7WordValue(value));
            }
        );

        /*
            210f  ww+++- BG2HOFS - BG2 Horizontal Scroll
            2110  ww+++- BG2VOFS - BG2 Vertical Scroll
            2111  ww+++- BG3HOFS - BG3 Horizontal Scroll
            2112  ww+++- BG3VOFS - BG3 Vertical Scroll
            2113  ww+++- BG4HOFS - BG4 Horizontal Scroll
            2114  ww+++- BG4VOFS - BG4 Vertical Scroll
                    ------xx xxxxxxxx

                    Note that these are "write twice" registers, first the low byte is
                    written then the high. Current theory is that writes to the register
                    work like this:
                      BGnHOFS = (Current<<8) | (Prev&~7) | ((Reg>>8)&7);
                      Prev = Current;
                        or
                      BGnVOFS = (Current<<8) | Prev;
                      Prev = Current;

                    Note that there is only one Prev shared by all the BGnxOFS registers.
                    This is NOT shared with the M7* registers (not even M7xOFS and
                    BG1xOFS).

                    x = The BG offset, at most 10 bits (some modes effectively use as few
                        as 8).

                    Note that all BGs wrap if you try to go past their edges. Thus, the
                    maximum offset value in BG Modes 0-6 is 1023, since you have at most 64
                    tiles (if x/y of BGnSC is set) of 16 pixels each (if the appropriate
                    bit of BGMODE is set).

                    Horizontal scrolling scrolls in units of full pixels no matter if we're
                    rendering a 256-pixel wide screen or a 512-half-pixel wide screen.
                    However, vertical scrolling will move in half-line increments if
                    interlace mode is active.

                    See the section "BACKGROUNDS" below for details.
        */

        /*
        2115  wb++?- VMAIN - Video Port Control
                i---mmii

                i    = Address increment mode:
                        0 => increment after writing $2118/reading $2139
                        1 => increment after writing $2119/reading $213a
                    Note that a word write stores low first, then high. Thus, if you're
                    storing a word value to $2118/9, you'll probably want to set 1
                    here.

                ii = Address increment amount
                    00 = Normal increment by 1
                    01 = Increment by 32
                    10 = Increment by 128
                    11 = Increment by 128
        
                mm = Address remapping
                    00 = No remapping
                    01 = Remap addressing aaaaaaaaBBBccccc => aaaaaaaacccccBBB
                    10 = Remap addressing aaaaaaaBBBcccccc => aaaaaaaccccccBBB
                    11 = Remap addressing aaaaaaBBBccccccc => aaaaaacccccccBBB

                    The "remap" modes basically implement address translation. If
                    $2116/7 are set to #$0003, then word address #$0018 will be written
                    instead, and $2116/7 will be incremented to $0004.
        */
        makeWriteRegister(0x2115, "Video Port Control", false,
            [this](Byte value)
            {
                videoPortControl = value;
                incrementVramOnHighByte = value.getBit(7);
            }
        );

        /*
            2116  wl++?- VMADDL - VRAM Address low byte
            2117  wh++?- VMADDH - VRAM Address high byte
                    aaaaaaaa aaaaaaaa

                    This sets the address for $2118/9 and $2139/a. Note that this is a word
                    address, not a byte address!

                    See the sections "BACKGROUNDS" and "SPRITES" below for details.
        */
        makeWriteRegister(0x2116, "VRAM Address low byte", false,
            [this](Byte value)
            {
                processor.vram.currentAddress.setLowByte(value);
                //vramBuffer = processor.vram.readNextWord(0);
            }
        );
        makeWriteRegister(0x2117, "VRAM Address high byte", false,
            [this](Byte value)
            {
                processor.vram.currentAddress.setHighByte(value & 0x7f);
                vramBuffer = processor.vram.readNextWord(0);
            }
        );
        //makeWriteRegister(0x2116, "VRAM Address", false, processor.vram.address);

        /*
            2118  wl++-- VMDATAL - VRAM Data Write low byte
            2119  wh++-- VMDATAH - VRAM Data Write high byte
                    xxxxxxxx xxxxxxxx

                    This writes data to VRAM. The writes take effect immediately(?), even
                    if no increment is performed. The address is incremented when one of
                    the two bytes is written; which one depends on the setting of bit 7 of
                    register $2115. Keep in mind the address translation bits of $2115 as
                    well.

                    The interaction between these registers and $2139/a is unknown.

                    See the sections "BACKGROUNDS" and "SPRITES" below for details.
        */
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

        /*
            211a  wb++?- M7SEL - Mode 7 Settings
                    rc----yx

                    r    = Playing field size: When clear, the playing field is 1024x1024
                        pixels (so the tilemap completely fills it). When set, the playing
                        field is much larger, and the 'empty space' fill is controlled by
                        bit 6.

                    c    = Empty space fill, when bit 7 is set:
                           0 = Transparent.
                           1 = Fill with character 0. Note that the fill is matrix
                               transformed like all other Mode 7 tiles.
        
                    x/y  = Horizontal/Veritcal mirroring. If the bit is set, flip the
                           256x256 pixel 'screen' in that direction.

                    See the section "BACKGROUNDS" below for details.
        */
        makeWriteRegister(0x211a, "Mode 7 Settings", true,
            [this](Byte value)
            {
                processor.mode7HorizontalMirroring = value.getBit(0);
                processor.mode7VerticalMirroring = value.getBit(1);
                processor.mode7EmptySpaceFill = value.getBit(6);
                processor.mode7PlayingFieldSize = value.getBit(7);
            });

        /*
            211b  ww+++- M7A - Mode 7 Matrix A (also used with $2134/6)
            211c  ww+++- M7B - Mode 7 Matrix B (also used with $2134/6)
            211d  ww+++- M7C - Mode 7 Matrix C
            211e  ww+++- M7D - Mode 7 Matrix D
                    aaaaaaaa aaaaaaaa

                    Note that these are "write twice" registers, first the low byte is
                    written then the high. Current theory is that writes to the register
                    work like this:
                      Reg = (Current<<8) | Prev;
                      Prev = Current;
        
                    Note that there is only one Prev shared by all these registers. This
                    Prev is NOT shared with the BGnxOFS registers, but it IS shared with
                    the M7xOFS registers.

                    These set the matrix parameters for Mode 7. The values are an 8-bit
                    fixed point, i.e. the value should be divided by 256.0 when used in
                    calculations. See below for more explanation.

                    The product A*(B>>8) may be read from registers $2134/6. There is
                    supposedly no important delay. It may not be operative during Mode 7
                    rendering.

                    See the section "BACKGROUNDS" below for details.
        */
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
            }
        );
        makeWriteRegister(0x211e, "Mode 7 Matrix D", false,
            [this](Byte value)
            {
                processor.mode7MatrixD = getMode7WordValue(value);
            }
        );

        /*
            211f  ww+++- M7X - Mode 7 Center X
            2120  ww+++- M7Y - Mode 7 Center Y
                    ---xxxxx xxxxxxxx

                    Note that these are "write twice" registers, like the other M7*
                    registers. See above for the write semantics. The value is 13 bit
                    two's-complement signed.

                    The matrix transformation formula is:

                    [ X ]   [ A B ]   [ SX + M7HOFS - CX ]   [ CX ]
                    [   ] = [     ] * [                  ] + [    ]
                    [ Y ]   [ C D ]   [ SY + M7VOFS - CY ]   [ CY ]

                    Note: SX/SY are screen coordinates. X/Y are coordinates in the playing
                    field from which the pixel is taken. If $211a bit 7 is clear, the
                    result is then restricted to 0<=X<=1023 and 0<=Y<=1023. If $211a bits 6
                    and 7 are both set and X or Y is less than 0 or greater than 1023, use
                    the low 3 bits of each to choose the pixel from character 0.

                    The bit-accurate formula seems to be something along the lines of:
                      #define CLIP(a) (((a)&0x2000)?((a)|~0x3ff):((a)&0x3ff))

                      X[0,y] = ((A*CLIP(HOFS-CX))&~63)
                             + ((B*y)&~63) + ((B*CLIP(VOFS-CY))&~63)
                             + (CX<<8)
                      Y[0,y] = ((C*CLIP(HOFS-CX))&~63)
                             + ((D*y)&~63) + ((D*CLIP(VOFS-CY))&~63)
                             + (CY<<8)

                      X[x,y] = X[x-1,y] + A
                      Y[x,y] = Y[x-1,y] + C

                    (In all cases, X[] and Y[] are fixed point with 8 bits of fraction)

                    See the section "BACKGROUNDS" below for details.
        */
        makeWriteRegister(0x211f, "Mode 7 Center X", false,
            [this](Byte value)
            {
                processor.mode7CenterX = to13Bit2sComplement(getMode7WordValue(value));
            }
        );
        makeWriteRegister(0x2120, "Mode 7 Center Y", false,
            [this](Byte value)
            {
                processor.mode7CenterY = to13Bit2sComplement(getMode7WordValue(value));
            }
        );

        /*
            2121  wb+++- CGADD - CGRAM Address
                    cccccccc

                    This sets the word address (i.e. color) which will be affected by $2122
                    and $213b.
        */
        makeWriteRegister(0x2121, "CGRAM Address", false,
            [this](Byte value)
            {
                processor.cgram.currentAddress.setLowByte(value);
                processor.cgram.currentAddress.setHighByte(0x00);
            }
        );

        /*
            2122  ww+++- CGDATA - CGRAM Data write
                    -bbbbbgg gggrrrrr

                    This writes to CGRAM, effectively setting the palette colors.
        
                    Accesses to CGRAM are handled just like accesses to the low table of
                    OAM, see $2104 for details.

                    Note that the color values are stored in BGR order.
        */
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

        /*
            2123  wb+++- W12SEL - Window Mask Settings for BG1 and BG2
            2124  wb+++- W34SEL - Window Mask Settings for BG3 and BG4
            2125  wb+++- WOBJSEL - Window Mask Settings for OBJ and Color Window
                    ABCDabcd

                    c    = Enable window 1 for BG1/BG3/OBJ
                    a    = Enable window 2 for BG1/BG3/OBJ
                    C/A  = Enable window 1/2 for BG2/BG4/Color
                        When the bit is set, the corresponding window will affect the
                        corresponding background (subject to the settings of $212e/f).

                    d    = Window 1 Inversion for BG1/BG3/OBJ
                    b    = Window 2 Inversion for BG1/BG3/OBJ
                    D/B  = Window 1/2 Inversion for BG2/BG4/Color
                        When the bit is set, "W" should be replaced by "~W" (not-W) in the
                        window combination formulae below.

                    See the section "WINDOWS" below for more details.
        */
        makeWriteRegister(0x2123, "Window Mask Settings", true, processor.windowMaskSettings);

        /*
            2126  wb+++- WH0 - Window 1 Left Position
            2127  wb+++- WH1 - Window 1 Right Position
            2128  wb+++- WH2 - Window 2 Left Position
            2129  wb+++- WH3 - Window 2 Right Position
                    xxxxxxxx

                    These set the offset of the appropriate edge of the appropriate window.
                    Note that if the left edge is greater than the right edge, the window
                    is considered to have no range at all (and thus "W" always is false).
                    See the section "WINDOWS" below for more details.
        */
        makeWriteRegister(0x2126, "Window 1 Left Position", false, processor.window1Left);
        makeWriteRegister(0x2127, "Window 1 Right Position", false, processor.window1Right);
        makeWriteRegister(0x2128, "Window 2 Left Position", false, processor.window2Left);
        makeWriteRegister(0x2129, "Window 2 Right Position", false, processor.window2Right);

        /*
            212a  wb+++- WBGLOG - Window mask logic for BGs
                    44332211
            212b  wb+++- WOBJLOG - Window mask logic for OBJs and Color Window
                    ----ccoo

                    44/33/22/11/oo/cc = Mask logic for BG1/BG2/BG3/BG4/OBJ/Color
                        This specified the window combination method, using standard
                        boolean operators:
                          00 = OR
                          01 = AND
                          10 = XOR
                          11 = XNOR

                        Consider two variables, W1 and W2, which are true for pixels
                        between the appropriate left and right bounds as set in
                        $2126-$2129 and false otherwise. Then, you have the following
                        possibilities: (replace "W#" with "~W#", depending on the Inversion
                        settings of $2123-$2125)
                          Neither window enabled => nothing masked.
                          One window enabled     => Either W1 or W2, as appropriate.
                          Both windows enabled   => W1 op W2, where "op" is as above.
                        Where the function is true, the BG will be masked.

                    See the section "WINDOWS" below for more details.
        */
        makeWriteRegister(0x212a, "Window Mask Logic", true, processor.windowMaskLogic);

        /*
            212c  wb+++- TM - Main Screen Designation
            212d  wb+++- TS - Subscreen Designation
                    ---o4321

                    1/2/3/4/o = Enable BG1/BG2/BG3/BG4/OBJ for display
                                on the main (or sub) screen.

                    See the section "BACKGROUNDS" below for details.
        */
        makeWriteRegister(0x212c, "Main Screen Designation", false, processor.mainScreenDesignation);
        makeWriteRegister(0x212d, "Subscreen Designation", false, processor.subscreenDesignation);

        /*
            212e  wb+++- TMW - Window Mask Designation for the Main Screen
            212f  wb+++- TSW - Window Mask Designation for the Subscreen
                    ---o4321

                    1/2/3/4/o = Enable window masking for BG1/BG2/BG3/BG4/OBJ on the
                                main (or sub) screen.

                    See the section "BACKGROUNDS" below for details.
        */
        makeWriteRegister(0x212e, "Window Mask Designation for the Main Screen", true, processor.mainScreenWindowMaskDesignation);
        makeWriteRegister(0x212f, "Window Mask Designation for the Subscreen", true, processor.subscreenWindowMaskDesignation);

        /*
            2130  wb+++- CGWSEL - Color Addition Select
                    ccmm--sd

                    cc = Clip colors to black before math
                        00 => Never
                        01 => Outside Color Window only
                        10 => Inside Color Window only
                        11 => Always

                    mm = Prevent color math
                        00 => Never
                        01 => Outside Color Window only
                        10 => Inside Color Window only
                        11 => Always

                    s     = Add subscreen (instead of fixed color)

                    d     = Direct color mode for 256-color BGs

                    See the sections "BACKGROUNDS", "WINDOWS", and "RENDERING THE
                    SCREEN" below for details.
        */
        makeWriteRegister(0x2130, "Color Addition Select", false,
            [this](Byte value)
            {
                processor.directColorMode = value.getBit(0);
                processor.addSubscreen = value.getBit(1);
                processor.clipColorMathMode = ColorWindowMode(int(value.getBits(4, 2)));
                processor.clipColorToBlackMode = ColorWindowMode(int(value.getBits(6, 2)));
            }
        );

        /*
            2131  wb+++- CGADSUB - Color math designation
                    shbo4321

                    s    = Add/subtract select
                        0 => Add the colors
                        1 => Subtract the colors

                    h    = Half color math. When set, the result of the color math is
                        divided by 2 (except when $2130 bit 1 is set and the fixed color is
                        used, or when color is cliped).

                    4/3/2/1/o/b = Enable color math on BG1/BG2/BG3/BG4/OBJ/Backdrop

                    See the sections "BACKGROUNDS", "WINDOWS", and "RENDERING THE
                    SCREEN" below for details.
        */
        makeWriteRegister(0x2131, "Color Math Designation", false, processor.currentColorMathDesignation);

        /*
            2132  wb+++- COLDATA - Fixed Color Data
                    bgrccccc

                    b/g/r = Which color plane(s) to set the intensity for.
                    ccccc = Color intensity.

                    So basically, to set an orange you'd do something along the lines of:
                        LDA #$3f
                        STA $2132
                        LDA #$4f
                        STA $2132
                        LDA #$80
                        STA $2132

                    See the sections "BACKGROUNDS" and "WINDOWS" below for details.
        */
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

        /*
            2133  wb+++- SETINI - Screen Mode/Video Select
                    se--poIi

                    s    = "External Sync". Used for superimposing "sfx" graphics, whatever
                        that means. Usually 0. Not much is known about this bit.
                        Interestingly, the SPPU1 chip has a pin named "EXTSYNC" (or
                        not-EXTSYNC, since it has a bar over it) which is tied to Vcc.

                    e    = Mode 7 EXTBG ("Extra BG"). When this bit is set, you may enable
                        BG2 on Mode 7. BG2 uses the same tile and character data as BG1,
                        but interprets the high bit of the color data as a priority for the
                        pixel.

                        Various sources report additional effects for this bit, possibly
                        related to bit 7. For example, "Enable the Data Supplied From the
                        External Lsi.", whatever that means. Of course, maybe that's a
                        typo and it's supposed to apply to bit 7 instead.

                    p    = Enable pseudo-hires mode. This creates a 512-pixel horizontal
                        resolution by taking pixels from the subscreen for the
                        even-numbered pixels (zero based) and from the main screen for the
                        odd-numbered pixels. Color math behaves just as with Mode 5/6
                        hires. The interlace bit still has no effect. Mosaic operates as
                        normal (not like Mode 5/6). The 'subscreen' pixel is clipped (by
                        windows) when the main-screen pixel to the LEFT is clipped, not
                        when the one to the RIGHT is clipped as you'd expect. What happens
                        with pixel column 0 is unknown.

                        Enabling this bit in Modes 5 or 6 has no effect.

                    o    = Overscan mode. When set, 239 lines will be displayed instead of
                        the normal 224. This also means V-Blank will occur that
                        much later, and be shorter. All that happens is that extra lines
                        get added to the display, and it seems the TV will like to move
                        the display up 8 pixels. See below for more details.

                    I    = OBJ Interlace. When set regardless of BG mode, the OBJ will be
                        interlaced (see bit 0 below), and thus will appear half-height.

                        Note that this only controls whether obj are drawn as normal or
                        not; the interlace signal is only output to the TV based on bit 0
                        below.

                    i    = Screen interlace. When set in BG mode 5 (and probably 6), the
                        effective screen height will be 448 (or 478) pixles, rather than
                        224 (or 239). When set in any other mode, the screen will just get
                        a bit jumpy. However, toggling the tilemap each field would
                        simulate the increased screen height (much like pseudo-hires
                        simulares hires).

                        In hardware, setting this bit makes the SNES output a normal
                        interlace signal rather than always forcing one frame.

                    See the sections "BACKGROUNDS" and "SPRITES" below for details.

                    Overscan: The bit only matters at the very end of the frame, if you
                    change the setting on line 0xE0 before the normal NMI trigger point
                    then it's the same as if you had it on all frame. Note that this
                    affects both the NMI trigger point and when HDMA stops for the
                    frame.

                    If you turn the bit off at the very beginning of scanline X (for
                    0xE1<=X<=0xF0), NMI will occur on line X and the last HDMA transfer
                    will occur on line X-1. However, on my TV at least, the display will
                    remain in the normal no-overscan position for lines E1-EC, it will
                    move up only one pixel for line ED, and it will lose vertical sync
                    for lines EF-F4!

                    Turning the bit on, only line E1 gives any effect: NMI will occur on
                    line E2, although the last HDMA will still occur on line E0.
                    Anything else acts like you left the bit off the whole time. Note,
                    however, that if you wait too long after the beginning of the
                    scanline then you will get no effect.

                    Even if there is no visible effect, the overscan setting still
                    affects VRAM writes. In particular, executing "LDA #'-' / STA $2118
                    / LDA r2133 / STA $2133 / LDA #'+' / STA $2118" during the E1-F0
                    period will write only + or only - to VRAM, depending on whether the
                    overscan bit was set to 0 or 1.
        */
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

        /*
            2134 r l+++? MPYL - Multiplication Result low byte
            2135 r m+++? MPYM - Multiplication Result middle byte
            2136 r h+++? MPYH - Multiplication Result high byte
                    xxxxxxxx xxxxxxxx xxxxxxxx

                    This is the 2's compliment product of the 16-bit value written to $211b
                    and the 8-bit value most recently written to $211c. There is supposedly
                    no important delay. It may not be operative during Mode 7 rendering.
        */
        makeReadRegister(0x2134, "Multiplication Result", false, multiplicationResult);

        /*
            2137   b++++ SLHV - Software Latch for H/V Counter
                    --------

                    When read, the H/V counter (as read from $213c and $213d) will be
                    latched to the current X and Y position if bit 7 of $4201 is set. The
                    data actually read is open bus.
        */
        makeReadRegister(0x2137, "Software Latch for H/V Counter", false,
            [this](Byte)
            {
                if (programmableIOPort.getBit(7))
                {
                    horizontalScanlineLocation.value = Word(hCounter);
                    verticalScanlineLocation.value = Word(vCounter);
                    externalLatch = true;
                }
            }
        );

        /*
            2138 r w++?- OAMDATAREAD* - Data for OAM read
                    xxxxxxxx

                    OAM reads are straightforward: the current byte as set in $2102/3 and
                    incremented by reads from this register and writes to $2104 will be
                    returned. Note that writes to the lower table are not affected so
                    logically. See register $2104 and the section "SPRITES" below for
                    details.

                    Also, note that OAM address invalidation probably affects the address
                    read by this register as well.
        */
        makeReadRegister(0x2138, "Data for OAM read", true/*,
            [this](Byte& value)
            {
                value = 0x99;
            }*/
        );

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
                    //throw NotYetImplementedException("Register 4016: Latch on");
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
