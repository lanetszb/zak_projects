#include <extra/extraData_read.h>
#include <GetFromFile.h>

void readLamb(Lamb &lmb, const std::string &thermalCond_table) {

    GetFromFile readTable(thermalCond_table);

    int vec2DCol = readTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = readTable.getVector<double>("vec2D");

    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        lmb.lambTable.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            lmb.lambTable.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }

}

void readDens(Lamb &lmb, const std::string &density_table) {

    GetFromFile readTable(density_table);

    int vec2DCol = readTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = readTable.getVector<double>("vec2D");

    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        lmb.densTable.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            lmb.densTable.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }
}

void readCapac(Lamb &lmb, const std::string &heatCapacity_table) {

    GetFromFile readTable(heatCapacity_table);

    int vec2DCol = readTable.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = readTable.getVector<double>("vec2D");

    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        lmb.capacTable.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            lmb.capacTable.back().push_back(vec1DFor2D[i * vec2DCol + j]);
    }
}