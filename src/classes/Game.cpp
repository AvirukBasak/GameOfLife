//
// Created by aviruk on 1/6/25.
//

#include <cmath>
#include <numeric>

#include "constants.h"
#include "states.h"
#include "classes/Game.h"
#include "components/Entity.h"

Game::Game(sf::RenderWindow &window) : mWindow(window),
                                       mMaze(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT),
                                       mMazeCellToolTip(mMaze),
                                       mCounterText(0),
                                       mPrevGeneration(States::currentGeneration) {
    for (int i = 0; i < States::populationSize; ++i) {
        mEntities.emplace_back(i, mMaze);
    }
}

Game::~Game() = default;

void Game::handleEvent(const sf::Event &event) {
    mCounterText.handleEvent(event);
    mMaze.handleEvent(event);
    for (Entity &e: mEntities) {
        e.handleEvent(event);
    }
    mMazeCellToolTip.handleEvent(event);
}

void Game::startSelectionAndReproduction() {
    // Sort entites in decreasing order of fitness
    std::sort(mEntities.begin(), mEntities.end(), [this](const Entity &e1, const Entity &e2) {
        const sf::Vector2f pos1 = e1.getPosition();
        const int fitness1 = mMaze.getFitnessOfCellNumber(mMaze.pixelToCellNumber(pos1.x, pos1.y));
        const sf::Vector2f pos2 = e2.getPosition();
        const int fitness2 = mMaze.getFitnessOfCellNumber(mMaze.pixelToCellNumber(pos2.x, pos2.y));
        return fitness1 > fitness2;
    });
    // Sum over all fitness values
    const int64_t fitnessSum = std::accumulate(
        mEntities.begin(), mEntities.end(), 0,
        [this](const int64_t lhs, const Entity &rhs) {
            const sf::Vector2f pos = rhs.getPosition();
            const int fitness = mMaze.getFitnessOfCellNumber(
                mMaze.pixelToCellNumber(pos.x, pos.y));
            return lhs + fitness;
        }
    );
    // Calculate mating counts of each entity (higher fitness = more mating count)
    // This is the no. of times an Entity can participate in reproduciton process
    // I like to call this reproductive vigour
    std::vector<int> vigourScore(mEntities.size());
    for (int i = 0; i < mEntities.size(); ++i) {
        const Entity &e = mEntities.at(i);
        const sf::Vector2f pos = e.getPosition();
        const int fitness = mMaze.getFitnessOfCellNumber(mMaze.pixelToCellNumber(pos.x, pos.y));
        const float selectionProba = (float) fitness / fitnessSum;
        const int matingCount = std::round(selectionProba * (float) mEntities.size());
        vigourScore[i] = matingCount;
    }
    // Two pointer mating selection algo (roulette wheel)
    int higherFitnessIdx = 0;
    // New vector containing new population
    std::vector<Entity> newPopulation{};
    // Higher and lower should never be equal
    // Also, the populatioon size should not exceed the States::entityCount limit
    while (higherFitnessIdx < mEntities.size() - 1 && newPopulation.size() < States::populationSize) {
        const Entity &theAlpha = mEntities.at(higherFitnessIdx);
        int lowerFitnessIdx = higherFitnessIdx + 1;
        // Mate the higherFitnessIdx with each Entity once
        // However, if higherFitnessIdx still has vigour left, we will repeat the process
        // Continue till higherFitnessIdx reaches 0 = no more vigour
        while (lowerFitnessIdx < mEntities.size()
               && vigourScore[higherFitnessIdx] > 0
               && newPopulation.size() < States::populationSize) {
            const Entity &thePartner = mEntities.at(lowerFitnessIdx);
            // Reporduce
            const auto [child1, child2] = theAlpha.mateWith(thePartner);
            newPopulation.emplace_back(child1.mId, child1.mMaze, child1.mChromosome);
            newPopulation.emplace_back(child2.mId, child2.mMaze, child2.mChromosome);
            // Reduce matingCount[higherFitnessIdx]
            --vigourScore[higherFitnessIdx];
            // Go to next mate
            ++lowerFitnessIdx;
        }
        // Consider the next alpha
        ++higherFitnessIdx;
    }
    // Set population to newPopulation
    mEntities = std::move(newPopulation);
}

void Game::update() {
    int entitiesStoppedCount = 0;
    mCounterText.update();
    mMaze.update();
    for (Entity &e: mEntities) {
        e.update();
        if (e.mHasStopped) {
            ++entitiesStoppedCount;
        }
    }
    if (entitiesStoppedCount == mEntities.size() || mPrevGeneration < States::currentGeneration) {
        // Current and prev gen number will be same if States::currentGeneration doesn't increment
        // So, the following is for when States::currentGeneration is NOT updated from outside
        if (mPrevGeneration == States::currentGeneration) {
            ++States::currentGeneration;
        }
        startSelectionAndReproduction();
        mPrevGeneration = States::currentGeneration;
    }
    mMazeCellToolTip.update();
}

void Game::render() const {
    mWindow.draw(mCounterText);
    mWindow.draw(mMaze);
    for (const Entity &e: mEntities) {
        mWindow.draw(e);
    }
    mWindow.draw(mMazeCellToolTip);
}
