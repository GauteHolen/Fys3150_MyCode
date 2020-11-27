#include "Ising.hpp"
#include<random>
#include<ctime>



inline int Ising::PBC(int i, int add){
    return (i + L + add) % (L);
}
inline double Ising::deltaE(int x, int y){
    return 2*spins(x,y)*(spins(x,PBC(y,1))+spins(x,PBC(y,-1))+spins(PBC(x,1),y)+spins(PBC(x,-1),y));
}
inline int Ising::get_Energy(int x, int y){
    return -(int) spins(x,y)*(spins(PBC(y,-1),x)+spins(y,PBC(x,-1)));
}
void Ising::probability_dist(){
    int E;
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            E = get_Energy(x,y);
            sampler.sample_E(E);
        }
        
    }
}


Ising::Ising(int _L, double _T, bool _random_spins){
    setup(_L, _T, _random_spins);
}

void Ising::setup(int _L, double _T, bool _random_spins){
    random_spins=_random_spins;
    T = _T;
    L = _L;
    n_spins=L*L;

    spins=arma::mat(L, L, arma::fill::ones);
    if(random_spins){
        init_random_spins();
    }
    
    init_total_E();
    init_total_M();
    init_w();

    /* initialize rng seed: */
    int seed = time(0);
    rng.seed(seed);
}

void Ising::run(int mcs, int start_sampling, bool prob_dist, bool T_gradient){
    n_flips = 0;
    sampler.init(mcs-start_sampling,n_spins,T_gradient);
    for (int i = 0; i < start_sampling; i++)
    {
        update();
    }

    if(prob_dist==true){
        for (int i = 0; i < mcs-start_sampling; i++)
        {
            sampler.sample(E,M,i);
            probability_dist();
            update();
        }
    }

    else{
        for (int i = 0; i < mcs-start_sampling; i++)
        {
            sampler.sample(E,M,i);
            update();
        }
    }

    if(T_gradient==false){
        sampler.write_to_file("EM_rng_"+to_string(random_spins)+"_mcs_"+to_string(mcs)+"_L_"+to_string(L)+"_T_"+to_string(T));
        sampler.statistics(T,n_spins, n_flips);
    }
    else
    {
        sampler.statistics(T,n_spins, n_flips);
    }
    
}


void Ising::update(){
    // loop over same number of updates as there are spins
    int x;
    int y;
    double dE;
    double spin;
    for (int i = 0; i < n_spins; i++)
    {
        x=(int) (unif(rng)*((double)L));
        y=(int) (unif(rng)*((double)L));
        //cout<<"x = "<<x<<" | y = "<<y<<endl;
        dE=deltaE(x,y);
        if(unif(rng) <= w(dE+8)){
            spin = spins(x,y);
            spins(x,y)=spin*(-1);
            M+= 2*spins(x,y);
            E += dE;
            n_flips++;

        }
    }
    
    
}

void Ising::print(){
    cout<<"E = "<<E<<endl;
    cout<<"M = "<<M<<endl;
    spins.print();
}



void Ising::init_total_E(){
    E=0;
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            E-= (double) spins(x,y)*(spins(PBC(y,-1),x)+spins(y,PBC(x,-1)));
        }
        
    }
    


}
void Ising::init_total_M(){
    M=0;
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            M+= (double) spins(x,y);
        }
        
    }
}

void Ising::init_w(){
    w = arma::vec(17);
    for( int de =-8; de <= 8; de++) w(de+8) = 0;
    for( int de =-8; de <= 8; de+=4) w(de+8) = exp(-de/T);
}

void Ising::init_random_spins(){
    for (int y = 0; y < L; y++)
    {
        for (int x = 0; x < L; x++)
        {
            if(unif(rng)<0.5){
                spins(x,y)=-1;
            }
        }
        
    }
}