#pragma once

#include <SFML/Graphics.hpp>

class Raycaster {
public:

	Raycaster(sf::RenderWindow* _window, const int _WIDTh, const int _HEIGHT);
	void draw();

private:
	sf::RenderWindow* window = nullptr;
	int WIDTH;
	int HEIGHT;

};