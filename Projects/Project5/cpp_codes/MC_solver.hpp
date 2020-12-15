#ifndef MC_solver_HPP
#define MC_solver_HPP
#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>
#include "Person.hpp"

using namespace std;

/**
    @brief Object holding values and member functions for running Monte Carlo Solver
*/
class MC_solver{
    public:
        MC_solver();
        void init_constants(double _a, double _b, double _c, double _d, double _dI, double _e, double _f, double _w, double _A);
        void init_population(int _N, int _S, int _I, int _R);
        void init_bulkvacc(double _f_BULK, int _bulk_stock);
        void run(double t_0, double t_n, string mode, int extra_seed);
        void write_to_file(string filename);

        double init_multiple_runs(string filename);
        void write_multiple_runs(string filename);
        void multiple_run_time(string filename, double multiple_start_time);
        void print_runtime();

        //Used for testing
        std::vector<Person> get_population();


    private:
        string mode;

        double runtime;
        double multiple_run_start_time;

        //RNG
        mt19937_64 rng;
        uniform_real_distribution<double> unif;

        ofstream ofile;
        int n_steps;
        double dt;

        double a; //Infection rate
        double b; //recovery rate 
        double c; //lose immunity rate
        double d; //natural death rate
        double dI; //death rate due to desease
        double e;   //birth rate
        double f;
        double f_BULK;
        double w;
        double A;
        int N;
        int vaccine_stock;

        std::vector<Person> population;
        std::vector<int (MC_solver::*)()> transition;

        int S_0;
        int I_0;
        int R_0;

        arma::vec state_counter;

        arma::vec S;
        arma::vec I;
        arma::vec R;
        arma::vec D;
        arma::vec DI;
        arma::vec E;
        arma::vec t;
        arma::vec Vaccinations;

        //Transition probabilities
        double P_StoI;
        double P_ItoR;
        double P_RtoS;
        double P_StoR;
        double P_BULK;
        double P_d;
        double P_dI;
        double P_e;

        //Transition functions
        int StoI();
        int ItoR();
        int RtoS();
        int SSeasonal();
        int SVaccine();
        int SBulkVaccine();

};

#endif