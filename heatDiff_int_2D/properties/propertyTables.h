#ifndef PROPERTYTABLES_H
#define PROPERTYTABLES_H


#include <vector>

struct PropertyTables {

    std::vector<std::vector<double>> lambdaTable;

    std::vector<std::vector<double>> densityTable;

    std::vector<std::vector<double>> capacityTable;

};

void getTable(std::vector<std::vector<double>> &table,
              const std::string &tableName);

PropertyTables getTables(const std::string &fileName);

#endif
