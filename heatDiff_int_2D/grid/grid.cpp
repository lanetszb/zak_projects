#include <GetFromFile.h>

#include <grid/grid.h>
#include <grid/gridCell.h>
#include <grid/gridSurf.h>

// Grid Data calculation

Grid getGrid(const std::string &fileName) {
    Grid grid;

    GetFromFile dataFile(fileName);

    auto gridFileName = dataFile.getWord<std::string>("GRID_DATA");
    auto nodesFileName = dataFile.getWord<std::string>("NODES_NUM");

    GetFromFile gridD(gridFileName);
    grid.X_coord = gridD.getVector<double>("Node_X");
    grid.Y_coord = gridD.getVector<double>("Node_Y");


    GetFromFile nodesD(nodesFileName);
    grid.nX = nodesD.getWord<int>("NODES_NUM_X");
    grid.nY = nodesD.getWord<int>("NODES_NUM_Y");

    // ***Numerical solution for heat diffusion begins here***

    grid.gridN = (grid.nX - 1) * (grid.nY - 1);

    grid.dx = (grid.X_coord[grid.nX - 1] - grid.X_coord[0]) / (grid.nX - 1);

    grid.dy = (grid.Y_coord[grid.Y_coord.size() - 1] - grid.Y_coord[0]) /
             (grid.nY - 1);

    // ***Surface area and volume determination***

    // Omega j Plus and Minus.
    grid.omegaTop = omegaTop_calc(grid);
    grid.omegaBot = omegaBot_calc(grid);

    // Omega i Plus and Minus.
    grid.omegaRight = omegaRight_calc(grid);
    grid.omegaLeft = omegaLeft_calc(grid);

    // Centre of blocks in X and Y directions.
    grid.Xcenter = Xcenter_calc(grid);
    grid.Ycenter = Ycenter_calc(grid);

    // Grid volume

    grid.gridVolume = gridVolume_calc(grid);

    // ***Grid surface centres***

    // Omega i Plus center, X and Y coordinates.
    grid.omegaRight_Xcent = omegaRight_Xcent_calc(grid);
    grid.omegaRight_Ycent = omegaRight_Ycent_calc(grid);
    // Omega i Minus center, X and Y coordinates.
    grid.omegaLeft_Xcent = omegaLeft_Xcent_calc(grid);
    grid.omegaLeft_Ycent = omegaLeft_Ycent_calc(grid);

    // Omega j Plus center, X and Y coordinates.
    grid.omegaTop_Xcent = omegaTop_Xcent_calc(grid);
    omegaTop_Ycent_calc(grid);

    // Omega j Minus center, X and Y coordinates.
    grid.omegaBot_Xcent = omegaBot_Xcent_calc(grid);
    omegaBot_Ycent_calc(grid);

    // Getting left and right dL

    grid.getLeft_dL = Left_dL_calc(grid);
    grid.getRight_dL = Right_dL_calc(grid);

    // Getting Top and Bot dL
    grid.getTop_dL = Top_dL_calc(grid);
    grid.getBot_dL = Bot_dL_calc(grid);

    return grid;

}



