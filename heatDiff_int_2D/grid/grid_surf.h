#ifndef GRID_GRID_SURF_H
#define GRID_GRID_SURF_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <grid/grid_struct.h>


std::vector<double> omegaTop_calc(Grid &grd);

std::vector<double> omegaBot_calc(Grid &grd);

std::vector<double> omegaRight_calc(Grid &grd);

std::vector<double> omegaLeft_calc(Grid &grd);

std::vector<double> omegaRight_Xcent_calc(Grid &grd);

std::vector<double> omegaRight_Ycent_calc(Grid &grd);

std::vector<double> omegaLeft_Xcent_calc(Grid &grd);

std::vector<double> omegaLeft_Ycent_calc(Grid &grd);

std::vector<double> omegaTop_Xcent_calc(Grid &grd);

void omegaTop_Ycent_calc(Grid &grd);

std::vector<double> omegaBot_Xcent_calc(Grid &grd);

void omegaBot_Ycent_calc(Grid &grd);

#endif
