//
// Created by aviruk on 1/11/25.
//

#include "constants.h"
#include "states.h"
#include "imgui/ControlPanel.h"

#include <imgui.h>

ControlPanel::ControlPanel() = default;

ControlPanel::~ControlPanel() = default;

void ControlPanel::callImGuiComponents() {
    ImGui::Begin("Controls");

    ImGui::Text("Controls");
    ImGui::Text("Controls");
    ImGui::Text("Controls");

    ImGui::End();
}
