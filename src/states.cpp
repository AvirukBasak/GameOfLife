//
// Created by aviruk on 1/8/25.
//

#include <stdexcept>

#include "constants.h"
#include "utils.h"
#include "states.h"

#include "SFML/Graphics/Font.hpp"

int States::simulationSpeedScaler = 1;
float States::mutationProbability = 0.5;
int States::entityCount = 10;
sf::Font States::defaultFont;

void States::init() {
    const auto fontpath = Utils::pathjoin({Constants::ASSETS_PATH, "fonts", "arial.ttf"});
    if (!defaultFont.loadFromFile(fontpath)) {
        throw std::runtime_error(std::string("Failed to load '").append(fontpath).append("'"));
    }
}
