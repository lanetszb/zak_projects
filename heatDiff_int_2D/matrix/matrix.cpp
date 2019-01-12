#include <matrix/matrix.h>
#include <matrix/matrix_vect.h>
#include <matrix/matrix_coeff.h>
#include <iostream>

void func_matrixCalculation(Grid &grd, Matrix &mtr, Param &prm,
                            std::vector<double> &getBot_lambda,
                            std::vector<double> &getTop_lambda,
                            std::vector<double> &getLeft_lambda,
                            std::vector<double> &getRight_lambda) {

    A_calc(grd, mtr, getBot_lambda);

    E_calc(grd, mtr, getTop_lambda);

    B_calc(grd, mtr, getLeft_lambda);

    D_calc(grd, mtr, getRight_lambda);

    F_calc(grd, mtr, prm);

    C_calc(grd, mtr);

    val_calc(grd, mtr);

    col_calc(grd, mtr);

    poi_calc(grd, mtr);

}
