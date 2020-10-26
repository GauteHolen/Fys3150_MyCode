#ifndef SolarSystem_HPP
#define SolarSystem_HPP

#include "Body.hpp"
#include <armadillo>
#include <sys/stat.h>
#include <fstream>

class SolarSystem
{
private:
    double h;
    double t;
    

    double pi;
    double G; //with scaling AU and years
    double c; //speed of light in AU/year
    std::vector<Body> bodies;
    arma::vec3 get_Fg(Body &body);
    void update();
    double relativistic_correction(arma::vec3 r, arma::vec3 v);
    double beta;
    bool relativistic;
    ofstream ofile;
    void write_init(int n, double t_n, double runtime);




public:
    string name;
    SolarSystem(string name_);
    void add_body(Body &body);
    void run(int n, double t_n, bool GR, double Beta);
    int n_bodies;
    void print();
    string foldername;
    double system_radius;

    double get_angular_momentum();


};


#endif