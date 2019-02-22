#include <vector>

#include <GetFromFile.h>

#include <properties/propertyTables.h>


PropertyTables getTables(const std::string &fileName) {

    PropertyTables propertyTables;

    GetFromFile dataFile(fileName);

    auto lambdaTableName = dataFile.getWord<std::string>("THERMALCOND_TABLE");
    auto densityTableName = dataFile.getWord<std::string>("DENSITY_TABLE");
    auto capacityTableName = dataFile.getWord<std::string>("CAPACITY_TABLE");

    getTable(propertyTables.lambda, lambdaTableName);
    getTable(propertyTables.density, densityTableName);
    getTable(propertyTables.capacity, capacityTableName);

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


double getValue(const std::vector<std::vector<double>> &table,
                const double &T) {

    double value = 0;


    double TCurrent = 0;
    double valueCurrent = 0;

    double TNext = 0;
    double valueNext = 0;


    if (T <= table[0][0])
        value = table[0][1];

    else if (T > table[table.size() - 1][0])
        value = table[table.size() - 1][1];

    else
        for (int i = 0; i < table.size() - 1; i++) {

            TCurrent = table[i][0];
            valueCurrent = table[i][1];

            TNext = table[i + 1][0];
            valueNext = table[i + 1][1];

            if (T <= TNext) {

                value = valueCurrent +
                        (valueNext - valueCurrent) / (TNext - TCurrent) *
                        (T - TCurrent);

                break;

            }
        }

    return value;
}