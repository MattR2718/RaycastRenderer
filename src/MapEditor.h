#pragma once
#include <SFML/Graphics.hpp>

class MapEditor {
public:

	MapEditor(sf::RenderWindow* _window);
	void draw();

private:
	sf::RenderWindow* window = nullptr;
};