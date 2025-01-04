cmake_minimum_required(VERSION 3.15)
project(GameOfLife
        LANGUAGES CXX
        VERSION 1.0
)

include_directories(include)

add_subdirectory(dependencies)
add_subdirectory(src)
