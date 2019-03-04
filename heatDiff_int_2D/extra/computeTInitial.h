#ifndef COMPUTETINITIAL_H
#define COMPUTETINITIAL_H

#include <vector>

#include <properties/properties.h>

/*!
\file
\brief This function computes the initial temperature distribution at all cells
*/

/**
Creates inittial temperature distribution
@param[in] grid - takes total number of nodes in X and Y directions
@param[in] settings - initial temperature at boundaries and in the center
@return initial temperature distribution
*/

std::vector<double> computeTInitial(const Grid &grid, const Settings &settings);


#endif
