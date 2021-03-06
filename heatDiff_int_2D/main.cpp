#include <grid/grid.h>
#include <properties/properties.h>
#include <settings/settings.h>
#include <coefficients/coefficients.h>
#include <matrix/matrix.h>
#include <extra/computeTInitial.h>
#include <extra/jacobi.h>
#include <plot/plot.h>

#include <boost/progress.hpp>
#include <ColorConsole.h>
#include <iostream>


int main(int narg, char **arg) {


    auto grid = processGrid(arg[1]);
    auto settings = getSettings(arg[1]);
    auto propertyTables = getTables(arg[1]);

    auto matrix = initiateMatrix(grid);
    auto coefficients = initiateCoefficients(grid);
    auto properties = initializeProperties(grid);

    auto T = computeTInitial(grid, settings);


    boost::progress_timer timer;

    int number = settings.time / settings.dt;
    std::cout << blue;
    boost::progress_display progressBar(number);


    std::cout << green;
    for (double t = settings.dt; t <= settings.time; t += settings.dt) {
        ++progressBar;

        computeProperties(properties, propertyTables, T, grid);
        computeCoefficients(coefficients, grid, settings, properties, T);
        fillMatrix(matrix, coefficients, grid, T);

        solveJacobiLS(matrix, coefficients, settings, T);

    }

    std::cout << purple;
    std::cout << std::endl << "calculation time is ";


    makePlot(grid, T);

    return 0;

}


