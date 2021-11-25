#include<iostream>
#include<math.h>
#include<vector>

using namespace std;

class Solution{
    public:
    vector <double> U;
    vector <double> t;
    int nSteps;
    int nEquations;

    Solution(int nS, int nE){
        nSteps=nS;
        nEquations=nE;
        U.resize(nSteps*nEquations);
        t.resize(nSteps);
    }

    double operator () (int i, int j){
        return U[i*nEquations + j];
    }

};


class Integrator{
    public:
    Solution sol;

    template <class Grad>
    Integrator(Grad& f, vector<double>& y0, double t0, double tmax, int nSteps){
        double dt = (tmax-t0)/nSteps; 
        int nEquations=y0.size();
        sol = Solution(nSteps+1, nEquations);

        vector<double>U = y0;
        for(int j=0; j<nEquations; j++){
            sol(0, j) = y0[j];
        }
        sol.t[0] = t0;
        double t = t0;

        for(int i=1;i<=nSteps; i++){
            t = t0 + i*dt;
            sol.t[i] = t;
            U = U + dt*f(U, t);
            for(int j=0; j<nEquations; j++){
                sol(i,j) = U[j];
            }   
        }
    }
};

int main(){}