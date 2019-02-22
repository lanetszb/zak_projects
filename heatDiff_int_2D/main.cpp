#include <string>

#include <coefficients/coefficients.h>
#include <grid/grid.h>
#include <plot/plot.h>
#include <properties/properties.h>
#include <extra/computeTInitial.h>
#include <matrix/matrix.h>
#include <param/param.h>
#include <extra/jacobi.h>


int main(int narg, char **arg) {

    auto inputFileName = std::string(arg[1]);

    Grid grid = getGrid(inputFileName);

    Param param = getParam(inputFileName);

    PropertyTables propertyTables = getTables(inputFileName);

    auto T = computeTInitial(grid, param);

    Matrix matrix = initiateMatrix(grid);

    Coefficients coefficients = initiateCoefficients(grid);

    Properties properties = initialiseProperties(grid);


    for (double t = param.dt; t <= param.time; t += param.dt) {

        computeProperties(properties, propertyTables, T, grid);
        computeCoefficients(coefficients, grid, param, properties, T);
        fillMatrix(matrix, coefficients, grid);

        computeLSJacobi(matrix, coefficients, param, T);
    }

    makePlot(grid, T);

    return 0;
}


