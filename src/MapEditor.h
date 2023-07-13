#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <nfd.h>
#include <nlohmann/json.hpp>

#include "point.h"
#include "wall.h"
#include "sector.h"
#include "map.h"

class MapEditor {
public:
	int currSector = 0;
	std::pair<int, int> topLeft{ 0, 0 };

	MapEditor(sf::RenderWindow* _window, const int _WIDTH, const int _HEIGHT);
	void draw(Map& map);
	void pollEvent(sf::Event& event, Map& map);
	void saveToJSON(Map& map);
	void loadFromJSON(Map& map);

private:
	sf::RenderWindow* window = nullptr;
	int WIDTH = 0;
	int HEIGHT = 0;

	int cellSize = 50;
	int gridLineWidth = 1;

	sf::Color backgroundColour = sf::Color(50, 50, 50);
	sf::Color lineColour = sf::Color(100, 100, 100);

	sf::RectangleShape vertGridLine;
	sf::RectangleShape horiGridLine;

	std::pair<int, int> prevMousePos{0, 0};

	bool dragging = false;

	bool point1Placed = false;

	//std::vector<Wall> walls;
	//std::vector<Sector> sectors = {Sector()};
	Point p1{ 0, 0 };
	Point p2{ 0, 0 };

	std::chrono::high_resolution_clock::time_point last_point_click = std::chrono::high_resolution_clock::now();
	int numMsSinceLastClickMin = 100;

};