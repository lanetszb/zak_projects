#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>


struct Settings {

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

Settings getSettings(const std::string &fileName);

#endif
