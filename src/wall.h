#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "point.h"

class Wall {
public:
	Point p1{ 0, 0 };
	Point p2{ 0, 0 };
	std::pair<int, int> topLeftOffset{0, 0};

	Wall(Point _p1, Point _p2);
	Wall(nlohmann::json& j);
	void draw(sf::RenderWindow* window);

	nlohmann::json toJSON();



private:

};