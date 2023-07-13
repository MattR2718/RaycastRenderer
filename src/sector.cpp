#include "sector.h"

Sector::Sector(){
}


//Create sector from json
Sector::Sector(nlohmann::json& j){
	this->walls.clear();
	std::cout << j.dump() << '\n';
	std::cout << "SIZE OF JSON SENT TO SECTOR: " << j.size() << '\n';
	for (nlohmann::json js : j) {
		this->appendWall(Wall(js));
	}
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

nlohmann::json Sector::toJSON(){
	nlohmann::json j;
	for (auto& w : this->walls) {
		j.emplace_back(w.toJSON());
	}
	return j;
}
