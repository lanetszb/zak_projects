#include <grid/gridSurf.h>

std::vector<double> omegaTop_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grd.Ny; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = fabs(grd.X_coord[indCur] - grd.X_coord[indCur + 1]);
            grd.omegaTop.push_back(value);
        }

    return grd.omegaTop;
}

std::vector<double> omegaBot_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = fabs(grd.X_coord[indCur] - grd.X_coord[indCur + 1]);
            grd.omegaBot.push_back(value);

        }

    return grd.omegaBot;
}

std::vector<double> omegaRight_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 1; j < grd.Nx; j++) {
            indCur = i * grd.Nx + j;
            value = fabs(grd.Y_coord[indCur] - grd.Y_coord[indCur + grd.Nx]);
            grd.omegaRight.push_back(value);
        }

    return grd.omegaRight;
}

std::vector<double> omegaLeft_calc(Grid &grd) {


    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = fabs(grd.Y_coord[indCur] - grd.Y_coord[indCur + grd.Nx]);
            grd.omegaLeft.push_back(value);
        }

    return grd.omegaLeft;
}


std::vector<double> omegaRight_Xcent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 1; j < grd.Nx; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.X_coord[indCur] + grd.X_coord[indCur + grd.Nx]) / 2.;
            grd.omegaRight_Xcent.push_back(value);
        }

    return grd.omegaRight_Xcent;
}

std::vector<double> omegaRight_Ycent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 1; j < grd.Nx; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.Y_coord[indCur] + grd.Y_coord[indCur + grd.Nx]) / 2.;
            grd.omegaLeft_Ycent.push_back(value);
        }

    return grd.omegaLeft_Ycent;
}

std::vector<double> omegaLeft_Xcent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.X_coord[indCur] + grd.X_coord[indCur + grd.Nx]) / 2.;
            grd.omegaLeft_Xcent.push_back(value);
        }

    return grd.omegaLeft_Ycent;
}

std::vector<double> omegaLeft_Ycent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.Y_coord[indCur] + grd.Y_coord[indCur + grd.Nx]) / 2.;
            grd.omegaLeft_Ycent.push_back(value);
        }

    return grd.omegaLeft_Ycent;
}

std::vector<double> omegaTop_Xcent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grd.Ny; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.X_coord[indCur] + grd.X_coord[indCur + 1]) / 2.;
            grd.omegaTop_Xcent.push_back(value);
        }

    return grd.omegaTop_Xcent;

}


void omegaTop_Ycent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grd.Ny; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.Y_coord[indCur] + grd.Y_coord[indCur + 1]) / 2.;
            grd.omegaTop_Ycent.push_back(value);
        }

}

std::vector<double> omegaBot_Xcent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.X_coord[indCur] + grd.X_coord[indCur + 1]) / 2.;
            grd.omegaBot_Xcent.push_back(value);
        }

    return grd.omegaBot_Xcent;

}

void omegaBot_Ycent_calc(Grid &grd) {

    double value = 0;
    int indCur = 0;
    for (int i = 0; i < grd.Ny - 1; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.Y_coord[indCur] + grd.Y_coord[indCur + 1]) / 2.;
            grd.omegaBot_Ycent.push_back(value);
        }

}
