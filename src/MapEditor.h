#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class MapEditor {
public:

	MapEditor(sf::RenderWindow* _window, const int _WIDTH, const int _HEIGHT);
	void draw();
	void pollEvent(sf::Event& event);

private:
	sf::RenderWindow* window = nullptr;
	int WIDTH = 0;
	int HEIGHT = 0;

	int cellSize = 50;
	int gridLineWidth = 1;

	sf::Color backgroundColour = sf::Color(50, 50, 50);
	sf::Color lineColour = sf::Color(100, 100, 100);

	sf::RectangleShape vertGridLine;
	sf::RectangleShape horiGridLine;

	std::pair<int, int> topLeft{ 0, 0 };
	std::pair<int, int> prevMousePos{0, 0};

	bool dragging = false;
};