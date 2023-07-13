#pragma once
#include <utility>

struct Ray {
	float ox;
	float oy;
	float dir;

	float rayMag = 1000;
	std::pair<double, double> insct = {0.0, 0.0};
};