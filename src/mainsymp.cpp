#include <iostream>
#include <string>
#include "libODE.h"
#include "libGradient.h"

using namespace std;

int main(int argc, char *argv[]){
    double t0=0, tmax = 6;
    int nSteps = 100;
    double omega;
    string fileName;

    if (argc == 3){
        omega = atof(argv[1]);
        fileName = argv[2];
    } else {
        cout << "Arguments required: double omega, string fileName\n";
        exit(1);
    }

    oscillatorGradientSymp F(omega);
    Array1D y0(2);
    y0[0] = 1;
    y0[1] = 0;
    
    Integrator I(F, y0, t0, tmax, nSteps, (string)"Verlet");

    I.sol.SaveToMFile(fileName);
    }