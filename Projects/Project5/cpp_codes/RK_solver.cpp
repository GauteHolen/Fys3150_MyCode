#include "RK_solver.hpp"
#include "functions.hpp"



//typedef double RK_solver::(RK_solver::*dtfunc)(double S, double I, double t);

RK_solver::RK_solver(){

}

void RK_solver::write_to_file(string filename){
    ofile.open("./Projects/Project5/results/"+filename+".txt");
    ofile<<"S\tI\tR\tt"<<endl;
    for (int i = 0; i < n_steps; i++)
    {
        ofile<<S(i)<<"\t"<<I(i)<<"\t"<<R(i)<<"\t"<<t(i)<<endl;
    }
}

void RK_solver::expected_values(){
    ES=b/a;
    EI=(1-b/a)/(1+b/c);
    ER=(b/c)*(1-b/a)/(1+b/c);
    cout<<"Expected S = "<<ES*(double)N<<endl;
    cout<<"Expected I = "<<EI*(double)N<<endl;
    cout<<"Expected R = "<<ER*(double)N<<endl;
}


void RK_solver::init_constants(double _a, double _b, double _c){
    a=_a;
    b=_b;
    c=_c;
}

void RK_solver::init_population(int _N, int _S, int _I, int _R){
    N = _N;
    S_0 = _S;
    I_0 = _I;
    R_0 = _R;
}


double RK_solver::susceptible(double S, double I, double t){
    return c*(N-S-I)-((a*S*I)/(double) N);
}

double RK_solver::infected(double S, double I, double t){
    return ((a*S*I)/(double) N) - b*I;
}


void RK_solver::solve(double t_0, double t_n, int _n_steps, double (RK_solver::*fS) (double,double,double), double (RK_solver::*fI) (double,double,double)){

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

    for (int i = 0; i < n_steps -1; i++)
    {   
        ti = (double) i * h;
        Si = S(i);
        Ii = I(i);


        Sk1=(this->*fS)(Si,Ii,ti);
        Ik1=(this->*fI)(Si,Ii,ti);

        Sk2=(this->*fS)(Si+h*0.5*Sk1,Ii+h*0.5*Ik2,ti+h*0.5);
        Ik2=(this->*fI)(Si+h*0.5*Sk1,Ii+h*0.5*Ik2,ti+h*0.5);

        Sk3 =(this->*fS)(Si + h*0.5*Sk2,Ii + h*0.5*Ik2,ti+h*0.5);
        Ik3 =(this->*fI)(Si + h*0.5*Sk2,Ii + h*0.5*Ik2,ti+h*0.5);

        Sk4 =(this->*fS)(Si + h*0.5*Sk3,Ii + h*0.5*Ik3,ti+h*0.5);
        Ik4 =(this->*fI)(Si + h*0.5*Sk3,Ii + h*0.5*Ik3,ti+h*0.5);

        S(i+1) = Si + (h/6) * (Sk1 +2*Sk2 + 2*Sk3 +Sk4);
        I(i+1) = Ii + (h/6) * (Ik1 +2*Ik2 + 2*Ik3 +Ik4);
        R(i+1) = N - S(i+1) - I(i+1);
        t(i+1) = ti + h;
    }

    cout<<"RK4 final S = "<<S(n_steps-1)<<endl;
    cout<<"RK4 final I = "<<I(n_steps-1)<<endl;
    cout<<"RK4 final R = "<<R(n_steps-1)<<endl;


    
    
    
}