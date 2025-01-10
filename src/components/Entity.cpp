//
// Created by aviruk on 1/4/25.
//

#include <random>
#include <iostream>

#include "states.h"
#include "components/Maze.h"
#include "components/Entity.h"

Entity::Entity(const int id, const Maze &maze)
    : mId(id), mMaze(maze), mChromosome(maze), mHasStopped(false),
      mDiameter(maze.getCellSizeInPixels() / 2) {
    mShape.setRadius(mDiameter / 2);
    mShape.setFillColor(sf::Color::Red);
    const sf::Vector2f pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        pixel.x,
        pixel.y
    );
};

Entity::Entity(const int id, const Maze &maze, Chromosome chromosome)
    : mId(id), mMaze(maze), mChromosome(std::move(chromosome)), mHasStopped(false),
      mDiameter(maze.getCellSizeInPixels() / 2) {
    mShape.setRadius(mDiameter / 2);
    mShape.setFillColor(sf::Color::Red);
    const sf::Vector2f pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        pixel.x,
        pixel.y
    );
}

void Entity::handleEvent(const sf::Event &event) {
}

void Entity::update() {
    // Update entity position every ENTITY_UPDATE_INTERVAL_MS ms
    const sf::Time enityUpdateInterval = sf::milliseconds(ENTITY_UPDATE_INTERVAL_MS);
    // In 1000 ms you move by UNIT_MOVE_PIXEL_PER_SEC, so we calculate move in each ENTITY_UPDATE_INTERVAL_MS ms
    constexpr float movePerUpdateInterval = UNIT_MOVE_PIXEL_PER_SEC / 1000.0f * ENTITY_UPDATE_INTERVAL_MS;
    if (mEntityPosnUpdateClock.getElapsedTime() >= enityUpdateInterval) {
        const auto [oldX, oldY] = mShape.getPosition();
        const sf::Vector2i cellNum = mMaze.pixelToCellNumber(oldX, oldY);
        const Chromosome::GeneticMoveInfo geneticMoveInfo = mChromosome.getGeneticMoveInfoByCellNumber(cellNum);
        float dX = 0, dY = 0;
        switch (geneticMoveInfo) {
            case Chromosome::UP:
                dY = -movePerUpdateInterval;
                break;
            case Chromosome::DOWN:
                dY = +movePerUpdateInterval;
                break;
            case Chromosome::LEFT:
                dX = -movePerUpdateInterval;
                break;
            case Chromosome::RIGHT:
                dX = +movePerUpdateInterval;
                break;
            case Chromosome::TOPLEFT:
                dY = -movePerUpdateInterval;
                dX = -movePerUpdateInterval;
                break;
            case Chromosome::TOPRIGHT:
                dY = -movePerUpdateInterval;
                dX = +movePerUpdateInterval;
                break;
            case Chromosome::BOTTOMLEFT:
                dY = +movePerUpdateInterval;
                dX = -movePerUpdateInterval;
                break;
            case Chromosome::BOTTOMRIGHT:
                dY = +movePerUpdateInterval;
                dX = +movePerUpdateInterval;
                break;
            case Chromosome::STOP:
                if (!mHasStopped) {
                    std::cerr << "Stopped Entity[" << mId << "] at position: ["
                            << oldX << ", " << oldY << "]" << std::endl;
                    mHasStopped = true;
                }
                break;
        }
        dX *= States::simulationSpeedScaler;
        dY *= States::simulationSpeedScaler;
        if (mMaze.isValidMoveInPixels(mDiameter, oldX, oldY, dX, dY)) {
            mShape.setPosition({oldX + dX, oldY + dY});
        }
        mEntityPosnUpdateClock.restart();
    }
}

void Entity::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(mShape, states);
}

std::pair<Entity, Entity> Entity::reproduce(const Entity &otherEntity) const {
    auto [chr1, chr2] = this->mChromosome.crossoverSinglePoint(otherEntity.mChromosome);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0, 1);

    if (dis(gen) < States::mutationProbability) {
        // chance in [0,1] for mutation in chromosome 1
        chr1.mutateRandom();
    }

    if (dis(gen) < States::mutationProbability) {
        // chance in [0,1] for mutation in chromosome 2
        chr2.mutateRandom();
    }

    return {
        Entity(this->mId, this->mMaze, chr1),
        Entity(otherEntity.mId, this->mMaze, chr2)
    };
}

Entity::~Entity() = default;
