//
// Created by aviruk on 1/4/25.
//

#ifndef COMPONENTS_ENTITY_H
#define COMPONENTS_ENTITY_H

#include "constants.h"
#include "classes/Chromosome.h"
#include "interfaces/IGameComponent.h"

class Entity final : public IGameComponent {
    const int mId;
    const Maze &mMaze;

    Chromosome mChromosome;
    sf::CircleShape mShape;

    sf::Clock mEntityPosnUpdateClock;

    bool mHasStopped;
    float mDiameter;

    friend class Game;

public:
    /**
     * Defines a single unit of move an Entity can take in the Maze.
     * The multiplier States::pixelMovementSpeedScaler is used to scale this to increase simultation speed.
     * This is in pixels and not in cells.
     */
    static constexpr int UNIT_MOVE_PIXEL_PER_SEC = 20;

    /**
     * How often update to enity position is to be done given that an
     * entity moves UNIT_MOVE_PIXEL_PER_SEC pixels in a second.
     */
    static constexpr float ENTITY_UPDATE_INTERVAL_MS = 1000.f / Constants::RENDER_FPS;

    explicit Entity(int id, const Maze &maze);

    explicit Entity(int id, const Maze &maze, const Chromosome &chromosome);

    Entity &operator=(const Entity &other);

    ~Entity() override;

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::pair<Entity, Entity> mateWith(const Entity &otherEntity) const;

    sf::Vector2f getPosition() const;
};

#endif //COMPONENTS_ENTITY_H
