#ifndef EXTRADATA_READ_H
#define EXTRADATA_READ_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <extra/extraData_struct.h>
#include <grid/grid_struct.h>

void readLamb(Lamb &lmb, const std::string &thermalCond_table);

void readDens(Lamb &lmb, const std::string &density_table);

void readCapac(Lamb &lmb, const std::string &heatCapacity_table);


#endif
