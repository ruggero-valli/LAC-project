#include <stdio.h>
<<<<<<< HEAD
#include <cmath>
#include "libODE.h"
=======
#include <iostream>
#include "libODE.h"
#include "Eigen/Dense"
>>>>>>> 2183916babe635354e6779ecc7542fafdb12cae7

using namespace std;
using namespace Eigen;

<<<<<<< HEAD

vector <double> F (vector <double> y, double t ) {return y;} 


=======
ArrayXd F (ArrayXd& y, double t ) {return (-y);} 
>>>>>>> 2183916babe635354e6779ecc7542fafdb12cae7

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