#ifndef LIBODE_H
#define LIBODE_H
#include "Eigen/Dense"

typedef Eigen::ArrayXd (*Grad) (Eigen::ArrayXd& y, double t );

class Solution{
    /*
    **************************************************************************
     * Represents the numerical solution of a Cauchy problem.
     * Contains a sequence of discrete times, and the value of the solution
     * calculated at those times.
    **************************************************************************
    */
    public:

    // The number of discrete time points
    int nSteps;
    // The number of equations of the problem
    int nEquations;
    // The solution array with shape (nSteps, nEquations)
    Eigen::ArrayXXd U;
    // The time array
    Eigen::ArrayXd  t;

    Solution(int nS, int nE);
    Solution(){}; // Default constructor. Seems like C++ needs it or it won't compile.
    void set_IC(Eigen::ArrayXd& y0, double t0);

};


class Integrator{
    /*
    **************************************************************************
     * Implements the numerical integration of the Cauchy problem
     * y'(t) = f(y(t),t)
     * with initial conditions
     * y(t=t0) = y0
     * between times t0 and tmax.
    **************************************************************************
    */
    public:

    Solution sol;

    Integrator(Grad f, Eigen::ArrayXd& y0, double t0, double tmax, int nSteps);
};

#endif