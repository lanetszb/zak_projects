#ifndef GRIDCELLS_H
#define GRIDCELLS_H

#include <grid/grid.h>


void processCells(Grid &grid);

void processCellsX(Grid &grid);
void processCellsY(Grid &grid);

void processCellsVolume(Grid &grid);

void processLLeft(Grid &grid);
void processLRight(Grid &grid);
void processLTop(Grid &grid);
void processLBottom(Grid &grid);

#endif
