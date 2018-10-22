#ifndef HEATDIFFUSION_GRID_SURF_H
#define HEATDIFFUSION_GRID_SURF_H
#include <vector>


std::vector<double> func_omega_jPlus(std::vector<double> &X_coord,
                                     const int &Nx);

std::vector<double> func_omega_jMin(std::vector<double> &X_coord,
                                    const int &Nx);

std::vector<double> func_omega_iPlus(std::vector<double> &Y_coord,
                                     const int &Nx);

std::vector<double> func_omega_iMin(std::vector<double> &Y_coord,
                                    const int &Nx);


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

std::vector<double> func_omega_jMinus_Xcent(const std::vector<double> &X_coord,
                                            const int &Nx);

std::vector<double> func_omega_jMinus_Ycent(const std::vector<double> &Y_coord,
                                            const int &Nx);

#endif
