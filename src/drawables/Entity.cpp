//
// Created by aviruk on 1/4/25.
//

#include <random>

#include "states.h"
#include "drawables/Maze.h"
#include "drawables/Entity.h"

#include <iostream>

Entity::Entity(const Maze &maze)
    : mMaze(maze), mChromosome(maze) {
    mShape.setRadius(static_cast<float>(maze.getCellSizeInPixels()) / 4);
    mShape.setFillColor(sf::Color::Red);
    const auto pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        static_cast<float>(pixel.x),
        static_cast<float>(pixel.y)
    );
};

Entity::Entity(const Maze &maze, Chromosome chromosome)
    : mMaze(maze), mChromosome(std::move(chromosome)) {
    mShape.setRadius(static_cast<float>(maze.getCellSizeInPixels()) / 2);
    mShape.setFillColor(sf::Color::Red);
    const auto pixel = maze.cellNumberToPixel(maze.getSrcCellNumber());
    mShape.setPosition(
        static_cast<float>(pixel.x),
        static_cast<float>(pixel.y)
    );
}

void Entity::update() {
    const auto [oldX, oldY] = static_cast<sf::Vector2i>(mShape.getPosition());
    const auto cellNum = mMaze.pixelToCellNumber(oldX, oldY);
    const int geneticMoveInfo = mChromosome.getGeneticMoveInfoByCellNumber(cellNum);
    const auto dX = geneticMoveInfo * States::pixelMovementSpeedScaler;
    const auto dY = geneticMoveInfo * States::pixelMovementSpeedScaler;
    if (mMaze.isValidMoveInPixels(oldX, oldX, dX, dY)) {
        mShape.setPosition(static_cast<float>(oldX), static_cast<float>(oldY));
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
