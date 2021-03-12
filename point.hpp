#pragma once

struct Point {
	double x;
	double y;
	unsigned int index;
	bool boundary;
	double temperature;
	Point();
	Point(double _x, double _y, unsigned int _index, bool _boundary, double _temperature);
	Point(double _x, double _y);
	Point(const Point &p);
};