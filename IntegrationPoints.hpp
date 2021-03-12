#pragma once
#include "integrationPoint.hpp"
#include "element.hpp"
#include <math.h>
template <int N>
class IntegrationPoints {
	IntegrationPoint IPs[N*N];
public:
	IntegrationPoints();
	IntegrationPoint operator [](int i) { return IPs[i]; }
};

template <>
inline IntegrationPoints<2>::IntegrationPoints()
{
	double coords[2] = { 
		-1 / sqrt(3), 
		1 / sqrt(3) 
	}; 
	double weights[2] = { 1, 1 };
	double w[4][2] = {
		{weights[0], weights[0]},
		{weights[0], weights[1]},
		{weights[1], weights[1]},
		{weights[1], weights[0]},
	};
	Point p1(coords[0], coords[0]);
	Point p2(coords[1], coords[0]);
	Point p3(coords[1], coords[1]);
	Point p4(coords[0], coords[1]);
	IntegrationPoint P1(p1, w[0]);
	IntegrationPoint P2(p2, w[1]);
	IntegrationPoint P3(p3, w[2]);
	IntegrationPoint P4(p4, w[3]);
	this->IPs[0] = P1;
	this->IPs[1] = P2;
	this->IPs[2] = P3;
	this->IPs[3] = P4;
}

template <>
inline IntegrationPoints<3>::IntegrationPoints()
{
	double coords[3] = {
		-sqrt(3.0/5.0),
		0,
		sqrt(3.0 / 5.0)
	};
	double weights[3] = {
		5.0/9.0,
		8.0 /9.0,
		5.0 /9.0
	};

	double w[9][2] = {
		{weights[0], weights[0]},
		{weights[0], weights[1]},
		{weights[0], weights[2]},
		{weights[1], weights[2]},
		{weights[2], weights[2]},
		{weights[2], weights[1]},
		{weights[2], weights[0]},
		{weights[1], weights[0]},
		{weights[1], weights[1]}
	};


	Point p1(coords[0], coords[0]);
	Point p2(coords[0], coords[1]);
	Point p3(coords[0], coords[2]);
	Point p4(coords[1], coords[2]);
	Point p5(coords[2], coords[2]);
	Point p6(coords[2], coords[1]);
	Point p7(coords[2], coords[0]);
	Point p8(coords[1], coords[0]);
	Point p9(coords[1], coords[1]);
	IntegrationPoint P1(p1, w[0]);
	IntegrationPoint P2(p2, w[1]);
	IntegrationPoint P3(p3, w[2]);
	IntegrationPoint P4(p4, w[3]);
	IntegrationPoint P5(p5, w[4]);
	IntegrationPoint P6(p6, w[5]);
	IntegrationPoint P7(p7, w[6]);
	IntegrationPoint P8(p8, w[7]);
	IntegrationPoint P9(p9, w[8]);
	this->IPs[0] = P1;
	this->IPs[1] = P2;
	this->IPs[2] = P3;
	this->IPs[3] = P4;
	this->IPs[4] = P5;
	this->IPs[5] = P6;
	this->IPs[6] = P7;
	this->IPs[7] = P8;
	this->IPs[8] = P9;
}