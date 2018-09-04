#ifndef HEATDIFFUSION_GRID_H
#define HEATDIFFUSION_GRID_H

// Structure containing all grid attributes.
struct Grid {
    // Nodes quantity in x direction
    int Nx;

    // Nodes quantity in y direction
    int Ny;
    int gridN;
    std::vector<double> X_coord;
    std::vector<double> Y_coord;
    std::vector<double> Xcenter;
    std::vector<double> Ycenter;
    std::vector<double> omega_jPlus;
    std::vector<double> omega_jMin;
    std::vector<double> omega_iPlus;
    std::vector<double> omega_iMin;
    std::vector<double> gridVolume;
    std::vector<double> omega_iPlus_Xcent;
    std::vector<double> omega_iPlus_Ycent;
    std::vector<double> omega_iMinus_Xcent;
    std::vector<double> omega_iMinus_Ycent;
    std::vector<double> getLeft_dL;
    std::vector<double> getRight_dL;
    std::vector<double> getTop_dL;
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
