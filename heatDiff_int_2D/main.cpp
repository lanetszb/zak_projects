#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>




int main(int narg, char **arg) {

    // reading data file
    GetFromFile dataFile(arg[1]);

    auto X0 = dataFile.getWord<double>("X0");
    auto Y0 = dataFile.getWord<double>("Y0");
    auto XL = dataFile.getWord<double>("XL");
    auto YL = dataFile.getWord<double>("YL");
    auto Nx = dataFile.getWord<double>("NODES_NUM_X");
    auto Ny = dataFile.getWord<double>("NODES_NUM_Y");

    auto dt = dataFile.getWord<double>("timeStep");
    auto time = dataFile.getWord<double>("time");
    auto Tl = dataFile.getWord<double>("tempLeft");
    auto Tr = dataFile.getWord<double>("tempRight");
    auto Ttop = dataFile.getWord<double>("tempTop");
    auto Tbot = dataFile.getWord<double>("tempBot");
    auto T0 = dataFile.getWord<double>("tempIni");
    auto Lx = dataFile.getWord<double>("lengthX");
    auto Ly = dataFile.getWord<double>("lengthY");
    auto Nx = dataFile.getWord<double>("Nx");
    auto Ny = dataFile.getWord<double>("Ny");
    auto maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

    // ***Numerical solution for heat diffusion begins here***

    double dx = Lx / (Nx + 1); // (m);
    double dy = Ly / (Ny + 1); // (m);
    double V = dx * dy;


    std::cout << dx << std::endl;
    std::cout << dy << std::endl;
    std::cout << V << std::endl;

    auto gridN = (Nx - 1) * (Ny - 1);

    std::vector<double> gridInd(gridN, 0);
    std::vector<double> omega_iPlus(gridN, Y_coord[1] - Y_coord[0]);
    std::vector<double> omega_jPlus(gridN, X_coord[1] - X_coord[0]);
    std::vector<double> omega_iMin(gridN, 0);
    std::vector<double> omega_jMin(gridN, 0);
    std::vector<double> vol(gridN, 0);

    for (int i = 0; i < gridN; i++) {

        omega_jMin[i] = omega_jPlus[i];
        omega_iMin[i] = omega_iPlus[i];

        vol[i] = omega_jPlus[i] * omega_iPlus[i];

    }

    for (int i = 0; i < gridN; i++)
        std::cout << "omega_jPlus " << omega_jPlus[i] << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < gridN; i++)
        std::cout << "volume " << vol[i] << std::endl;
    std::cout << std::endl;


    return 0;

}