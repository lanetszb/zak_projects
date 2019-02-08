#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <grid/gridStruct.h>

std::vector<double> Xcenter_calc(Grid &grd);

std::vector<double> Ycenter_calc(Grid &grd);

std::vector<double> gridVolume_calc(Grid &grd);

std::vector<double> Left_dL_calc(Grid &grd);

std::vector<double> Right_dL_calc(Grid &grd);

std::vector<double> Top_dL_calc(Grid &grd);

std::vector<double> Bot_dL_calc(Grid &grd);

#endif
