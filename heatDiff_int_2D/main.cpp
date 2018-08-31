#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>


std::vector<double> func_Xcenter(std::vector<double> &X_coord, const int &Nx);

std::vector<double> func_Ycenter(std::vector<double> &Y_coord, const int &Nx);

std::vector<double> func_omega_jPlus(std::vector<double> &X_coord, const int &Nx);

std::vector<double> func_omega_jMin(std::vector<double> &X_coord, const int &Nx);

std::vector<double> func_omega_iPlus(std::vector<double> &Y_coord, const int &Nx);

std::vector<double> func_omega_iMin(std::vector<double> &Y_coord, const int &Nx);

std::vector<double> func_gridVolume(std::vector<double> omega_iPlus, std::vector<double> omega_iMin, std::vector<double> omega_jPlus,
                                    std::vector<double> omega_jMin, const int gridN);

std::vector<double> func_omega_iPlus_Xcent(std::vector<double> &X_coord, const int &Nx);

std::vector<double> func_omega_iPlus_Ycent(std::vector<double> &Y_coord, const int &Nx);

std::vector<double> func_omega_iMinus_Xcent(std::vector<double> &X_coord, const int &Nx);

std::vector<double> func_omega_iMinus_Ycent(const std::vector<double> &Y_coord, const int &Nx);

std::vector<double> func_getLeft_lambda(const std::vector<double> &lamb, const int &Nx);

std::vector<double> func_getRight_lambda(const std::vector<double> &lamb, const int &Nx);

std::vector<double> func_getTop_lambda(const std::vector<double> &lamb, const int &Nx);

std::vector<double> func_getBot_lambda(const std::vector<double> &lamb, const int &Nx);

std::vector<double> func_getLeft_dL(const std::vector<double> &gridXcent, const int &Nx);

std::vector<double> func_getRight_dL(const std::vector<double> &gridXcent, const int &Nx);

std::vector<double> func_getTop_dL(const std::vector<double> &gridYcent, const int &Nx);

std::vector<double> func_getBot_dL(const std::vector<double> &gridYcent, const int &Nx);

std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx, const double &T0, const double &Tl,
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

    auto gridData = dataFile.getWord<std::string>("GRID_DATA");
    auto nodesData = dataFile.getWord<std::string>("NODES_NUM");

    auto maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

    GetFromFile gridD(gridData);
    auto X_coord = gridD.getVector<double>("Node_X");
    auto Y_coord = gridD.getVector<double>("Node_Y");

    GetFromFile nodesD(nodesData);

    int Nx = nodesD.getWord<int>("NODES_NUM_X");
    int Ny = nodesD.getWord<int>("NODES_NUM_Y");

    // ***Numerical solution for heat diffusion begins here***

    auto gridN = (Nx - 1) * (Ny - 1);
    auto nodeN = Nx * Ny;

    std::vector<double> lamb(gridN, lambda);

    std::vector<double> gridInd(gridN, 0);
    std::vector<double> vol(gridN, 0);

    for (int i = 0; i < gridN; i++) {

        vol[i] = 1;
    }

    // Temp vector

    auto heatDistr_ini = func_heatDistrib_ini(Ny, Nx, T0, Tl, Tr);

    for (int i = 0; i < heatDistr_ini.size(); i++)
        std::cout << heatDistr_ini[i] << std::endl;
    std::cout << std::endl;

    // Centre of blocks in X and Y directions

    auto gridXcent = func_Xcenter(X_coord, Nx);
    auto gridYcent = func_Ycenter(Y_coord, Nx);


    // ***Surface area and volume determination***


    // Omega j Plus and Minus

    auto omega_jPlus = func_omega_jPlus(X_coord, Nx);
    auto omega_jMin = func_omega_jMin(X_coord, Nx);

    // Omega i Plus and Minus

    auto omega_iPlus = func_omega_iPlus(Y_coord, Nx);
    auto omega_iMin = func_omega_iMin(Y_coord, Nx);

    // Grid volume

    auto gridVolume = func_gridVolume(omega_iPlus, omega_iMin, omega_jPlus,
                                      omega_jMin, gridN);

    // ***Grid surface centres***

    // Omega i Plus center, X and Y coordinates

    auto omega_iPlus_Xcent = func_omega_iPlus_Xcent(X_coord, Nx);
    auto omega_iPlus_Ycent = func_omega_iPlus_Ycent(Y_coord, Nx);

    // Omega i Minus center, X and Y coordinates

    auto omega_iMinus_Xcent = func_omega_iMinus_Xcent(X_coord, Nx);
    auto omega_iMinus_Ycent = func_omega_iMinus_Ycent(Y_coord, Nx);

    // Getting left and right lambda
    auto getLeft_lambda = func_getLeft_lambda(lamb, Nx);
    auto getRight_lambda = func_getRight_lambda(lamb, Nx);

    // Getting top and bottom lambda
    auto getTop_lambda = func_getTop_lambda(lamb, Nx);
    auto getBot_lambda = func_getBot_lambda(lamb, Nx);

    // Getting left and right dL
    auto getLeft_dL = func_getLeft_dL(gridXcent, Nx);
    auto getRight_dL = func_getRight_dL(gridXcent, Nx);

    // Getting Top and Bot dL
    auto getTop_dL = func_getTop_dL(gridYcent, Nx);
    auto getBot_dL = func_getBot_dL(gridYcent, Nx);

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

    */

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

    // data output

    return 0;

}

