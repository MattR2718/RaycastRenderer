#pragma once
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#define PI 3.141592653589793238

class Player {
public:
	float x;
	float y;

	float dir = PI;

	float vel = 33000.0;
	float turnVel = 50;

	Player(float _x = 0, float _y = 0);
	void move(sf::Event& event, double deltaT);
	void drawOnMapEditor(sf::RenderWindow* window, std::pair<int, int>& topLeft, const int WIDTH, const int HEIGHT);

private:
	int rad = 40.0;

	float dirLineMag = 100;

};