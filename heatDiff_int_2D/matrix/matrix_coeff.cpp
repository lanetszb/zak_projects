#include <matrix/matrix_coeff.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

// A coefficient
void A_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb) {

    mtr.A.clear();
    mtr.A = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.A[i] = (-1 * lmb.botLamb[i] * grd.omegaBot[i]) /
                   grd.getBot_dL[i];

    for (int i = 0; i < (grd.Nx - 2); i++)
        mtr.A[i] = 0;

    for (int i = (grd.Nx - 1);
         i < mtr.A.size() - (grd.Nx - 2); i += grd.Nx - 1)
        mtr.A[i] = 0;

    for (int i = mtr.A.size() - (grd.Nx - 2);
         i < mtr.A.size(); i++)
        mtr.A[i] = 0;

    for (int i = (grd.Nx - 2);
         i < mtr.A.size() - (grd.Nx - 1); i += grd.Nx - 1)
        mtr.A[i] = 0;

}

// E coefficient

void E_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb) {

    mtr.E.clear();
    mtr.E = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.E[i] = (-1 * lmb.topLamb[i] * grd.omegaTop[i]) /
                   grd.getTop_dL[i];

    for (int i = 0; i < (grd.Nx - 2); i++)
        mtr.E[i] = 0;

    for (int i = (grd.Nx - 1);
         i < mtr.E.size() - (grd.Nx - 2); i += grd.Nx - 1)
        mtr.E[i] = 0;

    for (int i = mtr.E.size() - (grd.Nx - 2);
         i < mtr.E.size(); i++)
        mtr.E[i] = 0;

    for (int i = (grd.Nx - 2);
         i < mtr.E.size() - (grd.Nx - 1); i += grd.Nx - 1)
        mtr.E[i] = 0;
}

// B coefficient
void B_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb) {

    mtr.B.clear();
    mtr.B = std::vector<double>(grd.gridN, 0);

    for (int j = 0, i = 0; i < grd.gridN; i++)
        mtr.B[i] =
                (-1 * lmb.leftLamb[i] * grd.omegaLeft[i]) /
                grd.getLeft_dL[i];

    for (int i = 0; i < (grd.Nx - 2); i++)
        mtr.B[i] = 0;

    for (int i = (grd.Nx - 1);
         i < mtr.B.size() - (grd.Nx - 2); i += grd.Nx - 1)
        mtr.B[i] = 0;

    for (int i = mtr.B.size() - (grd.Nx - 2);
         i < mtr.B.size(); i++)
        mtr.B[i] = 0;

    for (int i = (grd.Nx - 2);
         i < mtr.B.size() - (grd.Nx - 1); i += grd.Nx - 1)
        mtr.B[i] = 0;
}

// D coefficient
void D_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb) {

    mtr.D.clear();
    mtr.D = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.D[i] = (-1 * lmb.rightLamb[i] * grd.omegaRight[i]) /
                   grd.getRight_dL[i];

    for (int i = 0; i < (grd.Nx - 2); i++)
        mtr.D[i] = 0;

    for (int i = (grd.Nx - 1);
         i < mtr.D.size() - (grd.Nx - 2); i += grd.Nx - 1)
        mtr.D[i] = 0;

    for (int i = mtr.D.size() - (grd.Nx - 2);
         i < mtr.D.size(); i++)
        mtr.D[i] = 0;

    for (int i = (grd.Nx - 2);
         i < mtr.D.size() - (grd.Nx - 1); i += grd.Nx - 1)
        mtr.D[i] = 0;
}


// F coefficient
void F_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb,
            const std::vector<double> &Xprev, const double &dt) {

    mtr.F.clear();
    mtr.F = std::vector<double>(grd.gridN, 0);

    for (int i = 0; i < grd.gridN; i++)
        mtr.F[i] = Xprev[i] *
                   (-1 * grd.gridVolume[i] * lmb.density[i] * lmb.capacity[i]) /
                   dt;
}

// С coefficient
void C_calc(const Grid &grd, Matrix &mtr, const Param &prm, const Lamb &lmb,
            const double &dt) {

    mtr.C.clear();
    mtr.C = std::vector<double>(grd.gridN, 0);


    for (int i = 0; i < grd.gridN; i++)
        mtr.C[i] = (grd.gridVolume[i] * lmb.density[i] * lmb.capacity[i] / dt) +
                   (-1 * mtr.A[i]) + (-1 * mtr.B[i]) + (-1 * mtr.D[i]) +
                   (-1 * mtr.E[i]);

    for (int i = 0; i < (grd.Nx - 2); i++)
        mtr.C[i] = grd.gridVolume[i] * lmb.density[i] * lmb.capacity[i] / dt;

    for (int i = (grd.Nx - 1);
         i < mtr.C.size() - (grd.Nx - 2); i += grd.Nx - 1)
        mtr.C[i] = grd.gridVolume[i] * lmb.density[i] * lmb.capacity[i] / dt;

    for (int i = mtr.C.size() - (grd.Nx - 2);
         i < mtr.C.size(); i++)
        mtr.C[i] = grd.gridVolume[i] * lmb.density[i] * lmb.capacity[i] / dt;

    for (int i = (grd.Nx - 2);
         i < mtr.C.size() - (grd.Nx - 1); i += grd.Nx - 1)
        mtr.C[i] = grd.gridVolume[i] * lmb.density[i] * lmb.capacity[i] / dt;
}

