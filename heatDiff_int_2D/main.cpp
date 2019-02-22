#include <grid/grid.h>
#include <properties/properties.h>
#include <param/param.h>
#include <coefficients/coefficients.h>
#include <matrix/matrix.h>
#include <extra/computeTInitial.h>
#include <extra/jacobi.h>
#include <plot/plot.h>


int main(int narg, char **arg) {

    auto grid = getGrid(arg[1]);
    auto param = getParam(arg[1]);
    auto propertyTables = getTables(arg[1]);

    auto matrix = initiateMatrix(grid);
    auto coefficients = initiateCoefficients(grid);
    auto properties = initialiseProperties(grid);

    auto T = computeTInitial(grid, param);

    for (double t = param.dt; t <= param.time; t += param.dt) {

        computeProperties(properties, propertyTables, T, grid);
        computeCoefficients(coefficients, grid, param, properties, T);
        fillMatrix(matrix, coefficients, grid);

        solveJacobiLS(matrix, coefficients, param, T);

    }

    makePlot(grid, T);

    return 0;

}


