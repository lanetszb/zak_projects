#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <vector>

#include <properties/properties.h>
#include <properties/propertyTables.h>
#include <grid/grid.h>
#include <settings/settings.h>

struct Properties {

    std::vector<double> lambda;
    std::vector<double> density;
    std::vector<double> capacity;

    std::vector<double> lambdaLeft;
    std::vector<double> lambdaRight;
    std::vector<double> lambdaTop;
    std::vector<double> lambdaBottom;

    std::vector<double> TLambdaLeft;
    std::vector<double> TLambdaRight;
    std::vector<double> TLambdaTop;
    std::vector<double> TLambdaBottom;

};

Properties initializeProperties(const Grid &grid);


void computeCellsProperty(std::vector<double> &property,
                          const std::vector<double> &T,
                          const std::vector<std::vector<double>> &table);

void computeCellsProperties(Properties &properties,
                            const PropertyTables &propertyTables,
                            const std::vector<double> &T);


void computeSurfaceLambda(Properties &properties,
                          const Grid &grid,
                          const std::vector<double> &T,
                          const PropertyTables &propertyTables);


void computeProperties(Properties &properties,
                       const PropertyTables &propertyTables,
                       const std::vector<double> &T, const Grid &grid);


#endif
