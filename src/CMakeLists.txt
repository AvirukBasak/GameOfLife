add_executable(GameeOfLife)

# add_subdirectory(subdir)

target_sources(GameeOfLife PUBLIC main.cpp)
target_link_libraries(GameeOfLife PRIVATE sfml-graphics)
