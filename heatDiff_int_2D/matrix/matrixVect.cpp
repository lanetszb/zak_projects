#include <matrix/matrixVect.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

void val_calc(const Grid &grd, Matrix &mtr) {
// Vector Val
    mtr.val.clear();

    double valSize = 0;
    valSize = grd.gridN + 4 * ((grd.Nx - 3) * (grd.Ny - 3));


    double value = 0;

    for (int i = 0; i < grd.Nx - 1; i++) {
        value = mtr.C[i];
        mtr.val.push_back(value);
    }

    int indCur = 0;
    value = 0;
    for (int i = 1; i < grd.Ny - 2; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {

            if (j == 0) {
                indCur = (i - 1) * (grd.Nx - 1) + (grd.Nx - 1);
                value = mtr.C[indCur];
                mtr.val.push_back(value);

            } else if ((j > 0) && (j < grd.Nx - 2) &&
                       (j % ((i - 1) * (grd.Nx - 1) + (grd.Nx - 1) -
                             i * (grd.Nx - 1) + j) == 0)) {

                indCur = ((i - 1) * (grd.Nx - 1) + (grd.Nx - 1) + j);

                value = mtr.B[indCur];
                mtr.val.push_back(value);

                value = mtr.A[indCur];
                mtr.val.push_back(value);

                value = mtr.C[indCur];
                mtr.val.push_back(value);

                value = mtr.D[indCur];
                mtr.val.push_back(value);

                value = mtr.E[indCur];
                mtr.val.push_back(value);

            } else if (j == grd.Nx - 2) {
                indCur = (i - 1) * (grd.Nx - 1) + (grd.Nx - 1) + j;
                value = mtr.C[indCur];
                mtr.val.push_back(value);
            }
        }

    indCur = 0;
    value = 0;
    for (int i = 0; i < grd.Nx - 1; i++) {
        indCur = grd.gridN - (grd.Nx - 1) + i;
        value = mtr.C[indCur];
        mtr.val.push_back(value);

    }

}

// Vector Col
void col_calc(const Grid &grd, Matrix &mtr) {

    mtr.col.clear();

    double valSize = 0;
    valSize = grd.gridN + 4 * ((grd.Nx - 3) * (grd.Ny - 3));
    int calSize = valSize;

    double indCur = 0;
    double value = 0;

    std::vector<double> cal_mid;

    for (int i = 1; i < grd.Nx - 2; i++)
        for (int j = 1; j < 6; j++) {

            if (j == 1) {
                indCur = grd.Nx - (grd.Nx - 1) + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 5) {
                indCur = grd.Nx + (grd.Nx - 1) + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 2) {
                indCur = (grd.Nx - 1) + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 3) {
                indCur = grd.Nx + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 4) {
                indCur = grd.Nx + 1 + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            }
        }

    std::vector<double> cal_mid_1;

    for (int i = 1; i < grd.Ny - 2; i++)
        for (int j = 0; j < cal_mid.size(); j++) {
            indCur = cal_mid[j] + (i - 1) * (grd.Nx - 1);
            value = indCur;
            cal_mid_1.push_back(value);
        }

    value = 0;
    for (int i = 0; i < grd.Nx - 1; i++) {
        value = i;
        mtr.col.push_back(value);
    }

    indCur = 0;
    value = 0;
    for (int i = 1; i < grd.Ny - 2; i++)
        for (int j = 0; j < 2 + 5 * (grd.Nx - 3); j++) {

            if (j == 0) {
                indCur = i * (grd.Nx - 1);
                value = indCur;
                mtr.col.push_back(value);

            } else if ((j > 0) && (j < 2 + 5 * (grd.Nx - 3) - 1)) {

                indCur = cal_mid_1[(i - 1) * 5 * (grd.Nx - 3) + j - 1];
                value = indCur;
                mtr.col.push_back(value);


            } else if (j == 2 + 5 * (grd.Nx - 3) - 1) {

                indCur = i * (grd.Nx - 1) + grd.Nx - 2;
                value = indCur;
                mtr.col.push_back(value);
            }
        }

    value = 0;
    for (int i = grd.gridN - (grd.Nx - 1); i < grd.gridN; i++) {
        value = i;
        mtr.col.push_back(value);
    }

}


// Vector Poi
void poi_calc(const Grid &grd, Matrix &mtr) {

    mtr.poi.clear();

    double value = 0;
    double indCur = 0;

    for (int i = 0; i < grd.Nx - 1; i++) {
        value = i;
        mtr.poi.push_back(value);
    }

    for (int i = 1; i < grd.Ny - 2; i++)
        for (int j = 0; j < 5 * (grd.Nx - 1); j += 5) {

            if (j == 0) {
                value = (grd.Nx - 1) + (i - 1) * (2 + 5 * (grd.Nx - 3));
                indCur = value;
                mtr.poi.push_back(value);
            } else if ((j > 0) && (j < 5 * (grd.Nx - 1))) {
                value = (grd.Nx + (j - 5)) + (i - 1) * (2 + 5 * (grd.Nx - 3));
                mtr.poi.push_back(value);
            }
        }

    value = 0;
    for (int i = 1; i < grd.Nx + 1; i++) {
        value = mtr.poi[grd.gridN - (grd.Nx - 1) - 1] + i;
        mtr.poi.push_back(value);
    }


}
