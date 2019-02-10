#include <extra/computeProperties.h>
#include <extra/readProperties.h>
#include <iostream>

void readTables(Properties &properties,
                const std::string &lambdaTableName,
                const std::string &densityTableName,
                const std::string &capacityTableName) {

    readTable(properties.lambdaTable, lambdaTableName);
    readTable(properties.densityTable, densityTableName);
    readTable(properties.capacityTable, capacityTableName);

}

void computeProperties(Properties &properties, const Grid &grid,
                       std::vector<double> &T) {

    computeLambLeft(properties, grid, T);
    computeLambRight(properties, grid, T);
    computeLambTop(properties, grid, T);
    computeLambBot(properties, grid, T);

    computeDensity(properties, grid, T);
    computeCapacity(properties, grid, T);
}

void computeLambLeft(Properties &properties,
                     const Grid &grd, const std::vector<double> &T) {


    int gridN = (grd.nX - 1) * (grd.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);


    for (int i = 1; i < gridN; i++)
        lambTemp[i] = 2 * T[i - 1] * T[i] / (T[i] + T[i - 1]);

    properties.lambdaLeft.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < properties.lambdaTable.size(); j++) {
            if (lambTemp[i] >= properties.lambdaTable[j][0] &&
                lambTemp[i] < properties.lambdaTable[j + 1][0]) {
                properties.lambdaLeft.push_back(properties.lambdaTable[j][1] +
                                       ((properties.lambdaTable[j + 1][1] -
                                         properties.lambdaTable[j][1]) /
                                        (properties.lambdaTable[j + 1][0] -
                                         properties.lambdaTable[j][0])) *
                                       (lambTemp[i] - properties.lambdaTable[j][0]));
                break;
            }
        }
}

void computeLambRight(Properties &properties,
                      const Grid &grd, const std::vector<double> &T) {

    int gridN = (grd.nX - 1) * (grd.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN - 1; i++)
        lambTemp[i] = 2 * T[i + 1] * T[i] / (T[i] + T[i + 1]);

    properties.lambdaRight.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < properties.lambdaTable.size(); j++) {
            if (lambTemp[i] >= properties.lambdaTable[j][0] &&
                lambTemp[i] < properties.lambdaTable[j + 1][0]) {
                properties.lambdaRight.push_back(properties.lambdaTable[j][1] +
                                        ((properties.lambdaTable[j + 1][1] -
                                          properties.lambdaTable[j][1]) /
                                         (properties.lambdaTable[j + 1][0] -
                                          properties.lambdaTable[j][0])) *
                                        (lambTemp[i] - properties.lambdaTable[j][0]));
                break;
            }
        }
}

void computeLambTop(Properties &properties,
                    const Grid &grd, const std::vector<double> &T) {

    int gridN = (grd.nX - 1) * (grd.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN - (grd.nX - 1); i++)
        lambTemp[i] = 2 * T[i + grd.nX - 1] * T[i] / (T[i] + T[i + grd.nX - 1]);

    properties.lambdaTop.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < properties.lambdaTable.size(); j++) {
            if (lambTemp[i] >= properties.lambdaTable[j][0] &&
                lambTemp[i] < properties.lambdaTable[j + 1][0]) {
                properties.lambdaTop.push_back(properties.lambdaTable[j][1] +
                                      ((properties.lambdaTable[j + 1][1] -
                                        properties.lambdaTable[j][1]) /
                                       (properties.lambdaTable[j + 1][0] -
                                        properties.lambdaTable[j][0])) *
                                      (lambTemp[i] - properties.lambdaTable[j][0]));
                break;
            }
        }
}

void computeLambBot(Properties &properties,
                    const Grid &grd, const std::vector<double> &T) {

    int gridN = (grd.nX - 1) * (grd.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = grd.nX - 1; i < gridN; i++)
        lambTemp[i] =
                2 * T[i - (grd.nX - 1)] * T[i] / (T[i] + T[i - (grd.nX - 1)]);

    properties.lambdaBottom.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < properties.lambdaTable.size(); j++) {
            if (lambTemp[i] >= properties.lambdaTable[j][0] &&
                lambTemp[i] < properties.lambdaTable[j + 1][0]) {
                properties.lambdaBottom.push_back(properties.lambdaTable[j][1] +
                                      ((properties.lambdaTable[j + 1][1] -
                                        properties.lambdaTable[j][1]) /
                                       (properties.lambdaTable[j + 1][0] -
                                        properties.lambdaTable[j][0])) *
                                      (lambTemp[i] - properties.lambdaTable[j][0]));
                break;
            }
        }
}

void computeDensity(Properties &properties,
                    const Grid &grd, const std::vector<double> &T) {

    int gridN = (grd.nX - 1) * (grd.nY - 1);

    std::vector<double> densityTemp;
    densityTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN; i++)
        densityTemp[i] = T[i];

    properties.density.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < properties.densityTable.size(); j++) {
            if (densityTemp[i] >= properties.densityTable[j][0] &&
                densityTemp[i] < properties.densityTable[j + 1][0]) {
                properties.density.push_back(properties.densityTable[j][1] +
                                      ((properties.densityTable[j + 1][1] -
                                        properties.densityTable[j][1]) /
                                       (properties.densityTable[j + 1][0] -
                                        properties.densityTable[j][0])) *
                                      (densityTemp[i] - properties.densityTable[j][0]));
                break;
            }
        }
}

void computeCapacity(Properties &properties,
                     const Grid &grd, const std::vector<double> &T) {

    int gridN = (grd.nX - 1) * (grd.nY - 1);

    std::vector<double> capacityTemp;
    capacityTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN; i++)
        capacityTemp[i] = T[i];

    properties.density.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < properties.capacityTable.size(); j++) {
            if (capacityTemp[i] >= properties.capacityTable[j][0] &&
                capacityTemp[i] < properties.capacityTable[j + 1][0]) {
                properties.capacity.push_back(properties.capacityTable[j][1] +
                                       ((properties.capacityTable[j + 1][1] -
                                         properties.capacityTable[j][1]) /
                                        (properties.capacityTable[j + 1][0] -
                                         properties.capacityTable[j][0])) *
                                       (capacityTemp[i] - properties.densityTable[j][0]));
                break;
            }
        }
}
