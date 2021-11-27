#include "libODE.h"
#include "Eigen/Dense"
#include <string>
#include <fstream>
#include <iostream>

using namespace Eigen;
using namespace std;

Solution::Solution(int nS, int nE){
    /*
    ***************************************************************************
     * Constructor of the Solution class
    ***************************************************************************
    */
        nSteps=nS;
        nEquations=nE;
        U.resize(nSteps,nEquations);
        t.resize(nSteps);
}

void Solution::setIC(ArrayXd& y0, double t0){
    /*
    ***************************************************************************
     * Fill the first positions of the arrays with the initial conditions
    ***************************************************************************
    */
    for(int j=0; j<nEquations; j++){
        U(0, j) = y0[j];
    }
    t[0] = t0;
}

void Solution::SaveToMFile(string FileName){
    ofstream myfile(FileName, ios_base::out);
    myfile << "U=[ " << '\n';
    for(int i=0; i<nSteps; i++){
        for(int j=0; j<nEquations; j++){
           myfile << U(i,j) << " " ;
        }
        myfile << '\n';
    }
    myfile << "];" << '\n';
    myfile << "t=[ " << '\n';
    for (int i=0; i<nSteps; i++){
        myfile << t[i] << '\n';
    }
    myfile << "];" << '\n';
}

Integrator::Integrator(Grad f, ArrayXd& y0, double t0, double tmax, int nSteps){
    /*
    ***************************************************************************
     * Constructor of the Integrator class. Performs the integration and
     * saves the result into a Solution object
    ***************************************************************************
    */
    // integration time interval
    double dt = (tmax-t0)/nSteps; 
    int nEquations=y0.size();
    sol = Solution(nSteps, nEquations);

    // set the initial conditions
    sol.setIC(y0, t0);
    ArrayXd U = y0;
    double t = t0;

    // integration loop
    for(int i=1;i<nSteps; i++){
        t = t0 + i*dt;
        sol.t[i] = t;
        U = U + dt*f(U, t);
        for(int j=0; j<nEquations; j++){
            sol.U(i,j) = U[j];
        }   
    }
}
