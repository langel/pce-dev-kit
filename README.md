# PC Engine Development Archive
This is a collection of resources found around the web pertaining to homebrew development for the PC Engine aka TurboGrafx-16.

## CPU and Other Processors
The PCE has a custom 65C02 processor sometimes referred to by its CMOS designation 65CS02, but more commonly known as the HuC6280. The 6280 has extra opcodes specific for quicker operations with the console's Video Display Controller. The 6280 package also holds the programmable sound generator (sometimes referred to as an SCC chip by VGM nerds).

## MagicKit's HuC and PCEAS
HuC is a library and transpiler for making PC Engine ROMs using the C language. It converts the project into assembly and then compiles with PCEAS (PC Engine ASembler). DOS version literally requires DOS or DOSBOX. Windows version works on modern installs with Command Prompt. OSX version could easily predate OSX since the HuC/PCEAS source has not been updated since Dec 2000. Linux version wouldn't work on modern Debian. `"windows huc\bin\pceas.exe" -S test.asm` ftw

## PCEAS Updates
Newer builds of `pceas` can be found in the `pceas_bin` directory. These versions were all derived from the [nop00 repo](https://github.com/nop00/pceas) since it was the first one discovered with somewhat-recent patches. If these versions of pceas do not work on your environment you'll need to pull said repo, run `cmake` then `make`, and then it will be compiled to a `Debug` directory.

## PCEAS Quirks
indirect mode uses square brackets [] rather than the traditionally notated parenthesis () i.e.: `lda [addr],y` not `lda (addr),y` {rtfm but the manual is the source ;-;}

## Audio Notes
MML, Squirrel, Deflemask -- maybe some more notes someday haha  xD

## Links / Resources
- [ChibiAkumas General Knowledge](https://www.chibiakumas.com/6502/pcengine.php)
- [ChibiAkumas Intro to 6280 OpCodes](https://www.chibiakumas.com/6502/pcengine.php)
- [MagicKit Documentaion](http://www.magicengine.com/mkit/doc.html)
- [Archaic Pixels Dev Wiki](http://archaicpixels.com/Main_Page)
- [ObeyBrew Tutorials](http://obeybrew.com/tutorials.html)
- [Chris Covell's CPU / Emulator Tester](https://chrismcovell.com/CPUTest/index.html)
- [Alddee Homebrew Game w/ source](http://www.sebastianmihai.com/turbografx-alddee.html)
- [Wavegen algo waveform generator](https://melonadem.com/wavegen/)
- [Squirrel Music Maker for PCE](http://www.aetherbyte.com/aetherbyte-squirrel_for_pc-engine_and_turbografx-16.html)
- [An Immolated Hot Dog](https://tikolu.net/emojimix/%F0%9F%8C%AD+%F0%9F%94%A5)
