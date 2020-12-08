#include "MC_solver.hpp"


MC_solver::MC_solver(){

}


void MC_solver::init_constants(double _a, double _b, double _c){
    a=_a;
    b=_b;
    c=_c;
}

void MC_solver::write_to_file(string filename){
    ofile.open("./Projects/Project5/results/MC_solver_"+filename+".txt");
    ofile<<"S\tI\tR\tt"<<endl;
    for (int i = 0; i < n_steps; i++)
    {
        ofile<<S(i)<<"\t"<<I(i)<<"\t"<<R(i)<<"\t"<<t(i)<<endl;
    }
    ofile.close();
}

void MC_solver::init_population(int _N, int _S, int _I, int _R){
    N = _N;

    S_0 = _S;
    I_0 = _I;
    R_0 = _R;


    for (int i = 0; i < S_0; i++)
    {
        Person person(0);
        population.push_back(person);
    }
        for (int i = 0; i < I_0; i++)
    {
        Person person(1);
        population.push_back(person);
    }
        for (int i = 0; i < R_0; i++)
    {
        Person person(2);
        population.push_back(person);
    }
}

void MC_solver::run(double t_0, double t_n,string mode){
    /* initialize rng seed: */
    int seed = time(0);
    rng.seed(seed);

    double dt = min(5.0/(a*(double) N), 1.0/(b*(double) N));
    dt = min(dt,1.0/(c*(double) N));
    n_steps = (int) (t_n-t_0)/dt;

    S = arma::vec(n_steps);
    I = arma::vec(n_steps);
    R = arma::vec(n_steps);
    t = arma::vec(n_steps);

    S(0) = (double) S_0; double Si;
    I(0) = (double) I_0; double Ii;
    R(0) = (double) R_0; double Ri;
    t(0) = t_0; double ti;

    transition.push_back(&MC_solver::StoI);
    transition.push_back(&MC_solver::ItoR);
    transition.push_back(&MC_solver::RtoS);

    //TODO update every person but one cycle per update, also update P values every cycle
    
    int new_state, old_state;
    arma::vec3 state_counter = {(double) S_0, (double) I_0, (double) R_0};

    for (int i = 0; i < n_steps-1; i++)
    {   
        //state_counter = arma::vec3(arma::fill::zeros);

        Si = S(i);
        Ii = I(i);
        Ri = R(i);
        ti = t(i);

        //Maybe use indeces here and select pointers to functions before runtime for different modes
        P_StoI = a*Ii*dt/((double) N);
        P_ItoR = b*dt;//*Ii*dt;
        P_RtoS = c*dt;//*Ri*dt;

        for (int j = 0; j < N; j++)
        {
        //int j = (int) ((unif(rng))*(double) N); 
            old_state=population[j].get_state();
            new_state=(this->*transition[old_state])();
            population[j].set_state(new_state);
            state_counter(new_state)+=1;
            state_counter(old_state)-=1;
        }
        
        S(i+1)=state_counter(0);
        I(i+1)=state_counter(1);
        R(i+1)=state_counter(2);
        t(i+1)=ti+dt;
    }
    cout<<"MC final S = "<<S(n_steps-1)<<endl;
    cout<<"MC final I = "<<I(n_steps-1)<<endl;
    cout<<"MC final R = "<<R(n_steps-1)<<endl;
}

int MC_solver::StoI(){
    if(unif(rng) < P_StoI) {return 1;}
    else {return 0;}  
}

int MC_solver::ItoR(){
    if(unif(rng) < P_ItoR) {return 2;}
    else {return 1;}  
}

int MC_solver::RtoS(){
    if(unif(rng) < P_RtoS) {return 0;}
    else {return 2;}  
}