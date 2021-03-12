#pragma once
#include "point.hpp"

struct Element {
	Point points[4];
	Element(Point p1, Point p2, Point p3, Point p4);
};