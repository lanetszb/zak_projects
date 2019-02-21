#include <matrix/matrixCoeff.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>


void computeA(Matrix &matrix,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0; i < grid.gridN; i++)
        matrix.A[i] = (-1 * properties.lambdaBottom[i] * grid.omegaBot[i]) /
                      grid.getBot_dL[i];

    for (int i = 0; i < (grid.nX - 2); i++)
        matrix.A[i] = 0;

    for (int i = (grid.nX - 1);
         i < matrix.A.size() - (grid.nX - 2); i += grid.nX - 1)
        matrix.A[i] = 0;

    for (int i = matrix.A.size() - (grid.nX - 2);
         i < matrix.A.size(); i++)
        matrix.A[i] = 0;

    for (int i = (grid.nX - 2);
         i < matrix.A.size() - (grid.nX - 1); i += grid.nX - 1)
        matrix.A[i] = 0;

}

void computeB(Matrix &matrix,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int j = 0, i = 0; i < grid.gridN; i++)
        matrix.B[i] =
                (-1 * properties.lambdaLeft[i] * grid.omegaLeft[i]) /
                grid.getLeft_dL[i];

    for (int i = 0; i < (grid.nX - 2); i++)
        matrix.B[i] = 0;

    for (int i = (grid.nX - 1);
         i < matrix.B.size() - (grid.nX - 2); i += grid.nX - 1)
        matrix.B[i] = 0;

    for (int i = matrix.B.size() - (grid.nX - 2);
         i < matrix.B.size(); i++)
        matrix.B[i] = 0;

    for (int i = (grid.nX - 2);
         i < matrix.B.size() - (grid.nX - 1); i += grid.nX - 1)
        matrix.B[i] = 0;

}


void computeC(Matrix &matrix,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0; i < grid.gridN; i++)
        matrix.C[i] = (grid.gridVolume[i] * properties.density[i] *
                       properties.capacity[i] / param.dt) +
                      (-1 * matrix.A[i]) + (-1 * matrix.B[i]) +
                      (-1 * matrix.D[i]) +
                      (-1 * matrix.E[i]);

    for (int i = 0; i < (grid.nX - 2); i++)
        matrix.C[i] = grid.gridVolume[i] * properties.density[i] *
                      properties.capacity[i] / param.dt;

    for (int i = (grid.nX - 1);
         i < matrix.C.size() - (grid.nX - 2); i += grid.nX - 1)
        matrix.C[i] = grid.gridVolume[i] * properties.density[i] *
                      properties.capacity[i] / param.dt;

    for (int i = matrix.C.size() - (grid.nX - 2);
         i < matrix.C.size(); i++)
        matrix.C[i] = grid.gridVolume[i] * properties.density[i] *
                      properties.capacity[i] / param.dt;

    for (int i = (grid.nX - 2);
         i < matrix.C.size() - (grid.nX - 1); i += grid.nX - 1)
        matrix.C[i] = grid.gridVolume[i] * properties.density[i] *
                      properties.capacity[i] / param.dt;
}


void computeD(Matrix &matrix,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0; i < grid.gridN; i++)
        matrix.D[i] = (-1 * properties.lambdaRight[i] * grid.omegaRight[i]) /
                      grid.getRight_dL[i];

    for (int i = 0; i < (grid.nX - 2); i++)
        matrix.D[i] = 0;

    for (int i = (grid.nX - 1);
         i < matrix.D.size() - (grid.nX - 2); i += grid.nX - 1)
        matrix.D[i] = 0;

    for (int i = matrix.D.size() - (grid.nX - 2);
         i < matrix.D.size(); i++)
        matrix.D[i] = 0;

    for (int i = (grid.nX - 2);
         i < matrix.D.size() - (grid.nX - 1); i += grid.nX - 1)
        matrix.D[i] = 0;
}


void computeE(Matrix &matrix,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0; i < grid.gridN; i++)
        matrix.E[i] = (-1 * properties.lambdaTop[i] * grid.omegaTop[i]) /
                      grid.getTop_dL[i];

    for (int i = 0; i < (grid.nX - 2); i++)
        matrix.E[i] = 0;

    for (int i = (grid.nX - 1);
         i < matrix.E.size() - (grid.nX - 2); i += grid.nX - 1)
        matrix.E[i] = 0;

    for (int i = matrix.E.size() - (grid.nX - 2);
         i < matrix.E.size(); i++)
        matrix.E[i] = 0;

    for (int i = (grid.nX - 2);
         i < matrix.E.size() - (grid.nX - 1); i += grid.nX - 1)
        matrix.E[i] = 0;

}


void computeF(Matrix &matrix,
              const Grid &grid,
              const Param &param,
              const Properties &properties,
              const std::vector<double> &TPrevious) {

    for (int i = 0; i < grid.gridN; i++)
        matrix.F[i] = TPrevious[i] *
                      (-1 * grid.gridVolume[i] * properties.density[i] *
                       properties.capacity[i]) /
                      param.dt;
}



