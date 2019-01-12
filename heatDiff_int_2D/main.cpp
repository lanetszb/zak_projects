#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <grid.h>
#include <plot.h>
#include <matrix.h>
#include <param.h>


std::vector<double> func_getLeft_lambda(const std::vector<double> &lamb,
                                        const int &Nx);

std::vector<double> func_getRight_lambda(const std::vector<double> &lamb,
                                         const int &Nx);

std::vector<double> func_getTop_lambda(const std::vector<double> &lamb,
                                       const int &Nx);

std::vector<double> func_getBot_lambda(const std::vector<double> &lamb,
                                       const int &Nx);

std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                         const double &T0, const double &Tl,
                                         const double &Tr);


int main(int narg, char **arg) {

    // ***reading the required input data***
    GetFromFile dataFile(arg[1]);

    Param prm;
    getParam(prm, arg[1]);

    auto grdFileNm = dataFile.getWord<std::string>("GRID_DATA");
    auto nodesFileNm = dataFile.getWord<std::string>("NODES_NUM");

    Grid grd;

    func_gridCalculation(grd, grdFileNm, nodesFileNm);
    // ***Numerical solution for heat diffusion begins here***


    std::vector<double> lamb(grd.gridN, prm.lambda);


    // Temp vector

    auto heatDistr_ini = func_heatDistrib_ini(grd.Ny, grd.Nx, prm.T0, prm.Tl,
                                              prm.Tr);

    Plot plt;

    func_plot(grd, plt, heatDistr_ini);


    auto getBot_lambda = func_getBot_lambda(lamb, grd.Nx);
    auto getTop_lambda = func_getTop_lambda(lamb, grd.Nx);
    auto getLeft_lambda = func_getLeft_lambda(lamb, grd.Nx);
    auto getRight_lambda = func_getRight_lambda(lamb, grd.Nx);

    Matrix mtr;

    func_matrixCalculation(grd, mtr, prm, getBot_lambda, getTop_lambda,
                           getLeft_lambda, getRight_lambda);


    std::cout << "test" << std::endl;


    return 0;

}


//***all the functions are listed below***

std::vector<double> func_getLeft_lambda(const std::vector<double> &lamb,
                                        const int &Nx) {

    std::vector<double> getLeft_lambda(lamb.size(), 0);

    for (int i = 0; i < lamb.size(); i++) {
        getLeft_lambda[i] = lamb[i - 1];
    }

    for (int i = 0; i < lamb.size(); i += Nx - 1)
        getLeft_lambda[i] = 0;

    return getLeft_lambda;
}

std::vector<double> func_getRight_lambda(const std::vector<double> &lamb,
                                         const int &Nx) {

    std::vector<double> getRight_lambda(lamb.size(), 0);

    for (int i = 0; i < lamb.size(); i++)
        getRight_lambda[i] = lamb[i + 1];

    for (int i = Nx - 2; i < lamb.size(); i += Nx - 1)
        getRight_lambda[i] = 0;

    return getRight_lambda;
}

std::vector<double> func_getTop_lambda(const std::vector<double> &lamb,
                                       const int &Nx) {

    std::vector<double> getTop_lambda(lamb.size(), 0);

    for (int i = 0; i < getTop_lambda.size(); i++) {
        getTop_lambda[i] = lamb[i + Nx - 1];
    }

    for (int i = getTop_lambda.size() - (Nx - 1);
         i < getTop_lambda.size(); i++)
        getTop_lambda[i] = 0;

    return getTop_lambda;
}


std::vector<double> func_getBot_lambda(const std::vector<double> &lamb,
                                       const int &Nx) {

    std::vector<double> getBot_lambda(lamb.size(), 0);

    for (int i = 0; i < getBot_lambda.size(); i++) {
        getBot_lambda[i] = lamb[i - (Nx - 1)];
    }

    for (int i = 0; i < Nx - 1; i++)
        getBot_lambda[i] = 0;

    return getBot_lambda;
}

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