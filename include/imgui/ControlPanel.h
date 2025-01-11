//
// Created by aviruk on 1/11/25.
//

#ifndef COMPONENTS_CONTROLPANEL_H
#define COMPONENTS_CONTROLPANEL_H

#include "interfaces/IGameImGuiComponent.h"

class ControlPanel final : public IGameImGuiComponent {

public:
    ControlPanel();

    ~ControlPanel() override;

    void renderImGui() override;
};

#endif //COMPONENTS_CONTROLPANEL_H
