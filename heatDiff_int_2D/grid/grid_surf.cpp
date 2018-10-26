#include <grid_surf.h>

std::vector<double> func_omega_jPlus(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.X_coord.size() / grd.Nx - 1);
    std::vector<double> omega_jPlus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_jPlus[i] =
                grd.X_coord[i + 1 + j + grd.Nx] - grd.X_coord[i + j + grd.Nx];
        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (grd.Nx - 1), j = 0; i < gridN; i += (grd.Nx - 1), j++)
        omega_jPlus[i] = grd.X_coord[i + 2 + j] - grd.X_coord[i + 1 + j];

    return omega_jPlus;
}

std::vector<double> func_omega_jMin(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.X_coord.size() / grd.Nx - 1);
    std::vector<double> omega_jMin(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_jMin[i] = grd.X_coord[i + 1 + j] - grd.X_coord[i + j];
        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (grd.Nx - 1), j = 0; i < gridN; i += (grd.Nx - 1), j++)
        omega_jMin[i] = grd.X_coord[i + 2 + j] - grd.X_coord[i + 1 + j];

    return omega_jMin;
}

std::vector<double> func_omega_iPlus(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.Y_coord.size() / grd.Nx - 1);
    std::vector<double> omega_iPlus(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus[i] = (grd.Y_coord[i + grd.Nx + 1 + j] -
                          grd.Y_coord[i + 1 + j]);
        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iPlus;
}

std::vector<double> func_omega_iMin(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.Y_coord.size() / grd.Nx - 1);
    std::vector<double> omega_iMin(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMin[i] = (grd.Y_coord[i + grd.Nx + j] - grd.Y_coord[i + j]);
        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iMin;
}


std::vector<double> func_omega_iPlus_Xcent(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.X_coord.size() / grd.Nx - 1);
    std::vector<double> omega_iPlus_Xcent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus_Xcent[i] =
                (grd.X_coord[i + 1 + j + grd.Nx] + grd.X_coord[i + j + 1]) / 2;
        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }
    for (int i = (grd.Nx - 1), j = 0; i < gridN; i += (grd.Nx - 1), j++)
        omega_iPlus_Xcent[i] =
                (grd.X_coord[i + 2 + j + grd.Nx] + grd.X_coord[i + 2 + j]) / 2;

    return omega_iPlus_Xcent;
}

std::vector<double> func_omega_iPlus_Ycent(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.Y_coord.size() / grd.Nx - 1);
    std::vector<double> omega_iPlus_Ycent(gridN, 0);

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iPlus_Ycent[i] =
                ((grd.Y_coord[i + grd.Nx + 1 + j] + grd.Y_coord[i + 1 + j])) /
                2;
        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }
    return omega_iPlus_Ycent;
}

std::vector<double> func_omega_iMinus_Xcent(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.X_coord.size() / grd.Nx - 1);
    std::vector<double> omega_iMinus_Xcent(gridN, 0);
    int width = 7;

    for (int j = 0, i = 0; i < gridN; i++) {
        omega_iMinus_Xcent[i] =
                (grd.X_coord[i + j + grd.Nx] + grd.X_coord[i + j]) / 2;

        /*
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
               */
    }

    for (int i = (grd.Nx - 1), j = 0; i < gridN; i += (grd.Nx - 1), j++)
        omega_iMinus_Xcent[i] =
                (grd.X_coord[i + 1 + j + grd.Nx] + grd.X_coord[i + 1 + j]) / 2;


    return omega_iMinus_Xcent;
}

std::vector<double> func_omega_iMinus_Ycent(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.Y_coord.size() / grd.Nx - 1);
    std::vector<double> omega_iMinus_Ycent(gridN, 0);

    for (int j = 0, i = 0; i < omega_iMinus_Ycent.size(); i++) {
        omega_iMinus_Ycent[i] =
                (grd.Y_coord[i + grd.Nx + j] + grd.Y_coord[i + j]) / 2;

        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (grd.Nx - 1), j = 0; i < gridN; i += (grd.Nx - 1), j++)
        omega_iMinus_Ycent[i] =
                (grd.Y_coord[i + 1 + j + grd.Nx] + grd.Y_coord[i + 1 + j]) / 2;

    return omega_iMinus_Ycent;
}

std::vector<double> func_omega_jPlus_Xcent(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.X_coord.size() / grd.Nx - 1);
    std::vector<double> omega_jPlus_Xcent(gridN, 0);

    for (int j = 0, i = 0; i < omega_jPlus_Xcent.size(); i++) {
        omega_jPlus_Xcent[i] =
                (grd.X_coord[i + 1 + j + grd.Nx] +
                 grd.X_coord[i + j + grd.Nx]) / 2;

        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (grd.Nx - 1), j = 0;
         i < omega_jPlus_Xcent.size(); i += (grd.Nx - 1), j++)
        omega_jPlus_Xcent[i] =
                (grd.X_coord[i + 1 + j + grd.Nx] +
                 grd.X_coord[i + 2 + j + grd.Nx]) / 2;


    return omega_jPlus_Xcent;

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

    for (int i = 0; i < grd.omegaTop_Ycent.size(); i++)
        std::cout << grd.omegaTop_Ycent[i] << std::endl;
    std::cout << std::endl;

    std::cout << "test" << std::endl;

}

std::vector<double> func_omega_jMinus_Xcent(Grid &grd) {

    int gridN = (grd.Nx - 1) * (grd.X_coord.size() / grd.Nx - 1);
    std::vector<double> omega_jMinus_Xcent(gridN, 0);

    for (int j = 0, i = 0; i < omega_jMinus_Xcent.size(); i++) {
        omega_jMinus_Xcent[i] =
                (grd.X_coord[i + 1 + j] + grd.X_coord[i + j]) / 2;

        if (i % (grd.Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (grd.Nx - 1), j = 0;
         i < omega_jMinus_Xcent.size(); i += (grd.Nx - 1), j++)
        omega_jMinus_Xcent[i] =
                (grd.X_coord[i + 1 + j] + grd.X_coord[i + 2 + j]) / 2;

    std::cout << "test" << std::endl;

    for (int i = 0; i < grd.omega_jMinus_Xcent.size(); i++)
        std::cout << grd.omega_jMinus_Xcent[i] << std::endl;
    std::cout << std::endl;

    std::cout << "test" << std::endl;

    return omega_jMinus_Xcent;
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

    for (int i = 0; i < grd.omegaBot_Ycent.size(); i++)
        std::cout << grd.omegaBot_Ycent[i] << std::endl;
    std::cout << std::endl;

}
