add_executable(GameeOfLife
        globals.cpp
        classes/Game.cpp
        classes/Entity.cpp
        drawables/Maze.cpp
        drawables/CounterText.cpp
)

# add_subdirectory(subdir)

target_sources(GameeOfLife PUBLIC main.cpp)
target_link_libraries(GameeOfLife PRIVATE sfml-graphics)
