//
// Created by aviruk on 1/6/25.
//

#include <sstream>

#include "constants.h"
#include "states.h"
#include "components/CounterText.h"

std::string mkStrFromCount(const int count) {
    std::stringstream ss;
    ss << "Elapsed Time: " << count << " second";
    if (count != 1) ss << "s";
    return ss.str();
}

CounterText::CounterText(const int initialCount) : mCounter(initialCount) {
    mText.setFont(States::defaultSfmlFont);
    mText.setCharacterSize(20);
    mText.setFillColor(sf::Color::White);
    mText.setPosition(Constants::WINDOW_HEIGHT + 20, 20);
    mText.setString(mkStrFromCount(initialCount));
}

CounterText::~CounterText() = default;

void CounterText::handleEvent(const sf::Event &event) {
}

void CounterText::update() {
    if (mClock.getElapsedTime() >= sf::milliseconds(1000)) {
        mCounter++;
        mText.setString(mkStrFromCount(mCounter));
        mClock.restart();
    }
}

void CounterText::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(mText, states);
}
