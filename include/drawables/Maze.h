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
    int mMazeSize;

    constexpr int mUnitMoveSize = 5;

    /**
     * Maze - 0 means blocked or wall, 1 means open or path.
     */
    std::vector<std::vector<bool> > mBoolMaze;
    sf::Image mImage;

    sf::IntRect mSrcBox;
    sf::IntRect mDestBox;

public:
    static constexpr int IMGSIZE = 60;

    enum UnitMove {
        POSITIVE,
        NEGATIVE,
    };

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
     * Returns the cell number (rw, column) in 0 indexed format given the pixel.
     * @param pixelX Pixel x coordinate
     * @param pixelY Pixel y coordinate
     * @return Location of the cell in mBoolMaze
     */
    [[nodiscard]] static sf::Vector2i pixelToCellRowCol(int pixelX, int pixelY);

    /**
     * Check if move to a new location is possible given current location and change in loaction.
     * @param currentX Current pixel x value
     * @param currentY Current pixel y value
     * @param dx Change in x direction
     * @param dy Chnage in y direction
     * @return If new location is blocked, returns false
     */
    [[nodiscard]] bool isValidMove(int currentX, int currentY, UnitMove dx, UnitMove dy) const;

    /**
     * @return - The cell bounds of starting point
     */
    [[nodiscard]] sf::IntRect getSrcCellBounds() const;

    /**
     * @return - The cell bounds of destination point
     */
    [[nodiscard]] sf::IntRect getDestCellBounds() const;
};

#endif // CLASSES_MAZE_H
