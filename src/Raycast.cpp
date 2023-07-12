#include "Raycast.h"

Raycaster::Raycaster(sf::RenderWindow* _window){
	this->window = _window;
}

void Raycaster::draw(){
	sf::CircleShape c(100);
	c.setFillColor(sf::Color::Green);
	c.setPosition(sf::Vector2f(100, 100));

	this->window->draw(c);
}
