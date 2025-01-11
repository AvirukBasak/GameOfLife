//
// Created by aviruk on 1/6/25.
//

#include "constants.h"
#include "states.h"
#include "classes/Game.h"
#include "components/Entity.h"

Game::Game(sf::RenderWindow &window) : mWindow(window),
                                       mMaze(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT),
                                       mMazeCellToolTip(mMaze),
                                       mCounterText(0) {
    for (int i = 0; i < States::entityCount; ++i) {
        mEntities.emplace_back(i, mMaze);
    }
}

Game::~Game() = default;

void Game::handleEvent(const sf::Event &event) {
    mCounterText.handleEvent(event);
    mControlPanel.handleEvent(event);
    mMaze.handleEvent(event);
    for (Entity &e: mEntities) {
        e.handleEvent(event);
    }
    mMazeCellToolTip.handleEvent(event);
}

void Game::update() {
    mCounterText.update();
    mControlPanel.update();
    mMaze.update();
    for (Entity &e: mEntities) {
        e.update();
    }
    mMazeCellToolTip.update();
}

void Game::render() const {
    mWindow.clear(sf::Color::Black);

    mWindow.draw(mCounterText);
    mWindow.draw(mControlPanel);
    mWindow.draw(mMaze);
    for (const Entity &e: mEntities) {
        mWindow.draw(e);
    }
    mWindow.draw(mMazeCellToolTip);

    mWindow.display();
}
