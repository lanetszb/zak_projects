#include <grid/gridCell.h>


std::vector<double> Xcenter_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {

            indCur = i * grd.Nx + j;
            value = fabs(grd.X_coord[indCur] + grd.X_coord[indCur + 1] +
                         grd.X_coord[indCur + grd.Nx] +
                         grd.X_coord[indCur + 1 + grd.Nx]) / 4;

            grd.Xcenter.push_back(value);
        }

    return grd.Xcenter;
}

std::vector<double> Ycenter_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {

            indCur = i * grd.Nx + j;
            value = fabs(grd.Y_coord[indCur] + grd.Y_coord[indCur + 1] +
                         grd.Y_coord[indCur + grd.Nx] +
                         grd.Y_coord[indCur + 1 + grd.Nx]) / 4;

            grd.Ycenter.push_back(value);
        }

    return grd.Ycenter;

}

std::vector<double> gridVolume_calc(Grid &grd) {

    std::vector<double> semiPerimeter(grd.gridN, 0);

    double value = 0;

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

    for (int i = 0; i < gridArea.size(); i++) {
        value = gridArea[i] * gridZheight[i];
        grd.gridVolume.push_back(value);
    }

    return grd.gridVolume;
}

std::vector<double> Left_dL_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 1; j < grd.Nx - 1; j++) {

            indCur = i * (grd.Nx - 1) + j;
            value = fabs(
                    grd.Xcenter[indCur] - grd.Xcenter[indCur - 1]);

            grd.getLeft_dL.push_back(value);
        }

    return grd.getLeft_dL;
}

std::vector<double> Right_dL_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 2; j++) {

            indCur = i * (grd.Nx - 1) + j;
            value = fabs(
                    grd.Xcenter[indCur] - grd.Xcenter[indCur + 1]);

            grd.getRight_dL.push_back(value);
        }

    return grd.getRight_dL;
}

std::vector<double> Top_dL_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 2; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {

            indCur = i * (grd.Nx - 1) + j;
            value = fabs(
                    grd.Ycenter[indCur] - grd.Ycenter[indCur + (grd.Nx - 1)]);

            grd.getTop_dL.push_back(value);
        }

    return grd.getTop_dL;

}

std::vector<double> Bot_dL_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {

            indCur = i * (grd.Nx - 1) + j;
            value = fabs(
                    grd.Ycenter[indCur] - grd.Ycenter[indCur - (grd.Nx - 1)]);

            grd.getBot_dL.push_back(value);
        }

    return grd.getBot_dL;
}