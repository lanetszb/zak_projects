#ifndef PARAM_H
#define PARAM_H

#include <string>


struct Param {

    double dt;
    double time;
    double lambda;

    double TLeft;
    double TRight;
    double Ttop;
    double Tbot;
    double TInitial;

    double maxTolerance;
};

Param getParam(const std::string &fileName);

#endif
