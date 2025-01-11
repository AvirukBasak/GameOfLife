//
// Created by aviruk on 1/12/25.
//

#ifndef COMPONENTS_MAZECELLTOOLTIP_H
#define COMPONENTS_MAZECELLTOOLTIP_H

#include "SFML/Graphics.hpp"

#include "interfaces/IGameComponent.h"
#include "Maze.h"

class MazeCellToolTip final : public IGameComponent {
    static constexpr int TOOLTIP_OFFSET = 8;
    static constexpr int TOOLTIP_PADDING = 5;
    static constexpr int TOOLTIP_WIDTH = 185;
    static constexpr int TOOLTIP_HEIGHT = 91;

    const Maze &mMaze;

    /**
     * Show a tolltip with cell fitness value on hover over the cell.
     */
    sf::Text mCellFitnessTolltipText;
    sf::RectangleShape mCellFitnessToltipRect;
    sf::RectangleShape mCellIndicatorRect;

public:
    explicit MazeCellToolTip(const Maze &maze);

    ~MazeCellToolTip() override;

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //COMPONENTS_MAZECELLTOOLTIP_H
