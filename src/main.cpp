#include <iostream>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main(){
    const int WIDTH = sf::VideoMode::getDesktopMode().width;
    const int HEIGHT = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RaycastRenderer");
    ImGui::SFML::Init(window);
    
    sf::Clock deltaClock;
    while (window.isOpen()){
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


        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
