#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "libODE.h"
#include "libGradient.h"

using namespace std;

void checkOrder(string& method, vector<double>& dt, vector<double>& err);
void checkOrderStandard(string& method, vector<double>& dt, vector<double>& err);
void checkOrderSymplectic(string& method, vector<double>& dt, vector<double>& err);
void toFile(string& method, vector<double>& dt, vector<double>& err, string& outpath);

int main(int argc, char *argv[]){
    string method, outpath;
    vector<double> dt, err;

    if (argc < 3){
        cout << "Arguments missing:\n";
        cout << "first argument: output_path\n";
        cout << "subsequent arguments: integration method names\n";
        exit(1);
    }

    outpath = argv[1];
    for (int i=2; i<argc; i++){
        dt.clear();
        err.clear();
        method = argv[i];
        checkOrder(method, dt, err);
        toFile(method, dt, err, outpath);
    }
}

void checkOrder(string& method, vector<double>& dt, vector<double>& err){
    if (method == "EE" || method == "RK4" || method == "RK5"){
        checkOrderStandard(method, dt, err);
    } else if (method == "SE" || method == "Verlet"){
        checkOrderSymplectic(method, dt, err);
    } else{
        cout << "Integration method " << method << " not recognized. Quitting";
        exit(1);
    }
}

void checkOrderStandard(string& method, vector<double>& dt, vector<double>& err){
    double t0=0, tmax=1, y0 = 1, lambda = -1, t;
    testGradient F(lambda);
    Array1D U0(1);
    int nSteps;
    double exact;
    double numerical;

    for (double h=0.4; h>1e-3; h*=0.7){
        U0[0] = y0;
        nSteps = (tmax-t0)/h;

        Integrator I(F, U0, t0, tmax, nSteps, method);
        t = I.sol.t(Eigen::last);
        exact = y0*exp(lambda*(t-t0));
        numerical = I.sol.U(Eigen::last,0);

        dt.push_back(h);
        err.push_back(abs(numerical-exact)/exact);
    }
}

void checkOrderSymplectic(string& method, vector<double>& dt, vector<double>& err){
    double t0=0, tmax=6, y0 = 1, omega = 1, t;
    oscillatorGradientSymp F(omega);
    Array1D U0(2);
    int nSteps;
    double exact;
    double numerical;

    for (double h=0.4; h>1e-3; h*=0.7){
        U0[0] = y0;
        U0[1] = 0;
        nSteps = (tmax-t0)/h;

        Integrator I(F, U0, t0, tmax, nSteps, method);
        t = I.sol.t(Eigen::last);
        exact = y0*cos(omega*(t-t0));
        numerical = I.sol.U(Eigen::last,0);

        dt.push_back(h);
        err.push_back(abs(numerical-exact)/exact);
    }
}

void toFile(string& method, vector<double>& dt, vector<double>& err, string& outpath){
    string fileName = outpath+method+".dat";
    ofstream myfile(fileName, ios_base::out);
    auto h = dt.begin();
    auto e = err.begin();
    while (h != dt.end()){
        myfile << *h << " " << *e << "\n";
        h++;
        e++;
    }
}