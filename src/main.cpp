#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(700, 500), "Counter with Buttons");

    // Initialize counter
    int counter = 0;

    // Create font for the counter text
    sf::Font font;
    // Make sure to have a valid font path
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        return -1;
    }

    // Create text for the counter
    sf::Text counterText;
    counterText.setFont(font);
    counterText.setCharacterSize(50);
    counterText.setFillColor(sf::Color::Black);
    // Positioning the counter text in the window center
    counterText.setPosition(300, 200);

    // Create buttons
    sf::RectangleShape plusButton(sf::Vector2f(100, 50));
    plusButton.setFillColor(sf::Color::Green);
    plusButton.setPosition(150, 350);

    sf::RectangleShape minusButton(sf::Vector2f(100, 50));
    minusButton.setFillColor(sf::Color::Red);
    minusButton.setPosition(450, 350);

    // Create text for buttons
    sf::Text plusText("+", font, 30);
    plusText.setFillColor(sf::Color::White);
    plusText.setPosition(185, 360);

    sf::Text minusText("-", font, 30);
    minusText.setFillColor(sf::Color::White);
    minusText.setPosition(485, 360);

    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the mouse clicked inside the "+" button
                if (plusButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    counter++;
                }
                // Check if the mouse clicked inside the "-" button
                if (minusButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    counter--;
                }
            }
        }

        // Update the counter text
        std::stringstream ss;
        ss << counter;
        counterText.setString(ss.str());

        // Clear the window
        window.clear(sf::Color::White);

        // Draw everything
        window.draw(counterText);
        window.draw(plusButton);
        window.draw(minusButton);
        window.draw(plusText);
        window.draw(minusText);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
