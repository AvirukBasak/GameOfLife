//
// Created by aviruk on 1/4/25.
//

#ifndef GLOBALS_H
#define GLOBALS_H

class Constants final {
public:
    Constants() = delete;

    static constexpr const char *ASSETS_PATH = "../../assets";
    static constexpr const char *WINDOW_TITLE = "Rat in Maze";
    static constexpr float RENDER_FPS = 60.0f;
    static constexpr int WINDOW_WIDTH = 1200;
    static constexpr int WINDOW_HEIGHT = 840;

    static void init();
};

#endif //GLOBALS_H
