#include <iostream>
#include <string>
#include "libODE.h"
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

ArrayXd F (const ArrayXd& y, double t) {return (-y);} 

int main(){

    double t0=0, tmax = 1;
    int nSteps = 10;
    ArrayXd y0(1);
    y0 << 1;

    Integrator I(F, y0, t0, tmax, nSteps, (string)"EE");

    string FileName;
    cin >> FileName;
    I.sol.SaveToMFile(FileName);
    }