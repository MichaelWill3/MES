#include "includes.hpp"
std::vector<double> gauss(std::vector< std::vector<double> > A) {
	int n = A.size();

	for (int i = 0; i < n; i++) {
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k < n; k++) {
			if (abs(A[k][i]) > maxEl) {
				maxEl = abs(A[k][i]);
				maxRow = k;
			}
		}

		for (int k = i; k < n + 1; k++) {
			double tmp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = tmp;
		}

		for (int k = i + 1; k < n; k++) {
			double c = -A[k][i] / A[i][i];
			for (int j = i; j < n + 1; j++) {
				if (i == j) {
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}

	std::vector<double> x(n);
	for (int i = n - 1; i >= 0; i--) {
		x[i] = A[i][n] / A[i][i];
		for (int k = i - 1; k >= 0; k--) {
			A[k][n] -= A[k][i] * x[i];
		}
	}
	return x;
}

int main()
{
	parseSettings();

	Grid grid = createGrid();

	for (double t = 0; t < settings.simulation_time; t += settings.time_step)
	{

		std::vector<std::vector<double>> H;
		std::vector<std::vector<double>> C;
		std::vector<double> P;
		integrated_H(grid.elements, H, C, P);
	
	
		std::vector< std::vector<double>> H_plus_C_by_dt(grid.points.size(), std::vector<double>(grid.points.size()));
		for (int i = 0; i < grid.points.size(); i++)
			for (int j = 0; j < grid.points.size(); j++)
				H_plus_C_by_dt[i][j] = H[i][j] + (C[i][j] / settings.time_step);

		std::vector<double> C_by_dt_times_t0(grid.points.size());
		for (int i = 0; i < grid.points.size(); i++)
		{
			C_by_dt_times_t0[i] = 0;
			for (int j = 0; j < grid.points.size(); j++)
			{
				C_by_dt_times_t0[i] += (C[j][i] / settings.time_step) * grid.points[j]->temperature;
			}
		}

		std::vector<double> b(grid.points.size());
		for (int i = 0; i < grid.points.size(); i++)
		{
			b[i] = P[i] + C_by_dt_times_t0[i];
		}

		std::vector< std::vector<double>> to_solve(H_plus_C_by_dt);
		for (int i = 0; i < b.size(); i++)
		{
			to_solve[i].push_back(b[i]);
		}

		auto new_temperatures = gauss(to_solve);
		double min, max;
		min = new_temperatures[0];
		max = new_temperatures[0];
		for (int i = 0; i < grid.points.size(); i++)
		{
			grid.points[i]->temperature = new_temperatures[i];
			if (new_temperatures[i] > max) max = new_temperatures[i];
			if (new_temperatures[i] < min) min = new_temperatures[i];
		}
		std::cout << "min: " << min << ", max: " << max << std::endl;
	}

}