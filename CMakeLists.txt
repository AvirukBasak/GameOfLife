cmake_minimum_required(VERSION 3.15)
project(EvoMazeSolver
        LANGUAGES CXX
        VERSION 1.0
)

include_directories(
        include
        thirdparty/include
)

add_executable(${PROJECT_NAME})

add_subdirectory(dependencies)
add_subdirectory(thirdparty)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics GL)
