#include <iostream>
#include <string>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "imgui_setting.h"
#include "Raycaster.h"
#include "MapEditor.h"
#include "map.h"
#include "player.h"

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
    Map map;
    Player player(WIDTH / 2, HEIGHT / 2);

    
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    float fps;
    double deltaT = 0;

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

            if (event.type == sf::Event::KeyPressed) {
                player.move(event, deltaT);
            }

            if (useRaycaster) {
                //raycaster.draw();
            }
            else {
                mapEditor.pollEvent(event, map);
            }

        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear(sf::Color::Black);

        player.generateRays();
        player.getCurrentSector(map);

        ImGui::Begin("Player", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SetWindowFontScale(2);
        std::string posStr("Pos: (" + std::to_string(player.x) + ", " + std::to_string(player.y) + ")");
        ImGui::Text(posStr.c_str());
        ImGui::Text(std::string("Dir: " + std::to_string(player.dir)).c_str());

        ImGui::Text(std::string("Current Sector: " + std::to_string(player.currentSector)).c_str());

        ImGui::SliderFloat("Move Velocity", &player.vel, 0, 100000);
        ImGui::SliderFloat("Turn Velocity", &player.turnVel, 0, 100);
        ImGui::SliderInt("Num Rays", &player.numRays, 0, 100);
        ImGui::SliderFloat("FOV", &player.fov, 0, 2 * PI);
        ImGui::End();


        if (useRaycaster) {
            ImGui::Begin("Sectors", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::SetWindowFontScale(2);
            ImGui::Text(std::to_string(map.sectors.size()).c_str());
            ImGui::End();


            raycaster.draw();
        }
        else {
            ImGui::Begin("Sectors", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::SetWindowFontScale(2);
            ImGui::Text("SECTORS MUST BE DRAWN IN CLOCKWISE OR ANTICLOCKWISE FOR SECTOR SETECTION TO WORK");
            ImGui::Text(std::to_string(mapEditor.currSector).c_str());
            if (ImGui::Button("Next Sector")) {
                mapEditor.currSector++;
                if (mapEditor.currSector == map.sectors.size()) {
                    map.sectors.push_back(Sector());
                }
            }
            if (ImGui::Button("Previous Sector")) {
                mapEditor.currSector = (mapEditor.currSector > 0) ? mapEditor.currSector - 1 : map.sectors.size() - 1;
            }
            ImGui::End();


            ImGui::Begin("Save/Load Map", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::SetWindowFontScale(2);
            if (ImGui::Button("SAVE TO JSON")) {
                mapEditor.saveToJSON(map);
            }
            if (ImGui::Button("LOAD FROM JSON")) {
                mapEditor.loadFromJSON(map);
            }
            ImGui::End();

            mapEditor.draw(map);
            player.drawOnMapEditor(&window, mapEditor.topLeft, WIDTH, HEIGHT);
        }
        
        
        ImGui::ShowDemoWindow();


        ImGui::Begin("Render Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowFontScale(2);
        renderChoiceWidgetSize = ImGui::GetWindowSize();
        ImGui::SetWindowPos(ImVec2{ WIDTH - renderChoiceWidgetSize.x, fpsWidgetSize.y });
        ImGui::RadioButton("Raycaster", &useRaycaster, 1);
        ImGui::RadioButton("Map Editor", &useRaycaster, 0);
        ImGui::End();


        end = std::chrono::high_resolution_clock::now();
        deltaT = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
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
