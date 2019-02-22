#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <vector>

#include <properties/properties.h>
#include <properties/propertyTables.h>
#include <grid/gridStruct.h>
#include <settings/settings.h>

struct Properties {

    std::vector<double> lambdaLeft;
    std::vector<double> lambdaRight;
    std::vector<double> lambdaTop;
    std::vector<double> lambdaBottom;
    std::vector<double> density;
    std::vector<double> capacity;

};


Properties initializeProperties(const Grid &grid);


void computeProperties(Properties &properties,
                       const PropertyTables &propertyTables,
                       const std::vector<double> &T, const Grid &grid);


void computeLambLeft(Properties &properties,
                     const PropertyTables &propertyTables,
                     const std::vector<double> &T, const Grid &grid);

void computeLambRight(Properties &properties,
                      const PropertyTables &propertyTables,
                      const std::vector<double> &T, const Grid &grid);

void computeLambTop(Properties &properties,
                    const PropertyTables &propertyTables,
                    const std::vector<double> &T, const Grid &grid);

void computeLambBot(Properties &properties,
                    const PropertyTables &propertyTables,
                    const std::vector<double> &T, const Grid &grid);

void computeDensity(Properties &properties,
                    const PropertyTables &propertyTables,
                    const std::vector<double> &T, const Grid &grid);

void computeCapacity(Properties &properties,
                     const PropertyTables &propertyTables,
                     const std::vector<double> &T, const Grid &grid);

#endif
