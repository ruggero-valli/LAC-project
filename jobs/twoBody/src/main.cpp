#include <iostream>
#include <string>
#include "libODE.h"
#include "libGradient.h"
#include "libUnits.h"

using namespace std;
using namespace units;

int main(int argc, char *argv[]){
    string outFilePath;
    string cfgUnitsFilePath;
    if (argc > 2){
        outFilePath = argv[1];
        cfgUnitsFilePath = argv[2];
    }
    else {
        cout << "Pass a fileName!";
        exit(1);
    }
    units::init(cfgUnitsFilePath);
    double t0=0, tmax = 100;
    int nSteps = 1000;
    int N = 2;
    Array1D m(N);
    m[0] = 1.989e30/M;
    m[1] = 3.285e23/M;

    NbodiesGradientSymp F(m);
    Array1D y0(6*N);

    double majsemiaxis = 5.791e10/L;
    double initVel = 47.36e3/(L/T);
    y0[0] = 0;           y0[1] = 0;                  y0[2] = 0;
    y0[3] = majsemiaxis; y0[4] = 0;                  y0[5] = 0;
    y0[6] = 0;           y0[7] = -initVel*m[1]/m[0]; y0[8] = 0;
    y0[9] = 0;           y0[10] = initVel;           y0[11] = 0;

    Integrator I(F, y0, t0, tmax, nSteps, (string)"Verlet");
    
    I.sol.SaveToMFile(outFilePath);
    }