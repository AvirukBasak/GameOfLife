//
// Created by aviruk on 1/8/25.
//

#ifndef CLASSES_CHROMOSOME_H
#define CLASSES_CHROMOSOME_H

#include <vector>

#include "SFML/System/Vector2.hpp"

#include "states.h"
#include "components/Maze.h"

class Chromosome {
public:
    enum GeneticMoveInfo {
        STOP = 0, UP, DOWN, LEFT, RIGHT,
        TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT
    };

private:
    const Maze &mMaze;
    std::vector<GeneticMoveInfo> mChromoString;

public:
    explicit Chromosome(const Maze &maze);

    Chromosome &operator=(const Chromosome &other);

    /**
     * Returns the drection or move the entity should take given the location
     * i.e. the cell number (row, col) the entity is currently at in the maze.
     * @param cellNum The cell where the entity is currently.
     * @return The move the entity should take according to its genetic information.
     */
    [[nodiscard]] GeneticMoveInfo getGeneticMoveInfoByCellNumber(sf::Vector2i cellNum) const;

    /**
     * Uses random mutation strategy where each selected gene is replaced by a random
     * gene from the possible set of genes.
     * @param mutationCount Selects random genes to mutate.
     *                      If not given or exceeds chromosome length, all genes wll be mutated.
     * @return A new mutated chromosome.
     */
    void mutateRandom(int mutationCount = States::mutationCount);

    /**
     * Uses random single-point crossover strategy where a single random point is chosen
     * from either chromosome and the genetic information is exchanged. Ensures the length
     * of child chromsome remains equal to that of the parents.
     * @param other Another chromosome to crossover with.
     * @return Two new children
     */
    [[nodiscard]] std::pair<Chromosome, Chromosome> crossoverSinglePoint(const Chromosome &other) const;
};

#endif //CLASSES_CHROMOSOME_H
