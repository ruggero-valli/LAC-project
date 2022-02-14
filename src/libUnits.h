#ifndef UNITS_H
#define UNITS_H

#include <string>

namespace units{
    
extern double M;       // Mass unit
extern double L;       // Length unit
extern double G;       // Gravitational constant
extern double T;       // Time unit
extern double c;       // Speed of light

void init(std::string& cfgFilePath);
}

#endif