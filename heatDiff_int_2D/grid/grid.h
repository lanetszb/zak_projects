
#ifndef GRID_H
#define GRID_H

#include <vector>

#include <grid_struct.h>
#include <GetFromFile.h>
#include <grid_cell.h>
#include <grid_surf.h>

void func_gridCalculation(Grid &grd, const std::string &gridFileName,
                          const std::string &nodesFileName);

#endif
