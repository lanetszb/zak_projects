#ifndef EXTRA_COMPUTEPROPERTIES_H
#define EXTRA_COMPUTEPROPERTIES_H

#include <vector>

#include <extra/properties.h>
#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>
#include <param/param_struct.h>


void readTables(Properties &properties,
                const std::string &lambdaTableName,
                const std::string &densityTableName,
                const std::string &capacityTableName);

void computeProperties(Properties &properties, const Grid &grid,
                       std::vector<double> &T);

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
