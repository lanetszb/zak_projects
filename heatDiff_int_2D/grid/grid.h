#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

/*!
\file
\brief This structure consists of all the parameters correspondent to grid
blocks
*/

struct Grid {

    int nX;
    int nY;
    int nCells;


    std::vector<double> nodesX;
    std::vector<double> nodesY;

    std::vector<double> cellsX;
    std::vector<double> cellsY;


    std::vector<double> surfaceLeft;
    std::vector<double> surfaceRight;
    std::vector<double> surfaceTop;
    std::vector<double> surfaceBottom;

    std::vector<double> cellsVolume;


    std::vector<double> surfaceLeftX;
    std::vector<double> surfaceLeftY;

    std::vector<double> surfaceRightX;
    std::vector<double> surfaceRightY;

    std::vector<double> surfaceTopX;
    std::vector<double> surfaceTopY;

    std::vector<double> surfaceBottomX;
    std::vector<double> surfaceBottomY ;


    std::vector<double> LLeft;
    std::vector<double> LRight;
    std::vector<double> LTop;
    std::vector<double> LBottom;

};

/**
Processes all grid properties
@param[in] fileName - includes the data files with nodes X and Y corrdinates,
and grid data
@return processed grid parameters
*/

Grid processGrid(const std::string &fileName);

#endif
