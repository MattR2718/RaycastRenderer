#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "point.h"
#include "wall.h"

class Sector {
public:
	std::vector<Wall> walls;
	std::pair<int, int> topLeftOffset{0, 0};
	Sector();

	void appendWall(Wall w);
	void draw(sf::RenderWindow* window);

private:

};