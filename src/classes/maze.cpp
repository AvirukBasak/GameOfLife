//
// Created by aviruk on 1/4/25.
//

#include "maze.h"

CellBox Maze::get_src() {
    return this->srcbox;
}

CellBox Maze::get_dest() {
    return this->destbox;
}

void Maze::generate_maze(const int width, const int height) {
    this->maze = {
    };
}

Maze::Maze(const int width, const int height) {

}

Maze::~Maze() {

}
