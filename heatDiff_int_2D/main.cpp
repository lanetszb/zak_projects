#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <grid/grid.h>
#include <plot/plot.h>
#include <matrix/matrix.h>
#include <param.h>

//
std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                         const double &T0, const double &Tl,
                                         const double &Tr);


int main(int narg, char **arg) {

    // ***reading the required input data***
    GetFromFile dataFile(arg[1]);



    auto grdFileNm = dataFile.getWord<std::string>("GRID_DATA");
    auto nodesFileNm = dataFile.getWord<std::string>("NODES_NUM");

    Grid grd;

    func_gridCalculation(grd, grdFileNm, nodesFileNm);
    // ***Numerical solution for heat diffusion begins here***

    Param prm;
    std::string dataFileName = arg[1];
    getParam(prm, grd, dataFileName);

    // Temp vector

    auto heatDistr_ini = func_heatDistrib_ini(grd.Ny, grd.Nx, prm.T0, prm.Tl,
                                              prm.Tr);


    Plot plt;

    // func_plot(grd, plt, heatDistr_ini);

    Matrix mtr;

    func_matrixCalculation(grd, mtr, prm);

    return 0;

}


//***all the functions are listed below***

std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                         const double &T0, const double &Tl,
                                         const double &Tr) {

    int gridN = (Nx - 1) * (Ny - 1);
    std::vector<double> heatDistrib_ini(gridN, T0);

    for (int i = 0; i < (Nx - 2); i++)
        heatDistrib_ini[i] = Tl;

    for (int i = (Nx - 1);
         i < heatDistrib_ini.size() - (Nx - 2); i += Nx - 1)
        heatDistrib_ini[i] = Tl;

    for (int i = heatDistrib_ini.size() - (Nx - 2);
         i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = Tr;

    for (int i = (Nx - 2);
         i < heatDistrib_ini.size() - (Nx - 1); i += Nx - 1)
        heatDistrib_ini[i] = Tr;

    return heatDistrib_ini;

}