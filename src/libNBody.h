#ifndef LIBNBODY_H
#define LIBNBODY_H

#include <string>
#include "libUtils.h"

namespace NBody{
    
extern int N;
extern Array1D m;
extern Array2D r0;
extern Array2D v0;

void init(std::string& cfgFile);

}

#endif