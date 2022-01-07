#include <iostream>
#include <string>
#include "libODE.h"
#include "libGradient.h"

using namespace std;

int main(int argc, char *argv[]){
    double t0=0, tmax = 1;
    int nSteps = 100;
    double lambda;
    string fileName;

    if (argc == 3){
        lambda = atof(argv[1]);
        fileName = argv[2];
    } else {
        cout << "Arguments required: double lambda, string fileName\n";
        exit(1);
    }

    testGradient F(lambda);
    Array1D y0(1);
    y0 << 1;

    Integrator I(F, y0, t0, tmax, nSteps, (string)"EE");

    I.sol.SaveToMFile(fileName);
    }