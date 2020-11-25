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
    Sampler(int _samples);
    void sample(double _E, double _M, int i);
    void print();
    void write_to_file(string _filename);
    void statistics(double T, int n_spins);


private:
    arma::vec E;
    arma::vec M;
    int samples;

    string filename;
    ofstream ofile;


};






class  Ising
{
public:
    arma::mat spins;
    Ising(int _L, double _T, bool _random_spins);
    void setup(int _L, double _T, bool _random_spins);

    void update();
    void run(int mcs);
    void print();
    void init_random_spins();



private:
    double T; //Temperature
    double E; //Energy
    double M;  //Magnetic moment
    int L;  //Length of lattice
    int n_spins; //Number of spinsnt i, int limit, int add
    arma::vec w;
    arma::vec avg;

    //RNG
    mt19937_64 rng;
    uniform_real_distribution<double> unif;

    bool random_spins;
    void init_total_E();
    void init_total_M();
    void init_w();
    inline int PBC(int i, int add);
    inline double deltaE(int x, int y);



    string filename;
    ofstream ofile;

};

#endif 