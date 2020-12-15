#include "RK_solver.hpp"



/*
================================================================================================
This file contains the methods and implementation of running the fourth order Runge-Kutta
solver for the SIRS ODE.

The solve function takes pointers to the different S, I and R functions in RK_functions.cpp
as input arguments, as it will run the same way regardless of how S, I and R is defined.

If possible, the solve function will use a simplified set of differential equations of only
2 equations utilizing only S and I. However, if the simplification is not run, the full 3 
 equations are used (S, I and R).
================================================================================================
*/

RK_solver::RK_solver(){

}

/**
*   @brief Writes S, I, R, e, d, dI, f and t to a file
*
*   @param filename the name of the output file
*/
void RK_solver::write_to_file(string filename){
    cout<<"Writing results to file: "<<"./Projects/Project5/results/RK_solver_"+filename+".txt"<<endl;
    ofile.open("./Projects/Project5/results/RK_solver_"+filename+".txt");
    ofile<<"S\tI\tR\te\td\tdI\tf\tt"<<endl;
    for (int i = 0; i < n_steps; i++)
    {
        double Si = S(i);
        double Ii = I(i);
        double Ri = R(i);
        double Ni = Si+Ri+Ii;
        double di = Ni*d*h;
        double dIi = Ii*dI*h;
        double ei = e*(Si+Ri+Ii)*h;
        double fi = f*Si*h;

        ofile<<Si<<"\t"<<Ii<<"\t"<<Ri<<"\t"<<ei<<
        "\t"<<di<<"\t"<<dIi<<"\t"<<fi<<"\t"<<t(i)<<endl;
    }
    ofile.close();
}

void RK_solver::print_runtime(){
    cout<<"RK solver runtime = "<<runtime<<endl;
}

