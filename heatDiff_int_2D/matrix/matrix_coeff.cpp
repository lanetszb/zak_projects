#include <matrix/matrix_coeff.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

// A coefficient
void A_calc(Grid &grd, Matrix &mtr, Param &prm) {

    mtr.A.clear();
    mtr.A = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.A[i] = (-1 * prm.getBot_lambda[i] * grd.omegaBot[i]) / grd.getBot_dL[i];

    for (int i = 0; i < grd.Nx - 1; i++)
        mtr.A[i] = 0;

//std::cout << "A[i]" << std::endl;
//for (int i = 0; i < mtr.A.size(); i++)
//std::cout << mtr.A[i] << std::endl;
//std::cout << std::endl;
}

// E coefficient

void E_calc(Grid &grd, Matrix &mtr, Param &prm) {

    mtr.E.clear();
    mtr.E = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.E[i] = (-1 * prm.getTop_lambda[i] * grd.omegaTop[i]) / grd.getTop_dL[i];

    for (int i = grd.gridN - (grd.Nx - 1); i < grd.gridN; i++)
        mtr.E[i] = 0;

//    std::cout << "E[i]" << std::endl;
//    for (int i = 0; i < mtr.E.size(); i++)
//        std::cout << mtr.E[i] << std::endl;
//    std::cout << std::endl;
}

// B coefficient
void B_calc(Grid &grd, Matrix &mtr, Param &prm) {

    mtr.B.clear();
    mtr.B = std::vector<double>(grd.gridN, 0);

    for (int j = 0, i = 0; i < grd.gridN; i++)
        mtr.B[i] =
                (-1 * prm.getLeft_lambda[i] * grd.omegaLeft[i]) / grd.getLeft_dL[i];

    for (int i = 0; i < grd.gridN; i += grd.Nx - 1)
        mtr.B[i] = 0;


//    std::cout << "B[i]" << std::endl;
//    for (int i = 0; i < mtr.B.size(); i++)
//        std::cout << mtr.B[i] << std::endl;
//    std::cout << std::endl;
}

// D coefficient
void D_calc(Grid &grd, Matrix &mtr, Param &prm) {

    mtr.D.clear();
    mtr.D = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.D[i] = (-1 * prm.getRight_lambda[i] * grd.omegaRight[i]) /
                   grd.getRight_dL[i];

    for (int i = grd.Nx - 2; i < grd.gridN; i += grd.Nx - 1)
        mtr.D[i] = 0;

//    std::cout << "D[i]" << std::endl;
//    for (int i = 0; i < mtr.D.size(); i++) {
//        std::cout << mtr.D[i] << std::endl;
//        std::cout << std::endl;
}


// F coefficient
void F_calc(Grid &grd, Matrix &mtr, Param &prm) {

    mtr.F.clear();
    mtr.F = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.F[i] = (-1 * grd.gridVolume[i] * prm.dens * prm.capac) / prm.dt;

    std::cout << "F[i]" << std::endl;
    for (int i = 0; i < mtr.F.size(); i++)
        std::cout << mtr.F[i] << std::endl;
    std::cout << std::endl;
}

// С coefficient
void C_calc(Grid &grd, Matrix &mtr) {

    mtr.C.clear();
    mtr.C = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.C[i] = (-1 * mtr.F[i]) + (-1 * mtr.A[i]) + (-1 * mtr.B[i]) +
                   (-1 * mtr.D[i]) +
                   (-1 * mtr.E[i]);

//std::cout << "C[i]" << std::endl;
//for (int i = 0; i < mtr.C.size(); i++)
//std::cout << mtr.C[i] << std::endl;
//std::cout << std::endl;
}

