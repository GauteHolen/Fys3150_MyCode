#include "Ising.hpp"

Sampler::Sampler(int _samples){
    samples = _samples;
     E=arma::vec(samples);
     M=arma::vec(samples);
}

void Sampler::sample(double _E, double _M, int i){
    E(i) = _E;
    M(i) = _M;
}

void Sampler::print(){
    double EE = arma::sum(E)/samples;
    double EM = arma::sum(M)/samples;
    cout<<"E[E] = "<<EE<<endl;
    cout<<"E[M] = "<<EM<<endl;
}