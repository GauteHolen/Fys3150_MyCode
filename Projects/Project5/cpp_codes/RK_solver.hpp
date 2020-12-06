#ifndef RK_solver_HPP
#define RK_solver_HPP
#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>
#include "functions.hpp"

using namespace std;

class RK_solver {



    public:

        //typedef double dtfunc(double S, double I, double t);

        RK_solver();
        void solve(double t_0, double t_n, int _n_steps, double (RK_solver::*fS) (double,double,double), double (RK_solver::*fI) (double,double,double));
        void init_constants(double _a, double _b, double _c);
        void init_population(int _N, int _S, int _I, int _R);
        double susceptible(double S, double I, double t);
        double infected(double S, double I, double t);
        void write_to_file(string filename);
        void expected_values();



    private:

        ofstream ofile;

        double a;
        double b;
        double c;
        int N;

        int n_steps;
        double h;
        double t_0;
        double t_n;

        double S_0;
        double I_0;
        double R_0;
        arma::vec S;
        arma::vec I;
        arma::vec R;
        arma::vec t;
        double ES;
        double EI;
        double ER;



        double Sk1;
        double Sk2;
        double Sk3;
        double Sk4;
        double Ik1;
        double Ik2;
        double Ik3;
        double Ik4;
        
};

#endif