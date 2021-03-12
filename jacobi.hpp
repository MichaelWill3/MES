#pragma once
#include <vector>
#include "point.hpp"
#include "element.hpp"
//#include "IntegrationPoint.hpp"
//#include "IntegrationPoints.hpp"
std::vector<std::vector<std::vector<double>>> jacobi2p(Element *e);
std::vector<std::vector<std::vector<double>>> jacobi3p(Element *e);