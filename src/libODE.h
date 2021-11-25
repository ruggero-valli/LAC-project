#include<iostream>
#include<math.h>
using namespace std;

class Solution{
private:

public:
vector <double> U;
vector <double> t;

Solution(int nSteps, int nEquations){

U.resize(nSteps*nEquations);
t.resize(nSteps);

}

}


class Integrator{
private:

public:

Solution sol;

template <class Grad>;

double operator () (int i, int j){
    return U[i*nEquations+j]


}

Integrator(Grad& f, vector <double> y0, double t0, double tmax, int nSteps, string method){

double dt = (tmax-t0)/N;
int nEquations=y0.size();
sol= Solution(nSteps+1, nEquations);

}





}