#include "MapEditor.h"

MapEditor::MapEditor(sf::RenderWindow* _window, const int _WIDTH, const int _HEIGHT){
	this->window = _window;
	this->WIDTH = _WIDTH;
	this->HEIGHT = _HEIGHT;
	this->vertGridLine = sf::RectangleShape(sf::Vector2f(1, this->HEIGHT));
	this->vertGridLine.setFillColor(this->lineColour);
	this->horiGridLine = sf::RectangleShape(sf::Vector2f(this->WIDTH, 1));
	this->horiGridLine.setFillColor(this->lineColour);
}

void MapEditor::draw(){
	this->window->clear(this->backgroundColour);

	for (int i = this->topLeft.first % this->cellSize; i < this->WIDTH; i += this->cellSize) {
		this->vertGridLine.setPosition(sf::Vector2f(i, 0));
		this->window->draw(this->vertGridLine);
	}
	for (int j = this->topLeft.second % this->cellSize; j < this->HEIGHT; j += this->cellSize) {
		this->horiGridLine.setPosition(sf::Vector2f(0, j));
		this->window->draw(this->horiGridLine);
	}
}

void MapEditor::pollEvent(sf::Event& event){
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
		dragging = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
		dragging = false;
	}

	if (dragging) {
		auto mp = sf::Mouse::getPosition();
		this->topLeft.first -= (this->prevMousePos.first - mp.x);
		this->topLeft.second -= (this->prevMousePos.second - mp.y);
		//std::cout << this->topLeft.first << ' ' << this->topLeft.second << '\n';
	}

	auto mp = sf::Mouse::getPosition();
	this->prevMousePos = {mp.x, mp.y};
}
