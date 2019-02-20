#ifndef PLOT_H
#define PLOT_H


struct Plot {

    std::vector<double> nodesX;

    std::vector<double> nodesY;

    std::vector<double> value;

};

std::vector<double> getNodesX(const std::vector<double> &nodesX,
                              const int &nX, const int &dX);

std::vector<double> getNodesY(const std::vector<double> &nodesY,
                              const int &nX, const int &dY);

std::vector<double> getValue(const std::vector<double> &value, const int &nX);

void outputPlot(const Grid &grid, const Plot &plot);

void makePlot(const Grid &grid, const std::vector<double> value);


#endif
