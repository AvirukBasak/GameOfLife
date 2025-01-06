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
    int mImgLoadSize;
    int mImgDrawSize;

    /**
     * Maze - 0 means blocked or wall, 1 means open or path.
     */
    std::vector<std::vector<bool> > mBoolMaze;
    sf::Image mImage;

public:
    static constexpr int CELLS_PER_DIMENSION = 60;

    enum UnitMove {
        POSITIVE = +5,
        NEGATIVE = -5,
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
     * Returns the cell number (x, y) in 0 indexed format given the pixel.
     * @param pixelX Pixel x coordinate
     * @param pixelY Pixel y coordinate
     * @return - Location of the cell in mBoolMaze
     */
    [[nodiscard]] static sf::Vector2i pixelToCellNumber(int pixelX, int pixelY);

    /**
     * Check if move to a new location is possible given current location and change in loaction.
     * @param pixelX Current pixel x value
     * @param pixelY Current pixel y value
     * @param dx Change in x direction
     * @param dy Chnage in y direction
     * @return - If new location is blocked, returns false
     */
    [[nodiscard]] bool isValidMoveInPixels(int pixelX, int pixelY, UnitMove dx, UnitMove dy) const;

    /**
     * Check if (i, j) is a valid cell number.
     * @param cellNum Cell number (x, y)
     * @return - True if within bounds of mBoolMaze
     */
    [[nodiscard]] bool isCellNumberValid(sf::Vector2i cellNum) const;

    /**
     * @return - The cell number (x, y) of starting point
     */
    [[nodiscard]] sf::Vector2i getSrcCellNumber() const;

    /**
     * @return - The cell number (x, y) of destination point
     */
    [[nodiscard]] sf::Vector2i getDestCellNumber() const;

    /**
     * @return - The size (width & height) of any cell in pixels.
     */
    [[nodiscard]] float getCellSizeInPixels() const;
};

#endif // CLASSES_MAZE_H
