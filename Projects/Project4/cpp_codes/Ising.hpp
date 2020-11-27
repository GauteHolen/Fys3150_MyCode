#ifndef Ising_HPP
#define Ising_HPP

#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>

using namespace std;

class Sampler 
{
public:
    Sampler();
    Sampler(int _samples, int _n_spins, bool _T_Gradient);
    void init(int _samples, int _n_spins, bool _T_Gradient);
    void sample(double _E, double _M, int _flips, int i);
    void print();
    void write_to_file(string _filename);
    void statistics(double T, int sample_start, int n_spins, int n_flips);
    void sample_E(int E);
    void T_gradient_filename(string _filename);


private:
    arma::vec E;
    arma::vec M;
    arma::vec flips;
    arma::vec Ei;
    arma::vec PE;
    int samples;
    int n_spins;

    string filename;
    ofstream ofile;

    bool T_gradient;
};






class  Ising
{
public:
    arma::mat spins;
    Ising(int _L, double _T, bool _random_spins);
    void setup(int _L, double _T, bool _random_spins);

    void update();
    void run(int mcs, int start_sampling, bool prob_dist, bool T_gradient);
    void print();
    void init_random_spins();
    Sampler sampler;



private:
    double T; //Temperature
    double E; //Energy
    double M;  //Magnetic moment
    int L;  //Length of lattice
    int n_spins; //Number of spinsnt i, int limit, int add
    int n_flips; // Number of times the spin is flipped
    int flips_cycle;
    arma::vec w;
    arma::vec avg;

    //RNG
    mt19937_64 rng;
    uniform_real_distribution<double> unif;


    bool random_spins;
    void init_total_E();
    void init_total_M();
    void init_w();
    void probability_dist();
    inline int PBC(int i, int add);
    inline double deltaE(int x, int y);
    inline int get_Energy(int x, int y);



    string filename;
    ofstream ofile;

};

#endif 