// ***all the functions are listed below***

std::vector<double> func_Xcenter(std::vector<double> &X_coord, const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> gridXcent(gridN, 0);

    for (int j = 0, i = 0; i < gridXcent.size(); i++) {
        gridXcent[i] = abs(X_coord[i + 1 + j] + X_coord[i + j] + X_coord[i + 1 + j + Nx] + X_coord[i + j + Nx]) / 4;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        gridXcent[i] = abs(X_coord[i + 1 + j] + X_coord[i + 2 + j] + X_coord[i + 1 + j + Nx] + X_coord[i + 2 + j + Nx]) / 4;

    std::cout << std::endl;

    return gridXcent;


}

std::vector<double> func_Ycenter(std::vector<double> &Y_coord, const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> gridYcent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        gridYcent[i] = (Y_coord[i + Nx + 1 + j] + Y_coord[i + 1 + j] + Y_coord[i + Nx + j] + Y_coord[i + j]) / 4;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        gridYcent[i] = (Y_coord[i + 1 + j + Nx] + Y_coord[i + 1 + j] + Y_coord[i + 2 + j + Nx] + Y_coord[i + 2 + j]) / 4;


    return gridYcent;
}

std::vector<double> func_omega_jPlus(std::vector<double> &X_coord, const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_jPlus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_jPlus[i] = X_coord[i + 1 + j + Nx] - X_coord[i + j + Nx];
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_jPlus[i] = X_coord[i + 2 + j] - X_coord[i + 1 + j];

    return omega_jPlus;
}

std::vector<double> func_omega_jMin(std::vector<double> &X_coord, const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_jMin(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_jMin[i] = X_coord[i + 1 + j] - X_coord[i + j];
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_jMin[i] = X_coord[i + 2 + j] - X_coord[i + 1 + j];

    return omega_jMin;
}

std::vector<double> func_omega_iPlus(std::vector<double> &Y_coord, const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iPlus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus[i] = (Y_coord[i + Nx + 1 + j] - Y_coord[i + 1 + j]);
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iPlus;
}

std::vector<double> func_omega_iMin(std::vector<double> &Y_coord, const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iMin(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMin[i] = (Y_coord[i + Nx + j] - Y_coord[i + j]);
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iMin;
}

std::vector<double> func_gridVolume(std::vector<double> omega_iPlus, std::vector<double> omega_iMin, std::vector<double> omega_jPlus,
                                    std::vector<double> omega_jMin, const int gridN) {

    std::vector<double> semiPerimeter(gridN, 0);

    for (int i = 0; i < semiPerimeter.size(); i++)
        semiPerimeter[i] = (omega_iPlus[i] + omega_iMin[i] + omega_jPlus[i] + omega_jMin[i]) / 2;

    std::vector<double> gridArea(gridN, 0);
    for (int i = 0; i < gridArea.size(); i++)
        gridArea[i] = sqrt((semiPerimeter[i] - omega_iPlus[i]) * (semiPerimeter[i] - omega_iMin[i]) * (semiPerimeter[i] - omega_jPlus[i]) *
                           (semiPerimeter[i] - omega_jMin[i]));

    // Grid volume

    std::vector<double> gridZheight(gridN, 1);
    std::vector<double> gridVolume(gridN, 0);

    for (int i = 0; i < gridArea.size(); i++)
        gridVolume[i] = gridArea[i] * gridZheight[i];

    return gridVolume;
}

std::vector<double> func_omega_iPlus_Xcent(std::vector<double> &X_coord, const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_iPlus_Xcent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus_Xcent[i] = (X_coord[i + 1 + j + Nx] + X_coord[i + j + 1]) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iPlus_Xcent[i] = (X_coord[i + 2 + j + Nx] + X_coord[i + 2 + j]) / 2;

    return omega_iPlus_Xcent;
}

std::vector<double> func_omega_iPlus_Ycent(std::vector<double> &Y_coord, const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iPlus_Ycent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus_Ycent[i] = ((Y_coord[i + Nx + 1 + j] + Y_coord[i + 1 + j])) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iPlus_Ycent;
}

std::vector<double> func_omega_iMinus_Xcent(std::vector<double> &X_coord, const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_iMinus_Xcent(gridN, 0);
    int width = 7;

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMinus_Xcent[i] = (X_coord[i + j + Nx] + X_coord[i + j]) / 2;

        std::cout << X_coord[i + j + Nx] << "  ";
        std::cout << X_coord[i + j] << "  ";
        std::cout << j << " ";

        if (i % (Nx - 1) == 0 && i != 0)
            j++;


        std::cout << " vector: " << std::setw(width) << omega_iMinus_Xcent[i];
        std::cout << " formula: " << std::setw(width) << (X_coord[i + j + Nx] + X_coord[i + j]) / 2;

        std::cout << " " << j;
        std::cout << std::endl;
    }


    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iMinus_Xcent[i] = (X_coord[i + 1 + j + Nx] + X_coord[i + 1 + j]) / 2;

    std::cout << std::endl;


    return omega_iMinus_Xcent;
}

std::vector<double> func_omega_iMinus_Ycent(const std::vector<double> &Y_coord, const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iMinus_Ycent(gridN, 0);
    int width = 5;

    for (int j = 0, i = 0; i < omega_iMinus_Ycent.size(); i++) {
        omega_iMinus_Ycent[i] = (Y_coord[i + Nx + j] + Y_coord[i + j]) / 2;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;

    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iMinus_Ycent[i] = (Y_coord[i + 1 + j + Nx] + Y_coord[i + 1 + j]) / 2;

    return omega_iMinus_Ycent;
}

std::vector<double> func_getLeft_lambda(const std::vector<double> &lamb, const int &Nx) {

    std::vector<double> getLeft_lambda(lamb.size(), 0);
    int width = 5;

    for (int i = 0; i < lamb.size(); i++) {
        getLeft_lambda[i] = lamb[i - 1];

    }

    for (int i = 0; i < lamb.size(); i += Nx - 1)
        getLeft_lambda[i] = 0;

    return getLeft_lambda;
}

std::vector<double> func_getRight_lambda(const std::vector<double> &lamb, const int &Nx) {

    std::vector<double> getRight_lambda(lamb.size(), 0);
    int width = 5;

    for (int i = 0; i < lamb.size(); i++)
        getRight_lambda[i] = lamb[i + 1];

    for (int i = Nx - 2; i < lamb.size(); i += Nx - 1)
        getRight_lambda[i] = 0;

    return getRight_lambda;
}

std::vector<double> func_getTop_lambda(const std::vector<double> &lamb, const int &Nx) {

    std::vector<double> getTop_lambda(lamb.size(), 0);
    int width = 5;

    for (int i = 0; i < getTop_lambda.size(); i++) {
        getTop_lambda[i] = lamb[i + Nx - 1];

    }

    for (int i = getTop_lambda.size() - (Nx - 1); i < getTop_lambda.size(); i++)
        getTop_lambda[i] = 0;

    for (int i = 0; i < lamb.size(); i++)
        std::cout << std::setw(width) << getTop_lambda[i];

    std::cout << std::endl;

    return getTop_lambda;
}


std::vector<double> func_getBot_lambda(const std::vector<double> &lamb, const int &Nx) {

    std::vector<double> getBot_lambda(lamb.size(), 0);
    int width = 5;

    for (int i = 0; i < getBot_lambda.size(); i++) {
        getBot_lambda[i] = lamb[i - (Nx - 1)];

    }

    for (int i = 0; i < Nx - 1; i++)
        getBot_lambda[i] = 0;

    for (int i = 0; i < lamb.size(); i++)
        std::cout << std::setw(width) << getBot_lambda[i];

    std::cout << std::endl;

    return getBot_lambda;
}

std::vector<double> func_getLeft_dL(const std::vector<double> &gridXcent, const int &Nx) {

    std::vector<double> getLeft_dL(gridXcent.size(), 0);
    int width = 5;

    for (int i = 0; i < getLeft_dL.size(); i++) {
        getLeft_dL[i] = gridXcent[i] - gridXcent[i - 1];

    }

    for (int i = 0; i < getLeft_dL.size(); i += Nx - 1)
        getLeft_dL[i] = 0;

    for (int i = 0; i < getLeft_dL.size(); i++)
        std::cout << std::setw(width) << getLeft_dL[i];

    std::cout << std::endl;

    return getLeft_dL;
}

std::vector<double> func_getRight_dL(const std::vector<double> &gridXcent, const int &Nx) {

    std::vector<double> getRight_dL(gridXcent.size(), 0);
    int width = 5;

    for (int i = 0; i < getRight_dL.size(); i++) {
        getRight_dL[i] = gridXcent[i + 1] - gridXcent[i];

    }

    for (int i = Nx - 2; i < getRight_dL.size(); i += Nx - 1)
        getRight_dL[i] = 0;

    for (int i = 0; i < getRight_dL.size(); i++)
        std::cout << std::setw(width) << getRight_dL[i];

    std::cout << std::endl;

    return getRight_dL;
}

std::vector<double> func_getTop_dL(const std::vector<double> &gridYcent, const int &Nx) {

    std::vector<double> getTop_dL(gridYcent.size(), 0);
    int width = 5;

    for (int i = 0; i < getTop_dL.size(); i++)
        getTop_dL[i] = gridYcent[i + (Nx - 1)] - gridYcent[i];

    for (int i = getTop_dL.size() - (Nx - 1); i < getTop_dL.size(); i++)
        getTop_dL[i] = 0;

    for (int i = 0; i < getTop_dL.size(); i++)
        std::cout << std::setw(width) << getTop_dL[i];
    std::cout << std::endl;

    return getTop_dL;

}

std::vector<double> func_getBot_dL(const std::vector<double> &gridYcent, const int &Nx) {

    std::vector<double> getBot_dL(gridYcent.size(), 0);
    int width = 5;

    for (int i = 0; i < getBot_dL.size(); i++)
        getBot_dL[i] = gridYcent[i] - gridYcent[i - (Nx - 1)];

    for (int i = 0; i < Nx - 1; i++)
        getBot_dL[i] = 0;

    for (int i = 0; i < getBot_dL.size(); i++)
        std::cout << std::setw(width) << getBot_dL[i];
    std::cout << std::endl;

    return getBot_dL;

}

std::vector<double>
func_heatDistrib_ini(const int &Ny, const int &Nx, const double &T0, const double &Tl,
                     const double &Tr) {

    int gridN = (Nx - 1) * (Ny - 1);
    std::vector<double> heatDistrib_ini(gridN, T0);

    for (int i = 0; i < (Nx - 2); i++)
        heatDistrib_ini[i] = Tl;

    for (int i = (Nx - 1); i < heatDistrib_ini.size() - (Nx - 2); i += Nx - 1)
        heatDistrib_ini[i] = Tl;

    for (int i = heatDistrib_ini.size() - (Nx - 2); i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = Tr;

    for (int i = (Nx - 2); i < heatDistrib_ini.size() - (Nx - 1); i += Nx - 1)
        heatDistrib_ini[i] = Tr;

    return heatDistrib_ini;

}