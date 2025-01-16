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
    // Update entity position according to interval
    const sf::Time enityUpdateInterval = sf::seconds(
        States::simulationSpeedScaler == 0
            ? std::numeric_limits<float>::infinity()
            : ENTITY_UPDATE_INTERVAL_SEC / States::simulationSpeedScaler
    );
    // No updates if sim speed scaler is 0
    if (States::simulationSpeedScaler != 0 && mEntityPosnUpdateClock.getElapsedTime() >= enityUpdateInterval) {
        const auto [oldX, oldY] = mShape.getPosition();
        const sf::Vector2i cellNum = mMaze.pixelToCellNumber(oldX, oldY);
        const Chromosome::GeneticMoveInfo geneticMoveInfo = mChromosome.getGeneticMoveInfoByCellNumber(cellNum);
        float dX = 0, dY = 0;
        switch (geneticMoveInfo) {
            case Chromosome::UP:
                dY = -UNIT_MOVE_IN_PIXELS;
                break;
            case Chromosome::DOWN:
                dY = +UNIT_MOVE_IN_PIXELS;
                break;
            case Chromosome::LEFT:
                dX = -UNIT_MOVE_IN_PIXELS;
                break;
            case Chromosome::RIGHT:
                dX = +UNIT_MOVE_IN_PIXELS;
                break;
            case Chromosome::TOPLEFT:
                dY = -UNIT_MOVE_IN_PIXELS;
                dX = -UNIT_MOVE_IN_PIXELS;
                break;
            case Chromosome::TOPRIGHT:
                dY = -UNIT_MOVE_IN_PIXELS;
                dX = +UNIT_MOVE_IN_PIXELS;
                break;
            case Chromosome::BOTTOMLEFT:
                dY = +UNIT_MOVE_IN_PIXELS;
                dX = -UNIT_MOVE_IN_PIXELS;
                break;
            case Chromosome::BOTTOMRIGHT:
                dY = +UNIT_MOVE_IN_PIXELS;
                dX = +UNIT_MOVE_IN_PIXELS;
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
