//
// Created by aviruk on 1/6/25.
//

#ifndef CLASSES_COUNTERTEXT_H
#define CLASSES_COUNTERTEXT_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Drawable.hpp"

#include "interfaces/IRenderable.h"

class CounterText final : public IRenderable {
    sf::Text mText;
    sf::Font mFont;
    sf::Clock mClock;
    int mCounter;

public:
    explicit CounterText(int initialCount = 0);

    ~CounterText() override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //CLASSES_COUNTERTEXT_H
