#include <iostream>
#include <string>
#include "libODE.h"

using namespace std;

class lorenzGradient : public Gradient{
    public:
    Array1D operator()(Array1D y, double t){
    Array1D f;
    f.resizeLike(y);
    double sigma=10;
    double ro=28;
    double beta=8/3;
    f(0)=sigma*(y(1)-y(0));
    f(1)=ro*y(1) - y(1)*y(2) - y(1);
    f(2)=y(0)*y(1) -beta*y(2);
    return f;
    }
};

int main(int argc, char *argv[]){

    double t0=0, tmax = 1000;
    int nSteps = 1000000;
    lorenzGradient F;
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