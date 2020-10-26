#ifndef Body_HPP
#define Body_HPP

#include <iostream>
#include <armadillo>
#include <fstream>
#include <iomanip>

using namespace std;

class  Body
{
public:
    string name;
    arma::vec3 position;
    arma::vec3 velocity;
    arma::vec3 Fg;
    double mass;
    string folderpath;

    void write_to_file(double t);
    Body(arma::vec3 pos, arma::vec3 vel, double m, string name_,bool affected_by_Fg_, bool contributes_to_Fg_);
    Body(arma::vec3 pos, arma::vec3 vel, double m, string name_,bool affected_by_Fg_);
    Body(const Body &body);
    void print();
    void set_folderpath(string path);
    bool affected_by_Fg;
    bool contributes_to_Fg;
    bool lost;

    double get_r();
    double get_speed();
    arma::vec3 get_momentum_vector();

private:
    string filename;
    ofstream ofile;

};

#endif 