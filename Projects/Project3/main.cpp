#include "./cpp_codes_OO/SolarSystem.hpp"
#include "./cpp_codes_OO/Body.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>
#include <iostream>
#include <iomanip>


using namespace arma;

int main(int argc, char const *argv[]){

    int n = atoi(argv[1]);
    double t_n = atof(argv[2]);
    string name = argv[3];

    ofstream ofile;


    double h = t_n/(double) n;

    double pi = arma::datum::pi;

    vec3 pos_E = {1.0, 0.0, 0.0};
    vec3 v_E = {0.0, 2*pi, 0.0};

    Body earth(pos_E, v_E, 0.000003, "earth");

    vec3 pos_S = {0.0, 0.0 ,0.0};
    Body sun(pos_S,pos_S,1,"sun");

    SolarSystem solarsystem(name);
    solarsystem.add_body(earth);
    solarsystem.add_body(sun);
    
    solarsystem.run(n,t_n);
    solarsystem.print();



}