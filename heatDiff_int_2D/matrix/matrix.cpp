#include <matrix/matrix.h>
#include <coefficients/coefficients.h>


Matrix initiateMatrix(const Grid &grid) {

    Matrix matrix;

    int matrixSize = grid.nCells;
    int valSize = grid.nCells + 4 * ((grid.nX - 3) * (grid.nY - 3));

    matrix.val = std::vector<double>(valSize, 0);
    matrix.col = std::vector<int>(valSize, 0);
    matrix.poi = std::vector<int>(matrixSize + 1, 0);

    return matrix;
}


void fillMatrix(Matrix &matrix, const Coefficients &coefficients,
                const Grid &grid, const std::vector<double> &T) {

    int iCell = 0;
    int iMatrix = 0;

    for (int i = 0; i < grid.nX - 1; i++)
        fillMatrixExternalCell(matrix, iCell, iMatrix, coefficients, T);

    for (int i = 1; i < grid.nY - 2; i++) {

        fillMatrixExternalCell(matrix, iCell, iMatrix, coefficients, T);

        for (int j = 1; j < grid.nX - 2; j++)
            fillMatrixInternalCell(matrix, iCell, iMatrix, coefficients, grid);

        fillMatrixExternalCell(matrix, iCell, iMatrix, coefficients, T);
    }

    for (int i = 0; i < grid.nX - 1; i++)
        fillMatrixExternalCell(matrix, iCell, iMatrix, coefficients, T);

}


void fillMatrixExternalCell(Matrix &matrix, int &iCell, int &iMatrix,
                            const Coefficients &coefficients,
                            const std::vector<double> &T) {

    iCell++;
    iMatrix++;

    matrix.val[iMatrix - 1] = -coefficients.F[iCell - 1] / T[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - 1;
    matrix.poi[iCell] = iMatrix;

}


void fillMatrixInternalCell(Matrix &matrix, int &iCell, int &iMatrix,
                            const Coefficients &coefficients,
                            const Grid &grid) {

    iCell++;


    iMatrix++;
    matrix.val[iMatrix - 1] = coefficients.B[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - (grid.nX - 1) - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = coefficients.A[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - 1 - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = coefficients.C[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = coefficients.D[iCell - 1];
    matrix.col[iMatrix - 1] = iCell + 1 - 1;

    iMatrix++;
    matrix.val[iMatrix - 1] = coefficients.E[iCell - 1];
    matrix.col[iMatrix - 1] = iCell + (grid.nX - 1) - 1;


    matrix.poi[iCell] = iMatrix;

}

