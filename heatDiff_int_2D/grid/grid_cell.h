#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <vector>
#include <cmath>
#include <grid_struct.h>

std::vector<double> func_Xcenter(std::vector<double> &X_coord, const int &Nx);

std::vector<double> func_Ycenter(std::vector<double> &Y_coord, const int &Nx);

std::vector<double> func_gridVolume(std::vector<double> omega_iPlus,
                                    std::vector<double> omega_iMin,
                                    std::vector<double> omega_jPlus,
                                    std::vector<double> omega_jMin,
                                    const int gridN);

std::vector<double> func_getLeft_dL(const std::vector<double> &gridXcent,
                                    const int &Nx);

std::vector<double> func_getRight_dL(const std::vector<double> &gridXcent,
                                     const int &Nx);

std::vector<double> func_getTop_dL(const std::vector<double> &gridYcent,
                                   const int &Nx);

std::vector<double> func_getBot_dL(const Grid &grd);


#endif
