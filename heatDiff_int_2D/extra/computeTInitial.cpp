#include <extra/computeTInitial.h>
#include <GetFromFile.h>

std::vector<double> computeTInitial(const Grid &grid, const Settings &settings) {

    std::vector<double> heatDistrib_ini(grid.nCells, settings.TInitial);


    for (int i = 2 * (grid.nX - 2) + 1;
         i < heatDistrib_ini.size() - (grid.nX - 1); i += grid.nX - 1)
        heatDistrib_ini[i] = settings.TRight;

    for (int i = 0; i < grid.nX - 1; i++)
        heatDistrib_ini[i] = settings.TBot;

    for (int i = heatDistrib_ini.size() - (grid.nX - 1);
         i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = settings.TTop;

    for (int i = (grid.nX - 1);
         i < heatDistrib_ini.size() - (grid.nX - 1); i += grid.nX - 1)
        heatDistrib_ini[i] = settings.TLeft;

    return heatDistrib_ini;
}