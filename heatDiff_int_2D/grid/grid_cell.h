#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <vector>
#include <cmath>
#include <grid_struct.h>

std::vector<double> func_Xcenter(Grid &grd);

std::vector<double> func_Ycenter(Grid &grd);

std::vector<double> func_gridVolume(Grid &grd);

std::vector<double> func_getLeft_dL(Grid &grd);

std::vector<double> func_getRight_dL(Grid &grd);

std::vector<double> func_getTop_dL(Grid &grd);

std::vector<double> func_getBot_dL(Grid &grd);

#endif
