#include "grid.hpp"

Grid createGrid()
{
	Grid grid;
	//std::vector <Point*> points;
	double w_gap = settings.grid_width / settings.grid_n_of_elems_horizontally;
	double h_gap = settings.grid_heigth / settings.grid_n_of_elems_vertically;
	for (int h = 0; h < settings.grid_n_of_elems_horizontally; h++)
	{
		for (int w = 0; w < settings.grid_n_of_elems_vertically; w++)
		{
			Point *p = new Point(
				settings.grid_width / (settings.grid_n_of_elems_horizontally - 1) * w,
				settings.grid_heigth / (settings.grid_n_of_elems_vertically - 1) * h,
				h * settings.grid_n_of_elems_vertically + w,
				(w == 0 || h == 0 || w == (settings.grid_n_of_elems_horizontally - 1) || h == (settings.grid_n_of_elems_horizontally - 1)),
				settings.temperature
			);
			grid.points.push_back(p);
		}
	}

	//std::vector<Element*> elements((settings.grid_n_of_elems_horizontally - 1) * (settings.grid_n_of_elems_vertically - 1));
	//std::vector<Element*> elements;
	for (int h = 0; h < settings.grid_n_of_elems_horizontally - 1; h++)
	{
		for (int w = 0; w < settings.grid_n_of_elems_vertically - 1; w++)
		{
			Element* e = new Element(
				*grid.points[settings.grid_n_of_elems_horizontally * h + w ],
				*grid.points[settings.grid_n_of_elems_horizontally * h + w + 1 ],
				*grid.points[settings.grid_n_of_elems_horizontally * (h + 1) + w + 1 ],
				*grid.points[settings.grid_n_of_elems_horizontally * (h + 1) + w ]
			);
			grid.elements.push_back(e);
		}
	}

	return grid;
}