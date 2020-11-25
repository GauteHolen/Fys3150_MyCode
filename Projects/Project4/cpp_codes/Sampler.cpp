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

void Sampler::statistics(double T, int n_spins){

    double Evar = arma::var(E);
    double Mvar = arma::var(M);

    double Eavg = arma::sum(E)/samples;
    double Mavg = arma::sum(M)/samples;

    double Eavgspin = Eavg/((double) n_spins);
    double Mavgspin = Mavg/((double) n_spins);

    double CV = Evar/(T*T*n_spins);
    double X = Mvar/(T*T*n_spins);

    string statfilename = "stat_"+to_string(n_spins)+"spins_T_"+to_string(T);
    ofile.open("./Projects/Project4/results/"+statfilename+".txt");
    ofile<<"===== S T A T I S T I CS ======"<<endl;
    ofile<<"Number of spins = "<<n_spins<<endl;
    ofile<<"Temperature = "<<T<<endl;
    ofile<<"Monte Carlo Cycles mcs = "<<samples<<endl;
    ofile<<"-------------------------------"<<endl;
    ofile<<"Total mean E = "<<Eavg<<endl;
    ofile<<"Total mean M = "<<Mavg<<endl;
    ofile<<"-------------------------------"<<endl;
    ofile<<"mean E per spin = "<<Eavgspin<<endl;
    ofile<<"mean M per spin = "<<Mavgspin<<endl;
    ofile<<"Specific Heat CV per spin = "<<CV<<endl;
    ofile<<"Susceptebility X per spin = "<<X<<endl;
    ofile.close();
}

void Sampler::write_to_file(string _filename){
    filename = _filename;
    ofile.open("./Projects/Project4/results/"+filename+".txt");
    ofile<<"E_i"<<"\t"<<"M_i"<<endl;
    for (int i = 0; i < samples; i++)
    {
        ofile<<E(i)<<"\t"<<M(i)<<endl;
    }
    

    ofile.close();
}