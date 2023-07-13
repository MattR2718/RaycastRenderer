#include "wall.h"

Wall::Wall(Point _p1, Point _p2){
	this->p1 = _p1;
	this->p2 = _p2;
	
}

Wall::Wall(nlohmann::json& j){
	std::cout << "SIZE PASSED TO WALL: " << j.size() << '\n';
	this->p1 = Point(j[0][0], j[0][1]);
	this->p2 = Point(j[1][0], j[1][1]);
}

void Wall::draw(sf::RenderWindow* window){
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(this->p1.x + this->topLeftOffset.first, this->p1.y + this->topLeftOffset.second), this->p1.col),
		sf::Vertex(sf::Vector2f(this->p2.x + this->topLeftOffset.first, this->p2.y + this->topLeftOffset.second), this->p2.col)
	};
	window->draw(line, 2, sf::Lines);

	this->p1.topLeftOffset = this->topLeftOffset;
	this->p2.topLeftOffset = this->topLeftOffset;

	this->p1.draw(window);
	this->p2.draw(window);
}

nlohmann::json Wall::toJSON(){
	return nlohmann::json({ {p1.x, p1.y}, {p2.x, p2.y} });
}

