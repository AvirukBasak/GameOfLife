add_executable(GameeOfLife
        globals.cpp
        states.cpp
        classes/Chromosome.cpp
        classes/Game.cpp
        drawables/CounterText.cpp
        drawables/Entity.cpp
        drawables/Maze.cpp
)

# add_subdirectory(subdir)

target_sources(GameeOfLife PUBLIC main.cpp)
target_link_libraries(GameeOfLife PRIVATE sfml-graphics)
