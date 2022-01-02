#include <vector>
#include "libODE.h"
#include "libGradient.h"

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
}

NbodiesGradientSymp::NbodiesGradientSymp(vector<double> m){
    this->m = m;
}

Array1D NbodiesGradientSymp :: operator()(Array1D y, double t){


}

NbodiesGradient::NbodiesGradient(vector<double> m){
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
}