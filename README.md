# Genetic Algo Based Maze Solver

Idea taken from this video https://www.youtube.com/watch?v=XP2sFzp2Rig by [argonaut](https://www.youtube.com/@argonautcode).

Developed in C++ with `SFML v2.6.0`.

## Setting Up
This project was developed and tested on Linux (Ubuntu 24.04) so the following guide is based on the same.

You need to build this project with `CMake` with GCC as the compiler (had issues with Clang).
Ideally, you'll want CLion as an IDE but is not important.
You may be asked at every step to install a few libraries which you can with your distro package manager if possible.
If you are having dependency issues, or do not have said library versions in the distro package registry, change the SFML version at `dependencies/CMakeLists.txt` and see if it helps.

If you are not able to setup still, delete `dependecies/` and remove the line `add_subdirectory(dependencies)` from `/CMakeLists.txt`. Install SFML using your package manager and see if the project compiles.
If you are using an older (or newer) version of SFML, you may need to change the source code of this project to fit with the API.

## Screenshots
### Window
![Screenshot from 2025-01-10 00-46-34](https://github.com/user-attachments/assets/699e246c-513f-4c89-8818-ee735f4d0085)

### Fitness Function
![Screenshot from 2025-01-10 00-48-04](https://github.com/user-attachments/assets/6f732ffe-f17d-479f-8b2c-54262f17c103)
