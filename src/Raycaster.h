#pragma once

#include <SFML/Graphics.hpp>

#include "map.h"
#include "player.h"

class Raycaster {
public:

	Raycaster(sf::RenderWindow* _window, const int _WIDTh, const int _HEIGHT);
	void draw(Player& player);
	void raycast(Player& player, Map& map, sf::RenderWindow* window);

private:
	sf::RenderWindow* window = nullptr;
	int WIDTH;
	int HEIGHT;
	std::vector<float> dists;

};