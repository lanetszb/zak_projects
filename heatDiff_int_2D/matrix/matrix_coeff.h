#ifndef MATRIX_MATRIX_COEFF_H
#define MATRIX_MATRIX_COEFF_H

#include <grid/grid_struct.h>
#include <matrix/matrix_struct.h>
#include <param.h>

void A_calc(Grid &grd, Matrix &mtr, Param &prm);

void B_calc(Grid &grd, Matrix &mtr, Param &prm);

void C_calc(Grid &grd, Matrix &mtr);

void D_calc(Grid &grd, Matrix &mtr, Param &prm);

void E_calc(Grid &grd, Matrix &mtr, Param &prm);

void F_calc(Grid &grd, Matrix &mtr, Param &prm);

#endif
