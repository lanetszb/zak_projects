#include <vector>

#include <coefficients/coefficients.h>
#include <grid/grid.h>
#include <properties/properties.h>
#include <settings/settings.h>


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
                         const Settings &settings,
                         const Properties &properties,
                         const std::vector<double> &T) {

    computeA(coefficients, grid, properties);
    computeE(coefficients, grid, properties);
    computeB(coefficients, grid, properties);
    computeD(coefficients, grid, properties);
    computeF(coefficients, grid, settings, properties, T);
    computeC(coefficients, grid, settings, properties);


}


void computeA(Coefficients &coefficients, const Grid &grid,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)


        coefficients.A[i] = -properties.lambdaLeft[i] *
                            grid.surfaceLeft[i] / grid.LLeft[i];

}


void computeB(Coefficients &coefficients, const Grid &grid,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)


     coefficients.B[i] = -properties.lambdaBottom[i] *
                            grid.surfaceBottom[i] / grid.LBottom[i];

}


void computeC(Coefficients &coefficients,
              const Grid &grid,
              const Settings &settings,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)

        coefficients.C[i] = grid.cellsVolume[i] * properties.density[i] *
                            properties.capacity[i] / settings.dt
                            - coefficients.A[i] - coefficients.B[i]
                            - coefficients.D[i] - coefficients.E[i];

}


void computeD(Coefficients &coefficients, const Grid &grid,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)

        coefficients.D[i] = -properties.lambdaRight[i] *
                            grid.surfaceRight[i] / grid.LRight[i];

}


void computeE(Coefficients &coefficients, const Grid &grid,
              const Properties &properties) {

    for (int i = 0; i < grid.nCells; i++)

        coefficients.E[i] = -properties.lambdaTop[i] *
                            grid.surfaceTop[i] / grid.LTop[i];

}


void computeF(Coefficients &coefficients,
              const Grid &grid,
              const Settings &settings,
              const Properties &properties,
              const std::vector<double> &T) {

    for (int i = 0; i < grid.nCells; i++)
        coefficients.F[i] = -T[i] * grid.cellsVolume[i] * properties.density[i]
                            * properties.capacity[i] / settings.dt;

}
