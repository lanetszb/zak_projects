#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <grid/grid.h>
#include <plot/plot.h>
#include <random.h>
#include <matrix/matrix.h>
#include <param.h>


std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                         const double &T0, const double &Tl,
                                         const double &Tr);

/*void funcJacobi(const Matrix &mtr, const Param &prm, std::vector<double> &X);*/


int main(int narg, char **arg) {

    // ***reading the required input data***
    GetFromFile dataFile(arg[1]);

    auto grdFileNm = dataFile.getWord<std::string>("GRID_DATA");
    auto nodesFileNm = dataFile.getWord<std::string>("NODES_NUM");
    auto thermalCond_table = dataFile.getWord<std::string>("THERMALCOND_TABLE");

    Grid grd;
    func_gridCalculation(grd, grdFileNm, nodesFileNm);

    // ***Numerical solution for heat diffusion begins here***

    Param prm;
    std::string dataFileName = arg[1];
    getParam(prm, grd, dataFileName);


    auto X = func_heatDistrib_ini(grd.Ny, grd.Nx, prm.T0, prm.Tl, prm.Tr);

    Lamb lmb;

    readLamb(lmb, thermalCond_table);

    /*, grd.gridN, X*/

    Matrix mtr;

    for (double t = prm.dt; t <= prm.time; t += prm.dt) {

        func_matrixCalculation(grd, mtr, prm, X, prm.dt);

        funcJacobi(mtr, prm, X);

    }

    std::vector<double> lamb(grd.gridN, prm.lambda);

//    GetFromFile lambTable(thermalCond_table);
//
//    int vec2DCol = lambTable.getWord<int>("vec2DCol");
//    std::vector<double> vec1DFor2D = lambTable.getVector<double>("vec2D");
//    std::vector<std::vector<double> > vec2D;
//    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
//        vec2D.push_back(std::vector<double>());
//        for (int j = 0; j < vec2DCol; j++)
//            vec2D.back().push_back(vec1DFor2D[i * vec2DCol + j]);
//    }

    func_getLeft_lamb(lmb, grd, X);


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

