#pragma once
#include <vector>
#include "element.hpp"
#include "settings.hpp"

struct Grid {
	std::vector<Element*> elements;
	std::vector<Point*> points;
};

Grid createGrid();