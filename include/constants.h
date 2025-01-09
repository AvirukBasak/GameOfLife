//
// Created by aviruk on 1/4/25.
//

#ifndef GLOBALS_H
#define GLOBALS_H

class Constants final {
public:
    Constants() = delete;

    static constexpr auto ASSETS_PATH = "../../assets";
    static constexpr float RENDER_FPS = 60;
    static constexpr auto WINDOW_WIDTH = 1200;
    static constexpr auto WINDOW_HEIGHT = 840;
    static constexpr auto WINDOW_TITLE = "Rat in Maze";

    static void init();
};

#endif //GLOBALS_H
