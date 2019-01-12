
#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <vector>

#include <grid/grid_struct.h>
#include <GetFromFile.h>
#include <grid/grid_cell.h>
#include <grid/grid_surf.h>

void func_gridCalculation(Grid &grd, const std::string &gridFileName,
                          const std::string &nodesFileName);

#endif
