#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <grid/grid_struct.h>
#include <matrix/matrix_struct.h>
#include <param/param.h>
#include <extra/extraData.h>

void func_matrixCalculation(const Grid &grd, Matrix &mtr, const Param &prm,
                            const Lamb &lmb,
                            const std::vector<double> &Xprev,
                            const double &dt);

#endif
