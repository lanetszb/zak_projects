#include <param/param.h>
#include <GetFromFile.h>

void getParam(Param &prm, Grid &grd, std::string &dataFileName) {

    // ***reading the required input data***

    GetFromFile dataFile(dataFileName);

    prm.dt = dataFile.getWord<double>("timeStep");
    prm.time = dataFile.getWord<double>("time");
    /*prm.lambda = dataFile.getWord<double>("thermalCond");*/

    prm.Tl = dataFile.getWord<double>("tempLeft");
    prm.Tr = dataFile.getWord<double>("tempRight");
    prm.Ttop = dataFile.getWord<double>("tempTop");
    prm.Tbot = dataFile.getWord<double>("tempBot");
    prm.T0 = dataFile.getWord<double>("tempIni");

    prm.dens = dataFile.getWord<double>("density");
    prm.capac = dataFile.getWord<double>("heatCapac");

    prm.maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

}