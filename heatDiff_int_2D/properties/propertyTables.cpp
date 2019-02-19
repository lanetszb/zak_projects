#include <GetFromFile.h>

#include <properties/propertyTables.h>

PropertyTables getTables(const std::string &fileName) {

    PropertyTables propertyTables;

    GetFromFile dataFile(fileName);

    auto lambdaTableName = dataFile.getWord<std::string>("THERMALCOND_TABLE");
    auto densityTableName = dataFile.getWord<std::string>("DENSITY_TABLE");
    auto capacityTableName = dataFile.getWord<std::string>("CAPACITY_TABLE");

    getTable(propertyTables.lambdaTable, lambdaTableName);
    getTable(propertyTables.densityTable, densityTableName);
    getTable(propertyTables.capacityTable, capacityTableName);

    return propertyTables;
}

void getTable(std::vector<std::vector<double>> &table,
              const std::string &tableName) {

    GetFromFile getFromFile(tableName);

    int vec2DCol = getFromFile.getWord<int>("vec2DCol");
    std::vector<double> vec1DFor2D = getFromFile.getVector<double>("vec2D");

    for (int i = 0; i < vec1DFor2D.size() / vec2DCol; i++) {
        table.push_back(std::vector<double>());
        for (int j = 0; j < vec2DCol; j++)
            table.back().push_back(
                    vec1DFor2D[i * vec2DCol + j]);
    }

}