#ifndef MATRIX_MATRIX_COEFF_H
#define MATRIX_MATRIX_COEFF_H

#include <grid/grid_struct.h>
#include <matrix/matrix_struct.h>
#include <param.h>

void A_calc(const Grid &grd, Matrix &mtr, const Param &prm);

void B_calc(const Grid &grd, Matrix &mtr, const Param &prm);

void C_calc(const Grid &grd, Matrix &mtr, const Param &prm);

void D_calc(const Grid &grd, Matrix &mtr, const Param &prm);

void E_calc(const Grid &grd, Matrix &mtr, const Param &prm);

void F_calc(const Grid &grd, Matrix &mtr, const Param &prm,
            const std::vector<double> &Xprev);

#endif
