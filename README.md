Speech to Text module for Godot
===============================

[![Build Status](https://travis-ci.org/SamuraiSigma/speech-to-text.svg?branch=master)](https://travis-ci.org/SamuraiSigma/speech-to-text)

This is a Speech to Text (STT) module for [Godot][godot]. In other words, a module
that captures the user's microphone input and converts it to text.

[godot]: https://godotengine.org "Godot site"


Requirements
------------

The module can be built with Godot 3.0 on the following platforms:

- Windows
- OS X
- Unix (with **PulseAudio** or **ALSA** requirement)
- iOS
- Android

On all referred platforms, export templates were successfully built for Godot 3.0
with *Speech to Text*. Godot's repository can be found [here][godotRepo].

Check if your system fulfills Godot's building [requirements][compilingReq] on the
desired platform, or for cross-compiling to another system. Other than that, *Speech
to Text* has no additional requirements. It is intended to be used alongside a
microphone connected to the system, which will capture voice input.

[compilingReq]: http://docs.godotengine.org/en/3.0/development/compiling/index.html "Compiling Requirements"
[godotRepo]: https://github.com/godotengine/godot "Godot repository"


Building Godot with the module
------------------------------

The following steps assume that you are on a **Unix** system. For a different
platform supported by the module, use the equivalent tools.

1. If you don't have the source code for Godot, clone its repository from GitHub.

       $ git clone https://github.com/godotengine/godot

2. Inside the cloned repository, change to the latest stable build that the module
   works on (when these instructions were made, it was 3.0).

       $ git checkout 3.0-stable

3. Add this repository's `speech_to_text/` folder to your Godot `modules/` directory.

4. Build Godot, according to your desired platform (follow the
   [instructions][howToBuild] given on the Godot Docs).

5. Run Godot:

       $ ./bin/godot*tools*

6. In order to check if the module was successfully added, follow these final steps:

   6.1. After opening Godot, click the **New Project** button on the right side to
        open the **Create New Project** window.

   6.2. On the new window, add a **Project Path** (I'd recommend an empty directory)
        and a **Project Name** (you are free to choose as you like).

   6.3. Click **Create** to open the Godot project editor window.

   6.4. On the right side, there should be a **Scene** tab with a window below it.
        Click the first icon below the **Scene** label, which has a plus symbol `+`,
        to create a new node.

   6.5. Check if the ***STTRunner*** appears in the list of nodes; it should probably
        be near the end of the list. There is also a search bar for convenience.

[howToBuild]: http://docs.godotengine.org/en/3.0/development/compiling/index.html "How to build Godot"


Usage
-----

Check the html tutorial [here][sttTutorial], which was created on my Godot Docs
[fork][godotDocsFork], for more information on how to use the module.

[sttTutorial]: https://samuraisigma.github.io/godot-docs/doc/community/tutorials/misc/speech_to_text.html "Speech to Text module tutorial"
[godotDocsFork]: https://github.com/SamuraiSigma/godot-docs "My Godot Docs fork"


Export templates
----------------

If you wish to export a game that uses the *Speech to Text* module, you will first
need to build export templates for the desired platform.

Check the instructions and requirements on the Godot Docs [site][exportTemplates] to
learn how to build export templates for a specific system. This includes cross
compiling for opposite bits or even for a different platform.

[exportTemplates]: http://docs.godotengine.org/en/3.0/development/compiling/index.html "Building export templates"


Demo: Color Clutter
-------------------

[**Color Clutter**][colorClutterRepo] is a simple game, developed by me in Godot as
a demo for the module.

If you wish to do a quick test, follow the instructions below to run the game from
its project directory. Once again, the instructions suppose that you are on a
**Unix** system, but equivalent commands on other platforms should work.

1. Clone the game's repository.

       $ git clone https://github.com/SamuraiSigma/color-clutter

2. After building Godot, run it with the directory created in the last step as the
   `-path` argument.

       $ ./bin/godot*tools* -path <color_clutter_directory>

Instructions on how to play are in the repository's `README.md` file.

[colorClutterRepo]: https://github.com/SamuraiSigma/color-clutter "Color Clutter repository"
