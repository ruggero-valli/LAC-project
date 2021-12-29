/**
 * @file libODE.h
 * @authors Ruggero Valli, Francesca Vitali
 * @brief 
 * @version 0.2
 * @date 2021-12-26
 * 
 * 
 */

#ifndef LIBODE_H
#define LIBODE_H

#include "Eigen/Dense"
#include <string>

typedef Eigen::ArrayXd Array1D;
typedef Eigen::ArrayXXd Array2D;

/**
 * @brief the gradient of a system of ordinary differential equation.
 * 
 * This class is a functor that represents a function \f$f(y, t)\f$ such that
 * \f$y'(t) = f(y(t),t)\f$.
 * 
 */
class Gradient{
    public:
    virtual Array1D operator()(Array1D y, double t)=0;
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
    Array1D t;
    Array2D U;

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
    void setIC(Array1D& U0, double t0);
    
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
     * - "EE":     explicit Euler
     * - "SE":     symplectic Euler
     * - "RK4":    explicit Runge-Kutta of IV order (https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods#Examples)
     * - "RK5":    explicit Runge-Kutta of V order
     * - "Verlet": velocity Verlet's method (https://en.wikipedia.org/wiki/Verlet_integration#Velocity_Verlet)
     * 
     */
    Integrator(Gradient& f, Array1D& y0, double t0, double tmax, 
                int nSteps, std::string method);
};

/**
 * @brief splits the array in half.
 * 
 * The array `U` is split in two equal-length parts. The first half is copied
 * into the array `r`, the second one into the array `v`.
 * 
 * @param[in] U the array to be split
 * @param[out] r the first half of the array
 * @param[out] v the second half of the array
 */
void split(Array1D& U, Array1D& r, Array1D& v);

/**
 * @brief concatenates two arrays into one.
 * 
 * The array `r` and the array `v` are concatenated into the array `U`.
 * 
 * @param[out] U the resulting array
 * @param[in] r the first half of the array
 * @param[in] v the second half of the array
 */
void join(Array1D& U, Array1D& r, Array1D& v);

/**
 * @brief a template for the integration step functions
 * 
 */
typedef void (*integrationStep) (Gradient& f, Array1D& U, double t, double dt);

/**
 * @brief Performs one integration step using the Explicit Euler method.
 * 
 * The Explicit Euler method is the simplest integration method. First order
 * accuracy. The integration step is:
 * \f[
 * U_{i+1} = U_i + f(U_i, t) dt
 * \f]
 * Wikipedia: https://en.wikipedia.org/wiki/Euler_method
 * 
 * @param f is the gradient of the cauchy problem \f$y'=f(y,t)\f$
 * @param U is an array that contains the solution vector at time `t`
 * @param t is the time
 * @param dt is the integration timestep
 */
void EE(Gradient& f, Array1D& U, double t, double dt);

/**
 * @brief Performs one integration step using the Symplectic Euler method.
 * 
 * The Symplectic Euler method is a symplectic first order method.
 * It is meant to solve the symplectic cauchy problem
 * \f[
 * \dot{r} = v
 * \dot{v} = f(r,t)
 * \f]
 * The integration step of the method is:
 * \f[
 * v_{i+1} = v_i + f(r_i, t) dt
 * r_{i+1} = r_i + v_{i+1} dt
 * \f]
 * Wikipedia: https://en.wikipedia.org/wiki/Semi-implicit_Euler_method
 * 
 * @param f is the acceleration
 * @param U is an array that contains the solution vector at time `t`
 * @param t is the time
 * @param dt is the integration timestep
 * 
 * If 2N is the number of first order equations in the problem, `U` is an array
 * of length 2N. The first N elements correspond to the position variables.
 * The elements from `N+1` to `2N-1` correspond to the velocity variables, such
 * that for each i, U[N+i] is the velocity associated with the position stored
 * at U[i].
 */
void SE(Gradient& f, Array1D& U, double t, double dt);
void RK4(Gradient& f, Array1D& U, double t, double dt);
void RK5(Gradient& f, Array1D& U, double t, double dt);
void Verlet(Gradient& f, Array1D& U, double t, double dt);
#endif