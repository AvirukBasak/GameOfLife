#include <iostream>
#include <GL/gl.h>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
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

    ImGui::SetCurrentContext(ImGui::CreateContext());
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplOpenGL3_NewFrame();

    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui!" << std::endl;
    }

    States::defaultImguiFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(States::defaultFontPath.c_str(), 15);
    if (!States::defaultImguiFont) {
        throw std::runtime_error(std::string("imgui: failed to load '").append(States::defaultFontPath).append("'"));
    }

    // This is how you load a font in ImGui w/ SFML & OpenGL3 :)
    {
        unsigned char *outPixels;
        int outWidth, outHeight;
        ImGui::GetIO().Fonts->GetTexDataAsRGBA32(&outPixels, &outWidth, &outHeight);

        GLuint fontTextureID;
        glGenTextures(1, &fontTextureID);
        glBindTexture(GL_TEXTURE_2D, fontTextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, outWidth, outHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, outPixels);

        // You can store the texture ID and pass it to the ImGui renderer
        ImGui::GetIO().Fonts->TexID = (void *) (intptr_t) fontTextureID;
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
    ImGui_ImplOpenGL3_Shutdown();
    return 0;
}
