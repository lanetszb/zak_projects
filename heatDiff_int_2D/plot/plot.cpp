#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>
#include <grid/grid.h>
#include <plot/plot.h>


// data output

void makePlot(const Grid &grid, const std::vector<double> value) {

    double fictitiousValue = 0;

    std::vector<double> plotValue = getPlotValue(value, grid.nX,
                                                 fictitiousValue);

    outputPlot(grid, plotValue);

}

std::vector<double> getPlotValue(const std::vector<double> &value,
                                 const int &nX,
                                 const double &fictitiousValue) {

    std::vector<double> plotValue;

    for (int i = 0; i < value.size(); i++) {
        plotValue.push_back(value[i]);
        if ((i + 1) % (nX - 1) == 0)
            plotValue.push_back(fictitiousValue);
    }

    for (int i = 0; i < nX; i++)
        plotValue.push_back(fictitiousValue);

    return plotValue;
}

void outputPlot(const Grid &grid, const std::vector<double> plotValue) {

    std::ofstream oStream;

    int width = 15;

    oStream.open("out.txt");
    oStream.precision(4);
    oStream.setf(std::ios::scientific, std::ios::floatfield);

    for (int i = 0; i < grid.nodesX.size(); i++) {

        oStream << std::setw(width) << grid.nodesX[i];
        oStream << std::setw(width) << grid.nodesY[i];
        oStream << std::setw(width) << plotValue[i];
        oStream << std::endl;

        if ((i + 1) % grid.nX == 0)
            oStream << std::endl;
    }

    oStream.close();

    std::string Temp = "out.plt";
    oStream.open(Temp.c_str());


    oStream << "set term png size 1000,1000" << std::endl;
    oStream << "set output 'pm3d.png'" << std::endl;
    oStream << "set pm3d map corners2color c1" << std::endl;
    oStream << "set key outside" << std::endl;
    oStream << "set size square" << std::endl;
    oStream << "set pm3d map" << std::endl;
    oStream << "set cntrparam levels auto 7" << std::endl;
    oStream << "set zrange [0:]" << std::endl;
    oStream << "set palette rgbformulae 7,5,15" << std::endl;
    oStream << "set samples " << grid.nX << std::endl;
    oStream << "set isosamples " << grid.nY << std::endl;

    oStream << "splot 'out.txt' notitle" << std::endl;

    oStream.close();

    std::string plotTemp = "gnuplot " + Temp + "&& open pm3D.png";
    std::cout << system(plotTemp.c_str()) << std::endl;

}






