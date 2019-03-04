#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

#include <vector>

#include <grid/grid.h>
#include <properties/properties.h>
#include <settings/settings.h>

/*!
\file
\brief This structure consists of coefficients required for
matrix calculation
*/


struct Coefficients {

    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C;
    std::vector<double> D;
    std::vector<double> E;
    std::vector<double> F;

};

/**
Creates matrix coefficients
@param[in] grid - takes total number of Cells from structure Grid
@return initiated coefficients with 0 values
*/

Coefficients initiateCoefficients(const Grid &grid);

/*!
runs the computation of all matrix coefficients
@param[in] coefficients - takes already created coefficients from structure
Coefficients
@param[in] grid - takes total number of Cells from structure Grid
@param[in] settings - takes the required settings from structure Settings
@param[in] properties - takes the required settings from structure Properties
\return coefficients - initiated coefficients are filled with 0 values
*/

void computeCoefficients(Coefficients &coefficients,
                         const Grid &grid,
                         const Settings &settings,
                         const Properties &properties,
                         const std::vector<double> &T);

/*!
computes matrix coefficient A
@param[in, out] coefficients - takes already created coefficient A
and computes it
@param[in] grid - takes total number of Cells, correspondent Surface and
Length from structure Grid
@param[in] properties - takes the correspondent Lambda from structure Properties
*/

void computeA(Coefficients &coefficients, const Grid &grid,
              const Properties &properties);

/*!
computes matrix coefficient B
@param[in, out] coefficients - takes already created coefficient B
and computes it
@param[in] grid - takes total number of Cells, correspondent Surface and
Length from structure Grid
@param[in] properties - takes the correspondent Lambda from structure Properties
*/

void computeB(Coefficients &coefficients, const Grid &grid,
              const Properties &properties);

/*!
computes matrix coefficient C
@param[in, out] coefficients - takes already created coefficients C and A, B, D, E,
and computes C
@param[in] grid - takes total number of Cells, Cells Volumes and
Length from structure Grid
@param[in] settings - takes time step dt from structure Settings
@param[in] properties - takes the correspondent capacity from structure
Properties
*/

void computeC(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties);
/*!
computes matrix coefficient D
@param[in, out] coefficients - takes already created coefficient D
and computes it

@param[in] grid - takes total number of Cells, correspondent Surface and
Length from structure Grid
@param[in] properties - takes the correspondent Lambda from structure Properties
*/

void computeD(Coefficients &coefficients, const Grid &grid,
              const Properties &properties);

/*!
computes matrix coefficient E
@param[in, out] coefficients - takes already created coefficient E
and computes it
@param[in] grid - takes total number of Cells, correspondent Surface and
Length from structure Grid
@param[in] properties - takes the correspondent Lambda from structure Properties
*/

void computeE(Coefficients &coefficients, const Grid &grid,
              const Properties &properties);

/*!
computes matrix coefficient F
@param[in, out] coefficients - takes already created coefficient F
and computes it
@param[in] grid - takes total number of Cells and Cells Volumes
from structure Grid
@param[in] settings - takes time step dt from structure Settings
@param[in] properties - takes the correspondent Density and Capacity of cells
from structure Properties
@param[in] T - takes the correspondent Temperature at current time step
*/

void computeF(Coefficients &coefficients, const Grid &grid,
              const Settings &settings, const Properties &properties,
              const std::vector<double> &T);

#endif
