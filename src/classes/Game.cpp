//
// Created by aviruk on 1/6/25.
//

#include "globals.h"
#include "classes/Game.h"

Game::Game(sf::RenderWindow &window) : mWindow(window),
                                       mCounterText("Loading Counter..."),
                                       mMaze(WINDOW_WIDTH, WINDOW_HEIGHT) {
}

Game::~Game() = default;

void Game::update() {
    if (mCounterClock.getElapsedTime() >= sf::milliseconds(1000)) {
        mCounterText.incrementCount();
        mCounterClock.restart();
    }
}

void Game::render() const {
    mWindow.clear(sf::Color::Black);
    mWindow.draw(mMaze);
    mWindow.draw(mCounterText);
    mWindow.display();
}
