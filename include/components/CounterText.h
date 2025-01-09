//
// Created by aviruk on 1/6/25.
//

#ifndef CLASSES_COUNTERTEXT_H
#define CLASSES_COUNTERTEXT_H

#include <SFML/Graphics.hpp>
#include "interfaces/IGameComponent.h"

class CounterText final : public IGameComponent {
    sf::Text mText;
    sf::Clock mClock;
    int mCounter;

public:
    explicit CounterText(int initialCount = 0);

    ~CounterText() override;

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //CLASSES_COUNTERTEXT_H
