//
// Created by aviruk on 1/11/25.
//

#include <cmath>

#include "imgui.h"

#include "constants.h"
#include "states.h"
#include "imgui/ControlPanel.h"

ControlPanel::ControlPanel() = default;

ControlPanel::~ControlPanel() = default;

constexpr ImVec2 windowPosition = {Constants::WINDOW_HEIGHT + 20, 60};
constexpr ImVec2 windowSize = {
    Constants::WINDOW_WIDTH - Constants::WINDOW_HEIGHT - 2 * 20,
    Constants::WINDOW_HEIGHT - 60 - 14
};

constexpr float MAX_SIM_SPEED = 50;
constexpr float MAX_POPU_SIZE = 100;

void spacing(const int size) {
    for (int i = 0; i < size; i++) {
        ImGui::Spacing();
    }
}

void ui() {
    constexpr int spacing1 = 1;
    constexpr int spacing2 = 2;

    spacing(spacing2);

    // Simulation Speed slider
    {
        ImGui::Text("Simulation Speed");
        spacing(spacing1);
        ImGui::SliderFloat("##SimulationSpeed", &States::simulationSpeedScaler, 0, MAX_SIM_SPEED, "%.2f");
    }

    spacing(spacing2);

    // Population Size slider
    {
        ImGui::Text("Population Size");
        spacing(spacing1);
        ImGui::SliderInt("##PopulationSize", &States::populationSize, 2, MAX_POPU_SIZE);
    }

    spacing(spacing2);

    // Mutation Probability slider
    {
        float mutationPercentage = (float) States::mutationCount / (float) States::maxMutationCount * 100.f;
        ImGui::Text("Mutation Percent: %d Gene%s", States::mutationCount, States::mutationCount == 1 ? "" : "s");

        spacing(spacing1);

        ImGui::SliderFloat("##MutationPercent", &mutationPercentage, 0, 100, "%.2f %%");
        States::mutationCount = (int) ((float) States::maxMutationCount * mutationPercentage / 100.f);
    }

    spacing(spacing2);

    // Mutation Probability slider
    {
        ImGui::Text("Mutation Probability");
        spacing(spacing1);
        ImGui::SliderFloat("##MutationProbability", &States::mutationProbability, 0.0f, 1.0f, "%.2f");
    }

    spacing(spacing2);

    // Next Generation button
    {
        ImGui::Text("Current Generation: %d", States::currentGeneration);
        spacing(spacing1);
        if (ImGui::Button("Next Generation")) {
            ++States::currentGeneration;
        }
    }

    spacing(spacing2);

    // Additional info
    {
        ImGui::Text("Current Highest Fitness: %d", States::highestFitnessThisGen);
        ImGui::Text("Overall Highest Fitness: %d", States::highestOverallFitness);
    }
}

void ControlPanel::callImGuiComponents() {
    ImGui::SetNextWindowPos(windowPosition);
    ImGui::SetNextWindowSize(windowSize);

    ImGui::Begin("Controls", nullptr,
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoCollapse);

    // ImGui::PushFont(States::defaultImguiFont);

    ui();

    // ImGui::PopFont();
    ImGui::End();
}
