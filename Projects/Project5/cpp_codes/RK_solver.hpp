#ifndef RK_solver_HPP
#define RK_solver_HPP
#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>
#include "functions.hpp"

using namespace std;

/**
    @brief Object holding values and member functions for running Runge-Kutta Solver
*/
class RK_solver {



    public:

        //typedef double dtfunc(double S, double I, double t);

        RK_solver();
        void solve(double t_0, double t_n, int _n_steps, 
            double (RK_solver::*fS) (double,double,double,double), 
            double (RK_solver::*fI) (double,double,double,double), 
            double (RK_solver::*fR) (double,double,double,double));

        void init_constants(double _a, double _b, double _c, double _d, double _dI, double _e, double _f, double _w, double _A);
        void init_population(int _N, int _S, int _I, int _R);


        double susceptible(double S, double I, double R, double t);
        double infected(double S, double I, double R, double t);
        double recovering(double S, double I, double R, double t);
        //Vital
        double vitalS(double S, double I, double R, double t);
        double vitalI(double S, double I, double R, double t);
        double vitalR(double S, double I, double R, double t);
        //Vaccine
        double vaccineS(double S, double I, double R, double t);
        double vaccineI(double S, double I, double R, double t);
        double vaccineR(double S, double I, double R, double t);
        //Seasonal
        double seasonalS(double S, double I, double R, double t);
        double seasonalI(double S, double I, double R, double t);
        double seasonalR(double S, double I, double R, double t);

        //Include all cases
        double allS(double S, double I, double R, double t);
        double allI(double S, double I, double R, double t);
        double allR(double S, double I, double R, double t);
        

        void write_to_file(string filename);
        void expected_values();



    private:

        ofstream ofile;

        double a;
        double b;
        double c;
        double d;
        double dI;
        double e;
        double f;
        double w;
        double A;
        double N;

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
        double Rk1;
        double Rk2;
        double Rk3;
        double Rk4;

        
};

#endif