//
// Created by aviruk on 1/4/25.
//

#include <cassert>
#include <cstring>
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <iomanip>

#include "constants.h"
#include "utils.h"
#include "states.h"
#include "components/Maze.h"

template<typename T>
void printMatrix(const std::vector<std::vector<T> > &matrix, const std::string &name) {
    for (const std::vector<T> &row: matrix) {
        for (const T &cell: row) {
            if ("mFitnessMaze" == name) {
                if (cell == -1) {
                    std::cout << "\u2588\u2588\u2588\u2588";
                } else {
                    std::cout << std::setw(3) << cell << " ";
                }
            } else {
                if (false == cell) {
                    std::cout << "\u2588\u2588";
                } else {
                    std::cout << "  ";
                }
            }
        }
        std::cout << '\n';
    }
}

void fillFitnessMaze(const std::vector<std::vector<bool> > &mBoolMaze, std::vector<std::vector<int> > &mFitnessMaze) {
    const int size = mBoolMaze.size();
    const int destX = size - 2;
    const int destY = size - 2;

    // Define directions for up, down, left, right
    const std::vector<sf::Vector2i> directions = {
        {-1, 0},
        {+1, 0},
        {0, -1},
        {0, +1}
    };

    // BFS to calculate the shortest path distances
    std::queue<std::pair<int, int> > queue;

    /* Fill cells of mFitnessMaze coreesponding to 0 cells of mBoolMaze
     * with std::numeric_limits<int>::max() */
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (false == mBoolMaze[i][j]) {
                mFitnessMaze[i][j] = std::numeric_limits<int>::max();
            }
        }
    }

    if (true == mBoolMaze[destY][destX]) {
        queue.emplace(destX, destY);
        mFitnessMaze[destY][destX] = 0;
    } else {
        throw std::invalid_argument("Unexpected false at Maze starting cell");
    }

    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        for (const auto &[dx, dy]: directions) {
            const int nx = x + dx;
            const int ny = y + dy;

            if (nx >= 0 && nx < size &&
                ny >= 0 && ny < size &&
                true == mBoolMaze[ny][nx] &&
                mFitnessMaze[ny][nx] > mFitnessMaze[y][x] + 1
            ) {
                mFitnessMaze[ny][nx] = mFitnessMaze[y][x] + 1;
                queue.emplace(nx, ny);
            }
        }
    }

    // Fill cells that are not reachable with a specific value (e.g., -1)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (mFitnessMaze[i][j] == std::numeric_limits<int>::max()) {
                // Indicating unreachable cells
                mFitnessMaze[i][j] = -1;
            }
        }
    }

    // Print matrix
    // printMatrix(mBoolMaze, "mBoolMaze");
    // printMatrix(mFitnessMaze, "mFitnessMaze");
}

ChromosmeFriend::ChromosmeFriend()
    : mWhiteCellCount(0) {
}

EntityFriend::EntityFriend() = default;

