#include <extra/computeTInitial.h>
#include <GetFromFile.h>

std::vector<double> computeTInitial(const Grid &grid, const Settings &settings) {

    int gridN = (grid.nX - 1) * (grid.nY - 1);
    std::vector<double> heatDistrib_ini(gridN, settings.TInitial);


    for (int i = 2 * (grid.nX - 2) + 1;
         i < heatDistrib_ini.size() - (grid.nX - 1); i += grid.nX - 1)
        heatDistrib_ini[i] = settings.TRight;

    for (int i = 0; i < grid.nX - 1; i++)
        heatDistrib_ini[i] = settings.TLeft;

    for (int i = heatDistrib_ini.size() - (grid.nX - 1);
         i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = settings.TRight;

    for (int i = (grid.nX - 1);
         i < heatDistrib_ini.size() - (grid.nX - 1); i += grid.nX - 1)
        heatDistrib_ini[i] = settings.TLeft;

    return heatDistrib_ini;
}