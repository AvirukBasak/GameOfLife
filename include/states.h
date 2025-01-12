//
// Created by aviruk on 1/8/25.
//

#ifndef STATES_H
#define STATES_H

#include "imgui.h"
#include "SFML/Graphics/Font.hpp"

class States final {
public:
    class MazeCellToolTipData final {
    public:
        sf::Vector2i mCell;
        int mFitness{};
        int mGeneNo{};
        sf::Vector2f mTopLeft;
        sf::Vector2f mBottomRight;

        MazeCellToolTipData();
        MazeCellToolTipData(sf::Vector2i cell, int fitness, int geneNo, sf::Vector2f topLeft, sf::Vector2f bottomRight);

        static MazeCellToolTipData empty();

        [[nodiscard]] std::string toString() const;
        [[nodiscard]] bool isEmpty() const;
    };

    States() = delete;

    static float simulationSpeedScaler;
    static float mutationProbability;
    static int populationSize;
    static std::string defaultFontPath;
    static sf::Font defaultSfmlFont;
    static ImFont *defaultImguiFont;
    static MazeCellToolTipData mazeCellTooltipData;
    static int mutationCount;
    static int maxMutationCount;
    static int highestFitnessThisGen;
    static int highestOverallFitness;
    static int currentGeneration;

    static void init();
};

#endif //STATES_H
