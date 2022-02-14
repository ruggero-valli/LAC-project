#include <iostream>
#include <string>
#include "libODE.h"
#include "libGradient.h"
#include "libUnits.h"
#include "libSchw.h"
#include "libVariables.h"

using namespace std;

int main(int argc, char *argv[]){
    string outFilePath;
    string cfgUnitsFilePath;
    string cfgSchwFilePath;
    string cfgVariablesFilePath;
    if (argc > 4){
        outFilePath = argv[1];
        cfgUnitsFilePath = argv[2];
        cfgSchwFilePath = argv[3];
        cfgVariablesFilePath = argv[4];
    }
    else {
        cout << "Error: Pass a fileName!\n";
        exit(1);
    }
    
    units::init(cfgUnitsFilePath);
    Schw::init(cfgSchwFilePath);
    variables::init(cfgVariablesFilePath);

    Array1D y0(3);
    y0(0) = 0;
    y0(1) = 0;
    y0(2) = sqrt(Schw::r0(0)*Schw::r0(0) + Schw::r0(1)*Schw::r0(1) + Schw::r0(2)*Schw::r0(2));
   
    SchwGradient F(Schw::r0, Schw::v0, Schw::m);
    Integrator I(F, y0, variables::t0, variables::tmax, variables::nSteps, variables::method);
    I.sol.SaveToMFile(outFilePath);


}