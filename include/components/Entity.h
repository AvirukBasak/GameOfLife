//
// Created by aviruk on 1/4/25.
//

#ifndef CLASSES_ENTITY_H
#define CLASSES_ENTITY_H

#include "classes/Chromosome.h"
#include "interfaces/IGameComponent.h"

class Entity final : public IGameComponent {
    const int mId;
    const Maze &mMaze;

    const Chromosome mChromosome;
    sf::CircleShape mShape;
    sf::Vector2f mPosition;

    sf::Clock mEntityPosnUpdateClock;

    bool mHasStopped;

    explicit Entity(int id, const Maze &maze, Chromosome chromosome);

public:
    /**
     * Defines a single unit of move an Entity can take in the Maze.
     * The multiplier States::pixelMovementSpeedScaler is used to scale this to increase simultation speed.
     * This is in pixels and not in cells.
     */
    static constexpr int UNIT_MOVE_PIXEL_PER_SEC = 5;

    /**
     * How often update to enity position is to be done given that an
     * entity moves UNIT_MOVE_PIXEL_PER_SEC pixels in a second.
     */
    static constexpr int ENTITY_UPDATE_INTERVAL_MS = 75;

    explicit Entity(int id, const Maze &maze);

    ~Entity() override;

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::pair<Entity, Entity> reproduce(const Entity &otherEntity) const;

    void mutate();
};

#endif //CLASSES_ENTITY_H
