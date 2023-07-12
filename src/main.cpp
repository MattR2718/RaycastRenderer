#include <iostream>
#include <string>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "imgui_setting.h"

int main(){
    const int WIDTH = sf::VideoMode::getDesktopMode().width;
    const int HEIGHT = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RaycastRenderer");
    ImGui::SFML::Init(window);
    
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    float fps;

    set_imgui_theme();

    sf::Clock deltaClock;
    while (window.isOpen()){
        start = std::chrono::high_resolution_clock::now();

        sf::Event event;
        while (window.pollEvent(event)){
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear(sf::Color::Black);

        ImGui::ShowDemoWindow();


        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        ImGui::Begin("FPS", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowFontScale(2.5);
        ImGui::SetWindowPos(ImVec2{ WIDTH - ImGui::GetWindowWidth(), 0 });
        ImGui::Text(std::to_string(fps).c_str());
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
