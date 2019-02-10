#include <grid/grid.h>

// Grid Data calculation

void func_gridCalculation(Grid &grd, const std::string &gridFileName,
                          const std::string &nodesFileName) {


    GetFromFile gridD(gridFileName);
    grd.X_coord = gridD.getVector<double>("Node_X");
    grd.Y_coord = gridD.getVector<double>("Node_Y");


    GetFromFile nodesD(nodesFileName);
    grd.nX = nodesD.getWord<int>("NODES_NUM_X");
    grd.nY = nodesD.getWord<int>("NODES_NUM_Y");

    // ***Numerical solution for heat diffusion begins here***

    grd.gridN = (grd.nX - 1) * (grd.nY - 1);

    grd.dx = (grd.X_coord[grd.nX - 1] - grd.X_coord[0]) / (grd.nX - 1);

    grd.dy = (grd.Y_coord[grd.Y_coord.size() - 1] - grd.Y_coord[0]) /
             (grd.nY - 1);

    // ***Surface area and volume determination***

    // Omega j Plus and Minus.
    grd.omegaTop = omegaTop_calc(grd);
    grd.omegaBot = omegaBot_calc(grd);

    // Omega i Plus and Minus.
    grd.omegaRight = omegaRight_calc(grd);
    grd.omegaLeft = omegaLeft_calc(grd);

    // Centre of blocks in X and Y directions.
    grd.Xcenter = Xcenter_calc(grd);
    grd.Ycenter = Ycenter_calc(grd);

    // Grid volume

    grd.gridVolume = gridVolume_calc(grd);

    // ***Grid surface centres***

    // Omega i Plus center, X and Y coordinates.
    grd.omegaRight_Xcent = omegaRight_Xcent_calc(grd);
    grd.omegaRight_Ycent = omegaRight_Ycent_calc(grd);
    // Omega i Minus center, X and Y coordinates.
    grd.omegaLeft_Xcent = omegaLeft_Xcent_calc(grd);
    grd.omegaLeft_Ycent = omegaLeft_Ycent_calc(grd);

    // Omega j Plus center, X and Y coordinates.
    grd.omegaTop_Xcent = omegaTop_Xcent_calc(grd);
    omegaTop_Ycent_calc(grd);

    // Omega j Minus center, X and Y coordinates.
    grd.omegaBot_Xcent = omegaBot_Xcent_calc(grd);
    omegaBot_Ycent_calc(grd);

    // Getting left and right dL

    grd.getLeft_dL = Left_dL_calc(grd);
    grd.getRight_dL = Right_dL_calc(grd);

    // Getting Top and Bot dL
    grd.getTop_dL = Top_dL_calc(grd);
    grd.getBot_dL = Bot_dL_calc(grd);

}



