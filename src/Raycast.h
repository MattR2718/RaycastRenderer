#pragma once

#include <SFML/Graphics.hpp>

class Raycaster {
public:

	Raycaster(sf::RenderWindow* _window);
	void draw();

private:
	sf::RenderWindow* window = nullptr;

};