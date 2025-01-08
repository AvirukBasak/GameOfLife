//
// Created by aviruk on 1/4/25.
//

#ifndef CLASSES_ENTITY_H
#define CLASSES_ENTITY_H

#include "classes/Chromosome.h"
#include "interfaces/IRenderable.h"

class Entity final : public IRenderable {
    const Maze &mMaze;

    const Chromosome mChromosome;
    sf::CircleShape mShape;

    explicit Entity(const Maze &maze, Chromosome chromosome);

public:
    /**
     * Defines a single unit of move an Entity can take in the Maze.
     * The multiplier States::pixelMovementSpeedScaler is used to scale this to increase simultation speed.
     * This is in pixels and not in cells.
     */
    enum UnitMoveInPixels {
        POSITIVE = +1,
        NEGATIVE = -1,
    };

    explicit Entity(const Maze &maze);

    ~Entity() override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::pair<Entity, Entity> reproduce(const Entity &otherEntity) const;

    void mutate();
};

#endif //CLASSES_ENTITY_H
