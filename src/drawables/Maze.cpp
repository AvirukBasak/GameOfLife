//
// Created by aviruk on 1/4/25.
//

#include <cassert>
#include <cstring>

#include "globals.h"
#include "drawables/Maze.h"

Maze::Maze(const int width, const int height)
    : mImgLoadSize(CELLS_PER_DIMENSION),
      mImgDrawSize(std::min(width, height)),
      mBoolMaze(CELLS_PER_DIMENSION, std::vector<bool>(CELLS_PER_DIMENSION, false)) {
    /* Tasks:
     * - Load the IMGSIZE X IMGSIZE image Black / White image
     * - Set mBoolMaze values to mean of 4 channels of the image
     * - Set the mSrcBox and mDestBox
     * - Set mWidth and mHeight
     */
    // load image from file
    mImage.loadFromFile(pathjoin({
        ASSETS_PATH, "blueprint", "maze.png"
    }));
    assert(mImage.getSize().x == Maze::CELLS_PER_DIMENSION);
    assert(mImage.getSize().y == Maze::CELLS_PER_DIMENSION);

    // load pixels into array or size
    sf::Uint8 pixelArr[CELLS_PER_DIMENSION][CELLS_PER_DIMENSION][4];
    std::memcpy(pixelArr, mImage.getPixelsPtr(), sizeof(pixelArr));
    assert(pixelArr);

    /* load the image information into mBoolMaze vector by taking mean of 4 mage channels
     * and using a threshold to set tru or false */
    for (int i = 0; i < CELLS_PER_DIMENSION; i++) {
        for (int j = 0; j < CELLS_PER_DIMENSION; j++) {
            const sf::Uint8 *pixel = pixelArr[i][j];
            float grayScale = 0.0;
            for (int k = 0; k < 4; k++) {
                grayScale += static_cast<float>(pixel[k]) / 4;
            }
            /* Grayscale by mean for only R, G or B and 0 alpha
             * comes at around 63.27 and 0x41 is 65. So 0x41 - 2
             * i.e. 0x3F is 63, which is just below 63.75.
             * The reason for doing this is coz there are 2 cells in
             * the actual image that have markings in primary color
             * Rather than pure black or white, and they should be
             * interpreted as white. */
            mBoolMaze[i][j] = grayScale >= 0x3F;
        }
    }

    // ensure (1,1) and (59-1, 59-1) are true
    assert(mBoolMaze[1][1]);
    assert(mBoolMaze[CELLS_PER_DIMENSION-2][CELLS_PER_DIMENSION-2]);
}

Maze::~Maze() = default;

void Maze::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    sf::Texture texture;
    texture.loadFromImage(mImage);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    const sf::Vector2f targetSize(static_cast<float>(mImgDrawSize), static_cast<float>(mImgDrawSize));
    const auto spriteBounds = sprite.getLocalBounds();
    sprite.setScale(sf::Vector2f(targetSize.x / spriteBounds.width, targetSize.y / spriteBounds.height));

    target.draw(sprite, states);
}

sf::Vector2i Maze::pixelToCellNumber(const int pixelX, const int pixelY) {
    // image size in pixels when loaded from file = mImgLoadSize
    // image size in pixels when drawn = mImgDrawSize
    // total cells per dimension of image / maze (x and y dirn) = CELLS_PER_DIMENSION
    return {pixelX / CELLS_PER_DIMENSION, pixelY / CELLS_PER_DIMENSION};
}

bool Maze::isValidMoveInPixels(int pixelX, int pixelY, const UnitMove dx, const UnitMove dy) const {
    const int newX = pixelX + dx;
    const int newY = pixelY + dy;
    const auto cellNum = pixelToCellNumber(newX, newY);
    return isCellNumberValid(cellNum) && true == mBoolMaze[cellNum.y][cellNum.x];
}

bool Maze::isCellNumberValid(sf::Vector2i cellNum) const {
    const auto [j, i] = cellNum;
    return i >= 0 && i < mBoolMaze.size() && j >= 0 && j < mBoolMaze[0].size();
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
    return static_cast<float>(mImgDrawSize) / CELLS_PER_DIMENSION;
}
