#include <vector>

#include <grid/grid.h>
#include <plot/plot.h>
#include <properties/properties.h>
#include <extra/computeTInitial.h>
#include <matrix/matrix.h>
#include <param/param.h>
#include <extra/jacobi.h>

#include <string>


int main(int narg, char **arg) {

    auto fileName = std::string(arg[1]);

    Grid grid = getGrid(fileName);

    Param param = getParam(fileName);

    PropertyTables propertyTables = getTables(fileName);

    auto T = computeTInitial(grid, param);

    Matrix matrix;

    Properties properties;

    for (double t = param.dt; t <= param.time; t += param.dt) {

        computeProperties(properties, propertyTables, grid, T);

        computeMatrix(grid, matrix, param, properties, T, param.dt);

        computeLSJacobi(matrix, param, T);
    }

    Plot plot;
    func_plot(grid, plot, T);

    return 0;
}


