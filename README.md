# SnesEmulator

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

I did not in any way reverse engineer the SNES myself. I really feel I stand on the shoulders of giants here. In addition to relying on said documents I spent countless hours stepping through the debuggers of two emulators, bsnes classic (073u1) and SnesX9 (v1.51.ep10r2 with Geiger's debugger), comparing their emulation state with mine. However, I deliberately did not read any source code of their or any other emulator, so as not to be consciously or subconsciously affected. The source code of this project is in design and execution 100% my own.
