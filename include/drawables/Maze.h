//
// Created by aviruk on 1/4/25.
//

#ifndef CLASSES_MAZE_H
#define CLASSES_MAZE_H

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Rect.hpp"

class Maze final : public sf::Drawable {
public:
    static constexpr int IMGSIZE = 60;

    /**
     * Create a new random maze. A maze object guarantees a
     * path exists from source to destination.
     * Maze is always a square with size = min(width, height).
     * @param width - Width of displayed maze in window.
     * @param height - Height of displayed maze in window.
     */
    explicit Maze(int width, int height);

    ~Maze() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @return - The cell bounds of starting point
     */
    [[nodiscard]] sf::IntRect getSrcCellBounds() const;

    /**
     * @return - The cell bounds of destination point
     */
    [[nodiscard]] sf::IntRect getDestCellBounds() const;

private:
    int mMazeSize;

    /**
     * Maze - 0 means blocked or wall, 1 means open or path.
     */
    std::vector<std::vector<bool> > mBoolMaze;
    sf::Image mImage;

    sf::IntRect mSrcBox;
    sf::IntRect mDestBox;
};

#endif // CLASSES_MAZE_H
