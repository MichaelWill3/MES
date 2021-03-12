#pragma once
#ifndef SETTINGS
#define SETTINGS

struct Settings {
	double grid_width;
	double grid_heigth;
	int grid_n_of_elems_horizontally;
	int grid_n_of_elems_vertically;
	int integration_method;
	double conductivity;
	double convection;
	double density;
	double specific_heat;
	double temperature;
	double ambient_temperature;
	double time_step;
	double simulation_time;
};

extern struct Settings settings;
#endif