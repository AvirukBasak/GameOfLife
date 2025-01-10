//
// Created by aviruk on 1/4/25.
//

#ifndef CLASSES_MAZE_H
#define CLASSES_MAZE_H

#include <unordered_map>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Image.hpp"

#include "interfaces/IGameComponent.h"

template<>
struct std::hash<sf::Vector2i> {
    size_t operator()(const sf::Vector2i &sfVec2i32) const noexcept {
        // Shift x left by 32 bits and combine with y using XOR
        // This assumes x and y are 32-bit integers
        return (size_t) sfVec2i32.x << 32 |
               (size_t) sfVec2i32.y;
    }
};

class ChromosmeFriend final {
    friend class Chromosome;
    friend class Maze;

    int mWhiteCellCount;
    std::unordered_map<sf::Vector2i, int> mCellNumberToGeneIndexMapping;

public:
    ChromosmeFriend();
};

class EntityFriend final {
    friend class Maze;
    friend class Entity;

public:
    EntityFriend();
};

class Maze final : public IGameComponent {
    static constexpr int WORST_INVERSE_FITNESS = 999;
    static constexpr int TOOLTIP_OFFSET = 8;
    static constexpr int TOOLTIP_PADDING = 5;
    static constexpr int TOOLTIP_WIDTH = 184;
    static constexpr int TOOLTIP_HEIGHT = 90;

    /**
     * The size of the image when it is loaded, where each pixel corresponds to one cell.
     * Thhis value should equal CELLS_PER_DIMENSION.
     */
    float mImgLoadSize;

    /**
     * The dimensions the image should occupy when displayed in the UI.
     * This is to be equal to min(width, height) of the window.
     */
    float mImgDrawSize;

    /**
     * Maze - 0 means blocked or wall, 1 means open or path.
     */
    std::vector<std::vector<bool> > mBoolMaze;

    /**
     * The inverse fitness of a chromosome that cannot move past a cell (row, col)
     * is how far (in no. of cells) this cell is from the destination.
     * The fitness is calculated by subtracting this inverse fitness from WORST_FITNESS_INVERSE.
     */
    std::vector<std::vector<int> > mInverseFitnessMaze;

    /**
     * The image to display for the maze. This is for UI purposes.
     */
    sf::Image mImage;

    /**
     * Show a tolltip with cell fitness value on hover over the cell.
     */
    sf::Text mCellFitnessTolltipText;
    sf::RectangleShape mCellFitnessToltipRect;
    sf::RectangleShape mCellIndicatorRect;

public:
    ChromosmeFriend mChromosmeFriend;
    EntityFriend mEntityFriend;

    /**
     * Number of cells a maze should have in one dimension.
     * A maze is always a square.
     */
    static constexpr int CELLS_PER_DIMENSION = 60;

    /**
     * Create a new random maze. A maze object guarantees a
     * path exists from source to destination.
     * Maze is always a square with size = min(width, height).
     * @param width - Width of displayed maze in window.
     * @param height - Height of displayed maze in window.
     */
    explicit Maze(int width, int height);

    ~Maze() override;

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * Returns the cell number (x, y) in 0 indexed format given the pixel.
     * @param pixelX Pixel x coordinate
     * @param pixelY Pixel y coordinate
     * @return - Location of the cell in mBoolMaze
     */
    [[nodiscard]] sf::Vector2i pixelToCellNumber(float pixelX, float pixelY) const;

    [[nodiscard]] sf::Vector2f cellNumberToPixel(sf::Vector2i cellNumber) const;

    /**
     * Check if move to a new location is possible given current location and change in loaction.
     * @param pixelX Current pixel x value
     * @param pixelY Current pixel y value
     * @param dx Change in x direction in pixels
     * @param dy Chnage in y direction in pixels
     * @return - If new location is blocked, returns false
     */
    [[nodiscard]] bool isValidMoveInPixels(float pixelX, float pixelY, float dx, float dy) const;

    /**
     * Check if (i, j) is a valid cell number.
     * @param cellNum Cell number (x, y)
     * @return - True if within bounds of mBoolMaze
     */
    [[nodiscard]] bool isCellNumberValid(sf::Vector2i cellNum) const;

    /**
     * Returns a fitness value in range of [0, WORST_INVERSE_FITNESS]
     * @param cellNum  Cell number (x, y)
     * @return Fitness value of an entity that stops at cellNum. The higher the fitness value, the better.
     */
    [[nodiscard]] int getFitnessOfCellNumber(sf::Vector2i cellNum) const;

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
