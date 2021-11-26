#include<iostream>
#include<math.h>
#include<vector>

typedef std::vector<double> (*fun) (std::vector<double>, double);

class Solution{
    public:
    std::vector <double> U;
    std::vector <double> t;
    int nSteps;
    int nEquations;

    Solution(int nS, int nE);
    double operator () (int i, int j);
};


class Integrator{
    public:
    Solution sol;
    Integrator(fun f, std::vector<double>& y0, double t0, double tmax, int nSteps);
};

