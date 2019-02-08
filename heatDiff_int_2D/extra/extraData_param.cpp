#include <extra/extraData_param.h>

void getLeft_lamb(Lamb &lmb,
                  const Grid &grd, const std::vector<double> &X) {


    int gridN = (grd.Nx - 1) * (grd.Ny - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);


    for (int i = 1; i < gridN; i++)
        lambTemp[i] = 2 * X[i - 1] * X[i] / (X[i] + X[i - 1]);

    lmb.leftLamb.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < lmb.lambTable.size(); j++) {
            if (lambTemp[i] >= lmb.lambTable[j][0] &&
                lambTemp[i] < lmb.lambTable[j + 1][0]) {
                lmb.leftLamb.push_back(lmb.lambTable[j][1] +
                                       ((lmb.lambTable[j + 1][1] -
                                         lmb.lambTable[j][1]) /
                                        (lmb.lambTable[j + 1][0] -
                                         lmb.lambTable[j][0])) *
                                       (lambTemp[i] - lmb.lambTable[j][0]));
                break;
            }
        }
}

void getRight_lamb(Lamb &lmb,
                   const Grid &grd, const std::vector<double> &X) {

    int gridN = (grd.Nx - 1) * (grd.Ny - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN - 1; i++)
        lambTemp[i] = 2 * X[i + 1] * X[i] / (X[i] + X[i + 1]);

    lmb.rightLamb.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < lmb.lambTable.size(); j++) {
            if (lambTemp[i] >= lmb.lambTable[j][0] &&
                lambTemp[i] < lmb.lambTable[j + 1][0]) {
                lmb.rightLamb.push_back(lmb.lambTable[j][1] +
                                        ((lmb.lambTable[j + 1][1] -
                                          lmb.lambTable[j][1]) /
                                         (lmb.lambTable[j + 1][0] -
                                          lmb.lambTable[j][0])) *
                                        (lambTemp[i] - lmb.lambTable[j][0]));
                break;
            }
        }
}

void getTop_lamb(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X) {

    int gridN = (grd.Nx - 1) * (grd.Ny - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN - (grd.Nx - 1); i++)
        lambTemp[i] = 2 * X[i + grd.Nx - 1] * X[i] / (X[i] + X[i + grd.Nx - 1]);

    lmb.topLamb.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < lmb.lambTable.size(); j++) {
            if (lambTemp[i] >= lmb.lambTable[j][0] &&
                lambTemp[i] < lmb.lambTable[j + 1][0]) {
                lmb.topLamb.push_back(lmb.lambTable[j][1] +
                                      ((lmb.lambTable[j + 1][1] -
                                        lmb.lambTable[j][1]) /
                                       (lmb.lambTable[j + 1][0] -
                                        lmb.lambTable[j][0])) *
                                      (lambTemp[i] - lmb.lambTable[j][0]));
                break;
            }
        }
}

void getBot_lamb(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X) {

    int gridN = (grd.Nx - 1) * (grd.Ny - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = grd.Nx - 1; i < gridN; i++)
        lambTemp[i] =
                2 * X[i - (grd.Nx - 1)] * X[i] / (X[i] + X[i - (grd.Nx - 1)]);

    lmb.botLamb.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < lmb.lambTable.size(); j++) {
            if (lambTemp[i] >= lmb.lambTable[j][0] &&
                lambTemp[i] < lmb.lambTable[j + 1][0]) {
                lmb.botLamb.push_back(lmb.lambTable[j][1] +
                                      ((lmb.lambTable[j + 1][1] -
                                        lmb.lambTable[j][1]) /
                                       (lmb.lambTable[j + 1][0] -
                                        lmb.lambTable[j][0])) *
                                      (lambTemp[i] - lmb.lambTable[j][0]));
                break;
            }
        }
}

void getDensity(Lamb &lmb,
                const Grid &grd, const std::vector<double> &X) {

    int gridN = (grd.Nx - 1) * (grd.Ny - 1);

    std::vector<double> densityTemp;
    densityTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN; i++)
        densityTemp[i] = X[i];

    lmb.density.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < lmb.densTable.size(); j++) {
            if (densityTemp[i] >= lmb.densTable[j][0] &&
                densityTemp[i] < lmb.densTable[j + 1][0]) {
                lmb.density.push_back(lmb.densTable[j][1] +
                                      ((lmb.densTable[j + 1][1] -
                                        lmb.densTable[j][1]) /
                                       (lmb.densTable[j + 1][0] -
                                        lmb.densTable[j][0])) *
                                      (densityTemp[i] - lmb.densTable[j][0]));
                break;
            }
        }
}

void getCapacity(Lamb &lmb,
                 const Grid &grd, const std::vector<double> &X) {

    int gridN = (grd.Nx - 1) * (grd.Ny - 1);

    std::vector<double> capacityTemp;
    capacityTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN; i++)
        capacityTemp[i] = X[i];

    lmb.density.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < lmb.capacTable.size(); j++) {
            if (capacityTemp[i] >= lmb.capacTable[j][0] &&
                capacityTemp[i] < lmb.capacTable[j + 1][0]) {
                lmb.capacity.push_back(lmb.capacTable[j][1] +
                                       ((lmb.capacTable[j + 1][1] -
                                         lmb.capacTable[j][1]) /
                                        (lmb.capacTable[j + 1][0] -
                                         lmb.capacTable[j][0])) *
                                       (capacityTemp[i] - lmb.densTable[j][0]));
                break;
            }
        }
}
