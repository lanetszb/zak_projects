#ifndef GRIDSTRUCT_H
#define GRIDSTRUCT_H

#include <vector>

// Structure containing all grid attributes.
struct Grid {
    // Nodes quantity in x direction.
    int nX;

    // Nodes quantity in y direction.
    int nY;

    // total number of grid blocks.
    int gridN;

    // dX
    double dX;

    // dY
    double dY;

    // x coordinates of grid blocks.
    std::vector<double> nodesX;

    // y coordinates of grid blocks.
    std::vector<double> nodesY;

    // x coordinates of grid block centers.
    std::vector<double> Xcenter;

    // y coordinates of grid block centers.
    std::vector<double> Ycenter;

    // surface area j+.
    std::vector<double> omegaTop;

    // surface area j-.
    std::vector<double> omegaBot;

    // surface area i+.
    std::vector<double> omegaRight;

    // surface area i-.
    std::vector<double> omegaLeft;

    // grid volumes.
    std::vector<double> gridVolume;

    // x center of i+ surface.
    std::vector<double> omegaRight_Xcent;

    // y center of i+ surface.
    std::vector<double> omegaRight_Ycent;

    // x center of i- surface.
    std::vector<double> omegaLeft_Xcent;

    // y center of i- surface.
    std::vector<double> omegaLeft_Ycent;

    // x center of j+ surface.
    std::vector<double> omegaTop_Xcent;

    // y center of j+ surface.
    std::vector<double> omegaTop_Ycent;

    // x center of j- surface.
    std::vector<double> omegaBot_Xcent;

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
