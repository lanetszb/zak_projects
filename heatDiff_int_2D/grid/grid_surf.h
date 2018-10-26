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


std::vector<double> func_omega_iPlus_Xcent(Grid &grd);

std::vector<double> func_omega_iPlus_Ycent(Grid &grd);

std::vector<double> func_omega_iMinus_Xcent(Grid &grd);

std::vector<double> func_omega_iMinus_Ycent(Grid &grd);

std::vector<double> func_omega_jPlus_Xcent(Grid &grd);

void omegaTop_Ycent_calc(Grid &grd);

std::vector<double> func_omega_jMinus_Xcent(Grid &grd);

void omegaBot_Ycent_calc(Grid &grd);

#endif
