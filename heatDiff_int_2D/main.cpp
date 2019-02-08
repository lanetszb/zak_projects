#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <grid/grid.h>
#include <plot/plot.h>
#include <random.h>
#include <matrix/matrix.h>
#include <param/param.h>


std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                         const double &T0, const double &Tl,
                                         const double &Tr);

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

    auto X = func_heatDistrib_ini(grd.Ny, grd.Nx, prm.T0, prm.Tl, prm.Tr);

    Lamb lmb;
    readLamb(lmb, thermalCond_table);
    readDens(lmb, density_table);
    readCapac(lmb, heatCapacity_table);

    getLeft_lamb(lmb, grd, X);
    getRight_lamb(lmb, grd, X);
    getTop_lamb(lmb, grd, X);
    getBot_lamb(lmb, grd, X);

    getDensity(lmb, grd, X);
    getCapacity(lmb, grd, X);

    Matrix mtr;

    for (double t = prm.dt; t <= prm.time; t += prm.dt) {

        func_matrixCalculation(grd, mtr, prm, lmb, X, prm.dt);

        funcJacobi(mtr, prm, X);
    }

    Plot plt;
    func_plot(grd, plt, X);

    return 0;
}

//***all the functions are listed below***

std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                         const double &T0, const double &Tl,
                                         const double &Tr) {

    int gridN = (Nx - 1) * (Ny - 1);
    std::vector<double> heatDistrib_ini(gridN, T0);


    for (int i = 2 * (Nx - 2) + 1;
         i < heatDistrib_ini.size() - (Nx - 1); i += Nx - 1)
        heatDistrib_ini[i] = Tr;

    for (int i = 0; i < Nx - 1; i++)
        heatDistrib_ini[i] = Tl;

    for (int i = heatDistrib_ini.size() - (Nx - 1);
         i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = Tr;

    for (int i = (Nx - 1);
         i < heatDistrib_ini.size() - (Nx - 1); i += Nx - 1)
        heatDistrib_ini[i] = Tl;


    return heatDistrib_ini;
}

