//
// Created by aviruk on 1/12/25.
//

#include "constants.h"
#include "states.h"
#include "components/MazeCellToolTip.h"

MazeCellToolTip::MazeCellToolTip(const Maze &maze) : mMaze(maze) {
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
        mMaze.getCellSizeInPixels() - 2,
        mMaze.getCellSizeInPixels() - 2
    });
}

MazeCellToolTip::~MazeCellToolTip() = default;

void MazeCellToolTip::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::MouseMoved) {
        const auto [x, y] = event.mouseMove;
        if (!States::mazeCellTooltipData.isEmpty()) {
            const sf::Vector2f pixel = States::mazeCellTooltipData.mTopLeft;
            // Set component data from state
            mCellFitnessTolltipText.setString(States::mazeCellTooltipData.toString());
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
            States::mazeCellTooltipData = States::MazeCellToolTipData::empty();
        }
    }
}

void MazeCellToolTip::update() {
}

void MazeCellToolTip::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (mCellFitnessTolltipText.getString() != "") {
        target.draw(mCellIndicatorRect, states);
        target.draw(mCellFitnessToltipRect, states);
        target.draw(mCellFitnessTolltipText, states);
    }
}
