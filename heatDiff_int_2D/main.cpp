#include <grid/grid.h>
#include <properties/properties.h>
#include <settings/settings.h>
#include <coefficients/coefficients.h>
#include <matrix/matrix.h>
#include <extra/computeTInitial.h>
#include <extra/jacobi.h>
#include <plot/plot.h>


int main(int narg, char **arg) {

    auto grid = getGrid(arg[1]);
    auto settings = getSettings(arg[1]);
    auto propertyTables = getTables(arg[1]);

    auto matrix = initiateMatrix(grid);
    auto coefficients = initiateCoefficients(grid);
    auto properties = initializeProperties(grid);

    auto T = computeTInitial(grid, settings);

    for (double t = settings.dt; t <= settings.time; t += settings.dt) {

        computeProperties(properties, propertyTables, T, grid);
        computeCoefficients(coefficients, grid, settings, properties, T);
        fillMatrix(matrix, coefficients, grid);

        solveJacobiLS(matrix, coefficients, settings, T);

    }

    makePlot(grid, T);

    return 0;

}


