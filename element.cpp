#pragma once
#include "element.hpp"

Element::Element(Point p1, Point p2, Point p3, Point p4)
{
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	points[3] = p4;
}
