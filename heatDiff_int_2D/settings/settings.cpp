#include <settings/settings.h>
#include <GetFromFile.h>

Settings getSettings(const std::string &fileName) {

    GetFromFile dataFile(fileName);

    Settings settings;

    settings.dt = dataFile.getWord<double>("timeStep");
    settings.time = dataFile.getWord<double>("time");
    settings.TLeft = dataFile.getWord<double>("tempLeft");
    settings.TRight = dataFile.getWord<double>("tempRight");
    settings.Ttop = dataFile.getWord<double>("tempTop");
    settings.Tbot = dataFile.getWord<double>("tempBot");
    settings.TInitial = dataFile.getWord<double>("tempIni");
    settings.maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

    return settings;

}