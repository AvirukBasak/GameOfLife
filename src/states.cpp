//
// Created by aviruk on 1/8/25.
//

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <limits>

#include "constants.h"
#include "utils.h"
#include "states.h"

#include "imgui.h"
#include "SFML/Graphics/Font.hpp"

float States::simulationSpeedScaler = 1;
float States::mutationProbability = 0.2;
int States::entityCount = 10;
std::string States::defaultFontPath{};
sf::Font States::defaultSfmlFont;
ImFont *States::defaultImguiFont = nullptr;
States::MazeCellToolTipData States::mazeCellTooltipData{};
int States::currentGeneration = 1;

void States::init() {
    defaultFontPath = Utils::pathjoin({Constants::ASSETS_PATH, "fonts", "arial.ttf"});
    if (!defaultSfmlFont.loadFromFile(defaultFontPath)) {
        throw std::runtime_error(std::string("sfml: failed to load '").append(defaultFontPath).append("'"));
    }
}

States::MazeCellToolTipData::MazeCellToolTipData() {
    mFitness = std::numeric_limits<int>::min();
}

States::MazeCellToolTipData::MazeCellToolTipData(const sf::Vector2i cell, const int fitness, const int geneNo,
                                                 const sf::Vector2f topLeft, const sf::Vector2f bottomRight)
    : mCell(cell), mFitness(fitness), mGeneNo(geneNo), mTopLeft(topLeft), mBottomRight(bottomRight) {
}

States::MazeCellToolTipData States::MazeCellToolTipData::empty() {
    MazeCellToolTipData data;
    data.mFitness = std::numeric_limits<int>::min();
    return data;
}

std::string States::MazeCellToolTipData::toString() const {
    std::stringstream ss;
    ss << "Cell: " << mCell.x << ", " << mCell.y << std::endl
            << "Fitness: " << mFitness << std::endl
            << "Gene No: " << mGeneNo << std::endl
            << "Top Left: " << std::fixed << std::setprecision(1) << mTopLeft.x << ", " << mTopLeft.y << std::endl
            << "Bottom Right: " << std::fixed << std::setprecision(1) << mBottomRight.x << ", " << mBottomRight.y <<
            std::endl;
    return ss.str();
}

bool States::MazeCellToolTipData::isEmpty() const {
    return mFitness == std::numeric_limits<int>::min();
}
