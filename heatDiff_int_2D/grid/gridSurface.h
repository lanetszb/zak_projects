#ifndef GRIDSURFACE_H
#define GRIDSURFACE_H

#include <grid/grid.h>

/*!
\file
\brief This file allows to process grid surface' parameters, such as surface
 area and faces X and Y coordinates
*/

/**
Processes all grid surface' parameters
@param[in] grid - executes all the functions related to grid surfaces processing
*/
void processSurface(Grid &grid);

/**
Computes area of grid cell's Left surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceLeft(Grid &grid);

/**
Computes area of grid cell's Right surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceRight(Grid &grid);

/**
Computes area of grid cell's Top surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceTop(Grid &grid);

/**
Computes area of grid cell's Bottom surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceBottom(Grid &grid);

/**
Computes the X coordinate of grid cell's Right surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceRightX(Grid &grid);

/**
Computes the Y coordinate of grid cell's Right surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceRightY(Grid &grid);

/**
Computes the X coordinate of grid cell's Left surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceLeftX(Grid &grid);

/**
Computes the Y coordinate of grid cell's Left surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceLeftY(Grid &grid);

/**
Computes the X coordinate of grid cell's Top surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceTopX(Grid &grid);

/**
Computes the Y coordinate of grid cell's Top surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceTopY(Grid &grid);

/**
Computes the X coordinate of grid cell's Bottom surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceBottomX(Grid &grid);

/**
Computes the Y coordinate of grid cell's Bottom surface
@param[in, out] grid - takes total number of nodes in X and Y directions,
and their coordinates
*/

void processSurfaceBottomY(Grid &grid);

#endif
