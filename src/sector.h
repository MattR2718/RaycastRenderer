#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "point.h"
#include "wall.h"

class Sector {
public:
	std::vector<Wall> walls;
	std::pair<int, int> topLeftOffset{0, 0};
	Sector();
	Sector(nlohmann::json& j);

	void appendWall(Wall w);
	void draw(sf::RenderWindow* window);

	nlohmann::json toJSON();

private:

};