add_executable(GameeOfLife
        ../include/globals.h
        globals.cpp
        classes/maze.cpp
        classes/entity.cpp
        ../include/entity.h)

# add_subdirectory(subdir)

target_sources(GameeOfLife PUBLIC main.cpp)
target_link_libraries(GameeOfLife PRIVATE sfml-graphics)
