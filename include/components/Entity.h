//
// Created by aviruk on 1/4/25.
//

#ifndef COMPONENTS_ENTITY_H
#define COMPONENTS_ENTITY_H

#include "constants.h"
#include "classes/Chromosome.h"
#include "interfaces/IGameComponent.h"

class Entity final : public IGameComponent {
    const uint64_t mId;
    const Maze &mMaze;

    Chromosome mChromosome;
    sf::RectangleShape mShape;

    sf::Clock mEntityPosnUpdateClock;

    bool mHasStopped;
    float mEnd2EndSize;

    friend class Game;

    static constexpr float OUTLINE_THICKNESS = 1.f;

public:
    /**
     * Defines a single unit of move an Entity can take in the Maze.
     * This is in pixels and not in cells.
     */
    static constexpr float UNIT_MOVE_IN_PIXELS = 0.125f;

    /**
     * How often update to enity position is to be done. To be divided by States::simulationSpeedScaler
     * to increase simulation speed by scaling down update interval.
     */
    static constexpr float ENTITY_UPDATE_INTERVAL_SEC = 1 / Constants::RENDER_FPS;

    explicit Entity(uint64_t id, const Maze &maze);

    explicit Entity(uint64_t id, const Maze &maze, const Chromosome &chromosome);

    Entity &operator=(const Entity &other);

    ~Entity() override;

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::pair<Entity, Entity> mateWith(const Entity &otherEntity) const;

    sf::Vector2f getPosition() const;
};

#endif //COMPONENTS_ENTITY_H
