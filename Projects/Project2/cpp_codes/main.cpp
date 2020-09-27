#include "eigenvaluesolver.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>
#include <iostream>

using namespace arma;
int main(int argc, char const *argv[]) {

    std::cout<<"hello"<<endl;

    mat A;

    int n = 5;

    utils util;

    A=util.get_simple_A(0.0,1.0,n);

    jacobi_method solver;
    solver.init(A,n);
    solver.solve();


    vec eigval;
    mat eigvec;

    A=util.get_simple_A(0.0,1.0,n);
    cout<<"arma eigenvectors: "<<endl;
    eig_sym(eigval, eigvec, A);
    eigvec.print();
}