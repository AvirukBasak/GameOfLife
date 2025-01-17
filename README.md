# Evolutionary Maze Solver

Idea taken from this video https://www.youtube.com/watch?v=XP2sFzp2Rig by [argonaut](https://www.youtube.com/@argonautcode).

Developed in C++ with `SFML v2.6.0`, `Dear ImGui v1.90.6` and `ImGui-SFML v2.6`.

## Setting Up
This project was developed and tested on Linux (Ubuntu 24.04) so the following guide is based on the same.

You need to build this project with `CMake` with GCC as the compiler (had issues with Clang).
Ideally, you'll want CLion as an IDE but is not important.
You may be asked at every step to install a few libraries which you can with your distro package manager if possible.
If you are having dependency issues, or do not have said library versions in the distro package registry, change the SFML version at `dependencies/CMakeLists.txt` and see if it helps.

If you are not able to setup still, delete `dependencies/` and remove the line `add_subdirectory(dependencies)` from `/CMakeLists.txt`. Install SFML using your package manager and see if the project compiles.
If you are using an older (or newer) version of SFML, you may need to change the source code of this project to fit with the API.

ImGui font support and NewFrame functions are platform dependent and you'll need to call ImGui_ImplXXXX_NewFrame() depending on your platform. OpenGL3 will probably work for most.

Therefore depending on your platform, you'll need to call the functions accordingly. See [`thirdparty/imgui/backends`](thirdparty/imgui/backends) for platform specific sources.

### Build

#### Linux
```bash
cd $project_dir
mkdir build
cd build
cmake ..
make
```

#### Windows
On Windows use the following to build:
- [`GNU Make`](https://gnuwin32.sourceforge.net/packages/make.htm) For CMake
- [`CMake`](https://cmake.org/download/) Can be downloaded via `winget`
- [`MinGW MSVCRT`](https://github.com/niXman/mingw-builds-binaries/releases) Get the x86_64 Win32 SEH MSVCRT archive.

Download any archives, extract them and set path to the binaries accordingly. After which do the following.

```bash
cd $project_dir
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make
```

## Screenshots
### Window

[DemoVideo.webm](https://github.com/user-attachments/assets/cf8a842d-814b-4241-a761-abc490025fcf)


### Fitness Function
![Screenshot from 2025-01-10 00-48-04](https://github.com/user-attachments/assets/6f732ffe-f17d-479f-8b2c-54262f17c103)
