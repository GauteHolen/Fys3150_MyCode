#ifndef MC_solver_HPP
#define MC_solver_HPP
#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>
#include "Person.hpp"

using namespace std;

class MC_solver{
    public:
        MC_solver();
        void init_constants(double _a, double _b, double _c, double _d, double _dI, double _e, double _f, double _w, double _A);
        void init_population(int _N, int _S, int _I, int _R);
        void run(double t_0, double t_n, string mode);
        void write_to_file(string filename);


    private:
        //RNG
        mt19937_64 rng;
        uniform_real_distribution<double> unif;

        ofstream ofile;
        int n_steps;

        double a; //Infection rate
        double b; //recovery rate 
        double c; //lose immunity rate
        double d; //natural death rate
        double dI; //death rate due to desease
        double e;   //birth rate
        double f;
        double w;
        double A;
        int N;

        std::vector<Person> population;
        std::vector<int (MC_solver::*)()> transition;

        int S_0;
        int I_0;
        int R_0;

        arma::vec S;
        arma::vec I;
        arma::vec R;
        arma::vec D;
        arma::vec DI;
        arma::vec E;
        arma::vec t;

        //Transition probabilities
        double P_StoI;
        double P_ItoR;
        double P_RtoS;
        double P_StoR;

        //Transition functions
        int StoI();
        int ItoR();
        int RtoS();
        int SSeasonal();
        int SVaccine();

};

#endif