#include <matrix/matrixVect.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

void computeVal(Matrix &matrix, const Grid &grid) {

    matrix.val.clear();

    double valSize = grid.gridN + 4 * ((grid.nX - 3) * (grid.nY - 3));

    for (int i = 0; i < grid.nX - 1; i++)
        matrix.val.push_back(matrix.C[i]);

    int index = 0;
    for (int i = 1; i < grid.nY - 2; i++)
        for (int j = 0; j < grid.nX - 1; j++) {

            if (j == 0) {
                index = (i - 1) * (grid.nX - 1) + (grid.nX - 1);
                matrix.val.push_back(matrix.C[index]);

            } else if ((j > 0) && (j < grid.nX - 2) &&
                       (j % ((i - 1) * (grid.nX - 1) + (grid.nX - 1) -
                             i * (grid.nX - 1) + j) == 0)) {

                index = ((i - 1) * (grid.nX - 1) + (grid.nX - 1) + j);

                matrix.val.push_back(matrix.B[index]);
                matrix.val.push_back(matrix.A[index]);
                matrix.val.push_back(matrix.C[index]);
                matrix.val.push_back(matrix.D[index]);
                matrix.val.push_back(matrix.E[index]);

            } else if (j == grid.nX - 2) {
                index = (i - 1) * (grid.nX - 1) + (grid.nX - 1) + j;
                matrix.val.push_back(matrix.C[index]);
            }
        }

    for (int i = 0; i < grid.nX - 1; i++) {
        index = grid.gridN - (grid.nX - 1) + i;
        matrix.val.push_back(matrix.C[index]);
    }

}

// Vector Col
void col_calc(const Grid &grd, Matrix &mtr) {

    mtr.col.clear();

    double valSize = 0;
    valSize = grd.gridN + 4 * ((grd.nX - 3) * (grd.nY - 3));
    int calSize = valSize;

    double indCur = 0;
    double value = 0;

    std::vector<double> cal_mid;

    for (int i = 1; i < grd.nX - 2; i++)
        for (int j = 1; j < 6; j++) {

            if (j == 1) {
                indCur = grd.nX - (grd.nX - 1) + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 5) {
                indCur = grd.nX + (grd.nX - 1) + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 2) {
                indCur = (grd.nX - 1) + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 3) {
                indCur = grd.nX + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            } else if (j == 4) {
                indCur = grd.nX + 1 + (i - 1);
                value = indCur;
                cal_mid.push_back(value);
            }
        }

    std::vector<double> cal_mid_1;

    for (int i = 1; i < grd.nY - 2; i++)
        for (int j = 0; j < cal_mid.size(); j++) {
            indCur = cal_mid[j] + (i - 1) * (grd.nX - 1);
            value = indCur;
            cal_mid_1.push_back(value);
        }

    value = 0;
    for (int i = 0; i < grd.nX - 1; i++) {
        value = i;
        mtr.col.push_back(value);
    }

    indCur = 0;
    value = 0;
    for (int i = 1; i < grd.nY - 2; i++)
        for (int j = 0; j < 2 + 5 * (grd.nX - 3); j++) {

            if (j == 0) {
                indCur = i * (grd.nX - 1);
                value = indCur;
                mtr.col.push_back(value);

            } else if ((j > 0) && (j < 2 + 5 * (grd.nX - 3) - 1)) {

                indCur = cal_mid_1[(i - 1) * 5 * (grd.nX - 3) + j - 1];
                value = indCur;
                mtr.col.push_back(value);


            } else if (j == 2 + 5 * (grd.nX - 3) - 1) {

                indCur = i * (grd.nX - 1) + grd.nX - 2;
                value = indCur;
                mtr.col.push_back(value);
            }
        }

    value = 0;
    for (int i = grd.gridN - (grd.nX - 1); i < grd.gridN; i++) {
        value = i;
        mtr.col.push_back(value);
    }

}


// Vector Poi
void poi_calc(const Grid &grd, Matrix &mtr) {

    mtr.poi.clear();

    double value = 0;
    double indCur = 0;

    for (int i = 0; i < grd.nX - 1; i++) {
        value = i;
        mtr.poi.push_back(value);
    }

    for (int i = 1; i < grd.nY - 2; i++)
        for (int j = 0; j < 5 * (grd.nX - 1); j += 5) {

            if (j == 0) {
                value = (grd.nX - 1) + (i - 1) * (2 + 5 * (grd.nX - 3));
                indCur = value;
                mtr.poi.push_back(value);
            } else if ((j > 0) && (j < 5 * (grd.nX - 1))) {
                value = (grd.nX + (j - 5)) + (i - 1) * (2 + 5 * (grd.nX - 3));
                mtr.poi.push_back(value);
            }
        }

    value = 0;
    for (int i = 1; i < grd.nX + 1; i++) {
        value = mtr.poi[grd.gridN - (grd.nX - 1) - 1] + i;
        mtr.poi.push_back(value);
    }


}