/**
*   @brief Prints expected values of S, I and R
*/
void RK_solver::expected_values(){
    ES=b/a;
    EI=(1-b/a)/(1+b/c);
    ER=(b/c)*(1-b/a)/(1+b/c);
    cout<<"Expected S = "<<ES*(double)N<<endl;
    cout<<"Expected I = "<<EI*(double)N<<endl;
    cout<<"Expected R = "<<ER*(double)N<<endl;
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
void RK_solver::init_constants(double _a, double _b, double _c, double _d, double _dI, double _e, double _f, double _w, double _A){
    a=_a;
    b=_b;
    c=_c;
    d=_d;
    dI=_dI;
    e=_e;
    f=_f;
    w=_w;
    A=_A;
}

/**
*   @brief Sets the initial distribution of infected, suspectible and recovering in the population

    @param _N total population
    @param _S susceptible
    @param _I infected
    @param _R recovering
*/
void RK_solver::init_population(int _N, int _S, int _I, int _R){
    N = (double) _N;
    S_0 = _S;
    I_0 = _I;
    R_0 = _R;
}




/**
 * @brief solves the ODE for SIRS model. NOTE: init_constants and init_populations must be run first! 
 * If possible, the solve function will use a simplified set of differential equations of only
 * 2 equations utilizing only S and I. However, if the simplification is not run, the full 3 
 * equations are used (S, I and R).
 * 
 * @param t_0 Start time (usually zero)
 * @param t_n End time
 * @param _n_steps The number of time steps performed in the ODE solver
 * @param fS pointer to Susceptible member function
 * @param fI pointer to Infected member function
 * @param fR pointer to Recovering member function
 * 
 */
void RK_solver::solve(double t_0, double t_n, int _n_steps, 
                    double (RK_solver::*fS) (double,double,double,double), 
                    double (RK_solver::*fI) (double,double,double,double), 
                    double (RK_solver::*fR) (double,double,double,double)){

    n_steps = _n_steps;
    h=(t_n-t_0)/(double) n_steps;

    S = arma::vec(n_steps);
    I = arma::vec(n_steps);
    R = arma::vec(n_steps);
    t = arma::vec(n_steps);

    I(0) = I_0;
    S(0) = S_0;
    R(0) = R_0;
    t(0) = t_0;

    double ti;
    double Si;
    double Ii;
    double Ri;

    double start = omp_get_wtime();

    if(d+dI+e == 0){
        cout<<"Simplification from 3 to just 2 diff eq possible"<<endl;
        for (int i = 0; i < n_steps -1; i++)
        {   
        ti = (double) i * h;
        Si = S(i);
        Ii = I(i);
        Ri = R(i);

        Sk1=(this->*fS)(Si,Ii,Ri,ti);
        Ik1=(this->*fI)(Si,Ii,Ri,ti);
        

        Sk2=(this->*fS)(Si+h*0.5*Sk1,Ii+h*0.5*Ik2,Ri,ti+h*0.5);
        Ik2=(this->*fI)(Si+h*0.5*Sk1,Ii+h*0.5*Ik2,Ri,ti+h*0.5);

        Sk3 =(this->*fS)(Si + h*0.5*Sk2,Ii + h*0.5*Ik2,Ri,ti+h*0.5);
        Ik3 =(this->*fI)(Si + h*0.5*Sk2,Ii + h*0.5*Ik2,Ri,ti+h*0.5);

        Sk4 =(this->*fS)(Si + h*0.5*Sk3,Ii + h*0.5*Ik3,Ri,ti+h*0.5);
        Ik4 =(this->*fI)(Si + h*0.5*Sk3,Ii + h*0.5*Ik3,Ri,ti+h*0.5);

        S(i+1) = Si + (h/6) * (Sk1 +2*Sk2 + 2*Sk3 +Sk4);
        I(i+1) = Ii + (h/6) * (Ik1 +2*Ik2 + 2*Ik3 +Ik4);
        //R(i+1) = N-S(i+1)-I(i+1);
        R(i+1) = N - S(i+1) - I(i+1);
        t(i+1) = ti + h;
        N=S(i+1)+R(i+1)+I(i+1);
        }
    }
    else
    {   
        cout<<"Simplification from 3 to 2 diff eq NOT possible"<<endl;
        for (int i = 0; i < n_steps -1; i++)
        {   
        ti = (double) i * h;
        Si = S(i);
        Ii = I(i);
        Ri = R(i);
        N=Si+Ii+Ri;

        Sk1=(this->*fS)(Si,Ii,Ri,ti);
        Ik1=(this->*fI)(Si,Ii,Ri,ti);
        Rk1=(this->*fR)(Si,Ii,Ri,ti);
        //N=Sk1+Ik1+Rk1;
        
        Sk2=(this->*fS)(Si+h*0.5*Sk1,Ii+h*0.5*Ik2,Ri+h*0.5*Rk1,ti+h*0.5);
        Ik2=(this->*fI)(Si+h*0.5*Sk1,Ii+h*0.5*Ik2,Ri+h*0.5*Rk1,ti+h*0.5);
        Rk2=(this->*fR)(Si+h*0.5*Sk1,Ii+h*0.5*Ik2,Ri+h*0.5*Rk1,ti+h*0.5);
        //N=Sk2+Ik2+Rk2;

        Sk3 =(this->*fS)(Si + h*0.5*Sk2,Ii + h*0.5*Ik2,Ri + h*0.5*Rk2,ti+h*0.5);
        Ik3 =(this->*fI)(Si + h*0.5*Sk2,Ii + h*0.5*Ik2,Ri + h*0.5*Rk2,ti+h*0.5);
        Rk3 =(this->*fR)(Si + h*0.5*Sk2,Ii + h*0.5*Ik2,Ri + h*0.5*Rk2,ti+h*0.5);
        //N=Sk3+Ik3+Rk3;

        Sk4 =(this->*fS)(Si + h*0.5*Sk3,Ii + h*0.5*Ik3,Ri+0.5*h*Rk3,ti+h*0.5);
        Ik4 =(this->*fI)(Si + h*0.5*Sk3,Ii + h*0.5*Ik3,Ri+0.5*h*Rk3,ti+h*0.5);
        Rk4 =(this->*fR)(Si + h*0.5*Sk3,Ii + h*0.5*Ik3,Ri+0.5*h*Rk3,ti+h*0.5);
        //N=Sk4+Ik4+Rk4;

        S(i+1) = Si + (h/6) * (Sk1 +2*Sk2 + 2*Sk3 +Sk4);
        I(i+1) = Ii + (h/6) * (Ik1 +2*Ik2 + 2*Ik3 +Ik4);
        R(i+1) = Ri + (h/6) * (Rk1 +2*Rk2 + 2*Rk3 +Rk4);

        t(i+1) = ti + h;
        }
        double end = omp_get_wtime();
        runtime = end-start;
    }
    
    

    cout<<"RK4 final S = "<<S(n_steps-1)<<endl;
    cout<<"RK4 final I = "<<I(n_steps-1)<<endl;
    cout<<"RK4 final R = "<<R(n_steps-1)<<endl;
}


double RK_solver::get_last_I(){
    return I(n_steps-1);
}