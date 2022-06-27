# Building From Source

If you would like to build this project from source for whatever reasons, here are the instructions on how to do so. If these instructions do not work on your system, please open either an issue or a discussion.

## Windows

1. Ensure that you have [CMake](https://cmake.org), [Git](https://git-scm.com/), and [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com/) installed.
2. Clone this repository with the `--recursive` flag.
3. Open the repository folder in a terminal.
4. Run `cmake .`
5. Run `cmake --build .`
6. Run `./Debug/chess.exe` to play the game!

## Linux

1. Ensure that you have [CMake](https://cmake.org), [Git](https://git-scm.com/), a build system of your choice (Make and Ninja has both been tested to work, I'm not sure about other build systems), and either G++ or Clang installed. This project was developed using Clang, but it's been tested to work with G++ as well.
2. Clone this repository with the `--recursive` flag.
3. Open the repository folder in a terminal.
4. Run CMake with the flags to select your build system and compiler.
5. Run `cmake --build .`
6. Run `./chess` to play the game!

## macOS

As stated in the main README, I do not support macOS because OpenGL support is bad on macOS and I do not have a Mac to develop and test on macOS. However, if you wanted to, feel free to try and get this project running on macOS. Like before, please note that you might have to tinker with the code or the build scripts for it to work.