//
// Created by aviruk on 1/6/25.
//

#include "constants.h"
#include "states.h"
#include "classes/Game.h"
#include "components/Entity.h"

Game::Game(sf::RenderWindow &window) : mWindow(window),
                                       mMaze(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT),
                                       mCounterText(0) {
    for (int i = 0; i < States::entityCount; ++i) {
        mEntities.emplace_back(mMaze);
    }
}

Game::~Game() = default;

void Game::handleEvent(const sf::Event &event) {
    mMaze.handleEvent(event);
    for (auto e: mEntities) {
        e.handleEvent(event);
    }
    mCounterText.handleEvent(event);
}

void Game::update() {
    mMaze.update();
    for (auto e: mEntities) {
        e.update();
    }
    mCounterText.update();
}

void Game::render() const {
    mWindow.clear(sf::Color::Black);
    mWindow.draw(mMaze);
    for (const auto &e: mEntities) {
        mWindow.draw(e);
    }
    mWindow.draw(mCounterText);
    mWindow.display();
}
