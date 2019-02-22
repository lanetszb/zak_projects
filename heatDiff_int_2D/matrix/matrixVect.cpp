#include <matrix/matrixVect.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

void fillMatrixExternalCell(Matrix &matrix, int &iCell, int &iMatrix) {

    iCell++;
    iMatrix++;

    matrix.val[iMatrix - 1] = matrix.C[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - 1;
    matrix.poi[iCell] = iMatrix;

}


void fillMatrixInternalCell(Matrix &matrix, int &iCell, int &iMatrix,
                            const Grid &grid) {

    iCell++;


    iMatrix++;
    matrix.val[iMatrix - 1] = matrix.B[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - (grid.nX - 1) - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = matrix.A[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - 1 - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = matrix.C[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = matrix.D[iCell - 1];
    matrix.col[iMatrix - 1] = iCell + 1 - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = matrix.E[iCell - 1];
    matrix.col[iMatrix - 1] = iCell + (grid.nX - 1) - 1;


    matrix.poi[iCell] = iMatrix;

}

void fillMatrix(Matrix &matrix, const Grid &grid) {

    int iCell = 0;
    int iMatrix = 0;

    for (int i = 0; i < grid.nX - 1; i++)
        fillMatrixExternalCell(matrix, iCell, iMatrix);

    for (int i = 1; i < grid.nY - 2; i++) {
        fillMatrixExternalCell(matrix, iCell, iMatrix);
        for (int j = 1; j < grid.nX - 2; j++)
            fillMatrixInternalCell(matrix, iCell, iMatrix, grid);
        fillMatrixExternalCell(matrix, iCell, iMatrix);
    }

    for (int i = 0; i < grid.nX - 1; i++)
        fillMatrixExternalCell(matrix, iCell, iMatrix);

}


