#ifndef HEATDIFFUSION_GRID_H
#define HEATDIFFUSION_GRID_H

// Structure containing all grid attributes.
struct Grid {
    // Nodes quantity in x direction.
    int Nx;

    // Nodes quantity in y direction.
    int Ny;

    // total number of grid blocks.
    int gridN;

    // x coordinates of grid blocks.
    std::vector<double> X_coord;

    // y coordinates of grid blocks.
    std::vector<double> Y_coord;

    // x coordinates of grid block centers.
    std::vector<double> Xcenter;

    // y coordinates of grid block centers.
    std::vector<double> Ycenter;

    // surface area j+.
    std::vector<double> omega_jPlus;

    // surface area j-.
    std::vector<double> omega_jMin;

    // surface area i+.
    std::vector<double> omega_iPlus;

    // surface area i-.
    std::vector<double> omega_iMin;

    // grid volumes.
    std::vector<double> gridVolume;

    // x center of i+ surface.
    std::vector<double> omega_iPlus_Xcent;

    // y center of i+ surface.
    std::vector<double> omega_iPlus_Ycent;

    // x center of i- surface.
    std::vector<double> omega_iMinus_Xcent;

    // y center of i- surface.
    std::vector<double> omega_iMinus_Ycent;

    // x center of j+ surface.
    std::vector<double> omega_jPlus_Xcent;

    // y center of j+ surface.
    std::vector<double> omega_jPlus_Ycent;

    // distance between grid i and i - 1.
    std::vector<double> getLeft_dL;

    // distance between grid i and i + 1.
    std::vector<double> getRight_dL;

    // distance between grid j and j + 1.
    std::vector<double> getTop_dL;

    // distance between grid j and j - 1.
    std::vector<double> getBot_dL;
};

std::vector<double> func_Xcenter(std::vector<double> &X_coord, const int &Nx);

std::vector<double> func_Ycenter(std::vector<double> &Y_coord, const int &Nx);

std::vector<double> func_omega_jPlus(std::vector<double> &X_coord,
                                     const int &Nx);

std::vector<double> func_omega_jMin(std::vector<double> &X_coord,
                                    const int &Nx);

std::vector<double> func_omega_iPlus(std::vector<double> &Y_coord,
                                     const int &Nx);

std::vector<double> func_omega_iMin(std::vector<double> &Y_coord,
                                    const int &Nx);

std::vector<double> func_gridVolume(std::vector<double> omega_iPlus,
                                    std::vector<double> omega_iMin,
                                    std::vector<double> omega_jPlus,
                                    std::vector<double> omega_jMin,
                                    const int gridN);

std::vector<double> func_omega_iPlus_Xcent(std::vector<double> &X_coord,
                                           const int &Nx);

std::vector<double> func_omega_iPlus_Ycent(std::vector<double> &Y_coord,
                                           const int &Nx);

std::vector<double> func_omega_iMinus_Xcent(std::vector<double> &X_coord,
                                            const int &Nx);

std::vector<double> func_omega_iMinus_Ycent(const std::vector<double> &Y_coord,
                                            const int &Nx);

std::vector<double> func_omega_jPlus_Xcent(const std::vector<double> &X_coord,
                                            const int &Nx);

std::vector<double> func_omega_jPlus_Ycent(const std::vector<double> &Y_coord,
                                           const int &Nx);


std::vector<double> func_getLeft_dL(const std::vector<double> &gridXcent,
                                    const int &Nx);

std::vector<double> func_getRight_dL(const std::vector<double> &gridXcent,
                                     const int &Nx);

std::vector<double> func_getTop_dL(const std::vector<double> &gridYcent,
                                   const int &Nx);

std::vector<double> func_getBot_dL(const std::vector<double> &gridYcent,
                                   const int &Nx);

Grid func_gridCalculation(const std::string &gridFileName,
                          const std::string &nodesFileName);

#endif
