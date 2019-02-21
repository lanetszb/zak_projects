#ifndef MATRIXVECT_H
#define MATRIXVECT_H

#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>

void computeVal(Matrix &matrix, const Grid &grid);
void col_calc(const Grid &grd, Matrix &mtr);
void poi_calc(const Grid &grd, Matrix &mtr);

#endif
