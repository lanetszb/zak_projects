#ifndef EXTRA_COMPUTEPROPERTIES_H
#define EXTRA_COMPUTEPROPERTIES_H

#include <vector>

#include <extra/properties.h>
#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>
#include <param/param_struct.h>


void computeProperties(const Matrix &mtr, const Param &prm, const Grid &grd,
                       std::vector<double> &T,
                       const std::string &lambdaTable,
                       const std::string &densityTable,
                       const std::string &capacityTable,
                       Properties &properties);

void computeLambLeft(Properties &properties, const Grid &grd,
                     const std::vector<double> &T);

void computeLambRight(Properties &properties, const Grid &grd,
                      const std::vector<double> &T);

void computeLambTop(Properties &properties, const Grid &grd,
                    const std::vector<double> &T);

void computeLambBot(Properties &properties, const Grid &grd,
                    const std::vector<double> &T);

void computeDensity(Properties &properties, const Grid &grd,
                    const std::vector<double> &T);

void computeCapacity(Properties &properties, const Grid &grd,
                     const std::vector<double> &T);

#endif
