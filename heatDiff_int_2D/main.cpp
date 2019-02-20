#include <string>

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

    Matrix matrix;

    Properties properties;

    for (double t = param.dt; t <= param.time; t += param.dt) {

        computeProperties(properties, propertyTables, grid, T);

        computeMatrix(grid, matrix, param, properties, T, param.dt);

        computeLSJacobi(matrix, param, T);
    }

    makePlot(grid, T);

    return 0;
}


