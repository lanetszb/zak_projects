#include <vector>

#include <properties/properties.h>
#include <grid/grid.h>

#include <iostream>

Properties initializeProperties(const Grid &grid) {

    Properties properties;

    properties.lambda = std::vector<double>(grid.nCells, 0);
    properties.density = std::vector<double>(grid.nCells, 0);
    properties.capacity = std::vector<double>(grid.nCells, 0);

    properties.lambdaLeft = std::vector<double>(grid.nCells, 0);
    properties.lambdaRight = std::vector<double>(grid.nCells, 0);
    properties.lambdaTop = std::vector<double>(grid.nCells, 0);
    properties.lambdaBottom = std::vector<double>(grid.nCells, 0);

    properties.TLambdaLeft = std::vector<double>(grid.nCells, 0);
    properties.TLambdaRight = std::vector<double>(grid.nCells, 0);
    properties.TLambdaTop = std::vector<double>(grid.nCells, 0);
    properties.TLambdaBottom = std::vector<double>(grid.nCells, 0);

    return properties;

}


void computeCellsProperty(std::vector<double> &property,
                          const std::vector<double> &T,
                          const std::vector<std::vector<double>> &table) {

    for (int i = 0; i < property.size(); i++)
        property[i] = getValue(table, T[i]);

}


void computeCellsProperties(Properties &properties,
                            const PropertyTables &propertyTables,
                            const std::vector<double> &T) {

    /*computeCellsProperty(properties.lambda, T, propertyTables.lambda);*/
    computeCellsProperty(properties.density, T, propertyTables.density);
    computeCellsProperty(properties.capacity, T, propertyTables.capacity);

}


void computeSurfaceLambda(Properties &properties,
                          const Grid &grid,
                          const std::vector<double> &T,
                          const PropertyTables &propertyTables) {

    for (int i = 1; i < grid.nCells; i++) {
        properties.TLambdaLeft[i] = 2 * T[i] * T[i - 1] / (T[i] +
                                                           T[i - 1]);

        properties.lambdaLeft[i] = getValue(propertyTables.lambda,
                                            properties.TLambdaLeft[i]);

    }

    for (int i = 0; i < grid.nCells - 1; i++) {
        properties.TLambdaRight[i] = 2 * T[i] * T[i + 1] / (T[i] +
                                                            T[i + 1]);

        properties.lambdaRight[i] = getValue(propertyTables.lambda,
                                             properties.TLambdaRight[i]);

    }

    for (int i = 0; i < grid.nCells - (grid.nX - 1); i++) {

        properties.TLambdaTop[i] =
                2 * T[i] * T[i + (grid.nX - 1)] / (T[i] + T[i + (grid.nX - 1)]);

        properties.lambdaTop[i] = getValue(propertyTables.lambda,
                                           properties.TLambdaTop[i]);

    }

    for (int i = grid.nX - 1; i < grid.nCells; i++) {

        properties.TLambdaBottom[i] =
                2 * T[i] * T[i - (grid.nX - 1)] / (T[i] + T[i - (grid.nX - 1)]);

        properties.lambdaBottom[i] = getValue(propertyTables.lambda,
                                              properties.TLambdaBottom[i]);
    }


}


void computeProperties(Properties &properties,
                       const PropertyTables &propertyTables,
                       const std::vector<double> &T,
                       const Grid &grid) {

    computeCellsProperties(properties, propertyTables, T);
    computeSurfaceLambda(properties, grid, T, propertyTables);

}


