=================================================
Audio Overload - computer/console music player
Windows release 2.0 - July 28, 2008

Emulation core by Richard Bannister

Portions by R. Belmont, BouKiCHi, Fx3, Adam Bienias, 
Juergen Buchmueller, Jarek Burczynski, Julien Frelat, 
Benjamin Gerard, Shay Green, Charles MacDonald, 
Kerwin Medina, Mitsutaka Okazaki, Haruhiko Okumura, 
Tatsuyuki Satoh, Christian Scheurer, m_puusan, GORRY, 
smf, the P.E.Op.S. team, Mamiya, and cisc.

Windows port and GUI by R. Belmont
=================================================

What's this?
------------

Audio Overload is a player for various types of music files which you may
find on the Internet.

What's it play?
---------------

33 console and home computer file formats are now supported.

.AHX  - Commodore Amiga
.AY   - Amstrad CPC/Spectrum ZX/Atari ST
.COP  - Sam Coupe (also found as .SAA sometimes)
.DSF  - Sega Dreamcast
.GBS  - Nintendo Gameboy
.GSF  - Nintendo Gameboy Advance
.GYM  - Sega Megadrive/Genesis
.HES  - PC Engine
.HVT  - Commodore Amiga
.IMF  - PC-compatibles, various Apogee games
.KSS  - MSX
.MDX  - Sharp X68000
.MOD  - Commodore Amiga
.NSF  - Nintendo NES
.NSFE - Nintendo NES (enhanced tags)
.ORC  - TRS-80 Orchestra-90
.PSF  - Sony PlayStation
.PSF2 - Sony PlayStation 2
.QSF  - Capcom QSound
.RAW  - PC-compatibles with an AdLib
.ROL  - PC-compatibles, AdLib Visual Composer
.S3M  - PC-compatibles with a GUS or SoundBlaster
.S98  - NEC PC-98 (also the related .MYM and .X1F formats)
.SAP  - Atari XL/XE
.SC68 - Atari ST and Amiga (this file format can contain many other types)
.SCI  - PC-compatibles, various Sierra games
.SNDH - Atari ST
.SPC  - Super Nintendo
.SPU  - Sony PlayStation
.VGM  - Sega Master System/Game Gear
.VTX  - Spectrum Vortex Tracker
.WSR  - Bandai WonderSwan/WonderSwan Color
.YM   - Amstrad CPC/Spectrum ZX/Atari ST

In addition, AO can find files of those types when they are inside a .zip,
.7z, .cab, or .rar container.

What's new?
-----------

- DSF support
- Updated SSF support
- Tray icon now allows you to control AO without the app being frontmost
- Many bug/crash fixes, especially for 64-bit


What's wrong with it?
---------------------

SSF support is very preliminary - ElSemi and I are still working out
bugs in the SCSP emulation.

S3Ms with FM instruments don't work yet.  There's partial support in
the engine but not enough to make noise.

.GSF files may lose sync between the digital channels and the Game Boy
PSG after a while due to a core bug.  (This may be better in b9)


How to use?
-----------

Launch the "aowin32.exe" application.  Click the "Open" button to
bring up a standard open file dialog.  Choose a file of one of the types 
above or a .zip/.rar/.cab file containing files of those type(s).

You may remove a file from the list by clicking the "Delete item" button
while it's highlighted.

Unpacked files will appear by their filename in the list.  Files inside
a container (ZIP/RAR/CAB) will show the name of the container in parenthesis
after their name.  To play a file, simply double-click on it and it will 
start playing.

To stop playback, click the Stop button.

If no song is currently playing, the Play button will become active 
and you may click it to play whatever file is selected in the list.

Some filetypes (such as .NSF, .KSS, and .HES) contain multiple songs 
in each file.  If this is the case, the forward and back arrows will
become active when the song is playing and you may click the arrows to
navigate back and forth through the file.  Additionally for this type of
song the edit box marked "Song" will become active and you may jump to 
any valid song number by entering it in that box and pressing Enter or
clicking the "Jump" button.

To save a song to a WAV, click the "WAV..." button and pick a name.  The 
next time after that that you click the play button, "Jump to", track up, 
or track down the logging will begin.  To stop logging, click the stop button.


What's coming in the future?
----------------------------

[Windows specific]
- The framerate of the oscilloscope will be improved.  If you have an
  MFC component for a fast oscilloscope, please contact me on the 
  messageboard :-)

[In general]
- The ability to save and load playlists will be added.
- The ability to record any song to a .WAV file will be added.
- Improved playback and more filetypes.  Suggestions are welcome on the
  official Audio Overload messageboard located at www.bannister.org.


Legal
-----
Copyright (c) 2001-2008 Richard Bannister.
Port code and GUI (c) 2008 R. Belmont.  All rights reserved.




