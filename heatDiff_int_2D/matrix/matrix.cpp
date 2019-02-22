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
                const Grid &grid) {

    int iCell = 0;
    int iMatrix = 0;

    for (int i = 0; i < grid.nX - 1; i++)
        fillMatrixExternalCell(matrix, coefficients, iCell, iMatrix);

    for (int i = 1; i < grid.nY - 2; i++) {
        fillMatrixExternalCell(matrix, coefficients, iCell, iMatrix);
        for (int j = 1; j < grid.nX - 2; j++)
            fillMatrixInternalCell(matrix, coefficients, iCell, iMatrix, grid);
        fillMatrixExternalCell(matrix, coefficients, iCell, iMatrix);
    }

    for (int i = 0; i < grid.nX - 1; i++)
        fillMatrixExternalCell(matrix, coefficients, iCell, iMatrix);

}


void fillMatrixExternalCell(Matrix &matrix, const Coefficients &coefficients,
                            int &iCell, int &iMatrix) {

    iCell++;
    iMatrix++;

    matrix.val[iMatrix - 1] = coefficients.C[iCell - 1];
    matrix.col[iMatrix - 1] = iCell - 1;
    matrix.poi[iCell] = iMatrix;

}


void fillMatrixInternalCell(Matrix &matrix, const Coefficients &coefficients,
                            int &iCell, int &iMatrix,
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

