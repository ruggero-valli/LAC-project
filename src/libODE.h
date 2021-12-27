/**
 * @file libODE2.h
 * @authors Ruggero Valli, Francesca Vitali
 * @brief 
 * @version 0.1
 * @date 2021-12-26
 * 
 * 
 */

#ifndef LIBODE_H
#define LIBODE_H

#include "Eigen/Dense"
#include <string>

typedef Eigen::ArrayXd Array1d;
typedef Eigen::ArrayXXd Array2d;

/**
 * @brief the gradient of a system of ordinary differential equation.
 * 
 * This class is a functor that represents a function \f$f(y, t)\f$ such that
 * \f$y'(t) = f(y(t),t)\f$.
 * 
 */
class Gradient{
    public:
    virtual Array1d operator()(Array1d y, double t)=0;
};

/**
 * @brief the numerical solution of a Cauchy problem.
 * 
 * Contains a sequence of discrete times, and the value of the solution
 * calculated at those times.
*/
class Solution{
    public:
    int nSteps;
    int nEquations;
    Array1d t;
    Array2d U;

    /**
     * @brief Constructor of an empty Solution object
     * 
     */
    Solution(){};

    /**
     * @brief constructor of the Solution class.
     * 
     * @param nSteps the number of steps to integrate
     * @param nEquations the number of equations in the system
     * @return * Constructor 
     */
    Solution(int nSteps, int nEquations);

    /**
     * @brief set the initial conditions as the first value of the solution.
     * 
     * @param U0 the initial value of the solution
     * @param t0 the initial time
     */
    void setIC(Array1d& U0, double t0);

    // /**
    //  * @brief append the value of the current step to the solution
    //  * 
    //  * after calling this method, the solution contains a new point: the value
    //  * `u` at time `t`. The method raises an error if `t` is less or equal to
    //  * the latest time provided or if the solution already has `nStep` points.
    //  * 
    //  * @param U the value of the function at time `t`
    //  * @param t the new time
    //  */
    // void addStep(Array1d& U, double t);
    //
    // /**
    //  * @brief get the number of integration steps
    //  * 
    //  * @return the number of integration steps 
    //  */
    // int getNSteps();
    //
    //  /**
    //  * @brief get the number of equations in the system
    //  * 
    //  * @return the number of equations
    //  */
    // int getNEquations();
    //
    // /**
    //  * @brief get the array of times at which the solution is evaluated
    //  * 
    //  * @return the array of times
    //  */
    // Array1d& getT();
    //
    // /**
    //  * @brief the values of the solution at the discrete timesteps
    //  * 
    //  * the returned object is a 2d array.
    //  * The first index refers to the timestep
    //  * the second index is the equation number
    //  * 
    //  * @return the array containing the values of the solution
    //  */
    // Array2d& getU();
    
    /**
     * @brief write the solution to a MATLAB file
     * 
     * @param FileName the name of the file where the solution is to be saved
     */
    void SaveToMFile(std::string FileName);
};


/**
 * @brief integrate a system of ordinary differential equations.
 * 
 * Implements the numerical integration of the Cauchy problem
 * \f$y'(t) = f(y(t),t)\f$.
 */
class Integrator{
    public:
    Solution sol;

    /**
     * @brief Construct a new Integrator object
     * 
     * Performs the integration and saves the result into a Solution object.
     * 
     * @param f      is the gradient field of the Cauchy problem \f$f(y,t) = y'\f$
     * @param y0     array of initial conditions
     * @param t0     initial time
     * @param tmax   final time
     * @param nSteps number of integration steps
     * @param method the integration algorithm.
     * 
     * The available integration methods are:
     * - "EE":    explicit Euler (https://en.wikipedia.org/wiki/Euler_method)
     * - "RK4":   explicit Runge-Kutta of VI order (https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods#Examples) 
     * 
     */
    Integrator(Gradient& f, Array1d& y0, double t0, double tmax, 
                int nSteps, std::string method);

    // /**
    //  * @brief Get the numerical solution of the performed integration
    //  * 
    //  * @return the solution object
    //  */
    // Solution& getSolution();
};

typedef void (*integrationStep) (Gradient& f, Array1d U, double t, double dt);
void EE(Gradient& f, Array1d U, double t, double dt);
void EEs(Gradient& f, Array1d U, double t, double dt);
void RK4(Gradient& f, Array1d U, double t, double dt);
void RK4s(Gradient& f, Array1d U, double t, double dt);
#endif