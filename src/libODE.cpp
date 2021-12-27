#include "libODE.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Solution::Solution(int nSteps, int nEquations){
        this->nSteps=nSteps;
        this->nEquations=nEquations;
        this->U.resize(nSteps,nEquations);
        this->t.resize(nSteps);
}

void Solution::setIC(Array1d& y0, double t0){
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

Integrator::Integrator(Gradient& f, Array1d& y0, double t0, double tmax, int nSteps, string method){
    // integration time interval
    double dt = (tmax-t0)/nSteps; 
    int nEquations=y0.size();
    sol = Solution(nSteps, nEquations);

    // set the initial conditions
    sol.setIC(y0, t0);
    Array1d U = y0;
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

void EE(Gradient& f, Array1d U, double t, double dt){
    U = U + dt*f(U, t);
}

void RK4(Gradient& f, Array1d U, double t, double dt){
    Array1d k1, k2, k3, k4;
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

