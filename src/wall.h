#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#define MAX_RAY_DIST 10000.0

#include "point.h"
#include "ray.h"

#define PI 3.141592653589793238

class Wall {
public:
	Point p1{ 0, 0 };
	Point p2{ 0, 0 };
	std::pair<int, int> topLeftOffset{0, 0};

	Wall(Point _p1, Point _p2);
	Wall(nlohmann::json& j);
	void draw(sf::RenderWindow* window);

	nlohmann::json toJSON();

	float calculateIntersect(Ray& ray, sf::RenderWindow* window, bool showIntersections);



private:

};