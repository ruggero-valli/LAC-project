#include "libODE.h"
#include <string>
#include <fstream>
#include <iostream>
#include "libUtils.h"

using namespace std;

Solution::Solution(int nSteps, int nEquations){
        this->nSteps=nSteps;
        this->nEquations=nEquations;
        this->U.resize(nSteps,nEquations);
        this->t.resize(nSteps);
}

void Solution::setIC(Array1D& y0, double t0){
    for(int j=0; j<nEquations; j++){
        U(0, j) = y0[j];
    }
    t[0] = t0;
}

void Solution::SaveToMFile(string FileName){
    ofstream myfile(FileName, ios_base::out);
    if (myfile.is_open()){
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
        
        myfile.close();
    }
}

Integrator::Integrator(Gradient& f, Array1D& y0, double t0, double tmax, int nSteps, string method){
    // integration time interval
    double dt = (tmax-t0)/nSteps; 
    int nEquations=y0.size();
    sol = Solution(nSteps, nEquations);

    // set the initial conditions
    sol.setIC(y0, t0);
    Array1D U = y0;
    double t = t0;

    integrationStep integStep;
    if (method == "EE"){
        integStep = EE;
    } else if(method == "RK4"){
        integStep = RK4;
    } else if(method == "SE"){
        integStep = SE;
    } else if(method == "Verlet"){  
        integStep = Verlet;  
    } else if(method == "RK5"){
        integStep = RK5;    
    } else{    
        cout << "Integration method " << method << " not recognized. Quitting";
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

void EE(Gradient& f, Array1D& U, double t, double dt){
    U = U + dt*f(U, t);
}

void SE(Gradient& f, Array1D& U, double t, double dt){
    Array1D r, v;
    split(U, r, v);
    v = v + f(r,t) * dt;
    r = r + v * dt;
    join(U, r, v);
}

void Verlet(Gradient& f, Array1D& U, double t, double dt){
    Array1D r, v, a0, a1;
    split(U,r,v);
    a0=f(r,t);
    r = r + v * dt + a0 * dt * dt / 2;
    a1=f(r,t);
    v = v + (a0 + a1) * dt / 2;
    join(U, r, v);
}

void RK4(Gradient& f, Array1D& U, double t, double dt){
    Array1D k1, k2, k3, k4;
    k1.resizeLike(U);
    k2.resizeLike(U);
    k3.resizeLike(U);
    k4.resizeLike(U);

    k1 = f(U, t);
    k2 = f(U+dt/2*k1, t+dt/2);
    k3 = f(U+dt/2*k2, t+dt/2);
    k4 = f(U+dt*k3, t+dt);
    U += dt/6*(k1 + 2*k2 + 2*k3 +k4);
}

void RK5(Gradient& f, Array1D& U, double t, double dt){
    Array1D k1, k2, k3, k4, k5, k6;
    k1.resizeLike(U);
    k2.resizeLike(U);
    k3.resizeLike(U);
    k4.resizeLike(U);
    k5.resizeLike(U);
    k6.resizeLike(U);

    k1 = f(U, t) * dt;
    k2 = f(U+2./9*k1, t+2./9*dt) * dt;
    k3 = f(U+1./12*k1+1./4*k2, t+1./3*dt)*dt;
    k4 = f(U+69./128*k1-243./128*k2+135./64*k3, t+3./4*dt)*dt;
    k5 = f(U-17./12*k1+27./4*k2-27./5*k3+16./15*k4, t+dt) * dt;
    k6 = f(U+65./432*k1-5./16*k2+13./16*k3+4./27*k4+5./144*k5, t+5./6*dt) *dt;

    U+= 47./450*k1+12./25*k3+32./225*k4+1./30*k5+6./25*k6;
}

