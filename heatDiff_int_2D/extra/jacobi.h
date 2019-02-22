#ifndef JACOBI_H
#define JACOBI_H

#include <coefficients/coefficients.h>
#include <param/param.h>
#include <matrix/matrix.h>

void solveJacobiLS(const Matrix &matrix, const Coefficients &coefficients,
                   const Param &param,
                   std::vector<double> &X);

#endif
