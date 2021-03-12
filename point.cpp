#pragma once
#include "point.hpp"
Point::Point()
{
	this->x = 0;
	this->y = 0;
	this->index = 0;
}
Point::Point(double _x, double _y, unsigned int _index, bool _boundary, double _temperature)
{
	this->x = _x;
	this->y = _y;
	this->index = _index;
	this->boundary = _boundary;
	this->temperature = _temperature;
}
Point::Point(const Point& p)
{
	this->x = p.x;
	this->y = p.y;
	this->index = p.index;
	this->boundary = p.boundary;
	this->temperature = p.temperature;
}
Point::Point(double _x, double _y)
{
	this->x = _x;
	this->y = _y;
	this->index = 0;
	this->boundary = false;
	this->temperature = 0;
}