#ifndef UNITS_H
#define UNITS_H
#include <math.h>

double M = 2.0e30;              // Massa Sole in kg
double L = 5.7e10;              // Semiasse maggiore Mercurio in m
double G = 6.6725985e-11;       // Gravitational constant
double T = sqrt(L*L*L/M/G);     // Tempo caratteristico in s
//G = 1;

#endif