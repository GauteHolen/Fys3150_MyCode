#include "./cpp_codes/functions.hpp"
#include "./cpp_codes/RK_solver.hpp"
#include "./cpp_codes/MC_solver.hpp"
#include <omp.h>


int main(int argc, char const *argv[]){

    /*====================
    Input parameters
    ======================*/
    

    string mode = argv[1];
    string filename = argv[2];
    double a = atof(argv[3]);
    double b = atof(argv[4]);
    double c = atof(argv[5]);
    int S_0 = atoi(argv[6]);
    int I_0 = atoi(argv[7]);
    int R_0 = atoi(argv[8]);
    double t_0 = atof(argv[9]);
    double t_n = atof(argv[10]);
    double n_steps = atof(argv[11]);
    double N = S_0 + R_0 + I_0;

    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    cout<<"c = "<<c<<endl;

    double d = atof(argv[12]);
    double dI = atof(argv[13]);
    double e = atof(argv[14]);

    double f = atof(argv[15]);
    double w = atof(argv[16]);
    double A = atof(argv[17]);
    double f_BULK = atof(argv[18]);
    double bulk_stock = atoi(argv[19]);

    /*------------------------------------------------------------
    
    /*====================
    Runge-Kutta solver
    ======================*/

    RK_solver solver;
    solver.init_constants(a,b,c,d,dI,e,f,w,A);
    solver.init_population(N,S_0,I_0,R_0);

    if(d+dI+e+f+A==0){
        //Simple case with only a,b and c
        cout<<"Runge-Kutta solver with no optional parameters"<<endl;
        solver.solve(t_0,t_n,n_steps, &RK_solver::susceptible, &RK_solver::infected, &RK_solver::recovering);
    }
    else if(d+dI+e>0 && f+A == 0){
        //Only vital parameters
        cout<<"Runge-Kutta solver with only option: vital"<<endl;
        solver.solve(t_0,t_n,n_steps, &RK_solver::vitalS, &RK_solver::vitalI, &RK_solver::vitalR);
    }
    else if(f>0 && d+dI+e+A == 0){
        cout<<"Runge-Kutta solver with only opetion: vaccination"<<endl;
        solver.solve(t_0,t_n,n_steps, &RK_solver::vaccineS, &RK_solver::vaccineI, &RK_solver::vaccineR);

    }
    else if(A>0 && d+dI+e+f == 0){
        cout<<"Runge-Kutta solver with only seasonal variations"<<endl;
        solver.solve(t_0,t_n,n_steps, &RK_solver::seasonalS, &RK_solver::seasonalI, &RK_solver::seasonalR);
    }
    else{
        //Cover all parameters
        cout<<"Runge-Kutta solver more than one optional parameter group"<<endl;
        solver.solve(t_0,t_n,n_steps, &RK_solver::allS, &RK_solver::allI, &RK_solver::allR);
    }
    
    solver.expected_values();
    solver.write_to_file(filename);


    /*------------------------------------------------------------

    /*====================
    Monte Carlo solver
    ======================*/


    if(mode=="multiple"){
        int n_runs = atoi(argv[20]);
        MC_solver mc_multiple;
        cout<<"Multiple run mode"<<endl;
        double start_time = mc_multiple.init_multiple_runs(filename);
        {
        #pragma omp parallel for 
            for (int i = 0; i < n_runs; i++)
            {   
                MC_solver *mc_solver = new MC_solver;
                mc_solver->init_constants(a,b,c,d,dI,e,f,w,A);
                mc_solver->init_population(N,S_0,I_0,R_0);
                mc_solver->run(t_0,t_n,mode,i+1);
                mc_solver->write_multiple_runs(filename);
                delete  mc_solver;
            }
        }
        mc_multiple.multiple_run_time(filename,start_time);
    }
    else
    {   
        MC_solver mc_solver;
        mc_solver.init_constants(a,b,c,d,dI,e,f,w,A);
        mc_solver.init_population(N,S_0,I_0,R_0);
        if(mode=="BULK"){
            mc_solver.init_bulkvacc(f_BULK, bulk_stock);
        }
        mc_solver.run(t_0,t_n,mode,1);
        mc_solver.write_to_file(filename);   
    }
    
    

}