//
// Created by aviruk on 1/12/25.
//

#ifndef INTERFACES_IGAMEIMGUICOMPONENT_H
#define INTERFACES_IGAMEIMGUICOMPONENT_H

class IGameImGuiComponent {
public:
    virtual ~IGameImGuiComponent() = default;

    virtual void renderImGui() = 0;
};

#endif //INTERFACES_IGAMEIMGUICOMPONENT_H
