#ifndef COEFF_H
#define COEFF_H

#include <grid/grid_struct.h>
#include <matrix_struct.h>
#include <param.h>

void A_calc(Grid &grd, Matrix &mtr, std::vector<double> &getBot_lambda);
void B_calc(Grid &grd, Matrix &mtr,std::vector<double> &getLeft_lambda);
void C_calc(Grid &grd, Matrix &mtr);
void D_calc(Grid &grd, Matrix &mtr, std::vector<double> &getRight_lambda);
void E_calc(Grid &grd, Matrix &mtr,std::vector<double> &getTop_lambda);
void F_calc(Grid &grd, Matrix &mtr, Param &prm);

#endif
