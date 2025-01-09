#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

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

    // Create a game object
    Game game(window);

    // Setup rendering interval
    sf::Clock renderClock;
    const sf::Time renderInterval = sf::milliseconds(1 / Constants::RENDER_FPS * 1000);

    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Handle any game event
            game.handleEvent(event);
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
            game.render();
            renderClock.restart();
        }
    }

    return 0;
}
