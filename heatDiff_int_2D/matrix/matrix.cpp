#include <matrix/matrix.h>
#include <matrix/matrix_vect.h>
#include <matrix/matrix_coeff.h>
#include <iostream>

void func_matrixCalculation(const Grid &grd, Matrix &mtr, const Param &prm,
                            const std::vector<double> &Xprev) {

    A_calc(grd, mtr, prm);

    E_calc(grd, mtr, prm);

    B_calc(grd, mtr, prm);

    D_calc(grd, mtr, prm);

    F_calc(grd, mtr, prm, Xprev);

    C_calc(grd, mtr, prm);

    val_calc(grd, mtr);

    col_calc(grd, mtr);

    poi_calc(grd, mtr);
}
