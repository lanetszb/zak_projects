#ifndef MATRIXCOEFF_H
#define MATRIXCOEFF_H

#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>
#include <properties/properties.h>
#include <param/param.h>

void computeA(Matrix &matrix, const Grid &grid, const Param &param,
              const Properties &properties);

void computeB(Matrix &matrix, const Grid &grid, const Param &param,
              const Properties &properties);

void computeC(Matrix &matrix, const Grid &grid, const Param &param,
              const Properties &properties);

void computeD(Matrix &matrix, const Grid &grid, const Param &param,
              const Properties &properties);

void computeE(Matrix &matrix, const Grid &grid, const Param &param,
              const Properties &properties);

void computeF(Matrix &matrix, const Grid &grid, const Param &param,
              const Properties &properties,
              const std::vector<double> &TPrevious);

#endif
