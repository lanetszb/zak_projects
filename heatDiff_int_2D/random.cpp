#include <vector>
#include <cmath>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>
#include <random.h>

void getLamb(const std::string &thermalCond_table) {
    GetFromFile lambTable(thermalCond_table);

    int vec2DCol = lambTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = lambTable.getVector<double>("vec2D");
    std::vector<std::vector<double> > vec2D;
    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        vec2D.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            vec2D.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }

    std::cout << "vec2DCol " << vec2DCol << std::endl;
    std::cout << "vec2D" << std::endl;
    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[i].size(); j++)
            std::cout << vec2D[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
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