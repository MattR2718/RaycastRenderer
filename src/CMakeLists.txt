cmake_minimum_required(VERSION 3.8.0)

find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp "imgui_setting.h" "Raycast.cpp" "Raycast.h" "MapEditor.h" "MapEditor.cpp" "wall.h" "wall.cpp" "point.h" "point.cpp" "sector.h" "sector.cpp" "map.h" "map.cpp")

target_link_libraries(${PROJECT_NAME}
    imgui::imgui
    sfml-graphics sfml-system sfml-window
    ImGui-SFML::ImGui-SFML
    unofficial::nativefiledialog::nfd
    nlohmann_json::nlohmann_json
)