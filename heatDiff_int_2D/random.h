#ifndef RANDOM_H
#define RANDOM_H

#include <param_struct.h>
#include <matrix/matrix_struct.h>
#include <grid/grid_struct.h>

struct Lamb {

    std::vector<std::vector<double> > lambTable;

    std::vector<double> leftLamb;

    std::vector<double> rightLamb;

    std::vector<double> topLamb;

    std::vector<double> botLamb;

};

void funcJacobi(const Matrix &mtr, const Param &prm, std::vector<double> &X);

void readLamb(Lamb &lmb, const std::string &thermalCond_table);

void getLeft_lamb(Lamb &lmb,
                  const Grid &grd, const std::vector<double> &X);

void getRight_lamb(Lamb &lmb,
                  const Grid &grd, const std::vector<double> &X);

#endif
