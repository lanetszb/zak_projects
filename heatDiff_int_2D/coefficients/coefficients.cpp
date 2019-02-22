#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

#include <coefficients/coefficients.h>


Coefficients initiateCoefficients(const Grid &grid) {

    Coefficients coefficients;

    int matrixSize = grid.nCells;
    auto templateVector = std::vector<double>(matrixSize, 0);

    coefficients.A = templateVector;
    coefficients.B = templateVector;
    coefficients.C = templateVector;
    coefficients.D = templateVector;
    coefficients.E = templateVector;
    coefficients.F = templateVector;
    
    return coefficients;
}


void computeCoefficients(Coefficients &coefficients, const Grid &grid,
                         const Param &param,
                         const Properties &properties,
                         const std::vector<double> &T) {

    computeA(coefficients, grid, param, properties);
    computeE(coefficients, grid, param, properties);
    computeB(coefficients, grid, param, properties);
    computeD(coefficients, grid, param, properties);
    computeF(coefficients, grid, param, properties, T);
    computeC(coefficients, grid, param, properties);


}

void computeA(Coefficients &coefficients,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)

        coefficients.A[i] = -properties.lambdaBottom[i] * grid.omegaBot[i] /
                            grid.getBot_dL[i];


    for (int i = 0; i < (grid.nX - 2); i++)

        coefficients.A[i] = 0;


    for (int i = (grid.nX - 1);
         i < coefficients.A.size() - (grid.nX - 2); i += grid.nX - 1)

        coefficients.A[i] = 0;


    for (int i = coefficients.A.size() - (grid.nX - 2);
         i < coefficients.A.size(); i++)

        coefficients.A[i] = 0;


    for (int i = (grid.nX - 2);
         i < coefficients.A.size() - (grid.nX - 1); i += grid.nX - 1)

        coefficients.A[i] = 0;

}


void computeB(Coefficients &coefficients,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0;
         i < grid.nCells; i++)

        coefficients.B[i] = -properties.lambdaLeft[i] * grid.omegaLeft[i] /
                            grid.getLeft_dL[i];


    for (int i = 0;
         i < (grid.nX - 2); i++)

        coefficients.B[i] = 0;


    for (int i = (grid.nX - 1);
         i < coefficients.B.size() - (grid.nX - 2); i += grid.nX - 1)

        coefficients.B[i] = 0;


    for (int i = coefficients.B.size() - (grid.nX - 2);
         i < coefficients.B.size(); i++)

        coefficients.B[i] = 0;


    for (int i = (grid.nX - 2);
         i < coefficients.B.size() - (grid.nX - 1); i += grid.nX - 1)

        coefficients.B[i] = 0;

}


void computeC(Coefficients &coefficients,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)

        coefficients.C[i] = grid.gridVolume[i] * properties.density[i] *
                            properties.capacity[i] / param.dt
                            - coefficients.A[i] - coefficients.B[i]
                            - coefficients.D[i] - coefficients.E[i];


    for (int i = 0; i < (grid.nX - 2); i++)

        coefficients.C[i] = grid.gridVolume[i] * properties.density[i] *
                            properties.capacity[i] / param.dt;


    for (int i = (grid.nX - 1);
         i < coefficients.C.size() - (grid.nX - 2); i += grid.nX - 1)

        coefficients.C[i] = grid.gridVolume[i] * properties.density[i] *
                            properties.capacity[i] / param.dt;


    for (int i = coefficients.C.size() - (grid.nX - 2);
         i < coefficients.C.size(); i++)

        coefficients.C[i] = grid.gridVolume[i] * properties.density[i] *
                            properties.capacity[i] / param.dt;


    for (int i = (grid.nX - 2);
         i < coefficients.C.size() - (grid.nX - 1); i += grid.nX - 1)

        coefficients.C[i] = grid.gridVolume[i] * properties.density[i] *
                            properties.capacity[i] / param.dt;

}


void computeD(Coefficients &coefficients,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)
        coefficients.D[i] = -properties.lambdaRight[i] * grid.omegaRight[i] /
                            grid.getRight_dL[i];

    for (int i = 0; i < (grid.nX - 2); i++)
        coefficients.D[i] = 0;

    for (int i = (grid.nX - 1);
         i < coefficients.D.size() - (grid.nX - 2); i += grid.nX - 1)
        coefficients.D[i] = 0;

    for (int i = coefficients.D.size() - (grid.nX - 2);
         i < coefficients.D.size(); i++)
        coefficients.D[i] = 0;

    for (int i = (grid.nX - 2);
         i < coefficients.D.size() - (grid.nX - 1); i += grid.nX - 1)
        coefficients.D[i] = 0;
}


void computeE(Coefficients &coefficients,
              const Grid &grid,
              const Param &param,
              const Properties &properties) {

    for (int i = 0;
         i < grid.nCells; i++)

        coefficients.E[i] = (-1 * properties.lambdaTop[i] * grid.omegaTop[i]) /
                            grid.getTop_dL[i];


    for (int i = 0;
         i < (grid.nX - 2); i++)

        coefficients.E[i] = 0;


    for (int i = (grid.nX - 1);
         i < coefficients.E.size() - (grid.nX - 2); i += grid.nX - 1)

        coefficients.E[i] = 0;


    for (int i = coefficients.E.size() - (grid.nX - 2);
         i < coefficients.E.size(); i++)

        coefficients.E[i] = 0;


    for (int i = (grid.nX - 2);
         i < coefficients.E.size() - (grid.nX - 1); i += grid.nX - 1)

        coefficients.E[i] = 0;

}


void computeF(Coefficients &coefficients,
              const Grid &grid,
              const Param &param,
              const Properties &properties,
              const std::vector<double> &T) {

    for (int i = 0; i < grid.nCells; i++)
        coefficients.F[i] = -T[i] * grid.gridVolume[i] * properties.density[i]
                            * properties.capacity[i] / param.dt;

}
