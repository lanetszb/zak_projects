#include <matrix/matrixVect.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

void fillVal(Matrix &matrix, const Grid &grid) {

    int iCell = 0;
    int iMatrix = 0;


    for (int i = 0; i < grid.nX - 1; i++) {
        iCell++;
        iMatrix++;
        matrix.val[iMatrix - 1] = matrix.C[iCell - 1];
    }


    for (int i = 1; i < grid.nY - 2; i++) {

        iCell++;
        iMatrix++;
        matrix.val[iMatrix - 1] = matrix.C[iCell - 1];

        for (int j = 1; j < grid.nX - 2; j++) {

            iCell++;

            iMatrix++;
            matrix.val[iMatrix - 1] = matrix.B[iCell - 1];
            iMatrix++;
            matrix.val[iMatrix - 1] = matrix.A[iCell - 1];
            iMatrix++;
            matrix.val[iMatrix - 1] = matrix.C[iCell - 1];
            iMatrix++;
            matrix.val[iMatrix - 1] = matrix.D[iCell - 1];
            iMatrix++;
            matrix.val[iMatrix - 1] = matrix.E[iCell - 1];

        }

        iCell++;
        iMatrix++;
        matrix.val[iMatrix - 1] = matrix.C[iCell - 1];

    }


    for (int i = 0; i < grid.nX - 1; i++) {
        iCell++;
        iMatrix++;
        matrix.val[iMatrix - 1] = matrix.C[iCell - 1];
    }

}


void fillCol(Matrix &matrix, const Grid &grid) {

    int iCell = 0;
    int iMatrix = 0;


    for (int i = 0; i < grid.nX - 1; i++) {
        iCell++;
        iMatrix++;
        matrix.col[iMatrix - 1] = iCell - 1;
    }


    for (int i = 1; i < grid.nY - 2; i++) {

        iCell++;
        iMatrix++;
        matrix.col[iMatrix - 1] = iCell - 1;

        for (int j = 1; j < grid.nX - 2; j++) {

            iCell++;

            iMatrix++;
            matrix.col[iMatrix - 1] = iCell - (grid.nX - 1) - 1;
            iMatrix++;
            matrix.col[iMatrix - 1] = iCell - 1 - 1;
            iMatrix++;
            matrix.col[iMatrix - 1] = iCell - 1;
            iMatrix++;
            matrix.col[iMatrix - 1] = iCell + 1 - 1;
            iMatrix++;
            matrix.col[iMatrix - 1] = iCell + (grid.nX - 1) - 1;

        }

        iCell++;
        iMatrix++;
        matrix.col[iMatrix - 1] = iCell - 1;

    }


    for (int i = 0; i < grid.nX - 1; i++) {
        iCell++;
        iMatrix++;
        matrix.col[iMatrix - 1] = iCell - 1;
    }
}


void fillPoi(Matrix &matrix, const Grid &grid) {

    int iCell = 0;
    int iMatrix = 0;

    matrix.poi[0] = 0;

    for (int i = 0; i < grid.nX - 1; i++) {
        iCell++;
        iMatrix++;
        matrix.poi[iCell] = iMatrix;
    }

    for (int i = 1; i < grid.nY - 2; i++) {

        iCell++;
        iMatrix++;
        matrix.poi[iCell] = iMatrix;

        for (int j = 1; j < grid.nX - 2; j++) {

            iCell++;

            iMatrix++;
            iMatrix++;
            iMatrix++;
            iMatrix++;
            iMatrix++;

            matrix.poi[iCell] = iMatrix;
        }

        iCell++;
        iMatrix++;
        matrix.poi[iCell] = iMatrix;

    }

    for (int i = 0; i < grid.nX - 1; i++) {
        iCell++;
        iMatrix++;
        matrix.poi[iCell] = iMatrix;
    }


}
