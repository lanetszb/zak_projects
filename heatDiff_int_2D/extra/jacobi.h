#ifndef JACOBI_H
#define JACOBI_H

#include <coefficients/coefficients.h>
#include <settings/settings.h>
#include <matrix/matrix.h>

/*!
\file
\brief This function the system of linear differential equations using
Jacobi approach
*/

/**
Solves the system of linear differential equations and computes the Temperature
at next time step
@param[in] matrix - takes values, pointer and columns for matrix reconstruction
@param[in] coefficients - takes F coefficient
@param[in] coefficients - takes value of maximum acceptable error
for convergence
@return temperature at next time step
*/

void solveJacobiLS(const Matrix &matrix, const Coefficients &coefficients,
                   const Settings &settings,
                   std::vector<double> &X);

#endif
