#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>
#include <grid.h>

// Grid Data calculation

Grid func_gridCalculation(const std::string &gridFileName,
                          const std::string &nodesFileName) {

    Grid grd;

    GetFromFile gridD(gridFileName);
    grd.X_coord = gridD.getVector<double>("Node_X");
    grd.Y_coord = gridD.getVector<double>("Node_Y");

    GetFromFile nodesD(nodesFileName);
    grd.Nx = nodesD.getWord<int>("NODES_NUM_X");
    grd.Ny = nodesD.getWord<int>("NODES_NUM_Y");

    // ***Numerical solution for heat diffusion begins here***

    grd.gridN = (grd.Nx - 1) * (grd.Ny - 1);

    // Centre of blocks in X and Y directions.
    grd.Xcenter = func_Xcenter(grd.X_coord, grd.Nx);
    grd.Ycenter = func_Ycenter(grd.Y_coord, grd.Nx);

    // ***Surface area and volume determination***

    // Omega j Plus and Minus.
    grd.omega_jPlus = func_omega_jPlus(grd.X_coord, grd.Nx);
    grd.omega_jMin = func_omega_jMin(grd.X_coord, grd.Nx);

    // Omega i Plus and Minus.
    grd.omega_iPlus = func_omega_iPlus(grd.Y_coord, grd.Nx);
    grd.omega_iMin = func_omega_iMin(grd.Y_coord, grd.Nx);

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

    // Getting left and right dL
    grd.getLeft_dL = func_getLeft_dL(grd.Xcenter, grd.Nx);
    grd.getRight_dL = func_getRight_dL(grd.Xcenter, grd.Nx);

    // Getting Top and Bot dL
    grd.getTop_dL = func_getTop_dL(grd.Ycenter, grd.Nx);
    grd.getBot_dL = func_getBot_dL(grd.Ycenter, grd.Nx);

    return grd;
}

