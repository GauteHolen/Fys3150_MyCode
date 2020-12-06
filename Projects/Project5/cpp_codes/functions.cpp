#include "functions.hpp"

functions::functions(double _a, double _b, double _c, int _N){
    init(_a,_b,_c,_N);
}


void functions::init(double _a, double _b, double _c, int _N){
    a=_a;
    b=_b;
    c=_c;
    N=_N;
}


double functions::susceptible(double S, double I, double t){
    return c*(N-S-I)-((a*S*I)/(double) N);
}

double functions::infected(double S, double I, double t){
    return ((a*S*I)/(double) N) - b*I;
}