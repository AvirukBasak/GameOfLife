//
// Created by aviruk on 1/8/25.
//

#ifndef INTERFACES_IDRAWABLE_H
#define INTERFACES_IDRAWABLE_H

#include <SFML/Graphics.hpp>

class IRenderable : public sf::Drawable {
public:
    ~IRenderable() override = default;

    /**
     * Runs on every iteration of game loop
     */
    virtual void update() = 0;

    /**
     * Runs only RENDER_FPS times in each second
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif //INTERFACES_IDRAWABLE_H
