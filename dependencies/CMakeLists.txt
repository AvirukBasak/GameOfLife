include(FetchContent)

# SFML v2.6.0
FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 11b73743c42cf7ecd7c596ba83fdbf1150ffa96c # 2.6.0
)

add_subdirectory(sfml)

## ImGui v1.9.6
#FetchContent_Declare(
#        imgui
#        GIT_REPOSITORY https://github.com/ocornut/imgui
#        GIT_TAG 993fa347495860ed44b83574254ef2a317d0c14f # 1.9.6
#)
#
#FetchContent_MakeAvailable(imgui)
#
## ImGui-SFML v2.6
#FetchContent_Declare(
#        imgui-sfml
#        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
#        GIT_TAG de565ac8f2b795dedc0307b60830cb006afd2ecd # v2.6
#)
#add_subdirectory(imgui-sfml)
