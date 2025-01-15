file(GLOB_RECURSE SOURCE_FILES *.cpp)

target_sources(${PROJECT_NAME}
        PUBLIC
        ${SOURCE_FILES}
)

# Add subdirectory if needed
# add_subdirectory(subdir)
