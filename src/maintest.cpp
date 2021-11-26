#include <stdio.h>
#include <iostream>
#include "libODE.h"
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

ArrayXd F (ArrayXd& y, double t ) {return (-y);} 

int main(){

    double t0=0, tmax = 10;
    int nSteps = 10;
    ArrayXd y0(1);
    y0 << 1;

    Integrator I(F, y0, t0, tmax, nSteps);

    FILE *fout = fopen("out.dat", "w");

    for (int i=0; i<=nSteps; i++){
        fprintf(fout, "%lf %lf\n", I.sol.t[i], I.sol.U(i,0));
    }

    fclose(fout);
    }