//
// Created by aviruk on 1/4/25.
//

#include <random>
#include <iostream>

#include "states.h"
#include "components/Maze.h"
#include "components/Entity.h"

Entity::Entity(const uint64_t id, const Maze &maze)
    : mId(id), mMaze(maze), mChromosome(maze), mHasStopped(false),
      mEnd2EndSize(maze.getCellSizeInPixels() / 1.5f) {
    mShape.setOutlineThickness(OUTLINE_THICKNESS);
    mShape.setOutlineColor(sf::Color(100, 0, 0));
    mShape.setSize({mEnd2EndSize - 2 * OUTLINE_THICKNESS, mEnd2EndSize - 2 * OUTLINE_THICKNESS});
    mShape.setFillColor(sf::Color(255, 50, 100));
    const sf::Vector2f pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        pixel.x + 2 * OUTLINE_THICKNESS,
        pixel.y + 2 * OUTLINE_THICKNESS
    );
};

Entity::Entity(const uint64_t id, const Maze &maze, const Chromosome &chromosome)
    : mId(id), mMaze(maze), mChromosome(chromosome), mHasStopped(false),
      mEnd2EndSize(maze.getCellSizeInPixels() / 1.5f) {
    mShape.setOutlineThickness(OUTLINE_THICKNESS);
    mShape.setOutlineColor(sf::Color(100, 0, 0));
    mShape.setSize({mEnd2EndSize - 2 * OUTLINE_THICKNESS, mEnd2EndSize - 2 * OUTLINE_THICKNESS});
    mShape.setFillColor(sf::Color(255, 50, 100));
    const sf::Vector2f pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        pixel.x + 2 * OUTLINE_THICKNESS,
        pixel.y + 2 * OUTLINE_THICKNESS
    );
}

Entity &Entity::operator=(const Entity &other) {
    this->mChromosome = other.mChromosome;
    this->mShape = other.mShape;
    this->mEntityPosnUpdateClock = other.mEntityPosnUpdateClock;
    this->mHasStopped = other.mHasStopped;
    this->mEnd2EndSize = other.mEnd2EndSize;
    return *this;
}

void Entity::handleEvent(const sf::Event &event) {
}

void Entity::update() {
    // Update entity position every ENTITY_UPDATE_INTERVAL_MS ms
    const sf::Time enityUpdateInterval = sf::microseconds((int64_t) ENTITY_UPDATE_INTERVAL_MS * 1000.f);
    // In 1000 ms you move by UNIT_MOVE_PIXEL_PER_SEC, so we calculate move in each ENTITY_UPDATE_INTERVAL_MS ms
    const float movePerUpdateInterval = (float) UNIT_MOVE_PIXEL_PER_SEC * States::simulationSpeedScaler *
                                        (float) enityUpdateInterval.asMicroseconds() / 1e6f;
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
        if (mMaze.isValidMoveInPixels(mEnd2EndSize, oldX, oldY, dX, dY)) {
            mShape.setPosition({oldX + dX, oldY + dY});
        } else {
            mHasStopped = true;
        }
        mEntityPosnUpdateClock.restart();
    }
}

void Entity::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(mShape, states);
}

std::pair<Entity, Entity> Entity::mateWith(const Entity &otherEntity) const {
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

sf::Vector2f Entity::getPosition() const {
    return mShape.getPosition();
}

Entity::~Entity() = default;
