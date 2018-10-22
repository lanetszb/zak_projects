#include <vector>
#include <GetFromFile.h>
#include <grid.h>
#include <grid_cell.h>
#include <grid_surf.h>


// Grid Data calculation

void func_gridCalculation(Grid &grd, const std::string &gridFileName,
                          const std::string &nodesFileName) {


    GetFromFile gridD(gridFileName);
    grd.X_coord = gridD.getVector<double>("Node_X");
    grd.Y_coord = gridD.getVector<double>("Node_Y");


    GetFromFile nodesD(nodesFileName);
    grd.Nx = nodesD.getWord<int>("NODES_NUM_X");
    grd.Ny = nodesD.getWord<int>("NODES_NUM_Y");

    // ***Numerical solution for heat diffusion begins here***

    grd.gridN = (grd.Nx - 1) * (grd.Ny - 1);

    grd.dx = (grd.X_coord[grd.Nx - 1] - grd.X_coord[0]) / (grd.Nx - 1);

    grd.dy = (grd.Y_coord[grd.Y_coord.size() - 1] - grd.Y_coord[0]) /
             (grd.Ny - 1);

    // ***Surface area and volume determination***

    // Omega j Plus and Minus.
    grd.omega_jPlus = func_omega_jPlus(grd.X_coord, grd.Nx);
    grd.omega_jMin = func_omega_jMin(grd.X_coord, grd.Nx);

    // Omega i Plus and Minus.
    grd.omega_iPlus = func_omega_iPlus(grd.Y_coord, grd.Nx);
    grd.omega_iMin = func_omega_iMin(grd.Y_coord, grd.Nx);

    // Centre of blocks in X and Y directions.
    grd.Xcenter = func_Xcenter(grd.X_coord, grd.Nx);
    grd.Ycenter = func_Ycenter(grd.Y_coord, grd.Nx);

    // Grid volume

    grd.gridVolume = func_gridVolume(grd.omega_iPlus, grd.omega_iMin,
                                     grd.omega_jPlus,
                                     grd.omega_jMin, grd.gridN);

    // ***Grid surface centres***

    // Omega i Plus center, X and Y coordinates.
    grd.omega_iPlus_Xcent = func_omega_iPlus_Xcent(grd.X_coord, grd.Nx);
    grd.omega_iPlus_Ycent = func_omega_iPlus_Ycent(grd.Y_coord, grd.Nx);
    // Omega i Minus center, X and Y coordinates.
    grd.omega_iMinus_Xcent = func_omega_iMinus_Xcent(grd.X_coord, grd.Nx);
    grd.omega_iMinus_Ycent = func_omega_iMinus_Ycent(grd.Y_coord, grd.Nx);

    // Omega j Plus center, X and Y coordinates.
    grd.omega_jPlus_Xcent = func_omega_jPlus_Xcent(grd.X_coord, grd.Nx);
    grd.omega_jPlus_Ycent = func_omega_jPlus_Ycent(grd.Y_coord, grd.Nx);

    // Omega j Minus center, X and Y coordinates.
    grd.omega_jMinus_Xcent = func_omega_jMinus_Xcent(grd.X_coord, grd.Nx);
    grd.omega_jMinus_Ycent = func_omega_jMinus_Ycent(grd.Y_coord, grd.Nx);

    // Getting left and right dL

    grd.getLeft_dL = func_getLeft_dL(grd.Xcenter, grd.Nx);
    grd.getRight_dL = func_getRight_dL(grd.Xcenter, grd.Nx);

    // Getting Top and Bot dL
    grd.getTop_dL = func_getTop_dL(grd.Ycenter, grd.Nx);
    grd.getBot_dL = func_getBot_dL(grd);

}


