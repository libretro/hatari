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

**To use this core you need a valid TOS ROM image named 'tos.img' in your RetroArch system directory.  This is the default TOS image selected.**
**You can also place TOS ROM images of your choice in 'system/hatarib/tos' (.IMG extension).  Select the TOS image you wish to use in Core Options->System.**

## Machine types

You can select the type of Atari computer Hatari will emulate.  Options available are ST, STE, TT and Falcon.  The menu also lists the recommended TOS versions for optimal use of each system.
This is especially important for the STE ( so STE enhanced games will work properly ).  TT and Falcon for certain machine functionality.  TOS 2.06 is a good go to for hard drive use.

## RAM size

Options are 512KB, 1MB, 2MB, 4MB, 8MB and 14MB.  2MB is a good number.  Some games will only run with 512KB.  Anything higher than 4MB unless needed could cause problems.

## Reset Type

Defaults to Cold Start.  But if you really want it you can change to Warm Start.

## Disk images
The Atari ST was a disk based computer so you need a disk image of the software you want to use with the emulator.

Accepted File Extensions: **.st .msa .stx .ipf**

If you have the option set in Core Options to 'Auto Insert Drive B' Hatari will also automount a second disk if found into drive B.  If an M3U file is selected it will automount the 2nd disk in the list.
Be sure to only use this on programs that support a drive B.  If you don't it can interfere with the switching of disks within the retroarch interface.  If you try to insert a disk that is already in a drive the Retroarch Disk control interface will inform you of this.

When launched with a valid disk image the emulator will automatically launch the program (most of the time) or open the TOS with disk inserted into drive A. In the TOS you need to manually launch the program by opening Drive A (double-click on the drive icon) and finding/selecting a .prg file (double-click on the file icon).

There are also options to write protect floppy disks as well as an option to enable/disable fast floppy access.

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

If 'Auto Insert Drive B' is enabled Hatari will automount the 2nd disk listed in the M3U file into drive B.

When a game asks for it, you can change the current disk in the RetroArch 'Disk Control' menu :
- Eject the current disk with 'Disk Cycle Tray Status'.
- Select the right disk index.
- Insert the new disk with 'Disk Cycle Tray Status'.
- If a disk is already inserted in another drive the mount will fail and retroarch will inform you of this.

Note : zip support is provided by RetroArch and is done before passing the game to the core. So, when using a m3u file, the specified disk image must be uncompressed (.st, .msa, .ipf file formats).
Note 2: Do not try to add hard drive images ( .vhd, .ide, .gem ) to an M3U.  They will just be ignored.  I may add functionality for this if someone can give me a good example of where this is practical.

## Hard Disk images
This version of Hatari is capable of mounting ACSI and IDE hard drive images.  To use this functionality name your ACSI images with an extension of  '.VHD' and your IDE images with an extension of '.IDE'.
Images larger that 2GB currently on work in the Windows, XBOX One and Wii-U builds.

## GEMDOS drives
This version of Hatari is also capaable of using the GEMDOS drive function of Hatari.  Just create an empty file with the same name as the GEMDOS "directory" with an extension of '.GEM'.  
Selecting this file will automount the directory with the same name (minus extension ) as a GEMDOS drive.  

Example :

My GEMDOS Drive.GEM
```
|
-> My GEMDOS Drive
 desktop.inf
 GAMES
   10THFRAM
     lots of files..
 UTILS
   COLORTOS
   FASTMOUE E

and so on
```

If you have a disk image named 'BOOT.ST' in the 'system\hatari\' folder Hatari will automount this disk.  It is recommended to have this so that the emulated Atari will recognized the GEMDOS drive.
BOOT.ST is included in the Atari Gamebase ST.  So it is easy to obtain.

If the directory contains only single letter (C-Z) subdirectories, each of these subdirectories will be treated as a separate partition, otherwise the given directory itself will be assigned to drive "C:".
In the multiple partition case, the letters used as the subdirectory names will determine to which drives/partitions they’re assigned.

There is also an options to write protect the Hard Disk drives.

## Default Controls

```
Port 1:

B   Fire / Left mouse button / Virtual keyboard keypress
A   Auto-Fire / Right mouse button
Y   Toggle virtual keyboard Shift
X   Show/hide virtual keyboard
SEL Toggle Joystick / Mouse mode
STR Enter/Exit Hatari GUI
L   Show/Hide status bar
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

RetroPad Mappings:

Use the RetroPad Mappings option in the Core Options menu to remap your keys.
It is much more functional than the usual 'Controls' method.
Keep in mind that any mappings assigned to the VKBD will only work when the VKBD is onscreen.

```

## Drive activity, Joystick/Mouse mode and Mouse speed status display

You can tell Hatari to display drive LED activity in the retroarch status display for convenience.
You can also tell Hatari to display when Joystick/Mouse mode is toggled or the Mouse speed is changed either in the retroarch Status display or the retroarch OSD.
This is less obtrusive than the included status bar accessed with the L button.

## Hatari.cfg

Autoloading of the hatari.cfg file is turned off by default as to not cause interference with the new options.  If at all possible try to use the retroarch core options to set everything up.
For those who insist you can turn back on the autoloading of the hatari.cfg on a game by game basis.  The location of the Hatari.cfg file has also been changed to 'system\hatari'.
This fixes access to the files on many systems.  This has been left untouched for WIIU, VITA and PS3 systems until I receive feedback from users of those systems.

## Knows Bugs
- Toggling borders in the Hatari GUI menu doesn't work properly.  It is highly suggested to do this in the Core-Options menu.
- It's a debug release, so expect bug?
