//
// Created by aviruk on 1/6/25.
//

#ifndef CLASSES_GAME_H
#define CLASSES_GAME_H

#include "SFML/Graphics.hpp"

#include "drawables/CounterText.h"
#include "drawables/Maze.h"

class Game {
    sf::RenderWindow &mWindow;

    CounterText mCounterText;
    Maze mMaze;

    sf::Clock mCounterClock;

public:
    explicit Game(sf::RenderWindow &window);

    ~Game();

    /**
     * Runs on every iteration of game loop
     */
    void update();

    /**
     * Runs 1/FPS times per second in game loop.
     */
    void render() const;
};

#endif // CLASSES_GAME_H
