#include <matrix.h>
#include <matrix_vect.h>
#include <matrix_coeff.h>

void func_matrixCalculation(Grid &grd, Matrix &mtr, Param &prm,
                            std::vector<double> &getBot_lambda,
                            std::vector<double> &getTop_lambda,
                            std::vector<double> &getLeft_lambda,
                            std::vector<double> &getRight_lambda) {

    val_calc(grd, mtr);

    cal_calc(grd, mtr);

    poi_calc(grd, mtr);

    A_calc(grd, mtr, getBot_lambda);

    E_calc(grd, mtr, getTop_lambda);

    B_calc(grd, mtr, getLeft_lambda);

    D_calc(grd, mtr, getRight_lambda);

    F_calc(grd, mtr, prm);

    C_calc(grd, mtr);

}
