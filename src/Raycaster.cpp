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
		/*float leftSpan = leftmax - leftmin;
		float rightSpan = rightmax - rightmin;
		float valueScaled = (value - leftmin) / leftSpan;
		return rightmin + (valueScaled * rightSpan);*/

		float leftSpan = leftmax - leftmin;
		float rightSpan = rightmax - rightmin;
		float value_scaled = float(value - leftmin) / float(leftSpan);
		float ret = rightmin + (value_scaled * rightSpan);
		//if (ret < rightmin) { return rightmin;  }
		//if (ret > rightmax) { return rightmax;  }
		return ret;
	};


	//this->window->draw(c);

	//DRAW DISTS
	//float height = 1000;
	for (int i = 0; i < player.numRays; i++) {
		this->dists[i] *= std::abs(std::cos(0.5*player.rays[i].dir));
		float height = mapValue(this->dists[i], 0, 2000.0, HEIGHT, 200);
		//float height = mapValue(this->dists[i], 0, 2000.0, (2/3) * HEIGHT, 50);
		
		sf::RectangleShape rect(sf::Vector2f(std::ceil(WIDTH / player.numRays) + 5, height));
		rect.setPosition(sf::Vector2f(std::ceil((player.numRays - i - 1) * WIDTH / player.numRays), (HEIGHT - height) / 2));

		int mapColour = 255 - int(mapValue(height, HEIGHT, 200, 20, 200));
		//std::cout << this->dists[i]<<' '<< mapColour << '\n';

		rect.setFillColor(sf::Color(0, 0, mapColour, (this->dists[i] == MAX_RAY_DIST) ? 0 : 255));
		window->draw(rect);
	}

}

void Raycaster::raycast(Player& player, Map& map, sf::RenderWindow* window, bool showIntersections){
	player.generateRays();
	this->dists.clear();
	for (auto& r : player.rays) {
		std::vector<float> rdist;
		for (auto& w : player.sector.walls) {
			rdist.push_back(w.calculateIntersect(r, window, showIntersections));
		}

		//for (auto& d : rdist) { std::cout << d << ' '; } std::cout << '\n';

		this->dists.push_back(*std::min_element(rdist.begin(), rdist.end()));
	}
}
