cmake_minimum_required(VERSION 3.8.0)

find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG)

add_executable(${PROJECT_NAME} main.cpp "imgui_setting.h")

target_link_libraries(${PROJECT_NAME}
    imgui::imgui
    sfml-graphics sfml-system sfml-window
    ImGui-SFML::ImGui-SFML
)