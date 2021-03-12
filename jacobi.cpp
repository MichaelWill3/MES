#pragma once
#include "jacobi.hpp"
#include "IntegrationPoints.hpp"
#include <iostream>
#include "settings.hpp"

std::vector<std::vector<std::vector<double>>> jacobi2p(Element *e)
{
	std::vector<std::vector<std::vector<double>>> J_(4, std::vector<std::vector<double>>(4, std::vector<double>(4)));
	std::vector<std::vector<std::vector<double>>> J_tmp(4, std::vector<std::vector<double>>(4, std::vector<double>(4)));
	IntegrationPoints<2> IPs;
	double (*dNdksi[4])(IntegrationPoint);
	dNdksi[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.y) / 4; };
	dNdksi[1] = [](IntegrationPoint p) {return  1 * (1 - p.location.y) / 4; };
	dNdksi[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.y) / 4; };
	dNdksi[3] = [](IntegrationPoint p) {return -1 * (1 + p.location.y) / 4; };

	double (*dNdeta[4])(IntegrationPoint);
	dNdeta[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.x) / 4; };
	dNdeta[1] = [](IntegrationPoint p) {return -1 * (1 + p.location.x) / 4; };
	dNdeta[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.x) / 4; };
	dNdeta[3] = [](IntegrationPoint p) {return  1 * (1 - p.location.x) / 4; };

	for (int ip = 0; ip < 4; ip++)
	{
		for (int N = 0; N < 4; N++)
		{
			J_[ip][0][0] += dNdksi[N](IPs[ip]) * e->points[N].x;
			J_[ip][0][1] += dNdksi[N](IPs[ip]) * e->points[N].y;
			J_[ip][1][0] += dNdeta[N](IPs[ip]) * e->points[N].x;
			J_[ip][1][1] += dNdeta[N](IPs[ip]) * e->points[N].y;
		}
	}
	return J_;
}

std::vector<std::vector<std::vector<double>>> jacobi3p(Element* e)
{
	std::vector<std::vector<std::vector<double>>> J_(9, std::vector<std::vector<double>>(4, std::vector<double>(4)));
	IntegrationPoints<3> IPs;
	double (*dNdksi[4])(IntegrationPoint);
	dNdksi[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.y) / 4; };
	dNdksi[1] = [](IntegrationPoint p) {return  1 * (1 - p.location.y) / 4; };
	dNdksi[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.y) / 4; };
	dNdksi[3] = [](IntegrationPoint p) {return -1 * (1 + p.location.y) / 4; };

	double (*dNdeta[4])(IntegrationPoint);
	dNdeta[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.x) / 4; };
	dNdeta[1] = [](IntegrationPoint p) {return -1 * (1 + p.location.x) / 4; };
	dNdeta[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.x) / 4; };
	dNdeta[3] = [](IntegrationPoint p) {return  1 * (1 - p.location.x) / 4; };
	for (int ip = 0; ip < 9; ip++)
	{
		for (int N = 0; N < 4; N++)
		{
			J_[ip][0][0] += dNdksi[N](IPs[ip]) * e->points[N].x;
			J_[ip][0][1] += dNdksi[N](IPs[ip]) * e->points[N].y;
			J_[ip][1][0] += dNdeta[N](IPs[ip]) * e->points[N].x;
			J_[ip][1][1] += dNdeta[N](IPs[ip]) * e->points[N].y;
		}
	}
	return J_;
}