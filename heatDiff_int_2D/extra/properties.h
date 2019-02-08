#ifndef EXTRA_PROPERTIES_H
#define EXTRA_PROPERTIES_H

#include <vector>

struct Properties {

    std::vector<std::vector<double>> lambdaTable;

    std::vector<std::vector<double>> densityTable;

    std::vector<std::vector<double>> capacityTable;

    std::vector<double> lambdaLeft;

    std::vector<double> lambdaRight;

    std::vector<double> lambdaTop;

    std::vector<double> lambdaBottom;

    std::vector<double> density;

    std::vector<double> capacity;

};

#endif
