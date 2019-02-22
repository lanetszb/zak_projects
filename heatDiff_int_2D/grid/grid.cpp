#include <vector>
#include <string>

#include <GetFromFile.h>

#include <grid/grid.h>
#include <grid/gridCells.h>
#include <grid/gridSurface.h>

Grid processGrid(const std::string &fileName) {

    Grid grid;

    GetFromFile dataFile(fileName);

    auto nodesFileName = dataFile.getWord<std::string>("N_NODES_FILE");
    auto gridFileName = dataFile.getWord<std::string>("GRID_FILE");
    GetFromFile nodesFile(nodesFileName);
    GetFromFile gridFile(gridFileName);

    grid.nX = nodesFile.getWord<int>("N_NODES_X");
    grid.nY = nodesFile.getWord<int>("N_NODES_Y");
    grid.nCells = (grid.nX - 1) * (grid.nY - 1);

    grid.nodesX = gridFile.getVector<double>("NODES_X");
    grid.nodesY = gridFile.getVector<double>("NODES_Y");    

    processSurface(grid);    
    processCells(grid);

    return grid;

}



