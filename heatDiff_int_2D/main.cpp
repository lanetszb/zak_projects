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
    auto thermalCond_table = dataFile.getWord<std::string>("THERMALCOND_TABLE");
    auto density_table = dataFile.getWord<std::string>("DENSITY_TABLE");
    auto heatCapacity_table = dataFile.getWord<std::string>("CAPACITY_TABLE");

    Grid grd;
    func_gridCalculation(grd, grdFileNm, nodesFileNm);

    // ***Numerical solution for heat diffusion begins here***

    Param prm;
    std::string dataFileName = arg[1];
    getParam(prm, grd, dataFileName);

    auto X = computeTInitial(grd.Ny, grd.Nx, prm.T0, prm.Tl, prm.Tr);

    Matrix mtr;

    Properties properties;
    computeProperties(mtr, prm, grd, X, thermalCond_table, density_table,
                      heatCapacity_table, properties);

    for (double t = prm.dt; t <= prm.time; t += prm.dt) {

        func_matrixCalculation(grd, mtr, prm, properties, X, prm.dt);

        computeLSJacobi(mtr, prm, X);
    }

    Plot plt;
    func_plot(grd, plt, X);

    return 0;
}


