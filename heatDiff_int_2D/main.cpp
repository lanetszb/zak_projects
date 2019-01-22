#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <grid/grid.h>
#include <plot/plot.h>
#include <matrix/matrix.h>
#include <param.h>


std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                         const double &T0, const double &Tl,
                                         const double &Tr);

void funcJacobi(const Matrix &mtr, const Param &prm, std::vector<double> &X);


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


    auto X = func_heatDistrib_ini(grd.Ny, grd.Nx, prm.T0, prm.Tl, prm.Tr);


    Matrix mtr;

    for (double t = prm.dt; t <= prm.time; t += prm.dt) {

        func_matrixCalculation(grd, mtr, prm, X, prm.dt);

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

void funcJacobi(const Matrix &mtr, const Param &prm, std::vector<double> &X) {

    double curTolerance = 0;

    std::vector<std::vector<double>> Xcur{2, X};

    std::vector<int> dgInd;
    for (int i = 0; i < mtr.poi.size() - 1; i++)
        for (int j = mtr.poi[i]; j < mtr.poi[i + 1]; j++)
            if (i == mtr.col[j]) {
                dgInd.push_back(j);
                break;
            }

    unsigned int k = 0;

    do {

        for (int i = 0; i < mtr.poi.size() - 1; i++)
            Xcur[(k + 1) % 2][i] = X[i] + Xcur[k % 2][i] * mtr.val[dgInd[i]];

        for (int i = 0; i < mtr.poi.size() - 1; i++)
            for (int j = mtr.poi[i]; j < mtr.poi[i + 1]; j++)
                Xcur[(k + 1) % 2][i] -= mtr.val[j] * Xcur[k % 2][mtr.col[j]];

        for (int i = 0; i < mtr.poi.size() - 1; i++)
            Xcur[(k + 1) % 2][i] /= mtr.val[dgInd[i]];

        curTolerance = 0;
        for (int i = 0; i < mtr.poi.size() - 1; i++)
            curTolerance += fabs(2. * (Xcur[(k + 1) % 2][i] - Xcur[k % 2][i]) /
                                 (Xcur[(k + 1) % 2][i] + Xcur[k % 2][i])) /
                            X.size();
        k++;


    } while (curTolerance > prm.maxTolerance);


    X = Xcur[k % 2];

}