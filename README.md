Wwasm
=====

This is an unofficial WebAssembly port of the engine behind the 3D first-person shooter *Return to Castle Wolfenstein*.

[Run Wwasm in your browser here](https://gmh-code.github.io/wwasm/).

Wwasm is based upon [iortcw](https://github.com/iortcw/iortcw), and has an enhanced version of the *Quake III* engine at the core.

Also available are the following engines, which run very well in modern web browsers:

- [Qwasm](https://gmh-code.github.io/qwasm/) ([source](https://github.com/GMH-Code/Qwasm) based on id's original *Quake* engine code)
- [Qwasm2](https://gmh-code.github.io/qwasm2/) ([source](https://github.com/GMH-Code/Qwasm2) based on *Yamagi Quake II*)
- [Dwasm](https://gmh-code.github.io/dwasm/) ([source](https://github.com/GMH-Code/Dwasm) based on *PrBoom+* and the *DOOM* engine)

PK3 Prerequisites
-----------------

This project needs at least one `.pk3` resource file to run.  You can use any of the following:

- The file from the freely available demonstration version of the original game
- The files from the paid full version of the original game, combined with updates
- Third-party standalone files that are based on the *RTCW* engine

Playing the Original RTCW Demonstration Version
-----------------------------------------------

If you just want to get up and running with the demonstration version, you can get this freely available Linux installer online:

    Filename: wolfspdemo-linux-1.1b.x86.run
    File size: 117,813,349 bytes (112 MiB)
    SHA1: 15B6DEFDBB2B9520D286FD700BB7ECC7C7935424
    SHA256: DBFF5EA928802B1BDDFD4C171BF08ED4294B2DA0273E1CF0802FDCEDC40C23C3

It is not necessary to run the installer.

Extract `pak0.pk3`:

1. Open the file in an extraction tool that can handle Linux installers embedded with Gzipped data.  *7-Zip* or *WinRAR* are both compatible.
2. Open the resultant TAR file in the same program.  The file should be called `wolfspdemo-linux-1.1b.x86` (no `.tar` extension).
3. The `pak0.pk3` file is located in the `demomain` folder.

Transfer the file to Wwasm:

1. In the `wasm/fs` folder for this project, rename the `main` folder to `demomain`, keeping the contents.
2. Place `pak0.pk3` in the `demomain` folder, along with the other files.

Then build the project.  Note that updates are not required for the demo.

When viewing the completed build in a browser, you will need to set `com_basegame` to `demomain`, as specified in the command-line example.

Playing the Original RTCW Full Game
-----------------------------------

Extract these files from your purchased version of the game:

    pak0.pk3
    sp_pak1.pk3
    sp_pak2.pk3

These patch data files are also required.  They are included in *iortcw* release 1.51c, amongst other locations:

    sp_pak3.pk3
    sp_pak4.pk3

Add the files to `wasm/fs/main`, keeping the files already there, and build the project.

Do not host the full game publically.

Playing a Third-Party Standalone Version
----------------------------------------

To play a game that does not require the demonstration or full versions of RTCW:

1. In `wasm/fs`, rename `main` to the standalone game's name, if necessary.
2. Place the `.pk3` files in the renamed folder, along with the other files.
3. If the third-party version contains a `vm` folder containing QVM game code, you should include this folder and not create the QVM code yourself.
4. Follow the *iortcw* documentation regarding how to create a standalone version.

When you are done, build the project with `BUILD_STANDALONE=1` and, if the default game name has changed, add `BASEGAME=mygame`, replacing `mygame` with the new name.

Licence Warnings
----------------

The licence for the demonstration version of Return to Castle Wolfenstein only appears to permit duplication of the installer that was originally obtained from an official source, so it appears as though, understandably, the installer's contents cannot be distributed nor embedded separately.

The licence for the full version of Return to Castle Wolfenstein is obviously much more restrictive.  You should never host or run this publically, nor share the files with others.

Licence compliance is always entirely your responsibility.

System Requirements
-------------------

A 64-bit browser is highly recommended for play, and this is included in most modern devices.  32-bit browsers, or devices running with low system RAM, may not always be able to start or play the game due to large, contiguous memory allocations being denied.  In these circumstances, the engine may run sometimes, but not at other times.

In-Browser Saving
-----------------

Attempts will be made to commit data to browser storage when:

- The game auto-saves your progress
- Manually saving a named game
- Changing settings and exiting the program

Data should persist across browser sessions.

Command-Line Arguments
----------------------

You can pass arguments to Wwasm at runtime.  By default, the query portion of the URL is used, but the JavaScript code can be modified to use anything else, such as an input text box.

For example, to start the game up in demo mode, you would normally start the game with command-line arguments set to `+set com_basegame demomain`.  This would translate to something like:

    https://127.0.0.1/?+set&com_basegame&demomain

Physical Gamepads & Joysticks
-----------------------------

Attached gamepads and analogue controls should work, providing your browser supports their functionality.

To activate a controller, press a button on it during play.  You can also physically connect or disconnect controllers after the game starts, and the change should be recognised automatically.

Recording Demos
---------------

Recording demos is supported.

You can create a demo by starting the game, opening the console with the key above `TAB` (usually the tilde or backquote key), and then typing something like this:

    record mydemo

Then to stop:

    stoprecord

The file will be saved in the browser database, but you will also be given the opportunity to export it if you want to.

The demo can be played back later by typing this in the console:

    demo mydemo

Playing back a demo will permanently stop any game in progress.

Known Issues / Workarounds
--------------------------

### Rendering

Any code that normally restarts the video subsystem will *not* do so due to graphical corruption in the GL4ES layer.  If you have made changes that require a video restart, you must quit the game the normal way and restart it to apply the changes.

In Wwasm, the `vid_restart` command (or anything that calls it) will do one of two things:

- If outside of the menu, such as when playing the game, a yellow console message will be shown, allowing you to save and quit.  You can then reload the page.
- If in the main menu, a modal message box will be shown, since console messages are hidden at that time.

### Game Code

There are two versions of game code that the engine can run:

- Native compiled C code
- QVM (Quake 3 Virtual Machine) code

QVM is slower than native code, but game code is not running all of the time, and the performance penalty appears to be acceptable.

Both native and QVM code can be successfully compiled and loaded, but currently only QVM code successfully executes in Wwasm.

### Multiplayer

The multiplayer version is not included, but the patches created for the single player port of Wwasm should be mostly compatible with the multiplayer version of *iortcw*.

If you choose to apply the single player patches to the multiplayer version, you will need to fix all the conflicts and issues along the way, and then either:

- Run a private WebSockets proxy and configure the build with the proxy's configuration, or,
- Port the UDP protocol code to WebSockets.

If you decide to release a multiplayer version based on Wwasm, please give credit where it is due.

Building on Linux for WebAssembly
---------------------------------

You need to complete all the following steps in order to make a working build.

### Put PK3 Files in Position

Place the required `.pk3` files in the correct location in Wwasm's project folder, as indicated towards the top of this document.

### Generate Game Code

You must build (or supply) these three cross-platform QVM (Quake 3 Virtual Machine) game code files:

    cgame.sp.qvm
    qagame.sp.qvm
    ui.sp.qvm

It is likely you do not have these files already, so this project includes the ability to compile the versions of these files that work with the default game types.  To do this, run this command on a Linux system in this project's root directory:

    make BUILD_CLIENT=0 BUILD_GAME_SO=0 BUILD_GAME_QVM=1

The three `.qvm` files will normally be written into a folder similar to `build/release-linux-x86_64/main/vm`.

These files should be placed in this project's `wasm/fs/demomain/vm` or `wasm/fs/main/vm` directory.  Create the `vm` folder if necessary.

### Get EMSDK

This is required to build both GL4ES and Wwasm.

Clone or download EMSDK: https://emscripten.org/docs/getting_started/downloads.html

Install, activate, and set the environment variables for the latest version, as per the instructions.

### Compile GL4ES

This is required to translate hardware-accelerated graphics from regular OpenGL to OpenGL ES.  EMSDK then does final adjustments to get the OpenGL ES code to run in WebGL.

1. Clone or download GL4ES from https://ptitseb.github.io/gl4es/
2. Run the GL4ES *Emscripten* build according to the instructions on https://ptitseb.github.io/gl4es/COMPILE.html

### Compile Wwasm

Ensure you have completed all the above steps before you proceed.

Run this command in the Wwasm folder.  Replace `/tmp/gl4es` with the location of your GL4ES build:

    emmake make GL4ES_PATH=/tmp/gl4es

Emscripten will be automatically detected and used for the build.

When the build is complete, the process will output the following into the `build/release-emscripten-wasm` folder:

    index.html
    index.js
    index.data
    index.wasm

These files can then be placed on a web server.  To reduce bandwidth and download time, compress the files using Gzip (or better, Brotli) compression, host the files statically, and verify the web browser is doing the decompression for each file.

Other READMEs
-------------

Some READMEs have been renamed to avoid conflicts:

- The `README.txt` file for id Software's *Return to Castle Wolfenstein* Single Player code is now named `README-id.txt`.
- The `README.md` file for *iortcw* is now named `README-iortcw.md`.

-----

This project is not affiliated with, endorsed by, or in any way connected to id Software, Bethesda Softworks, or ZeniMax Media.  All trademarks and copyrights are the property of their respective owners.
