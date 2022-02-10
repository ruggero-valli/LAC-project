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

    Array1D y0(6*NBody::Npart);
    RVtoU(y0,NBody::r0, NBody::v0);
    
    if (variables::method == "EE" || variables::method == "RK4" || variables::method == "RK5"){
        NbodiesGradient F(NBody::m);
        Integrator I(F, y0, variables::t0, variables::tmax, variables::nSteps, variables::method);
        I.sol.SaveToMFile(outFilePath);
    }
    if (variables::method == "SE" || variables::method == "Verlet" || variables::method == "S4"){
        NbodiesGradientSymp F(NBody::m);
        Integrator I(F, y0, variables::t0, variables::tmax, variables::nSteps, variables::method);
        I.sol.SaveToMFile(outFilePath);
    }
}