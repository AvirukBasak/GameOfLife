//
// Created by aviruk on 1/11/25.
//

#include "constants.h"
#include "states.h"
#include "imgui/ControlPanel.h"

#include <imgui.h>

ControlPanel::ControlPanel() = default;

ControlPanel::~ControlPanel() = default;

constexpr ImVec2 windowPosition = {Constants::WINDOW_HEIGHT + 20, 60};
constexpr ImVec2 windowSize = {
    Constants::WINDOW_WIDTH - Constants::WINDOW_HEIGHT - 2 * 20,
    Constants::WINDOW_HEIGHT - 60 - 14
};

void ui() {
    constexpr int spacing = 2;

    for (int i = 0; i < spacing; i++) {
        ImGui::Spacing();
    }

    // Simulation Speed slider
    ImGui::Text("Simulation Speed");
    ImGui::SliderFloat("##SimulationSpeed", &States::simulationSpeedScaler, 0, 10, "%.2f");

    for (int i = 0; i < spacing; i++) {
        ImGui::Spacing();
    }

    // Population Size slider
    ImGui::Text("Population Size");
    ImGui::SliderInt("##PopulationSize", &States::entityCount, 2, 20);

    for (int i = 0; i < spacing; i++) {
        ImGui::Spacing();
    }

    // Mutation Probability slider
    ImGui::Text("Mutation Probability");
    ImGui::SliderFloat("##MutationProbability", &States::mutationProbability, 0.0f, 1.0f, "%.2f");

    for (int i = 0; i < spacing; i++) {
        ImGui::Spacing();
    }

    // Next Generation button
    if (ImGui::Button("Next Generation")) {
    }
}

void ControlPanel::callImGuiComponents() {
    ImGui::SetNextWindowPos(windowPosition);
    ImGui::SetNextWindowSize(windowSize);
    ImGui::Begin("Controls", nullptr,
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoCollapse);

    ui();

    ImGui::End();
}
