//
// Created by aviruk on 1/8/25.
//

#ifndef STATES_H
#define STATES_H

#include "SFML/Graphics/Font.hpp"

class States final {
public:
    States() = delete;

    static int simulationSpeedScaler;
    static float mutationProbability;
    static int entityCount;
    static sf::Font defaultFont;

    static void init();
};

#endif //STATES_H
