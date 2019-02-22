#ifndef JACOBI_H
#define JACOBI_H

#include <coefficients/coefficients.h>
#include <settings/settings.h>
#include <matrix/matrix.h>

void solveJacobiLS(const Matrix &matrix, const Coefficients &coefficients,
                   const Settings &settings,
                   std::vector<double> &X);

#endif
