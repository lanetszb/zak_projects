#ifndef GRID_SURF_H
#define GRID_SURF_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <grid_struct.h>


std::vector<double> func_omega_jPlus(Grid &grd);

std::vector<double> func_omega_jMin(Grid &grd);

std::vector<double> func_omega_iPlus(Grid &grd);

std::vector<double> func_omega_iMin(Grid &grd);


std::vector<double> omegaRight_Xcent_calc(Grid &grd);

std::vector<double> omegaRight_Ycent_calc(Grid &grd);

std::vector<double> omegaLeft_Xcent_calc(Grid &grd);

std::vector<double> omegaLeft_Ycent_calc(Grid &grd);

std::vector<double> omegaTop_Xcent_calc(Grid &grd);

void omegaTop_Ycent_calc(Grid &grd);

std::vector<double> omegaBot_Xcent_calc(Grid &grd);

void omegaBot_Ycent_calc(Grid &grd);

#endif
