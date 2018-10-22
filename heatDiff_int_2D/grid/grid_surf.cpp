#include <grid_surf.h>

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

    for (int i = (Nx - 1), j = 0; i < gridN; i += (Nx - 1), j++)
        omega_iMinus_Xcent[i] =
                (X_coord[i + 1 + j + Nx] + X_coord[i + 1 + j]) / 2;


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
        omega_jPlus_Xcent[i] =
                (X_coord[i + 1 + j + Nx] + X_coord[i + j + Nx]) / 2;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0;
         i < omega_jPlus_Xcent.size(); i += (Nx - 1), j++)
        omega_jPlus_Xcent[i] =
                (X_coord[i + 1 + j + Nx] + X_coord[i + 2 + j + Nx]) / 2;


    return omega_jPlus_Xcent;

}


void omega_jPlus_Ycent_calc(Grid &grd) {


    // grd.omega_jPlus_Ycent = std::vector<double>(grd.gridN, 0);


    /*for (int i = 0, j = 0; j < grd.gridN; i++, j++) {

        if (grd.Y_coord[i + 1] > grd.Y_coord[i] && i != 0)
            i++;

        grd.omega_jPlus_Ycent[j] =
                ((grd.Y_coord[i + grd.Nx + 1] + grd.Y_coord[i + grd.Nx])) / 2;

    }*/

    double value = 0;
    int indCur = 0;
    for (int i = 1; i < grd.Ny; i++)
        for (int j = 0; j < grd.Nx - 1; j++) {
            indCur = i * grd.Nx + j;
            value = (grd.Y_coord[indCur] + grd.Y_coord[indCur + 1]) / 2.;
            grd.omega_jPlus_Ycent.push_back(value);
        }
}

std::vector<double> func_omega_jMinus_Xcent(const std::vector<double> &X_coord,
                                            const int &Nx) {

    int gridN = (Nx - 1) * (X_coord.size() / Nx - 1);
    std::vector<double> omega_jMinus_Xcent(gridN, 0);

    for (int j = 0, i = 0; i < omega_jMinus_Xcent.size(); i++) {
        omega_jMinus_Xcent[i] = (X_coord[i + 1 + j] + X_coord[i + j]) / 2;

        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0;
         i < omega_jMinus_Xcent.size(); i += (Nx - 1), j++)
        omega_jMinus_Xcent[i] =
                (X_coord[i + 1 + j] + X_coord[i + 2 + j]) / 2;

    return omega_jMinus_Xcent;

}

std::vector<double> func_omega_jMinus_Ycent(const std::vector<double> &Y_coord,
                                            const int &Nx) {

    int gridN = (Nx - 1) * (Y_coord.size() / Nx - 1);
    std::vector<double> omega_jMinus_Ycent(gridN, 0);

    for (int j = 0, i = 0; i < Y_coord.size(); i++) {
        omega_jMinus_Ycent[i] =
                ((Y_coord[i + 1 + j] + Y_coord[i + j])) / 2;
        if (i % (Nx - 1) == 0 && i != 0)
            j++;
    }

    for (int i = (Nx - 1), j = 0;
         i < omega_jMinus_Ycent.size(); i += (Nx - 1), j++)
        omega_jMinus_Ycent[i] =
                (Y_coord[i + 2 + j] + Y_coord[i + 1 + j]) / 2;

    return omega_jMinus_Ycent;
}
