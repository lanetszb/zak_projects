#include <matrix/matrix.h>
#include <matrix/matrixVect.h>
#include <matrix/matrixCoeff.h>

#include <iostream>

void computeMatrix(Matrix &matrix,
                   const Grid &grid,
                   const Param &param,
                   const Properties &properties,
                   const std::vector<double> &TPrevious) {

    computeA(matrix, grid, param, properties);
    computeE(matrix, grid, param, properties);
    computeB(matrix, grid, param, properties);
    computeD(matrix, grid, param, properties);
    computeF(matrix, grid, param, properties, TPrevious);
    computeC(matrix, grid, param, properties);

    fillMatrix(matrix, grid);

}


Matrix initiateMatrix(const Grid &grid) {

    Matrix matrix;

    int matrixSize = grid.nCells;
    int valSize = grid.nCells + 4 * ((grid.nX - 3) * (grid.nY - 3));
    auto templateVector = std::vector<double>(matrixSize, 0);

    matrix.A = templateVector;
    matrix.B = templateVector;
    matrix.C = templateVector;
    matrix.D = templateVector;
    matrix.E = templateVector;
    matrix.F = templateVector;

    matrix.val = std::vector<double>(valSize, 0);
    matrix.col = std::vector<int>(valSize, 0);
    matrix.poi = std::vector<int>(matrixSize + 1, 0);

    return matrix;
}