std::vector<double> func_Xcenter(std::vector<double> &X_coord, const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> gridXcent(gridN, 0);

    for (int j = 0, i = 0; i < gridXcent.size(); i++) {
        gridXcent[i] = abs(X_coord[i + 1 + j] + X_coord[i + j] +
                           X_coord[i + 1 + j + Nx] + X_coord[i + j + Nx]) / 4;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        gridXcent[i] = abs(X_coord[i + 1 + j] + X_coord[i + 2 + j] +
                           X_coord[i + 1 + j + Nx] + X_coord[i + 2 + j + Nx]) /
                       4;

    std::cout << std::endl;

    return gridXcent;


}

std::vector<double> func_Ycenter(std::vector<double> &Y_coord, const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> gridYcent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        gridYcent[i] = (Y_coord[i + Nx + 1 + j] + Y_coord[i + 1 + j] +
                        Y_coord[i + Nx + j] + Y_coord[i + j]) / 4;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        gridYcent[i] = (Y_coord[i + 1 + j + Nx] + Y_coord[i + 1 + j] +
                        Y_coord[i + 2 + j + Nx] + Y_coord[i + 2 + j]) / 4;


    return gridYcent;
}

std::vector<double> func_omega_jPlus(std::vector<double> &X_coord,
                                     const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_jPlus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_jPlus[i] = X_coord[i + 1 + j + Nx] - X_coord[i + j + Nx];
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_jPlus[i] = X_coord[i + 2 + j] - X_coord[i + 1 + j];

    return omega_jPlus;
}

std::vector<double> func_omega_jMin(std::vector<double> &X_coord,
                                    const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_jMin(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_jMin[i] = X_coord[i + 1 + j] - X_coord[i + j];
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_jMin[i] = X_coord[i + 2 + j] - X_coord[i + 1 + j];

    return omega_jMin;
}

std::vector<double> func_omega_iPlus(std::vector<double> &Y_coord,
                                     const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iPlus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus[i] = (Y_coord[i + Nx + 1 + j] - Y_coord[i + 1 + j]);
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iPlus;
}

std::vector<double> func_omega_iMin(std::vector<double> &Y_coord,
                                    const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iMin(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMin[i] = (Y_coord[i + Nx + j] - Y_coord[i + j]);
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iMin;
}

std::vector<double> func_gridVolume(std::vector<double> omega_iPlus,
                                    std::vector<double> omega_iMin,
                                    std::vector<double> omega_jPlus,
                                    std::vector<double> omega_jMin,
                                    const int gridN) {

    std::vector<double> semiPerimeter(gridN, 0);

    for (int i = 0; i < semiPerimeter.size(); i++)
        semiPerimeter[i] = (omega_iPlus[i] + omega_iMin[i] + omega_jPlus[i] +
                            omega_jMin[i]) / 2;

    std::vector<double> gridArea(gridN, 0);
    for (int i = 0; i < gridArea.size(); i++)
        gridArea[i] = sqrt((semiPerimeter[i] - omega_iPlus[i]) *
                           (semiPerimeter[i] - omega_iMin[i]) *
                           (semiPerimeter[i] - omega_jPlus[i]) *
                           (semiPerimeter[i] - omega_jMin[i]));

    // Grid volume

    std::vector<double> gridZheight(gridN, 1);
    std::vector<double> gridVolume(gridN, 0);

    for (int i = 0; i < gridArea.size(); i++)
        gridVolume[i] = gridArea[i] * gridZheight[i];

    return gridVolume;
}

std::vector<double> func_omega_iPlus_Xcent(std::vector<double> &X_coord,
                                           const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_iPlus_Xcent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus_Xcent[i] =
                (X_coord[i + 1 + j + Nx] + X_coord[i + j + 1]) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iPlus_Xcent[i] =
                (X_coord[i + 2 + j + Nx] + X_coord[i + 2 + j]) / 2;

    return omega_iPlus_Xcent;
}

std::vector<double> func_omega_iPlus_Ycent(std::vector<double> &Y_coord,
                                           const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iPlus_Ycent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus_Ycent[i] =
                ((Y_coord[i + Nx + 1 + j] + Y_coord[i + 1 + j])) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iPlus_Ycent;
}

std::vector<double> func_omega_iMinus_Xcent(std::vector<double> &X_coord,
                                            const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_iMinus_Xcent(gridN, 0);
    int width = 7;

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMinus_Xcent[i] = (X_coord[i + j + Nx] + X_coord[i + j]) / 2;

        std::cout << X_coord[i + j + Nx] << "  ";
        std::cout << X_coord[i + j] << "  ";
        std::cout << j << " ";

        if (i % (Nx - 1) == 0 && i != 0)
            j++;


        std::cout << " vector: " << std::setw(width) << omega_iMinus_Xcent[i];
        std::cout << " formula: " << std::setw(width)
                  << (X_coord[i + j + Nx] + X_coord[i + j]) / 2;

        std::cout << " " << j;
        std::cout << std::endl;
    }


    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iMinus_Xcent[i] =
                (X_coord[i + 1 + j + Nx] + X_coord[i + 1 + j]) / 2;

    std::cout << std::endl;


    return omega_iMinus_Xcent;
}

std::vector<double> func_omega_iMinus_Ycent(const std::vector<double> &Y_coord,
                                            const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_iMinus_Ycent(gridN, 0);

    for (int j = 0, i = 0; i < omega_iMinus_Ycent.size(); i++) {
        omega_iMinus_Ycent[i] = (Y_coord[i + Nx + j] + Y_coord[i + j]) / 2;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iMinus_Ycent[i] =
                (Y_coord[i + 1 + j + Nx] + Y_coord[i + 1 + j]) / 2;

    return omega_iMinus_Ycent;
}

std::vector<double> func_omega_jPlus_Xcent(const std::vector<double> &X_coord,
                                           const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_jPlus_Xcent(gridN, 0);

    for (int j = 0, i = 0; i < omega_jPlus_Xcent.size(); i++) {
        omega_jPlus_Xcent[i] = (X_coord[i + 1 + j] + X_coord[i + j]) / 2;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0;
         i < omega_jPlus_Xcent.size(); i += (Nx - 1), j++)
        omega_jPlus_Xcent[i] =
                (X_coord[i + 1 + j] + X_coord[i + 2 + j]) / 2;

    return omega_jPlus_Xcent;

}

std::vector<double> func_omega_jPlus_Ycent(const std::vector<double> &Y_coord,
                                           const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_jPlus_Ycent(gridN, 0);

    for (int j = 0, i = 0; i < Y_coord.size(); i++) {
        omega_jPlus_Ycent[i] =
                ((Y_coord[i + Nx + 1 + j] + Y_coord[i + Nx + j])) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0;
         i < omega_jPlus_Ycent.size(); i += (Nx - 1), j++)
        omega_jPlus_Ycent[i] =
                (Y_coord[i + 2 + j + Nx] + Y_coord[i + 1 + j + Nx]) / 2;

    return omega_jPlus_Ycent;
}


std::vector<double> func_getLeft_dL(const std::vector<double> &gridXcent,
                                    const int &Nx) {

    std::vector<double> getLeft_dL(gridXcent.size(), 0);

    for (int i = 0; i < getLeft_dL.size(); i++) {
        getLeft_dL[i] = gridXcent[i] - gridXcent[i - 1];
    }

    for (int i = 0; i < getLeft_dL.size(); i += Nx - 1)
        getLeft_dL[i] = 0;

    return getLeft_dL;
}

std::vector<double> func_getRight_dL(const std::vector<double> &gridXcent,
                                     const int &Nx) {

    std::vector<double> getRight_dL(gridXcent.size(), 0);

    for (int i = 0; i < getRight_dL.size(); i++) {
        getRight_dL[i] = gridXcent[i + 1] - gridXcent[i];
    }

    for (int i = Nx - 2; i < getRight_dL.size(); i += Nx - 1)
        getRight_dL[i] = 0;

    return getRight_dL;
}

std::vector<double> func_getTop_dL(const std::vector<double> &gridYcent,
                                   const int &Nx) {

    std::vector<double> getTop_dL(gridYcent.size(), 0);

    for (int i = 0; i < getTop_dL.size(); i++)
        getTop_dL[i] = gridYcent[i + (Nx - 1)] - gridYcent[i];

    for (int i = getTop_dL.size() - (Nx - 1); i < getTop_dL.size(); i++)
        getTop_dL[i] = 0;

    return getTop_dL;

}

std::vector<double> func_getBot_dL(const std::vector<double> &gridYcent,
                                   const int &Nx) {

    std::vector<double> getBot_dL(gridYcent.size(), 0);

    for (int i = 0; i < getBot_dL.size(); i++)
        getBot_dL[i] = gridYcent[i] - gridYcent[i - (Nx - 1)];

    for (int i = 0; i < Nx - 1; i++)
        getBot_dL[i] = 0;

    return getBot_dL;
}