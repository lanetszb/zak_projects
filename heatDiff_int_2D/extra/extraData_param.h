#ifndef EXTRAFILES_LAMB_H
#define EXTRAFILES_LAMB_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <extra/extraData_struct.h>
#include <grid/grid_struct.h>

void getLeft_lamb(Lamb &lmb,
                  const Grid &grd, const std::vector<double> &X);

void getRight_lamb(Lamb &lmb,
                   const Grid &grd, const std::vector<double> &X);

void getTop_lamb(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X);

void getBot_lamb(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X);

void getDensity(Lamb &lmb,
                const Grid &grd, const std::vector<double> &X);

void getCapacity(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X);

#endif
