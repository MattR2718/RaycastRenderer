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

	/*for (auto& w : this->walls) {
		w.topLeftOffset = this->topLeft;
		w.draw(window);
	}*/

	for (auto& s : this->sectors) {
		s.topLeftOffset = this->topLeft;
		s.draw(window);
	}
}

void MapEditor::pollEvent(sf::Event& event){
	//Dragging Background
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
		dragging = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
		dragging = false;
	}
	if (dragging) {
		auto mp = sf::Mouse::getPosition(*this->window);
		this->topLeft.first -= (this->prevMousePos.first - mp.x);
		this->topLeft.second -= (this->prevMousePos.second - mp.y);
		//std::cout << this->topLeft.first << ' ' << this->topLeft.second << '\n';
	}

	//Place Point
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && numMsSinceLastClickMin < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->last_point_click).count()) {
		auto mp = sf::Mouse::getPosition(*this->window);

		bool wallPointChosen = false;
		for (auto& sect : this->sectors) {
			for (auto& w : sect.walls) {
				if ((std::abs(w.p1.x - mp.x - this->topLeft.first) * std::abs(w.p1.x - mp.x - this->topLeft.first) + std::abs(w.p1.y - mp.y - this->topLeft.second) * std::abs(w.p1.y - mp.y - this->topLeft.second)) <= (w.p1.rad * w.p1.rad)) {
					wallPointChosen = true;
					if (this->point1Placed) {
						this->p2 = w.p1;
						sect.appendWall(Wall{ this->p1, this->p2 });
						this->point1Placed = false;
					}
					else {
						this->p1 = w.p1;
						this->point1Placed = true;
					}
				}
				else {
					if ((std::abs(w.p2.x - mp.x - this->topLeft.first) * std::abs(w.p2.x - mp.x - this->topLeft.first) + std::abs(w.p2.y - mp.y - this->topLeft.second) * std::abs(w.p2.y - mp.y - this->topLeft.second)) <= (w.p2.rad * w.p2.rad)) {
						wallPointChosen = true;
						if (this->point1Placed) {
							this->p2 = w.p2;
							sect.appendWall(Wall{ this->p1, this->p2 });
							this->point1Placed = false;
						}
						else {
							this->p1 = w.p2;
							this->point1Placed = true;
						}
					}
				}
			}
		}

		if (!wallPointChosen) {
			if (this->point1Placed) {
				this->p2 = Point(mp.x - this->topLeft.first, mp.y - this->topLeft.second);
				this->sectors[0].appendWall(Wall{this->p1, this->p2});
				this->point1Placed = false;
			}
			else {
				this->p1 = Point(mp.x - this->topLeft.first, mp.y - this->topLeft.second);
				this->point1Placed = true;
			}
		}
		this->last_point_click = std::chrono::high_resolution_clock::now();
	}

	auto mp = sf::Mouse::getPosition(*this->window);
	this->prevMousePos = {mp.x, mp.y};
}
