#ifndef MATRIXVECT_H
#define MATRIXVECT_H

#include <grid/gridStruct.h>
#include <matrix/matrixStruct.h>

void fillMatrixExternalCell(Matrix &matrix, int &iCell, int &iMatrix);
void fillMatrixInternalCell(Matrix &matrix, int &iCell, int &iMatrix,
                            const Grid &grid);
void fillMatrix(Matrix &matrix, const Grid &grid);

#endif
