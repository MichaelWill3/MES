//#include "parser.hpp"
//#include <fstream>
//#include <iostream>
//#include "settings.hpp"
//#include <sstream>
//#include <string>
//#define SETTINGS_FILE_NAME "settings.txt"
//inline void parseSettings()
//{
//	std::ifstream file(SETTINGS_FILE_NAME);
//	if (!file.good())
//	{
//		std::ofstream f(SETTINGS_FILE_NAME);
//		f << "0.1" << std::endl << "0.1" << std::endl << "4" << std::endl << "4" << std::endl << "2" << std::endl << "25";
//	}
//	std::string a;
//	file >> settings.grid_width;
//	file >> settings.grid_heigth;
//	file >> settings.grid_n_of_elems_horizontally;
//	file >> settings.grid_n_of_elems_vertically;
//	file >> settings.integration_method;
//	file >> settings.conductivity;
//}