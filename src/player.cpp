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
