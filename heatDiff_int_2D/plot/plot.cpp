#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>
#include <grid/gridStruct.h>
#include <plot/plot.h>


// data output

void makePlot(const Grid &grid, const std::vector<double> value) {

    Plot plot;

    plot.nodesX = getNodesX(grid.nodesX, grid.nX, grid.dX);
    plot.nodesY = getNodesY(grid.nodesY, grid.nX, grid.dY);
    plot.value = getValue(value, grid.nX);

    outputPlot(grid, plot);

}

std::vector<double> getNodesX(const std::vector<double> &nodesX,
                              const int &nX,
                              const int &dX) {

    std::vector<double> X_gnuplot(nodesX.size(), 0);
    X_gnuplot[0] = nodesX[0];


    for (int i = 1; i < X_gnuplot.size(); i++) {
        X_gnuplot[i] = X_gnuplot[i - 1];
        if (i % nX == 0)
            X_gnuplot[i] = X_gnuplot[i] + dX;

    }
    return X_gnuplot;
}

std::vector<double> getNodesY(const std::vector<double> &nodesY, const int &nX,
                              const int &dY) {

    std::vector<double> Y_gnuplot(nodesY.size(), 0);

    for (int i = 0; i < 1; i++)
        Y_gnuplot[i] = nodesY[0];

    for (int i = 1; i < Y_gnuplot.size(); i++) {

        if (i < nX)
            Y_gnuplot[i] = Y_gnuplot[i - 1] + dY;
        else
            Y_gnuplot[i] = Y_gnuplot[i - nX];
    }
    return Y_gnuplot;
}

std::vector<double> getValue(const std::vector<double> &value, const int &nX) {

    std::vector<double> plotValue;

    for (int i = 0; i < nX; i++)
        for (int j = 0; j < nX; j++)
            plotValue.push_back(value[i + j * (nX - 1)]);

    for (int i = nX - 1; i < plotValue.size(); i += nX)
        plotValue[i] = 0;

    for (int i = plotValue.size() - (nX); i < plotValue.size(); i++)
        plotValue[i] = 0;

    return plotValue;
}

void outputPlot(const Grid &grid, const Plot &plot) {

    std::ofstream oStream;

    int width = 7;

    oStream.open("out.txt");

    for (int i = 0; i < plot.nodesX.size(); i++) {

        if (i % grid.nX == 0 && i != 0)
            oStream << std::endl;

        oStream << plot.nodesX[i] << "  ";
        oStream << plot.nodesY[i] << "  ";
        oStream << plot.value[i] << "  ";
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






