add_executable(GameeOfLife
        globals.cpp
        states.cpp
        classes/Chromosome.cpp
        classes/Game.cpp
        components/CounterText.cpp
        components/Entity.cpp
        components/Maze.cpp
)

# add_subdirectory(subdir)

target_sources(GameeOfLife PUBLIC main.cpp)
target_link_libraries(GameeOfLife PRIVATE sfml-graphics)
