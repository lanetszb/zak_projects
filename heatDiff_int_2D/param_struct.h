#ifndef PARAM_STRUCT_H
#define PARAM_STRUCT_H

#include <vector>

// Structure containing all calculation parameters.
struct Param {

    double dt;
    double time;
    double lambda;

    double Tl;
    double Tr;
    double Ttop;
    double Tbot;
    double T0;

    double dens;
    double capac;

    double maxTolerance;

    std::vector<double> getBot_lambda;
    std::vector<double> getTop_lambda;
    std::vector<double> getLeft_lambda;
    std::vector<double> getRight_lambda;
};

#endif 
