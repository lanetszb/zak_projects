#ifndef PLOT_H
#define PLOT_H


std::vector<double> getPlotValue(const std::vector<double> &value,
                                 const int &nX,
                                 const double &fictitiousValue);

void outputPlot(const Grid &grid, const std::vector<double> plotValue);

void makePlot(const Grid &grid, const std::vector<double> value);


#endif
