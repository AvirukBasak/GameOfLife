//
// Created by aviruk on 1/4/25.
//

#ifndef CLASSES_ENTITY_H
#define CLASSES_ENTITY_H

#include "classes/Chromosome.h"
#include "interfaces/IRenderable.h"

class Entity final : public IRenderable {
    Chromosome mChromosome;

public:
    /**
     * Defines a single unit of move an Entity can take in the Maze.
     * The multiplier States::pixelMovementSpeedScaler is used to scale this to increase simultation speed.
     * This is in pixels and not in cells.
     */
    enum UnitMoveInPixels {
        POSITIVE = +5,
        NEGATIVE = -5,
    };

    explicit Entity(const Maze &maze);

    ~Entity() override;

    void update() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //CLASSES_ENTITY_H
