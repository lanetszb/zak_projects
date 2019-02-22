#include <extra/jacobi.h>
#include <cmath>

#include <coefficients/coefficients.h>
#include <settings/settings.h>
#include <matrix/matrix.h>


void solveJacobiLS(const Matrix &matrix, const Coefficients &coefficients,
                   const Settings &settings,
                   std::vector<double> &X) {

    double curTolerance = 0;

    std::vector<std::vector<double>> Xcur{2, X};

    std::vector<int> dgInd;
    for (int i = 0; i < matrix.poi.size() - 1; i++)
        for (int j = matrix.poi[i]; j < matrix.poi[i + 1]; j++)
            if (i == matrix.col[j]) {
                dgInd.push_back(j);
                break;
            }

    unsigned int k = 0;

    do {

        for (int i = 0; i < matrix.poi.size() - 1; i++)
            Xcur[(k + 1) % 2][i] =
                    -coefficients.F[i] + Xcur[k % 2][i] * matrix.val[dgInd[i]];

        for (int i = 0; i < matrix.poi.size() - 1; i++)
            for (int j = matrix.poi[i]; j < matrix.poi[i + 1]; j++)
                Xcur[(k + 1) % 2][i] -=
                        matrix.val[j] * Xcur[k % 2][matrix.col[j]];

        for (int i = 0; i < matrix.poi.size() - 1; i++)
            Xcur[(k + 1) % 2][i] /= matrix.val[dgInd[i]];

        curTolerance = 0;
        for (int i = 0; i < matrix.poi.size() - 1; i++)
            curTolerance +=
                    fabs(2. * (Xcur[(k + 1) % 2][i] - Xcur[k % 2][i]) /
                         (Xcur[(k + 1) % 2][i] + Xcur[k % 2][i])) /
                    X.size();
        k++;


    } while (curTolerance > settings.maxTolerance);


    X = Xcur[k % 2];
}