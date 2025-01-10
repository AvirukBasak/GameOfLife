//
// Created by aviruk on 1/11/25.
//

#ifndef COMPONENTS_CONTROLPANEL_H
#define COMPONENTS_CONTROLPANEL_H

#include "interfaces/IGameComponent.h"

class ControlPanel final : public IGameComponent {

public:
    ControlPanel();

    ~ControlPanel() override;

    void handleEvent(const sf::Event &event) override;

    void update() override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //COMPONENTS_CONTROLPANEL_H
