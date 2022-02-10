#include <iostream>
#include <string>
#include "libODE.h"
#include "libGradient.h"
#include "libUnits.h"
#include "libNBody.h"
#include "libVariables.h"

using namespace std;

int main(int argc, char *argv[]){
    string outFilePath;
    string cfgUnitsFilePath;
    string cfgNBodyFilePath;
    string cfgVariablesFilePath;
    if (argc > 4){
        outFilePath = argv[1];
        cfgUnitsFilePath = argv[2];
        cfgNBodyFilePath = argv[3];
        cfgVariablesFilePath = argv[4];
    }
    else {
        cout << "Error: Pass a fileName!\n";
        exit(1);
    }
    units::init(cfgUnitsFilePath);
    NBody::init(cfgNBodyFilePath);
    variables::init(cfgVariablesFilePath);
    
    //double t0=0, tmax = 6.28*200;
    //int nSteps = 1000*200;

    NbodiesGradientSymp F(NBody::m);
    Array1D y0(6*NBody::Npart);
    RVtoU(y0,NBody::r0, NBody::v0);

    Integrator I(F, y0, variables::t0, variables::tmax, variables::nSteps, variables::method); //(string)"Verlet");
    
    I.sol.SaveToMFile(outFilePath);
    }