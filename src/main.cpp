#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "globals.h"
#include "classes/Game.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
                            sf::Style::Titlebar | sf::Style::Close);
    Game game(window);

    sf::Clock renderClock;
    const sf::Time renderInterval = sf::milliseconds(1 / RENDER_FPS * 1000);

    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return 0;
                default:
                    break;
            }
        }

        game.update();

        if (renderClock.getElapsedTime() >= renderInterval) {
            game.render();
            renderClock.restart();
        }
    }

    return 0;
}
