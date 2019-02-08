#ifndef RANDOM_H
#define RANDOM_H

#include <param/param_struct.h>
#include <matrix/matrix_struct.h>
#include <grid/grid_struct.h>
#include <extra/extraData_struct.h>
#include <extra/extraData_read.h>
#include <extra/extraData_param.h>



void getExtra(const Matrix &mtr, const Param &prm, const Grid &grd,
              std::vector<double> &X,
              const std::string &thermalCond_table,
              const std::string &density_table,
              const std::string &heatCapacity_table, Lamb &lmb);

void funcJacobi(const Matrix &mtr, const Param &prm, std::vector<double> &X);

#endif
