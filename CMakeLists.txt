cmake_minimum_required(VERSION 3.15)
project(EvoMazeSolver
        LANGUAGES CXX
        VERSION 1.0
)

include_directories(
        include
        thirdparty/include
        thirdparty/imgui/backends
)

add_executable(${PROJECT_NAME})

add_subdirectory(dependencies)
add_subdirectory(thirdparty)
add_subdirectory(src)

if (WIN32)
    set(OPENGLLIB "opengl32")
elseif (UNIX)
    find_package(OpenGL REQUIRED)
    set(OPENGLLIB ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

message(STATUS "Found OpenGL: ${OPENGLLIB}")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics ${OPENGLLIB})
