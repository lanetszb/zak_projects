#include <extra/jacobi.h>
#include <cmath>

void computeLSJacobi(const Matrix &mtr, const Param &prm,
                     std::vector<double> &X) {

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
                Xcur[(k + 1) % 2][i] -=
                        mtr.val[j] * Xcur[k % 2][mtr.col[j]];

        for (int i = 0; i < mtr.poi.size() - 1; i++)
            Xcur[(k + 1) % 2][i] /= mtr.val[dgInd[i]];

        curTolerance = 0;
        for (int i = 0; i < mtr.poi.size() - 1; i++)
            curTolerance +=
                    fabs(2. * (Xcur[(k + 1) % 2][i] - Xcur[k % 2][i]) /
                         (Xcur[(k + 1) % 2][i] + Xcur[k % 2][i])) /
                    X.size();
        k++;


    } while (curTolerance > prm.maxTolerance);


    X = Xcur[k % 2];
}