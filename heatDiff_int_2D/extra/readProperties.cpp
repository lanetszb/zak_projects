#include <extra/readProperties.h>
#include <GetFromFile.h>

void readLambda(Properties &properties, const std::string &lambdaTable) {

    GetFromFile readTable(lambdaTable);

    int vec2DCol = readTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = readTable.getVector<double>("vec2D");

    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        properties.lambdaTable.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            properties.lambdaTable.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }

}

void readDensity(Properties &properties, const std::string &densityTable) {

    GetFromFile readTable(densityTable);

    int vec2DCol = readTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = readTable.getVector<double>("vec2D");

    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        properties.densityTable.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            properties.densityTable.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }
}

void readCapacity(Properties &properties, const std::string &capacityTable) {

    GetFromFile readTable(capacityTable);

    int vec2DCol = readTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = readTable.getVector<double>("vec2D");

    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        properties.capacityTable.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            properties.capacityTable.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }
}

std::vector<double> computeTInitial(const int &nY, const int &nX,
                                    const double &TInitial, const double &TLeft,
                                    const double &TRight) {

    int gridN = (nX - 1) * (nY - 1);
    std::vector<double> heatDistrib_ini(gridN, TInitial);


    for (int i = 2 * (nX - 2) + 1;
         i < heatDistrib_ini.size() - (nX - 1); i += nX - 1)
        heatDistrib_ini[i] = TRight;

    for (int i = 0; i < nX - 1; i++)
        heatDistrib_ini[i] = TLeft;

    for (int i = heatDistrib_ini.size() - (nX - 1);
         i < heatDistrib_ini.size(); i++)
        heatDistrib_ini[i] = TRight;

    for (int i = (nX - 1);
         i < heatDistrib_ini.size() - (nX - 1); i += nX - 1)
        heatDistrib_ini[i] = TLeft;

    return heatDistrib_ini;
}