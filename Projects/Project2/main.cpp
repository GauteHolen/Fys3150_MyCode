#include "./cpp_codes/eigenvaluesolver.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>
#include <iostream>
#include <iomanip>

using namespace arma;


void print_eigen(vec jacobi, vec arma, vec analytic){

    cout<<setw(15)<<"jacobi_method"<<setw(15)<<"arma"<<setw(15)<<"analytic"<<setw(15)<<"n"<<endl;
    for (int i = 0; i < 5; i++)
    {
        cout<<setw(15)<<jacobi(i)<<setw(15)<<arma(i)<<setw(15)<<analytic(i)<<setw(15)<<i+1<<endl;
    }  
}


int main(int argc, char const *argv[]) {

    int n = atoi(argv[1]);
    string algorithm = string(argv[2]);
    double p_max = atof(argv[3]);
    string filename = algorithm + "_N_" + to_string(n) + "_pmax_" + to_string(p_max);


    mat A;

    vec analytical_eigval(n);
    analytical_eigval.zeros();

    mat_utils util;
    util.init(0.0,p_max,n,algorithm);

    if(algorithm=="simple"){
        analytical_eigval = util.get_analytical_eigval_simple();
        A=util.get_simple_A();
    }

    if(algorithm=="QDsingle"){
        A=util.get_single_electron_V();
    }

    if(algorithm=="QDdouble"){
        double w_r = atof(argv[4]);
        A=util.get_double_electron_V(w_r);
        filename+="_wr_" + to_string(w_r);
        
    }

    jacobi_method solver;
    solver.init(A,n,algorithm);
    solver.solve();
    filename+=".txt";
    util.write_to_file(filename);
    solver.write_to_file(filename);

}

