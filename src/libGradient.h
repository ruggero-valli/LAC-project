/**
 * @file libGradient.h
 * @author Ruggero Valli, Francesca Vitali
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 */

#ifndef LIBGRADIENT_H 
#define LIBGRADIENT_H

#include "libODE.h"

class testGradient : public Gradient{
    public:
    double lambda;
    testGradient(double lambda);
    Array1D operator()(Array1D y, double t);
};

class lorenzGradient : public Gradient{
    public:
    double sigma, ro, beta;
    lorenzGradient(double sigma, double ro, double beta);
    Array1D operator()(Array1D y, double t);
};

class oscillatorGradientSymp : public Gradient{
    public:
    double omega;
    oscillatorGradientSymp(double omega);
    Array1D operator()(Array1D y, double t);
};

class oscillatorGradient : public Gradient{
    public:
    double omega;
    oscillatorGradient(double omega);
    Array1D operator()(Array1D y, double t);
};

class NbodiesGradientSymp : public Gradient{
    public:
    Array1D m;

    NbodiesGradientSymp(Array1D m);
    Array1D operator()(Array1D y, double t);
};

class NbodiesGradient : public Gradient{
    public:
    Array1D m;

    NbodiesGradient(Array1D m);
    Array1D operator()(Array1D y, double t);
};

class SchwGradient : public Gradient{
    public:
    double M;
    double L;
    double eps;

    SchwGradient(Array1D r0, Array1D v0, Array1D m);
    Array1D operator()(Array1D y, double t);
};

#endif