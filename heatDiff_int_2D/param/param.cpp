#include <param/param.h>
#include <GetFromFile.h>

Param getParam(const std::string &fileName) {

    GetFromFile dataFile(fileName);

    Param param;

    param.dt = dataFile.getWord<double>("timeStep");
    param.time = dataFile.getWord<double>("time");
    param.TLeft = dataFile.getWord<double>("tempLeft");
    param.TRight = dataFile.getWord<double>("tempRight");
    param.Ttop = dataFile.getWord<double>("tempTop");
    param.Tbot = dataFile.getWord<double>("tempBot");
    param.TInitial = dataFile.getWord<double>("tempIni");
    param.maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

    return param;

}