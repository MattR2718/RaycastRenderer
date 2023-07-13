#include <iostream>
#include <string>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "imgui_setting.h"
#include "Raycast.h"
#include "MapEditor.h"

int main(){
    const int WIDTH = sf::VideoMode::getDesktopMode().width;
    const int HEIGHT = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RaycastRenderer");
    ImGui::SFML::Init(window);

    int useRaycaster = 0;
    ImVec2 fpsWidgetSize = { 0, 0 };
    ImVec2 renderChoiceWidgetSize = { 0, 0 };

    Raycaster raycaster(&window, WIDTH, HEIGHT);
    MapEditor mapEditor(&window, WIDTH, HEIGHT);
    

    
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

            if (useRaycaster) {
                //raycaster.draw();
            }
            else {
                mapEditor.pollEvent(event);
            }

        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear(sf::Color::Black);

        if (useRaycaster) {
            raycaster.draw();
        }
        else {
            ImGui::Begin("Sectors");
            ImGui::Text(std::to_string(mapEditor.currSector).c_str());
            if (ImGui::Button("Next Sector")) {
                mapEditor.currSector++;
                if (mapEditor.currSector == mapEditor.map.sectors.size()) {
                    mapEditor.map.sectors.push_back(Sector());
                }
            }
            if (ImGui::Button("Previous Sector")) {
                mapEditor.currSector = (mapEditor.currSector > 0) ? mapEditor.currSector - 1 : mapEditor.map.sectors.size() - 1;
            }
            ImGui::End();


            ImGui::Begin("Save/Load Map");
            if (ImGui::Button("SAVE TO JSON")) {
                mapEditor.saveToJSON();
            }
            if (ImGui::Button("LOAD FROM JSON")) {
                mapEditor.loadFromJSON();
            }
            ImGui::End();

            mapEditor.draw();
        }
        
        
        ImGui::ShowDemoWindow();


        ImGui::Begin("Render Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowFontScale(1.5);
        renderChoiceWidgetSize = ImGui::GetWindowSize();
        ImGui::SetWindowPos(ImVec2{ WIDTH - renderChoiceWidgetSize.x, fpsWidgetSize.y });
        ImGui::RadioButton("Raycaster", &useRaycaster, 1);
        ImGui::RadioButton("Map Editor", &useRaycaster, 0);
        ImGui::End();


        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        ImGui::Begin("FPS", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowFontScale(2.5);
        fpsWidgetSize = ImGui::GetWindowSize();
        ImGui::SetWindowPos(ImVec2{ WIDTH - fpsWidgetSize.x, 0 });
        ImGui::Text(std::to_string(fps).c_str());
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
