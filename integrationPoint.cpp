#include "integrationPoint.hpp"

IntegrationPoint::IntegrationPoint()
{
	location.x = 0;
	location.y = 0;
	weight[0] = 0;
	weight[1] = 0;
}

IntegrationPoint::IntegrationPoint(const IntegrationPoint& p)
{
	location.x = p.location.x;
	location.y = p.location.y;
	weight[0] = p.weight[0];
	weight[1] = p.weight[1];
}

IntegrationPoint::IntegrationPoint(Point _p, double _weight[2])
{
	location.x = _p.x;
	location.y = _p.y;
	weight[0] = _weight[0];
	weight[1] = _weight[1];
}