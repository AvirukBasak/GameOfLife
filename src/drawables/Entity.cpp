//
// Created by aviruk on 1/4/25.
//

#include "drawables/Entity.h"
#include "drawables/Maze.h"

Entity::Entity(const Maze &maze)
    : mChromosome(maze) {
};

void Entity::update() {
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}

Entity::~Entity() = default;
