#include "Ising.hpp"

Sampler::Sampler(int _samples, int _n_spins, bool _T_Gradient){
    init(_samples, _n_spins, _T_Gradient);
}

Sampler::Sampler(){

}

void Sampler::init(int _samples, int _n_spins, bool _T_Gradient){
    T_gradient = _T_Gradient;
    n_spins = _n_spins;
    samples = _samples;
    E=arma::vec(samples);
    M=arma::vec(samples);
    flips=arma::vec(samples);

    //Initializing possible enrgies
    Ei=arma::vec(9,arma::fill::zeros);
}

void Sampler::sample(double _E, double _M, int _flips, int i){
    E(i) = _E;
    M(i) = _M;
    flips(i) = _flips;
}

void Sampler::sample_E(int E){
    
    Ei(E+4)+=1;
    //cout<<PE(E_index)<<endl;

}



void Sampler::print(){
    double EE = arma::sum(E)/samples;
    double EM = arma::sum(M)/samples;
    cout<<"E[E] = "<<EE<<endl;
    cout<<"E[M] = "<<EM<<endl;

}

void Sampler::statistics(double T, int sample_start, int n_spins, int n_flips){

    double Evar = arma::var(E);
    double Mvar = arma::var(M);

    double Eavg = arma::sum(E)/samples;
    double Mavg = arma::sum(M)/samples;

    double Eavgspin = Eavg/((double) n_spins);
    double Mavgspin = Mavg/((double) n_spins);

    double CV = Evar/(T*T*n_spins);
    double X = Mvar/(T*T*n_spins);

    if(T_gradient==false){    
        cout<<"Creating statistics file"<<endl;

        string statfilename = "stat_"+to_string(n_spins)+"spins_T_"+to_string(T)+"_mcs_"+to_string(samples+sample_start)+"_ss_"+to_string(sample_start);
        ofile.open("./Projects/Project4/results/"+statfilename+".txt");
        ofile<<"===== S T A T I S T I CS ======"<<endl;
        ofile<<"Number of spins = "<<n_spins<<endl;
        ofile<<"Temperature = "<<T<<endl;
        ofile<<"Started sampling after Monte Carlo Cycle mcs = "<<sample_start<<endl;
        ofile<<"Toral Monte Carlo Cycles mcs = "<<samples+sample_start<<endl;
        ofile<<"Accepted new configurations = "<<n_flips<<endl;
        ofile<<"-------------------------------"<<endl;
        ofile<<"Total mean E = "<<Eavg<<endl;
        ofile<<"Total mean M = "<<Mavg<<endl;
        ofile<<"-------------------------------"<<endl;
        ofile<<"mean E per spin = "<<Eavgspin<<endl;
        ofile<<"variance E per spin = "<<Evar/n_spins<<endl;
        ofile<<"mean M per spin = "<<Mavgspin<<endl;
        ofile<<"variance M per spin = "<<Mvar/n_spins<<endl;
        ofile<<"Specific Heat CV per spin = "<<CV<<endl;
        ofile<<"Susceptebility X per spin = "<<X<<endl;

        if(arma::sum(Ei)>0){
            ofile<<"-------------------------------"<<endl;
            ofile<<"Probability distribution for energies:"<<endl;
            ofile<<"P(-4) = "<<Ei(0)/samples/n_spins<<endl;
            ofile<<"P(-2) = "<<Ei(2)/samples/n_spins<<endl;
            ofile<<"P(0) = "<<Ei(4)/samples/n_spins<<endl;
            ofile<<"P(2) = "<<Ei(6)/samples/n_spins<<endl;
            ofile<<"P(4) = "<<Ei(8)/samples/n_spins<<endl;
        }

        ofile.close();
    }
    else
    {
        ofile.open(filename,std::ios::app);
        ofile<<T<<"\t"<<Eavgspin<<"\t"<<Mavgspin<<"\t"<<CV<<"\t"<<X<<endl;
        ofile.close();
    }
    
}

void Sampler::T_gradient_filename(string _filename){
    filename = _filename;
}

void Sampler::write_to_file(string _filename){
    cout<<"Creating file with E, M and A(t) vectors..."<<endl;
    filename = _filename;
    ofile.open("./Projects/Project4/results/"+filename+".txt");
    ofile<<"E_i"<<"\t"<<"M_i"<<"\t"<<"A(t)"<<endl;
    for (int i = 0; i < samples; i++)
    {
        ofile<<E(i)/n_spins<<"\t"<<M(i)/n_spins<<"\t"<<flips(i)/n_spins<<endl;
    }
    

    ofile.close();
}