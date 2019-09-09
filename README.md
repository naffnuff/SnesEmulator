# SnesEmulator
## Purpose
This is intended as a showcase of my abilities as a C++ programmer. The source code is, in design and execution, all my own creation.

## Scope
This emulator will probably never be able to run all or even most SNES games, let alone have all the features of some of the other emulators out there. I will be extremely pleased if some day I manage to finish my three favorite SNES games on it, namely
* Super Mario World
* The Legend of Zelda - A Link to the Past
* Super Metroid

As of now, there is no audio.

## Requirements
In order to build the source you will need a compiler capable of C++17. Visual Studio 2019 Community is the main tool I used, but I have also worked to keep compability with GCC (v7.3.1) and CMake (v3.10). You will also need
* GLEW (v2.1.0)
* GLFW (v3.3)
* OpenGL (I worked with v4.5, but the renderer creates a v3.1 context, so that is probably the requirement)

## Sources and acknowledgements
I read a lot to get me going with this project. So far I have found that the following documents contain all the information I needed to write this emulator. Without them, I don't think I could have done it.
### WDC 65816
## Table of opcodes
http://www.defence-force.org/computing/oric/coding/annexe_2/index.htm
## Description of opcodes
http://www.6502.org/tutorials/65c816opcodes.html
## Data sheet
http://www.westerndesigncenter.com/wdc/documentation/w65c816s.pdf
## Decimal mode
http://www.6502.org/tutorials/decimal_mode.html
### SPC-700
## Table of opcodes, register descriptions, and boot ROM
https://github.com/gilligan/snesdev/blob/master/docs/spc700.txt
## Full description of the sound module
https://web.archive.org/web/20090106230547/http://www.alpha-ii.com/snesmusic/files/spc700_apu_manual.txt
### SNES registers
http://folk.uio.no/sigurdkn/snes/registers.txt
### SNES memory map
http://simsnex.tripod.com/SNESMem.txt
### SNES timing
http://folk.uio.no/sigurdkn/snes/timing.txt
### SNES transparency
http://folk.uio.no/sigurdkn/snes/transparency.txt

I did not in any way reverse engineer the SNES myself (I have never even ownded one!). In addition to relying on said documents I spent countless hours stepping through the debuggers of two emulators, Bsnes Classic plus (v073u1) and SnesX9 (v1.51.ep10r2 with Geiger's debugger), comparing their emulation state with mine and analyzing the behaviours I had an extra hard time understanding. The former is known for it's fidelity to the SNES hardware and has a very user-friendly debugger, whereas the latter was mainly useful to me for analyzing (H)DMA.

To get me started with the renderer I also took and modified some code from tutorial #1 in these [turorials](https://github.com/opengl-tutorials/ogl).