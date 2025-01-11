//
// Created by aviruk on 1/8/25.
//

#ifndef INTERFACES_IGAMECOMPONENT_H
#define INTERFACES_IGAMECOMPONENT_H

#include <SFML/Graphics.hpp>

class IGameComponent : public sf::Drawable {
public:
    ~IGameComponent() override = default;

    /**
     * Receives an event from Game class.
     * All IGameComponent components receive every event.
     * @param event An event that needs to be handled.
     */
    virtual void handleEvent(const sf::Event &event) = 0;

    /**
     * Runs on every iteration of game loop
     */
    virtual void update() = 0;

    /**
     * Runs only RENDER_FPS times in each second
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif //INTERFACES_IGAMECOMPONENT_H
