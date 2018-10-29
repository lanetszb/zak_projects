#include <grid_cell.h>


std::vector<double> func_Xcenter(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.X_coord.size() / grd.Nx - 1);
    std::vector<double> gridXcent(gridN, 0);

    for (int j = 0, i = 0; i < gridXcent.size(); i++) {
        gridXcent[i] = abs(grd.X_coord[i + 1 + j] + grd.X_coord[i + j] +
                           grd.X_coord[i + 1 + j + grd.Nx] +
                           grd.X_coord[i + j + grd.Nx]) / 4;

        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (grd.Nx - 1), j = 0; i < gridN; i += (grd.Nx - 1), j++)
        gridXcent[i] = abs(grd.X_coord[i + 1 + j] + grd.X_coord[i + 2 + j] +
                           grd.X_coord[i + 1 + j + grd.Nx] +
                           grd.X_coord[i + 2 + j + grd.Nx]) /
                       4;

    return gridXcent;


}

std::vector<double> func_Ycenter(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.Y_coord.size() / grd.Nx - 1);
    std::vector<double> gridYcent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        gridYcent[i] =
                (grd.Y_coord[i + grd.Nx + 1 + j] + grd.Y_coord[i + 1 + j] +
                 grd.Y_coord[i + grd.Nx + j] + grd.Y_coord[i + j]) / 4;

        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (grd.Nx - 1), j = 0; i < gridN; i += (grd.Nx - 1), j++)
        gridYcent[i] =
                (grd.Y_coord[i + 1 + j + grd.Nx] + grd.Y_coord[i + 1 + j] +
                 grd.Y_coord[i + 2 + j + grd.Nx] + grd.Y_coord[i + 2 + j]) / 4;


    return gridYcent;
}

std::vector<double> func_gridVolume(Grid &grd) {

    std::vector<double> semiPerimeter(grd.gridN, 0);

    for (int i = 0; i < semiPerimeter.size(); i++)
        semiPerimeter[i] =
                (grd.omegaRight[i] + grd.omegaLeft[i] + grd.omegaTop[i] +
                 grd.omegaBot[i]) / 2;

    std::vector<double> gridArea(grd.gridN, 0);
    for (int i = 0; i < gridArea.size(); i++)
        gridArea[i] = sqrt((semiPerimeter[i] - grd.omegaRight[i]) *
                           (semiPerimeter[i] - grd.omegaLeft[i]) *
                           (semiPerimeter[i] - grd.omegaTop[i]) *
                           (semiPerimeter[i] - grd.omegaBot[i]));

    // Grid volume

    std::vector<double> gridZheight(grd.gridN, 1);
    std::vector<double> gridVolume(grd.gridN, 0);

    for (int i = 0; i < gridArea.size(); i++)
        gridVolume[i] = gridArea[i] * gridZheight[i];

    return gridVolume;
}

std::vector<double> func_getLeft_dL(Grid &grd) {

    std::vector<double> getLeft_dL(grd.Xcenter.size(), 0);

    for (int i = 0; i < getLeft_dL.size(); i++) {
        getLeft_dL[i] = grd.Xcenter[i] - grd.Xcenter[i - 1];
    }

    for (int i = 0; i < getLeft_dL.size(); i += grd.Nx - 1)
        getLeft_dL[i] = 0;

    return getLeft_dL;
}

std::vector<double> func_getRight_dL(Grid &grd) {

    std::vector<double> getRight_dL(grd.Xcenter.size(), 0);

    for (int i = 0; i < getRight_dL.size(); i++) {
        getRight_dL[i] = grd.Xcenter[i + 1] - grd.Xcenter[i];
    }

    for (int i = grd.Nx - 2; i < getRight_dL.size(); i += grd.Nx - 1)
        getRight_dL[i] = 0;

    return getRight_dL;
}

std::vector<double> func_getTop_dL(Grid &grd) {

    std::vector<double> getTop_dL(grd.Ycenter.size(), 0);

    for (int i = 0; i < getTop_dL.size(); i++)
        getTop_dL[i] = grd.Ycenter[i + (grd.Nx - 1)] - grd.Ycenter[i];

    for (int i = getTop_dL.size() - (grd.Nx - 1); i < getTop_dL.size(); i++)
        getTop_dL[i] = 0;

    return getTop_dL;

}

std::vector<double> func_getBot_dL(Grid &grd) {

    std::vector<double> getBot_dL(grd.Ycenter.size(), 0);

    for (int i = 0; i < getBot_dL.size(); i++)
        getBot_dL[i] = grd.Ycenter[i] - grd.Ycenter[i - (grd.Nx - 1)];

    for (int i = 0; i < grd.Nx - 1; i++)
        getBot_dL[i] = 0;

    return getBot_dL;

}