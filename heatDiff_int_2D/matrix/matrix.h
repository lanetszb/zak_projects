#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>
#include <param/param.h>
#include <extra/computeProperties.h>

void func_matrixCalculation(const Grid &grd, Matrix &mtr, const Param &prm,
                            const Properties &lmb,
                            const std::vector<double> &Xprev,
                            const double &dt);

#endif
