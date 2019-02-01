#include <matrix/matrix.h>
#include <matrix/matrix_vect.h>
#include <matrix/matrix_coeff.h>
#include <iostream>

void func_matrixCalculation(const Grid &grd, Matrix &mtr, const Param &prm,
                            const Lamb &lmb,
                            const std::vector<double> &Xprev,
                            const double &dt) {

    A_calc(grd, mtr, prm, lmb);

    E_calc(grd, mtr, prm, lmb);

    B_calc(grd, mtr, prm, lmb);

    D_calc(grd, mtr, prm, lmb);

    F_calc(grd, mtr, prm, Xprev, dt);

    C_calc(grd, mtr, prm, dt);

    val_calc(grd, mtr);

    col_calc(grd, mtr);

    poi_calc(grd, mtr);
}
