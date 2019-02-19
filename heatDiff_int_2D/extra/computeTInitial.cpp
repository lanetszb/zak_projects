#include <extra/computeTInitial.h>
#include <GetFromFile.h>

std::vector<double> computeTInitial(const Grid &grid, const Param &param) {

    int gridN = (grid.nX - 1) * (grid.nY - 1);
    std::vector<double> heatDistrib_ini(gridN, param.TInitial);


    for (int i = 2 * (grid.nX - 2) + 1;
         i < heatDistrib_ini.size() - (grid.nX - 1); i += grid.nX - 1)
        heatDistrib_ini[i] = param.TRight;

    for (int i = 0; i < grid.nX - 1; i++)
        heatDistrib_ini[i] = param.TLeft;

    for (int i = heatDistrib_ini.size() - (grid.nX - 1);
         i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = param.TRight;

    for (int i = (grid.nX - 1);
         i < heatDistrib_ini.size() - (grid.nX - 1); i += grid.nX - 1)
        heatDistrib_ini[i] = param.TLeft;

    return heatDistrib_ini;
}