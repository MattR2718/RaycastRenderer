#pragma once
#include <iostream>
#include <cmath>
#include <set>

#include <SFML/Graphics.hpp>

#include "ray.h"
#include "map.h"

#define PI 3.141592653589793238

class Player {
public:
	float x;
	float y;

	float dir = PI;

	float vel = 33000.0;
	float turnVel = 50;
	float fov = PI;
	int numRays = 5;

	int currentSector = -1;

	std::vector<Ray> rays;

	Player(float _x = 0, float _y = 0);
	void move(sf::Event& event, double deltaT);
	void drawOnMapEditor(sf::RenderWindow* window, std::pair<int, int>& topLeft, const int WIDTH, const int HEIGHT);
	void generateRays();
	void getCurrentSector(Map& map);

private:
	int rad = 40.0;

	float dirLineMag = 100;

	Sector sector;

};