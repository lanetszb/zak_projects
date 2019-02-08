#ifndef EXTRAFILES_STRUCT_H
#define EXTRAFILES_STRUCT_H

#include <vector>

struct Lamb {

    std::vector<std::vector<double> > lambTable;

    std::vector<std::vector<double> > densTable;

    std::vector<std::vector<double> > capacTable;

    std::vector<double> leftLamb;

    std::vector<double> rightLamb;

    std::vector<double> topLamb;

    std::vector<double> botLamb;

    std::vector<double> density;

    std::vector<double> capacity;

};

#endif
