#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <grid.h>
#include <plot.h>


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

    auto dt = dataFile.getWord<double>("timeStep");
    auto time = dataFile.getWord<double>("time");
    auto lambda = dataFile.getWord<double>("thermalCond");

    auto Tl = dataFile.getWord<double>("tempLeft");
    auto Tr = dataFile.getWord<double>("tempRight");
    auto Ttop = dataFile.getWord<double>("tempTop");
    auto Tbot = dataFile.getWord<double>("tempBot");
    auto T0 = dataFile.getWord<double>("tempIni");

    auto dens = dataFile.getWord<double>("density");
    auto capac = dataFile.getWord<double>("heatCapac");

    auto grdFileNm = dataFile.getWord<std::string>("GRID_DATA");
    auto nodesFileNm = dataFile.getWord<std::string>("NODES_NUM");

    auto maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

    Grid grd;

    func_gridCalculation(grd, grdFileNm, nodesFileNm);




    // ***Numerical solution for heat diffusion begins here***


    std::vector<double> lamb(grd.gridN, lambda);


    // Temp vector

    auto heatDistr_ini = func_heatDistrib_ini(grd.Ny, grd.Nx, T0, Tl, Tr);

    Plot plt;

    func_plot(grd, plt, heatDistr_ini);


    // A coefficient

    auto getBot_lambda = func_getBot_lambda(lamb, grd.Nx);
    auto getTop_lambda = func_getTop_lambda(lamb, grd.Nx);
    auto getLeft_lambda = func_getLeft_lambda(lamb, grd.Nx);
    auto getRight_lambda = func_getRight_lambda(lamb, grd.Nx);


    std::cout << "test" << std::endl;

    std::vector<double> A(grd.gridN, 0);
    for (int i = 0; i < grd.gridN; i++)
        A[i] = (-1 * getBot_lambda[i] * grd.omega_jMin[i]) / grd.getBot_dL[i];

    for (int i = 0; i < grd.Nx - 1; i++)
        A[i] = 0;

    std::cout << "A[i]" << std::endl;
    for (int i = 0; i < A.size(); i++)
        std::cout << A[i] << std::endl;
    std::cout << std::endl;


// E coefficient


    std::vector<double> E(grd.gridN, 0);
    for (int i = 0; i < grd.gridN; i++)
        E[i] = (-1 * getTop_lambda[i] * grd.omega_jPlus[i]) / grd.getTop_dL[i];

    for (int i = grd.gridN - (grd.Nx - 1); i < grd.gridN; i++)
        E[i] = 0;

    std::cout << "E[i]" << std::endl;
    for (int i = 0; i < E.size(); i++)
        std::cout << E[i] << std::endl;
    std::cout << std::endl;



// B coefficient

    std::vector<double> B(grd.gridN, 0);
    for (int j = 0, i = 0; i < grd.gridN; i++)
        B[i] = (-1 * getLeft_lambda[i] * grd.omega_iMin[i]) / grd.getLeft_dL[i];

    for (int i = 0; i < grd.gridN; i += grd.Nx - 1)
        B[i] = 0;


    std::cout << "B[i]" << std::endl;
    for (int i = 0; i < B.size(); i++)
        std::cout << B[i] << std::endl;
    std::cout << std::endl;

// D coefficient

    std::vector<double> D(grd.gridN, 0);
    for (int i = 0; i < grd.gridN; i++)
        D[i] = (-1 * getRight_lambda[i] * grd.omega_iPlus[i]) /
               grd.getRight_dL[i];

    for (int i = grd.Nx - 2; i < grd.gridN; i += grd.Nx - 1)
        D[i] = 0;

    std::cout << "D[i]" << std::endl;
    for (int i = 0; i < D.size(); i++)
        std::cout << D[i] << std::endl;
    std::cout << std::endl;


// F coefficient

    std::vector<double> F(grd.gridN, 0);
    for (int i = 0; i < grd.gridN; i++)
        F[i] = (-1 * grd.gridVolume[i] * dens * capac) / dt;

    std::cout << "F[i]" << std::endl;
    for (int i = 0; i < F.size(); i++)
        std::cout << F[i] << std::endl;
    std::cout << std::endl;




// С coefficient

    std::vector<double> C(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        C[i] = (-1 * F[i]) + (-1 * A[i]) + (-1 * B[i]) + (-1 * D[i]) +
               (-1 * E[i]);


    std::cout << "C[i]" << std::endl;
    for (int i = 0; i < C.size(); i++)
        std::cout << C[i] << std::endl;
    std::cout << std::endl;

    return 0;

}


// ***all the functions are listed below***

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