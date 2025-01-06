add_executable(GameeOfLife
        globals.cpp
        drawables/Maze.cpp
        classes/Entity.cpp
        classes/Game.cpp
        drawables/CounterText.cpp
        ../include/drawables/CounterText.h
)

# add_subdirectory(subdir)

target_sources(GameeOfLife PUBLIC main.cpp)
target_link_libraries(GameeOfLife PRIVATE sfml-graphics)
