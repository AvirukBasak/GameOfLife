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

// Font loading function should be called once after font creation
inline void LoadFontToImGuiWithOpenGL() {
    unsigned char *outPixels;
    int outWidth, outHeight;
    ImGui::GetIO().Fonts->GetTexDataAsRGBA32(&outPixels, &outWidth, &outHeight);

    GLuint fontTextureID;
    glGenTextures(1, &fontTextureID);
    glBindTexture(GL_TEXTURE_2D, fontTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, outWidth, outHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, outPixels);

    ImGui::GetIO().Fonts->TexID = (void *) (intptr_t) fontTextureID;
}

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

    // window.setFramerateLimit(Constants::RENDER_FPS);

    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui!" << std::endl;
        return -1;
    }

    ImGui_ImplOpenGL3_Init();

    // Load font
    States::defaultImguiFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(States::defaultFontPath.c_str(), 15);
    if (!States::defaultImguiFont) {
        throw std::runtime_error(std::string("imgui: failed to load '").append(States::defaultFontPath).append("'"));
    }

    // Load font texture ONCE after font is added
    LoadFontToImGuiWithOpenGL();

    // Create game object
    Game game(window);
    ControlPanel controlPanel;

    // Setup rendering interval
    sf::Clock sfmlRenderDeltaClock;
    sf::Clock imguiRenderDeltaClock;
    const sf::Time renderInterval = sf::milliseconds(1000 / Constants::RENDER_FPS);

    // Main loop
    while (window.isOpen()) {
        ImGui_ImplOpenGL3_NewFrame();
        // ImGui::NewFrame(); <-- Not called as ImGui::SFML::Update() calls this

        sf::Event event{};
        while (window.pollEvent(event)) {
            game.handleEvent(event);
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
                // Break to allow proper cleanup after window closed
                break;
            }
        }

        game.update();

        if (sfmlRenderDeltaClock.getElapsedTime() >= renderInterval) {
            window.clear(sf::Color::Black);
            game.render();
            sfmlRenderDeltaClock.restart();
        }

        ImGui::SFML::Update(window, imguiRenderDeltaClock.restart());
        controlPanel.callImGuiComponents();
        ImGui::SFML::Render(window);

        window.display();
        ImGui::EndFrame();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui::SFML::Shutdown();
    return 0;
}
