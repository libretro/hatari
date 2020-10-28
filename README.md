# HATARI LIBRETRO

Hatari is an Atari ST/STE/TT/Falcon emulator for Linux, FreeBSD, NetBSD, BeOS, Mac-OSX and other Systems which are supported by the SDL library.

Unlike most other open source ST emulators which try to give you a good environment for running GEM applications, Hatari tries to emulate the hardware as close as possible so that it is able to run most of the old Atari games and demos.  Because of this, it may be somewhat slower than less accurate emulators.

Hatari homepage: http://hatari.tuxfamily.org/index.html
Shallow fork of: https://hg.tuxfamily.org/mercurialroot/hatari/hatari

## Building Hatari-libretro
```
git clone http://github.com/libretro/hatari
cd hatari
make -f Makefile.libretro EXTERNAL_ZLIB=1
```

## The Atari ST

The Atari ST was a 16/32 bit computer system which was first released by Atari in 1985. Using the Motorola 68000 CPU, it was a very popular computer having quite a lot of CPU power at that time. 

## TOS image
TOS (The Operating System; also Tramiel Operating System, from Jack Tramiel, owner of Atari Corp. at the time) is the operating system of the Atari ST range of computers. Atari's TOS was usually run from ROM chips contained in the computer.
See https://en.wikipedia.org/wiki/Atari_TOS

**To use this core you need a valid TOS ROM image named 'tos.img' in your RetroArch system directory.**

## Disk images
The Atari ST was a disk based computer so you need a disk image of the software you want to use with the emulator.

Accepted File Extensions: **.st .msa .ipf**

When launched with a valid disk image the emulator will automatically launch the program (most of the time) or open the TOS with disk inserted into drive A. In the TOS you need to manually launch the program by opening Drive A (double-click on the drive icon) and finding/selecting a .prg file (double-click on the file icon).

## M3U Support and Disk control
When you have a multi disk game, you can use a m3u file to specify each disk of the game and change them from the RetroArch Disk control interface.

A M3U file is a simple text file with one disk per line (see https://en.wikipedia.org/wiki/M3U).

Example :

Simpsons, The - Bart vs. The Space Mutants.m3u
```
Simpsons, The - Bart vs. The Space Mutants_Disk1.st
Simpsons, The - Bart vs. The Space Mutants_Disk2.st
```
Path can be absolute or relative to the location of the M3U file.

When a game ask for it, you can change the current disk in the RetroArch 'Disk Control' menu :
- Eject the current disk with 'Disk Cycle Tray Status'.
- Select the right disk index.
- Insert the new disk with 'Disk Cycle Tray Status'.

Note : zip support is provided by RetroArch and is done before passing the game to the core. So, when using a m3u file, the specified disk image must be uncompressed (.st, .msa, .ipf file formats).

## Default Controls

```
Port 1:

B   Fire / Left mouse button / Virtual keyboard keypress
A   Auto-Fire / Right mouse button
Y   Toggle virtual keyboard Shift
X   Show/hide virtual keyboard
SEL Toggle Joystick / Mouse mode
STR Enter/Exit Hatari GUI
L   Show/Hide status
R   Select virtual keyboard page
L2  Lower Mouse Speed (1-6) for gui and emu
R2  Raise Mouse speed (1-6)
R3  Keyboard space
Pad / Analog Left - Joystick / Mouse

Port 2:

B   Fire
A   Auto-Fire
L2  Show/Hide status
Pad / Analog Left - Joystick

Other:

Mouse - Mouse (when port 1 is not in Joystick mode)
Keyboard - Atari ST keys
Scroll Lock - (RetroArch default hotkey) game focus mode disables keyboard shortcuts, captures mouse
F11 - (RetroArch default hotkey) capture/release mouse
```

## Knows Bugs
- It's a debug release, so expect bug?
