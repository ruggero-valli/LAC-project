#include <iostream>
#include <string>
#include "libODE.h"
#include "libGradient.h"

using namespace std;

int main(int argc, char *argv[]){

    double t0=0, tmax = 100;
    int nSteps = 10000;
    lorenzGradient F(10,28,8./3);
    Array1D y0(3);
    y0[0] = 1; y0[1] = 1; y0[2] = 1;

    Integrator I(F, y0, t0, tmax, nSteps, (string)"RK5");
    
    string FileName;
    if (argc > 1){
        FileName = argv[1];
    }
    else {
        cout << "Pass a fileName!";
        exit(1);
    }
    I.sol.SaveToMFile(FileName);
    }