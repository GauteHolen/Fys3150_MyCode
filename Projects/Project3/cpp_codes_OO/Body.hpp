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

    void write_to_file(string foldername, double t);
    Body(arma::vec3 pos, arma::vec3 vel, double m, string name_);
    Body(const Body &body);
    void print();

private:
    string filename;
    ofstream ofile;

};

#endif 