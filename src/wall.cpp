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

//float Wall::calculateIntersect(const Ray& ray){
//	float x1 = ray.ox;
//	float y1 = ray.oy;
//	float x2 = ray.ox + MAX_RAY_DIST * std::sin(ray.dir);
//	float y2 = ray.oy + MAX_RAY_DIST * std::cos(ray.dir);
//
//	float x3 = this->p1.x;
//	float y3 = this->p1.y;
//	float x4 = this->p2.x;
//	float y4 = this->p2.y;
//
//	float m1 = (y2 - y1) / (x2 - x1);
//	float m2 = (y3 - y4) / (x3 - x4);
//
//	float c1 = y1 - m1 * x1;
//	float c2 = y3 - m2 * x3;
//
//	float xi = (c2 - c1) / (m1 - m2);
//	float yi = m1 * xi + c1;
//
//	if ((((x1 <= xi && xi <= x2) || (x2 <= xi && xi <= x1))
//		&& ((x3 <= xi && xi <= x4) || (x4 <= xi && xi <= x3)))
//		&& (((y1 <= yi && yi <= y2) || (y2 <= yi && yi <= y1))
//			&& ((y3 <= yi && yi <= y4) || (y4 <= yi && yi <= y3)))) {
//
//		//std::cout << std::sqrt(std::abs(xi - x1) * std::abs(xi - x1) + std::abs(yi - y1) * std::abs(yi - y1)) << '\n';
//		return std::sqrt(std::abs(xi - x1) * std::abs(xi - x1) + std::abs(yi - y1) * std::abs(yi - y1));
//	}
//
//	return MAX_RAY_DIST;
//}

float Wall::calculateIntersect(Ray& ray, sf::RenderWindow* window, bool showIntersections) {

	auto crossP = [](const Point& p1, const Point& p2, const Point& p3) {
		return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	};

	auto onSegment = [](const Point& p1, const Point& p2, const Point& p3) {
		return (std::min(p1.x, p2.x) <= p3.x && p3.x <= std::max(p1.x, p2.x) &&
			std::min(p1.y, p2.y) <= p3.y && p3.y <= std::max(p1.y, p2.y));
	};

	auto doIntersect = [crossP, onSegment](const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
		double cp1 = crossP(p1, p2, p3);
		double cp2 = crossP(p1, p2, p4);
		double cp3 = crossP(p3, p4, p1);
		double cp4 = crossP(p3, p4, p2);

		if (cp1 == 0 && cp2 == 0 && cp3 == 0 && cp4 == 0) {
			// The two line segments are collinear
			return onSegment(p1, p2, p3) || onSegment(p1, p2, p4) ||
				onSegment(p3, p4, p1) || onSegment(p3, p4, p2);
		}

		return (cp1 * cp2 < 0) && (cp3 * cp4 < 0);
	};

	auto calcIntersect = [](const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
		double x1 = p1.x, y1 = p1.y;
		double x2 = p2.x, y2 = p2.y;
		double x3 = p3.x, y3 = p3.y;
		double x4 = p4.x, y4 = p4.y;

		double determinant = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / determinant;
		double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / determinant;

		return std::make_pair(x, y);
	};

	Point p1(ray.ox, ray.oy);
	Point p2(ray.ox + MAX_RAY_DIST * std::sin(ray.dir), ray.oy + MAX_RAY_DIST * std::cos(ray.dir));
	Point p3(this->p1.x, this->p1.y);
	Point p4(this->p2.x, this->p2.y);

	if (doIntersect(p1, p2, p3, p4)) {
		auto in = calcIntersect(p1, p2, p3, p4);
		ray.insct = in;
		if (showIntersections) {
			sf::CircleShape c(20.0);
			c.setPosition(sf::Vector2f(in.first - 20.0 + this->topLeftOffset.first, in.second - 20.0 + this->topLeftOffset.second));
			c.setFillColor(sf::Color::Red);
			window->draw(c);
		}

		return std::sqrt((p1.x - in.first) * (p1.x - in.first) + (p1.y - in.second) * (p1.y - in.second));
	}
	else {
		//std::cout << "The line segments do not intersect.\n";
		return MAX_RAY_DIST;
	}

}