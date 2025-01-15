file(GLOB IMGUI_SRC
        imgui/*.cpp
        imgui/*.c
)

file(GLOB IMGUI_SFML_SRC
        imgui-sfml/*.cpp
        imgui-sfml/*.c
)

file(GLOB IMGUI_BACKENDS
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3.h
)

target_sources(${PROJECT_NAME}
        PUBLIC
        ${IMGUI_SRC}
        ${IMGUI_SFML_SRC}
        ${IMGUI_BACKENDS}
)
