#ifndef MATRIX_H
#define MATRIX_H

#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>
#include <param/param.h>
#include <properties/properties.h>

void computeMatrix(Matrix &matrix, const Grid &grid, const Param &param,
                   const Properties &properties,
                   const std::vector<double> &TPrevious);

Matrix initiateMatrix(const Grid & grid);

#endif
