#include "Raycast.h"

Raycaster::Raycaster(sf::RenderWindow* _window, const int _WIDTH, const int _HEIGHT){
	this->window = _window;
	this->WIDTH = _WIDTH;
	this->HEIGHT = _HEIGHT;
}

void Raycaster::draw(){
	sf::CircleShape c(100);
	c.setFillColor(sf::Color::Green);
	c.setPosition(sf::Vector2f(100, 100));

	this->window->draw(c);

}
