#ifndef UNITS_H
#define UNITS_H

#include <string>

namespace units{
    
extern double M;       // Mass unit: Sun's mass in kilograms
extern double L;       // Length unit: Mercury's semimajor axis in metres
extern double G;       // Gravitational constant
extern double T;       // Time unit: characteristic time in seconds

void init(std::string& cfgFilePath);
}

#endif