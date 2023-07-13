#include "player.h"

Player::Player(float _x, float _y){
	this->x = _x;
	this->y = _y;
}

void Player::move(sf::Event& event, double deltaT){
	std::cout << deltaT << '\n';
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::W) {
			std::cout << "W PRESSED\n";
			this->x += this->vel * std::sin(this->dir) * (deltaT / 1e9);
			this->y += this->vel * std::cos(this->dir) * (deltaT / 1e9);

		}
		if (event.key.code == sf::Keyboard::A) {
			std::cout << "A PRESSED\n";
			this->x += this->vel * std::sin(this->dir + PI / 2) * (deltaT / 1e9);
			this->y += this->vel * std::cos(this->dir + PI / 2) * (deltaT / 1e9);
		}
		if (event.key.code == sf::Keyboard::S) {
			std::cout << "S PRESSED\n";
			this->x -= this->vel * std::sin(this->dir) * (deltaT / 1e9);
			this->y -= this->vel * std::cos(this->dir) * (deltaT / 1e9);
		}
		if (event.key.code == sf::Keyboard::D) {
			std::cout << "D PRESSED\n";
			this->x += this->vel * std::sin(this->dir - PI / 2) * (deltaT / 1e9);
			this->y += this->vel * std::cos(this->dir - PI / 2) * (deltaT / 1e9);
		}
		if (event.key.code == sf::Keyboard::Left) {
			std::cout << "LEFT PRESSED\n";
			dir += this->turnVel * (deltaT / 1e9);
		}
		if (event.key.code == sf::Keyboard::Right) {
			std::cout << "RIGHT PRESSED\n";
			dir -= this->turnVel * (deltaT / 1e9);
		}
	}
}

void Player::drawOnMapEditor(sf::RenderWindow* window, std::pair<int, int>& topLeft, const int WIDTH, const int HEIGHT){
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(this->x + topLeft.first, this->y + topLeft.second), sf::Color::Red),
		sf::Vertex(sf::Vector2f(this->x + topLeft.first + this->dirLineMag * std::sin(this->dir), this->y + topLeft.second + this->dirLineMag * std::cos(this->dir)), sf::Color::Red)
	};
	window->draw(line, 2, sf::Lines);

	for (auto& r : rays) {
		sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(r.ox + topLeft.first, r.oy + topLeft.second), sf::Color::Red),
		sf::Vertex(sf::Vector2f(r.ox + topLeft.first + r.rayMag * std::sin(r.dir), r.oy + topLeft.second + r.rayMag * std::cos(r.dir)), sf::Color::Red)
		};
		window->draw(line, 2, sf::Lines);
	}
	
	sf::CircleShape c(this->rad);
	c.setPosition(sf::Vector2f(this->x - this->rad + topLeft.first, this->y - this->rad + topLeft.second));
	c.setFillColor(sf::Color::Red);
	window->draw(c);
}

void Player::generateRays(){
	this->rays.clear();
	float rayStep = this->fov / this->numRays;
	/*for (int i = -this->numRays / 2; i < 0; i++) {
		this->rays.push_back(Ray{ this->x, this->y, this->dir + i * rayStep });
	}
	for (int i = 0; i < this->numRays / 2; i++) {
		this->rays.push_back(Ray{ this->x, this->y, this->dir + i * rayStep });
	}*/

	for (int i = -std::floor(this->numRays / 2); i <= std::ceil(this->numRays / 2); i++) {
		this->rays.push_back(Ray{ this->x, this->y, this->dir + i * rayStep });
	}
}


//http://alienryderflex.com/polygon/
//SECTORS MUST BE DRAWN IN CLOCKWISE OR ANTICLOCKWISE ORDER FOR SECTOR DETECTION TO WORK
void Player::getCurrentSector(Map& map){
	auto playerInSector = [](const auto& polyX, const auto& polyY, const int polyCorners, float x, float y) {
		int   i, j = polyCorners - 1;
		bool  oddNodes = false;
		for (i = 0; i < polyCorners; i++) {
			if ((polyY[i] < y && polyY[j] >= y
				|| polyY[j] < y && polyY[i] >= y)
				&& (polyX[i] <= x || polyX[j] <= x)) {
				if (polyX[i] + (y - polyY[i]) / (polyY[j] - polyY[i]) * (polyX[j] - polyX[i]) < x) {
					oddNodes = !oddNodes;
				}
			}
			j = i;
		}

		return oddNodes;
	};
	
	int i = 0;
	for (auto& s : map.sectors) {
		std::vector<int> xVals;
		std::vector<int> yVals;
		//std::vector<std::pair<int, int>> points;
		for (auto& w : s.walls) {
			//points.push_back(std::make_pair(w.p1.x, w.p1.y));
			//points.push_back(std::make_pair(w.p2.x, w.p2.y));

			xVals.push_back(w.p1.x);
			xVals.push_back(w.p2.x);
			yVals.push_back(w.p1.y);
			yVals.push_back(w.p2.y);
		}

		/*for (auto& p : points) {
			xVals.push_back(p.first);
			yVals.push_back(p.second);
		}*/

		if(playerInSector(xVals, yVals, xVals.size(), this->x, this->y)){
			this->currentSector = i;
			std::cout << xVals.size() << '\n';
			return;
		}
		i++;
	}
	this->currentSector = -1;

	if (this->currentSector >= 0) {
		this->sector = map.sectors[this->currentSector];
	}
}
