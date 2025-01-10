#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "imgui-SFML.h"

#include "constants.h"
#include "states.h"
#include "classes/Game.h"

int main() {
    // Initialize constants and states
    Constants::init();
    States::init();

    // Create a window
    sf::RenderWindow window(
        sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT),
        Constants::WINDOW_TITLE,
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(Constants::RENDER_FPS);
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui!" << std::endl;
    }

    // Create a game object
    Game game(window);

    // Setup rendering interval
    sf::Clock renderClock;
    const sf::Time renderInterval = sf::milliseconds(1 / Constants::RENDER_FPS * 1000);

    // Keep seperate clock for ImGui
    sf::Clock imguiDeltaClock;

    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Handle events in ImGui
            ImGui::SFML::ProcessEvent(window, event);
            // Handle events in Game components
            game.handleEvent(event);
            // Handle window closed event after to allow necessary cleanup above
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }

        // Call ImGui update
        ImGui::SFML::Update(window, imguiDeltaClock.restart());

        // Call game update function to update states on eaach iter
        game.update();

        // ImGui render
        ImGui::SFML::Render(window);

        // Render frame RENDER_FPS times
        if (renderClock.getElapsedTime() >= renderInterval) {
            game.render();
            renderClock.restart();
        }
    }

    ImGui::SFML::Shutdown();
    return 0;
}
