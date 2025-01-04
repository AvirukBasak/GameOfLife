//
// Created by aviruk on 1/4/25.
//

#ifndef MAZE_H
#define MAZE_H

#include <vector>

struct CellBox {
    int tl;
    int tr;
    int bl;
    int br;
};

class Maze {
    /**
     * Maze - 0 means blocked or wall, 1 means open or path.
     */
    std::vector<std::vector<bool>> maze;

    CellBox srcbox;
    CellBox destbox;

    /**
     * Genrate a maze from the given width and height and set the CellBox.
     * @param width - The width within which the maze is to be fit
     * @param height - The height within which the maze is to be fit
     */
    void generate_maze(const int width, const int height);
public:
    /**
     * Create a new random maze. A maze object guarantees a
     * path exists from source to destination.
     * @param width - The width within which the maze is to be fit
     * @param height - The height within which the maze is to be fit
     */
    explicit Maze(const int width, const int height);

    /**
     * @return - The cell bounds from where to start
     */
    CellBox get_src();

    /**
     * @return - The cell bounds to reach
     */
    CellBox get_dest();

    ~Maze();
};

#endif
