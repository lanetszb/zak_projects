#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>


struct Settings {

    double dt;
    double time;

    double TLeft;
    double TRight;
    double TTop;
    double TBot;
    double TInitial;

    double maxTolerance;
};

Settings getSettings(const std::string &fileName);

#endif
