#ifndef MATRIX_H
#define MATRIX_H

#include <grid/grid_struct.h>
#include <matrix/matrix_struct.h>
#include <param.h>

void func_matrixCalculation(Grid &grd, Matrix &mtr, Param &prm,
                            std::vector<double> &getBot_lambda,
                            std::vector<double> &getTop_lambda,
                            std::vector<double> &getLeft_lambda,
                            std::vector<double> &getRight_lambda);

#endif
