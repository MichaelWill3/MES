#pragma once
#ifndef PARSER
#define PARSER
//#include "parser.hpp"
#include <fstream>
#include <iostream>
#include "settings.hpp"
#include <sstream>
#include <string>
#define SETTINGS_FILE_NAME "settings.txt"
inline void parseSettings()
{
	std::ifstream file(SETTINGS_FILE_NAME);
		if (!file.good())
		{
			std::ofstream f(SETTINGS_FILE_NAME);
			f << "0.1" << std::endl << "0.1" << std::endl << "4" << std::endl << "4" << std::endl << "2" << std::endl << "25" << std::endl << "300" << std::endl << "7800" << std::endl << "700" << std::endl << 100 << std::endl << "1200" << std::endl << "50" << std::endl << "500";
		}
		static bool triedtofix = false;
	std::string a;
	try {
		file >> settings.grid_width;
		file >> settings.grid_heigth;
		file >> settings.grid_n_of_elems_horizontally;
		file >> settings.grid_n_of_elems_vertically;
		file >> settings.integration_method;
		file >> settings.conductivity;
		file >> settings.convection;
		file >> settings.density;
		file >> settings.specific_heat;
		file >> settings.temperature;
		file >> settings.ambient_temperature;
		file >> settings.time_step;
		file >> settings.simulation_time;
	}
	catch (...)
	{
		if (!triedtofix)
		{
			triedtofix = true;
			remove(SETTINGS_FILE_NAME);
			parseSettings();
		}
		else {
			std::cout << "\nSomething bad happened while trying to read file.";
			return;
		}
	}
}
#endif