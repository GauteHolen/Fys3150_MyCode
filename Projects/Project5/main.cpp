#include "./cpp_codes/functions.hpp"
#include "./cpp_codes/RK_solver.hpp"


int main(int argc, char const *argv[]){

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

    

    RK_solver solver;
    solver.init_constants(a,b,c);
    solver.init_population(N,S_0,I_0,R_0);
    solver.solve(t_0,t_n,n_steps, &RK_solver::susceptible, &RK_solver::infected);
    solver.expected_values();
    solver.write_to_file(filename);


}