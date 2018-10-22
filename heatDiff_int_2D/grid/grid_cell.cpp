#include <grid_cell.h>
#include <cmath>


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

std::vector<double> func_getBot_dL(const Grid &grd) {

    std::vector<double> getBot_dL(grd.Ycenter.size(), 0);

    for (int i = 0; i < getBot_dL.size(); i++)
        getBot_dL[i] = grd.Ycenter[i] - grd.Ycenter[i - (grd.Nx - 1)];

    for (int i = 0; i < grd.Nx - 1; i++)
        getBot_dL[i] = 0;

    return getBot_dL;

}