Maze::Maze(const int width, const int height)
    : mImgLoadSize(CELLS_PER_DIMENSION),
      mImgDrawSize(std::min(width, height)),
      mBoolMaze(CELLS_PER_DIMENSION, std::vector<bool>(CELLS_PER_DIMENSION, false)),
      mInverseFitnessMaze(CELLS_PER_DIMENSION, std::vector<int>(CELLS_PER_DIMENSION, WORST_INVERSE_FITNESS)) {
    /* Tasks:
     * - Load the IMGSIZE X IMGSIZE image Black / White image
     * - Set mBoolMaze values to mean of 4 channels of the image
     * - Set the mSrcBox and mDestBox
     * - Set mWidth and mHeight
     */
    // load image from file
    mImage.loadFromFile(Utils::pathjoin({
        Constants::ASSETS_PATH, "blueprint", "maze.png"
    }));
    assert(mImage.getSize().x == Maze::CELLS_PER_DIMENSION);
    assert(mImage.getSize().y == Maze::CELLS_PER_DIMENSION);

    // load pixels as an array
    using PixelArray = sf::Uint8[CELLS_PER_DIMENSION][CELLS_PER_DIMENSION][4];
    const PixelArray &pixelArr = *reinterpret_cast<const PixelArray *>(mImage.getPixelsPtr());

    /* load the image information into mBoolMaze vector by taking mean of 4 mage channels
     * and using a threshold to set tru or false */
    for (int i = 0; i < CELLS_PER_DIMENSION; i++) {
        for (int j = 0; j < CELLS_PER_DIMENSION; j++) {
            const sf::Uint8 *pixel = pixelArr[i][j];
            float grayScale = 0.0;
            for (int k = 0; k < 4; k++) {
                grayScale += pixel[k] / 4.0f;
            }
            // If white image cell (or far enough from black in color)
            if (grayScale >= 64) {
                mBoolMaze[i][j] = true; // Mark cell as true
                mChromosmeFriend.mWhiteCellCount += 1; // Increment count of white cells by 1
                // Set mCellNumberToGeneIndexMapping for (j, i) i.e. (row, col) to the index of gene
                mChromosmeFriend.mCellNumberToGeneIndexMapping[{j, i}] =
                        mChromosmeFriend.mWhiteCellCount - 1;
            }
        }
    }

    // Ensure (1,1) and (59-1, 59-1) are true
    assert(mBoolMaze[1][1]);
    assert(mBoolMaze[CELLS_PER_DIMENSION-2][CELLS_PER_DIMENSION-2]);

    // Fill the fitness matrix
    fillFitnessMaze(mBoolMaze, mInverseFitnessMaze);

    // Set up other drawable components
    mCellFitnessTolltipText.setFont(States::defaultFont);
    mCellFitnessTolltipText.setCharacterSize(15);
    mCellFitnessTolltipText.setFillColor(sf::Color::Black);

    mCellFitnessToltipRect.setFillColor(sf::Color::Yellow);
    mCellFitnessToltipRect.setOutlineColor(sf::Color::Black);
    mCellFitnessToltipRect.setOutlineThickness(1);
    // Padding of 3 size
    mCellFitnessToltipRect.setSize({
        TOOLTIP_WIDTH + TOOLTIP_PADDING,
        TOOLTIP_HEIGHT + TOOLTIP_PADDING
    });

    mCellIndicatorRect.setFillColor(sf::Color::Transparent);
    mCellIndicatorRect.setOutlineColor(sf::Color::Red);
    mCellIndicatorRect.setOutlineThickness(1);
    // -2 adjustment to compensate for the outline in all sides
    mCellIndicatorRect.setSize({
        getCellSizeInPixels() - 2,
        getCellSizeInPixels() - 2
    });
}

Maze::~Maze() = default;

void Maze::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::MouseMoved) {
        const auto [x, y] = event.mouseMove;
        const sf::Vector2i cellNum = pixelToCellNumber(x, y);
        if (isCellNumberValid(cellNum) && mBoolMaze[cellNum.y][cellNum.x]) {
            const int fitness = getFitnessOfCellNumber(cellNum);
            const sf::Vector2f pixel = cellNumberToPixel(cellNum);
            // Compute the tooltip text
            std::stringstream ss;
            ss << "Cell: " << cellNum.x << ", " << cellNum.y << std::endl
                    << "Fitness: " << fitness << std::endl
                    << "Gene No: " << mChromosmeFriend.mCellNumberToGeneIndexMapping[{cellNum.x, cellNum.y}] <<
                    std::endl
                    << "Top Left: " << std::fixed << std::setprecision(1) << pixel.x << ", " << pixel.y << std::endl
                    << "Bottom Right: " << std::fixed << std::setprecision(1) << pixel.x + getCellSizeInPixels() << ", "
                    << pixel.y + getCellSizeInPixels() << std::endl;
            // Set component data
            mCellFitnessTolltipText.setString(ss.str());
            // Set positions and offset upwards if tooltip goes out of screen
            const float yOffset = (y + TOOLTIP_OFFSET + mCellFitnessToltipRect.getSize().y > Constants::WINDOW_HEIGHT)
                                      ? -(TOOLTIP_OFFSET + +TOOLTIP_OFFSET + mCellFitnessToltipRect.getSize().y)
                                      : 0;
            mCellFitnessToltipRect.setPosition(
                x + TOOLTIP_OFFSET,
                y + TOOLTIP_OFFSET + yOffset
            );
            mCellFitnessTolltipText.setPosition(
                x + TOOLTIP_OFFSET + TOOLTIP_PADDING,
                y + TOOLTIP_OFFSET + TOOLTIP_PADDING + yOffset
            );
            // Highlight the cell being hovered on, +1 adjustment to highlight within the cell
            mCellIndicatorRect.setPosition(pixel.x + 1, pixel.y + 1);
        } else {
            mCellFitnessTolltipText.setString("");
        }
    }
}

