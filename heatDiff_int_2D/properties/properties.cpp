#include <properties/properties.h>
#include <extra/computeTInitial.h>
#include <iostream>

void computeProperties(Properties &properties,
                       const PropertyTables &propertyTables,
                       const std::vector<double> &TPrevious,
                       const Grid &grid) {

    computeLambLeft(properties, propertyTables, TPrevious, grid);
    computeLambRight(properties, propertyTables, TPrevious, grid);
    computeLambTop(properties, propertyTables, TPrevious, grid);
    computeLambBot(properties, propertyTables, TPrevious, grid);
    computeDensity(properties, propertyTables, TPrevious, grid);
    computeCapacity(properties, propertyTables, TPrevious, grid);
}

void computeLambLeft(Properties &properties,
                     const PropertyTables &propertyTables,
                     const std::vector<double> &T,
                     const Grid &grid) {


    int gridN = (grid.nX - 1) * (grid.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);


    for (int i = 1; i < gridN; i++)
        lambTemp[i] = 2 * T[i - 1] * T[i] / (T[i] + T[i - 1]);

    properties.lambdaLeft.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < propertyTables.lambdaTable.size(); j++) {
            if (lambTemp[i] >= propertyTables.lambdaTable[j][0] &&
                lambTemp[i] < propertyTables.lambdaTable[j + 1][0]) {
                properties.lambdaLeft.push_back(
                        propertyTables.lambdaTable[j][1] +
                        ((propertyTables.lambdaTable[j + 1][1] -
                          propertyTables.lambdaTable[j][1]) /
                         (propertyTables.lambdaTable[j + 1][0] -
                          propertyTables.lambdaTable[j][0])) *
                        (lambTemp[i] - propertyTables.lambdaTable[j][0]));
                break;
            }
        }
}

void computeLambRight(Properties &properties,
                      const PropertyTables &propertyTables,
                      const std::vector<double> &T,
                      const Grid &grid) {

    int gridN = (grid.nX - 1) * (grid.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN - 1; i++)
        lambTemp[i] = 2 * T[i + 1] * T[i] / (T[i] + T[i + 1]);

    properties.lambdaRight.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < propertyTables.lambdaTable.size(); j++) {
            if (lambTemp[i] >= propertyTables.lambdaTable[j][0] &&
                lambTemp[i] < propertyTables.lambdaTable[j + 1][0]) {
                properties.lambdaRight.push_back(
                        propertyTables.lambdaTable[j][1] +
                        ((propertyTables.lambdaTable[j + 1][1] -
                          propertyTables.lambdaTable[j][1]) /
                         (propertyTables.lambdaTable[j + 1][0] -
                          propertyTables.lambdaTable[j][0])) *
                        (lambTemp[i] - propertyTables.lambdaTable[j][0]));
                break;
            }
        }
}

void computeLambTop(Properties &properties,
                    const PropertyTables &propertyTables,
                    const std::vector<double> &T,
                    const Grid &grid) {

    int gridN = (grid.nX - 1) * (grid.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN - (grid.nX - 1); i++)
        lambTemp[i] =
                2 * T[i + grid.nX - 1] * T[i] / (T[i] + T[i + grid.nX - 1]);

    properties.lambdaTop.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < propertyTables.lambdaTable.size(); j++) {
            if (lambTemp[i] >= propertyTables.lambdaTable[j][0] &&
                lambTemp[i] < propertyTables.lambdaTable[j + 1][0]) {
                properties.lambdaTop.push_back(
                        propertyTables.lambdaTable[j][1] +
                        ((propertyTables.lambdaTable[j + 1][1] -
                          propertyTables.lambdaTable[j][1]) /
                         (propertyTables.lambdaTable[j + 1][0] -
                          propertyTables.lambdaTable[j][0])) *
                        (lambTemp[i] - propertyTables.lambdaTable[j][0]));
                break;
            }
        }
}

void computeLambBot(Properties &properties,
                    const PropertyTables &propertyTables,
                    const std::vector<double> &T,
                    const Grid &grid) {

    int gridN = (grid.nX - 1) * (grid.nY - 1);

    std::vector<double> lambTemp;
    lambTemp = std::vector<double>(gridN, 0);

    for (int i = grid.nX - 1; i < gridN; i++)
        lambTemp[i] =
                2 * T[i - (grid.nX - 1)] * T[i] / (T[i] + T[i - (grid.nX - 1)]);

    properties.lambdaBottom.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < propertyTables.lambdaTable.size(); j++) {
            if (lambTemp[i] >= propertyTables.lambdaTable[j][0] &&
                lambTemp[i] < propertyTables.lambdaTable[j + 1][0]) {
                properties.lambdaBottom.push_back(
                        propertyTables.lambdaTable[j][1] +
                        ((propertyTables.lambdaTable[j + 1][1] -
                          propertyTables.lambdaTable[j][1]) /
                         (propertyTables.lambdaTable[j + 1][0] -
                          propertyTables.lambdaTable[j][0])) *
                        (lambTemp[i] - propertyTables.lambdaTable[j][0]));
                break;
            }
        }
}

void computeDensity(Properties &properties,
                    const PropertyTables &propertyTables,
                    const std::vector<double> &T,
                    const Grid &grid) {

    int gridN = (grid.nX - 1) * (grid.nY - 1);

    std::vector<double> densityTemp;
    densityTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN; i++)
        densityTemp[i] = T[i];

    properties.density.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < propertyTables.densityTable.size(); j++) {
            if (densityTemp[i] >= propertyTables.densityTable[j][0] &&
                densityTemp[i] < propertyTables.densityTable[j + 1][0]) {
                properties.density.push_back(
                        propertyTables.densityTable[j][1] +
                        ((propertyTables.densityTable[j + 1][1] -
                          propertyTables.densityTable[j][1]) /
                         (propertyTables.densityTable[j + 1][0] -
                          propertyTables.densityTable[j][0])) *
                        (densityTemp[i] - propertyTables.densityTable[j][0]));
                break;
            }
        }
}

void computeCapacity(Properties &properties,
                     const PropertyTables &propertyTables,
                     const std::vector<double> &T,
                     const Grid &grid) {

    int gridN = (grid.nX - 1) * (grid.nY - 1);

    std::vector<double> capacityTemp;
    capacityTemp = std::vector<double>(gridN, 0);

    for (int i = 0; i < gridN; i++)
        capacityTemp[i] = T[i];

    properties.density.clear();

    for (int i = 0; i < gridN; i++)
        for (int j = 0; j < propertyTables.capacityTable.size(); j++) {
            if (capacityTemp[i] >= propertyTables.capacityTable[j][0] &&
                capacityTemp[i] < propertyTables.capacityTable[j + 1][0]) {
                properties.capacity.push_back(
                        propertyTables.capacityTable[j][1] +
                        ((propertyTables.capacityTable[j + 1][1] -
                          propertyTables.capacityTable[j][1]) /
                         (propertyTables.capacityTable[j + 1][0] -
                          propertyTables.capacityTable[j][0])) *
                        (capacityTemp[i] - propertyTables.densityTable[j][0]));
                break;
            }
        }
}


