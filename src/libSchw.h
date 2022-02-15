#ifndef LIBSCHW_H
#define LIBSCHW_H

#include <string>
#include "libUtils.h"

namespace Schw{

    extern int Npart;
    extern Array1D m;
    extern Array1D r0;
    extern Array1D v0;

    void init(std::string& cfgFile);
}

#endif