#include <iostream>
#include <string>
#include "libODE.h"

using namespace std;

class testGradient : public Gradient{
    private:
    double omega;
    public:
    testGradient(double omega){
        this->omega = omega;
    }
    Array1D operator()(Array1D y, double t){
        return -omega*omega*y;
    }
};

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

    testGradient F(omega);
    Array1D y0(2);
    y0[0] = 1;
    y0[1] = 0;
    
    Integrator I(F, y0, t0, tmax, nSteps, (string)"SE");

    I.sol.SaveToMFile(fileName);
    }