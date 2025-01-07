//
// Created by aviruk on 1/8/25.
//

#include "classes/Chromosome.h"

#include <random>
#include <algorithm>

// Random number generation setup (see https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution)
static std::random_device rd;
static std::mt19937 gen(rd());

Chromosome::Chromosome(const std::shared_ptr<Maze> &mazePtr)
    : mMazePtr(mazePtr), mChromoString(mazePtr->mChromosmeFriend.mWhiteCellCount) {
    // Initialize with random moves (8 possible moves)
    std::uniform_int_distribution<> distrib(0, 7);

    for (auto &gene: mChromoString) {
        gene = static_cast<GeneticMoveInfo>(distrib(gen));
    }
}

Chromosome::GeneticMoveInfo Chromosome::getGeneticMoveInfoByCellNumber(const sf::Vector2i cellNum) const {
    const auto geneLocation = mMazePtr->mChromosmeFriend.mCellNumberToGeneIndexMapping[cellNum];
    return mChromoString[geneLocation];
}

Chromosome Chromosome::mutateRandom(int mutationCount) const {
    // Create a copy of current chromosome
    Chromosome mutated = *this;

    // If mutationCount is 0 or exceeds chromosome length, mutate all genes
    if (mutationCount <= 0 || mutationCount > mChromoString.size()) {
        mutationCount = static_cast<int>(mChromoString.size());
    }

    // Create a uniform distribution for selecting random moves
    std::uniform_int_distribution<> moveDistrib(0, 7);

    // Create a uniform distribution for selecting gene positions
    std::uniform_int_distribution<> positionDistrib(0, static_cast<int>(mChromoString.size()) - 1);

    // Perform random mutations
    for (int i = 0; i < mutationCount; ++i) {
        // Select a random position to mutate
        const int position = positionDistrib(gen);
        // Generate a new random move
        const auto newMove = static_cast<GeneticMoveInfo>(moveDistrib(gen));
        // Apply mutation
        mutated.mChromoString[position] = newMove;
    }

    return mutated;
}

Chromosome Chromosome::crossoverSinglePoint(const Chromosome &other) const {
    Chromosome child(this->mMazePtr);

    // Ensure child has same size as parents
    child.mChromoString.resize(mChromoString.size());

    // Select random crossover point
    std::uniform_int_distribution<> distrib(0, static_cast<int>(mChromoString.size()) - 1);
    const int crossoverPoint = distrib(gen);

    // Copy genes from first parent up to crossover point
    std::copy(mChromoString.begin(),
              mChromoString.begin() + crossoverPoint,
              child.mChromoString.begin());

    // Copy genes from second parent after crossover point
    std::copy(other.mChromoString.begin() + crossoverPoint,
              other.mChromoString.end(),
              child.mChromoString.begin() + crossoverPoint);

    return child;
}
