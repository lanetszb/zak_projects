#ifndef EXTRA_JACOBI_H
#define EXTRA_JACOBI_H

#include <param/param_struct.h>
#include <matrix/matrixStruct.h>

void computeLSJacobi(const Matrix &mtr, const Param &prm,
        std::vector<double> &X);

#endif
