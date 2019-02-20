#ifndef PLOT_H
#define PLOT_H


struct Plot {

    // X coordinates for gnuplot
    std::vector<double> X_gnuplot;

    // Y coordinates for gnuplot
    std::vector<double> Y_gnuplot;

    // Temperature values for gnuplot

    std::vector<double> T_gnuplot;

};

std::vector<double> func_Xgnuplot(std::vector<double> &X_coord, const int &Nx,
                                  const int dx);

std::vector<double> func_Ygnuplot(std::vector<double> &Y_coord, const int &Nx,
                                  const int dy);

std::vector<double> func_Tgnuplot(std::vector<double> &X_coord,
                                  std::vector<double> &X_gnuplot,
                                  std::vector<double> &heatDistr_ini,
                                  const int &Nx);

void func_oStream(Grid &grd, Plot &plt);

void func_plot(Grid &grd, Plot &plt,
               const std::vector<double> heatDistr_ini);


#endif //HEATDIFFUSION_PLOT_H
