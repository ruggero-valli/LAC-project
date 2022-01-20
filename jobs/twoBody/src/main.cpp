#include <iostream>
#include <string>
#include "libODE.h"
#include "libGradient.h"
#include "libUnits.h"
#include "libNBody.h"

using namespace std;

int main(int argc, char *argv[]){
    string outFilePath;
    string cfgUnitsFilePath;
    string cfgNBodyFilePath;
    if (argc > 3){
        outFilePath = argv[1];
        cfgUnitsFilePath = argv[2];
        cfgNBodyFilePath = argv[3];
    }
    else {
        cout << "Error: Pass a fileName!\n";
        exit(1);
    }
    units::init(cfgUnitsFilePath);
    NBody::init(cfgNBodyFilePath);
    
    double t0=0, tmax = 6.28*200;
    int nSteps = 1000*200;

    NbodiesGradient F(NBody::m);
    Array1D y0(6*NBody::Npart);
    RVtoU(y0,NBody::r0, NBody::v0);

    Integrator I(F, y0, t0, tmax, nSteps, (string)"RK5");
    
    I.sol.SaveToMFile(outFilePath);
    }