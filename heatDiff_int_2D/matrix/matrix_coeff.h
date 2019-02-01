#ifndef MATRIX_MATRIX_COEFF_H
#define MATRIX_MATRIX_COEFF_H

#include <grid/grid_struct.h>
#include <matrix/matrix_struct.h>
#include <random.h>
#include <param.h>

void A_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb);

void B_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb);

void C_calc(const Grid &grd, Matrix &mtr, const Param &prm, const double &dt);

void D_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb);

void E_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb);

void F_calc(const Grid &grd, Matrix &mtr, const Param &prm,
            const std::vector<double> &Xprev, const double &dt);

#endif
