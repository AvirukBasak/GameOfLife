//
// Created by aviruk on 1/4/25.
//

#include <cassert>
#include <cstring>

#include "globals.h"
#include "drawables/Maze.h"

sf::IntRect Maze::getSrcCellBounds() const {
    return mSrcBox;
}

sf::IntRect Maze::getDestCellBounds() const {
    return mDestBox;
}

sf::Uint8 toGrayScale(const sf::Uint8 r, const sf::Uint8 g, const sf::Uint8 b, const sf::Uint8 a) {
    return (r + g + b + a) / 4;
}

Maze::Maze(const int width, const int height)
    : mMazeSize(std::min(width, height)),
      mBoolMaze(IMGSIZE, std::vector<bool>(IMGSIZE, false)) {
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
    assert(mImage.getSize().x == Maze::IMGSIZE);
    assert(mImage.getSize().y == Maze::IMGSIZE);

    // load pixels into array or size
    sf::Uint8 pixelArr[IMGSIZE][IMGSIZE][4];
    std::memcpy(pixelArr, mImage.getPixelsPtr(), sizeof(pixelArr));
    assert(pixelArr);

    /* load the image information into mBoolMaze vector by taking mean of 4 mage channels
     * and using a threshold to set tru or false */
    for (int i = 0; i < IMGSIZE; i++) {
        for (int j = 0; j < IMGSIZE; j++) {
            const sf::Uint8 *pixel = pixelArr[i][j];
            float grayScale = 0.0;
            for (int k = 0; k < 4; k++) {
                grayScale += static_cast<float>(pixel[k]) / 4;
            }
            mBoolMaze[i][j] = static_cast<sf::Uint8>(grayScale) >= 0.5;
        }
    }
}

void Maze::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    sf::Texture texture;
    texture.loadFromImage(mImage);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    const sf::Vector2f targetSize(static_cast<float>(mMazeSize), static_cast<float>(mMazeSize));
    const auto spriteBounds = sprite.getLocalBounds();
    sprite.setScale(sf::Vector2f(targetSize.x / spriteBounds.width, targetSize.y / spriteBounds.height));

    target.draw(sprite, states);
}

Maze::~Maze() = default;
