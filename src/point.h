#pragma once

#include <SFML/Graphics.hpp>

class Point {
public:
	int x = -1;
	int y = -1;
	std::pair<int, int> topLeftOffset{0, 0};
	int rad = 10;

	sf::Color col{255, 255, 0};

	Point(int _x, int _y);
	void draw(sf::RenderWindow* window);
private:
	sf::CircleShape c;

};