void Maze::update() {
}

void Maze::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    sf::Texture texture;
    texture.loadFromImage(mImage);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    const sf::Vector2f targetSize(mImgDrawSize, mImgDrawSize);
    const sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setScale({
        targetSize.x / spriteBounds.width,
        targetSize.y / spriteBounds.height
    });

    target.draw(sprite, states);

    if (mCellFitnessTolltipText.getString() != "") {
        target.draw(mCellIndicatorRect, states);
        target.draw(mCellFitnessToltipRect, states);
        target.draw(mCellFitnessTolltipText, states);
    }
}

sf::Vector2i Maze::pixelToCellNumber(const float pixelX, const float pixelY) const {
    // image size in pixels when loaded from file = mImgLoadSize
    // image size in pixels when drawn = mImgDrawSize
    // total cells per dimension of image / maze (x and y dirn) = CELLS_PER_DIMENSION
    return {
        (int) (pixelX / getCellSizeInPixels()),
        (int) (pixelY / getCellSizeInPixels())
    };
}

sf::Vector2f Maze::cellNumberToPixel(const sf::Vector2i cellNumber) const {
    return {
        cellNumber.x * getCellSizeInPixels(),
        cellNumber.y * getCellSizeInPixels()
    };
}

bool Maze::isValidMoveInPixels(const float yourSize, const float pixelX, const float pixelY, const float dx,
                               const float dy) const {
    const float newX = pixelX + dx;
    const float newY = pixelY + dy;
    const sf::Vector2i cellNumForEntityTL = pixelToCellNumber(newX, newY);
    const sf::Vector2i cellNumForEntityBR = pixelToCellNumber(newX + yourSize, newY + yourSize);
    return isCellNumberValid(cellNumForEntityTL) && true == mBoolMaze[cellNumForEntityTL.y][cellNumForEntityTL.x]
           && isCellNumberValid(cellNumForEntityBR) && true == mBoolMaze[cellNumForEntityBR.y][cellNumForEntityBR.x];
}

bool Maze::isCellNumberValid(sf::Vector2i cellNum) const {
    const auto [j, i] = cellNum;
    return i >= 0 && i < mBoolMaze.size() && j >= 0 && j < mBoolMaze[0].size();
}

int Maze::getFitnessOfCellNumber(sf::Vector2i cellNum) const {
    const auto [j, i] = cellNum;
    return WORST_INVERSE_FITNESS - mInverseFitnessMaze[i][j];
}

sf::Vector2i Maze::getSrcCellNumber() const {
    // ensure (1,1) is true
    assert(mBoolMaze[1][1]);
    return {1, 1};
}

sf::Vector2i Maze::getDestCellNumber() const {
    // ensure (59-1, 59-1) is true
    assert(mBoolMaze[CELLS_PER_DIMENSION-2][CELLS_PER_DIMENSION-2]);
    return {CELLS_PER_DIMENSION - 2, CELLS_PER_DIMENSION - 2};
}

float Maze::getCellSizeInPixels() const {
    // image size in pixels when loaded from file = mImgLoadSize
    // image size in pixels when drawn = mImgDrawSize
    // total cells per dimension of image / maze (x and y dirn) = CELLS_PER_DIMENSION
    return mImgDrawSize / CELLS_PER_DIMENSION;
}
