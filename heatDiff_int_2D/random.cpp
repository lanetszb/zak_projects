#include <vector>
#include <cmath>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>
#include <random.h>


void readLamb(Lamb &lmb, const std::string &thermalCond_table) {

    GetFromFile readTable(thermalCond_table);

    int vec2DCol = readTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = readTable.getVector<double>("vec2D");


    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        lmb.lambTable.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            lmb.lambTable.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }
}

void getLeft_lamb(Lamb &lmb,
                  const Grid &grd, const std::vector<double> &X) {

    int gridN = (grd.Nx - 1) * (grd.Ny - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);


    for (int i = 1; i < gridN; i++)
        lambTemp[i] = 2 * X[i - 1] * X[i] / (X[i] + X[i - 1]);

    lmb.leftLamb.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < gridN; j++) {
            if (lambTemp[i] >= lmb.lambTable[j][0] &&
                lambTemp[i] < lmb.lambTable[j + 1][0]) {
                lmb.leftLamb.push_back(
                        lmb.lambTable[j][1] +
                        ((lmb.lambTable[j + 1][1] - lmb.lambTable[j][1]) /
                         (lmb.lambTable[j + 1][0] - lmb.lambTable[j][0])) *
                        (lambTemp[i] - lmb.lambTable[j][0])
                );
                break;
            }
        }

  /*  for (int i = 0; i < lmb.leftLamb.size(); i++)
        std::cout << lmb.leftLamb[i] << " ";
    std::cout << std::endl << " ";*/
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
            Xcur[(k + 1) % 2][i] =
                    -mtr.F[i] + Xcur[k % 2][i] * mtr.val[dgInd[i]];

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


