add_executable(GameeOfLife
        constants.cpp
        states.cpp
        utils.cpp
        classes/Chromosome.cpp
        classes/Game.cpp
        components/CounterText.cpp
        components/Entity.cpp
        components/Maze.cpp
)

# add_subdirectory(subdir)

target_sources(GameeOfLife PUBLIC main.cpp)
target_link_libraries(GameeOfLife PRIVATE sfml-graphics)
