# SnesEmulator
## Purpose
This is intended as a showcase of my abilities as a software engineer and as a C++ programmer. The source code is, in design and execution, 100% my own.

## Scope
This emulator will probably never be able to run all or even most SNES games. I will be extremely please if some day I manage to run my three favorite games on the SNES on it:
* Super Mario World
* The Legend of Zelda - A Link to the Past
* Super Metroid

## Requirements
In order to build the source you will need a compiler capable of C++17. Visual Studio 2017 is the main tool I used, but I have also worked to keep compability with GCC (v7.3.1) and CMake (v3.10). You will also need
* GLEW (v2.1.0)
* GLFW (v3.3)
* OpenGL (I have v4.5, but the renderer creates a v3.1 context, so that would probably be the minimum)

## Sources and acknowledgements
I read a lot to get me going with this project. So far I have found that the following documents contain all the information I needed to write this emulator. Without them, I don't think I could have done it.
### 65816
http://www.defence-force.org/computing/oric/coding/annexe_2/index.htm
http://www.6502.org/tutorials/65c816opcodes.html
http://www.westerndesigncenter.com/wdc/documentation/w65c816s.pdf
https://wiki.nesdev.com/w/images/7/76/Programmanual.pdf
### SPC-700
https://github.com/gilligan/snesdev/blob/master/docs/spc700.txt
https://www.crazysmart.net.au/kindred/files/spc700_inst_op.pdf
https://web.archive.org/web/20090106230547/http://www.alpha-ii.com/snesmusic/files/spc700_apu_manual.txt
### SNES registers
http://folk.uio.no/sigurdkn/snes/registers.txt
### SNES memory map
http://simsnex.tripod.com/SNESMem.txt
### SNES timing
http://folk.uio.no/sigurdkn/snes/timing.txt
### SNES transparency
http://folk.uio.no/sigurdkn/snes/transparency.txt

I did not in any way reverse engineer the SNES myself. I really feel I stand on the shoulders of giants here. In addition to relying on said documents I spent countless hours stepping through the debuggers of two emulators, Bsnes Classic (v073u1) and SnesX9 (v1.51.ep10r2 with Geiger's debugger), comparing their emulation state with mine. However, I deliberately did not read any source code of these or any other emulators, so that I can be sure that the source code of this project is indeed my own.
