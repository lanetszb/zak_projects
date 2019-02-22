#ifndef GRIDSURFACE_H
#define GRIDSURFACE_H

#include <grid/grid.h>


void processSurface(Grid &grid);


void processSurfaceLeft(Grid &grid);
void processSurfaceRight(Grid &grid);
void processSurfaceTop(Grid &grid);
void processSurfaceBottom(Grid &grid);

void processSurfaceRightX(Grid &grid);
void processSurfaceRightY(Grid &grid);

void processSurfaceLeftX(Grid &grid);
void processSurfaceLeftY(Grid &grid);

void processSurfaceTopX(Grid &grid);
void processSurfaceTopY(Grid &grid);

void processSurfaceBottomX(Grid &grid);
void processSurfaceBottomY(Grid &grid);

#endif
