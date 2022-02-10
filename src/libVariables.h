#ifndef LIBVARIABLES_H
#define LIBVARIABLES_H

#include <string>

namespace variables{
extern int nSteps;
extern int t0;
extern int tmax;
extern std::string method;

void init(std::string& cfgFile);

}

#endif