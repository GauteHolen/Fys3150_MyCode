#include "eigenvaluesolver.hpp"


mat utils::get_simple_A(double p_min, double p_max, int n){

    mat A(n,n);
    double h = (p_max-p_min)/n;
    double a = (double) -1/(h*h);
    double d = (double) 2/(h*h);

    A(0,0)=d; A(0,1)=a;
    for(int i = 1; i<n-1; i++){
        A(i,i)=d;
        A(i,i-1)=a;
        A(i,i+1)=a;
    }
    A(n-1,n-1)=d;
    A(n-1,n-2)=a;

    return A;
}