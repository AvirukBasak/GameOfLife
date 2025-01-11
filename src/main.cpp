#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "imgui-SFML.h"

#include "constants.h"
#include "states.h"
#include "classes/Game.h"
#include "imgui/ControlPanel.h"

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

    // Create a controls object for ImGui components
    ControlPanel controlPanel;

    // Setup rendering interval
    sf::Clock renderClock;
    const sf::Time renderInterval = sf::milliseconds(1 / Constants::RENDER_FPS * 1000);

    // Keep seperate clock for ImGui
    sf::Clock imguiDeltaClock;

    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Handle events in Game components
            game.handleEvent(event);
            // Handle events in ImGui
            ImGui::SFML::ProcessEvent(window, event);
            // Handle window closed event after to allow necessary cleanup above
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }

        // Call game update function to update states on eaach iter
        game.update();

        // Render frame RENDER_FPS times
        if (renderClock.getElapsedTime() >= renderInterval) {
            // Clear and render but dont display yet
            window.clear(sf::Color::Black);
            game.render();
            renderClock.restart();
        }

        // Call ImGui update
        ImGui::SFML::Update(window, imguiDeltaClock.restart());

        // Call ImGui functions
        controlPanel.callImGuiComponents();

        // Render ImGui last to display it over the SFML game
        ImGui::SFML::Render(window);

        // Display with game and ImGui content
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
