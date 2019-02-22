#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

#include <vector>

#include <grid/gridStruct.h>
#include <properties/properties.h>
#include <settings/settings.h>


struct Coefficients {

    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C;
    std::vector<double> D;
    std::vector<double> E;
    std::vector<double> F;

};


Coefficients initiateCoefficients(const Grid &grid);


void computeCoefficients(Coefficients &coefficients,
                         const Grid &grid,
                         const Settings &settings,
                         const Properties &properties,
                         const std::vector<double> &T);


void computeA(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties);

void computeB(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties);

void computeC(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties);

void computeD(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties);

void computeE(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties);

void computeF(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties,
              const std::vector<double> &T);

#endif
