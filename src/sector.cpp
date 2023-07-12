#include "sector.h"

Sector::Sector(){
}

void Sector::appendWall(Wall w){
	this->walls.push_back(w);
}

void Sector::draw(sf::RenderWindow* window){
	for (auto& w : this->walls) {
		w.topLeftOffset = this->topLeftOffset;
		w.draw(window);
	}
}
