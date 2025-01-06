//
// Created by aviruk on 1/4/25.
//

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <initializer_list>

inline constexpr auto ASSETS_PATH = "../../assets";
inline constexpr float RENDER_FPS = 60;
inline constexpr auto WINDOW_WIDTH = 1200;
inline constexpr auto WINDOW_HEIGHT = 840;
inline constexpr auto WINDOW_TITLE = "Rat in Maze";

std::string pathjoin(std::initializer_list<std::string> paths);

#endif //GLOBALS_H
