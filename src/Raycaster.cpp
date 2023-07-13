#include "Raycaster.h"

Raycaster::Raycaster(sf::RenderWindow* _window, const int _WIDTH, const int _HEIGHT){
	this->window = _window;
	this->WIDTH = _WIDTH;
	this->HEIGHT = _HEIGHT;
}

void Raycaster::draw(Player& player){
	sf::CircleShape c(100);
	c.setFillColor(sf::Color::Green);
	c.setPosition(sf::Vector2f(100, 100));

	auto mapValue = [](float value, float leftmin, float leftmax, float rightmin, float rightmax) {
		float leftSpan = leftmax - leftmin;
		float rightSpan = rightmax - rightmin;
		float valueScaled = (value - leftmin) / leftSpan;
		return rightmin + (valueScaled * rightSpan);
	};

	this->window->draw(c);
	float height = 1000;
	for (int i = 0; i < player.numRays; i++) {
		
		height = mapValue(this->dists[i], 0, 2000.0, HEIGHT, 200);
		
		sf::RectangleShape rect(sf::Vector2f(WIDTH / player.numRays, height));
		rect.setPosition(sf::Vector2f(i * WIDTH / player.numRays, (HEIGHT - height) / 2));
		rect.setFillColor(sf::Color(0, 0, 255, (this->dists[i] == MAX_RAY_DIST) ? 0 : 255));
		window->draw(rect);
	}

}

void Raycaster::raycast(Player& player, Map& map, sf::RenderWindow* window){
	player.generateRays();
	for (auto& r : player.rays) {
		std::vector<float> rdist;
		for (auto& w : player.sector.walls) {
			rdist.push_back(w.calculateIntersect(r, window));
		}

		//for (auto& d : rdist) { std::cout << d << ' '; } std::cout << '\n';

		this->dists.push_back(*std::min_element(rdist.begin(), rdist.end()));
	}
}
