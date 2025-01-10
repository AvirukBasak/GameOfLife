add_executable(${PROJECT_NAME}
        constants.cpp
        states.cpp
        utils.cpp
        classes/Chromosome.cpp
        classes/Game.cpp
        components/CounterText.cpp
        components/Entity.cpp
        components/Maze.cpp
        components/ControlPanel.cpp
)

# add_subdirectory(subdir)

target_sources(${PROJECT_NAME} PUBLIC main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
