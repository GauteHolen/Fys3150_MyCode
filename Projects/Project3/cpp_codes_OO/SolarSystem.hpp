#ifndef SolarSystem_HPP
#define SolarSystem_HPP

#include "Body.hpp"
#include <armadillo>
#include <sys/stat.h>

class SolarSystem
{
private:
    double h;
    double t;
    string foldername;

    double pi;
    double G;
    std::vector<Body> bodies;
    arma::vec3 get_Fg(Body &body);
    void update();



public:
    string name;
    SolarSystem(string name_);
    void add_body(Body &body);
    void run(int n, double t_n);
    int n_bodies;
    void print();


};


#endif