#include "libGradient.h"
#include <iostream>
#include <math.h>
#include "Eigen/Dense"
#include "libUtils.h"
#include "libUnits.h"

using namespace std;
using namespace Eigen;


testGradient :: testGradient(double lambda){
    this->lambda = lambda;
}

Array1D testGradient :: operator()(Array1D y, double t){
    return lambda*y;
}

lorenzGradient :: lorenzGradient(double sigma, double ro, double beta){
    this->sigma = sigma;
    this->ro    = ro;
    this->beta  = beta;
}

Array1D lorenzGradient :: operator()(Array1D y, double t){
    Array1D f;
    f.resizeLike(y);
    double sigma=10;
    double ro=28;
    double beta=8./3;
    f(0)=sigma*(y(1)-y(0));
    f(1)=ro*y(1) - y(1)*y(2) - y(1);
    f(2)=y(0)*y(1) -beta*y(2);
    return f;
}

oscillatorGradientSymp :: oscillatorGradientSymp(double omega){
    this->omega = omega;
}

Array1D oscillatorGradientSymp :: operator()(Array1D y, double t){
    return -omega*omega*y;
}

oscillatorGradient :: oscillatorGradient(double omega){
    this->omega = omega;
}

Array1D oscillatorGradient :: operator()(Array1D y, double t){
    Array1D drdt, dvdt, r, v;
    Array1D dydt;
    oscillatorGradientSymp acc(this->omega);
    split(y, r, v);
    drdt = v;
    dvdt = acc(r,t);
    join(dydt, drdt, dvdt);

    return dydt;
}

NbodiesGradientSymp::NbodiesGradientSymp(Array1D m){
    this->m = m;
}

Array1D NbodiesGradientSymp :: operator()(Array1D y, double t){
    int N = y.size()/3;
    Array2D r = y.matrix().reshaped(3, N).array();
    Array1D dij, d;
    Array1D dydt;
    Array2D dvdt = Array2D :: Zero(3, N);
    double d2;
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i; j++){
            dij = r(all, j) - r(all, i);
            d2 = dij(0)*dij(0) + dij(1)*dij(1) + dij(2)*dij(2);
            d = dij * pow(d2, -3./2);
            dvdt(all, i) += m(j)*d;
            dvdt(all, j) -= m(i)*d;
        }
    }
    dydt = dvdt.matrix().reshaped(3*N, 1).array();
    return dydt;
}

NbodiesGradient::NbodiesGradient(Array1D m){
    this->m = m;
}

Array1D NbodiesGradient :: operator()(Array1D y, double t){
    Array1D drdt, dvdt, r, v;
    Array1D dydt;
    NbodiesGradientSymp acc(m);
    split(y, r, v);
    drdt = v;
    dvdt = acc(r,t);
    join(dydt, drdt, dvdt);

    return dydt;
}

SchwGradient :: SchwGradient(Array1D r0, Array1D v0, double m){
    double arg1 = r0(1)*v0(2) - r0(2)*v0(1);
    double arg2 = r0(2)*v0(0) - r0(0)*v0(2);
    double arg3 = r0(0)*v0(1) - r0(1)*v0(0);
    double v = sqrt(v0(0)*v0(0)+v0(1)*v0(1)+v0(2)*v0(2));

    this->L = sqrt(arg1*arg1+arg2*arg2+arg3*arg3);
    //this->eps = v*v/2;
    this->eps = 10*v*v;
    this->m = m;
}

Array1D SchwGradient :: operator()(Array1D y, double t){
    Array1D f;
    f.resizeLike(y);

    double drdt, dphidt, dttdt;
    Array1D dydt;
    double M = units::G*m/(units::c*units::c);
    double r;
    r = y(2);
    dphidt = L/(r*r);
    dttdt = eps/(1-(2*M/r));
    drdt = eps*eps - (1+(L*L/(r*r)))*(1-(2*M/r));

    f(0) = dphidt;
    f(1) = dttdt;
    f(2) = drdt;
    cout << L << ' ' << M <<  ' ' << eps << '\n';
    return f;
}


