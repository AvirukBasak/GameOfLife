//
// Created by aviruk on 1/4/25.
//

#include <random>

#include "states.h"
#include "components/Maze.h"
#include "components/Entity.h"

Entity::Entity(const Maze &maze)
    : mMaze(maze), mChromosome(maze) {
    mShape.setRadius(maze.getCellSizeInPixels() / 4);
    mShape.setFillColor(sf::Color::Red);
    const auto pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        pixel.x,
        pixel.y
    );
    mPosition = mShape.getPosition();
};

Entity::Entity(const Maze &maze, Chromosome chromosome)
    : mMaze(maze), mChromosome(std::move(chromosome)) {
    mShape.setRadius(maze.getCellSizeInPixels() / 2);
    mShape.setFillColor(sf::Color::Red);
    const auto pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        pixel.x,
        pixel.y
    );
    mPosition = mShape.getPosition();
}

void Entity::handleEvent(const sf::Event &event) {
}

void Entity::update() {
    // Update entity position every ENTITY_UPDATE_INTERVAL_MS ms
    const sf::Time enityUpdateInterval = sf::milliseconds(ENTITY_UPDATE_INTERVAL_MS);
    // In 1000 ms you move by UNIT_MOVE_PIXEL_PER_SEC, so we calculate move in each ENTITY_UPDATE_INTERVAL_MS ms
    constexpr float movePerUpdateInterval = UNIT_MOVE_PIXEL_PER_SEC / 1000.0f * ENTITY_UPDATE_INTERVAL_MS;
    if (mEntityPosnUpdateClock.getElapsedTime() >= enityUpdateInterval) {
        const auto [oldX, oldY] = mPosition;
        const auto cellNum = mMaze.pixelToCellNumber(oldX, oldY);
        const auto geneticMoveInfo = mChromosome.getGeneticMoveInfoByCellNumber(cellNum);
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
        }
        dX *= States::simulationSpeedScaler;
        dY *= States::simulationSpeedScaler;
        if (mMaze.isValidMoveInPixels(oldX, oldX, dX, dY)) {
            const auto newX = oldX + dX;
            const auto newY = oldY + dY;
            mPosition = {newX, newY};
            mShape.setPosition(mPosition);
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

    return {Entity(this->mMaze, chr1), Entity(this->mMaze, chr2)};
}

Entity::~Entity() = default;
