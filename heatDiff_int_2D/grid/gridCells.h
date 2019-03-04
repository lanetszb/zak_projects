#ifndef GRIDCELLS_H
#define GRIDCELLS_H

#include <grid/grid.h>

/**
Processes all grid cells' parameters
@param[in] grid - executes all the functions related to cells processing
*/
void processCells(Grid &grid);

/**
Computes X coordinate of grid blocks centers
@param[in, out] grid - takes total number of nodes in X and Y directions, and
computes the X coordinates of grid block centers
*/

void processCellsX(Grid &grid);

/**
Computes Y coordinate of grid blocks centers
@param[in, out] grid - takes total number of nodes in X and Y directions, and
computes the Y coordinates of grid block centers
*/
void processCellsY(Grid &grid);

/**
Computes Volume of grid blocks
@param[in, out] grid - takes total number of grid cells and size of
grid surfaces, and computes grid Volumes
*/

void processCellsVolume(Grid &grid);

/**
Computes Length between current and Left cells
@param[in, out] grid - takes total number of nodes in X and Y directions,
and X coordinates of block centers, and computes the distance between
the center of current grid block and the one to its Left
*/

void processLLeft(Grid &grid);

/**
Computes Length between current and Right cells
@param[in, out] grid - takes total number of nodes in X and Y directions,
and X coordinates of block centers, and computes the distance between
the center of current grid block and the one to its Right
*/
void processLRight(Grid &grid);

/**
Computes Length between current and Top cells
@param[in, out] grid - takes total number of nodes in X and Y directions,
and X coordinates of block centers, and computes the distance between
the center of current grid block and the one to its Top
*/
void processLTop(Grid &grid);

/**
Computes Length between current and Bottom cells
@param[in, out] grid - takes total number of nodes in X and Y directions,
and X coordinates of block centers, and computes the distance between
the center of current grid block and the to its Bottom
*/

void processLBottom(Grid &grid);

#endif
