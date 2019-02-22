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

    computeCellsProperty(properties.lambda, T, propertyTables.lambda);
    computeCellsProperty(properties.density, T, propertyTables.density);
    computeCellsProperty(properties.capacity, T, propertyTables.capacity);

}


void computeSurfaceLambda(Properties &properties, const Grid &grid) {

    for (int i = 0; i < grid.nCells; i++) {

        properties.lambdaLeft[i] = properties.lambda[i];
        properties.lambdaRight[i] = properties.lambda[i];
        properties.lambdaTop[i] = properties.lambda[i];
        properties.lambdaBottom[i] = properties.lambda[i];

    }

}


void computeProperties(Properties &properties,
                       const PropertyTables &propertyTables,
                       const std::vector<double> &T,
                       const Grid &grid) {

    computeCellsProperties(properties, propertyTables, T);
    computeSurfaceLambda(properties, grid);

}


