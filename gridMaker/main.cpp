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

    // ***Numerical solution for heat diffusion begins here***

    std::cout << X0 << std::endl;
    std::cout << YL << std::endl;
    std::cout << Ny << std::endl;

    char response;

    std::cout << "Does your grid system regular (dx and dy are constants), Y/N?" << std::endl;
    std::cin >> response;
    if (response == 'Y') {

        auto dx = (XL - X0) / (Nx - 1);
        std::vector<double> X_coord(Nx, 0);

        for (int i = 0; i < 1; i++)
            X_coord[i] = X0;

        for (int i = 1; i < Nx; i++)
            X_coord[i] = X_coord[i - 1] + dx;

        auto dy = (YL - Y0) / (Ny - 1);
        std::vector<double> Y_coord(Ny, 0);

        for (int i = 0; i < 1; i++)
            Y_coord[i] = Y0;

        for (int i = 1; i < Nx; i++)
            Y_coord[i] = Y_coord[i - 1] + dy;

        // ***data output***
        std::ofstream oStream;

        oStream.open("out.txt");

        oStream << "Node_X" << std:: endl;

        for (int i = 0; i < Nx; i++)
            for (int j = 0; j < Nx; j++)
                oStream << X_coord[j] << " ";
        oStream << std::endl << std::endl;

        oStream << "Node_Y" << std:: endl;

        for (int i = 0; i < Ny; i++)
            for (int j = 0; j < Ny; j++)
                oStream << Y_coord[j] << " ";
        oStream << std::endl << std::endl;

        oStream << std::endl;

        oStream.close();

    } else if (response == 'N') {
        std::cout << "Fuck off" << std::endl;
    }

    return 0;
}