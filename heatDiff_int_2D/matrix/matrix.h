#ifndef MATRIX_H
#define MATRIX_H

#include <grid/gridStruct.h>
#include <param/param.h>
#include <properties/properties.h>
#include <coefficients/coefficients.h>


struct Matrix {

    std::vector<double> val;
    std::vector<int> col;
    std::vector<int> poi;

};

Matrix initiateMatrix(const Grid &grid);

void fillMatrix(Matrix &matrix, const Coefficients &coefficients,
                const Grid &grid);

void fillMatrixExternalCell(Matrix &matrix, const Coefficients &coefficients,
                            int &iCell, int &iMatrix);

void fillMatrixInternalCell(Matrix &matrix, const Coefficients &coefficients,
                            int &iCell, int &iMatrix,
                            const Grid &grid);

#endif
