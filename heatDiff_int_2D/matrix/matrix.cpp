#include <matrix/matrix.h>
#include <matrix/matrixVect.h>
#include <matrix/matrixCoeff.h>

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

    computeVal(matrix, grid);

    col_calc(grid, matrix);

    poi_calc(grid, matrix);
}


Matrix initiateMatrix(const Grid &grid) {

    Matrix matrix;

    auto templateVector = std::vector<double>(grid.gridN, 0);

    matrix.A = templateVector;
    matrix.B = templateVector;
    matrix.C = templateVector;
    matrix.D = templateVector;
    matrix.E = templateVector;
    matrix.F = templateVector;

    return matrix;
}
