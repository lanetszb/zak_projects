#ifndef JACOBI_H
#define JACOBI_H

#include <coefficients/coefficients.h>
#include <param/param_struct.h>
#include <matrix/matrix.h>

void computeLSJacobi(const Matrix &matrix, const Coefficients &coefficients,
                     const Param &param,
                     std::vector<double> &X);

#endif
