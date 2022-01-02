#include <math.h>
#include "Eigen/Dense"
#include "libODE.h"
#include "libGradient.h"
//#include "libUnits.h"

using namespace Eigen;
using namespace std;

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
    Array2D r = y.matrix().reshaped(N, 3).array();
    Array1D dij, d;
    Array1D dydt;
    Array2D dvdt = Array2D :: Zero(N, 3);
    double d2;
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i; j++){
            dij = r(j, all) - r(i, all);
            d2 = dij(0)*dij(0) + dij(1)*dij(1) + dij(2)*dij(2);
            d = dij / pow(d2, 3./2);
            dvdt(i, all) += m(j)*d;
            dvdt(j, all) -= m(i)*d;
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