#ifndef READPROPERTIES_H
#define READPROPERTIES_H

#include <vector>

#include <extra/properties.h>


void readLambda(Properties &properties, const std::string &lambdaTable);

void readDensity(Properties &properties, const std::string &densityTable);

void readCapacity(Properties &properties, const std::string &capacityTable);

std::vector<double> computeTInitial(const int& nY, const int& nX,
                                    const double& TInitial,
                                    const double& TLeft,
                                    const double& TRight);


#endif
