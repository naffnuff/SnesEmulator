# SnesEmulator
## Purpose
This is intended as a showcase of my abilities as a C++ programmer. The source code is, in design and execution, all my own creation.

## Scope
This emulator will probably never be able to run all or even most SNES games, let alone have all the features of some of the other emulators out there. I will be extremely pleased if some day I manage to finish my three favorite SNES games on it, namely
* Super Mario World
* The Legend of Zelda - A Link to the Past
* Super Metroid

As of now, there is no audio.

## Build dependencies
In order to build the source you will need a compiler capable of C++17. Visual Studio 2019 Community is the main tool I used, but I have also worked to keep compability with GCC (v7.3.1) and CMake (v3.10). You will also need
* GLFW (v3.3)
* OpenGL (v3.2)
* PortAudio (v19.6)

## Sources and acknowledgements
I read a lot to get me going with this project. So far I have found that the following documents contain all the information on the SNES I needed to write this emulator. Most of them are a product of the work of other enthusiasts who often had to reverse engineer the hardware themselves. Without them, this would have been a much harder task.
### WDC 65816 (CPU)
#### Table of opcodes
http://www.defence-force.org/computing/oric/coding/annexe_2/index.htm
#### Description of opcodes
http://www.6502.org/tutorials/65c816opcodes.html
#### Data sheet
http://www.westerndesigncenter.com/wdc/documentation/w65c816s.pdf
#### Decimal mode
http://www.6502.org/tutorials/decimal_mode.html
### SPC-700 (Sound processor)
#### Table of opcodes, register descriptions, and boot ROM
https://github.com/gilligan/snesdev/blob/master/docs/spc700.txt
#### DSP (Digital Signal Processor, part of the sound processor)
##### General
The SNES DSP is one area of the SNES for which it is especially hard to find secondary documentation. For this, I had to resort to the official SNES development manual, which is notoriously opaque and rife with error. I found it through the following link:
http://folk.uio.no/sigurdkn/snes/snes_manual1.pdf
##### ADSR (Attack-Delay-Sustain-Release, or sound envelope)
I found the official documentation especially lacking as to how the SNES produces its sound envelopes. Instead I ended up modelling it on a technique I found in the following blog posts (part 1-3):
http://www.earlevel.com/main/2013/06/01/envelope-generators/
##### BRR (Bit-Rate Reduction)
https://wiki.superfamicom.org/bit-rate-reduction-(brr)
### SNES
#### registers
http://folk.uio.no/sigurdkn/snes/registers.txt
#### memory map
http://simsnex.tripod.com/SNESMem.txt
#### timing
http://folk.uio.no/sigurdkn/snes/timing.txt
#### transparency
http://folk.uio.no/sigurdkn/snes/transparency.txt

I did not in any way reverse engineer the SNES myself. In addition to relying on said documents I spent some time stepping through the debuggers of two emulators, Bsnes Plus (v05.35) and SnesX9 (v1.51.ep10r2 with Geiger's debugger), comparing their emulation state with mine and analyzing the behaviours I had an extra hard time understanding. The former is known for it's fidelity to the SNES hardware and has a very user-friendly debugger, whereas the latter was mainly useful to me for analyzing (H)DMA.

To get me started with the renderer I also took and modified some code from tutorial #1 in these turorials:
https://github.com/opengl-tutorials/ogl
