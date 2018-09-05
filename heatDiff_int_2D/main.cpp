#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>
#include <grid.h>


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

    Grid grd = func_gridCalculation(grdFileNm, nodesFileNm);



    // ***Numerical solution for heat diffusion begins here***


    std::vector<double> lamb(grd.gridN, lambda);


    // Temp vector

    auto heatDistr_ini = func_heatDistrib_ini(grd.Ny, grd.Nx, T0, Tl, Tr);

    for (int i = 0; i < heatDistr_ini.size(); i++)
        std::cout << heatDistr_ini[i] << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < heatDistr_ini.size(); i++)
        std::cout << grd.omega_jMinus_Ycent[i] << std::endl;
    std::cout << std::endl;

    /*

    // A coefficient

    std::vector<double> A(gridN, 0);
    for (int i = 0; i < gridN; i++)
        A[i] = (-lamb[i - (Nx - 1)] * omega_jM[i]) / (((Y_coord[i + 1 + Nx] - Y_coord[i + 1]) +
                                                       (Y_coord[i + 1] - Y_coord[i + 1 - Nx])) / 2);

    std::cout << "A[i]" << std::endl;
    for (int i = 0; i < A.size(); i++)
        std::cout << A[i] << std::endl;
    std::cout << std::endl;

    // E coefficient


    std::vector<double> E(gridN, 0);
    for (int i = 0; i < gridN; i++)
        E[i] = (-lamb[i + (Nx - 1)] * omega_jP[i]) / (((Y_coord[i + 1 + 2 * Nx] - Y_coord[i + 1 + Nx]) +
                                                       (Y_coord[i + 1 + Nx] - Y_coord[i + 1])) / 2);

    std::cout << "E[i]" << std::endl;
    for (int i = 0; i < E.size(); i++)
        std::cout << E[i] << std::endl;
    std::cout << std::endl;

    // B coefficient

    std::vector<double> B(gridN, 0);


    for (int j = 0, i = 0; i < gridN; i++) {


        B[i] = -1 * lamb[i - 1] * omega_iM[i] / abs((X_coord[i + 1 + j] - X_coord[i + j]) +
                                                    (X_coord[i + 2 + j] - X_coord[i + 1 + j])) / 2;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;

    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        B[i] = (-1 * lamb[i - 1] * omega_iM[i]) / (abs(((X_coord[i + 1 + j] - X_coord[i + 2 + j]) +
                                                        (X_coord[i + 2 + j]) - X_coord[i + 3 + j])) / 2);

    for (int i = (Nx - 2), j = 0; i < gridN; i += (Nx - 1), j++)
        B[i] = (-1 * lamb[i - 1] * omega_iM[i]) / abs((((X_coord[i + j] - X_coord[i + 1 + j]) +
                                                        (X_coord[i + 2 + j]) - X_coord[i + 3 + j])) / 2);

    // D coefficient

    std::vector<double> D(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {

        D[i] = (-1 * lamb[i + 1] * omega_iP[i]) / (((X_coord[i + 1 + j] - X_coord[i + j]) +
                                                    (X_coord[i + 2 + j] - X_coord[i + 1 + j])) / 2);

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        D[i] = (-1 * lamb[i + 1] * omega_iP[i]) / (((X_coord[i + 2 + j] - X_coord[i + 1 + j]) +
                                                    (X_coord[i + 3 + j] - X_coord[i + 2 + j])) / 2);
    for (int i = (Nx - 2), j = 0; i < gridN; i += (Nx - 1), j++)
        D[i] = (-1 * lamb[i + 1] * omega_iP[i]) / (((X_coord[i + 1 + j] - X_coord[i + j]) +
                                                    (X_coord[i + 3 + j] - X_coord[i + 2 + j])) / 2);

    // F coefficient

    std::vector<double> F(gridN, 0);
    for (int i = 0; i < gridN; i++)
        F[i] = (-1 * vol[i] * dens * capac) / dt;


    // С coefficient
    std::vector<double> C(gridN, 0);
    for (int j = 0, i = 0; i < gridN; i++) {
        C[i] = /*-1 * vol[i] * dens * capac / dt + lamb[i - (Nx - 1)] * omega_jM[i] / (((Y_coord[i + 1 + Nx] - Y_coord[i + 1]) +
                                                                                          (Y_coord[i + 1] - Y_coord[i + 1 - Nx])) / 2) +
                                                     lamb[i - 1] * omega_iM[i] / abs((X_coord[i + 1 + j] - X_coord[i + j]) +
                                                                                     (X_coord[i + 2 + j] - X_coord[i + 1 + j])) / 2 +
                                                     lamb[i + 1] * omega_iP[i] / (((X_coord[i + 1 + j] - X_coord[i + j]) +
                                                                                   (X_coord[i + 2 + j] - X_coord[i + 1 + j])) / 2) +
                                                     lamb[i + (Nx - 1)] * omega_jP[i] /
                                                     (((Y_coord[i + 1 + 2 * Nx] - Y_coord[i + 1 + Nx]) +
                                                       (Y_coord[i + 1 + Nx] - Y_coord[i + 1])) / 2);
        if (i % (Nx - 1) == 0 && i != 0)
            j++;

    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        C[i] = /*-1 * vol[i] * dens * capac / dt + lamb[i - (Nx - 1)] * omega_jM[i] / (((Y_coord[i + 1 + Nx] - Y_coord[i + 1]) +
                                                                                          (Y_coord[i + 1] - Y_coord[i + 1 - Nx])) / 2) +
                                                     lamb[i - 1] * omega_iM[i] / abs((X_coord[i + 1 + j] - X_coord[i + 2 + j]) +
                                                                                     (X_coord[i + 2 + j] - X_coord[i + 3 + j])) / 2 +
                                                     lamb[i + 1] * omega_iP[i] / (((X_coord[i + 2 + j] - X_coord[i + 1 + j]) +
                                                                                   (X_coord[i + 3 + j] - X_coord[i + 2 + j])) / 2) +
                                                     lamb[i + (Nx - 1)] * omega_jP[i] /
                                                     (((Y_coord[i + 1 + 2 * Nx] - Y_coord[i + 1 + Nx]) +
                                                       (Y_coord[i + 1 + Nx] - Y_coord[i + 1])) / 2);


    for (int i = (Nx - 2), j = 0; i < gridN; i += (Nx - 1), j++)
        C[i] = /*-1 * vol[i] * dens * capac / dt + lamb[i - (Nx - 1)] * omega_jM[i] / (((Y_coord[i + 1 + Nx] - Y_coord[i + 1]) +
                                                                                          (Y_coord[i + 1] - Y_coord[i + 1 - Nx])) / 2) +
                                                     lamb[i - 1] * omega_iM[i] / abs((X_coord[i + j] - X_coord[i + 1 + j]) +
                                                                                     (X_coord[i + 2 + j] - X_coord[i + 3 + j])) / 2 +
                                                     lamb[i + 1] * omega_iP[i] / (((X_coord[i + 1 + j] - X_coord[i + j]) +
                                                                                   (X_coord[i + 3 + j] - X_coord[i + 2 + j])) / 2) +
                                                     lamb[i + (Nx - 1)] * omega_jP[i] /
                                                     (((Y_coord[i + 1 + 2 * Nx] - Y_coord[i + 1 + Nx]) +
                                                       (Y_coord[i + 1 + Nx] - Y_coord[i + 1])) / 2);

    // check output




    std::cout << "B[i]" << std::endl;
    for (int i = 0; i < B.size(); i++)
        std::cout << std::setw(width) << B[i];
    std::cout << std::endl;

    std::cout << "D[i]" << std::endl;
    for (int i = 0; i < D.size(); i++)
        std::cout << D[i] << std::endl;
    std::cout << std::endl;

    std::cout << "F[i]" << std::endl;
    for (int i = 0; i < F.size(); i++)
        std::cout << F[i] << std::endl;
    std::cout << std::endl;

    std::cout << "C[i]" << std::endl;
    for (int i = 0; i < C.size(); i++)
        std::cout << C[i] << std::endl;
    std::cout << std::endl;



    int width = 5;

    std::cout << "gridXcent[i]" << std::endl;
    for (int i = 0; i < gridXcent.size(); i++)
        std::cout << gridXcent[i] << std::endl;
    std::cout << std::endl;

    std::cout << "gridYcent[i]" << std::endl;
    for (int i = 0; i < gridYcent.size(); i++)
        std::cout << gridYcent[i] << std::endl;
    std::cout << std::endl;

    std::cout << "gridYcent[i]" << std::endl;
    for (int i = 0; i < gridYcent.size(); i++)
        std::cout << gridYcent[i] << std::endl;
    std::cout << std::endl;

    std::cout << "omega_jPlus[i]" << std::endl;
    for (int i = 0; i < omega_jPlus.size(); i++)
        std::cout << omega_jPlus[i] << std::endl;
    std::cout << std::endl;

    std::cout << "omega_jMin[i]" << std::endl;
    for (int i = 0; i < omega_jMin.size(); i++)
        std::cout << omega_jMin[i] << std::endl;
    std::cout << std::endl;

    std::cout << "omega_iPlus[i]" << std::endl;
    for (int i = 0; i < omega_iPlus.size(); i++)
        std::cout << omega_iPlus[i] << std::endl;
    std::cout << std::endl;

    std::cout << "omega_iMinus[i]" << std::endl;
    for (int i = 0; i < omega_iMin.size(); i++)
        std::cout << omega_iMin[i] << std::endl;
    std::cout << std::endl;

    std::cout << "omega_iMinus[i]" << std::endl;
    for (int i = 0; i < omega_iMinus_Ycent.size(); i++)
        std::cout << std::setw(width) << omega_iMinus_Ycent[i];
    std::cout << std::endl;


    double ZH = 1;
    std::cout << "ZH " << gridXcent[1] << std::endl;
    std::cout << std::endl;

      */

    // data output

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

    for (int i = getTop_lambda.size() - (Nx - 1); i < getTop_lambda.size(); i++)
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

    for (int i = (Nx - 1); i < heatDistrib_ini.size() - (Nx - 2); i += Nx - 1)
        heatDistrib_ini[i] = Tl;

    for (int i = heatDistrib_ini.size() - (Nx - 2);
         i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = Tr;

    for (int i = (Nx - 2); i < heatDistrib_ini.size() - (Nx - 1); i += Nx - 1)
        heatDistrib_ini[i] = Tr;

    return heatDistrib_ini;

}