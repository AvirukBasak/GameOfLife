//
// Created by aviruk on 1/6/25.
//

#include <sstream>

#include "globals.h"
#include "drawables/CounterText.h"

CounterText::CounterText(const std::string& text) : mCounter(0) {
    if (!mFont.loadFromFile(pathjoin({ASSETS_PATH, "fonts", "arial.ttf"}))) {
        throw std::runtime_error("Failed to load font");
    }
    mText.setFont(mFont);
    mText.setCharacterSize(20);
    mText.setFillColor(sf::Color::White);
    mText.setPosition(WINDOW_HEIGHT + 20, 20);
    mText.setString(text);
}

void CounterText::incrementCount() {
    mCounter++;
    std::stringstream ss;
    ss << "Elapsed Seconds: " << mCounter;
    mText.setString(ss.str());
}

void CounterText::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(mText, states);
}

CounterText::~CounterText() = default;
