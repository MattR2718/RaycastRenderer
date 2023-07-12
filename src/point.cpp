#include "point.h"

Point::Point(int _x, int _y){
	this->x = _x;
	this->y = _y;
	this->c = sf::CircleShape(this->rad);
	this->c.setPosition(sf::Vector2f(this->x - this->rad, this->y - this->rad));
	this->c.setFillColor(this->col);
}

void Point::draw(sf::RenderWindow* window){
	this->c.setPosition(sf::Vector2f(this->x - this->rad + this->topLeftOffset.first, this->y - this->rad + this->topLeftOffset.second));
	window->draw(this->c);
}
