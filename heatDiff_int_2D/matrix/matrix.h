#ifndef MATRIX_H
#define MATRIX_H

#include <grid/grid.h>
#include <settings/settings.h>
#include <properties/properties.h>
#include <coefficients/coefficients.h>


struct Matrix {

    std::vector<double> val;
    std::vector<int> col;
    std::vector<int> poi;

};

Matrix initiateMatrix(const Grid &grid);

void fillMatrix(Matrix &matrix, const Coefficients &coefficients,
                const Grid &grid, const std::vector<double> &T);

void fillMatrixExternalCell(Matrix &matrix, int &iCell, int &iMatrix,
                            const Coefficients &coefficients,
                            const std::vector<double> &T);

void fillMatrixInternalCell(Matrix &matrix, int &iCell, int &iMatrix,
                            const Coefficients &coefficients,
                            const Grid &grid);

#endif
