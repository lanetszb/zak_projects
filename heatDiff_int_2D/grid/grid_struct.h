#ifndef GRID_STRUCT_H
#define GRID_STRUCT_H

#include <vector>

// Structure containing all grid attributes.
struct Grid {
    // Nodes quantity in x direction.
    int Nx;

    // Nodes quantity in y direction.
    int Ny;

    // total number of grid blocks.
    int gridN;

    // dx
    double dx;

    // dy
    double dy;

    // x coordinates of grid blocks.
    std::vector<double> X_coord;

    // y coordinates of grid blocks.
    std::vector<double> Y_coord;

    // x coordinates of grid block centers.
    std::vector<double> Xcenter;

    // y coordinates of grid block centers.
    std::vector<double> Ycenter;

    // surface area j+.
    std::vector<double> omega_jPlus;

    // surface area j-.
    std::vector<double> omega_jMin;

    // surface area i+.
    std::vector<double> omega_iPlus;

    // surface area i-.
    std::vector<double> omega_iMin;

    // grid volumes.
    std::vector<double> gridVolume;

    // x center of i+ surface.
    std::vector<double> omega_iPlus_Xcent;

    // y center of i+ surface.
    std::vector<double> omega_iPlus_Ycent;

    // x center of i- surface.
    std::vector<double> omega_iMinus_Xcent;

    // y center of i- surface.
    std::vector<double> omega_iMinus_Ycent;

    // x center of j+ surface.
    std::vector<double> omega_jPlus_Xcent;

    // y center of j+ surface.
    std::vector<double> omegaTop_Ycent;

    // x center of j- surface.
    std::vector<double> omega_jMinus_Xcent;

    // y center of j- surface.
    std::vector<double> omegaBot_Ycent ;

    // distance between grid i and i - 1.
    std::vector<double> getLeft_dL;

    // distance between grid i and i + 1.
    std::vector<double> getRight_dL;

    // distance between grid j and j + 1.
    std::vector<double> getTop_dL;

    // distance between grid j and j - 1.
    std::vector<double> getBot_dL;
};


#endif
