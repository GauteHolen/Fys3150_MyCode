#include "MC_solver.hpp"



MC_solver::MC_solver(){

}


void MC_solver::init_constants(double _a, double _b, double _c, double _d, double _dI, double _e, double _f, double _w, double _A){
    a=_a;
    b=_b;
    c=_c;
    e = _e;
    d = _d;
    dI = _dI;
    f = _f;
    w = _w;
    A = _A;
}

void MC_solver::init_bulkvacc(double _f_BULK, int _bulk_stock){
    f_BULK = _f_BULK;
    vaccine_stock = _bulk_stock;
}

void MC_solver::write_to_file(string filename){
    ofile.open("./Projects/Project5/results/MC_solver_"+filename+".txt");
    ofile<<"S\tI\tR\te\td\tdI\tf\tt"<<endl;
    for (int i = 0; i < n_steps; i++)
    {
        ofile<<S(i)<<"\t"<<I(i)<<"\t"<<R(i)<<"\t"<<E(i)<<"\t"<<D(i)<<"\t"<<DI(i)<<"\t"<<Vaccinations(i)<<"\t"<<t(i)<<endl;
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

void MC_solver::run(double t_0, double t_n, string _mode){
    /* initialize rng seed: */
    mode = _mode;
    int seed = time(0);
    rng.seed(seed);

    double dt = min(5.0/(a*(double) N), 1.0/(b*(double) N));
    dt = min(dt,1.0/(c*(double) N));
    //dt = min(dt, 1.0/(f_BULK*(double) N));
    P_BULK = f_BULK*dt;
    //Set static transition probabilities
    P_StoR = f*dt;
    P_ItoR = b*dt;
    P_RtoS = c*dt;
    P_d = d*dt;
    P_dI = dI*dt;
    P_e = e*dt;

    n_steps = (int) (t_n-t_0)/dt;

    S = arma::vec(n_steps);
    I = arma::vec(n_steps);
    R = arma::vec(n_steps);
    t = arma::vec(n_steps);
    D = arma::vec(n_steps);
    DI = arma::vec(n_steps);
    E = arma::vec(n_steps);
    Vaccinations = arma::vec(n_steps);

    S(0) = (double) S_0; double Si;
    I(0) = (double) I_0; double Ii;
    R(0) = (double) R_0; double Ri;
    t(0) = t_0; double ti;
    D(0) = 0;
    DI(0) = 0;
    E(0) = 0;
    Vaccinations(0) = 0;

    if(mode=="BULK"){
        transition.push_back(&MC_solver::SBulkVaccine);
        transition.push_back(&MC_solver::ItoR);
        transition.push_back(&MC_solver::RtoS);
        cout<<"BULK vaccine mode"<<endl;
    }
    else{
        transition.push_back(&MC_solver::SVaccine);
        transition.push_back(&MC_solver::ItoR);
        transition.push_back(&MC_solver::RtoS);
        cout<<"constant vaccin rate mode"<<endl;
    }
    
    
    int new_state, old_state;
    //State counter {susceptible, infected, resistant, born, dead (natural), dead (disease), vaccines}
    state_counter = {(double) S_0, (double) I_0, (double) R_0, 0.0, 0.0, 0.0, 0.0};

    

    for (int i = 0; i < n_steps-1; i++)
    {   
        //Resets state_counter
        state_counter(3) = 0;
        state_counter(4) = 0;
        state_counter(5) = 0;
        state_counter(6) = 0;

        Si = S(i);
        Ii = I(i);
        Ri = R(i);
        ti = t(i);

        //Maybe use indeces here and select pointers to functions before runtime for different modes

        //Set dynamic transition probabilities
        P_StoI = a*Ii*dt/((double) N) + A*cos(w*ti);

        for (int j = 0; j < N; j++)
        {
            //Death/Birth rates
            if(unif(rng)<P_e){
                Person person(0);
                population.push_back(person);
                state_counter(0)+=1;
                state_counter(3)+=1;
                N+=1;
            }

            //If dead, remove, else proceed as normal
            old_state=population[j].get_state();
            if (unif(rng)<P_d)
            {   
                state_counter(old_state)-=1;
                population.erase(population.begin() + j);
                state_counter(4)+=1;
                N-=1;
            }
            else if(old_state==1 && unif(rng)<P_dI){
                state_counter(old_state)-=1;
                population.erase(population.begin() + j);
                state_counter(5)+=1;
                N-=1;
            }
            else
            {   
                new_state=(this->*transition[old_state])();
                population[j].set_state(new_state);
                state_counter(new_state)+=1;
                state_counter(old_state)-=1;
            }
        }
        
        S(i+1)=state_counter(0);
        I(i+1)=state_counter(1);
        R(i+1)=state_counter(2);
        E(i+1)=state_counter(3);
        D(i+1)=state_counter(4);
        DI(i+1)=state_counter(5);
        Vaccinations(i+1)=state_counter(6);
        t(i+1)=ti+dt;

    }
    cout<<"MC final S = "<<S(n_steps-1)<<endl;
    cout<<"MC final I = "<<I(n_steps-1)<<endl;
    cout<<"MC final R = "<<R(n_steps-1)<<endl;
}