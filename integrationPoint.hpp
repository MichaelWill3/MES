#pragma once
#include "point.hpp"

class IntegrationPoint {
public:
	Point location;
	double weight[2];
	IntegrationPoint(); 
	IntegrationPoint(const IntegrationPoint& p);
	//IntegrationPoint(double x, double y, double _weight[2]);
	IntegrationPoint(Point _p, double _weight[2]);
};