#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>


std::vector<double> func_Xcenter(std::vector<double> &X_coord, const int &Nx);

void func_Ycenter(std::vector<double> &gridYcent, std::vector<double> &Y_coord, const int &gridN, const int &Nx);

void func_omega_jPl(std::vector<double> &omega_iPl, std::vector<double> &X_coord, const int &gridN, const int &Nx);

void func_omega_jMin(std::vector<double> &omega_iMin, std::vector<double> &X_coord, const int &gridN, const int &Nx);


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
    std::vector<double> omega_iP(gridN, 0);
    std::vector<double> omega_jP(gridN, 0);
    std::vector<double> omega_iM(gridN, 0);
    std::vector<double> omega_jM(gridN, 0);
    std::vector<double> vol(gridN, 0);

    for (int i = 0; i < gridN; i++) {

        omega_jM[i] = omega_jP[i];
        omega_iM[i] = omega_iP[i];

        vol[i] = omega_jP[i] * omega_iP[i];
    }

    // Temp vector

    std::vector<double> T(gridN, T0);

    for (int i = 0; i < Nx; i++)
        T[i] = Tl;

    for (int i = (Nx - 1); i < T.size() - (Nx - 1); i += Nx - 1)
        T[i] = Tl;

    for (int i = T.size() - (Nx - 1); i < T.size(); i++)
        T[i] = Tr;

    for (int i = 2 * (Nx - 1) - 1; i < T.size() - (Nx - 1); i += Nx - 1)
        T[i] = Tr;

    for (int i = 0; i < T.size(); i++)
        std::cout << T[i] << std::endl;
    std::cout << std::endl;

    // ***Grid block centre***

    // Centre of blocks in X directions

    auto gridXcent = func_Xcenter(X_coord, Nx);

    // Centre of blocks in Y directions

    std::vector<double> gridYcent(gridN, 0);
    func_Ycenter(gridYcent, Y_coord, gridN, Nx);

    // ***Surface area determination***

    // Omega j Plus

    std::vector<double> omega_jPlus(gridN, 0);
    func_omega_jPl(omega_jPlus, X_coord, gridN, Nx);

    // Omega j Minus
    std::vector<double> omega_jMin(gridN, 0);
    func_omega_jMin(omega_jMin, X_coord, gridN, Nx);

    // Omega i Plus

    std::vector<double> omega_iPlus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus[i] = (Y_coord[i + Nx + 1 + j] - Y_coord[i + 1 + j]);
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    // Omega i Minus

    std::vector<double> omega_iMinus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMinus[i] = (Y_coord[i + Nx + j] - Y_coord[i + j]);
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

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
        C[i] = /*-1 * vol[i] * dens * capac / dt + */lamb[i - (Nx - 1)] * omega_jM[i] / (((Y_coord[i + 1 + Nx] - Y_coord[i + 1]) +
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
        C[i] = /*-1 * vol[i] * dens * capac / dt + */lamb[i - (Nx - 1)] * omega_jM[i] / (((Y_coord[i + 1 + Nx] - Y_coord[i + 1]) +
                                                                                          (Y_coord[i + 1] - Y_coord[i + 1 - Nx])) / 2) +
                                                     lamb[i - 1] * omega_iM[i] / abs((X_coord[i + 1 + j] - X_coord[i + 2 + j]) +
                                                                                     (X_coord[i + 2 + j] - X_coord[i + 3 + j])) / 2 +
                                                     lamb[i + 1] * omega_iP[i] / (((X_coord[i + 2 + j] - X_coord[i + 1 + j]) +
                                                                                   (X_coord[i + 3 + j] - X_coord[i + 2 + j])) / 2) +
                                                     lamb[i + (Nx - 1)] * omega_jP[i] /
                                                     (((Y_coord[i + 1 + 2 * Nx] - Y_coord[i + 1 + Nx]) +
                                                       (Y_coord[i + 1 + Nx] - Y_coord[i + 1])) / 2);


    for (int i = (Nx - 2), j = 0; i < gridN; i += (Nx - 1), j++)
        C[i] = /*-1 * vol[i] * dens * capac / dt + */lamb[i - (Nx - 1)] * omega_jM[i] / (((Y_coord[i + 1 + Nx] - Y_coord[i + 1]) +
                                                                                          (Y_coord[i + 1] - Y_coord[i + 1 - Nx])) / 2) +
                                                     lamb[i - 1] * omega_iM[i] / abs((X_coord[i + j] - X_coord[i + 1 + j]) +
                                                                                     (X_coord[i + 2 + j] - X_coord[i + 3 + j])) / 2 +
                                                     lamb[i + 1] * omega_iP[i] / (((X_coord[i + 1 + j] - X_coord[i + j]) +
                                                                                   (X_coord[i + 3 + j] - X_coord[i + 2 + j])) / 2) +
                                                     lamb[i + (Nx - 1)] * omega_jP[i] /
                                                     (((Y_coord[i + 1 + 2 * Nx] - Y_coord[i + 1 + Nx]) +
                                                       (Y_coord[i + 1 + Nx] - Y_coord[i + 1])) / 2);

    // check output

    int width = 5;


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
    for (int i = 0; i < omega_iMinus.size(); i++)
        std::cout << omega_iMinus[i] << std::endl;
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
        gridXcent[i] = abs(X_coord[i + 1 + j] + X_coord[i + j]) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        gridXcent[i] = abs(X_coord[i + 1 + j] - X_coord[i + 2 + j]) / 2;

    return gridXcent;
}

void func_Ycenter(std::vector<double> &gridYcent, std::vector<double> &Y_coord, const int &gridN, const int &Nx) {
    for (int j = 0, i = 0; i < gridN; i++) {
        gridYcent[i] = (Y_coord[i + Nx + 1 + j] + Y_coord[i + 1 + j]) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
}

void func_omega_jPl(std::vector<double> &omega_iPl, std::vector<double> &X_coord, const int &gridN, const int &Nx) {
    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPl[i] = X_coord[i + 1 + j + Nx] - X_coord[i + j + Nx];
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iPl[i] = X_coord[i + 2 + j] - X_coord[i + 1 + j];
}

void func_omega_jMin(std::vector<double> &omega_iMin, std::vector<double> &X_coord, const int &gridN, const int &Nx) {
    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMin[i] = X_coord[i + 1 + j] - X_coord[i + j];
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iMin[i] = X_coord[i + 2 + j] - X_coord[i + 1 + j];
}


