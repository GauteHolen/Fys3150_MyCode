#include "MC_solver.hpp"



MC_solver::MC_solver(){

}

/**
*   @brief Initializes the parameters for the simulation

    @param _a infection rate
    @param _b recovery rate
    @param _c loss of immunity rate
    @param _d natural death rate
    @param _dI death rate due to infection
    @param _e birth rate
    @param _f vaccination rate
    @param _w angular frequency of seasonality (default 2pi)
    @param _A Max amplitude of seasonality
*/
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

/**
 * 
 * @brief initalizes a bulk vaccination mode where vaccines are given at a fixed frequency until stock runs out
 * 
 * @param _f_BULK frequency of vaccination
 * @param _bulk_stock inital stock of vaccines
 * 
 */
void MC_solver::init_bulkvacc(double _f_BULK, int _bulk_stock){
    f_BULK = _f_BULK;
    vaccine_stock = _bulk_stock;
}

/**
*   @brief Writes S, I, R, e, d, dI, f and t to a file
*
*   @param filename the name of the output file
*/
void MC_solver::write_to_file(string filename){
    cout<<"MC final S = "<<S(n_steps-1)<<endl;
    cout<<"MC final I = "<<I(n_steps-1)<<endl;
    cout<<"MC final R = "<<R(n_steps-1)<<endl;

    ofile.open("./Projects/Project5/results/MC_solver_"+filename+".txt");
    ofile<<"S\tI\tR\te\td\tdI\tf\tt"<<endl;
    for (int i = 0; i < n_steps; i++)
    {
        ofile<<S(i)<<"\t"<<I(i)<<"\t"<<R(i)<<"\t"<<E(i)<<"\t"<<D(i)<<"\t"<<DI(i)<<"\t"<<Vaccinations(i)<<"\t"<<t(i)<<endl;
    }
    ofile.close();
}


/**
*   @brief Sets the initial distribution of infected, suspectible and recovering in the population

    @param _N total population
    @param _S susceptible
    @param _I infected
    @param _R recovering
*/
void MC_solver::init_population(int _N, int _S, int _I, int _R){
    N = _N;

    S_0 = _S;
    I_0 = _I;
    R_0 = _R;

    population.clear();

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

/**
 * 
 * @brief Runs the Monte Carlo sumulation for the specified time.
 * 
 * @param t_0 start time
 * @param t_n end time
 * @param mode "BULK" enters bulk vaccination mode where a vaccine stock is implemented
 * @param extra_seed Extra unique param for when when multiple runs are started simoultaneously and the time dependent seed is the same. 
 * 
 */
void MC_solver::run(double t_0, double t_n, string _mode, int extra_seed){

    /* initialize rng seed: */
    mode = _mode;
    int seed = time(0)*extra_seed;
    rng.seed(seed);

    dt = min(5.0/(a*(double) N), 1.0/(b*(double) N));
    dt = min(dt,1.0/(c*(double) N));
    double a_seasonal;
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

    S = arma::vec(n_steps,arma::fill::zeros);
    I = arma::vec(n_steps,arma::fill::zeros);
    R = arma::vec(n_steps,arma::fill::zeros);
    t = arma::vec(n_steps,arma::fill::zeros);
    D = arma::vec(n_steps,arma::fill::zeros);
    DI = arma::vec(n_steps,arma::fill::zeros);
    E = arma::vec(n_steps,arma::fill::zeros);
    Vaccinations = arma::vec(n_steps,arma::fill::zeros);

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
        
    }
    else{
        transition.push_back(&MC_solver::SVaccine);
        transition.push_back(&MC_solver::ItoR);
        transition.push_back(&MC_solver::RtoS);
        
    }
    
    
    int new_state, old_state;

    //State counter {susceptible, infected, resistant, born, dead (natural), dead (disease), vaccines}
    state_counter = {(double) S_0, (double) I_0, (double) R_0, 0.0, 0.0, 0.0, 0.0};

    
    double start = omp_get_wtime();
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

        //Set dynamic transition probabilities
        a_seasonal=a+A*cos(w*ti);
        P_StoI = a_seasonal*Ii*dt/((double) N);

        for (int j = 0; j < N; j++)
        {
            //I don't like the amount of if-statements there are here :( makes me sad

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
    double end = omp_get_wtime();
    runtime = end - start;
}

/**
 * @brief writes critical info used for statistics for when multiple runs with the same paramaters are run
 * 
 * @param filename output file name
 * 
 */
void MC_solver::write_multiple_runs(string filename){
    double peak_time = (double) arma::index_max(I)*dt;

    double infection_over = n_steps;
    for (int i = 50; i < n_steps; i++)
    {
        if(I(i)==0){
            infection_over=(double) i*dt;
            break;
        }
    }

    ofile.open("./Projects/Project5/results/MC_solver_"+filename+".txt",std::ios::app);
    ofile<<peak_time<<"\t"<<infection_over<<"\t"<<runtime<<endl;
    ofile.close();
}

/**
 * @brief initializes the output file for the multiple runs
 * 
 * @param filename output file name
 */
double MC_solver::init_multiple_runs(string filename){
    ofile.open("./Projects/Project5/results/MC_solver_"+filename+".txt");
    ofile<<"Peak[t]\tI_over[t]\tsingle_runtime\ttoal_runtime"<<endl;
    ofile.close();

    multiple_run_start_time = omp_get_wtime();
}

void MC_solver::multiple_run_time(string filename, double multiple_start_time){
    double end_time = omp_get_wtime();
    double multiple_run_time = end_time - multiple_run_start_time;

    ofile.open("./Projects/Project5/results/MC_solver_"+filename+".txt",std::ios::app);
    ofile<<"\t\t\t"<<multiple_run_time<<endl;
    ofile.close();
}

std::vector<Person> MC_solver::get_population(){
    return population;
}