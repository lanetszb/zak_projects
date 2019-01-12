#ifndef GRID_GRID_CELL_H
#define GRID_GRID_CELL_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <grid/grid_struct.h>

std::vector<double> Xcenter_calc(Grid &grd);

std::vector<double> Ycenter_calc(Grid &grd);

std::vector<double> gridVolume_calc(Grid &grd);

std::vector<double> Left_dL_calc(Grid &grd);

std::vector<double> Right_dL_calc(Grid &grd);

std::vector<double> Top_dL_calc(Grid &grd);

std::vector<double> Bot_dL_calc(Grid &grd);

#endif
