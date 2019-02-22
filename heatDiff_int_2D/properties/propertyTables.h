#ifndef PROPERTYTABLES_H
#define PROPERTYTABLES_H


#include <vector>

struct PropertyTables {

    std::vector<std::vector<double>> lambda;

    std::vector<std::vector<double>> density;

    std::vector<std::vector<double>> capacity;

};

void getTable(std::vector<std::vector<double>> &table,
              const std::string &tableName);

PropertyTables getTables(const std::string &fileName);

double getValue(const std::vector<std::vector<double>> &table,
                const double &T);

#endif
