#ifndef RANDOM_H
#define RANDOM_H

#include <param/param_struct.h>
#include <matrix/matrix_struct.h>
#include <grid/grid_struct.h>

struct Lamb {

    std::vector<std::vector<double> > lambTable;

    std::vector<std::vector<double> > densTable;

    std::vector<std::vector<double> > capacTable;

    std::vector<double> leftLamb;

    std::vector<double> rightLamb;

    std::vector<double> topLamb;

    std::vector<double> botLamb;

    std::vector<double> density;

};

void funcJacobi(const Matrix &mtr, const Param &prm, std::vector<double> &X);

void readLamb(Lamb &lmb, const std::string &thermalCond_table);

void readDens(Lamb &lmb, const std::string &density_table);

void readCapac(Lamb &lmb, const std::string &heatCapacity_table);

void getLeft_lamb(Lamb &lmb,
                  const Grid &grd, const std::vector<double> &X);

void getRight_lamb(Lamb &lmb,
                   const Grid &grd, const std::vector<double> &X);

void getTop_lamb(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X);

void getBot_lamb(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X);

void getDensity(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X);

#endif
