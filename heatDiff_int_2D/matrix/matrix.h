#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <grid/grid_struct.h>
#include <matrix/matrix_struct.h>
#include <param.h>

void func_matrixCalculation(const Grid &grd, Matrix &mtr, const Param &prm,
                            const std::vector<double> &Xprev);

#endif
