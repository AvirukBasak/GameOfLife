//
// Created by aviruk on 1/6/25.
//

#ifndef CLASSES_COUNTERTEXT_H
#define CLASSES_COUNTERTEXT_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Drawable.hpp"

class CounterText : public sf::Drawable {
    sf::Text mText;
    sf::Font mFont;
    int mCounter;
public:
    explicit CounterText(const std::string& text);
    void incrementCount();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    ~CounterText() override;
};

#endif //CLASSES_COUNTERTEXT_H
