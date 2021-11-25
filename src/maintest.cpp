#include <vector>
#include <stdio.h>
#include <cmath>
#include "libODE.cpp"

using namespace std;


inline vector <double> F (vector <double> y, double t ) {return y;} 



int main(){

    double t0=0, tmax = 10;
    int nSteps = 1000;
    vector<double> y0(1, 1);

    Integrator I(F, y0, t0, tmax, nSteps);

    FILE *fout = fopen("out.dat", "w");

    for (int i=0; i<=nSteps; i++){
        fprintf(fout, "%lf %lf\n", I.sol.t[i], I.sol(i,0));
    }

    fclose(fout);
    }