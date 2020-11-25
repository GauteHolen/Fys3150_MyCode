#include "Ising.hpp"
#include<random>
#include<ctime>



inline int Ising::PBC(int i, int add){
    return (i + L + add) % (L);
}
inline double Ising::deltaE(int x, int y){
    return 2*spins(x,y)*(spins(x,PBC(y,1))+spins(x,PBC(y,-1))+spins(PBC(x,1),y)+spins(PBC(x,-1),y));
}


Ising::Ising(int _L, double _T, bool _random_spins){
    setup(_L, _T, _random_spins);
}

void Ising::setup(int _L, double _T, bool _random_spins){
    T = _T;
    L = _L;
    n_spins=L*L;

    spins=arma::mat(L, L, arma::fill::ones);
    if(_random_spins){
        init_random_spins();
    }
    
    init_total_E();
    init_total_M();
    init_w();

    /* initialize rng seed: */
    int seed = time(0);
    rng.seed(seed);
}

void Ising::run(int mcs){

    Sampler sampler(mcs);
    for (int i = 0; i < mcs; i++)
    {
        sampler.sample(E,M,i);
        update();
    }
    sampler.print();
    sampler.write_to_file("test");
    sampler.statistics(T,n_spins);
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