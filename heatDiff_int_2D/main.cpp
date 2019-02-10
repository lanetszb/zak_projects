#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

#include <GetFromFile.h>

#include <grid/grid.h>
#include <plot/plot.h>
#include <extra/computeProperties.h>
#include <extra/readProperties.h>
#include <matrix/matrix.h>
#include <param/param.h>
#include <extra/jacobi.h>


int main(int narg, char **arg) {

    // ***reading the required input data***
    GetFromFile dataFile(arg[1]);

    auto grdFileNm = dataFile.getWord<std::string>("GRID_DATA");
    auto nodesFileNm = dataFile.getWord<std::string>("NODES_NUM");
    auto lambdaTableName = dataFile.getWord<std::string>("THERMALCOND_TABLE");
    auto densityTableName = dataFile.getWord<std::string>("DENSITY_TABLE");
    auto capacityTableName = dataFile.getWord<std::string>("CAPACITY_TABLE");

    Grid grid;
    func_gridCalculation(grid, grdFileNm, nodesFileNm);

    // ***Numerical solution for heat diffusion begins here***

    Param prm;
    std::string dataFileName = arg[1];
    getParam(prm, grid, dataFileName);

    auto T = computeTInitial(grid.nY, grid.nX, prm.TInitial,
                             prm.TLeft, prm.TRight);

    Matrix mtr;

    Properties properties;
    readTables(properties, lambdaTableName, densityTableName,
               capacityTableName);



    for (double t = prm.dt; t <= prm.time; t += prm.dt) {

        computeProperties(properties, grid, T);

        func_matrixCalculation(grid, mtr, prm, properties, T, prm.dt);

        computeLSJacobi(mtr, prm, T);
    }



    Plot plt;
    func_plot(grid, plt, T);

    return 0;
}


