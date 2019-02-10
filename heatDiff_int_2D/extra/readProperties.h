#ifndef READPROPERTIES_H
#define READPROPERTIES_H

#include <vector>

#include <extra/properties.h>

void readTable(std::vector<std::vector<double>> &table,
               const std::string &tableName);

std::vector<double> computeTInitial(const int& nY, const int& nX,
                                    const double& TInitial,
                                    const double& TLeft,
                                    const double& TRight);


#endif
