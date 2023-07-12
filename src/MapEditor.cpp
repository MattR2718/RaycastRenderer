#include "MapEditor.h"

MapEditor::MapEditor(sf::RenderWindow* _window){
	this->window = _window;
}

void MapEditor::draw(){
	sf::CircleShape c(100);
	c.setFillColor(sf::Color::Red);
	c.setPosition(sf::Vector2f(100, 100));

	this->window->draw(c);
}
