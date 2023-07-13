#pragma once
#include <vector>

#include "point.h"
#include "wall.h"
#include "sector.h"

class Map {
public:
	std::vector<Sector> sectors{ Sector() };

	Map();


private:

};