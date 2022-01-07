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
        cout << "Pass a fileName!";
        exit(1);
    }
    units::init(cfgUnitsFilePath);
    NBody::init(cfgNBodyFilePath);
    
    double t0=0, tmax = 100;
    int nSteps = 1000;

    NbodiesGradientSymp F(NBody::m);
    Array1D y0(6*NBody::Npart);
    RVtoU(y0,NBody::r0, NBody::v0);

    Integrator I(F, y0, t0, tmax, nSteps, (string)"Verlet");
    
    I.sol.SaveToMFile(outFilePath);
    }