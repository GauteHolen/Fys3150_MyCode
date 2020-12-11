#include "MC_solver.hpp"


/*
The functions governing state transitions in the MC solver.
0 = susceptible
1 = infeted
2 = recovering
3 = born
4 = dead (natural)
5 = dead (infected)
*/


// Default scenario transitions

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

//Vaccine models
int MC_solver::SVaccine(){
    if(unif(rng) < P_StoI) {return 1;}
    else if(unif(rng) < P_StoR) {
        state_counter(6)+=1;
        return 2;
        }
    else {return 0;}  
}

int MC_solver::SBulkVaccine(){
    if(unif(rng) < P_StoI) {return 1;}
    else if(unif(rng) < P_BULK && vaccine_stock>0) {
        state_counter(6)+=1;
        vaccine_stock-=1;
        return 2;
        }
    else {return 0;}  
}



//Seasonal parameters scenario


int MC_solver::SSeasonal(){
    if(unif(rng) < P_StoI) {return 1;}
    else {return 0;}  
}

/*

int MC_solver::ItoR(){
    if(unif(rng) < P_ItoR) {return 2;}
    else {return 1;}  
}

int MC_solver::RtoS(){
    if(unif(rng) < P_RtoS) {return 0;}
    else {return 2;}  
}
*/