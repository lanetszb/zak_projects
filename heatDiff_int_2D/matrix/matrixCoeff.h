#ifndef MATRIX_COEFF_H
#define MATRIX_COEFF_H

#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>
#include <extra/computeProperties.h>
#include <param/param.h>

void A_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Properties &lmb);

void B_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Properties &lmb);

void C_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Properties &lmb,
            const double &dt);

void D_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Properties &lmb);

void E_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Properties &lmb);

void F_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Properties &lmb,
            const std::vector<double> &Xprev, const double &dt);

#endif
