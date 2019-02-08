
#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <vector>

#include <grid/gridStruct.h>
#include <GetFromFile.h>
#include <grid/gridCell.h>
#include <grid/gridSurf.h>

void func_gridCalculation(Grid &grd, const std::string &gridFileName,
                          const std::string &nodesFileName);

#endif
