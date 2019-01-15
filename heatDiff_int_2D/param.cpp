#include <param.h>
#include <GetFromFile.h>

void getParam(Param &prm, Grid &grd, std::string &dataFileName) {

    std::vector<double> func_getLeft_lambda(const std::vector<double> &lamb,
                                            const int &Nx);

    std::vector<double> func_getRight_lambda(const std::vector<double> &lamb,
                                             const int &Nx);

    std::vector<double> func_getTop_lambda(const std::vector<double> &lamb,
                                           const int &Nx);

    std::vector<double> func_getBot_lambda(const std::vector<double> &lamb,
                                           const int &Nx);

    std::vector<double> func_heatDistrib_ini(const int &Ny, const int &Nx,
                                             const double &T0, const double &Tl,
                                             const double &Tr);

    // ***reading the required input data***

    GetFromFile dataFile(dataFileName);

    prm.dt = dataFile.getWord<double>("timeStep");
    prm.time = dataFile.getWord<double>("time");
    prm.lambda = dataFile.getWord<double>("thermalCond");

    prm.Tl = dataFile.getWord<double>("tempLeft");
    prm.Tr = dataFile.getWord<double>("tempRight");
    prm.Ttop = dataFile.getWord<double>("tempTop");
    prm.Tbot = dataFile.getWord<double>("tempBot");
    prm.T0 = dataFile.getWord<double>("tempIni");

    prm.dens = dataFile.getWord<double>("density");
    prm.capac = dataFile.getWord<double>("heatCapac");

    prm.maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

    std::vector<double> lamb(grd.gridN, prm.lambda);

    prm.getBot_lambda = func_getBot_lambda(lamb, grd.Nx);
    prm.getTop_lambda = func_getTop_lambda(lamb, grd.Nx);
    prm.getLeft_lambda = func_getLeft_lambda(lamb, grd.Nx);
    prm.getRight_lambda = func_getRight_lambda(lamb, grd.Nx);

}

//***all the functions are listed below***

std::vector<double> func_getLeft_lambda(const std::vector<double> &lamb,
                                        const int &Nx) {

    std::vector<double> getLeft_lambda(lamb.size(), 0);

    for (int i = 0; i < lamb.size(); i++) {
        getLeft_lambda[i] = lamb[i - 1];
    }

    for (int i = 0; i < lamb.size(); i += Nx - 1)
        getLeft_lambda[i] = 0;

    return getLeft_lambda;
}

std::vector<double> func_getRight_lambda(const std::vector<double> &lamb,
                                         const int &Nx) {

    std::vector<double> getRight_lambda(lamb.size(), 0);

    for (int i = 0; i < lamb.size(); i++)
        getRight_lambda[i] = lamb[i + 1];

    for (int i = Nx - 2; i < lamb.size(); i += Nx - 1)
        getRight_lambda[i] = 0;

    return getRight_lambda;
}

std::vector<double> func_getTop_lambda(const std::vector<double> &lamb,
                                       const int &Nx) {

    std::vector<double> getTop_lambda(lamb.size(), 0);

    for (int i = 0; i < getTop_lambda.size(); i++) {
        getTop_lambda[i] = lamb[i + Nx - 1];
    }

    for (int i = getTop_lambda.size() - (Nx - 1);
         i < getTop_lambda.size(); i++)
        getTop_lambda[i] = 0;

    return getTop_lambda;
}


std::vector<double> func_getBot_lambda(const std::vector<double> &lamb,
                                       const int &Nx) {

    std::vector<double> getBot_lambda(lamb.size(), 0);

    for (int i = 0; i < getBot_lambda.size(); i++) {
        getBot_lambda[i] = lamb[i - (Nx - 1)];
    }

    for (int i = 0; i < Nx - 1; i++)
        getBot_lambda[i] = 0;

    return getBot_lambda;
}