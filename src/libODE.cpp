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

Integrator::Integrator(Grad f, ArrayXd& y0, double t0, double tmax, int nSteps, string method){
    /*
    ***************************************************************************
     * Constructor of the Integrator class. Performs the integration and
     * saves the result into a Solution object.
     * ************************************************************************
     * Arguments:
     * * f:         f(y,t) = y' is the gradient field of the solution
     * * y0:        array of initial conditions
     * * t0:        initial time
     * * tmax:      final time
     * * nSteps:    number of integration steps
     * * method:    the integration algorithm. It can assume the values:
     * * * "EE":        explicit Euler (https://en.wikipedia.org/wiki/Euler_method)
     * * * "Heun":      Heun's method  (https://en.wikipedia.org/wiki/Heun%27s_method) 
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

    integrationStep integStep;
    if (method == "EE"){
        integStep = EE;
    }
    else if(method == "RK4"){
        integStep = RK4;
    }else{
        cout << "Integration method not recognized. Quitting";
        exit(1);
    }

    // integration loop
    for(int i=1;i<nSteps; i++){
        t = t0 + i*dt;
        sol.t[i] = t;
        integStep(f,U,t,dt);
        for(int j=0; j<nEquations; j++){
            sol.U(i,j) = U[j];
        }   
    }
}

void EE(Grad f, ArrayXd& U, double t, double dt){
    U = U + dt*f(U, t);
}

void RK4(Grad f, ArrayXd& U, double t, double dt){
    ArrayXd k1, k2, k3, k4;
    k1.resizeLike(U);
    k2.resizeLike(U);
    k3.resizeLike(U);
    k4.resizeLike(U);

    k1 = f(U, t);
    k2 = f(U+dt/2*k1, t+dt/2);
    k3 = f(U+dt/2*k2, t+dt/2);
    k4 = f(U+dt*k3, t+dt);
    U += dt/6*(k1+2*k2 + 2*k3 +k4);
}

