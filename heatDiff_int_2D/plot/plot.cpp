#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>
#include <grid/gridStruct.h>
#include <plot/plot.h>


// data output

void func_plot(Grid &grd, Plot &plt, std::vector<double> X) {


    plt.X_gnuplot = func_Xgnuplot(grd.X_coord, grd.nX, grd.dx);
    plt.Y_gnuplot = func_Ygnuplot(grd.Y_coord, grd.nX, grd.dy);
    plt.T_gnuplot = func_Tgnuplot(grd.X_coord, plt.X_gnuplot, X,
                                  grd.nX);

    func_oStream(grd, plt);

}

std::vector<double> func_Xgnuplot(std::vector<double> &X_coord, const int &Nx,
                                  const int dx) {

    std::vector<double> X_gnuplot(X_coord.size(), 0);
    X_gnuplot[0] = X_coord[0];


    for (int i = 1; i < X_gnuplot.size(); i++) {
        X_gnuplot[i] = X_gnuplot[i - 1];
        if (i % Nx == 0)
            X_gnuplot[i] = X_gnuplot[i] + dx;

    }
    return X_gnuplot;
}

std::vector<double> func_Ygnuplot(std::vector<double> &Y_coord, const int &Nx,
                                  const int dy) {

    std::vector<double> Y_gnuplot(Y_coord.size(), 0);

    for (int i = 0; i < 1; i++)
        Y_gnuplot[i] = Y_coord[0];

    for (int i = 1; i < Y_gnuplot.size(); i++) {

        if (i < Nx)
            Y_gnuplot[i] = Y_gnuplot[i - 1] + dy;
        else
            Y_gnuplot[i] = Y_gnuplot[i - Nx];
    }
    return Y_gnuplot;
}

std::vector<double> func_Tgnuplot(std::vector<double> &X_coord,
                                  std::vector<double> &X_gnuplot,
                                  std::vector<double> &X,
                                  const int &Nx) {

    std::vector<double> T_gnuplot;

    for (int i = 0; i < Nx; i++)
        for (int j = 0; j < Nx; j++)
            T_gnuplot.push_back(X[i + j * (Nx - 1)]);

    for (int i = Nx - 1; i < T_gnuplot.size(); i += Nx)
        T_gnuplot[i] = 0;

    for (int i = T_gnuplot.size() - (Nx); i < T_gnuplot.size(); i++)
        T_gnuplot[i] = 0;

    return T_gnuplot;
}

void func_oStream(Grid &grd, Plot &plt) {

    std::ofstream oStream;

    int width = 7;

    oStream.open("out.txt");

    for (int i = 0; i < plt.X_gnuplot.size(); i++) {

        if (i % grd.nX == 0 && i != 0)
            oStream << std::endl;

        oStream << plt.X_gnuplot[i] << "  ";
        oStream << plt.Y_gnuplot[i] << "  ";
        oStream << plt.T_gnuplot[i] << "  ";
        oStream << std::endl;
    }

    oStream.close();

    std::string Temp = "out.plt";
    oStream.open(Temp.c_str());
    oStream.precision(7);
    int w = 15;
    oStream.setf(std::ios::scientific, std::ios::floatfield);

    oStream << "set term png size 1000,1000" << std::endl;
    oStream << "set output 'pm3d.png'" << std::endl;
    oStream << "set pm3d map corners2color c1" << std::endl;
    oStream << "set key outside" << std::endl;
    oStream << "set size square" << std::endl;
    oStream << "set pm3d map" << std::endl;
    oStream << "set cntrparam levels auto 7" << std::endl;
    // oStream << "set cbtics 2000" << std::endl;
    oStream << "set zrange [0:]" << std::endl;
    oStream << "set palette rgbformulae 7,5,15" << std::endl;
    oStream << "set samples 10" << std::endl;
    oStream << "set isosamples 10" << std::endl;

    oStream << "splot 'out.txt' notitle" << std::endl;

    oStream.close();

    std::string plotTemp = "gnuplot " + Temp + "&& open pm3D.png";
    std::cout << system(plotTemp.c_str()) << std::endl;

}






