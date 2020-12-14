#include "RK_solver.hpp"

/*
================================================================================================
This file contains the RK functions for susceptible, infected and recovering in the SIRS model
================================================================================================
*/

//Simple case
double RK_solver::susceptible(double S, double I, double R, double t){
    return c*R-((a*S*I)/ N);
}

double RK_solver::infected(double S, double I, double R, double t){
    return ((a*S*I)/ N) - b*I;
}

double RK_solver::recovering(double S, double I, double R, double t){
    return b*I-c*R;
}

//Vital parameterss

double RK_solver::vitalS(double S, double I, double R, double t){
    return c*R-((a*S*I)/ N)-d*S +e*N;

}
double RK_solver::vitalI(double S, double I, double R, double t){
    return ((a*S*I)/ N) - b*I - dI*I - d*I;
}
double RK_solver::vitalR(double S, double I, double R, double t){
    return b*I-c*R-d*R;

}

//Vaccine
double RK_solver::vaccineS(double S, double I, double R, double t){
    return c*R-((a*S*I)/ N) -S*f;
}
double RK_solver::vaccineI(double S, double I, double R, double t){
     return ((a*S*I)/ N) - b*I;
}
double RK_solver::vaccineR(double S, double I, double R, double t){
    //Unused
}
//Seasonal
double RK_solver::seasonalS(double S, double I, double R, double t){
    return c*R-((a*S*I)/ N);
}
double RK_solver::seasonalI(double S, double I, double R, double t){
    double a_seasonal = a + A*cos(w*t);
    return (((a_seasonal*S*I)/ N) - b*I);
}
double RK_solver::seasonalR(double S, double I, double R, double t){
    //unused
}

//Include all cases
double RK_solver::allS(double S, double I, double R, double t){
    return c*R-((a*S*I)/ N)-d*S +e*N -S*f;

}
double RK_solver::allI(double S, double I, double R, double t){
    double a_seasonal = a + A*cos(w*t);
    return (((a_seasonal*S*I)/ N) - b*I)- dI*I - d*I;

}
double RK_solver::allR(double S, double I, double R, double t){
    return b*I-c*R-d*R +S*f;
}